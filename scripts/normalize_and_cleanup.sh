#!/usr/bin/env bash
set -euo pipefail

# Normalize trivial differences (whitespace/comments) then remove duplicates.
# This script expects a small list of pairwise trivial duplicates. If none,
# it exits cleanly.

TRIVIAL_PAIRS=(
  # Add pairs as: "file_keep:file_remove"
  # Example: "src/foo.c:mud-references/old/foo.c"
)

if [ ${#TRIVIAL_PAIRS[@]} -eq 0 ]; then
  echo "No Red-Trivial pairs detected. Nothing to normalize."
  exit 0
fi

for pair in "${TRIVIAL_PAIRS[@]}"; do
  keep=${pair%%:*}
  remove=${pair#*:}
  echo "Processing trivial pair: keep=$keep remove=$remove"
  if command -v clang-format >/dev/null 2>&1; then
    clang-format -i "$keep" || true
    clang-format -i "$remove" || true
  else
    echo "clang-format not available — skipping formatting step"
  fi

  if cmp -s "$keep" "$remove"; then
    if git ls-files --error-unmatch "$remove" >/dev/null 2>&1; then
      git rm -- "$remove"
    else
      rm -v -- "$remove"
    fi
    echo "Removed duplicate: $remove"
  else
    echo "After normalization files still differ: $keep vs $remove — skipping"
  fi
done

echo "normalize_and_cleanup.sh completed."
