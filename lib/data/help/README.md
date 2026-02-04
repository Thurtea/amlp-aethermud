===============================================================================
HELP DAEMON - HELPER FUNCTIONS
===============================================================================

This file documents the help system implementation for AetherMUD.

HELP FILE STRUCTURE:
-------------------
/lib/data/help/
  commands/      - Command help files (attack, introduce, etc.)
  concepts/      - Concept help (combat, identity, getting-started)
  occs/          - OCC-specific help files
  systems/       - System help (races, occs, magic, psionics)

FILE NAMING:
-----------
- All lowercase
- Hyphens for spaces (getting-started, hand-to-hand)
- No .txt extension (plain text files)

HELP FILE FORMAT:
----------------
Line 1: Title bar (80 =)
Line 2: Title centered
Line 3: Title bar (80 =)
Line 4: Blank
Content: Formatted text with sections
Last lines: Related commands/topics

EXAMPLE:
========
===============================================================================
COMMAND NAME
===============================================================================

SYNTAX:
  command <args>

DESCRIPTION:
  What it does...

EXAMPLES:
  > command example
  Result shown

NOTES:
  - Important info
  - Warnings

RELATED:
  other commands

===============================================================================
