#!/usr/bin/env python3
"""Build a compact LLM-friendly index from archived-md/ttrpg-references.json

Writes `lib/llm_index.json` containing an array of condensed entries with
fields useful for prompting an LLM when filling placeholders/stubs.
"""
import json
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
SRC = ROOT / "archived-md" / "ttrpg-references.json"
OUT = ROOT / "lib" / "llm_index.json"


def slugify(s: str) -> str:
    s = s or ""
    s = s.strip().lower()
    s = re.sub(r"[^a-z0-9]+", "-", s)
    s = re.sub(r"-+", "-", s).strip("-")
    return s or "entry"


def short(text: str, n: int = 300) -> str:
    if not text:
        return ""
    t = re.sub(r"\s+", " ", text).strip()
    return t if len(t) <= n else t[: n - 1].rsplit(" ", 1)[0] + "…"


def build():
    print(f"Reading {SRC}")
    data = json.loads(SRC.read_text(encoding="utf-8"))
    entries = data.get("entries", [])
    out = []
    for e in entries:
        name = e.get("name") or e.get("id")
        if not name:
            continue
        slug = slugify(name if not name.isdigit() else (e.get("id") or name))
        target = f"lib/occs/{slug}.lpc"

        item = {
            "id": e.get("id"),
            "name": name,
            "slug": slug,
            "section": e.get("section"),
            "description": short(e.get("description") or e.get("raw_text"), 400),
            "attribute_requirements": e.get("attribute_requirements_parsed"),
            "occ_skills": e.get("occ_skills_list") or e.get("occ_skills"),
            "standard_equipment": e.get("standard_equipment_list") or e.get("standard_equipment"),
            "money": e.get("money"),
            "cybernetics": e.get("cybernetics"),
            "ppe": e.get("ppe"),
            "source_range": e.get("source_line_range"),
            "raw_snippet": short(e.get("raw_text"), 800),
            "suggested_target": target,
        }
        out.append(item)

    OUT.parent.mkdir(parents=True, exist_ok=True)
    OUT.write_text(json.dumps({"meta": {"source": str(SRC), "entries": len(out)}, "entries": out}, indent=2), encoding="utf-8")
    print(f"Wrote {OUT} with {len(out)} entries")


if __name__ == "__main__":
    build()
