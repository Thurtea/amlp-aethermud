#!/usr/bin/env bash
set -e
# Rollback cleanup batch 01
# Attempt to restore from stash if present
if git stash list | grep -q "Pre-cleanup backup"; then
  echo "Restoring stash..."
  git stash pop || true
else
  echo "No stash found; attempting to reset to previous commit"
  git reset --hard HEAD~1 || true
fi
