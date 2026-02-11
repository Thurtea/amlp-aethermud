#!/bin/bash
# AMLP Command Reorganization Script
# Dry-run mode: set DRY_RUN=1 to echo commands instead of executing them
# To perform actual moves, set DRY_RUN=0 and re-run the script

DRY_RUN=1
ROOT="/home/thurtea/amlp-aethermud"

run() {
    if [ "$DRY_RUN" -eq 1 ]; then
        echo "$@"
    else
        eval "$@"
    fi
}

# Section 1: Move creator/ files to creators/
echo "Section 1: Move creator/ -> creators/"
run "mkdir -p $ROOT/lib/cmds/creators"
run "mv $ROOT/lib/cmds/creator/cd.lpc $ROOT/lib/cmds/creators/cd.lpc"
run "mv $ROOT/lib/cmds/creator/clone.lpc $ROOT/lib/cmds/creators/clone.lpc"
run "mv $ROOT/lib/cmds/creator/grep.lpc $ROOT/lib/cmds/creators/grep.lpc"
run "mv $ROOT/lib/cmds/creator/cat.lpc $ROOT/lib/cmds/creators/cat.lpc"
run "mv $ROOT/lib/cmds/creator/destruct.lpc $ROOT/lib/cmds/creators/destruct.lpc"
run "mv $ROOT/lib/cmds/creator/ls.lpc $ROOT/lib/cmds/creators/ls.lpc"
run "mv $ROOT/lib/cmds/creator/mkdir.lpc $ROOT/lib/cmds/creators/mkdir.lpc"
run "mv $ROOT/lib/cmds/creator/find.lpc $ROOT/lib/cmds/creators/find.lpc"
run "mv $ROOT/lib/cmds/creator/load.lpc $ROOT/lib/cmds/creators/load.lpc"
run "mv $ROOT/lib/cmds/creator/pwd.lpc $ROOT/lib/cmds/creators/pwd.lpc"
run "mv $ROOT/lib/cmds/creator/force.lpc $ROOT/lib/cmds/creators/force.lpc"
run "mv $ROOT/lib/cmds/creator/update.lpc $ROOT/lib/cmds/creators/update.lpc"
run "mv $ROOT/lib/cmds/creator/tail.lpc $ROOT/lib/cmds/creators/tail.lpc"
run "mv $ROOT/lib/cmds/creator/head.lpc $ROOT/lib/cmds/creators/head.lpc"
run "mv $ROOT/lib/cmds/creator/mkroom.lpc $ROOT/lib/cmds/creators/mkroom.lpc"
run "mv $ROOT/lib/cmds/creator/eval.lpc $ROOT/lib/cmds/creators/eval.lpc"
run "mv $ROOT/lib/cmds/creator/mkobject.lpc $ROOT/lib/cmds/creators/mkobject.lpc"
run "mv $ROOT/lib/cmds/creator/ed.lpc $ROOT/lib/cmds/creators/ed.lpc"

# Section 2: Move admin/ files to admins/
echo "\nSection 2: Move admin/ -> admins/"
run "mkdir -p $ROOT/lib/cmds/admins"
run "mv $ROOT/lib/cmds/admin/wiztool.lpc $ROOT/lib/cmds/admins/wiztool.lpc"
run "mv $ROOT/lib/cmds/admin/wiz.lpc $ROOT/lib/cmds/admins/wiz.lpc"
run "mv $ROOT/lib/cmds/admin/grantskill.lpc $ROOT/lib/cmds/admins/grantskill.lpc"
run "mv $ROOT/lib/cmds/admin/testskill.lpc $ROOT/lib/cmds/admins/testskill.lpc"
run "mv $ROOT/lib/cmds/admin/promote.lpc $ROOT/lib/cmds/admins/promote.lpc"
run "mv $ROOT/lib/cmds/admin/tattoogun.lpc $ROOT/lib/cmds/admins/tattoogun.lpc"
run "mv $ROOT/lib/cmds/admin/demote.lpc $ROOT/lib/cmds/admins/demote.lpc"
run "mv $ROOT/lib/cmds/admin/goto.lpc $ROOT/lib/cmds/admins/goto.lpc"
run "mv $ROOT/lib/cmds/admin/setocc.lpc $ROOT/lib/cmds/admins/setocc.lpc"
run "mv $ROOT/lib/cmds/admin/stat.lpc $ROOT/lib/cmds/admins/stat.lpc"
run "mv $ROOT/lib/cmds/admin/shutdown.lpc $ROOT/lib/cmds/admins/shutdown.lpc"

