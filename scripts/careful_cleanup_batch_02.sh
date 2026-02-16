#!/usr/bin/env bash
set -e
# Careful cleanup for Yellow Zone - updates includes then removes duplicates
git stash push -m "Pre-careful-cleanup $(date +%Y%m%d_%H%M%S)"
if [ "$(git branch --show-current)" != "main" ]; then
  echo "Not on main branch, exiting"
  exit 1
fi


echo "Review sed examples above and run changes manually.
"
