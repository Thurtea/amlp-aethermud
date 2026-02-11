#!/usr/bin/env python3
"""
Lightweight converter for archived-md/ttrpg-references.txt -> JSON
Creates /archived-md/ttrpg-references.json with a list of detected entries.

Heuristic approach (first pass):
- Detect entries where the heading line contains "O.C.C." or "R.C.C." (e.g. "Borg O.C.C.")
- Collect until the next such heading (or EOF)
- For each block, extract simple labeled fields if present:
  - Attribute Requirements
  - O.C.C. Skills / O.C.C. Related Skills
  - Standard Equipment
  - Money
  - Cybernetics
  - P.P.E. / I.S.P. clues
- Output JSON objects containing: id, name, source_line_range, raw_text, and extracted fields.

This is intentionally conservative: first pass focuses on reliable chunking + raw_text storage
so the data can be reviewed and improved iteratively.
"""

import json
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
SRC = ROOT / 'archived-md' / 'ttrpg-references.txt'
OUT = ROOT / 'archived-md' / 'ttrpg-references.json'

HEADING_RE = re.compile(r'\b(O\.C\.C\.|R\.C\.C\.|O\.C\.C\.s|R\.C\.C\.s)\b', re.IGNORECASE)

# Section markers
OCC_SECTION_RE = re.compile(r'Occupational Character Classes', re.IGNORECASE)
RCC_SECTION_RE = re.compile(r'Racial Character', re.IGNORECASE)

# Candidate heading: shortish title line, optionally with O.C.C./R.C.C. suffix
HEADING_CANDIDATE_RE = re.compile(r'^[A-Za-z0-9 \'"()\-]{3,80}(?:\s+(?:O\.C\.C\.|R\.C\.C\.|O\.C\.C\.s|R\.C\.C\.s))?$')

# Lines that end with a page number in a TOC (e.g., "Shifter 87")
TOC_LINE_RE = re.compile(r"\s+\d{1,4}$")
# Lines with multiple numeric tokens (likely TOC with multiple entries)
NUM_TOK_RE = re.compile(r"\d+")
LABELS = [
    'Attribute Requirements',
    'Attribute Requirements:',
    'O.C.C. Skills',
    'O.C.C. Skills:',
    'O.C.C. Related Skills',
    'O.C.C. Related Skills:',
    'O.C.C. Related Skills',
    'Standard Equipment',
    'Standard Equipment:',
    'Standard Equipment: ',
    'Money',
    'Money:',
    'Cybernetics',
    'Cybernetics:',
    'P.P.E.',
    'P.P.E.:'
]


def slugify(name: str) -> str:
    s = name.lower()
    s = re.sub(r"[^a-z0-9]+", "-", s).strip('-')
    return s


def extract_label(block_lines, label):
    # Improved extraction:
    # - match label anywhere in line (case-insensitive)
    # - capture following non-empty lines until a blank line or next label/heading
    lab_lc = label.lower().rstrip(':')
    labels_set = [l.lower().rstrip(':') for l in LABELS]
    for i, ln in enumerate(block_lines):
        if lab_lc in ln.lower():
            # capture subsequent lines until a blank line or next label-like line
            out_lines = []
            j = i + 1
            while j < len(block_lines):
                cur = block_lines[j]
                if not cur.strip():
                    break
                # stop if this line itself looks like another label header
                first_token = cur.strip().split(':', 1)[0]
                if first_token.lower() in labels_set:
                    break
                # also stop if the line is ALL CAPS and short (likely a heading)
                s = cur.strip()
                if s.isupper() and len(s) < 80 and ' ' not in s[:3] or (s.isupper() and len(s.split())<6):
                    break
                out_lines.append(cur.rstrip())
                j += 1
            return '\n'.join(out_lines).strip() or None
    return None


def detect_name_from_heading(line):
    # try to normalize heading lines like "Borg O.C.C." -> "Borg"
    ln = line.strip()
    # remove trailing page numbers or weird breaks
    ln = re.sub(r'\s{2,}', ' ', ln)
    m = re.search(r'^(.*?)(?:\s+O\.C\.C\.|\s+O\.C\.C\.|\s+R\.C\.C\.|\s+O\.C\.C\.s|\s+R\.C\.C\.s)\b', ln, re.IGNORECASE)
    if m:
        return m.group(1).strip()
    # fallback, return the whole line
    return ln


def parse_attribute_requirements(text):
    if not text:
        return None
    pairs = re.findall(r'([A-Za-z]{2,16})\s*(?:[:=\-])?\s*(\d+)', text)
    if not pairs:
        return None
    out = {}
    for k, v in pairs:
        out[k.strip().lower()] = int(v)
    return out


def parse_list_field(text):
    if not text:
        return None
    parts = re.split(r'[;\n\u2022\-\*]+|,', text)
    items = [p.strip() for p in parts if p and p.strip()]
    return items if items else None