# Section 3: Move player commands to players/
echo "\nSection 3: Move top-level player commands -> players/"
run "mkdir -p $ROOT/lib/cmds/players"
run "mv $ROOT/lib/cmds/inventory.lpc $ROOT/lib/cmds/players/inventory.lpc"
run "mv $ROOT/lib/cmds/get.lpc $ROOT/lib/cmds/players/get.lpc"
run "mv $ROOT/lib/cmds/go.lpc $ROOT/lib/cmds/players/go.lpc"
run "mv $ROOT/lib/cmds/repair.lpc $ROOT/lib/cmds/players/repair.lpc"
run "mv $ROOT/lib/cmds/metamorph.lpc $ROOT/lib/cmds/players/metamorph.lpc"
run "mv $ROOT/lib/cmds/cast.lpc $ROOT/lib/cmds/players/cast.lpc"
run "mv $ROOT/lib/cmds/manifest.lpc $ROOT/lib/cmds/players/manifest.lpc"
run "mv $ROOT/lib/cmds/quit.lpc $ROOT/lib/cmds/players/quit.lpc"
run "mv $ROOT/lib/cmds/drive.lpc $ROOT/lib/cmds/players/drive.lpc"
run "mv $ROOT/lib/cmds/prompt.lpc $ROOT/lib/cmds/players/prompt.lpc"
run "mv $ROOT/lib/cmds/wield.lpc $ROOT/lib/cmds/players/wield.lpc"
run "mv $ROOT/lib/cmds/chat.lpc $ROOT/lib/cmds/players/chat.lpc"
run "mv $ROOT/lib/cmds/wear.lpc $ROOT/lib/cmds/players/wear.lpc"
run "mv $ROOT/lib/cmds/pilot.lpc $ROOT/lib/cmds/players/pilot.lpc"
run "mv $ROOT/lib/cmds/money.lpc $ROOT/lib/cmds/players/money.lpc"
run "mv $ROOT/lib/cmds/tattoos.lpc $ROOT/lib/cmds/players/tattoos.lpc"
run "mv $ROOT/lib/cmds/stats.lpc $ROOT/lib/cmds/players/stats.lpc"
run "mv $ROOT/lib/cmds/drop.lpc $ROOT/lib/cmds/players/drop.lpc"
run "mv $ROOT/lib/cmds/remove.lpc $ROOT/lib/cmds/players/remove.lpc"
run "mv $ROOT/lib/cmds/whisper.lpc $ROOT/lib/cmds/players/whisper.lpc"
run "mv $ROOT/lib/cmds/flee.lpc $ROOT/lib/cmds/players/flee.lpc"
run "mv $ROOT/lib/cmds/skills.lpc $ROOT/lib/cmds/players/skills.lpc"
run "mv $ROOT/lib/cmds/position.lpc $ROOT/lib/cmds/players/position.lpc"
run "mv $ROOT/lib/cmds/buy.lpc $ROOT/lib/cmds/players/buy.lpc"
run "mv $ROOT/lib/cmds/exits.lpc $ROOT/lib/cmds/players/exits.lpc"
run "mv $ROOT/lib/cmds/score.lpc $ROOT/lib/cmds/players/score.lpc"
run "mv $ROOT/lib/cmds/look.lpc $ROOT/lib/cmds/players/look.lpc"
run "mv $ROOT/lib/cmds/unwield.lpc $ROOT/lib/cmds/players/unwield.lpc"
run "mv $ROOT/lib/cmds/equipment.lpc $ROOT/lib/cmds/players/equipment.lpc"
run "mv $ROOT/lib/cmds/give.lpc $ROOT/lib/cmds/players/give.lpc"
run "mv $ROOT/lib/cmds/who.lpc $ROOT/lib/cmds/players/who.lpc"
run "mv $ROOT/lib/cmds/language.lpc $ROOT/lib/cmds/players/language.lpc"
run "mv $ROOT/lib/cmds/sell.lpc $ROOT/lib/cmds/players/sell.lpc"
run "mv $ROOT/lib/cmds/languages.lpc $ROOT/lib/cmds/players/languages.lpc"
run "mv $ROOT/lib/cmds/enter.lpc $ROOT/lib/cmds/players/enter.lpc"
run "mv $ROOT/lib/cmds/tell.lpc $ROOT/lib/cmds/players/tell.lpc"
run "mv $ROOT/lib/cmds/kill.lpc $ROOT/lib/cmds/players/kill.lpc"
run "mv $ROOT/lib/cmds/stop.lpc $ROOT/lib/cmds/players/stop.lpc"
run "mv $ROOT/lib/cmds/put.lpc $ROOT/lib/cmds/players/put.lpc"
run "mv $ROOT/lib/cmds/start.lpc $ROOT/lib/cmds/players/start.lpc"
run "mv $ROOT/lib/cmds/introduce.lpc $ROOT/lib/cmds/players/introduce.lpc"
run "mv $ROOT/lib/cmds/shout.lpc $ROOT/lib/cmds/players/shout.lpc"
run "mv $ROOT/lib/cmds/say.lpc $ROOT/lib/cmds/players/say.lpc"
run "mv $ROOT/lib/cmds/remember.lpc $ROOT/lib/cmds/players/remember.lpc"
run "mv $ROOT/lib/cmds/attack.lpc $ROOT/lib/cmds/players/attack.lpc"
run "mv $ROOT/lib/cmds/forget.lpc $ROOT/lib/cmds/players/forget.lpc"
run "mv $ROOT/lib/cmds/take.lpc $ROOT/lib/cmds/players/take.lpc"
run "mv $ROOT/lib/cmds/examine.lpc $ROOT/lib/cmds/players/examine.lpc"
run "mv $ROOT/lib/cmds/surname.lpc $ROOT/lib/cmds/players/surname.lpc"

