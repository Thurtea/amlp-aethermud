LLM index for archived ttrpg references
======================================

This fileset is produced by scripts/build_llm_index.py and is intended
to give LLMs a compact, easy-to-navigate dataset to consult when auto-
generating or populating OCC/RCC stubs under lib/.

Usage
-----

- Run the builder:

  python3 scripts/build_llm_index.py

- This writes lib/llm_index.json with a meta block and entries array.

Recommended prompt pattern for the LLM when filling a stub:

1. Load the index entry by matching name or slug.
2. Provide the LLM with the description, attribute_requirements,
   occ_skills, standard_equipment, and raw_snippet fields.
3. Ask the model to generate a conservative LPC stub for
   suggested_target following existing lib/occs/*.lpc style.

Example (instruction to LLM):

Using the entry JSON (paste the entry), produce an LPC OCC file that:
- sets set_occ_name and set_occ_id to the entry values
- fills set_occ_description with a cleaned 2-3 sentence summary
- maps parsed skills and equipment into set_occ_skills and set_standard_equipment
- leaves precise numeric stat bonuses conservative and flagged for review
- keep all changes in a single file and add a comment that the content was
  auto-generated from archived-md/ttrpg-references.txt and needs review.

Security & Review
-----------------

This index is heuristic and imperfect. Always review generated stubs
before committing or bulk-applying changes into the lib tree.
