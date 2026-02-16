#!/usr/bin/env python3
"""
duplicate_file_analysis.py
Scan repository for duplicate files and produce a Markdown report.

Usage:
    python3 scripts/duplicate_file_analysis.py

Writes report to archived-md/06_duplicate_files_analysis.md by default.

Excludes directories named: .git
"""
import os
import sys
import hashlib
from collections import defaultdict
from argparse import ArgumentParser

CHUNK_SIZE = 8192

EXT_CANONICAL = {
    '.c': 'src/',
    '.h': 'src/',
    '.lpc': 'lib/',
    '.lp': 'lib/',
}


def md5_of_file(path):
    h = hashlib.md5()
    try:
        with open(path, 'rb') as f:
            while True:
                chunk = f.read(CHUNK_SIZE)
                if not chunk:
                    break
                h.update(chunk)
    except Exception as e:
        return None
    return h.hexdigest()


def human_size(n):
    for unit in ['B','KB','MB','GB']:
        if n < 1024.0:
            return f"{n:.0f}{unit}"
        n /= 1024.0
    return f"{n:.1f}TB"


def choose_canonical(paths):
    # Heuristic: prefer src/, then lib/, then lib/include/, then shortest path
    pref_order = ['src/', 'lib/include/', 'lib/', 'config/', 'scripts/']
    for p in paths:
        for pref in pref_order:
            if f'/{pref}' in ('/' + p.replace('\\', '/')) or p.startswith(pref):
                return p
    # fallback: shortest path (lexicographic)
    return sorted(paths, key=lambda x: (len(x), x))[0]


def gather_files(root, exclude_dirs=None):
    exclude_dirs = set(exclude_dirs or ['.git'])
    name_map = defaultdict(list)       # filename -> [fullpath]
    hash_map = defaultdict(list)       # md5 -> [fullpath]
    name_size_map = defaultdict(list)  # (name,size) -> [fullpath]
    total = 0

    for dirpath, dirnames, filenames in os.walk(root):
        # filter out excluded directories in-place so os.walk won't descend
        dirnames[:] = [d for d in dirnames if d not in exclude_dirs]
        for fn in filenames:
            full = os.path.join(dirpath, fn)
            # skip if it's a directory or symlink to dir
            if os.path.islink(full):
                # include symlinked files but not broken ones
                try:
                    if os.path.isdir(os.readlink(full)):
                        continue
                except Exception:
                    pass
            try:
                st = os.stat(full)
            except Exception:
                continue
            size = st.st_size
            name_map[fn].append((full, size))
            name_size_map[(fn, size)].append(full)
            total += 1
    # compute hashes for files that appear more than once in name_map or name_size_map
    # For performance, compute for all files but cache results
    hash_cache = {}
    for name, items in list(name_map.items()):
        for full, size in items:
            if full in hash_cache:
                h = hash_cache[full]
            else:
                h = md5_of_file(full)
                hash_cache[full] = h
            if h:
                hash_map[h].append(full)
    return total, name_map, name_size_map, hash_map