# Section 4: Move common commands to common/
echo "\nSection 4: Move shared commands -> common/"
run "mkdir -p $ROOT/lib/cmds/common"
run "mv $ROOT/lib/cmds/vstatus.lpc $ROOT/lib/cmds/common/vstatus.lpc"
run "mv $ROOT/lib/cmds/test.lpc $ROOT/lib/cmds/common/test.lpc"
run "mv $ROOT/lib/cmds/help.lpc $ROOT/lib/cmds/common/help.lpc"
run "mv $ROOT/lib/cmds/users.lpc $ROOT/lib/cmds/common/users.lpc"
run "mv $ROOT/lib/cmds/credits.lpc $ROOT/lib/cmds/common/credits.lpc"

# Section 5: Delete duplicate stubs
echo "\nSection 5: Delete duplicate/top-level stub files (dry-run unless DRY_RUN=0)"
run "rm -f $ROOT/lib/cmds/cd.lpc"
run "rm -f $ROOT/lib/cmds/clone.lpc"
run "rm -f $ROOT/lib/cmds/cat.lpc"
run "rm -f $ROOT/lib/cmds/pwd.lpc"
run "rm -f $ROOT/lib/cmds/goto.lpc"
run "rm -f $ROOT/lib/cmds/shutdown.lpc"
run "rm -f $ROOT/lib/cmds/promote.lpc"
run "rm -f $ROOT/lib/cmds/eval.lpc"

# Section 6: Delete dragon directory and specific admin replacements
echo "\nSection 6: Delete incorrect structures"
run "rm -rf $ROOT/lib/cmds/dragon/"
run "rm -f $ROOT/lib/cmds/admin/promote.lpc"
run "rm -f $ROOT/lib/cmds/admin/demote.lpc"
run "rm -f $ROOT/lib/cmds/admin/grantskill.lpc"

# Section 7: Files needing manual review (commented out)
echo "\nSection 7: Manual review files - decide before uncommenting"
# Examples below are commented out - review before un-commenting to execute
# run "mv $ROOT/lib/cmds/ls.lpc $ROOT/lib/cmds/creators/ls.lpc"  # DECIDE: keep new implementation or canonical creator version
# run "mv $ROOT/lib/cmds/repair.lpc $ROOT/lib/cmds/admins/repair.lpc"  # DECIDE: player vs admin
# run "mv $ROOT/lib/cmds/metamorph.lpc $ROOT/lib/cmds/admins/metamorph.lpc"  # DECIDE: restrict
# run "mv $ROOT/lib/cmds/kill.lpc $ROOT/lib/cmds/admins/kill.lpc"  # DECIDE: check privilege

echo "\nReorganization script completed (DRY_RUN=$DRY_RUN). Review above output."
