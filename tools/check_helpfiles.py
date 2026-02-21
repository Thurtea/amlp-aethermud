#!/usr/bin/env python3
import os
import re

# Desired helpfile names (as provided)
HELP_NAMES = """
aberrant abilities account advance air warlock alias
alignment anarchist ansi assassination assist assistance
atlantean nomad attack autododge autoparry body fixer bot
bots bounty hunter brief bug card chat
city rat coalition grunt color colorize combat commands
communication concept concept1 concept2 consent converse
crazy cs grunt cs military specialist cs ranger cs samas pilot cs samas rpa
cs specialist cs tech-officer cs technical officer cs tech officer customize cyber-doc
cyber-knight cyberknight death delphi juicer description diabolic
disclaimer disposition dodge drop echo eject
email emote eq exa examine experience
face faq forger forget forward freelance spy
get getting-started gifted gypsy give glitter boy pilot glitterboy pilot
goal greet harassment headhunter help history
horror hyperion juicer i icq idea index
information information sharing insert introduce introduction introduction2
iss peacekeeper iss specter items juicer kill kittani field mechanic
kittani warrior knight l language laugh left
levels lineecho linerows line walker look map
master assassin mercs misc miscreant movement multi-playing
multiplaying mystic names nega-psychic news ngr mechanic
ngr soldier ninja juicer nomad ntset protector occs ooc
operator palmer palmer2 parry password pemote
picture pirate position post principled privacy
privacy-policy professional thief prompt psihelp psionics quests
quit radio religion remember remove reply
reporting rest aethermud right rogue scholar rogue scientist
roleplaying royal knight rules rules.990925 rules.old sailorm
save saving throws say sbar score scrupulous
sentiment sirname skills slave smuggler special forces
staff starting equipment stats stop suicide syntax
take tattooed-man tell testcolor thank think
three strikes policy tips trigger triggers typo unload
unprincipled unwield vagabond vehicles view wake
weapon wear whimpy whisper who wield
wilderness scout wimpy withdraw wizardship wizardship.old wizardship2
worn www
""".split()

ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), '..'))
SEARCH_DIRS = [
    os.path.join(ROOT, 'lib'),
]

# normalize: remove non-alnum, lowercase
def norm(s):
    return re.sub(r'[^a-z0-9]', '', s.lower())

# build file index: map normalized basename -> list of paths
index = {}
for base in SEARCH_DIRS:
    for dirpath, dirs, files in os.walk(base):
        for fn in files:
            name, ext = os.path.splitext(fn)
            key = norm(name)
            index.setdefault(key, []).append(os.path.join(dirpath, fn))

found = {}
missing = []

for name in HELP_NAMES:
    key = norm(name)
    matches = []
    # exact match
    if key in index:
        matches.extend(index[key])
    else:
        # substring match on normalized filename
        for k, paths in index.items():
            if key in k:
                matches.extend(paths)
    if matches:
        found[name] = sorted(set(matches))
    else:
        missing.append(name)

out_dir = os.path.join(ROOT, 'data')
os.makedirs(out_dir, exist_ok=True)
report_path = os.path.join(out_dir, 'helpfile_scan_report.txt')
with open(report_path, 'w') as f:
    f.write('Helpfile scan report\n')
    f.write('Root: %s\n\n' % ROOT)
    f.write('FOUND:\n')
    for name, paths in sorted(found.items()):
        f.write(f"{name}:\n")
        for p in paths:
            f.write(f"  {p}\n")
    f.write('\nMISSING:\n')
    for m in sorted(missing):
        f.write(m + '\n')

print('Report written to', report_path)
print('Found:', len(found), 'Missing:', len(missing))