def generate_report(root, report_path, exclude_dirs=None):
    total, name_map, name_size_map, hash_map = gather_files(root, exclude_dirs=exclude_dirs)

    same_name = {name:items for name,items in name_map.items() if len(items) > 1}
    same_size_name = {k:v for k,v in name_size_map.items() if len(v) > 1}
    identical_content = {h:pths for h,pths in hash_map.items() if len(pths) > 1}

    # Stats
    filename_duplicates = len(same_name)
    content_duplicates = len(identical_content)
    likely_duplicates = len(same_size_name)

    # Construct markdown
    lines = []
    lines.append('# Duplicate Files Analysis')
    lines.append('')
    lines.append(f'- Root scanned: `{os.path.abspath(root)}`')
    lines.append(f'- Total files scanned: **{total}**')
    lines.append('')

    # Section 1
    lines.append('## Section 1: Files with Same Name in Multiple Locations')
    lines.append('')
    if not same_name:
        lines.append('No filename collisions detected.')
    else:
        for name, items in sorted(same_name.items()):
            lines.append(f'### `{name}`')
            for full, size in sorted(items):
                rel = os.path.relpath(full, root)
                lines.append(f'- `{rel}` — {human_size(size)}')
            # Recommendation (simple heuristic)
            # Prefer keeping a file under `src/` for C files, `lib/` for LPC files
            ext = os.path.splitext(name)[1].lower()
            rec = 'Manual review'
            if ext in ('.c', '.h'):
                rec = 'Keep the copy in `src/` and remove duplicates elsewhere (or symlink).'
            elif ext in ('.lpc', '.lp') or name.endswith('.lpc'):
                rec = 'Keep the copy in `lib/` and remove duplicates elsewhere.'
            else:
                rec = 'Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).'
            lines.append(f'**Recommendation:** {rec}')
            lines.append('')

    # Section 2
    lines.append('## Section 2: Files with Identical Content (by MD5 hash)')
    lines.append('')
    if not identical_content:
        lines.append('No files with identical content detected.')
    else:
        for h, paths in sorted(identical_content.items(), key=lambda x: x[0]):
            lines.append(f'### Hash `{h}`')
            for p in sorted(paths):
                rel = os.path.relpath(p, root)
                try:
                    size = os.path.getsize(p)
                except Exception:
                    size = 0
                lines.append(f'- `{rel}` — {human_size(size)}')
            # pick canonical
            canon = choose_canonical(paths)
            relc = os.path.relpath(canon, root)
            # recommendation based on extension
            ext = os.path.splitext(canon)[1].lower()
            if ext in ('.c', '.h'):
                recommended = f'Canonical: `{relc}` (belongs in `src/`); move others to backups or remove.'
            elif ext in ('.lpc', '.lp'):
                recommended = f'Canonical: `{relc}` (belongs in `lib/`); move others to backups or remove.'
            else:
                recommended = f'Canonical: `{relc}`; choose appropriate directory per project conventions.'
            lines.append(f'**Recommendation:** {recommended}')
            lines.append('')

    # Section 3
    lines.append('## Section 3: Likely Duplicates (Same Name + Same Size)')
    lines.append('')
    if not same_size_name:
        lines.append('No likely duplicates detected by name+size.')
    else:
        for (name, size), paths in sorted(same_size_name.items(), key=lambda x: x[0]):
            lines.append(f'### `{name}` — {human_size(size)}')
            for p in sorted(paths):
                rel = os.path.relpath(p, root)
                lines.append(f'- `{rel}`')
            lines.append('**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.')
            lines.append('')

    # Section 4
    lines.append('## Section 4: Consolidation Guide')
    lines.append('')
    lines.append('Proper directory structure (recommended):')
    lines.append('')
    lines.append('| Directory | Purpose |')
    lines.append('|---|---|')
    lines.append('| `src/` | C driver source |')
    lines.append('| `lib/` | LPC game library sources |')
    lines.append('| `lib/include/` | LPC headers and shared include files |')
    lines.append('| `config/` | Configuration files |')
    lines.append('| `docs/` | Documentation |')
    lines.append('| `scripts/` | Shell and helper scripts |')
    lines.append('| `tests/` | Test suites |')
    lines.append('| `tools/` | Development tools and utilities |')
    lines.append('')
    lines.append('Cleanup strategy:')
    lines.append('')
    lines.append('1. Verify differences with `diff -u fileA fileB` or `cmp` before removing anything.')
    lines.append('2. Determine canonical location using project conventions (see above).')
    lines.append('3. Move duplicates to a backup folder or replace with symlinks if appropriate:')
    lines.append('')
    lines.append('```sh')
    lines.append('mkdir -p archived-md/duplicates-backup')
    lines.append('mv path/to/duplicate archived-md/duplicates-backup/')
    lines.append('ln -s ../src/file.c path/to/duplicate')
    lines.append('```')
    lines.append('')
    lines.append('4. Update references in `Makefile` and include paths as needed.')
    lines.append('5. Rebuild and run tests (`make`, `make test`).')
    lines.append('6. Commit changes in a single, reviewable commit for easy rollback.')
    lines.append('')

    # Section 5
    lines.append('## Section 5: Summary Statistics')
    lines.append('')
    lines.append(f'- Total files scanned: **{total}**')
    lines.append(f'- Number of filename duplicates (same name in multiple locations): **{filename_duplicates}**')
    lines.append(f'- Number of content-duplicates (identical MD5 hash groups): **{content_duplicates}**')
    lines.append(f'- Number of likely duplicates (same name + same size): **{likely_duplicates}**')
    lines.append('')

    # Save report
    os.makedirs(os.path.dirname(report_path), exist_ok=True)
    with open(report_path, 'w', encoding='utf-8') as rf:
        rf.write('\n'.join(lines))

    # Print short summary to stdout
    print('Report written to', report_path)
    print('Total files scanned:', total)
    print('Filename duplicates:', filename_duplicates)
    print('Content duplicates:', content_duplicates)
    print('Likely duplicates (name+size):', likely_duplicates)


def main():
    p = ArgumentParser(description='Duplicate file detection and analysis for project')
    p.add_argument('--root', '-r', default='.', help='Project root directory to scan (default: current dir)')
    p.add_argument('--report', default='archived-md/06_duplicate_files_analysis.md', help='Output markdown report path')
    p.add_argument('--exclude', '-e', action='append', default=['.git'], help='Directories to exclude (can be repeated)')
    args = p.parse_args()

    root = args.root
    report = args.report
    exclude = args.exclude

    generate_report(root, report, exclude_dirs=exclude)


if __name__ == '__main__':
    main()
