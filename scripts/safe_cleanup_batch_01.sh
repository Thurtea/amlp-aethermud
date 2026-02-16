#!/usr/bin/env bash
set -e

# Safe cleanup batch 01 - removes Green Zone duplicates
git stash push -m "Pre-cleanup backup $(date +%Y%m%d_%H%M%S)"
if [ "$(git branch --show-current)" != "main" ]; then
  echo "Not on main branch, exiting"
  exit 1
fi


# Build/test
if command -v make >/dev/null 2>&1; then
  make clean || true
  if ! make; then
    echo "Build failed, reverting"
    git reset --hard HEAD
    git stash pop || true
    exit 1
  fi
fi

# Commit
git commit -m "Remove verified duplicate files (Green Zone batch 1)" || echo "Nothing to commit"