def parse():
    text = SRC.read_text(encoding='utf-8', errors='replace')
    lines = text.splitlines()
    entries = []

    # Locate OCC and RCC sections if present to improve heading detection
    # prefer the last occurrence of the section headers (skip TOC matches)
    occ_indices = []
    rcc_indices = []
    for i, ln in enumerate(lines):
        if OCC_SECTION_RE.search(ln):
            occ_indices.append(i)
        if RCC_SECTION_RE.search(ln):
            rcc_indices.append(i)
    occ_start = occ_indices[-1] if occ_indices else None
    rcc_start = rcc_indices[-1] if rcc_indices else None

    # define a scanning range: prefer OCC section to RCC section; else whole file
    scan_ranges = []
    if occ_start is not None:
        # OCC section runs until RCC or end
        occ_end = rcc_start if (rcc_start and rcc_start > occ_start) else len(lines)
        scan_ranges.append(('occ', occ_start, occ_end))
        # if RCC exists, add it separately
        if rcc_start:
            scan_ranges.append(('rcc', rcc_start, len(lines)))
    else:
        # fallback: scan entire file for candidates
        scan_ranges.append(('all', 0, len(lines)))

    # helper to determine if a line is a heading candidate
    def is_heading_candidate(i, ln):
        if not ln.strip():
            return False
        # not too long
        if len(ln.strip()) > 80:
            return False
        # exclude lines that look like long paragraphs (contain multiple commas)
        if ln.count(',') > 2:
            return False
        # exclude obvious TOC lines that end with page numbers
        if TOC_LINE_RE.search(ln.strip()):
            return False
        # exclude lines that contain multiple numeric tokens (e.g., "Men of Arms 47 Death's Head 199")
        if len(NUM_TOK_RE.findall(ln)) > 1:
            return False
        if HEADING_RE.search(ln):
            return True
        if HEADING_CANDIDATE_RE.match(ln.strip()):
            # prefer lines that are TITLE-ISH (capitalized words)
            return True
        return False

    # Collect headings within ranges
    candidate_indices = []
    for kind, start, end in scan_ranges:
        for i in range(start, end):
            ln = lines[i]
            if is_heading_candidate(i, ln):
                # ensure not mid-paragraph: prefer blank line before or after
                prev_blank = (i == 0) or (lines[i-1].strip() == '')
                next_blank = (i+1 >= len(lines)) or (lines[i+1].strip() == '')
                # accept if either context suggests heading
                if prev_blank or next_blank or HEADING_RE.search(ln):
                    # if the following few lines contain multiple numeric tokens,
                    # this is likely a TOC block — skip it
                    toc_follow_count = 0
                    for j in range(i+1, min(i+4, len(lines))):
                        toc_follow_count += len(NUM_TOK_RE.findall(lines[j]))
                    if toc_follow_count >= 2:
                        continue
                    candidate_indices.append(i)

    # Remove duplicates and sort
    heading_idxs = sorted(set(candidate_indices))

    if not heading_idxs:
        print('No headings found with refined heuristics. Falling back to old method.', file=sys.stderr)
        return []

    # Build blocks from headings; merge headings that are very close (likely TOC lines)
    merged_heads = []
    for idx in heading_idxs:
        if not merged_heads:
            merged_heads.append(idx)
            continue
        if idx - merged_heads[-1] <= 1:
            # skip contiguous headings (TOC style), keep the first
            continue
        merged_heads.append(idx)

    for idx_num, start in enumerate(merged_heads):
        end = merged_heads[idx_num + 1] if idx_num + 1 < len(merged_heads) else len(lines)
        block_lines = lines[start:end]
        heading_line = lines[start].strip()
        # normalize name
        name = detect_name_from_heading(heading_line)
        if not name:
            # fallback: take first few words
            name = heading_line.split('\n')[0][:60].strip()
        slug = slugify(name or f'entry-{start}')
        raw_text = '\n'.join(block_lines).strip()
        # description: first non-empty paragraph after heading
        desc = None
        for ln in block_lines[1:6]:
            if ln.strip():
                desc = ln.strip()
                break
        # extracted fields (search block and a small tail for inline labels)
        attr = extract_label(block_lines, 'Attribute Requirements') or extract_label(block_lines, 'Attribute Requirements:')
        occ_skills = extract_label(block_lines, 'O.C.C. Skills') or extract_label(block_lines, 'O.C.C. Related Skills') or extract_label(block_lines, 'O.C.C. Skills:')
        related_skills = extract_label(block_lines, 'O.C.C. Related Skills')
        equipment = extract_label(block_lines, 'Standard Equipment') or extract_label(block_lines, 'Standard Equipment:')
        money = extract_label(block_lines, 'Money') or extract_label(block_lines, 'Money:')
        cyber = extract_label(block_lines, 'Cybernetics') or extract_label(block_lines, 'Cybernetics:')
        ppe = extract_label(block_lines, 'P.P.E.')

        # also try inline captures on the heading line (e.g., "Borg O.C.C.")
        inline_attr = None
        m = re.search(r'Attribute Requirements:?(.*)', heading_line, re.IGNORECASE)
        if m and m.group(1).strip():
            inline_attr = m.group(1).strip()
        if inline_attr and not attr:
            attr = inline_attr

        entry = {
            'id': slug,
            'name': name,
            'source_line_range': [start + 1, end],
            'raw_text': raw_text,
            'description': desc,
            'attribute_requirements': attr,
            'occ_skills': occ_skills,
            'occ_related_skills': related_skills,
            'standard_equipment': equipment,
            'money': money,
            'cybernetics': cyber,
            'ppe': ppe
        }
        # add parsed/structured versions where possible
        entry['attribute_requirements_parsed'] = parse_attribute_requirements(entry['attribute_requirements'])
        entry['occ_skills_list'] = parse_list_field(entry['occ_skills'])
        entry['standard_equipment_list'] = parse_list_field(entry['standard_equipment'])

        # determine section (occ/rcc/other) from scan ranges
        entry_section = 'other'
        for kind, sstart, send in scan_ranges:
            if start >= sstart and start < send:
                entry_section = kind
                break
        entry['section'] = entry_section
        entries.append(entry)

    return entries


if __name__ == '__main__':
    print('Parsing', SRC)
    entries = parse()
    print(f'Found {len(entries)} entries (heuristic OCC/RCC headings).')
    OUT.write_text(json.dumps({'meta': {'source': str(SRC), 'entries_found': len(entries)}, 'entries': entries}, indent=2, ensure_ascii=False))
    print('Wrote', OUT)
