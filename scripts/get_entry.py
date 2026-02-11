#!/usr/bin/env python3
"""Fetch entries from lib/llm_index.json by slug or name, or export per-entry JSON files.

Usage examples:
  python3 scripts/get_entry.py --list
  python3 scripts/get_entry.py --slug psi_stalker
  python3 scripts/get_entry.py --name "Psi Stalker"
  python3 scripts/get_entry.py --export-dir lib/llm_entries
"""
import argparse
import json
import os
import sys

INDEX_PATH = os.path.join(os.path.dirname(__file__), '..', 'lib', 'llm_index.json')


def load_index(path=None):
    path = path or INDEX_PATH
    path = os.path.normpath(path)
    if not os.path.exists(path):
        print(f"Index not found: {path}", file=sys.stderr)
        sys.exit(2)
    with open(path, 'r', encoding='utf-8') as f:
        return json.load(f)


def list_entries(idx):
    for e in idx.get('entries', []):
        print(f"{e.get('slug','?')}: {e.get('name','(no name)')}")


def find_by_slug(idx, slug):
    for e in idx.get('entries', []):
        if e.get('slug') == slug:
            return e
    return None


def find_by_name(idx, name):
    name_l = name.lower()
    for e in idx.get('entries', []):
        if e.get('name','').lower() == name_l:
            return e
    # fallback: contains
    for e in idx.get('entries', []):
        if name_l in e.get('name','').lower():
            return e
    return None


def export_all(idx, outdir):
    os.makedirs(outdir, exist_ok=True)
    for e in idx.get('entries', []):
        slug = e.get('slug') or e.get('name','').lower().replace(' ','_')
        if not slug:
            continue
        path = os.path.join(outdir, f"{slug}.json")
        with open(path, 'w', encoding='utf-8') as f:
            json.dump(e, f, ensure_ascii=False, indent=2)
    print(f"Exported {len(idx.get('entries',[]))} entries to {outdir}")


def main(argv=None):
    p = argparse.ArgumentParser()
    p.add_argument('--index', help='Path to llm_index.json', default=INDEX_PATH)
    grp = p.add_mutually_exclusive_group()
    grp.add_argument('--list', action='store_true', help='List slugs and names')
    grp.add_argument('--slug', help='Fetch entry by slug')
    grp.add_argument('--name', help='Fetch entry by name (case-insensitive)')
    p.add_argument('--export-dir', help='Export per-entry JSON files to this directory')

    args = p.parse_args(argv)

    idx = load_index(args.index)

    if args.list:
        list_entries(idx)
        return

    if args.export_dir:
        export_all(idx, args.export_dir)
        return

    entry = None
    if args.slug:
        entry = find_by_slug(idx, args.slug)
    elif args.name:
        entry = find_by_name(idx, args.name)

    if entry is None:
        print('Entry not found', file=sys.stderr)
        sys.exit(3)

    print(json.dumps(entry, ensure_ascii=False, indent=2))


if __name__ == '__main__':
    main()
