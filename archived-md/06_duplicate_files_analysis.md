# Duplicate Files Analysis

- Root scanned: `/home/thurtea/amlp-aethermud`
- Total files scanned: **6142**

## Section 1: Files with Same Name in Multiple Locations

### `.gitignore`
- `.gitignore` — 488B
- `lib/.gitignore` — 232B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `223clip.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/obj/223clip.c` — 648B
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/obj/223clip.c` — 649B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/obj/223clip.c` — 693B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `223round.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/obj/223round.c` — 662B
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/obj/223round.c` — 664B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/obj/223round.c` — 678B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `357pistol.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/weap/357pistol.c` — 717B
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/weap/357pistol.c` — 757B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/weap/357pistol.c` — 742B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `357round.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/obj/357round.c` — 469B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/obj/357round.c` — 469B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `357shell.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/obj/357shell.c` — 483B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/obj/357shell.c` — 496B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `45round.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/obj/45round.c` — 494B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/obj/45round.c` — 494B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `50round.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/obj/50round.c` — 519B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/obj/50round.c` — 535B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `9mil.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/weap/9mil.c` — 553B
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/weap/9mil.c` — 590B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/weap/9mil.c` — 590B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `9mmclip.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/obj/9mmclip.c` — 649B
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/obj/9mmclip.c` — 650B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/obj/9mmclip.c` — 694B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `9mmpistol_mp.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/weap/9mmpistol_mp.c` — 925B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/weap/9mmpistol_mp.c` — 928B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `9mmround.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/obj/9mmround.c` — 442B
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/obj/9mmround.c` — 442B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/obj/9mmround.c` — 458B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `AddAlcohol`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/AddAlcohol` — 290B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/AddAlcohol` — 290B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `AddCaffeine`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/AddCaffeine` — 355B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/AddCaffeine` — 355B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `AddChannel`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/AddChannel` — 320B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/chat/AddChannel` — 320B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `AddDrink`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/AddDrink` — 289B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/AddDrink` — 289B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `AddExperiencePoints`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/AddExperiencePoints` — 370B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/AddExperiencePoints` — 370B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `AddExtraChannels`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/AddExtraChannels` — 440B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/AddExtraChannels` — 440B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `AddFingers`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/AddFingers` — 440B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/AddFingers` — 440B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `AddFood`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/AddFood` — 286B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/AddFood` — 286B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `AddHP`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/AddHP` — 268B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/AddHP` — 268B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `AddHealthPoints`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/AddHealthPoints` — 813B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/AddHealthPoints` — 813B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/player/AddHealthPoints` — 813B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `AddHeartModifier`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/AddHeartModifier` — 392B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/AddHeartModifier` — 392B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `AddLead`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/AddLead` — 271B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/AddLead` — 271B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `AddLimb`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/AddLimb` — 878B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/AddLimb` — 878B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `AddMagicPoints`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/AddMagicPoints` — 299B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/AddMagicPoints` — 299B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `AddMagicProtection`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/AddMagicProtection` — 610B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/AddMagicProtection` — 610B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `AddMoJo`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/AddMoJo` — 308B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/AddMoJo` — 308B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `AddPoison`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/AddPoison` — 299B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/AddPoison` — 299B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/poison/AddPoison` — 299B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `AddQuestPoints`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/AddQuestPoints` — 324B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/AddQuestPoints` — 324B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `AddSacrificeType`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/AddSacrificeType` — 421B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/chapel/AddSacrificeType` — 421B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `AddSkillPoints`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/AddSkillPoints` — 613B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/abilities/AddSkillPoints` — 613B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/classes/AddSkillPoints` — 613B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `CanBurn`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/CanBurn` — 291B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/burn/CanBurn` — 291B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `CanExtinguish`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/CanExtinguish` — 309B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/burn/CanExtinguish` — 309B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `CanFly`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/CanFly` — 466B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/CanFly` — 466B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/room/CanFly` — 466B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/virt_sky/CanFly` — 466B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `CanJoin`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/CanJoin` — 328B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/clan/CanJoin` — 328B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `CanLight`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/CanLight` — 190B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/light/CanLight` — 190B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `CanManipulate`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/CanManipulate` — 443B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/CanManipulate` — 443B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/manipulate/CanManipulate` — 443B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `CanMarry`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/CanMarry` — 379B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/chapel/CanMarry` — 379B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/interactive/CanMarry` — 379B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `CanReceive`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/CanReceive` — 595B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/clip/CanReceive` — 595B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/container/CanReceive` — 595B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/corpse/CanReceive` — 595B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/firearm/CanReceive` — 595B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/flashlight/CanReceive` — 595B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/furnace/CanReceive` — 595B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/holder/CanReceive` — 595B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/limb/CanReceive` — 595B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/npc/CanReceive` — 595B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/player/CanReceive` — 595B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/post_office/CanReceive` — 595B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/room/CanReceive` — 595B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `CanRelease`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/CanRelease` — 477B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/clip/CanRelease` — 477B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/container/CanRelease` — 477B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/firearm/CanRelease` — 477B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/fishing/CanRelease` — 477B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `CanRemoveItem`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/CanRemoveItem` — 354B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/CanRemoveItem` — 354B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `CanSacrifice`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/CanSacrifice` — 457B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/chapel/CanSacrifice` — 457B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `CanWear`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/CanWear` — 557B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/CanWear` — 557B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `ChangeClass`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/ChangeClass` — 311B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/classes/ChangeClass` — 311B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `ClassMember`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/ClassMember` — 299B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/classes/ClassMember` — 299B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `Contents`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lpc/basic/Contents` — 393B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lpc/intermediate/Contents` — 280B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `Copyright`
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/Copyright` — 729B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lpc/intermediate/Copyright` — 3KB
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `DestLimb`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/DestLimb` — 473B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/DestLimb` — 473B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `GNUmakefile`
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/GNUmakefile` — 9KB
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/packages/GNUmakefile` — 507B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `GetAffectLong`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetAffectLong` — 445B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetAffectLong` — 445B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/clan/GetAffectLong` — 445B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `GetAlcohol`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetAlcohol` — 317B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetAlcohol` — 317B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/race/GetAlcohol` — 317B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `GetAllowSacrifice`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetAllowSacrifice` — 386B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/chapel/GetAllowSacrifice` — 386B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `GetAmmoType`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetAmmoType` — 429B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/clip/GetAmmoType` — 429B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/firearm/GetAmmoType` — 429B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/round/GetAmmoType` — 429B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/shell/GetAmmoType` — 429B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `GetBaseStatLevel`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetBaseStatLevel` — 434B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/classes/GetBaseStatLevel` — 434B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/combat/GetBaseStatLevel` — 434B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/genetics/GetBaseStatLevel` — 434B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `GetBodyComposition`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetBodyComposition` — 309B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetBodyComposition` — 309B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `GetBonusDuration`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetBonusDuration` — 310B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/bonus/GetBonusDuration` — 310B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `GetBurnRate`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetBurnRate` — 261B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/burn/GetBurnRate` — 261B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/lamp/GetBurnRate` — 261B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `GetBurning`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetBurning` — 252B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/burn/GetBurning` — 252B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `GetBurntValue`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetBurntValue` — 277B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/burn/GetBurntValue` — 277B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `GetCaffeine`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetCaffeine` — 305B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetCaffeine` — 305B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `GetCaliber`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetCaliber` — 410B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/clip/GetCaliber` — 410B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/firearm/GetCaliber` — 410B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/round/GetCaliber` — 410B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/shell/GetCaliber` — 410B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `GetCanBite`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetCanBite` — 329B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetCanBite` — 329B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `GetCapName`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetCapName` — 294B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetCapName` — 294B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/connect/GetCapName` — 294B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/id/GetCapName` — 294B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/npc/GetCapName` — 294B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/player/GetCapName` — 294B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `GetCellType`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetCellType` — 372B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/battery/GetCellType` — 372B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetCellType` — 373B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/flashlight/GetCellType` — 372B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `GetChannels`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetChannels` — 327B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/chat/GetChannels` — 327B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `GetCharge`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetCharge` — 318B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/battery/GetCharge` — 318B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `GetClan`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetClan` — 243B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/classes/GetClan` — 243B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `GetClanName`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetClanName` — 255B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/clan/GetClanName` — 255B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `GetClanObject`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetClanObject` — 294B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/clan/GetClanObject` — 294B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `GetClanSkill`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetClanSkill` — 276B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/clan/GetClanSkill` — 276B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `GetClass`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetClass` — 260B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/classes/GetClass` — 260B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/damage/GetClass` — 260B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `GetDeathEvents`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetDeathEvents` — 459B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetDeathEvents` — 459B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `GetDrainRate`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetDrainRate` — 328B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/battery/GetDrainRate` — 328B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `GetDrainable`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetDrainable` — 288B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/battery/GetDrainable` — 288B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `GetDrink`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetDrink` — 224B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetDrink` — 224B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `GetDying`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetDying` — 347B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetDying` — 347B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `GetEncumbrance`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetEncumbrance` — 489B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetEncumbrance` — 489B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `GetEquippedLimbs`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetEquippedLimbs` — 326B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetEquippedLimbs` — 326B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `GetExperiencePoints`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetExperiencePoints` — 269B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetExperiencePoints` — 269B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `GetExtraChannels`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetExtraChannels` — 440B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetExtraChannels` — 440B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `GetFingers`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetFingers` — 427B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/armor/GetFingers` — 427B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetFingers` — 427B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/worn_storage/GetFingers` — 427B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `GetFirearmType`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetFirearmType` — 432B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/clip/GetFirearmType` — 432B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/firearm/GetFirearmType` — 432B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/round/GetFirearmType` — 432B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/shell/GetFirearmType` — 432B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `GetFood`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetFood` — 368B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetFood` — 368B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/fish/GetFood` — 368B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `GetFuelRequired`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetFuelRequired` — 280B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/burn/GetFuelRequired` — 280B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `GetHealRate`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetHealRate` — 243B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetHealRate` — 243B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/race/GetHealRate` — 243B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `GetHealthPoints`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetHealthPoints` — 396B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetHealthPoints` — 396B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `GetHealthShort`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetHealthShort` — 302B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetHealthShort` — 302B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/corpse/GetHealthShort` — 302B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `GetHeartModifier`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetHeartModifier` — 417B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetHeartModifier` — 417B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `GetHeartRate`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetHeartRate` — 261B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetHeartRate` — 261B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/race/GetHeartRate` — 261B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `GetHeat`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetHeat` — 250B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/burn/GetHeat` — 250B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `GetLead`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetLead` — 363B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetLead` — 363B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `GetLeader`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetLeader` — 359B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/clan/GetLeader` — 359B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/follow/GetLeader` — 359B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `GetLimbChildren`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetLimbChildren` — 368B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetLimbChildren` — 368B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `GetLimbClass`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetLimbClass` — 343B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetLimbClass` — 343B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `GetLimbParent`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetLimbParent` — 345B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetLimbParent` — 345B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `GetLimbs`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetLimbs` — 243B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetLimbs` — 243B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `GetLong`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetLong` — 502B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetLong` — 502B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/bot/GetLong` — 502B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/creator/GetLong` — 502B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/donate/GetLong` — 502B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/door/GetLong` — 502B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/fuel/GetLong` — 502B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/interactive/GetLong` — 502B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/lamp/GetLong` — 502B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/look/GetLong` — 502B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/npc/GetLong` — 502B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/player/GetLong` — 502B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/room/GetLong` — 502B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/torch/GetLong` — 502B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `GetMagicPoints`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetMagicPoints` — 297B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetMagicPoints` — 297B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `GetMaxHealthPoints`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetMaxHealthPoints` — 459B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetMaxHealthPoints` — 459B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/combat/GetMaxHealthPoints` — 459B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/living/GetMaxHealthPoints` — 459B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/npc/GetMaxHealthPoints` — 459B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/race/GetMaxHealthPoints` — 459B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `GetMaxMagicPoints`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetMaxMagicPoints` — 396B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetMaxMagicPoints` — 396B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/race/GetMaxMagicPoints` — 396B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `GetMaxStaminaPoints`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetMaxStaminaPoints` — 396B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetMaxStaminaPoints` — 396B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/race/GetMaxStaminaPoints` — 396B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `GetMelee`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetMelee` — 327B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetMelee` — 327B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `GetMillimeter`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetMillimeter` — 415B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/clip/GetMillimeter` — 415B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/firearm/GetMillimeter` — 415B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/round/GetMillimeter` — 415B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/shell/GetMillimeter` — 415B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `GetMinHeat`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetMinHeat` — 292B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/burn/GetMinHeat` — 292B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `GetMissingLimbParent`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetMissingLimbParent` — 356B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetMissingLimbParent` — 356B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `GetMissingLimbParents`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetMissingLimbParents` — 364B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetMissingLimbParents` — 364B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `GetMissingLimbs`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetMissingLimbs` — 440B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetMissingLimbs` — 440B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `GetMoJo`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetMoJo` — 306B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetMoJo` — 306B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `GetMorality`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetMorality` — 251B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/classes/GetMorality` — 251B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/spell/GetMorality` — 251B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `GetMoralityDescription`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetMoralityDescription` — 317B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/classes/GetMoralityDescription` — 317B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `GetName`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetName` — 369B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetName` — 369B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/creator/GetName` — 369B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/id/GetName` — 369B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/interactive/GetName` — 369B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/messages/GetName` — 369B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/npc/GetName` — 369B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/player/GetName` — 369B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `GetNoChanColors`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetNoChanColors` — 319B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/chat/GetNoChanColors` — 319B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `GetPacifist`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetPacifist` — 360B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetPacifist` — 360B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `GetPoints`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetPoints` — 325B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/bonus/GetPoints` — 325B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/potion/GetPoints` — 325B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `GetPoison`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetPoison` — 256B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetPoison` — 256B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/poison/GetPoison` — 256B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `GetProtect`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetProtect` — 306B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetProtect` — 306B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `GetQuestPoints`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetQuestPoints` — 273B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetQuestPoints` — 273B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `GetRace`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetRace` — 324B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetRace` — 324B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/corpse/GetRace` — 324B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/limb/GetRace` — 324B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/race/GetRace` — 324B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `GetRandomLimb`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetRandomLimb` — 304B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetRandomLimb` — 304B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `GetRechargeable`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetRechargeable` — 304B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/battery/GetRechargeable` — 304B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `GetReligion`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetReligion` — 264B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/chapel/GetReligion` — 264B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/classes/GetReligion` — 264B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `GetResistance`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetResistance` — 350B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetResistance` — 350B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/genetics/GetResistance` — 350B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/race/GetResistance` — 350B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `GetRestrictedChannels`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetRestrictedChannels` — 315B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/chat/GetRestrictedChannels` — 315B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `GetSacrificeType`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetSacrificeType` — 418B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/chapel/GetSacrificeType` — 418B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `GetSkillModifier`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetSkillModifier` — 323B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/classes/GetSkillModifier` — 323B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `GetSkills`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetSkills` — 702B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/abilities/GetSkills` — 702B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/bonus/GetSkills` — 702B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/potion/GetSkills` — 702B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/spell/GetSkills` — 702B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `GetSleeping`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetSleeping` — 415B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetSleeping` — 415B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `GetStaminaPoints`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetStaminaPoints` — 293B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetStaminaPoints` — 293B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `GetStats`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetStats` — 630B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/bonus/GetStats` — 630B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/genetics/GetStats` — 630B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/potion/GetStats` — 630B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `GetTorso`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetTorso` — 320B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetTorso` — 320B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `GetWielded`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetWielded` — 520B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetWielded` — 520B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/weapon/GetWielded` — 520B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `GetWieldingLimbs`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetWieldingLimbs` — 470B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetWieldingLimbs` — 470B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `GetWorn`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetWorn` — 588B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetWorn` — 588B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/equip/GetWorn` — 588B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `HandleTeller`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/HandleTeller` — 557B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/bank/HandleTeller` — 557B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `HealLimb`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/HealLimb` — 282B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/HealLimb` — 282B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `InitComposition`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/InitComposition` — 311B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/clay/InitComposition` — 311B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `Introduction`
- `mud-references/deadsouls/ds3.8.2/lib/doc/build/Introduction` — 7KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/lpc/basic/Introduction` — 6KB
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `Makefile`
- `Makefile` — 11KB
- `lib/Makefile` — 216B
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/Makefile` — 292B
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/packages/Makefile` — 407B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `ModCharge`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/ModCharge` — 315B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/battery/ModCharge` — 315B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `NewBody`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/NewBody` — 303B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/NewBody` — 303B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/race/NewBody` — 303B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `ParseHook`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/ParseHook` — 328B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/ParseHook` — 328B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `README`
- `mud-references/deadsouls/ds3.8.2/bin/README` — 417B
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/README` — 3KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/README` — 387B
- `mud-references/deadsouls/ds3.8.2/lib/doc/old/README` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/domains/Praxis/README` — 804B
- `mud-references/deadsouls/ds3.8.2/lib/domains/Praxis/adm/README` — 472B
- `mud-references/deadsouls/ds3.8.2/lib/domains/README` — 450B
- `mud-references/deadsouls/ds3.8.2/lib/domains/Ylsrim/README` — 474B
- `mud-references/deadsouls/ds3.8.2/lib/domains/Ylsrim/adm/README` — 472B
- `mud-references/deadsouls/ds3.8.2/lib/domains/Ylsrim/broken/README` — 131B
- `mud-references/deadsouls/ds3.8.2/lib/domains/Ylsrim/virtual/README` — 896B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/adm/README` — 472B
- `mud-references/deadsouls/ds3.8.2/lib/domains/cave/adm/README` — 472B
- `mud-references/deadsouls/ds3.8.2/lib/domains/examples/room/README` — 901B
- `mud-references/deadsouls/ds3.8.2/lib/domains/learning/adm/README` — 472B
- `mud-references/deadsouls/ds3.8.2/lib/obj/README` — 580B
- `mud-references/deadsouls/ds3.8.2/lib/std/README` — 384B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `README.txt`
- `mud-references/deadsouls/ds3.8.2/README.txt` — 1KB
- `mud-references/deadsouls/ds3.8.2/extra/README.txt` — 570B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `RemoveBonuses`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/RemoveBonuses` — 255B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/bonus/RemoveBonuses` — 255B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `RemoveChannel`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/RemoveChannel` — 338B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/chat/RemoveChannel` — 338B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `RemoveExtraChannels`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/RemoveExtraChannels` — 468B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/RemoveExtraChannels` — 468B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `RemoveLimb`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/RemoveLimb` — 486B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/RemoveLimb` — 486B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `RemoveMagicProtection`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/RemoveMagicProtection` — 363B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/RemoveMagicProtection` — 363B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `RestoreLimb`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/RestoreLimb` — 798B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/RestoreLimb` — 798B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `RestrictChannel`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/RestrictChannel` — 335B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/chat/RestrictChannel` — 335B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `SetAllowSacrifice`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetAllowSacrifice` — 388B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/chapel/SetAllowSacrifice` — 388B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `SetAmmoType`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetAmmoType` — 445B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/clip/SetAmmoType` — 445B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/firearm/SetAmmoType` — 445B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/round/SetAmmoType` — 445B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/shell/SetAmmoType` — 445B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `SetBodyComposition`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetBodyComposition` — 452B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/SetBodyComposition` — 452B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `SetBonusDuration`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetBonusDuration` — 351B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/bonus/SetBonusDuration` — 351B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `SetBonuses`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetBonuses` — 305B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/bonus/SetBonuses` — 305B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `SetBurnRate`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetBurnRate` — 365B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/burn/SetBurnRate` — 365B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/lamp/SetBurnRate` — 365B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `SetCaliber`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetCaliber` — 468B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/clip/SetCaliber` — 468B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/firearm/SetCaliber` — 468B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/round/SetCaliber` — 468B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/shell/SetCaliber` — 468B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `SetCanBite`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetCanBite` — 398B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/SetCanBite` — 398B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `SetCellType`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetCellType` — 411B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/battery/SetCellType` — 411B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/flashlight/SetCellType` — 411B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `SetCharge`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetCharge` — 338B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/battery/SetCharge` — 338B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `SetClan`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetClan` — 277B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/classes/SetClan` — 277B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `SetClanName`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetClanName` — 302B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/clan/SetClanName` — 302B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `SetClanObject`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetClanObject` — 323B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/clan/SetClanObject` — 323B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `SetClanSkill`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetClanSkill` — 272B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/clan/SetClanSkill` — 272B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `SetClass`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetClass` — 412B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/classes/SetClass` — 412B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/damage/SetClass` — 412B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/npc/SetClass` — 412B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/player/SetClass` — 412B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `SetComposition`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetComposition` — 722B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/clay/SetComposition` — 722B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `SetDeathEvents`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetDeathEvents` — 463B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/SetDeathEvents` — 463B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `SetDrainRate`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetDrainRate` — 431B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/battery/SetDrainRate` — 431B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/SetDrainRate` — 432B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/flashlight/SetDrainRate` — 431B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `SetDrainable`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetDrainable` — 348B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/battery/SetDrainable` — 348B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `SetExtraChannels`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetExtraChannels` — 437B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/SetExtraChannels` — 437B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `SetFingers`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetFingers` — 198B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/armor/SetFingers` — 198B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/SetFingers` — 156B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/worn_storage/SetFingers` — 198B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `SetFirearmType`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetFirearmType` — 452B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/clip/SetFirearmType` — 452B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/firearm/SetFirearmType` — 452B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/round/SetFirearmType` — 452B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/shell/SetFirearmType` — 452B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `SetFuelRequired`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetFuelRequired` — 283B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/burn/SetFuelRequired` — 283B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `SetHeat`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetHeat` — 259B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/burn/SetHeat` — 259B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `SetLeader`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetLeader` — 390B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/clan/SetLeader` — 390B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/follow/SetLeader` — 390B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `SetMelee`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetMelee` — 380B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/SetMelee` — 380B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `SetMillimeter`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetMillimeter` — 487B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/clip/SetMillimeter` — 487B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/firearm/SetMillimeter` — 487B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/round/SetMillimeter` — 487B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/shell/SetMillimeter` — 487B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `SetMinHeat`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetMinHeat` — 301B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/burn/SetMinHeat` — 301B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `SetMorality`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetMorality` — 253B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/classes/SetMorality` — 253B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/spell/SetMorality` — 253B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `SetNoChanColors`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetNoChanColors` — 345B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/chat/SetNoChanColors` — 345B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `SetPacifist`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetPacifist` — 282B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/SetPacifist` — 282B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `SetPoints`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetPoints` — 397B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/bonus/SetPoints` — 397B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/potion/SetPoints` — 397B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `SetPowerType`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetPowerType` — 307B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/battery/SetPowerType` — 307B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `SetProtect`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetProtect` — 329B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/SetProtect` — 329B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `SetRechargeable`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetRechargeable` — 296B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/battery/SetRechargeable` — 296B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `SetReligion`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetReligion` — 281B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/chapel/SetReligion` — 281B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/classes/SetReligion` — 281B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `SetSacrificeType`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetSacrificeType` — 412B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/chapel/SetSacrificeType` — 412B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `SetSkillModifier`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetSkillModifier` — 349B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/classes/SetSkillModifier` — 349B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `SetSkills`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetSkills` — 480B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/bonus/SetSkills` — 480B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/potion/SetSkills` — 480B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/spell/SetSkills` — 480B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `SetSleeping`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetSleeping` — 514B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/SetSleeping` — 514B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `SetStats`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetStats` — 365B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/bonus/SetStats` — 365B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/potion/SetStats` — 365B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `Spent`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/Spent` — 262B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/battery/Spent` — 262B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `TODO`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/TODO` — 905B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/parsing/TODO` — 905B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `UnrestrictChannel`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/UnrestrictChannel` — 341B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/chat/UnrestrictChannel` — 341B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `abox.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/obj/abox.c` — 877B
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/obj/abox.c` — 735B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `access.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/Praxis/adm/access.c` — 34B
- `mud-references/deadsouls/ds3.8.2/lib/domains/Ylsrim/adm/access.c` — 204B
- `mud-references/deadsouls/ds3.8.2/lib/secure/lib/std/access.c` — 3KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `acos`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/acos` — 246B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/floats/acos` — 246B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `activate.c`
- `mud-references/deadsouls/ds3.8.2/lib/lib/events/activate.c` — 676B
- `mud-references/deadsouls/ds3.8.2/lib/verbs/items/activate.c` — 997B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `add_action`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/add_action` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/add_action` — 2KB
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `add_action.c`
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/add_action.c` — 18KB
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/testsuite/single/tests/efuns/add_action.c` — 329B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `addr_server`
- `mud-references/deadsouls/ds3.8.2/bin/addr_server` — 24KB
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/addr_server` — 24KB
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `admin`
- `mud-references/deadsouls/ds3.8.2/lib/doc/help/creators/admin` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/news/admin` — 1KB
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `ale.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/Ylsrim/meal/ale.c` — 813B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/meals/ale.c` — 764B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/meals/ale.c` — 508B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `all_inventory`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/all_inventory` — 386B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/objects/all_inventory` — 386B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `all_previous_objects`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/all_previous_objects` — 502B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/all_previous_objects` — 502B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `allocate`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/allocate` — 264B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/arrays/allocate` — 264B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `allocate_buffer`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/allocate_buffer` — 435B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/buffers/allocate_buffer` — 435B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `allocate_mapping`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/allocate_mapping` — 798B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mappings/allocate_mapping` — 798B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `apple.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/meals/apple.c` — 529B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/obj/apple.c` — 436B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `apply.c`
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/compat/simuls/apply.c` — 265B
- `mud-references/deadsouls/ds3.8.2/lib/lib/events/apply.c` — 463B
- `mud-references/deadsouls/ds3.8.2/lib/verbs/items/apply.c` — 826B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `arch.c`
- `mud-references/deadsouls/ds3.8.2/lib/cmds/admins/arch.c` — 805B
- `mud-references/deadsouls/ds3.8.2/lib/domains/Praxis/arch.c` — 757B
- `mud-references/deadsouls/ds3.8.2/lib/secure/room/arch.c` — 7KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `arena.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/room/arena.c` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/virtual/arena.c` — 5KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `armor.c`
- `mud-references/deadsouls/ds3.8.2/lib/lib/std/armor.c` — 151B
- `mud-references/deadsouls/ds3.8.2/lib/obj/armor.c` — 448B
- `mud-references/deadsouls/ds3.8.2/lib/secure/modules/armor.c` — 6KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `array.c`
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/array.c` — 63KB
- `src/array.c` — 4KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `array.h`
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/array.h` — 2KB
- `src/array.h` — 844B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `arrayp`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/arrayp` — 156B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mixed/arrayp` — 156B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `ascii.c`
- `mud-references/deadsouls/ds3.8.2/lib/cmds/creators/ascii.c` — 1022B
- `mud-references/deadsouls/ds3.8.2/lib/secure/sefun/ascii.c` — 379B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `asin`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/asin` — 228B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/floats/asin` — 228B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `astar.c`
- `mud-references/deadsouls/ds3.8.2/lib/cmds/creators/astar.c` — 4KB
- `mud-references/deadsouls/ds3.8.2/lib/secure/sefun/astar.c` — 11KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `atan`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/atan` — 235B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/floats/atan` — 235B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `atlantean.lpc`
- `lib/languages/atlantean.lpc` — 736B
- `lib/races/atlantean.lpc` — 4KB
**Recommendation:** Keep the copy in `lib/` and remove duplicates elsewhere.

### `author_file`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/author_file` — 665B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/author_file` — 665B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `author_stats`
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/testsuite/log/author_stats` — 20B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/author_stats` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mudlib/author_stats` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/log/author_stats` — 23B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `axe.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/cave/weap/axe.c` — 488B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/weap/axe.c` — 482B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `badge.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/armor/badge.c` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/armor/badge.c` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/armor/badge.c` — 1KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `bag.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/Praxis/obj/misc/bag.c` — 501B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/obj/bag.c` — 621B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/obj/bag.c` — 359B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `bait.c`
- `mud-references/deadsouls/ds3.8.2/lib/lib/events/bait.c` — 877B
- `mud-references/deadsouls/ds3.8.2/lib/verbs/items/bait.c` — 957B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `bait.h`
- `mud-references/deadsouls/ds3.8.2/lib/lib/include/bait.h` — 298B
- `mud-references/deadsouls/ds3.8.2/lib/verbs/items/include/bait.h` — 163B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `balrog.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/Praxis/obj/mon/balrog.c` — 368B
- `mud-references/deadsouls/ds3.8.2/lib/domains/Ylsrim/npc/balrog.c` — 931B
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/npc/balrog.c` — 477B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `bandanna.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/armor/bandanna.c` — 598B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/armor/bandanna.c` — 598B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `banish.c`
- `mud-references/deadsouls/ds3.8.2/lib/daemon/banish.c` — 9KB
- `mud-references/deadsouls/ds3.8.2/lib/secure/cmds/admins/banish.c` — 2KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `bank.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/Praxis/bank.c` — 6KB
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/room/bank.c` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/lib/bank.c` — 670B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `barkeep.c`
- `mud-references/deadsouls/ds3.8.2/lib/lib/std/barkeep.c` — 7KB
- `mud-references/deadsouls/ds3.8.2/lib/obj/barkeep.c` — 478B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `basement.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/room/basement.c` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/room/basement.c` — 945B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `bboard.c`
- `mud-references/deadsouls/ds3.8.2/lib/lib/bboard.c` — 10KB
- `mud-references/deadsouls/ds3.8.2/lib/secure/daemon/bboard.c` — 5KB
- `mud-references/deadsouls/ds3.8.2/lib/secure/lib/bboard.c` — 101B
- `mud-references/deadsouls/ds3.8.2/lib/std/board/bboard.c` — 101B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `bboard.h`
- `mud-references/deadsouls/ds3.8.2/lib/lib/include/bboard.h` — 852B
- `mud-references/deadsouls/ds3.8.2/lib/secure/daemon/bboard.h` — 448B
- `mud-references/deadsouls/ds3.8.2/lib/secure/include/bboard.h` — 179B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `bbucket.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/obj/bbucket.c` — 874B
- `mud-references/deadsouls/ds3.8.2/lib/domains/cave/obj/bbucket.c` — 874B
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/obj/bbucket.c` — 876B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/obj/bbucket.c` — 874B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `bdu.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/armor/bdu.c` — 660B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/armor/bdu.c` — 697B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `bear.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/npc/bear.c` — 504B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/npc/bear.c` — 505B
- `mud-references/deadsouls/ds3.8.2/lib/shadows/bear.c` — 2KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `bearskin.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/armor/bearskin.c` — 954B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/armor/bearskin.c` — 960B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `bed.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/obj/bed.c` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/lib/std/bed.c` — 309B
- `mud-references/deadsouls/ds3.8.2/lib/obj/bed.c` — 383B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `beggar.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/Praxis/obj/mon/beggar.c` — 3KB
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/npc/beggar.c` — 3KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `bind`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/bind` — 521B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/functions/bind` — 521B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `bk.db`
- `mud-references/deadsouls/ds3.8.2/lib/realms/template/bak/bk.db` — 30B
- `mud-references/deadsouls/ds3.8.2/lib/realms/thurtea/bak/bk.db` — 43B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `blue_wins`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charles/bak2/bak1/blue_wins` — 3B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charles/bak2/blue_wins` — 2B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charles/blue_wins` — 5B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charly/bak/blue_wins` — 5B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charly/blue_wins` — 5B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `board.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/weap/board.c` — 779B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/weap/board.c` — 618B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `body.c`
- `mud-references/deadsouls/ds3.8.2/lib/lib/body.c` — 60KB
- `mud-references/deadsouls/ds3.8.2/lib/verbs/common/body.c` — 4KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `boobytrap_ring.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/cave/armor/boobytrap_ring.c` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/armor/boobytrap_ring.c` — 1KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `book.c`
- `mud-references/deadsouls/ds3.8.2/lib/lib/std/book.c` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/obj/book.c` — 426B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `bourbon.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/meals/bourbon.c` — 787B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/meals/bourbon.c` — 620B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `box.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/obj/box.c` — 651B
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/obj/box.c` — 324B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `break_string.c`
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/compat/simuls/break_string.c` — 605B
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/testsuite/single/tests/efuns/break_string.c` — 42B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `breather.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/armor/breather.c` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/armor/breather.c` — 843B
- `mud-references/deadsouls/ds3.8.2/lib/shadows/breather.c` — 1KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `brush.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/weap/brush.c` — 572B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/weap/brush.c` — 632B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `buffer.c`
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/buffer.c` — 3KB
- `mud-references/deadsouls/ds3.8.2/lib/powers/spells/buffer.c` — 4KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `bufferp`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/bufferp` — 218B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mixed/bufferp` — 218B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `bugs.c`
- `mud-references/deadsouls/ds3.8.2/lib/cmds/creators/bugs.c` — 354B
- `mud-references/deadsouls/ds3.8.2/lib/daemon/bugs.c` — 3KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `builder_chest.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/obj/builder_chest.c` — 931B
- `mud-references/deadsouls/ds3.8.2/lib/realms/template/area/obj/builder_chest.c` — 867B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `burster.lpc`
- `lib/occs/burster.lpc` — 2KB
- `lib/races/burster.lpc` — 4KB
**Recommendation:** Keep the copy in `lib/` and remove duplicates elsewhere.

### `bury.c`
- `mud-references/deadsouls/ds3.8.2/lib/lib/events/bury.c` — 267B
- `mud-references/deadsouls/ds3.8.2/lib/verbs/items/bury.c` — 2KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `buy.c`
- `mud-references/deadsouls/ds3.8.2/lib/lib/events/buy.c` — 375B
- `mud-references/deadsouls/ds3.8.2/lib/verbs/items/buy.c` — 1KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `cache.c`
- `mud-references/deadsouls/ds3.8.2/lib/cmds/admins/cache.c` — 375B
- `mud-references/deadsouls/ds3.8.2/lib/domains/Praxis/cache.c` — 194B
- `mud-references/deadsouls/ds3.8.2/lib/domains/Ylsrim/adm/cache.c` — 393B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `cache_stats`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/cache_stats` — 376B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/internals/cache_stats` — 376B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `call_other`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/call_other` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/calls/call_other` — 1KB
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `call_out`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/call_out` — 883B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/calls/call_out` — 883B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `call_out.c`
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/call_out.c` — 14KB
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/testsuite/single/tests/efuns/call_out.c` — 853B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `call_out_info`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/call_out_info` — 792B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/call_out_info` — 792B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `call_stack`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/call_stack` — 532B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/calls/call_stack` — 532B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `cap.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/armor/cap.c` — 546B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/armor/cap.c` — 546B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `capitalize`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/capitalize` — 240B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/strings/capitalize` — 240B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `carving_knife.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/weap/carving_knife.c` — 814B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/weap/carving_knife.c` — 900B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `case.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/obj/case.c` — 939B
- `mud-references/deadsouls/ds3.8.2/lib/realms/template/area/obj/case.c` — 717B
- `mud-references/deadsouls/ds3.8.2/lib/realms/thurtea/area/obj/case.c` — 717B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `cask.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/Ylsrim/obj/cask.c` — 590B
- `mud-references/deadsouls/ds3.8.2/lib/domains/cave/obj/cask.c` — 570B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `cat.lpc`
- `lib/cmds/cat.lpc` — 2KB
- `lib/cmds/creator/cat.lpc` — 1KB
**Recommendation:** Keep the copy in `lib/` and remove duplicates elsewhere.

### `catch`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/catch` — 644B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/calls/catch` — 644B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `catch_tell`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/catch_tell` — 596B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/interactive/catch_tell` — 596B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `cavetroll.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/cave/npc/cavetroll.c` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/domains/cave/room/cavetroll.c` — 1KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `cd.lpc`
- `lib/cmds/cd.lpc` — 267B
- `lib/cmds/creator/cd.lpc` — 1KB
**Recommendation:** Keep the copy in `lib/` and remove duplicates elsewhere.

### `ceil`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/ceil` — 317B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/floats/ceil` — 317B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `chainmail.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/armor/chainmail.c` — 602B
- `mud-references/deadsouls/ds3.8.2/lib/domains/cave/armor/chainmail.c` — 670B
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/armor/chainmail.c` — 648B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/armor/chainmail.c` — 643B
- `mud-references/deadsouls/ds3.8.2/lib/realms/template/area/armor/chainmail.c` — 630B
- `mud-references/deadsouls/ds3.8.2/lib/realms/thurtea/area/armor/chainmail.c` — 630B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `chair.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/obj/chair.c` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/domains/cave/obj/chair.c` — 360B
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/obj/chair.c` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/obj/chair.c` — 907B
- `mud-references/deadsouls/ds3.8.2/lib/lib/std/chair.c` — 527B
- `mud-references/deadsouls/ds3.8.2/lib/obj/chair.c` — 344B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `chamber.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/room/chamber.c` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/lib/chamber.c` — 9KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `chamber1.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/Praxis/mountains/chamber1.c` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/domains/Praxis/orc_valley/chamber1.c` — 2KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `chamber2.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/Praxis/mountains/chamber2.c` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/domains/Praxis/orc_valley/chamber2.c` — 2KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `channel.c`
- `mud-references/deadsouls/ds3.8.2/lib/cmds/admins/channel.c` — 3KB
- `mud-references/deadsouls/ds3.8.2/lib/daemon/services/channel.c` — 8KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `chapel.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/Praxis/chapel.c` — 903B
- `mud-references/deadsouls/ds3.8.2/lib/lib/chapel.c` — 3KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `chapter01`
- `mud-references/deadsouls/ds3.8.2/lib/doc/bguide/chapter01` — 4KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/guide/chapter01` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/hbook/chapter01` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/manual/chapter01` — 5KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/phints/chapter01` — 6KB
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/txt/shame/chapter01` — 12KB
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `chapter02`
- `mud-references/deadsouls/ds3.8.2/lib/doc/bguide/chapter02` — 4KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/guide/chapter02` — 5KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/hbook/chapter02` — 9KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/manual/chapter02` — 10KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/phints/chapter02` — 5KB
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/txt/shame/chapter02` — 8KB
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `chapter03`
- `mud-references/deadsouls/ds3.8.2/lib/doc/bguide/chapter03` — 12KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/guide/chapter03` — 3KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/hbook/chapter03` — 11KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/manual/chapter03` — 9KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/phints/chapter03` — 4KB
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/txt/shame/chapter03` — 64KB
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `chapter04`
- `mud-references/deadsouls/ds3.8.2/lib/doc/bguide/chapter04` — 6KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/guide/chapter04` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/hbook/chapter04` — 3KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/manual/chapter04` — 10KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/phints/chapter04` — 9KB
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/txt/shame/chapter04` — 12KB
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `chapter05`
- `mud-references/deadsouls/ds3.8.2/lib/doc/bguide/chapter05` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/guide/chapter05` — 4KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/hbook/chapter05` — 3KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/manual/chapter05` — 7KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/phints/chapter05` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/txt/shame/chapter05` — 44KB
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `chapter06`
- `mud-references/deadsouls/ds3.8.2/lib/doc/bguide/chapter06` — 3KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/guide/chapter06` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/hbook/chapter06` — 433B
- `mud-references/deadsouls/ds3.8.2/lib/doc/manual/chapter06` — 14KB
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `chapter07`
- `mud-references/deadsouls/ds3.8.2/lib/doc/bguide/chapter07` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/guide/chapter07` — 7KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/hbook/chapter07` — 3KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/manual/chapter07` — 15KB
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `chapter08`
- `mud-references/deadsouls/ds3.8.2/lib/doc/bguide/chapter08` — 3KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/guide/chapter08` — 14KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/hbook/chapter08` — 3KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/manual/chapter08` — 9KB
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `chapter09`
- `mud-references/deadsouls/ds3.8.2/lib/doc/guide/chapter09` — 3KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/hbook/chapter09` — 3KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/manual/chapter09` — 8KB
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `chapter1`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lpc/basic/chapter1` — 5KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/lpc/intermediate/chapter1` — 8KB
- `mud-references/deadsouls/ds3.8.2/lib/obj/book_source/chapter1` — 73B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `chapter2`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lpc/basic/chapter2` — 10KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/lpc/intermediate/chapter2` — 12KB
- `mud-references/deadsouls/ds3.8.2/lib/obj/book_source/chapter2` — 75B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `chapter3`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lpc/basic/chapter3` — 9KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/lpc/intermediate/chapter3` — 21KB
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `chapter4`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lpc/basic/chapter4` — 10KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/lpc/intermediate/chapter4` — 8KB
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `chapter5`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lpc/basic/chapter5` — 7KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/lpc/intermediate/chapter5` — 9KB
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `chapter6`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lpc/basic/chapter6` — 14KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/lpc/intermediate/chapter6` — 12KB
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `chapter7`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lpc/basic/chapter7` — 15KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/lpc/intermediate/chapter7` — 15KB
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `chat.c`
- `mud-references/deadsouls/ds3.8.2/lib/lib/chat.c` — 8KB
- `mud-references/deadsouls/ds3.8.2/lib/secure/daemon/chat.c` — 33KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `chat.h`
- `mud-references/deadsouls/ds3.8.2/lib/daemon/include/chat.h` — 436B
- `mud-references/deadsouls/ds3.8.2/lib/lib/include/chat.h` — 395B
- `mud-references/deadsouls/ds3.8.2/lib/secure/daemon/include/chat.h` — 429B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `chat_command`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/chat_command` — 411B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/chat/chat_command` — 411B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `checkCollapse`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/checkCollapse` — 336B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/checkCollapse` — 336B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `check_memory`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/check_memory` — 392B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/check_memory` — 392B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `chest.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/Praxis/obj/misc/chest.c` — 902B
- `mud-references/deadsouls/ds3.8.2/lib/domains/Ylsrim/etc/chest.c` — 683B
- `mud-references/deadsouls/ds3.8.2/lib/domains/cave/obj/chest.c` — 650B
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/obj/chest.c` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/obj/chest.c` — 713B
- `mud-references/deadsouls/ds3.8.2/lib/realms/template/area/obj/chest.c` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/realms/thurtea/area/obj/chest.c` — 1KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `chest2.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/cave/obj/chest2.c` — 951B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/obj/chest2.c` — 687B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `chieftain.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/cave/npc/chieftain.c` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/domains/cave/room/chieftain.c` — 1KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `children`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/children` — 379B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/objects/children` — 379B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `church.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/Ylsrim/room/church.c` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/room/church.c` — 2KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `church_button.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/Ylsrim/etc/church_button.c` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/obj/church_button.c` — 730B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `cigar.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/obj/cigar.c` — 662B
- `mud-references/deadsouls/ds3.8.2/lib/lib/cigar.c` — 970B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `classes.c`
- `mud-references/deadsouls/ds3.8.2/lib/daemon/classes.c` — 5KB
- `mud-references/deadsouls/ds3.8.2/lib/lib/classes.c` — 4KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `classes.h`
- `mud-references/deadsouls/ds3.8.2/lib/daemon/include/classes.h` — 195B
- `mud-references/deadsouls/ds3.8.2/lib/lib/include/classes.h` — 555B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `classp`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/classp` — 190B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mixed/classp` — 190B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `clean.c`
- `mud-references/deadsouls/ds3.8.2/lib/cmds/creators/clean.c` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/lib/props/clean.c` — 3KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `clear_bit`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/clear_bit` — 353B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/strings/clear_bit` — 353B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `cleric`
- `mud-references/deadsouls/ds3.8.2/lib/doc/help/classes/cleric` — 798B
- `mud-references/deadsouls/ds3.8.2/lib/secure/cfg/classes/cleric` — 283B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `clerk.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/npc/clerk.c` — 819B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/room/clerk.c` — 822B
- `mud-references/deadsouls/ds3.8.2/lib/lib/clerk.c` — 4KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `climb.c`
- `mud-references/deadsouls/ds3.8.2/lib/lib/events/climb.c` — 4KB
- `mud-references/deadsouls/ds3.8.2/lib/verbs/rooms/climb.c` — 2KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `climb.h`
- `mud-references/deadsouls/ds3.8.2/lib/include/climb.h` — 201B
- `mud-references/deadsouls/ds3.8.2/lib/verbs/rooms/include/climb.h` — 363B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `clip.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/obj/clip.c` — 649B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/obj/clip.c` — 690B
- `mud-references/deadsouls/ds3.8.2/lib/lib/clip.c` — 5KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `clone.lpc`
- `lib/cmds/clone.lpc` — 254B
- `lib/cmds/creator/clone.lpc` — 1KB
**Recommendation:** Keep the copy in `lib/` and remove duplicates elsewhere.

### `clone_object`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/clone_object` — 513B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/objects/clone_object` — 513B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `clonep`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/clonep` — 697B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/objects/clonep` — 697B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `close.c`
- `mud-references/deadsouls/ds3.8.2/lib/lib/events/close.c` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/verbs/items/close.c` — 951B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `close.h`
- `mud-references/deadsouls/ds3.8.2/lib/lib/include/close.h` — 621B
- `mud-references/deadsouls/ds3.8.2/lib/verbs/items/include/close.h` — 170B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `cold.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/Praxis/obj/misc/cold.c` — 709B
- `mud-references/deadsouls/ds3.8.2/lib/domains/Ylsrim/broken/cold.c` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/obj/cold.c` — 4KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `collar.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/armor/collar.c` — 706B
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/armor/collar.c` — 816B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/armor/collar.c` — 760B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `combat.c`
- `mud-references/deadsouls/ds3.8.2/lib/lib/combat.c` — 33KB
- `src/combat.c` — 37KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `combat.h`
- `lib/include/combat.h` — 7KB
- `src/combat.h` — 5KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `command`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/command` — 567B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/command` — 567B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `command.c`
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/testsuite/single/tests/efuns/command.c` — 588B
- `mud-references/deadsouls/ds3.8.2/lib/daemon/command.c` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/lib/command.c` — 17KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `command.h`
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/testsuite/include/command.h` — 40B
- `mud-references/deadsouls/ds3.8.2/lib/daemon/include/command.h` — 251B
- `mud-references/deadsouls/ds3.8.2/lib/lib/include/command.h` — 402B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `commands`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/commands` — 620B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/commands` — 620B
- `mud-references/deadsouls/ds3.8.2/lib/domains/Praxis/commands` — 789B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `compile_object`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/compile_object` — 1008B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/compile_object` — 1008B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `compiler.c`
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/compiler.c` — 83KB
- `src/compiler.c` — 44KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `compiler.h`
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/compiler.h` — 9KB
- `src/compiler.h` — 2KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `config.h`
- `lib/include/config.h` — 127B
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/config.h` — 3KB
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/testsuite/include/config.h` — 227B
- `mud-references/deadsouls/ds3.8.2/lib/secure/include/config.h` — 3KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `configuration`
- `mud-references/deadsouls/ds3.8.2/extra/mingw/configuration` — 97B
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/configuration` — 141B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `configure.h`
- `mud-references/deadsouls/ds3.8.2/extra/mingw/configure.h` — 491B
- `mud-references/deadsouls/ds3.8.2/extra/wolfpaw/configure.h` — 1KB
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/Win32/configure.h` — 343B
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/configure.h` — 947B
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/windows/configure.h` — 338B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `connect`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/connect` — 622B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/connect` — 622B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `connect.c`
- `mud-references/deadsouls/ds3.8.2/lib/secure/lib/connect.c` — 30KB
- `mud-references/deadsouls/ds3.8.2/lib/www/cgi/connect.c` — 2KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `consult.c`
- `mud-references/deadsouls/ds3.8.2/lib/lib/events/consult.c` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/verbs/items/consult.c` — 985B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `container.c`
- `mud-references/deadsouls/ds3.8.2/lib/lib/comp/container.c` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/obj/container.c` — 398B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `copy`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/copy` — 488B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/general/copy` — 488B
- `mud-references/deadsouls/ds3.8.2/lib/doc/sefun/copy` — 1KB
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `copy.c`
- `mud-references/deadsouls/ds3.8.2/lib/secure/sefun/copy.c` — 695B
- `mud-references/deadsouls/ds3.8.2/lib/verbs/builders/copy.c` — 4KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `cos`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/cos` — 309B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/floats/cos` — 309B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `cosmo_knight.lpc`
- `lib/occs/cosmo_knight.lpc` — 2KB
- `lib/races/cosmo_knight.lpc` — 3KB
**Recommendation:** Keep the copy in `lib/` and remove duplicates elsewhere.

### `cot.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/cave/obj/cot.c` — 450B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/obj/cot.c` — 560B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `couch.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/obj/couch.c` — 653B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/obj/couch.c` — 681B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `cp`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/cp` — 324B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/filesystem/cp` — 324B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `cp.c`
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/testsuite/single/tests/efuns/cp.c` — 253B
- `mud-references/deadsouls/ds3.8.2/lib/secure/cmds/creators/cp.c` — 4KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `crash`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/crash` — 637B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/crash` — 637B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `crawl.c`
- `mud-references/deadsouls/ds3.8.2/lib/lib/events/crawl.c` — 111B
- `mud-references/deadsouls/ds3.8.2/lib/verbs/players/crawl.c` — 2KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `crc32`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/crc32` — 243B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/buffers/crc32` — 243B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `crc32.c`
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/crc32.c` — 694B
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/testsuite/single/tests/efuns/crc32.c` — 89B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `create.c`
- `mud-references/deadsouls/ds3.8.2/lib/secure/cmds/builders/create.c` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/secure/modules/create.c` — 39KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `creator`
- `mud-references/deadsouls/ds3.8.2/lib/doc/help/creators/creator` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/news/creator` — 521B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `creator_file`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/creator_file` — 872B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/creator_file` — 872B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `crypt`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/crypt` — 311B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/strings/crypt` — 311B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `crypt.c`
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/crypt.c` — 14KB
- `mud-references/deadsouls/ds3.8.2/lib/domains/Praxis/crypt.c` — 14KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `ctime`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/ctime` — 282B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/ctime` — 282B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `cup.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/cave/obj/cup.c` — 524B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/obj/cup.c` — 968B
- `mud-references/deadsouls/ds3.8.2/lib/realms/template/area/obj/cup.c` — 524B
- `mud-references/deadsouls/ds3.8.2/lib/realms/thurtea/area/obj/cup.c` — 524B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `custom.c`
- `mud-references/deadsouls/ds3.8.2/lib/realms/template/cmds/custom.c` — 118B
- `mud-references/deadsouls/ds3.8.2/lib/realms/thurtea/cmds/custom.c` — 118B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `customdefs.h`
- `mud-references/deadsouls/ds3.8.2/lib/realms/template/area/customdefs.h` — 454B
- `mud-references/deadsouls/ds3.8.2/lib/realms/thurtea/area/customdefs.h` — 462B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `dagger.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/Praxis/obj/weapon/dagger.c` — 400B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/weap/dagger.c` — 606B
- `mud-references/deadsouls/ds3.8.2/lib/domains/cave/weap/dagger.c` — 520B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/weap/dagger.c` — 520B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `dcell.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/obj/dcell.c` — 549B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/obj/dcell.c` — 557B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `dcell_crappy.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/obj/dcell_crappy.c` — 549B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/obj/dcell_crappy.c` — 556B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `dcell_good.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/obj/dcell_good.c` — 552B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/obj/dcell_good.c` — 559B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `dcell_std.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/obj/dcell_std.c` — 551B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/obj/dcell_std.c` — 558B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `death.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/room/death.c` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/domains/cave/room/death.c` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/room/death.c` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/domains/learning/room/death.c` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/room/death.c` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/std/death.c` — 2KB
- `src/death.c` — 4KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `death.txt`
- `lib/help/basics/death.txt` — 499B
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/etc/death.txt` — 1KB
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `debug.c`
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/debug.c` — 1KB
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/packages/debug.c` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/cmds/creators/debug.c` — 685B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `debug.h`
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/debug.h` — 2KB
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/packages/debug.h` — 0B
- `mud-references/deadsouls/ds3.8.2/lib/secure/daemon/i3router/debug.h` — 1KB
- `src/debug.h` — 2KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `debug_info`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/debug_info` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/internals/debug_info` — 2KB
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `debug_message`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/debug_message` — 273B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/debug_message` — 273B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `debugmalloc`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/debugmalloc` — 619B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/internals/debugmalloc` — 619B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `deed.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/Praxis/obj/misc/deed.c` — 5KB
- `mud-references/deadsouls/ds3.8.2/lib/obj/deed.c` — 450B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `deep_inherit_list`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/deep_inherit_list` — 300B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/deep_inherit_list` — 300B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `deep_inventory`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/deep_inventory` — 429B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/objects/deep_inventory` — 429B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `deer.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/npc/deer.c` — 524B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/npc/deer.c` — 562B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `defines.c`
- `mud-references/deadsouls/ds3.8.2/lib/cmds/creators/defines.c` — 590B
- `mud-references/deadsouls/ds3.8.2/lib/daemon/defines.c` — 1KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `describe.c`
- `mud-references/deadsouls/ds3.8.2/lib/lib/events/describe.c` — 14KB
- `mud-references/deadsouls/ds3.8.2/lib/verbs/players/describe.c` — 955B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `dest.c`
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/testsuite/command/dest.c` — 578B
- `mud-references/deadsouls/ds3.8.2/lib/verbs/builders/dest.c` — 3KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `destruct`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/destruct` — 523B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/objects/destruct` — 523B
- `mud-references/deadsouls/ds3.8.2/lib/doc/sefun/destruct` — 658B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `dig.c`
- `mud-references/deadsouls/ds3.8.2/lib/lib/events/dig.c` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/verbs/items/dig.c` — 2KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `dirs.h`
- `lib/include/dirs.h` — 238B
- `mud-references/deadsouls/ds3.8.2/lib/secure/include/dirs.h` — 6KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `disable_commands`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/disable_commands` — 237B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/disable_commands` — 237B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `disable_wizard`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/disable_wizard` — 263B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/disable_wizard` — 263B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `disarm.c`
- `mud-references/deadsouls/ds3.8.2/lib/lib/events/disarm.c` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/verbs/items/disarm.c` — 654B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `domain_file`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/domain_file` — 606B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/domain_file` — 606B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `domain_stats`
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/testsuite/log/domain_stats` — 46B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/domain_stats` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mudlib/domain_stats` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/log/domain_stats` — 97B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `domains.c`
- `mud-references/deadsouls/ds3.8.2/lib/cmds/creators/domains.c` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/daemon/domains.c` — 434B
- `mud-references/deadsouls/ds3.8.2/lib/secure/sefun/domains.c` — 2KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `donate.c`
- `mud-references/deadsouls/ds3.8.2/lib/lib/donate.c` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/verbs/items/donate.c` — 1KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `door.c`
- `mud-references/deadsouls/ds3.8.2/lib/lib/door.c` — 13KB
- `mud-references/deadsouls/ds3.8.2/lib/obj/door.c` — 719B
- `mud-references/deadsouls/ds3.8.2/lib/secure/modules/door.c` — 10KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `downloads.html`
- `mud-references/deadsouls/ds3.8.2/lib/www/downloads.html` — 25KB
- `mud-references/deadsouls/ds3.8.2/lib/www/lpmuds/downloads.html` — 25KB
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `drink.c`
- `mud-references/deadsouls/ds3.8.2/lib/lib/events/drink.c` — 611B
- `mud-references/deadsouls/ds3.8.2/lib/obj/drink.c` — 481B
- `mud-references/deadsouls/ds3.8.2/lib/verbs/items/drink.c` — 2KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `driver`
- `build/driver` — 1MB
- `mud-references/deadsouls/ds3.8.2/bin/driver` — 728KB
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/driver` — 728KB
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `drone.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/npc/drone.c` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/secure/npc/drone.c` — 5KB
- `mud-references/deadsouls/ds3.8.2/lib/shadows/drone.c` — 126B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `drop.c`
- `mud-references/deadsouls/ds3.8.2/lib/lib/events/drop.c` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/verbs/items/drop.c` — 3KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `drop.h`
- `mud-references/deadsouls/ds3.8.2/lib/lib/include/drop.h` — 319B
- `mud-references/deadsouls/ds3.8.2/lib/verbs/items/include/drop.h` — 274B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `dummy.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/npc/dummy.c` — 3KB
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/npc/dummy.c` — 3KB
- `mud-references/deadsouls/ds3.8.2/lib/lib/std/dummy.c` — 496B
- `mud-references/deadsouls/ds3.8.2/lib/secure/sefun/dummy.c` — 105B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `dump_file_descriptors`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/dump_file_descriptors` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/internals/dump_file_descriptors` — 1KB
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `dump_prog`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/dump_prog` — 618B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/internals/dump_prog` — 618B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `dump_socket_status`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/dump_socket_status` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/internals/dump_socket_status` — 2KB
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `dumpallobj`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/dumpallobj` — 485B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/internals/dumpallobj` — 485B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `dumpallobj.c`
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/testsuite/single/tests/efuns/dumpallobj.c` — 68B
- `mud-references/deadsouls/ds3.8.2/lib/cmds/admins/dumpallobj.c` — 386B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `economy.c`
- `mud-references/deadsouls/ds3.8.2/lib/secure/cmds/creators/economy.c` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/secure/daemon/economy.c` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/secure/sefun/economy.c` — 2KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `ed`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/ed` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/ed` — 1KB
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `ed.c`
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/ed.c` — 89KB
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/testsuite/command/ed.c` — 181B
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/testsuite/single/tests/efuns/ed.c` — 345B
- `mud-references/deadsouls/ds3.8.2/lib/secure/cmds/creators/ed.c` — 2KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `ed_cmd`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/ed_cmd` — 279B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/ed_cmd` — 279B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `ed_start`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/ed_start` — 581B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/ed_start` — 581B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `elevator.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/chamber/elevator.c` — 375B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/room/elevator.c` — 4KB
- `mud-references/deadsouls/ds3.8.2/lib/lib/elevator.c` — 2KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `emote.c`
- `lib/cmds/players/emote.c` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/cmds/players/emote.c` — 1KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `enable_commands`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/enable_commands` — 531B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/enable_commands` — 531B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `enable_wizard`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/enable_wizard` — 934B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/enable_wizard` — 934B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `enter`
- `mud-references/deadsouls/ds3.8.2/lib/log/enter` — 563B
- `mud-references/deadsouls/ds3.8.2/lib/secure/log/enter` — 398B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `enter.c`
- `mud-references/deadsouls/ds3.8.2/lib/lib/enter.c` — 4KB
- `mud-references/deadsouls/ds3.8.2/lib/verbs/rooms/enter.c` — 1KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `entrance.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/Praxis/mountains/entrance.c` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/domains/examples/room/entrance.c` — 5KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `environment`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/environment` — 388B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/objects/environment` — 388B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `epilog`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/epilog` — 619B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/epilog` — 619B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `error`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/error` — 332B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/error` — 332B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `error.c`
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/testsuite/single/tests/efuns/error.c` — 108B
- `mud-references/deadsouls/ds3.8.2/lib/daemon/services/error.c` — 1KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `error_handler`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/error_handler` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/error_handler` — 1KB
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `eval.c`
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/eval.c` — 698B
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/testsuite/command/eval.c` — 338B
- `mud-references/deadsouls/ds3.8.2/lib/secure/cmds/creators/eval.c` — 3KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `eval.lpc`
- `lib/cmds/creator/eval.lpc` — 2KB
- `lib/cmds/eval.lpc` — 262B
**Recommendation:** Keep the copy in `lib/` and remove duplicates elsewhere.

### `eval_cost`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/eval_cost` — 305B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/eval_cost` — 305B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `evaldefs.h`
- `mud-references/deadsouls/ds3.8.2/lib/realms/template/evaldefs.h` — 315B
- `mud-references/deadsouls/ds3.8.2/lib/realms/thurtea/evaldefs.h` — 315B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `evaluate`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/evaluate` — 275B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/functions/evaluate` — 275B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `eventBring`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventBring` — 390B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/clan/eventBring` — 390B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `eventBurnOut`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventBurnOut` — 267B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/burn/eventBurnOut` — 267B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `eventBuy`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventBuy` — 661B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/eventBuy` — 661B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/vendor/eventBuy` — 661B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `eventCharge`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventCharge` — 278B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/battery/eventCharge` — 278B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `eventCheckHealing`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventCheckHealing` — 449B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/eventCheckHealing` — 449B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `eventCheckProtection`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventCheckProtection` — 505B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/eventCheckProtection` — 505B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `eventCollapse`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventCollapse` — 267B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/eventCollapse` — 267B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `eventCompareLimbs`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventCompareLimbs` — 333B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/eventCompareLimbs` — 333B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `eventCompleteHeal`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventCompleteHeal` — 463B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/eventCompleteHeal` — 463B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `eventDestruct`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventDestruct` — 879B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/bonus/eventDestruct` — 879B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/chat/eventDestruct` — 879B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/clean/eventDestruct` — 879B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/client/eventDestruct` — 879B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/connect/eventDestruct` — 879B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/daemon/eventDestruct` — 879B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/file/eventDestruct` — 879B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/ftp_client/eventDestruct` — 879B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/ftp_data_connection/eventDestruct` — 879B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/interactive/eventDestruct` — 879B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/meal/eventDestruct` — 879B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/npc/eventDestruct` — 879B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/server/eventDestruct` — 879B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `eventDie`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventDie` — 714B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/eventDie` — 714B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/bot/eventDie` — 714B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/combat/eventDie` — 714B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/flashlight/eventDie` — 714B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/npc/eventDie` — 714B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/player/eventDie` — 714B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/race/eventDie` — 714B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `eventDrain`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventDrain` — 281B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/battery/eventDrain` — 281B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `eventExtinguish`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventExtinguish` — 325B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/burn/eventExtinguish` — 325B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/flashlight/eventExtinguish` — 325B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `eventFall`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventFall` — 324B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/eventFall` — 324B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/position/eventFall` — 324B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `eventHealDamage`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventHealDamage` — 761B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/eventHealDamage` — 761B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `eventInitiate`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventInitiate` — 504B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/clan/eventInitiate` — 504B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `eventJoin`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventJoin` — 467B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/clan/eventJoin` — 467B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/leader/eventJoin` — 467B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `eventLight`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventLight` — 425B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/burn/eventLight` — 425B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/flashlight/eventLight` — 425B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/lamp/eventLight` — 425B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/light/eventLight` — 425B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `eventLoad`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventLoad` — 543B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/clip/eventLoad` — 543B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/firearm/eventLoad` — 543B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/load/eventLoad` — 543B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/round/eventLoad` — 543B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `eventMarry`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventMarry` — 301B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/chapel/eventMarry` — 301B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/interactive/eventMarry` — 301B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `eventMoralAct`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventMoralAct` — 370B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/classes/eventMoralAct` — 370B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `eventReceiveDamage`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventReceiveDamage` — 476B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/armor/eventReceiveDamage` — 476B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/eventReceiveDamage` — 476B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/combat/eventReceiveDamage` — 476B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/deterioration/eventReceiveDamage` — 476B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/worn_storage/eventReceiveDamage` — 476B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `eventReceiveThrow`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventReceiveThrow` — 323B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/eventReceiveThrow` — 323B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `eventReconnect`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventReconnect` — 370B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/eventReconnect` — 370B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/chat/eventReconnect` — 370B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/creator/eventReconnect` — 370B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/interactive/eventReconnect` — 370B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/npc/eventReconnect` — 370B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/player/eventReconnect` — 370B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `eventRemoveItem`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventRemoveItem` — 347B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/eventRemoveItem` — 347B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `eventRetire`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventRetire` — 470B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/clan/eventRetire` — 470B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `eventSacrifice`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventSacrifice` — 388B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/chapel/eventSacrifice` — 388B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `eventUnjoin`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventUnjoin` — 450B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/clan/eventUnjoin` — 450B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `eventUnload`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventUnload` — 549B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/clip/eventUnload` — 549B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/firearm/eventUnload` — 549B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/load/eventUnload` — 549B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/round/eventUnload` — 549B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `eventUse`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventUse` — 426B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/battery/eventUse` — 426B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/flashlight/eventUse` — 426B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/player/eventUse` — 426B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `eventWear`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventWear` — 446B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/eventWear` — 446B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `eventWelcome`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventWelcome` — 363B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/clan/eventWelcome` — 363B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `events.c`
- `mud-references/deadsouls/ds3.8.2/lib/cmds/creators/events.c` — 3KB
- `mud-references/deadsouls/ds3.8.2/lib/secure/daemon/events.c` — 6KB
- `mud-references/deadsouls/ds3.8.2/lib/secure/sefun/events.c` — 730B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `events.h`
- `mud-references/deadsouls/ds3.8.2/lib/secure/daemon/events.h` — 418B
- `mud-references/deadsouls/ds3.8.2/lib/secure/include/events.h` — 3KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `exec`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/exec` — 833B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/exec` — 833B
- `mud-references/deadsouls/ds3.8.2/lib/doc/sefun/exec` — 522B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `exits.c`
- `mud-references/deadsouls/ds3.8.2/lib/cmds/creators/exits.c` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/lib/exits.c` — 10KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `exp`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/exp` — 240B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/floats/exp` — 240B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `explode`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/explode` — 442B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/strings/explode` — 442B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `explorer`
- `mud-references/deadsouls/ds3.8.2/lib/doc/help/classes/explorer` — 429B
- `mud-references/deadsouls/ds3.8.2/lib/secure/cfg/classes/explorer` — 259B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `explosive_trap.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/obj/explosive_trap.c` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/shadows/explosive_trap.c` — 929B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `export_uid`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/export_uid` — 376B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mudlib/export_uid` — 376B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `external_start`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/external_start` — 565B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/external_start` — 566B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `favicon.ico`
- `mud-references/deadsouls/ds3.8.2/lib/www/articles/favicon.ico` — 6KB
- `mud-references/deadsouls/ds3.8.2/lib/www/favicon.ico` — 6KB
- `mud-references/deadsouls/ds3.8.2/lib/www/lpmuds/favicon.ico` — 6KB
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `fblue`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charles/bak2/bak1/fblue` — 2B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charles/bak2/fblue` — 2B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charles/fblue` — 4B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charly/bak/fblue` — 5B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charly/fblue` — 5B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `fetch_variable`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/fetch_variable` — 424B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/general/fetch_variable` — 424B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `fgreen`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charles/bak2/bak1/fgreen` — 2B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charles/bak2/fgreen` — 3B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charles/fgreen` — 4B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charly/bak/fgreen` — 5B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charly/fgreen` — 5B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `fighter`
- `mud-references/deadsouls/ds3.8.2/lib/doc/help/classes/fighter` — 288B
- `mud-references/deadsouls/ds3.8.2/lib/news/fighter` — 43B
- `mud-references/deadsouls/ds3.8.2/lib/secure/cfg/classes/fighter` — 255B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `fighter.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/Ylsrim/room/fighter.c` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/npc/fighter.c` — 850B
- `mud-references/deadsouls/ds3.8.2/lib/realms/template/area/npc/fighter.c` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/realms/thurtea/area/npc/fighter.c` — 1KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `fighter_hall.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/Praxis/fighter_hall.c` — 9KB
- `mud-references/deadsouls/ds3.8.2/lib/domains/Ylsrim/room/fighter_hall.c` — 2KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `file.c`
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/file.c` — 29KB
- `mud-references/deadsouls/ds3.8.2/lib/cmds/creators/file.c` — 714B
- `mud-references/deadsouls/ds3.8.2/lib/secure/daemon/file.c` — 5KB
- `mud-references/deadsouls/ds3.8.2/lib/secure/lib/file.c` — 6KB
- `mud-references/deadsouls/ds3.8.2/lib/secure/modules/file.c` — 19KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `file_length`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/file_length` — 440B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/filesystem/file_length` — 440B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `file_name`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/file_name` — 650B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/objects/file_name` — 650B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `file_size`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/file_size` — 290B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/filesystem/file_size` — 290B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `files.c`
- `mud-references/deadsouls/ds3.8.2/lib/lib/files.c` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/secure/cmds/admins/files.c` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/secure/sefun/files.c` — 3KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `files.h`
- `mud-references/deadsouls/ds3.8.2/lib/lib/include/files.h` — 155B
- `mud-references/deadsouls/ds3.8.2/lib/secure/include/files.h` — 29B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `filter`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/filter` — 726B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/general/filter` — 726B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `filter.c`
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/testsuite/single/tests/efuns/filter.c` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/secure/daemon/filter.c` — 9KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `filter_array`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/filter_array` — 328B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/arrays/filter_array` — 328B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `filter_mapping`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/filter_mapping` — 341B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mappings/filter_mapping` — 341B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `find_call_out`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/find_call_out` — 425B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/find_call_out` — 425B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `find_living`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/find_living` — 614B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mudlib/find_living` — 614B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `find_object`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/find_object` — 364B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/objects/find_object` — 364B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `find_player`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/find_player` — 304B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/find_player` — 304B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `finger.c`
- `mud-references/deadsouls/ds3.8.2/lib/daemon/services/finger.c` — 3KB
- `mud-references/deadsouls/ds3.8.2/lib/secure/cmds/players/finger.c` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/secure/daemon/finger.c` — 7KB
- `mud-references/deadsouls/ds3.8.2/lib/www/cgi/finger.c` — 1017B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `first_inventory`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/first_inventory` — 424B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/objects/first_inventory` — 424B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `fish.c`
- `mud-references/deadsouls/ds3.8.2/lib/lib/fish.c` — 538B
- `mud-references/deadsouls/ds3.8.2/lib/verbs/rooms/fish.c` — 1KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `fish.h`
- `mud-references/deadsouls/ds3.8.2/lib/lib/include/fish.h` — 228B
- `mud-references/deadsouls/ds3.8.2/lib/verbs/rooms/include/fish.h` — 144B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `flag`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/flag` — 380B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/flag` — 380B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `flashlight.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/obj/flashlight.c` — 413B
- `mud-references/deadsouls/ds3.8.2/lib/lib/flashlight.c` — 5KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `flask.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/obj/flask.c` — 545B
- `mud-references/deadsouls/ds3.8.2/lib/lib/flask.c` — 6KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `floatp`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/floatp` — 219B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mixed/floatp` — 219B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `floor`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/floor` — 250B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/floats/floor` — 250B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `flu.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/Ylsrim/broken/flu.c` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/obj/flu.c` — 5KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `flush_messages`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/flush_messages` — 406B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/flush_messages` — 406B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `fly.c`
- `mud-references/deadsouls/ds3.8.2/lib/lib/events/fly.c` — 107B
- `mud-references/deadsouls/ds3.8.2/lib/verbs/rooms/fly.c` — 3KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `follow.c`
- `mud-references/deadsouls/ds3.8.2/lib/lib/follow.c` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/verbs/players/follow.c` — 3KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `follow.h`
- `mud-references/deadsouls/ds3.8.2/lib/lib/include/follow.h` — 254B
- `mud-references/deadsouls/ds3.8.2/lib/verbs/players/include/follow.h` — 183B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `foo.txt`
- `mud-references/deadsouls/ds3.8.2/lib/daemon/tmp/foo.txt` — 36B
- `mud-references/deadsouls/ds3.8.2/lib/estates/foo.txt` — 36B
- `mud-references/deadsouls/ds3.8.2/lib/ftp/foo.txt` — 36B
- `mud-references/deadsouls/ds3.8.2/lib/log/adm/foo.txt` — 36B
- `mud-references/deadsouls/ds3.8.2/lib/log/archive/foo.txt` — 36B
- `mud-references/deadsouls/ds3.8.2/lib/log/chan/foo.txt` — 36B
- `mud-references/deadsouls/ds3.8.2/lib/log/errors/foo.txt` — 36B
- `mud-references/deadsouls/ds3.8.2/lib/log/law/adm/foo.txt` — 36B
- `mud-references/deadsouls/ds3.8.2/lib/log/law/email/foo.txt` — 36B
- `mud-references/deadsouls/ds3.8.2/lib/log/law/names/foo.txt` — 36B
- `mud-references/deadsouls/ds3.8.2/lib/log/law/sites-misc/foo.txt` — 36B
- `mud-references/deadsouls/ds3.8.2/lib/log/law/sites-register/foo.txt` — 36B
- `mud-references/deadsouls/ds3.8.2/lib/log/law/sites-tempban/foo.txt` — 36B
- `mud-references/deadsouls/ds3.8.2/lib/log/law/sites-watch/foo.txt` — 36B
- `mud-references/deadsouls/ds3.8.2/lib/log/open/foo.txt` — 36B
- `mud-references/deadsouls/ds3.8.2/lib/log/reports/foo.txt` — 36B
- `mud-references/deadsouls/ds3.8.2/lib/log/router/foo.txt` — 36B
- `mud-references/deadsouls/ds3.8.2/lib/log/secure/foo.txt` — 36B
- `mud-references/deadsouls/ds3.8.2/lib/log/watch/foo.txt` — 36B
- `mud-references/deadsouls/ds3.8.2/lib/secure/log/adm/foo.txt` — 36B
- `mud-references/deadsouls/ds3.8.2/lib/secure/log/bak/foo.txt` — 36B
- `mud-references/deadsouls/ds3.8.2/lib/secure/log/intermud/foo.txt` — 36B
- `mud-references/deadsouls/ds3.8.2/lib/secure/log/network/foo.txt` — 36B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `food_storage1.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/cave/doors/food_storage1.c` — 703B
- `mud-references/deadsouls/ds3.8.2/lib/domains/cave/room/food_storage1.c` — 2KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `foodsmock.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/armor/foodsmock.c` — 494B
- `mud-references/deadsouls/ds3.8.2/lib/domains/cave/armor/foodsmock.c` — 494B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `fountain.lpc`
- `lib/domains/new_camelot/garden/fountain.lpc` — 815B
- `lib/domains/new_camelot/garden/obj/fountain.lpc` — 277B
**Recommendation:** Keep the copy in `lib/` and remove duplicates elsewhere.

### `fred`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charles/bak2/bak1/fred` — 2B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charles/bak2/fred` — 2B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charles/fred` — 4B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charly/bak/fred` — 5B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charly/fred` — 5B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `freezer.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/Praxis/freezer.c` — 921B
- `mud-references/deadsouls/ds3.8.2/lib/domains/Ylsrim/adm/freezer.c` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/room/freezer.c` — 707B
- `mud-references/deadsouls/ds3.8.2/lib/domains/cave/room/freezer.c` — 707B
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/room/freezer.c` — 707B
- `mud-references/deadsouls/ds3.8.2/lib/domains/learning/room/freezer.c` — 707B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/room/freezer.c` — 707B
- `mud-references/deadsouls/ds3.8.2/lib/std/freezer.c` — 707B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `function`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lpc/constructs/function` — 755B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lpc/types/function` — 684B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `function.c`
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/function.c` — 10KB
- `mud-references/deadsouls/ds3.8.2/lib/secure/daemon/function.c` — 6KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `function.h`
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/function.h` — 1KB
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/include/function.h` — 446B
- `mud-references/deadsouls/ds3.8.2/lib/secure/include/function.h` — 511B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `function_exists`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/function_exists` — 738B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/function_exists` — 738B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `function_owner`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/function_owner` — 266B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/functions/function_owner` — 266B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `function_profile`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/function_profile` — 847B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/function_profile` — 847B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `functionp`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/functionp` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mixed/functionp` — 1KB
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `functions`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/functions` — 892B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/functions` — 892B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `furnace.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/Ylsrim/room/furnace.c` — 110B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/room/furnace.c` — 110B
- `mud-references/deadsouls/ds3.8.2/lib/domains/cave/room/furnace.c` — 110B
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/room/furnace.c` — 110B
- `mud-references/deadsouls/ds3.8.2/lib/domains/learning/room/furnace.c` — 110B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/room/furnace.c` — 110B
- `mud-references/deadsouls/ds3.8.2/lib/lib/std/furnace.c` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/std/furnace.c` — 110B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `gate.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/doors/gate.c` — 847B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/room/gate.c` — 3KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `gecko.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/npc/gecko.c` — 488B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/npc/gecko.c` — 495B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `general`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lpc/types/general` — 5KB
- `mud-references/deadsouls/ds3.8.2/lib/news/general` — 235B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `generate_source`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/generate_source` — 755B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/compile/generate_source` — 755B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `generic.c`
- `mud-references/deadsouls/ds3.8.2/lib/secure/lib/net/generic.c` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/secure/modules/generic.c` — 10KB
- `mud-references/deadsouls/ds3.8.2/lib/secure/sefun/generic.c` — 136B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `get.c`
- `mud-references/deadsouls/ds3.8.2/lib/lib/events/get.c` — 3KB
- `mud-references/deadsouls/ds3.8.2/lib/verbs/items/get.c` — 6KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `get.h`
- `mud-references/deadsouls/ds3.8.2/lib/lib/include/get.h` — 485B
- `mud-references/deadsouls/ds3.8.2/lib/verbs/items/include/get.h` — 769B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `get_bb_uid`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/get_bb_uid` — 393B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/get_bb_uid` — 393B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `get_char`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/get_char` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/get_char` — 1KB
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `get_config`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/get_config` — 309B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/internals/get_config` — 309B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `get_dir`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/get_dir` — 930B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/filesystem/get_dir` — 930B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `get_root_uid`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/get_root_uid` — 350B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/get_root_uid` — 350B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `get_save_file_name`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/get_save_file_name` — 411B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/get_save_file_name` — 411B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `geteuid`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/geteuid` — 625B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mudlib/geteuid` — 625B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `getuid`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/getuid` — 416B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mudlib/getuid` — 416B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `give.c`
- `mud-references/deadsouls/ds3.8.2/lib/lib/events/give.c` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/verbs/items/give.c` — 5KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `globals.h`
- `lib/include/globals.h` — 3KB
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/testsuite/include/globals.h` — 702B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `glove.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/armor/glove.c` — 765B
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/armor/glove.c` — 683B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/armor/glove.c` — 715B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `glove_l.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/armor/glove_l.c` — 746B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/armor/glove_l.c` — 720B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `glove_r.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/armor/glove_r.c` — 749B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/armor/glove_r.c` — 723B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `goblin.lpc`
- `lib/languages/goblin.lpc` — 695B
- `lib/races/goblin.lpc` — 5KB
**Recommendation:** Keep the copy in `lib/` and remove duplicates elsewhere.

### `goto.lpc`
- `lib/cmds/admin/goto.lpc` — 685B
- `lib/cmds/goto.lpc` — 249B
**Recommendation:** Keep the copy in `lib/` and remove duplicates elsewhere.

### `grate.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/doors/grate.c` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/doors/grate.c` — 966B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `green_wins`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charles/bak2/bak1/green_wins` — 3B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charles/bak2/green_wins` — 3B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charles/green_wins` — 5B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charly/bak/green_wins` — 5B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charly/green_wins` — 5B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `grenade.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/weap/grenade.c` — 72B
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/weap/grenade.c` — 5KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `guard.c`
- `mud-references/deadsouls/ds3.8.2/lib/daemon/guard.c` — 4KB
- `mud-references/deadsouls/ds3.8.2/lib/domains/Praxis/obj/mon/guard.c` — 481B
- `mud-references/deadsouls/ds3.8.2/lib/domains/Praxis/orc_valley/guard.c` — 3KB
- `mud-references/deadsouls/ds3.8.2/lib/lib/guard.c` — 4KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `ham_sand.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/meals/ham_sand.c` — 612B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/meals/ham_sand.c` — 487B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `heart_beat_info`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/heart_beat_info` — 316B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/objects/heart_beat_info` — 316B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `heart_beats`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/heart_beats` — 344B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/objects/heart_beats` — 344B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `helm.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/Praxis/obj/armour/helm.c` — 857B
- `mud-references/deadsouls/ds3.8.2/lib/domains/Ylsrim/armor/helm.c` — 1KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `helmet.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/armor/helmet.c` — 710B
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/armor/helmet.c` — 533B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/armor/helmet.c` — 538B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `help.c`
- `mud-references/deadsouls/ds3.8.2/lib/cmds/common/help.c` — 6KB
- `mud-references/deadsouls/ds3.8.2/lib/daemon/help.c` — 20KB
- `mud-references/deadsouls/ds3.8.2/lib/lib/help.c` — 575B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `help.h`
- `mud-references/deadsouls/ds3.8.2/lib/lib/include/help.h` — 144B
- `mud-references/deadsouls/ds3.8.2/lib/verbs/common/include/help.h` — 422B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `herring.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/cave/meals/herring.c` — 552B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/meals/herring.c` — 512B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `history.c`
- `mud-references/deadsouls/ds3.8.2/lib/lib/history.c` — 6KB
- `mud-references/deadsouls/ds3.8.2/lib/secure/cmds/players/history.c` — 3KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `hole.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/Praxis/hole.c` — 909B
- `mud-references/deadsouls/ds3.8.2/lib/domains/Ylsrim/etc/hole.c` — 647B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `horse.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/npc/horse.c` — 642B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/npc/horse.c` — 758B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `imc2.c`
- `mud-references/deadsouls/ds3.8.2/lib/secure/cmds/creators/imc2.c` — 219B
- `mud-references/deadsouls/ds3.8.2/lib/secure/daemon/imc2.c` — 60KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `implode`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/implode` — 712B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/strings/implode` — 712B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `in_edit`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/in_edit` — 326B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/in_edit` — 326B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `in_input`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/in_input` — 339B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/in_input` — 339B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `index`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/index` — 565B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/arrays/index` — 261B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/buffers/index` — 233B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/calls/index` — 344B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/compile/index` — 171B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/filesystem/index` — 324B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/floats/index` — 266B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/functions/index` — 179B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/general/index` — 298B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/index` — 1022B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/internals/index` — 525B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mappings/index` — 245B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mudlib/index` — 401B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/numbers/index` — 171B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/objects/index` — 750B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/parsing/index` — 150B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/sockets/index` — 412B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/strings/index` — 391B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/index` — 565B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `index.html`
- `mud-references/deadsouls/ds3.8.2/lib/www/cgi/index.html` — 22B
- `mud-references/deadsouls/ds3.8.2/lib/www/index.html` — 476B
- `mud-references/deadsouls/ds3.8.2/lib/www/lpmuds/index.html` — 7KB
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `inherit_list`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/inherit_list` — 406B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/inherit_list` — 406B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `inherits`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/inherits` — 355B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/inherits` — 355B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `inherits.c`
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/testsuite/single/tests/efuns/inherits.c` — 477B
- `mud-references/deadsouls/ds3.8.2/lib/cmds/creators/inherits.c` — 1KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `input_to`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/input_to` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/input_to` — 1KB
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `install.c`
- `mud-references/deadsouls/ds3.8.2/lib/lib/events/install.c` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/verbs/items/install.c` — 851B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `insttest`
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/insttest` — 9B
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/tmp/insttest` — 9B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `interactive`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/interactive` — 323B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/interactive` — 323B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `interactive.c`
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/testsuite/single/tests/efuns/interactive.c` — 197B
- `mud-references/deadsouls/ds3.8.2/lib/lib/interactive.c` — 18KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `interface.c`
- `mud-references/deadsouls/ds3.8.2/lib/lib/interface.c` — 14KB
- `mud-references/deadsouls/ds3.8.2/lib/secure/sefun/interface.c` — 1KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `intp`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/intp` — 221B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mixed/intp` — 221B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `inventory.c`
- `mud-references/deadsouls/ds3.8.2/lib/cmds/players/inventory.c` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/lib/props/inventory.c` — 4KB
- `mud-references/deadsouls/ds3.8.2/lib/secure/sefun/inventory.c` — 513B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `invis.c`
- `mud-references/deadsouls/ds3.8.2/lib/cmds/creators/invis.c` — 541B
- `mud-references/deadsouls/ds3.8.2/lib/domains/Praxis/obj/magic/invis.c` — 1KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `item.c`
- `mud-references/deadsouls/ds3.8.2/lib/lib/std/item.c` — 9KB
- `src/item.c` — 33KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `item.h`
- `mud-references/deadsouls/ds3.8.2/lib/lib/include/item.h` — 1KB
- `src/item.h` — 4KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `javelin.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/cave/weap/javelin.c` — 616B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/weap/javelin.c` — 647B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `jeans.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/armor/jeans.c` — 571B
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/armor/jeans.c` — 569B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/armor/jeans.c` — 502B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `jump.c`
- `mud-references/deadsouls/ds3.8.2/lib/lib/events/jump.c` — 3KB
- `mud-references/deadsouls/ds3.8.2/lib/verbs/rooms/jump.c` — 3KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `jump.h`
- `mud-references/deadsouls/ds3.8.2/lib/include/jump.h` — 213B
- `mud-references/deadsouls/ds3.8.2/lib/lib/include/jump.h` — 528B
- `mud-references/deadsouls/ds3.8.2/lib/verbs/rooms/include/jump.h` — 734B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `key.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/Ylsrim/etc/key.c` — 474B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/obj/key.c` — 508B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/obj/key.c` — 391B
- `mud-references/deadsouls/ds3.8.2/lib/realms/template/area/obj/key.c` — 375B
- `mud-references/deadsouls/ds3.8.2/lib/realms/thurtea/area/obj/key.c` — 375B
- `mud-references/deadsouls/ds3.8.2/lib/secure/obj/key.c` — 396B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `keys`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/keys` — 554B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mappings/keys` — 554B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `kleiner.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/npc/kleiner.c` — 6KB
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/room/kleiner.c` — 500B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `knife.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/weap/knife.c` — 484B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/weap/knife.c` — 465B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `knock.c`
- `mud-references/deadsouls/ds3.8.2/lib/lib/events/knock.c` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/verbs/items/knock.c` — 1KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `kurogane.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/cave/doors/kurogane.c` — 717B
- `mud-references/deadsouls/ds3.8.2/lib/domains/cave/npc/kurogane.c` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/domains/cave/room/kurogane.c` — 1KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `lamp.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/obj/lamp.c` — 377B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/obj/lamp.c` — 377B
- `mud-references/deadsouls/ds3.8.2/lib/lib/lamp.c` — 1KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `language.lpc`
- `lib/cmds/language.lpc` — 2KB
- `lib/std/language.lpc` — 5KB
**Recommendation:** Keep the copy in `lib/` and remove duplicates elsewhere.

### `languages.lpc`
- `lib/cmds/languages.lpc` — 2KB
- `lib/daemon/languages.lpc` — 5KB
**Recommendation:** Keep the copy in `lib/` and remove duplicates elsewhere.

### `lars.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/Praxis/obj/mon/lars.c` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/domains/Ylsrim/npc/lars.c` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/npc/lars.c` — 2KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `lead.c`
- `mud-references/deadsouls/ds3.8.2/lib/lib/lead.c` — 4KB
- `mud-references/deadsouls/ds3.8.2/lib/verbs/players/lead.c` — 1020B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `lead.h`
- `mud-references/deadsouls/ds3.8.2/lib/lib/include/lead.h` — 489B
- `mud-references/deadsouls/ds3.8.2/lib/verbs/players/include/lead.h` — 134B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `learn.c`
- `mud-references/deadsouls/ds3.8.2/lib/lib/learn.c` — 326B
- `mud-references/deadsouls/ds3.8.2/lib/verbs/players/learn.c` — 1KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `leather_armor.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/Ylsrim/armor/leather_armor.c` — 869B
- `mud-references/deadsouls/ds3.8.2/lib/domains/cave/armor/leather_armor.c` — 869B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/armor/leather_armor.c` — 844B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `leather_boot_l.c`
- `mud-references/deadsouls/ds3.8.2/lib/realms/template/area/armor/leather_boot_l.c` — 676B
- `mud-references/deadsouls/ds3.8.2/lib/realms/thurtea/area/armor/leather_boot_l.c` — 676B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `leather_boot_r.c`
- `mud-references/deadsouls/ds3.8.2/lib/realms/template/area/armor/leather_boot_r.c` — 679B
- `mud-references/deadsouls/ds3.8.2/lib/realms/thurtea/area/armor/leather_boot_r.c` — 679B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `lever.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/obj/lever.c` — 436B
- `mud-references/deadsouls/ds3.8.2/lib/domains/cave/obj/lever.c` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/obj/lever.c` — 436B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `levitation.lpc`
- `lib/psionics/physical/levitation.lpc` — 3KB
- `lib/spells/level2/levitation.lpc` — 2KB
**Recommendation:** Keep the copy in `lib/` and remove duplicates elsewhere.

### `lex.c`
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/lex.c` — 108KB
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/npc/quarantine/lex.c` — 355B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `lie.c`
- `mud-references/deadsouls/ds3.8.2/lib/lib/events/lie.c` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/verbs/players/lie.c` — 1KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `light.c`
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/testsuite/single/tests/efuns/light.c` — 145B
- `mud-references/deadsouls/ds3.8.2/lib/lib/light.c` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/obj/light.c` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/powers/spells/light.c` — 999B
- `mud-references/deadsouls/ds3.8.2/lib/secure/sefun/light.c` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/verbs/items/light.c` — 3KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `light.h`
- `mud-references/deadsouls/ds3.8.2/lib/lib/include/light.h` — 297B
- `mud-references/deadsouls/ds3.8.2/lib/verbs/items/include/light.h` — 326B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `link`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/link` — 495B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/filesystem/link` — 495B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `listen.c`
- `mud-references/deadsouls/ds3.8.2/lib/lib/events/listen.c` — 3KB
- `mud-references/deadsouls/ds3.8.2/lib/verbs/items/listen.c` — 2KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `living`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/living` — 349B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mudlib/living` — 349B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `living.c`
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/testsuite/single/tests/efuns/living.c` — 144B
- `mud-references/deadsouls/ds3.8.2/lib/lib/living.c` — 28KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `livings`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/livings` — 369B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mudlib/livings` — 369B
- `mud-references/deadsouls/ds3.8.2/lib/doc/sefun/livings` — 489B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `load.c`
- `mud-references/deadsouls/ds3.8.2/lib/lib/events/load.c` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/verbs/items/load.c` — 984B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `load_object`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/load_object` — 510B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/objects/load_object` — 510B
- `mud-references/deadsouls/ds3.8.2/lib/doc/sefun/load_object` — 543B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `localtime`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/localtime` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/localtime` — 1KB
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `localtime.h`
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/include/localtime.h` — 331B
- `mud-references/deadsouls/ds3.8.2/lib/secure/include/localtime.h` — 304B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `lock.c`
- `mud-references/deadsouls/ds3.8.2/lib/lib/events/lock.c` — 7KB
- `mud-references/deadsouls/ds3.8.2/lib/verbs/items/lock.c` — 2KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `lock.h`
- `mud-references/deadsouls/ds3.8.2/lib/lib/include/lock.h` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/verbs/items/include/lock.h` — 199B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `locker.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/obj/locker.c` — 1018B
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/obj/locker.c` — 716B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `lockpick.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/obj/lockpick.c` — 364B
- `mud-references/deadsouls/ds3.8.2/lib/lib/std/lockpick.c` — 991B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `log`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/log` — 236B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/floats/log` — 236B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `log.c`
- `mud-references/deadsouls/ds3.8.2/lib/secure/cmds/creators/log.c` — 603B
- `mud-references/deadsouls/ds3.8.2/lib/secure/daemon/log.c` — 2KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `log_error`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/log_error` — 591B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/log_error` — 591B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `login.c`
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/testsuite/clone/login.c` — 610B
- `mud-references/deadsouls/ds3.8.2/lib/www/cgi/login.c` — 3KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `login.lpc`
- `lib/clone/login.lpc` — 8KB
- `lib/daemon/login.lpc` — 177B
**Recommendation:** Keep the copy in `lib/` and remove duplicates elsewhere.

### `logon`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/interactive/logon` — 367B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/logon` — 367B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `long_boot_l.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/armor/long_boot_l.c` — 678B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/armor/long_boot_l.c` — 655B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `long_boot_r.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/armor/long_boot_r.c` — 682B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/armor/long_boot_r.c` — 659B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `look.c`
- `mud-references/deadsouls/ds3.8.2/lib/lib/events/look.c` — 8KB
- `mud-references/deadsouls/ds3.8.2/lib/verbs/items/look.c` — 5KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `lower_case`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/lower_case` — 272B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/strings/lower_case` — 272B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `lpc_info`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/lpc_info` — 301B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/lpc_info` — 301B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `ls.lpc`
- `lib/cmds/creator/ls.lpc` — 4KB
- `lib/cmds/ls.lpc` — 4KB
**Recommendation:** Keep the copy in `lib/` and remove duplicates elsewhere.

### `m16rifle.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/weap/m16rifle.c` — 824B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/weap/m16rifle.c` — 824B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `m_delete`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/m_delete` — 646B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mappings/m_delete` — 646B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `m_indices`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/m_indices` — 249B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mappings/m_indices` — 249B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `m_values`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/m_values` — 253B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mappings/m_values` — 253B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `macros.h`
- `mud-references/deadsouls/ds3.8.2/extra/wolfpaw/macros.h` — 9KB
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/macros.h` — 9KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `mage`
- `mud-references/deadsouls/ds3.8.2/lib/doc/help/classes/mage` — 646B
- `mud-references/deadsouls/ds3.8.2/lib/secure/cfg/classes/mage` — 189B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `magic.c`
- `mud-references/deadsouls/ds3.8.2/lib/lib/magic.c` — 5KB
- `src/magic.c` — 41KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `magic.h`
- `mud-references/deadsouls/ds3.8.2/lib/include/magic.h` — 184B
- `src/magic.h` — 5KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `maglite.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/obj/maglite.c` — 659B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/obj/maglite.c` — 661B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `make_path_absolute`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/make_path_absolute` — 238B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/make_path_absolute` — 238B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `malloc.c`
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/malloc.c` — 271B
- `mud-references/deadsouls/ds3.8.2/lib/cmds/creators/malloc.c` — 349B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `malloc_status`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/malloc_status` — 488B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/internals/malloc_status` — 488B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `map`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/map` — 708B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/general/map` — 708B
- `mud-references/deadsouls/ds3.8.2/lib/doc/help/players/map` — 18B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `map.c`
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/testsuite/single/tests/efuns/map.c` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/daemon/map.c` — 8KB
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/obj/map.c` — 641B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/obj/map.c` — 536B
- `mud-references/deadsouls/ds3.8.2/lib/secure/cmds/players/map.c` — 431B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `map.txt`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/map.txt` — 956B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/txt/map.txt` — 1004B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `map_array`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/map_array` — 286B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/arrays/map_array` — 286B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `map_delete`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/map_delete` — 760B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mappings/map_delete` — 760B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `map_mapping`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/map_mapping` — 671B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mappings/map_mapping` — 671B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `mapp`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/mapp` — 189B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mixed/mapp` — 189B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `mapping.c`
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/mapping.c` — 38KB
- `mud-references/deadsouls/ds3.8.2/lib/secure/modules/mapping.c` — 11KB
- `src/mapping.c` — 5KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `mapping.h`
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/mapping.h` — 4KB
- `src/mapping.h` — 845B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `mappings`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lpc/concepts/mappings` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/lpc/types/mappings` — 5KB
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `master`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/master` — 188B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/objects/master` — 188B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `master.c`
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/master.c` — 4KB
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/testsuite/single/master.c` — 6KB
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/testsuite/single/tests/efuns/master.c` — 73B
- `mud-references/deadsouls/ds3.8.2/lib/domains/Praxis/adm/master.c` — 611B
- `mud-references/deadsouls/ds3.8.2/lib/secure/daemon/master.c` — 34KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `master.h`
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/master.h` — 365B
- `mud-references/deadsouls/ds3.8.2/lib/secure/daemon/master.h` — 2KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `master.lpc`
- `lib/master.lpc` — 1KB
- `lib/secure/master.lpc` — 5KB
**Recommendation:** Keep the copy in `lib/` and remove duplicates elsewhere.

### `match.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/Praxis/obj/misc/match.c` — 489B
- `mud-references/deadsouls/ds3.8.2/lib/domains/Ylsrim/etc/match.c` — 586B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/obj/match.c` — 615B
- `mud-references/deadsouls/ds3.8.2/lib/domains/cave/obj/match.c` — 519B
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/obj/match.c` — 460B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/obj/match.c` — 519B
- `mud-references/deadsouls/ds3.8.2/lib/lib/match.c` — 1KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `match_path`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/match_path` — 475B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mappings/match_path` — 475B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `math.c`
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/packages/math.c` — 7KB
- `tests/lpc/math.c` — 724B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `max_eval_cost`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/max_eval_cost` — 315B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/max_eval_cost` — 315B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `mayor.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/npc/mayor.c` — 727B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/room/mayor.c` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/lib/mayor.c` — 2KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `meal.c`
- `mud-references/deadsouls/ds3.8.2/lib/lib/meal.c` — 6KB
- `mud-references/deadsouls/ds3.8.2/lib/obj/meal.c` — 469B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `medbag.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/obj/medbag.c` — 576B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/obj/medbag.c` — 438B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `member_array`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/member_array` — 503B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/arrays/member_array` — 503B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `memory_info`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/memory_info` — 693B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/internals/memory_info` — 693B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `memory_summary`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/memory_summary` — 566B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/memory_summary` — 566B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `message`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/message` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/message` — 1KB
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `message.c`
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/testsuite/single/tests/efuns/message.c` — 34B
- `mud-references/deadsouls/ds3.8.2/lib/cmds/creators/message.c` — 1KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `mind_block.lpc`
- `lib/psionics/sensitive/mind_block.lpc` — 2KB
- `lib/psionics/super/mind_block.lpc` — 1KB
**Recommendation:** Keep the copy in `lib/` and remove duplicates elsewhere.

### `mind_melter.lpc`
- `lib/occs/mind_melter.lpc` — 2KB
- `lib/races/mind_melter.lpc` — 3KB
**Recommendation:** Keep the copy in `lib/` and remove duplicates elsewhere.

### `minimap.c`
- `mud-references/deadsouls/ds3.8.2/lib/cmds/players/minimap.c` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/secure/sefun/minimap.c` — 2KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `missile.c`
- `mud-references/deadsouls/ds3.8.2/lib/lib/missile.c` — 4KB
- `mud-references/deadsouls/ds3.8.2/lib/powers/spells/missile.c` — 1KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `mkdir`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/mkdir` — 227B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/filesystem/mkdir` — 227B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `mkdir.c`
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/testsuite/single/tests/efuns/mkdir.c` — 33B
- `mud-references/deadsouls/ds3.8.2/lib/secure/cmds/creators/mkdir.c` — 1KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `money.c`
- `mud-references/deadsouls/ds3.8.2/lib/cmds/players/money.c` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/lib/money.c` — 661B
- `mud-references/deadsouls/ds3.8.2/lib/secure/modules/money.c` — 4KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `monty.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/npc/monty.c` — 6KB
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/room/monty.c` — 2KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `mount.c`
- `mud-references/deadsouls/ds3.8.2/lib/lib/mount.c` — 5KB
- `mud-references/deadsouls/ds3.8.2/lib/verbs/players/mount.c` — 638B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `move.c`
- `mud-references/deadsouls/ds3.8.2/lib/lib/props/move.c` — 6KB
- `mud-references/deadsouls/ds3.8.2/lib/verbs/items/move.c` — 875B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `move_object`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/move_object` — 257B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/objects/move_object` — 257B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `mssp`
- `mud-references/deadsouls/ds3.8.2/lib/doc/help/creators/mssp` — 835B
- `mud-references/deadsouls/ds3.8.2/lib/log/mssp` — 760B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `mud_status`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/mud_status` — 483B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/internals/mud_status` — 483B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `mudinfo.c`
- `mud-references/deadsouls/ds3.8.2/lib/cmds/players/mudinfo.c` — 401B
- `mud-references/deadsouls/ds3.8.2/lib/secure/daemon/mudinfo.c` — 7KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `mudos.cfg`
- `mud-references/deadsouls/ds3.8.2/bin/mudos.cfg` — 5KB
- `mud-references/deadsouls/ds3.8.2/lib/secure/cfg/mudos.cfg` — 5KB
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `named_livings`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/named_livings` — 388B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/named_livings` — 388B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `necklace.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/armor/necklace.c` — 459B
- `mud-references/deadsouls/ds3.8.2/lib/domains/cave/armor/necklace.c` — 432B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `needle_trap.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/obj/needle_trap.c` — 1001B
- `mud-references/deadsouls/ds3.8.2/lib/shadows/needle_trap.c` — 394B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `needle_trap2.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/obj/needle_trap2.c` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/shadows/needle_trap2.c` — 394B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `net_dead`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/interactive/net_dead` — 492B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/net_dead` — 492B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `network_stats`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/network_stats` — 3B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/sockets/network_stats` — 3B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `new`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/new` — 309B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/objects/new` — 309B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `new.c`
- `mud-references/deadsouls/ds3.8.2/lib/cmds/players/new.c` — 306B
- `mud-references/deadsouls/ds3.8.2/lib/www/cgi/new.c` — 2KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `news.c`
- `mud-references/deadsouls/ds3.8.2/lib/daemon/news.c` — 6KB
- `mud-references/deadsouls/ds3.8.2/lib/verbs/players/news.c` — 1KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `news.h`
- `mud-references/deadsouls/ds3.8.2/lib/daemon/include/news.h` — 298B
- `mud-references/deadsouls/ds3.8.2/lib/secure/include/news.h` — 693B
- `mud-references/deadsouls/ds3.8.2/lib/verbs/players/include/news.h` — 123B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `newt.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/npc/newt.c` — 463B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/npc/newt.c` — 470B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `next_bit`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/next_bit` — 282B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/strings/next_bit` — 282B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `next_inventory`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/next_inventory` — 352B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/objects/next_inventory` — 352B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `notify.c`
- `mud-references/deadsouls/ds3.8.2/lib/daemon/notify.c` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/secure/cmds/admins/notify.c` — 2KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `notify_fail`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/notify_fail` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/notify_fail` — 1KB
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `npc.c`
- `mud-references/deadsouls/ds3.8.2/lib/lib/npc.c` — 19KB
- `mud-references/deadsouls/ds3.8.2/lib/obj/npc.c` — 421B
- `src/npc.c` — 15KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `npc.h`
- `mud-references/deadsouls/ds3.8.2/lib/lib/include/npc.h` — 2KB
- `src/npc.h` — 3KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `nullp`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/nullp` — 215B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mixed/nullp` — 215B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `object.c`
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/object.c` — 57KB
- `mud-references/deadsouls/ds3.8.2/lib/lib/comp/object.c` — 1KB
- `src/object.c` — 15KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `object.h`
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/object.h` — 7KB
- `mud-references/deadsouls/ds3.8.2/lib/secure/include/object.h` — 69B
- `src/object.h` — 8KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `object_name`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/object_name` — 377B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/object_name` — 377B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `objectp`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/objectp` — 195B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mixed/objectp` — 195B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `objects`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/objects` — 833B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/objects/objects` — 833B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lpc/concepts/objects` — 717B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `omni.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/obj/omni.c` — 3KB
- `mud-references/deadsouls/ds3.8.2/lib/domains/cave/obj/omni.c` — 3KB
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/obj/omni.c` — 2KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `oob.c`
- `mud-references/deadsouls/ds3.8.2/lib/daemon/services/oob.c` — 76B
- `mud-references/deadsouls/ds3.8.2/lib/secure/daemon/oob.c` — 10KB
- `mud-references/deadsouls/ds3.8.2/lib/secure/lib/net/oob.c` — 8KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `opcprof`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/opcprof` — 482B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/internals/opcprof` — 482B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `opcprof.c`
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/testsuite/single/tests/efuns/opcprof.c` — 115B
- `mud-references/deadsouls/ds3.8.2/lib/secure/cmds/admins/opcprof.c` — 564B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `open.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/Praxis/orc_valley/open.c` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/verbs/items/open.c` — 1KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `options.h`
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/options.h` — 36KB
- `mud-references/deadsouls/ds3.8.2/lib/secure/daemon/options.h` — 470B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `orc`
- `mud-references/deadsouls/ds3.8.2/lib/doc/help/races/orc` — 70B
- `mud-references/deadsouls/ds3.8.2/lib/secure/cfg/races/orc` — 1KB
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `orc.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/npc/orc.c` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/npc/orc.c` — 628B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/npc/orc.c` — 1KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `orc_boot_l.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/cave/armor/orc_boot_l.c` — 675B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/armor/orc_boot_l.c` — 676B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `orc_boot_r.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/cave/armor/orc_boot_r.c` — 678B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/armor/orc_boot_r.c` — 679B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `orc_helmet.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/cave/armor/orc_helmet.c` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/armor/orc_helmet.c` — 1KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `orc_shaman.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/Praxis/obj/mon/orc_shaman.c` — 522B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/npc/orc_shaman.c` — 1KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `orc_slayer.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/Praxis/obj/weapon/orc_slayer.c` — 880B
- `mud-references/deadsouls/ds3.8.2/lib/domains/Ylsrim/weapon/orc_slayer.c` — 1KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `orcslayer.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/Praxis/quests/orcslayer.c` — 493B
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/weap/orcslayer.c` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/weap/orcslayer.c` — 1KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `order.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/Praxis/obj/misc/order.c` — 5KB
- `mud-references/deadsouls/ds3.8.2/lib/obj/order.c` — 450B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `origin`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/origin` — 512B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/calls/origin` — 512B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `origin.h`
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/include/origin.h` — 530B
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/origin.h` — 405B
- `mud-references/deadsouls/ds3.8.2/lib/secure/include/origin.h` — 530B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `overalls.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/armor/overalls.c` — 791B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/armor/overalls.c` — 697B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `pack.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/obj/pack.c` — 709B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/obj/pack.c` — 690B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `package.json`
- `lpc-extension/package.json` — 973B
- `tools/ws_telnet_proxy/package.json` — 299B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `pants.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/cave/armor/pants.c` — 561B
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/armor/pants.c` — 561B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/armor/pants.c` — 511B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `parse_command`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/parse_command` — 9KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/parsing/parse_command` — 9KB
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `parse_command_adjectiv_id_list`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/parse_command_adjectiv_id_list` — 369B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/parsing/parse_command_adjectiv_id_list` — 369B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `parse_command_all_word`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/parse_command_all_word` — 278B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/parse_command_all_word` — 278B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `parse_command_id_list`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/parse_command_id_list` — 340B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/parsing/parse_command_id_list` — 340B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `parse_command_plural_id_list`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/parse_command_plural_id_list` — 361B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/parsing/parse_command_plural_id_list` — 361B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `parse_command_prepos_list`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/parse_command_prepos_list` — 309B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/parse_command_prepos_list` — 309B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `parser.c`
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/packages/parser.c` — 108KB
- `src/parser.c` — 60KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `parser.h`
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/packages/parser.h` — 6KB
- `src/parser.h` — 11KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `parser_error.h`
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/include/parser_error.h` — 283B
- `mud-references/deadsouls/ds3.8.2/lib/secure/include/parser_error.h` — 249B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `party.c`
- `mud-references/deadsouls/ds3.8.2/lib/daemon/party.c` — 8KB
- `mud-references/deadsouls/ds3.8.2/lib/domains/Praxis/party.c` — 7KB
- `mud-references/deadsouls/ds3.8.2/lib/verbs/players/party.c` — 4KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `party.h`
- `mud-references/deadsouls/ds3.8.2/lib/daemon/include/party.h` — 848B
- `mud-references/deadsouls/ds3.8.2/lib/verbs/players/include/party.h` — 389B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `pedestal.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/Praxis/obj/misc/pedestal.c` — 3KB
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/obj/pedestal.c` — 6KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `percent`
- `mud-references/deadsouls/ds3.8.2/lib/doc/sefun/percent` — 554B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charles/bak2/bak1/percent` — 1B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charles/bak2/percent` — 1B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charles/percent` — 1B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charly/bak/percent` — 1B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charly/percent` — 1B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `performMarriage`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/performMarriage` — 379B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/clerk/performMarriage` — 380B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `persist.c`
- `mud-references/deadsouls/ds3.8.2/lib/lib/persist.c` — 4KB
- `mud-references/deadsouls/ds3.8.2/lib/secure/sefun/persist.c` — 337B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `pile.c`
- `mud-references/deadsouls/ds3.8.2/lib/lib/pile.c` — 4KB
- `mud-references/deadsouls/ds3.8.2/lib/std/lib/pile.c` — 100B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `pin.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/obj/pin.c` — 393B
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/obj/pin.c` — 393B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `ping.c`
- `mud-references/deadsouls/ds3.8.2/lib/cmds/creators/ping.c` — 888B
- `mud-references/deadsouls/ds3.8.2/lib/secure/daemon/ping.c` — 3KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `pipe.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/obj/pipe.c` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/lib/pipe.c` — 2KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `pitcher.c`
- `mud-references/deadsouls/ds3.8.2/lib/realms/template/area/obj/pitcher.c` — 651B
- `mud-references/deadsouls/ds3.8.2/lib/realms/thurtea/area/obj/pitcher.c` — 651B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `plan`
- `mud-references/deadsouls/ds3.8.2/lib/doc/help/creators/plan` — 232B
- `mud-references/deadsouls/ds3.8.2/lib/realms/template/plan` — 28B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `platemail.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/cave/armor/platemail.c` — 846B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/armor/platemail.c` — 848B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `pluralize`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/pluralize` — 297B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/strings/pluralize` — 297B
- `mud-references/deadsouls/ds3.8.2/lib/doc/sefun/pluralize` — 677B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `pod.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/cave/room/pod.c` — 388B
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/room/pod.c` — 375B
- `mud-references/deadsouls/ds3.8.2/lib/domains/learning/room/pod.c` — 375B
- `mud-references/deadsouls/ds3.8.2/lib/std/pod.c` — 375B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `pointerp`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/pointerp` — 192B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mixed/pointerp` — 192B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `poison.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/meals/poison.c` — 887B
- `mud-references/deadsouls/ds3.8.2/lib/lib/events/poison.c` — 863B
- `mud-references/deadsouls/ds3.8.2/lib/lib/poison.c` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/verbs/items/poison.c` — 1KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `poison.h`
- `mud-references/deadsouls/ds3.8.2/lib/lib/include/poison.h` — 280B
- `mud-references/deadsouls/ds3.8.2/lib/verbs/items/include/poison.h` — 253B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `pole.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/Ylsrim/etc/pole.c` — 708B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/obj/pole.c` — 715B
- `mud-references/deadsouls/ds3.8.2/lib/lib/pole.c` — 3KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `poleepkwa`
- `mud-references/deadsouls/ds3.8.2/lib/doc/help/races/poleepkwa` — 430B
- `mud-references/deadsouls/ds3.8.2/lib/secure/cfg/races/poleepkwa` — 1KB
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `portal.c`
- `mud-references/deadsouls/ds3.8.2/lib/obj/portal.c` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/secure/daemon/portal.c` — 4KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `portbind`
- `mud-references/deadsouls/ds3.8.2/bin/portbind` — 13KB
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/portbind` — 13KB
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `position.c`
- `mud-references/deadsouls/ds3.8.2/lib/cmds/players/position.c` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/lib/lvs/position.c` — 7KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `post.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/Praxis/post.c` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/secure/obj/post.c` — 51KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `post.h`
- `mud-references/deadsouls/ds3.8.2/lib/secure/include/post.h` — 284B
- `mud-references/deadsouls/ds3.8.2/lib/secure/obj/include/post.h` — 3KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `pow`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/pow` — 260B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/floats/pow` — 260B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `preload`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/preload` — 533B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/preload` — 533B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `present`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/present` — 643B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/objects/present` — 643B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `press.c`
- `mud-references/deadsouls/ds3.8.2/lib/lib/events/press.c` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/verbs/items/press.c` — 1KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `previous_object`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/previous_object` — 734B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/calls/previous_object` — 734B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `print.css`
- `mud-references/deadsouls/ds3.8.2/lib/www/lpmuds/print.css` — 60B
- `mud-references/deadsouls/ds3.8.2/lib/www/print.css` — 60B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `printf`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/printf` — 3KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/printf` — 3KB
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `privs_file`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/privs_file` — 481B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/privs_file` — 481B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `process_input`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/interactive/process_input` — 851B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/process_input` — 851B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `profile`
- `mud-references/deadsouls/ds3.8.2/lib/doc/help/creators/profile` — 331B
- `mud-references/deadsouls/ds3.8.2/lib/realms/template/profile` — 21B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `program.c`
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/program.c` — 3KB
- `src/program.c` — 3KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `program.h`
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/program.h` — 10KB
- `src/program.h` — 1KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `program_info`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/program_info` — 357B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/program_info` — 357B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `promote.lpc`
- `lib/cmds/admin/promote.lpc` — 4KB
- `lib/cmds/promote.lpc` — 278B
**Recommendation:** Keep the copy in `lib/` and remove duplicates elsewhere.

### `psi_healer.lpc`
- `lib/occs/psi_healer.lpc` — 2KB
- `lib/races/psi_healer.lpc` — 4KB
**Recommendation:** Keep the copy in `lib/` and remove duplicates elsewhere.

### `psi_stalker.lpc`
- `lib/occs/psi_stalker.lpc` — 2KB
- `lib/races/psi_stalker.lpc` — 6KB
**Recommendation:** Keep the copy in `lib/` and remove duplicates elsewhere.

### `psi_sword.lpc`
- `lib/psionics/physical/psi_sword.lpc` — 4KB
- `lib/psionics/super/psi_sword.lpc` — 4KB
**Recommendation:** Keep the copy in `lib/` and remove duplicates elsewhere.

### `pub.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/Praxis/pub.c` — 3KB
- `mud-references/deadsouls/ds3.8.2/lib/domains/Ylsrim/room/pub.c` — 3KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `pull.c`
- `mud-references/deadsouls/ds3.8.2/lib/lib/events/pull.c` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/verbs/items/pull.c` — 1KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `put.c`
- `mud-references/deadsouls/ds3.8.2/lib/lib/events/put.c` — 3KB
- `mud-references/deadsouls/ds3.8.2/lib/verbs/items/put.c` — 6KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `put.h`
- `mud-references/deadsouls/ds3.8.2/lib/lib/include/put.h` — 369B
- `mud-references/deadsouls/ds3.8.2/lib/verbs/items/include/put.h` — 321B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `pwd.lpc`
- `lib/cmds/creator/pwd.lpc` — 353B
- `lib/cmds/pwd.lpc` — 276B
**Recommendation:** Keep the copy in `lib/` and remove duplicates elsewhere.

### `query_ed_mode`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/query_ed_mode` — 376B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/query_ed_mode` — 376B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `query_heart_beat`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/query_heart_beat` — 401B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/objects/query_heart_beat` — 401B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `query_host_name`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/query_host_name` — 256B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/query_host_name` — 256B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `query_idle`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/query_idle` — 269B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/query_idle` — 269B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `query_ip_name`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/query_ip_name` — 451B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/query_ip_name` — 451B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `query_ip_number`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/query_ip_number` — 299B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/query_ip_number` — 299B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `query_ip_port`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/query_ip_port` — 541B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/query_ip_port` — 541B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `query_load_average`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/query_load_average` — 299B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/internals/query_load_average` — 299B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `query_notify_fail`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/query_notify_fail` — 599B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/query_notify_fail` — 599B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `query_num`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/query_num` — 3B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/numbers/query_num` — 3B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `query_privs`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/query_privs` — 444B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mudlib/query_privs` — 444B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `query_shadowing`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/query_shadowing` — 375B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/calls/query_shadowing` — 375B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `query_snoop`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/query_snoop` — 268B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/query_snoop` — 268B
- `mud-references/deadsouls/ds3.8.2/lib/doc/sefun/query_snoop` — 614B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `query_snooping`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/query_snooping` — 333B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/query_snooping` — 333B
- `mud-references/deadsouls/ds3.8.2/lib/doc/sefun/query_snooping` — 549B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `query_verb`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/query_verb` — 498B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/parsing/query_verb` — 498B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `quest_ob.c`
- `mud-references/deadsouls/ds3.8.2/lib/obj/quest_ob.c` — 577B
- `mud-references/deadsouls/ds3.8.2/lib/std/quest_ob.c` — 122B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `race.h`
- `mud-references/deadsouls/ds3.8.2/lib/include/race.h` — 162B
- `mud-references/deadsouls/ds3.8.2/lib/lib/include/race.h` — 742B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `races`
- `lib/data/help/systems/races` — 3KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/help/players/races` — 2KB
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `rack.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/cave/obj/rack.c` — 788B
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/obj/rack.c` — 855B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/obj/rack.c` — 929B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `random`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/random` — 204B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/numbers/random` — 204B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `rat.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/npc/rat.c` — 668B
- `mud-references/deadsouls/ds3.8.2/lib/domains/cave/npc/rat.c` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/npc/rat.c` — 986B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/npc/rat.c` — 963B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `rations.lpc`
- `lib/objects/supplies/rations.lpc` — 513B
- `lib/single/rations.lpc` — 580B
**Recommendation:** Keep the copy in `lib/` and remove duplicates elsewhere.

### `rayovac.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/obj/rayovac.c` — 667B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/obj/rayovac.c` — 680B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `read.c`
- `mud-references/deadsouls/ds3.8.2/lib/lib/events/read.c` — 4KB
- `mud-references/deadsouls/ds3.8.2/lib/secure/modules/read.c` — 3KB
- `mud-references/deadsouls/ds3.8.2/lib/verbs/items/read.c` — 2KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `read.h`
- `mud-references/deadsouls/ds3.8.2/lib/lib/include/read.h` — 318B
- `mud-references/deadsouls/ds3.8.2/lib/verbs/items/include/read.h` — 323B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `read_buffer`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/read_buffer` — 844B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/buffers/read_buffer` — 844B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `read_bytes`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/read_bytes` — 467B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/filesystem/read_bytes` — 467B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `read_file`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/read_file` — 510B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/filesystem/read_file` — 510B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `readme`
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/packages/readme` — 289B
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/testsuite/clone/readme` — 0B
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/testsuite/command/readme` — 135B
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/testsuite/data/readme` — 77B
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/testsuite/include/readme` — 98B
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/testsuite/inherit/readme` — 81B
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/testsuite/log/readme` — 72B
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/testsuite/readme` — 2KB
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/testsuite/single/readme` — 193B
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/testsuite/single/tests/efuns/readme` — 0B
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/testsuite/u/readme` — 84B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `reaper.c`
- `mud-references/deadsouls/ds3.8.2/lib/secure/daemon/reaper.c` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/secure/sefun/reaper.c` — 2KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `receive`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/receive` — 475B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/receive` — 475B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `receive_message`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/interactive/receive_message` — 561B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/receive_message` — 561B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `receive_snoop`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/interactive/receive_snoop` — 458B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/receive_snoop` — 458B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `reclaim_objects`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/reclaim_objects` — 649B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/reclaim_objects` — 649B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `red_wins`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charles/bak2/bak1/red_wins` — 3B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charles/bak2/red_wins` — 2B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charles/red_wins` — 5B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charly/bak/red_wins` — 5B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charly/red_wins` — 5B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `refs`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/refs` — 383B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/internals/refs` — 383B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `reg_assoc`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/reg_assoc` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/strings/reg_assoc` — 2KB
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `regexp`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/regexp` — 4KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/strings/regexp` — 4KB
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `regexp.c`
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/regexp.c` — 40KB
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/testsuite/single/tests/efuns/regexp.c` — 937B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `register.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/obj/register.c` — 548B
- `mud-references/deadsouls/ds3.8.2/lib/secure/cmds/admins/register.c` — 2KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `reload.c`
- `mud-references/deadsouls/ds3.8.2/lib/secure/daemon/reload.c` — 14KB
- `mud-references/deadsouls/ds3.8.2/lib/secure/sefun/reload.c` — 3KB
- `mud-references/deadsouls/ds3.8.2/lib/verbs/builders/reload.c` — 5KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `reload_object`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/reload_object` — 517B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/objects/reload_object` — 517B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `remote.c`
- `mud-references/deadsouls/ds3.8.2/extra/creremote/remote.c` — 3KB
- `mud-references/deadsouls/ds3.8.2/lib/realms/template/adm/remote.c` — 77B
- `mud-references/deadsouls/ds3.8.2/lib/realms/thurtea/adm/remote.c` — 77B
- `mud-references/deadsouls/ds3.8.2/lib/secure/lib/net/remote.c` — 5KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `remove_action`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/remove_action` — 543B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/remove_action` — 543B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `remove_call_out`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/remove_call_out` — 541B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/calls/remove_call_out` — 541B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `remove_interactive`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/remove_interactive` — 457B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/remove_interactive` — 457B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `remove_shadow`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/remove_shadow` — 423B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/calls/remove_shadow` — 423B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `rename`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/rename` — 207B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/filesystem/rename` — 207B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `repeat_string`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/repeat_string` — 427B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/strings/repeat_string` — 427B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `replace_program`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/replace_program` — 901B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/replace_program` — 901B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `replace_string`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/replace_string` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/strings/replace_string` — 2KB
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `replaceable`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/replaceable` — 868B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/replaceable` — 868B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `reset`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/reset` — 461B
- `mud-references/deadsouls/ds3.8.2/lib/log/reset` — 2KB
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `reset_eval_cost`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/reset_eval_cost` — 277B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/reset_eval_cost` — 277B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `resolve`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/resolve` — 798B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/resolve` — 798B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `restore_object`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/restore_object` — 504B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/objects/restore_object` — 504B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `restore_variable`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/restore_variable` — 314B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/general/restore_variable` — 314B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `retrieve_ed_setup`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/retrieve_ed_setup` — 304B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/retrieve_ed_setup` — 304B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `returnChannels`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/returnChannels` — 338B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/chat/returnChannels` — 338B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `ring.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/armor/ring.c` — 516B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/armor/ring.c` — 493B
- `mud-references/deadsouls/ds3.8.2/lib/shadows/ring.c` — 4KB
- `mud-references/deadsouls/ds3.8.2/lib/verbs/items/ring.c` — 1KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `rm`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/rm` — 208B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/filesystem/rm` — 208B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `rm.c`
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/testsuite/command/rm.c` — 118B
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/testsuite/single/tests/efuns/rm.c` — 151B
- `mud-references/deadsouls/ds3.8.2/lib/secure/cmds/creators/rm.c` — 2KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `rmdir`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/rmdir` — 160B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/filesystem/rmdir` — 160B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `rmdir.c`
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/testsuite/single/tests/efuns/rmdir.c` — 144B
- `mud-references/deadsouls/ds3.8.2/lib/secure/cmds/creators/rmdir.c` — 1KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `road.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/Ylsrim/etc/road.c` — 975B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/room/road.c` — 2KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `robe.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/armor/robe.c` — 579B
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/armor/robe.c` — 774B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/armor/robe.c` — 563B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `rock.c`
- `mud-references/deadsouls/ds3.8.2/lib/lib/events/rock.c` — 561B
- `mud-references/deadsouls/ds3.8.2/lib/verbs/items/rock.c` — 1KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `rocketpack.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/armor/rocketpack.c` — 6KB
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/armor/rocketpack.c` — 952B
- `mud-references/deadsouls/ds3.8.2/lib/shadows/rocketpack.c` — 648B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `roll.c`
- `mud-references/deadsouls/ds3.8.2/lib/lib/events/roll.c` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/verbs/items/roll.c` — 4KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `room.c`
- `mud-references/deadsouls/ds3.8.2/lib/lib/std/room.c` — 32KB
- `mud-references/deadsouls/ds3.8.2/lib/obj/room.c` — 212B
- `mud-references/deadsouls/ds3.8.2/lib/realms/thurtea/room.c` — 4KB
- `mud-references/deadsouls/ds3.8.2/lib/secure/modules/room.c` — 19KB
- `mud-references/deadsouls/ds3.8.2/lib/std/room.c` — 100B
- `src/room.c` — 58KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `room.h`
- `mud-references/deadsouls/ds3.8.2/lib/lib/include/room.h` — 1KB
- `src/room.h` — 3KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `rooms.c`
- `mud-references/deadsouls/ds3.8.2/lib/secure/daemon/rooms.c` — 24KB
- `mud-references/deadsouls/ds3.8.2/lib/secure/sefun/rooms.c` — 5KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `round.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/obj/round.c` — 469B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/obj/round.c` — 469B
- `mud-references/deadsouls/ds3.8.2/lib/lib/round.c` — 4KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `router.c`
- `mud-references/deadsouls/ds3.8.2/lib/secure/cmds/admins/router.c` — 16KB
- `mud-references/deadsouls/ds3.8.2/lib/secure/room/router.c` — 7KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `runs`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charles/bak2/bak1/runs` — 3B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charles/bak2/runs` — 3B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charles/runs` — 5B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charly/bak/runs` — 5B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charly/runs` — 6B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `runtime`
- `mud-references/deadsouls/ds3.8.2/lib/log/runtime` — 382B
- `mud-references/deadsouls/ds3.8.2/log/runtime` — 2KB
- `mud-references/deadsouls/log/runtime` — 0B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `runtime_config.h`
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/include/runtime_config.h` — 3KB
- `mud-references/deadsouls/ds3.8.2/lib/secure/include/runtime_config.h` — 3KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `rusage`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/rusage` — 964B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/internals/rusage` — 964B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `sample_room.c`
- `mud-references/deadsouls/ds3.8.2/lib/realms/template/area/room/sample_room.c` — 623B
- `mud-references/deadsouls/ds3.8.2/lib/realms/thurtea/area/room/sample_room.c` — 623B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `sample_two.c`
- `mud-references/deadsouls/ds3.8.2/lib/realms/template/area/room/sample_two.c` — 532B
- `mud-references/deadsouls/ds3.8.2/lib/realms/thurtea/area/room/sample_two.c` — 532B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `save.c`
- `mud-references/deadsouls/ds3.8.2/lib/cmds/players/save.c` — 766B
- `mud-references/deadsouls/ds3.8.2/lib/lib/props/save.c` — 3KB
- `mud-references/deadsouls/ds3.8.2/lib/www/cgi/save.c` — 2KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `save_ed_setup`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/save_ed_setup` — 347B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/save_ed_setup` — 347B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `save_object`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/save_object` — 577B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/objects/save_object` — 577B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `save_variable`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/save_variable` — 222B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/general/save_variable` — 222B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `say`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/say` — 712B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/say` — 712B
- `mud-references/deadsouls/ds3.8.2/lib/doc/sefun/say` — 1010B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `say.c`
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/testsuite/command/say.c` — 191B
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/testsuite/single/tests/efuns/say.c` — 734B
- `mud-references/deadsouls/ds3.8.2/lib/verbs/common/say.c` — 2KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `scratch.c`
- `mud-references/deadsouls/ds3.8.2/lib/lib/events/scratch.c` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/verbs/items/scratch.c` — 1KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `search.c`
- `mud-references/deadsouls/ds3.8.2/lib/lib/events/search.c` — 4KB
- `mud-references/deadsouls/ds3.8.2/lib/verbs/items/search.c` — 2KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `search.h`
- `mud-references/deadsouls/ds3.8.2/lib/lib/include/search.h` — 396B
- `mud-references/deadsouls/ds3.8.2/lib/verbs/items/include/search.h` — 207B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `sell.c`
- `mud-references/deadsouls/ds3.8.2/lib/lib/events/sell.c` — 500B
- `mud-references/deadsouls/ds3.8.2/lib/verbs/items/sell.c` — 2KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `server.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/Ylsrim/virtual/server.c` — 582B
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/virtual/server.c` — 778B
- `mud-references/deadsouls/ds3.8.2/lib/domains/learning/virtual/server.c` — 825B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/virtual/server.c` — 778B
- `mud-references/deadsouls/ds3.8.2/lib/secure/daemon/i3router/server.c` — 26KB
- `mud-references/deadsouls/ds3.8.2/lib/secure/daemon/imc2server/server.c` — 22KB
- `mud-references/deadsouls/ds3.8.2/lib/secure/lib/net/server.c` — 9KB
- `src/server.c` — 18KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `server_log.h`
- `mud-references/deadsouls/ds3.8.2/lib/secure/daemon/i3router/server_log.h` — 264B
- `mud-references/deadsouls/ds3.8.2/lib/secure/daemon/imc2server/server_log.h` — 274B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `set_author`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/set_author` — 776B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mudlib/set_author` — 776B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `set_bit`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/set_bit` — 525B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/strings/set_bit` — 525B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `set_debug_level`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/set_debug_level` — 531B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/internals/set_debug_level` — 531B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `set_eval_limit`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/set_eval_limit` — 477B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/set_eval_limit` — 477B
- `mud-references/deadsouls/ds3.8.2/lib/doc/sefun/set_eval_limit` — 573B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `set_heart_beat`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/set_heart_beat` — 638B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/objects/set_heart_beat` — 638B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `set_hide`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/set_hide` — 569B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/objects/set_hide` — 569B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `set_light`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/set_light` — 608B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mudlib/set_light` — 608B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `set_living_name`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/set_living_name` — 406B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mudlib/set_living_name` — 406B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `set_malloc_mask`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/set_malloc_mask` — 520B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/internals/set_malloc_mask` — 520B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `set_privs`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/set_privs` — 371B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mudlib/set_privs` — 371B
- `mud-references/deadsouls/ds3.8.2/lib/doc/sefun/set_privs` — 528B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `set_reset`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/set_reset` — 495B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/set_reset` — 495B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `set_this_player`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/set_this_player` — 487B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/set_this_player` — 487B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `seteuid`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/seteuid` — 568B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mudlib/seteuid` — 568B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `sewer.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/Praxis/sewer.c` — 653B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/room/sewer.c` — 3KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `shadow`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/shadow` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/calls/shadow` — 2KB
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `shadow.c`
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/testsuite/single/tests/efuns/shadow.c` — 749B
- `mud-references/deadsouls/ds3.8.2/lib/lib/shadow.c` — 671B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `shake.c`
- `mud-references/deadsouls/ds3.8.2/lib/lib/events/shake.c` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/verbs/items/shake.c` — 926B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `shallow_inherit_list`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/shallow_inherit_list` — 436B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/shallow_inherit_list` — 436B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `shark.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/Ylsrim/fish/shark.c` — 970B
- `mud-references/deadsouls/ds3.8.2/lib/domains/Ylsrim/meal/shark.c` — 573B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/meals/shark.c` — 1KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `sharpsword.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/weap/sharpsword.c` — 655B
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/weap/sharpsword.c` — 495B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/weap/sharpsword.c` — 531B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `shield.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/Ylsrim/armor/shield.c` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/armor/shield.c` — 792B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/armor/shield.c` — 659B
- `mud-references/deadsouls/ds3.8.2/lib/obj/shield.c` — 655B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `shield.lpc`
- `lib/objects/armor/shield.lpc` — 313B
- `lib/single/shield.lpc` — 687B
**Recommendation:** Keep the copy in `lib/` and remove duplicates elsewhere.

### `shirt.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/armor/shirt.c` — 501B
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/armor/shirt.c` — 499B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/armor/shirt.c` — 431B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `shoot.c`
- `mud-references/deadsouls/ds3.8.2/lib/lib/events/shoot.c` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/verbs/items/shoot.c` — 3KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `shop.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/cave/room/shop.c` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/room/shop.c` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/lib/shop.c` — 812B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `shop2.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/cave/room/shop2.c` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/room/shop2.c` — 2KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `shout`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/shout` — 272B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/shout` — 272B
- `mud-references/deadsouls/ds3.8.2/lib/doc/sefun/shout` — 665B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `shovel.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/Praxis/obj/misc/shovel.c` — 532B
- `mud-references/deadsouls/ds3.8.2/lib/domains/Ylsrim/etc/shovel.c` — 539B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `show.c`
- `mud-references/deadsouls/ds3.8.2/lib/lib/events/show.c` — 382B
- `mud-references/deadsouls/ds3.8.2/lib/verbs/items/show.c` — 1KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `shutdown`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/shutdown` — 951B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/shutdown` — 951B
- `mud-references/deadsouls/ds3.8.2/lib/doc/sefun/shutdown` — 477B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `shutdown.c`
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/testsuite/command/shutdown.c` — 72B
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/testsuite/single/tests/efuns/shutdown.c` — 163B
- `mud-references/deadsouls/ds3.8.2/lib/secure/cmds/admins/shutdown.c` — 2KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `shutdown.lpc`
- `lib/cmds/admin/shutdown.lpc` — 283B
- `lib/cmds/shutdown.lpc` — 254B
**Recommendation:** Keep the copy in `lib/` and remove duplicates elsewhere.

### `silverring.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/armor/silverring.c` — 816B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/armor/silverring.c` — 799B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `simple_chair.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/obj/simple_chair.c` — 361B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/obj/simple_chair.c` — 361B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `simul_efun.c`
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/simul_efun.c` — 5KB
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/testsuite/single/simul_efun.c` — 4KB
- `src/simul_efun.c` — 4KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `simul_efun.h`
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/simul_efun.h` — 298B
- `src/simul_efun.h` — 1KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `sin`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/sin` — 291B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/floats/sin` — 291B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `sink.c`
- `mud-references/deadsouls/ds3.8.2/lib/lib/events/sink.c` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/verbs/players/sink.c` — 942B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `sit.c`
- `mud-references/deadsouls/ds3.8.2/lib/lib/events/sit.c` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/verbs/players/sit.c` — 2KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `sizeof`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/sizeof` — 269B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/general/sizeof` — 269B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `skills.c`
- `mud-references/deadsouls/ds3.8.2/lib/cmds/players/skills.c` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/daemon/skills.c` — 2KB
- `src/skills.c` — 27KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `skills.lpc`
- `lib/cmds/skills.lpc` — 2KB
- `lib/daemon/skills.lpc` — 7KB
**Recommendation:** Keep the copy in `lib/` and remove duplicates elsewhere.

### `skin.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/cave/obj/skin.c` — 589B
- `mud-references/deadsouls/ds3.8.2/lib/verbs/items/skin.c` — 2KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `sky.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/virtual/sky.c` — 5KB
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/virtual/sky.c` — 4KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `slow_shutdown`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/slow_shutdown` — 576B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/slow_shutdown` — 576B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `smell.c`
- `mud-references/deadsouls/ds3.8.2/lib/lib/events/smell.c` — 3KB
- `mud-references/deadsouls/ds3.8.2/lib/verbs/items/smell.c` — 2KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `smell.h`
- `mud-references/deadsouls/ds3.8.2/lib/lib/include/smell.h` — 337B
- `mud-references/deadsouls/ds3.8.2/lib/verbs/items/include/smell.h` — 207B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `smflogo.gif`
- `mud-references/deadsouls/ds3.8.2/lib/www/lpmuds/smflogo.gif` — 4KB
- `mud-references/deadsouls/ds3.8.2/lib/www/smflogo.gif` — 334B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `smoke.c`
- `mud-references/deadsouls/ds3.8.2/lib/lib/events/smoke.c` — 225B
- `mud-references/deadsouls/ds3.8.2/lib/verbs/items/smoke.c` — 1KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `snoop`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/snoop` — 805B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/snoop` — 805B
- `mud-references/deadsouls/ds3.8.2/lib/doc/sefun/snoop` — 443B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `snoop.c`
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/testsuite/single/tests/efuns/snoop.c` — 85B
- `mud-references/deadsouls/ds3.8.2/lib/secure/cmds/creators/snoop.c` — 849B
- `mud-references/deadsouls/ds3.8.2/lib/secure/daemon/snoop.c` — 9KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `socket_accept`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/socket_accept` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/sockets/socket_accept` — 2KB
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `socket_acquire`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/socket_acquire` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/sockets/socket_acquire` — 1KB
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `socket_address`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/socket_address` — 578B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/sockets/socket_address` — 578B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `socket_bind`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/socket_bind` — 907B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/sockets/socket_bind` — 907B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `socket_close`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/socket_close` — 547B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/sockets/socket_close` — 547B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `socket_connect`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/socket_connect` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/sockets/socket_connect` — 2KB
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `socket_create`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/socket_create` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/sockets/socket_create` — 2KB
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `socket_err.h`
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/include/socket_err.h` — 2KB
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/socket_err.h` — 109B
- `mud-references/deadsouls/ds3.8.2/lib/secure/include/socket_err.h` — 2KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `socket_error`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/socket_error` — 465B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/sockets/socket_error` — 465B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `socket_error.h`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/socket_error.h` — 0B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/sockets/socket_error.h` — 0B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `socket_listen`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/socket_listen` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/sockets/socket_listen` — 1KB
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `socket_release`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/socket_release` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/sockets/socket_release` — 2KB
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `socket_write`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/socket_write` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/sockets/socket_write` — 1KB
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `sockets.c`
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/packages/sockets.c` — 7KB
- `mud-references/deadsouls/ds3.8.2/lib/secure/sefun/sockets.c` — 1KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `sofa.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/obj/sofa.c` — 666B
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/obj/sofa.c` — 500B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/obj/sofa.c` — 502B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `sort_array`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/sort_array` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/arrays/sort_array` — 1KB
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `source.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/room/source.c` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/secure/cmds/creators/source.c` — 3KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `spam.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/obj/spam.c` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/obj/spam.c` — 2KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `spam.txt`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/spam.txt` — 880B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/txt/spam.txt` — 863B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `spells.c`
- `mud-references/deadsouls/ds3.8.2/lib/cmds/players/spells.c` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/daemon/spells.c` — 2KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `spent.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/obj/spent.c` — 598B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/obj/spent.c` — 575B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `spider.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/Praxis/obj/mon/spider.c` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/npc/spider.c` — 592B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/npc/spider.c` — 550B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `spike.lpc`
- `lib/domains/castle/spike.lpc` — 3KB
- `lib/domains/staff_castle/npc/spike.lpc` — 5KB
**Recommendation:** Keep the copy in `lib/` and remove duplicates elsewhere.

### `sprintf`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/sprintf` — 3KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/strings/sprintf` — 3KB
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `sprintf.c`
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/sprintf.c` — 47KB
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/testsuite/single/tests/efuns/sprintf.c` — 5KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `sqrt`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/sqrt` — 332B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/floats/sqrt` — 332B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `sscanf`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/sscanf` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/strings/sscanf` — 2KB
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `stables.lpc`
- `lib/domains/new_camelot/stables.lpc` — 524B
- `lib/domains/staff_castle/room/stables.lpc` — 2KB
**Recommendation:** Keep the copy in `lib/` and remove duplicates elsewhere.

### `staff.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/weap/staff.c` — 597B
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/weap/staff.c` — 573B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/weap/staff.c` — 633B
- `mud-references/deadsouls/ds3.8.2/lib/secure/obj/staff.c` — 992B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `stargate.c`
- `mud-references/deadsouls/ds3.8.2/lib/cmds/creators/stargate.c` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/daemon/stargate.c` — 4KB
- `mud-references/deadsouls/ds3.8.2/lib/domains/Praxis/obj/misc/stargate.c` — 510B
- `mud-references/deadsouls/ds3.8.2/lib/domains/Ylsrim/obj/stargate.c` — 513B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/obj/stargate.c` — 517B
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/obj/stargate.c` — 528B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/obj/stargate.c` — 523B
- `mud-references/deadsouls/ds3.8.2/lib/lib/stargate.c` — 7KB
- `mud-references/deadsouls/ds3.8.2/lib/obj/stargate.c` — 3KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `stargate.h`
- `mud-references/deadsouls/ds3.8.2/lib/daemon/include/stargate.h` — 473B
- `mud-references/deadsouls/ds3.8.2/lib/include/stargate.h` — 333B
- `mud-references/deadsouls/ds3.8.2/lib/lib/include/stargate.h` — 283B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `start.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/room/start.c` — 980B
- `mud-references/deadsouls/ds3.8.2/lib/domains/cave/room/start.c` — 229B
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/room/start.c` — 1011B
- `mud-references/deadsouls/ds3.8.2/lib/domains/examples/room/start.c` — 384B
- `mud-references/deadsouls/ds3.8.2/lib/domains/learning/room/start.c` — 470B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/room/start.c` — 1KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `start.lpc`
- `lib/cmds/start.lpc` — 1KB
- `lib/domains/tutorial/rooms/start.lpc` — 345B
**Recommendation:** Keep the copy in `lib/` and remove duplicates elsewhere.

### `stat`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/stat` — 514B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/filesystem/stat` — 514B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `stats.c`
- `mud-references/deadsouls/ds3.8.2/lib/cmds/players/stats.c` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/daemon/stats.c` — 1KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `stays`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charles/bak2/bak1/stays` — 3B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charles/bak2/stays` — 2B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charles/stays` — 1B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charly/bak/stays` — 5B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charly/stays` — 5B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `std.h`
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/std.h` — 560B
- `mud-references/deadsouls/ds3.8.2/lib/secure/include/std.h` — 1KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `steal.c`
- `mud-references/deadsouls/ds3.8.2/lib/lib/steal.c` — 946B
- `mud-references/deadsouls/ds3.8.2/lib/verbs/items/steal.c` — 4KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `steal.h`
- `mud-references/deadsouls/ds3.8.2/lib/lib/include/steal.h` — 370B
- `mud-references/deadsouls/ds3.8.2/lib/verbs/items/include/steal.h` — 378B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `steel_door.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/doors/steel_door.c` — 786B
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/doors/steel_door.c` — 720B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/doors/steel_door.c` — 638B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `steel_door2.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/doors/steel_door2.c` — 792B
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/doors/steel_door2.c` — 730B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `steel_door3.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/doors/steel_door3.c` — 649B
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/doors/steel_door3.c` — 730B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `stein.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/cave/obj/stein.c` — 651B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/meals/stein.c` — 572B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `stick.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/Ylsrim/weapon/stick.c` — 678B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/obj/stick.c` — 843B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `stone.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/Praxis/obj/misc/stone.c` — 4KB
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/doors/stone.c` — 1KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `stop.c`
- `mud-references/deadsouls/ds3.8.2/lib/lib/events/stop.c` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/verbs/rooms/stop.c` — 626B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `storage.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/Praxis/storage.c` — 433B
- `mud-references/deadsouls/ds3.8.2/lib/lib/std/storage.c` — 772B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `store_variable`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/store_variable` — 475B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/general/store_variable` — 475B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `strcmp`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/strcmp` — 692B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/strings/strcmp` — 692B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `stringp`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/stringp` — 211B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mixed/stringp` — 211B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `strings.c`
- `mud-references/deadsouls/ds3.8.2/lib/secure/sefun/strings.c` — 25KB
- `tests/lpc/strings.c` — 1011B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `strlen`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/strlen` — 220B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/strings/strlen` — 220B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `strsrch`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/strsrch` — 703B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/strings/strsrch` — 703B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `style.css`
- `mud-references/deadsouls/ds3.8.2/lib/www/lpmuds/style.css` — 8KB
- `mud-references/deadsouls/ds3.8.2/lib/www/style.css` — 2KB
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `surface.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/virtual/surface.c` — 3KB
- `mud-references/deadsouls/ds3.8.2/lib/lib/comp/surface.c` — 159B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `swap`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/swap` — 549B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/internals/swap` — 549B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `swim.c`
- `mud-references/deadsouls/ds3.8.2/lib/lib/events/swim.c` — 109B
- `mud-references/deadsouls/ds3.8.2/lib/verbs/rooms/swim.c` — 3KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `switches`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charles/bak2/bak1/switches` — 3B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charles/bak2/switches` — 1B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charles/switches` — 5B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charly/bak/switches` — 5B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charly/switches` — 5B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `swivel.c`
- `mud-references/deadsouls/ds3.8.2/lib/lib/events/swivel.c` — 581B
- `mud-references/deadsouls/ds3.8.2/lib/verbs/items/swivel.c` — 1KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `sword.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/Praxis/obj/weapon/sword.c` — 549B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/weap/sword.c` — 639B
- `mud-references/deadsouls/ds3.8.2/lib/domains/cave/weap/sword.c` — 509B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/weap/sword.c` — 509B
- `mud-references/deadsouls/ds3.8.2/lib/obj/sword.c` — 495B
- `mud-references/deadsouls/ds3.8.2/lib/realms/template/area/weap/sword.c` — 469B
- `mud-references/deadsouls/ds3.8.2/lib/realms/thurtea/area/weap/sword.c` — 469B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `sword.lpc`
- `lib/objects/weapons/sword.lpc` — 317B
- `lib/single/sword.lpc` — 660B
**Recommendation:** Keep the copy in `lib/` and remove duplicates elsewhere.

### `system_libs`
- `mud-references/deadsouls/ds3.8.2/extra/wolfpaw/system_libs` — 32B
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/system_libs` — 23B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `table.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/cave/obj/table.c` — 576B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/obj/table.c` — 595B
- `mud-references/deadsouls/ds3.8.2/lib/lib/std/table.c` — 344B
- `mud-references/deadsouls/ds3.8.2/lib/obj/table.c` — 349B
- `mud-references/deadsouls/ds3.8.2/lib/realms/template/area/obj/table.c` — 591B
- `mud-references/deadsouls/ds3.8.2/lib/realms/thurtea/area/obj/table.c` — 591B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `tail`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/tail` — 281B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/filesystem/tail` — 281B
- `mud-references/deadsouls/ds3.8.2/lib/doc/sefun/tail` — 473B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `tail.c`
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/compat/simuls/tail.c` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/secure/cmds/creators/tail.c` — 1021B
- `mud-references/deadsouls/ds3.8.2/lib/secure/sefun/tail.c` — 305B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `tan`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/tan` — 227B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/floats/tan` — 227B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `teach.c`
- `mud-references/deadsouls/ds3.8.2/lib/lib/teach.c` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/verbs/players/teach.c` — 1KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `telekinesis.lpc`
- `lib/psionics/physical/telekinesis.lpc` — 2KB
- `lib/spells/level3/telekinesis.lpc` — 3KB
**Recommendation:** Keep the copy in `lib/` and remove duplicates elsewhere.

### `tell.c`
- `mud-references/deadsouls/ds3.8.2/lib/daemon/services/tell.c` — 3KB
- `mud-references/deadsouls/ds3.8.2/lib/secure/cmds/players/tell.c` — 8KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `tell_object`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/tell_object` — 386B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/objects/tell_object` — 386B
- `mud-references/deadsouls/ds3.8.2/lib/doc/sefun/tell_object` — 450B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `tell_room`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/tell_room` — 451B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/objects/tell_room` — 451B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `teller_check`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/teller_check` — 355B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/bank/teller_check` — 355B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `telnet_suboption`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/interactive/telnet_suboption` — 687B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/telnet_suboption` — 687B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `terminal.c`
- `mud-references/deadsouls/ds3.8.2/lib/cmds/players/terminal.c` — 693B
- `mud-references/deadsouls/ds3.8.2/lib/daemon/terminal.c` — 6KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `terminal_colour`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/terminal_colour` — 625B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/strings/terminal_colour` — 625B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `terminal_type`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/interactive/terminal_type` — 395B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/terminal_type` — 395B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `test.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/room/test.c` — 394B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/doors/test.c` — 717B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `test_bit`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/test_bit` — 242B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/strings/test_bit` — 242B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `tests.c`
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/testsuite/command/tests.c` — 1KB
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/testsuite/inherit/tests.c` — 123B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `thief`
- `mud-references/deadsouls/ds3.8.2/lib/doc/help/classes/thief` — 477B
- `mud-references/deadsouls/ds3.8.2/lib/secure/cfg/classes/thief` — 264B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `thing.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/obj/thing.c` — 444B
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/obj/thing.c` — 450B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/obj/thing.c` — 449B
- `mud-references/deadsouls/ds3.8.2/lib/obj/thing.c` — 450B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `this_interactive`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/this_interactive` — 392B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/this_interactive` — 392B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `this_object`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/this_object` — 315B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/calls/this_object` — 315B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `this_player`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/this_player` — 170B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/this_player` — 170B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `this_user`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/this_user` — 592B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/this_user` — 592B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `throw`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/throw` — 480B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/calls/throw` — 480B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `time`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/time` — 271B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/time` — 271B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `time.c`
- `mud-references/deadsouls/ds3.8.2/lib/daemon/time.c` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/secure/sefun/time.c` — 2KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `time_expression`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/time_expression` — 508B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/internals/time_expression` — 508B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `to_float`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/to_float` — 277B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/numbers/to_float` — 277B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `to_int`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/to_int` — 522B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/floats/to_int` — 522B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `torch.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/Praxis/obj/misc/torch.c` — 614B
- `mud-references/deadsouls/ds3.8.2/lib/domains/Ylsrim/etc/torch.c` — 683B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/obj/torch.c` — 712B
- `mud-references/deadsouls/ds3.8.2/lib/domains/cave/obj/torch.c` — 615B
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/obj/torch.c` — 584B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/obj/torch.c` — 615B
- `mud-references/deadsouls/ds3.8.2/lib/lib/torch.c` — 1KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `touch.c`
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/Win32/touch.c` — 360B
- `mud-references/deadsouls/ds3.8.2/lib/lib/events/touch.c` — 3KB
- `mud-references/deadsouls/ds3.8.2/lib/verbs/items/touch.c` — 971B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `towel.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/armor/towel.c` — 479B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/armor/towel.c` — 515B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `trace`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/trace` — 771B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/internals/trace` — 771B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `traceprefix`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/traceprefix` — 409B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/internals/traceprefix` — 409B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `trainer.c`
- `mud-references/deadsouls/ds3.8.2/lib/lib/trainer.c` — 143B
- `mud-references/deadsouls/ds3.8.2/lib/obj/trainer.c` — 781B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `tree.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/chamber/tree.c` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/npc/tree.c` — 2KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `troll.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/npc/troll.c` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/npc/troll.c` — 1KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `tshirt.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/armor/tshirt.c` — 557B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/armor/tshirt.c` — 628B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `tunnel2.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/Praxis/mountains/tunnel2.c` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/room/tunnel2.c` — 2KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `turn.c`
- `mud-references/deadsouls/ds3.8.2/lib/lib/events/turn.c` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/verbs/items/turn.c` — 2KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `type.h`
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/include/type.h` — 336B
- `mud-references/deadsouls/ds3.8.2/lib/secure/include/type.h` — 273B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `typeof`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/typeof` — 451B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/general/typeof` — 451B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `types.c`
- `mud-references/deadsouls/ds3.8.2/lib/cmds/creators/types.c` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/daemon/types.c` — 4KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `undefinedp`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/undefinedp` — 680B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mixed/undefinedp` — 680B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `unique_array`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/unique_array` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/arrays/unique_array` — 1KB
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `unique_mapping`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/unique_mapping` — 463B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mappings/unique_mapping` — 463B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `update.c`
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/testsuite/command/update.c` — 348B
- `mud-references/deadsouls/ds3.8.2/lib/secure/cmds/creators/update.c` — 6KB
- `mud-references/deadsouls/ds3.8.2/lib/secure/daemon/update.c` — 496B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `upper_case`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/upper_case` — 354B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/strings/upper_case` — 354B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `uptime`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/uptime` — 290B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/uptime` — 290B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `userp`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/userp` — 234B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/userp` — 234B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `users`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/users` — 269B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/users` — 269B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `users.c`
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/testsuite/single/tests/efuns/users.c` — 125B
- `mud-references/deadsouls/ds3.8.2/lib/cmds/players/users.c` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/secure/sefun/users.c` — 802B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `valid_bind`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/valid_bind` — 416B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/valid_bind` — 416B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `valid_compile_to_c`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/valid_compile_to_c` — 418B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/valid_compile_to_c` — 418B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `valid_hide`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/valid_hide` — 642B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/valid_hide` — 642B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `valid_link`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/valid_link` — 450B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/valid_link` — 450B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `valid_object`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/valid_object` — 627B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/valid_object` — 627B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `valid_override`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/valid_override` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/valid_override` — 1KB
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `valid_read`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/valid_read` — 501B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/valid_read` — 501B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `valid_save_binary`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/valid_save_binary` — 570B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/valid_save_binary` — 570B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `valid_seteuid`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/valid_seteuid` — 503B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/valid_seteuid` — 503B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `valid_shadow`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/valid_shadow` — 585B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/valid_shadow` — 585B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `valid_socket`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/valid_socket` — 961B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/valid_socket` — 961B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `valid_write`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/valid_write` — 548B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/valid_write` — 548B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `values`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/values` — 466B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mappings/values` — 466B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `values.c`
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/testsuite/single/tests/efuns/values.c` — 176B
- `mud-references/deadsouls/ds3.8.2/lib/secure/sefun/values.c` — 576B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `variables`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/variables` — 800B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/variables` — 800B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `vendor.c`
- `mud-references/deadsouls/ds3.8.2/lib/lib/std/vendor.c` — 18KB
- `mud-references/deadsouls/ds3.8.2/lib/obj/vendor.c` — 548B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `vest.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/armor/vest.c` — 563B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/armor/vest.c` — 617B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `vibro_blade.lpc`
- `lib/objects/weapons/vibro_blade.lpc` — 750B
- `lib/single/vibro_blade.lpc` — 981B
**Recommendation:** Keep the copy in `lib/` and remove duplicates elsewhere.

### `virtual.h`
- `mud-references/deadsouls/ds3.8.2/lib/lib/include/virtual.h` — 111B
- `mud-references/deadsouls/ds3.8.2/lib/secure/include/virtual.h` — 378B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `virtualp`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/virtualp` — 374B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/objects/virtualp` — 374B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `void.c`
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/testsuite/single/void.c` — 17B
- `mud-references/deadsouls/ds3.8.2/lib/domains/Praxis/void.c` — 231B
- `mud-references/deadsouls/ds3.8.2/lib/domains/Ylsrim/adm/void.c` — 412B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/room/void.c` — 463B
- `mud-references/deadsouls/ds3.8.2/lib/domains/cave/room/void.c` — 299B
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/room/void.c` — 282B
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/virtual/void.c` — 366B
- `mud-references/deadsouls/ds3.8.2/lib/domains/learning/room/void.c` — 282B
- `mud-references/deadsouls/ds3.8.2/lib/domains/learning/virtual/void.c` — 413B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/room/void.c` — 282B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/virtual/void.c` — 366B
- `mud-references/deadsouls/ds3.8.2/lib/std/void.c` — 282B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `void.lpc`
- `lib/domains/forest/rooms/void.lpc` — 0B
- `lib/domains/start/room/void.lpc` — 531B
**Recommendation:** Keep the copy in `lib/` and remove duplicates elsewhere.

### `wall.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/Praxis/wall.c` — 3KB
- `mud-references/deadsouls/ds3.8.2/lib/domains/Ylsrim/etc/wall.c` — 647B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/obj/wall.c` — 2KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `watch.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/obj/watch.c` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/obj/watch.c` — 3KB
- `mud-references/deadsouls/ds3.8.2/lib/realms/template/area/obj/watch.c` — 3KB
- `mud-references/deadsouls/ds3.8.2/lib/realms/thurtea/area/obj/watch.c` — 3KB
- `mud-references/deadsouls/ds3.8.2/lib/secure/cmds/admins/watch.c` — 1KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `water.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/meals/water.c` — 536B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/meals/water.c` — 536B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `weapon.c`
- `mud-references/deadsouls/ds3.8.2/lib/lib/comp/weapon.c` — 5KB
- `mud-references/deadsouls/ds3.8.2/lib/obj/weapon.c` — 470B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `wear.c`
- `mud-references/deadsouls/ds3.8.2/lib/lib/events/wear.c` — 955B
- `mud-references/deadsouls/ds3.8.2/lib/verbs/items/wear.c` — 2KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `wget.c`
- `mud-references/deadsouls/ds3.8.2/lib/secure/cmds/creators/wget.c` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/secure/daemon/wget.c` — 4KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `whip.c`
- `mud-references/deadsouls/ds3.8.2/lib/obj/whip.c` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/powers/spells/whip.c` — 2KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `who.c`
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/testsuite/command/who.c` — 407B
- `mud-references/deadsouls/ds3.8.2/lib/cmds/players/who.c` — 7KB
- `mud-references/deadsouls/ds3.8.2/lib/daemon/services/who.c` — 3KB
- `mud-references/deadsouls/ds3.8.2/lib/www/cgi/who.c` — 2KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `wield.c`
- `mud-references/deadsouls/ds3.8.2/lib/lib/events/wield.c` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/verbs/items/wield.c` — 4KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `wim.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/npc/wim.c` — 319B
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/npc/quarantine/wim.c` — 355B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `window_size`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/interactive/window_size` — 317B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/window_size` — 317B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `wins`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charles/bak2/bak1/wins` — 3B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charles/bak2/wins` — 3B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charles/wins` — 5B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charly/bak/wins` — 5B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charly/wins` — 5B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `wiz_hall.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/cave/room/wiz_hall.c` — 557B
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/room/wiz_hall.c` — 3KB
- `mud-references/deadsouls/ds3.8.2/lib/domains/learning/room/wiz_hall.c` — 540B
- `mud-references/deadsouls/ds3.8.2/lib/std/wiz_hall.c` — 540B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `wizard_hat.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/armor/wizard_hat.c` — 809B
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/armor/wizard_hat.c` — 809B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/armor/wizard_hat.c` — 682B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `wizardp`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/wizardp` — 334B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/wizardp` — 334B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `wiztool.lpc`
- `lib/cmds/admin/wiztool.lpc` — 2KB
- `lib/std/wiztool.lpc` — 17KB
**Recommendation:** Keep the copy in `lib/` and remove duplicates elsewhere.

### `workboot_l.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/armor/workboot_l.c` — 660B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/armor/workboot_l.c` — 660B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `workboot_r.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/armor/workboot_r.c` — 663B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/armor/workboot_r.c` — 663B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `workglove_l.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/armor/workglove_l.c` — 737B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/armor/workglove_l.c` — 737B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `workglove_r.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/armor/workglove_r.c` — 749B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/armor/workglove_r.c` — 749B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `workroom.bak`
- `mud-references/deadsouls/ds3.8.2/lib/realms/template/workroom.bak` — 3KB
- `mud-references/deadsouls/ds3.8.2/lib/realms/thurtea/workroom.bak` — 4KB
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `workroom.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/creator/workroom.c` — 530B
- `mud-references/deadsouls/ds3.8.2/lib/realms/template/workroom.c` — 4KB
- `mud-references/deadsouls/ds3.8.2/lib/realms/thurtea/workroom.c` — 4KB
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `workroom.orig`
- `mud-references/deadsouls/ds3.8.2/lib/realms/template/bak/workroom.orig` — 4KB
- `mud-references/deadsouls/ds3.8.2/lib/realms/thurtea/bak/workroom.orig` — 4KB
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `worn_storage.c`
- `mud-references/deadsouls/ds3.8.2/lib/lib/std/worn_storage.c` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/obj/worn_storage.c` — 616B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

### `write`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/write` — 307B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/write` — 307B
- `mud-references/deadsouls/ds3.8.2/lib/doc/sefun/write` — 482B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `write_buffer`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/write_buffer` — 594B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/buffers/write_buffer` — 594B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `write_bytes`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/write_bytes` — 306B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/filesystem/write_bytes` — 306B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `write_file`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/write_file` — 288B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/filesystem/write_file` — 288B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `write_prompt`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/interactive/write_prompt` — 366B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/write_prompt` — 366B
**Recommendation:** Decide canonical directory (e.g., `src/`, `lib/`, `scripts/`).

### `zoe.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/npc/zoe.c` — 941B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/npc/zoe.c` — 1013B
**Recommendation:** Keep the copy in `src/` and remove duplicates elsewhere (or symlink).

## Section 2: Files with Identical Content (by MD5 hash)

### Hash `0029ea3ecf96a794c934bfe183c6477c`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/set_this_player` — 487B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/set_this_player` — 487B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/set_this_player`; choose appropriate directory per project conventions.

### Hash `002ea600c8aa953b0c249ea52657d2ef`
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/virtual/void.c` — 366B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/virtual/void.c` — 366B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/domains/default/virtual/void.c` (belongs in `src/`); move others to backups or remove.

### Hash `00ac3e5f29cd5b77785b12ab8a60764b`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/fetch_variable` — 424B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/general/fetch_variable` — 424B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/fetch_variable`; choose appropriate directory per project conventions.

### Hash `00ba39b12290ad6a2b852ad31613d6fd`
- `mud-references/deadsouls/ds3.8.2/lib/realms/template/area/weap/sword.c` — 469B
- `mud-references/deadsouls/ds3.8.2/lib/realms/thurtea/area/weap/sword.c` — 469B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/realms/template/area/weap/sword.c` (belongs in `src/`); move others to backups or remove.

### Hash `0166ce5796f9daae03870500456e8788`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/parse_command_id_list` — 340B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/parsing/parse_command_id_list` — 340B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/applies/parse_command_id_list`; choose appropriate directory per project conventions.

### Hash `016bcdbb1b2a23e006d106a2768e9d1b`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/rusage` — 964B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/internals/rusage` — 964B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/rusage`; choose appropriate directory per project conventions.

### Hash `01742bfa0da3c365c92fba7eec80b534`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/AddSacrificeType` — 421B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/chapel/AddSacrificeType` — 421B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/AddSacrificeType`; choose appropriate directory per project conventions.

### Hash `017f3f366f78a52eb7e72ba9624412c6`
- `mud-references/deadsouls/ds3.8.2/lib/doc/bguide/chapter04` — 6KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/manual/chapter35` — 6KB
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/bguide/chapter04`; choose appropriate directory per project conventions.

### Hash `01b6627beb554a0f1ebd3c8fd6fa6e13`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/find_living` — 614B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mudlib/find_living` — 614B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/find_living`; choose appropriate directory per project conventions.

### Hash `022d2dc45e999011e0b952221381a1d6`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/parse_command_all_word` — 278B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/parse_command_all_word` — 278B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/applies/parse_command_all_word`; choose appropriate directory per project conventions.

### Hash `02f5760ffe44e1bfb8d48a8f51f0dc04`
- `mud-references/deadsouls/ds3.8.2/lib/www/lpmuds/print.css` — 60B
- `mud-references/deadsouls/ds3.8.2/lib/www/print.css` — 60B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/www/print.css`; choose appropriate directory per project conventions.

### Hash `02f8a5a0aba82a3b8bc0c9c33af64700`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/socket_error` — 465B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/sockets/socket_error` — 465B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/socket_error`; choose appropriate directory per project conventions.

### Hash `041dcb1134aba0f55e22176d271ad684`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetPacifist` — 282B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/SetPacifist` — 282B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetPacifist`; choose appropriate directory per project conventions.

### Hash `0469c7c62828a27e402815a8b8e1e1b6`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/classp` — 190B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mixed/classp` — 190B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/classp`; choose appropriate directory per project conventions.

### Hash `049829c0b3e7513c1944d89c297fac80`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventRetire` — 470B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/clan/eventRetire` — 470B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventRetire`; choose appropriate directory per project conventions.

### Hash `04aedaed341a76b500a5b7862a42fa59`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/terminal_colour` — 625B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/strings/terminal_colour` — 625B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/terminal_colour`; choose appropriate directory per project conventions.

### Hash `054a19d5d3e613922b76dbbc62ae2f2c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/cave/weap/dagger.c` — 520B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/weap/dagger.c` — 520B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/domains/town/weap/dagger.c` (belongs in `src/`); move others to backups or remove.

### Hash `0556764706425c4bb927fd97bb597d7c`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/set_malloc_mask` — 520B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/internals/set_malloc_mask` — 520B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/set_malloc_mask`; choose appropriate directory per project conventions.

### Hash `05c0a199e1c60ee25436b15295b4b730`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/member_array` — 503B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/arrays/member_array` — 503B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/member_array`; choose appropriate directory per project conventions.

### Hash `06b0bc6004d8a2f90c41b02707aa647e`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/AddCaffeine` — 355B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/AddCaffeine` — 355B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/AddCaffeine`; choose appropriate directory per project conventions.

### Hash `072c05af6ac9cbed215813e7dca44f92`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/enable_commands` — 531B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/enable_commands` — 531B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/enable_commands`; choose appropriate directory per project conventions.

### Hash `079d4b352913c67836e8f1133b2c0140`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/UnrestrictChannel` — 341B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/chat/UnrestrictChannel` — 341B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/UnrestrictChannel`; choose appropriate directory per project conventions.

### Hash `08070d70247a6b96d7e52b122e3f4a86`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/dump_socket_status` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/internals/dump_socket_status` — 2KB
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/dump_socket_status`; choose appropriate directory per project conventions.

### Hash `083c55d5b12ce9e8a78e2497fc29025f`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/eval_cost` — 305B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/eval_cost` — 305B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/eval_cost`; choose appropriate directory per project conventions.

### Hash `09022fa879e3b7cdf93783d250a7a985`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/geteuid` — 625B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mudlib/geteuid` — 625B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/geteuid`; choose appropriate directory per project conventions.

### Hash `095559e6e798a20c1a09e5529f3c842d`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/replace_program` — 901B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/replace_program` — 901B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/replace_program`; choose appropriate directory per project conventions.

### Hash `0993919fa52f8a01e15c36512a22d4fd`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/set_privs` — 371B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mudlib/set_privs` — 371B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/set_privs`; choose appropriate directory per project conventions.

### Hash `0994fce22ae581bc3692cb4923f6cfdd`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetCanBite` — 329B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetCanBite` — 329B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetCanBite`; choose appropriate directory per project conventions.

### Hash `0a0b788edc265e6d2e7286a4f4cc7df1`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/rename` — 207B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/filesystem/rename` — 207B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/rename`; choose appropriate directory per project conventions.

### Hash `0aa1e98a749a73b12b5e7fe2b5862cc8`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetSacrificeType` — 418B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/chapel/GetSacrificeType` — 418B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetSacrificeType`; choose appropriate directory per project conventions.

### Hash `0ab06b7a01c2ba73c98050374a84607a`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/obj/backpack_civilian.c` — 722B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/obj/backpack_empty.c` — 722B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/domains/campus/obj/backpack_empty.c` (belongs in `src/`); move others to backups or remove.

### Hash `0ab77a81206a2d87157a3a383792ce62`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetEquippedLimbs` — 326B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetEquippedLimbs` — 326B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetEquippedLimbs`; choose appropriate directory per project conventions.

### Hash `0abbb4a81449a94b210e14386ac9fd7e`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/HandleTeller` — 557B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/bank/HandleTeller` — 557B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/HandleTeller`; choose appropriate directory per project conventions.

### Hash `0b780650efd44f15097e765582e4283d`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetBonusDuration` — 310B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/bonus/GetBonusDuration` — 310B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetBonusDuration`; choose appropriate directory per project conventions.

### Hash `0cd7abce8c03de188d12e615135c89fd`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/pluralize` — 297B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/strings/pluralize` — 297B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/pluralize`; choose appropriate directory per project conventions.

### Hash `0d2973e79f1606c6b73eb227a4f51f05`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventCompleteHeal` — 463B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/eventCompleteHeal` — 463B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventCompleteHeal`; choose appropriate directory per project conventions.

### Hash `0d44804e2814a7e5df573fff49922f6d`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/malloc_status` — 488B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/internals/malloc_status` — 488B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/malloc_status`; choose appropriate directory per project conventions.

### Hash `0da713f5e857743a9d98d6e56b4e0d64`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/function_owner` — 266B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/functions/function_owner` — 266B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/function_owner`; choose appropriate directory per project conventions.

### Hash `0e0211d371ae65accf7e5b22eb27927b`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetQuestPoints` — 273B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetQuestPoints` — 273B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetQuestPoints`; choose appropriate directory per project conventions.

### Hash `0e051211ce3e2bffb432c454c0a35032`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/debug_message` — 273B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/debug_message` — 273B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/debug_message`; choose appropriate directory per project conventions.

### Hash `0e6f6a3927f9e1f745a50cc164985035`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/object_name` — 377B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/object_name` — 377B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/applies/object_name`; choose appropriate directory per project conventions.

### Hash `0ebd4ea7aa9d265c88b8a736fedee996`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/find_player` — 304B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/find_player` — 304B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/find_player`; choose appropriate directory per project conventions.

### Hash `0ef037f8ab0e89bafb0a168b8838923c`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetMissingLimbParent` — 356B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetMissingLimbParent` — 356B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetMissingLimbParent`; choose appropriate directory per project conventions.

### Hash `0f429bf05c1ab38d3b96206d0cb1545c`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/interactive/process_input` — 851B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/process_input` — 851B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/applies/process_input`; choose appropriate directory per project conventions.

### Hash `0f927e04ea81f3c5242f909577aac98e`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/disable_wizard` — 263B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/disable_wizard` — 263B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/disable_wizard`; choose appropriate directory per project conventions.

### Hash `0ff711915b27113d81b558db8afd40db`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetClan` — 243B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/classes/GetClan` — 243B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetClan`; choose appropriate directory per project conventions.

### Hash `101f7ff1123631fd6285defc244c1f14`
- `mud-references/deadsouls/ds3.8.2/lib/realms/template/area/obj/table.c` — 591B
- `mud-references/deadsouls/ds3.8.2/lib/realms/thurtea/area/obj/table.c` — 591B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/realms/template/area/obj/table.c` (belongs in `src/`); move others to backups or remove.

### Hash `10512034a5ae4f5a4fc056d4b02326c9`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/valid_shadow` — 585B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/valid_shadow` — 585B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/applies/valid_shadow`; choose appropriate directory per project conventions.

### Hash `10b45fa0bf3f82c9490e8987cd07ef3c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/armor/workboot_l.c` — 660B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/armor/workboot_l.c` — 660B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/domains/campus/armor/workboot_l.c` (belongs in `src/`); move others to backups or remove.

### Hash `115815f41c75ef0d6c206007317b8b0f`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/mkdir` — 227B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/filesystem/mkdir` — 227B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/mkdir`; choose appropriate directory per project conventions.

### Hash `1180f68ee07c18fd0115e29b95759d38`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/find_call_out` — 425B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/find_call_out` — 425B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/find_call_out`; choose appropriate directory per project conventions.

### Hash `11a88309007b415e4dba00f2b87e0448`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventCharge` — 278B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/battery/eventCharge` — 278B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventCharge`; choose appropriate directory per project conventions.

### Hash `11f3893aeb55cceb4e0d5b32468bf6b2`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/query_ip_number` — 299B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/query_ip_number` — 299B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/query_ip_number`; choose appropriate directory per project conventions.

### Hash `12e649c329b16538a066d1ffd7d8271a`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/compile_object` — 1008B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/compile_object` — 1008B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/applies/compile_object`; choose appropriate directory per project conventions.

### Hash `12fbf3c6adf15c7cb3d13c0045397154`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/interactive/write_prompt` — 366B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/write_prompt` — 366B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/applies/write_prompt`; choose appropriate directory per project conventions.

### Hash `1304aadb971b56e1b1df49f73771484e`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventCompareLimbs` — 333B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/eventCompareLimbs` — 333B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventCompareLimbs`; choose appropriate directory per project conventions.

### Hash `1348337c591436d8a4ac6fb24f3cc059`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/reload_object` — 517B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/objects/reload_object` — 517B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/reload_object`; choose appropriate directory per project conventions.

### Hash `138174b77dff31a382f0723bf5b060d1`
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/weap/sharpsword.c` — 495B
- `mud-references/deadsouls/ds3.8.2/lib/obj/sword.c` — 495B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/obj/sword.c` (belongs in `src/`); move others to backups or remove.

### Hash `14050ff0ca88bfd60d0cc1d1f49e9670`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/stringp` — 211B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mixed/stringp` — 211B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/stringp`; choose appropriate directory per project conventions.

### Hash `145931bd6760ff95d068d9ccf4432f4d`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/network_stats` — 3B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/query_num` — 3B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/numbers/query_num` — 3B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/sockets/network_stats` — 3B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/query_num`; choose appropriate directory per project conventions.

### Hash `14c036adedc930610cee0434600a7cc8`
- `mud-references/deadsouls/ds3.8.2/lib/verbs/players/include/,vote.h` — 141B
- `mud-references/deadsouls/ds3.8.2/lib/verbs/players/include/vote.h` — 141B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/verbs/players/include/,vote.h` (belongs in `src/`); move others to backups or remove.

### Hash `153a3871df3059404fda5604d5dcd6d4`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/shutdown` — 951B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/shutdown` — 951B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/shutdown`; choose appropriate directory per project conventions.

### Hash `15708aa18aa501daeb41a16dcb5ccace`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetDrainRate` — 328B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/battery/GetDrainRate` — 328B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetDrainRate`; choose appropriate directory per project conventions.

### Hash `1587c2ffa3ba4315a618ab53aa6e610a`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/bind` — 521B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/functions/bind` — 521B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/bind`; choose appropriate directory per project conventions.

### Hash `15d4c2c9103231c3b3fdda7adbfb9bd3`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventBring` — 390B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/clan/eventBring` — 390B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventBring`; choose appropriate directory per project conventions.

### Hash `15f3802bde7739158620835db34223ee`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/error_handler` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/error_handler` — 1KB
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/applies/error_handler`; choose appropriate directory per project conventions.

### Hash `1601b6f8dbd9ce221129aa923f691dea`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetBodyComposition` — 309B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetBodyComposition` — 309B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetBodyComposition`; choose appropriate directory per project conventions.

### Hash `164edd8996425dbf0acf44daa55c4bec`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/intp` — 221B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mixed/intp` — 221B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/intp`; choose appropriate directory per project conventions.

### Hash `17aa07d030809f80787359c3d0fd4b69`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/exp` — 240B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/floats/exp` — 240B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/floats/exp`; choose appropriate directory per project conventions.

### Hash `17aa5ad61073d41f91b2a03ee7248166`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/deep_inherit_list` — 300B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/deep_inherit_list` — 300B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/deep_inherit_list`; choose appropriate directory per project conventions.

### Hash `17f1fb642337d709679477b320cf7765`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/AddChannel` — 320B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/chat/AddChannel` — 320B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/AddChannel`; choose appropriate directory per project conventions.

### Hash `18235e22946e8d780a173ebab1b589d5`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetLimbs` — 243B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetLimbs` — 243B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetLimbs`; choose appropriate directory per project conventions.

### Hash `1885ebbd08c59dead9559601cc3c5392`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/author_file` — 665B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/author_file` — 665B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/applies/author_file`; choose appropriate directory per project conventions.

### Hash `19351e197ff2d09ed246d77b8dd75e60`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/sprintf` — 3KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/strings/sprintf` — 3KB
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/sprintf`; choose appropriate directory per project conventions.

### Hash `1956e9167d0abfa7a6244aa75f472483`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/crypt` — 311B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/strings/crypt` — 311B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/crypt`; choose appropriate directory per project conventions.

### Hash `1abf07ecbe628fb4444e013f47d072f9`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetCaliber` — 410B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/clip/GetCaliber` — 410B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/firearm/GetCaliber` — 410B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/round/GetCaliber` — 410B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/shell/GetCaliber` — 410B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetCaliber`; choose appropriate directory per project conventions.

### Hash `1ad2a9eb466c45a837f86958d3458684`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/virtualp` — 374B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/objects/virtualp` — 374B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/virtualp`; choose appropriate directory per project conventions.

### Hash `1aff6136cb1e65a60de6cc943c5e11ba`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/clonep` — 697B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/objects/clonep` — 697B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/clonep`; choose appropriate directory per project conventions.

### Hash `1b4ede06f0de17d1792993b0e36ff7e5`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetStaminaPoints` — 293B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetStaminaPoints` — 293B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetStaminaPoints`; choose appropriate directory per project conventions.

### Hash `1b617e1fa2331d0749fa16fd939cc186`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/map_array` — 286B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/arrays/map_array` — 286B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/map_array`; choose appropriate directory per project conventions.

### Hash `1babc3d85f495ff597a72c9bcc83faac`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/variables` — 800B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/variables` — 800B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/variables`; choose appropriate directory per project conventions.

### Hash `1bc7922dd2c7fdf678f88dcf98ce62b5`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/this_user` — 592B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/this_user` — 592B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/this_user`; choose appropriate directory per project conventions.

### Hash `1bee5dd605a1228a506e552cb2be368b`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/remove_shadow` — 423B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/calls/remove_shadow` — 423B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/remove_shadow`; choose appropriate directory per project conventions.

### Hash `1c3d7344960126b2d92e90ccd24b7908`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/say` — 712B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/say` — 712B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/say`; choose appropriate directory per project conventions.

### Hash `1ca6626b6e004bbce7097ded8028ae2d`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/store_variable` — 475B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/general/store_variable` — 475B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/store_variable`; choose appropriate directory per project conventions.

### Hash `1d07c3caccc2622365180c72859af0f9`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/obj/pin.c` — 393B
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/obj/pin.c` — 393B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/domains/campus/obj/pin.c` (belongs in `src/`); move others to backups or remove.

### Hash `1d38830aa31b31f0e3513b6db56ba2e1`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/socket_create` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/sockets/socket_create` — 2KB
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/socket_create`; choose appropriate directory per project conventions.

### Hash `1d6f0cbff7c090c4a1c81936e0283720`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/armor/bandanna.c` — 598B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/armor/bandanna.c` — 598B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/domains/campus/armor/bandanna.c` (belongs in `src/`); move others to backups or remove.

### Hash `200852ab64fab152ea824cfd8e2cee44`
- `mud-references/deadsouls/ds3.8.2/lib/realms/template/area/obj/pitcher.c` — 651B
- `mud-references/deadsouls/ds3.8.2/lib/realms/thurtea/area/obj/pitcher.c` — 651B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/realms/template/area/obj/pitcher.c` (belongs in `src/`); move others to backups or remove.

### Hash `205ac0ed359d7e28a1f614ebd4c00b7d`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetAmmoType` — 445B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/clip/SetAmmoType` — 445B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/firearm/SetAmmoType` — 445B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/round/SetAmmoType` — 445B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/shell/SetAmmoType` — 445B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetAmmoType`; choose appropriate directory per project conventions.

### Hash `20f908a1eaf53253612238f0f9428d38`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/command` — 567B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/command` — 567B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/command`; choose appropriate directory per project conventions.

### Hash `2184ba98991940122af98714008bb5c1`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetFirearmType` — 432B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/clip/GetFirearmType` — 432B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/firearm/GetFirearmType` — 432B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/round/GetFirearmType` — 432B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/shell/GetFirearmType` — 432B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetFirearmType`; choose appropriate directory per project conventions.

### Hash `21c037c4b6ce0144cc912f46b69e7244`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/call_out_info` — 792B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/call_out_info` — 792B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/call_out_info`; choose appropriate directory per project conventions.

### Hash `21f811a0b7483498b244d56ebdf1bbbf`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetClanObject` — 323B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/clan/SetClanObject` — 323B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetClanObject`; choose appropriate directory per project conventions.

### Hash `224fcf36b8d096a9aebd142c3e1eb59f`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/unique_array` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/arrays/unique_array` — 1KB
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/unique_array`; choose appropriate directory per project conventions.

### Hash `225a6bfa0707cb346762a48b7e4bedbe`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/this_interactive` — 392B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/this_interactive` — 392B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/this_interactive`; choose appropriate directory per project conventions.

### Hash `2278e6b5f046970bc85c941ca3614f33`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/interactive/receive_snoop` — 458B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/receive_snoop` — 458B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/applies/receive_snoop`; choose appropriate directory per project conventions.

### Hash `229c9719e99e89ddf2805079cf42aa4d`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/preload` — 533B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/preload` — 533B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/applies/preload`; choose appropriate directory per project conventions.

### Hash `22bf58f81d836c87ce16b4305f7e1ae4`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/livings` — 369B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mudlib/livings` — 369B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/livings`; choose appropriate directory per project conventions.

### Hash `23093348eb20b74a671c08723d9ed82f`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetTorso` — 320B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetTorso` — 320B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetTorso`; choose appropriate directory per project conventions.

### Hash `241b07c2c34428e4ab21a082c2d25d57`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/valid_save_binary` — 570B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/valid_save_binary` — 570B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/applies/valid_save_binary`; choose appropriate directory per project conventions.

### Hash `2420c17dd6726c21f30b736652e6e393`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/replace_string` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/strings/replace_string` — 2KB
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/replace_string`; choose appropriate directory per project conventions.

### Hash `249170941920b0c1560ef743c9910fc7`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/RemoveLimb` — 486B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/RemoveLimb` — 486B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/RemoveLimb`; choose appropriate directory per project conventions.

### Hash `24a213a84da19b4affca838b011a4c6a`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetMinHeat` — 292B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/burn/GetMinHeat` — 292B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetMinHeat`; choose appropriate directory per project conventions.

### Hash `24f5dd6ae72634f4405de1700204a06d`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/meals/water.c` — 536B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/meals/water.c` — 536B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/domains/campus/meals/water.c` (belongs in `src/`); move others to backups or remove.

### Hash `24feceff80506722570644cc9a176795`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/mapp` — 189B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mixed/mapp` — 189B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/mapp`; choose appropriate directory per project conventions.

### Hash `254e9d81a8ae046fd59321f9ec08951e`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetRechargeable` — 296B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/battery/SetRechargeable` — 296B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetRechargeable`; choose appropriate directory per project conventions.

### Hash `256662b6e05a3b70d18dad2ba8ddec8d`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/parse_command_prepos_list` — 309B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/parse_command_prepos_list` — 309B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/applies/parse_command_prepos_list`; choose appropriate directory per project conventions.

### Hash `257aefdd0ab6f4285bd9f5a87f2ad71c`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/AddHP` — 268B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/AddHP` — 268B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/AddHP`; choose appropriate directory per project conventions.

### Hash `257b012181e4c5ec6f67f6fe6ab0ba9c`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/query_heart_beat` — 401B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/objects/query_heart_beat` — 401B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/query_heart_beat`; choose appropriate directory per project conventions.

### Hash `257c6b8b3eb13b31dcddbc33b72f105d`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/traceprefix` — 409B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/internals/traceprefix` — 409B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/traceprefix`; choose appropriate directory per project conventions.

### Hash `25a01a236f5a343e73c8ac18388390d2`
- `mud-references/deadsouls/ds3.8.2/lib/doc/bguide/chapter02` — 4KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/manual/chapter33` — 4KB
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/bguide/chapter02`; choose appropriate directory per project conventions.

### Hash `2626cfefaae832ebe60c1ac9b0a50822`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/domain_stats` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mudlib/domain_stats` — 2KB
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/domain_stats`; choose appropriate directory per project conventions.

### Hash `2737db8b9a84bf993845ff3356aec872`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/sin` — 291B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/floats/sin` — 291B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/floats/sin`; choose appropriate directory per project conventions.

### Hash `2755acdff5a5466bce9b47f79a0a72e6`
- `mud-references/deadsouls/ds3.8.2/lib/domains/Ylsrim/npc/traveler.c` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/domains/Ylsrim/npc/traveller.c` — 2KB
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/domains/Ylsrim/npc/traveller.c` (belongs in `src/`); move others to backups or remove.

### Hash `275b1a329f7995717485a9f1e8c71b5b`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/shout` — 272B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/shout` — 272B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/shout`; choose appropriate directory per project conventions.

### Hash `27da895e75e10d2000aa1f6877071394`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/arrayp` — 156B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mixed/arrayp` — 156B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/arrayp`; choose appropriate directory per project conventions.

### Hash `2835d49346cd833f754f3ee3bb8bdbfa`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/chat_command` — 411B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/chat/chat_command` — 411B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/chat_command`; choose appropriate directory per project conventions.

### Hash `28c44aeb148b341f3cf6f436c8f3f8b9`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/file_name` — 650B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/objects/file_name` — 650B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/file_name`; choose appropriate directory per project conventions.

### Hash `28f6b236f0280e6dcf14f2059831f2f4`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/call_stack` — 532B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/calls/call_stack` — 532B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/call_stack`; choose appropriate directory per project conventions.

### Hash `28fc8069c2382b0928bea0786609b535`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/snoop` — 805B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/snoop` — 805B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/snoop`; choose appropriate directory per project conventions.

### Hash `293000c66008d75648792d41ee0d1be5`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetClanSkill` — 272B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/clan/SetClanSkill` — 272B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetClanSkill`; choose appropriate directory per project conventions.

### Hash `294523784610c351e350a9e08ec4d0ba`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventDrain` — 281B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/battery/eventDrain` — 281B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventDrain`; choose appropriate directory per project conventions.

### Hash `2965c0c943642119ce5a3abdb3b5e08d`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetWorn` — 588B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetWorn` — 588B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/equip/GetWorn` — 588B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetWorn`; choose appropriate directory per project conventions.

### Hash `29aafd4c09789eba425afbf4ba22d896`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/query_privs` — 444B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mudlib/query_privs` — 444B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/query_privs`; choose appropriate directory per project conventions.

### Hash `2a27dfaa77426ab2a9e71d8d99d74d69`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/time_expression` — 508B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/internals/time_expression` — 508B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/time_expression`; choose appropriate directory per project conventions.

### Hash `2a9eac7d836be82b9ec0464956c5b620`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventRemoveItem` — 347B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/eventRemoveItem` — 347B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventRemoveItem`; choose appropriate directory per project conventions.

### Hash `2c84a06f7748572d4f53930cebd6e2bf`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/set_light` — 608B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mudlib/set_light` — 608B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/set_light`; choose appropriate directory per project conventions.

### Hash `2ca2019d73f1e7b2c78db648d44a0674`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/AddMagicPoints` — 299B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/AddMagicPoints` — 299B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/AddMagicPoints`; choose appropriate directory per project conventions.

### Hash `2cbdde98d080dd2bfc48603bdafeb23d`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/stat` — 514B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/filesystem/stat` — 514B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/stat`; choose appropriate directory per project conventions.

### Hash `2cf5c26daecff4174333ac699d87c4e5`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetAllowSacrifice` — 388B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/chapel/SetAllowSacrifice` — 388B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetAllowSacrifice`; choose appropriate directory per project conventions.

### Hash `2d7356df06d0aa7b7969d07d9f1a314d`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetNoChanColors` — 345B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/chat/SetNoChanColors` — 345B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetNoChanColors`; choose appropriate directory per project conventions.

### Hash `2d9220dd2390368d4cd607d667d23d48`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/interactive/terminal_type` — 395B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/terminal_type` — 395B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/applies/terminal_type`; choose appropriate directory per project conventions.

### Hash `2e4122accc0898a5d115b01fa6c9b0f2`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/to_float` — 277B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/numbers/to_float` — 277B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/to_float`; choose appropriate directory per project conventions.

### Hash `2e641e1b84165d5736fc3fd5b68dd536`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/valid_socket` — 961B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/valid_socket` — 961B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/applies/valid_socket`; choose appropriate directory per project conventions.

### Hash `2e74d12ac722b75f98526fc2c273575d`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/this_object` — 315B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/calls/this_object` — 315B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/this_object`; choose appropriate directory per project conventions.

### Hash `2f3b3f50512afcfd485bc46a399aedea`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charles/blue_wins` — 5B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charles/red_wins` — 5B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charles/red_wins`; choose appropriate directory per project conventions.

### Hash `2f507dd3eb89c89d40ed8ce64117bda2`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/map` — 708B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/general/map` — 708B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/map`; choose appropriate directory per project conventions.

### Hash `2f6f69776d02207556a483da03c244a1`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/heart_beat_info` — 316B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/objects/heart_beat_info` — 316B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/heart_beat_info`; choose appropriate directory per project conventions.

### Hash `2f953c0da347fba868e2559dda37c93f`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetCaliber` — 468B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/clip/SetCaliber` — 468B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/firearm/SetCaliber` — 468B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/round/SetCaliber` — 468B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/shell/SetCaliber` — 468B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetCaliber`; choose appropriate directory per project conventions.

### Hash `2f9d6dde4dbf9c376306b74b83424d7c`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetCharge` — 318B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/battery/GetCharge` — 318B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetCharge`; choose appropriate directory per project conventions.

### Hash `2fbd3c8add1c1348d1cd27857ca4ef6e`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/allocate_mapping` — 798B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mappings/allocate_mapping` — 798B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/allocate_mapping`; choose appropriate directory per project conventions.

### Hash `305013fe02503b573e16387230b5aa64`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetSkills` — 480B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/bonus/SetSkills` — 480B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/potion/SetSkills` — 480B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/spell/SetSkills` — 480B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetSkills`; choose appropriate directory per project conventions.

### Hash `3061e95f7217be6b6a34e54dd2b577b5`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/valid_link` — 450B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/valid_link` — 450B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/applies/valid_link`; choose appropriate directory per project conventions.

### Hash `32ec25b3ec4d0114e1533aba6193d40a`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/map_mapping` — 671B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mappings/map_mapping` — 671B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/map_mapping`; choose appropriate directory per project conventions.

### Hash `334aa5a92fae0f3b4d06513d6a175e95`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetDeathEvents` — 459B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetDeathEvents` — 459B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetDeathEvents`; choose appropriate directory per project conventions.

### Hash `33ca398fc827650781cd8f18a3a30cdd`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/trace` — 771B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/internals/trace` — 771B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/trace`; choose appropriate directory per project conventions.

### Hash `33d7de270dff79aac68e0346a2721663`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/ed_start` — 581B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/ed_start` — 581B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/ed_start`; choose appropriate directory per project conventions.

### Hash `344ed8657e481cb00706b576a86fb212`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetBaseStatLevel` — 434B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/classes/GetBaseStatLevel` — 434B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/combat/GetBaseStatLevel` — 434B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/genetics/GetBaseStatLevel` — 434B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetBaseStatLevel`; choose appropriate directory per project conventions.

### Hash `350caa1e8557f7722ff783754ad8576d`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetBurnRate` — 261B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/burn/GetBurnRate` — 261B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/lamp/GetBurnRate` — 261B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetBurnRate`; choose appropriate directory per project conventions.

### Hash `358f84848ec008abd07bf43eca05aa71`
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/malloc.c` — 271B
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/sysmalloc.c` — 271B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/malloc.c` (belongs in `src/`); move others to backups or remove.

### Hash `35a2b437154835f6dd80a9f783552ed5`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/write_bytes` — 306B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/filesystem/write_bytes` — 306B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/write_bytes`; choose appropriate directory per project conventions.

### Hash `360f5e70accf3bcf9d679f9cfa836677`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetExtraChannels` — 437B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/SetExtraChannels` — 437B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetExtraChannels`; choose appropriate directory per project conventions.

### Hash `363fbae8d5ddde32ccc95987e577c477`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/objectp` — 195B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mixed/objectp` — 195B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/objectp`; choose appropriate directory per project conventions.

### Hash `365d8dc7d19405af313ffed3e388d3aa`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/function_profile` — 847B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/function_profile` — 847B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/function_profile`; choose appropriate directory per project conventions.

### Hash `369d7b7a6b0476b6d2b5fd7b83242cd3`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/returnChannels` — 338B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/chat/returnChannels` — 338B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/returnChannels`; choose appropriate directory per project conventions.

### Hash `37016863a73ec42723e14c5b7ecfcc46`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetFingers` — 427B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/armor/GetFingers` — 427B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetFingers` — 427B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/worn_storage/GetFingers` — 427B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetFingers`; choose appropriate directory per project conventions.

### Hash `379cca6a7c6f452ac0e7422d381bbfe3`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/socket_write` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/sockets/socket_write` — 1KB
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/socket_write`; choose appropriate directory per project conventions.

### Hash `387a99f297688947a60ea8e87d626d4e`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/random` — 204B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/numbers/random` — 204B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/random`; choose appropriate directory per project conventions.

### Hash `38d92195323f9a1657a242ceee393427`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetHealthPoints` — 396B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetHealthPoints` — 396B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetHealthPoints`; choose appropriate directory per project conventions.

### Hash `38e169210a53ecad071315c10458f13d`
- `mud-references/deadsouls/ds3.8.2/lib/realms/template/area/armor/chainmail.c` — 630B
- `mud-references/deadsouls/ds3.8.2/lib/realms/thurtea/area/armor/chainmail.c` — 630B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/realms/template/area/armor/chainmail.c` (belongs in `src/`); move others to backups or remove.

### Hash `39089bd4db05367e0db95b2de1401346`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/mud_status` — 483B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/internals/mud_status` — 483B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/mud_status`; choose appropriate directory per project conventions.

### Hash `39904820bd5d4db4069a5609d3c53f36`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetMillimeter` — 487B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/clip/SetMillimeter` — 487B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/firearm/SetMillimeter` — 487B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/round/SetMillimeter` — 487B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/shell/SetMillimeter` — 487B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetMillimeter`; choose appropriate directory per project conventions.

### Hash `39fb51fc1f3a404fd2bc144a658f6233`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/socket_connect` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/sockets/socket_connect` — 2KB
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/socket_connect`; choose appropriate directory per project conventions.

### Hash `3a061af6d088bd4a7d1780d9ad82e16b`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/disable_commands` — 237B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/disable_commands` — 237B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/disable_commands`; choose appropriate directory per project conventions.

### Hash `3a394a2ad4b40b971caaef95e81a6821`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/pow` — 260B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/floats/pow` — 260B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/floats/pow`; choose appropriate directory per project conventions.

### Hash `3b19f8e092e2a023293b8676866f7d5b`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetRestrictedChannels` — 315B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/chat/GetRestrictedChannels` — 315B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetRestrictedChannels`; choose appropriate directory per project conventions.

### Hash `3b3d0e259550e9e32da7b2a780814bcc`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/Spent` — 262B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/battery/Spent` — 262B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/Spent`; choose appropriate directory per project conventions.

### Hash `3b44e999142643ebe5abd5abf7b7d782`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetLimbClass` — 343B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetLimbClass` — 343B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetLimbClass`; choose appropriate directory per project conventions.

### Hash `3c09cd54bd09afde42d4f01cc292c7ab`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/index` — 565B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/index` — 565B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/index`; choose appropriate directory per project conventions.

### Hash `3c81dad103b9ccaff6c9ebc0adcce5de`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetName` — 369B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetName` — 369B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/creator/GetName` — 369B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/id/GetName` — 369B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/interactive/GetName` — 369B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/messages/GetName` — 369B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/npc/GetName` — 369B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/player/GetName` — 369B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetName`; choose appropriate directory per project conventions.

### Hash `3cfcf04273da5219f4d433e0a7a33e95`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/all_inventory` — 386B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/objects/all_inventory` — 386B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/all_inventory`; choose appropriate directory per project conventions.

### Hash `3e0e5c5c566b5189e6021ab0cee472ce`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/write_buffer` — 594B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/buffers/write_buffer` — 594B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/buffers/write_buffer`; choose appropriate directory per project conventions.

### Hash `3e3572f5db4aadd287584e1faef28f7d`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/clone_object` — 513B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/objects/clone_object` — 513B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/clone_object`; choose appropriate directory per project conventions.

### Hash `3e968a1ed796d9d7ed502041184ab32b`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/move_object` — 257B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/objects/move_object` — 257B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/move_object`; choose appropriate directory per project conventions.

### Hash `3ec3e529e337ccc3ce738472f994bf6e`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetCapName` — 294B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetCapName` — 294B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/connect/GetCapName` — 294B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/id/GetCapName` — 294B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/npc/GetCapName` — 294B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/player/GetCapName` — 294B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetCapName`; choose appropriate directory per project conventions.

### Hash `3ef775b22d4fdf2b48e6a869c74dcc3f`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/CanJoin` — 328B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/clan/CanJoin` — 328B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/CanJoin`; choose appropriate directory per project conventions.

### Hash `3ef9ed3aa23fa11228f978fa78fa075e`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/socket_close` — 547B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/sockets/socket_close` — 547B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/socket_close`; choose appropriate directory per project conventions.

### Hash `3f11cd401846b382eb592f05eab48fbe`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetAllowSacrifice` — 386B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/chapel/GetAllowSacrifice` — 386B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetAllowSacrifice`; choose appropriate directory per project conventions.

### Hash `3f5b978f8579389312dadb81b776ad2e`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/m_indices` — 249B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mappings/m_indices` — 249B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/m_indices`; choose appropriate directory per project conventions.

### Hash `401389a25f7c95c30db3084383e160b9`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/enable_wizard` — 934B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/enable_wizard` — 934B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/enable_wizard`; choose appropriate directory per project conventions.

### Hash `40c99c416f8fdea56a443a6b1d7943d1`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetChannels` — 327B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/chat/GetChannels` — 327B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetChannels`; choose appropriate directory per project conventions.

### Hash `419ea0e8848993eab6f3fae03d47404f`
- `mud-references/deadsouls/ds3.8.2/lib/realms/template/workroom.c` — 4KB
- `mud-references/deadsouls/ds3.8.2/lib/realms/thurtea/bak/workroom.orig` — 4KB
- `mud-references/deadsouls/ds3.8.2/lib/realms/thurtea/room.c` — 4KB
- `mud-references/deadsouls/ds3.8.2/lib/realms/thurtea/workroom.bak` — 4KB
- `mud-references/deadsouls/ds3.8.2/lib/realms/thurtea/workroom.c` — 4KB
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/realms/thurtea/room.c` (belongs in `src/`); move others to backups or remove.

### Hash `41f829ca008717c8d2144b381fc8cb0d`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetExtraChannels` — 440B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetExtraChannels` — 440B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetExtraChannels`; choose appropriate directory per project conventions.

### Hash `424a50e4b1e6a8fdedf2041b54503c3a`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/regexp` — 4KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/strings/regexp` — 4KB
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/regexp`; choose appropriate directory per project conventions.

### Hash `43d892840e98d40aeaed0f048ff1cf49`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/deep_inventory` — 429B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/objects/deep_inventory` — 429B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/deep_inventory`; choose appropriate directory per project conventions.

### Hash `456e17ca2c7be8ac2127dd230067ee43`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventCheckHealing` — 449B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/eventCheckHealing` — 449B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventCheckHealing`; choose appropriate directory per project conventions.

### Hash `45d4dacec45af131a97489868907f220`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/AddHealthPoints` — 813B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/AddHealthPoints` — 813B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/player/AddHealthPoints` — 813B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/AddHealthPoints`; choose appropriate directory per project conventions.

### Hash `466e0c6fba2451964f28d424965e9a92`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/interactive` — 323B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/interactive` — 323B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/interactive`; choose appropriate directory per project conventions.

### Hash `46a88852d0d0f873463a2796ccfa29f7`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/obj/9mmround.c` — 442B
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/obj/9mmround.c` — 442B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/domains/campus/obj/9mmround.c` (belongs in `src/`); move others to backups or remove.

### Hash `4793d3a2449e0c5702bf73cc46c8bda7`
- `mud-references/deadsouls/ds3.8.2/lib/secure/include/network.h` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/secure/save/backup/network.6666.orig` — 1KB
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/secure/include/network.h` (belongs in `src/`); move others to backups or remove.

### Hash `47db224dfbf06717ce798d943b32fd5d`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/message` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/message` — 1KB
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/message`; choose appropriate directory per project conventions.

### Hash `47dcc03aacc96018472e363ae24f8872`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetMorality` — 253B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/classes/SetMorality` — 253B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/spell/SetMorality` — 253B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetMorality`; choose appropriate directory per project conventions.

### Hash `4808f3716d870bc88b07e13454e06a99`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/remove_call_out` — 541B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/calls/remove_call_out` — 541B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/remove_call_out`; choose appropriate directory per project conventions.

### Hash `488a6d5a3bc45df34e8e8b728bb7890c`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetAffectLong` — 445B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetAffectLong` — 445B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/clan/GetAffectLong` — 445B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetAffectLong`; choose appropriate directory per project conventions.

### Hash `48f5ba0e88209166a30758a770ac73f2`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/socket_address` — 578B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/sockets/socket_address` — 578B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/socket_address`; choose appropriate directory per project conventions.

### Hash `49245b5c7285b0c7eff07c6cb5c41dba`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventReceiveDamage` — 476B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/armor/eventReceiveDamage` — 476B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/eventReceiveDamage` — 476B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/combat/eventReceiveDamage` — 476B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/deterioration/eventReceiveDamage` — 476B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/worn_storage/eventReceiveDamage` — 476B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventReceiveDamage`; choose appropriate directory per project conventions.

### Hash `496348ac6aed8fbb7a050744b6520bae`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetProtect` — 329B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/SetProtect` — 329B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetProtect`; choose appropriate directory per project conventions.

### Hash `4a44dc02848e03094218778d38273d4f`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/parse_command_adjectiv_id_list` — 369B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/parsing/parse_command_adjectiv_id_list` — 369B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/applies/parse_command_adjectiv_id_list`; choose appropriate directory per project conventions.

### Hash `4a6229c31fbde1b7fe6480158ca8bf2c`
- `mud-references/deadsouls/ds3.8.2/lib/realms/template/area/obj/case.c` — 717B
- `mud-references/deadsouls/ds3.8.2/lib/realms/thurtea/area/obj/case.c` — 717B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/realms/template/area/obj/case.c` (belongs in `src/`); move others to backups or remove.

### Hash `4c90bf4bead8ce8f9d33f42fb5a7034d`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/valid_compile_to_c` — 418B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/valid_compile_to_c` — 418B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/applies/valid_compile_to_c`; choose appropriate directory per project conventions.

### Hash `4d2447e4b370fc70121ea6722358a755`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/get_save_file_name` — 411B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/get_save_file_name` — 411B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/applies/get_save_file_name`; choose appropriate directory per project conventions.

### Hash `4d352cc021d3864fc470313ee1a93afd`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/rmdir` — 160B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/filesystem/rmdir` — 160B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/rmdir`; choose appropriate directory per project conventions.

### Hash `4d494c42afdeedde3192615ba8c6f981`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/valid_bind` — 416B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/valid_bind` — 416B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/applies/valid_bind`; choose appropriate directory per project conventions.

### Hash `4d5cf072b3afad49136bce0a5f0172c7`
- `mud-references/deadsouls/ds3.8.2/lib/domains/cave/obj/cask.c` — 570B
- `mud-references/deadsouls/ds3.8.2/lib/domains/cave/obj/cask2.c` — 570B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/domains/cave/obj/cask.c` (belongs in `src/`); move others to backups or remove.

### Hash `4db06355322c827d5a468f48ad7dcd29`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/dump_prog` — 618B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/internals/dump_prog` — 618B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/dump_prog`; choose appropriate directory per project conventions.

### Hash `4fc2e5a9871823292bd206a566d04fb0`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/AddQuestPoints` — 324B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/AddQuestPoints` — 324B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/AddQuestPoints`; choose appropriate directory per project conventions.

### Hash `50458a6900d666ee2a3f368f4e4626bf`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/set_author` — 776B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mudlib/set_author` — 776B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/set_author`; choose appropriate directory per project conventions.

### Hash `50694b8cbe390cec20a8f236ffc88d92`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/armor/workglove_r.c` — 749B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/armor/workglove_r.c` — 749B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/domains/campus/armor/workglove_r.c` (belongs in `src/`); move others to backups or remove.

### Hash `508edd7173ebbb5c73b592e707d8a58b`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/dumpallobj` — 485B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/internals/dumpallobj` — 485B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/dumpallobj`; choose appropriate directory per project conventions.

### Hash `50d35755f868a7a0d18eb1933edd5897`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetHeat` — 250B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/burn/GetHeat` — 250B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetHeat`; choose appropriate directory per project conventions.

### Hash `5144d757810244163979e3b2399ec24a`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/load_object` — 510B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/objects/load_object` — 510B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/load_object`; choose appropriate directory per project conventions.

### Hash `516523963a524bed0f297eeeebe955ea`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetMaxMagicPoints` — 396B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetMaxMagicPoints` — 396B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/race/GetMaxMagicPoints` — 396B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetMaxMagicPoints`; choose appropriate directory per project conventions.

### Hash `519b1fba5a27c4e754fff7fa741583ca`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetCharge` — 338B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/battery/SetCharge` — 338B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetCharge`; choose appropriate directory per project conventions.

### Hash `51b02c6d2e962e97d04d79aeaf0efc23`
- `mud-references/deadsouls/ds3.8.2/lib/verbs/players/include/,nominate.h` — 153B
- `mud-references/deadsouls/ds3.8.2/lib/verbs/players/include/nominate.h` — 153B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/verbs/players/include/nominate.h` (belongs in `src/`); move others to backups or remove.

### Hash `537de3e7d0bffeb6c88b363990ead0e9`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/teller_check` — 355B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/bank/teller_check` — 355B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/teller_check`; choose appropriate directory per project conventions.

### Hash `54565d6ff7628ddb10458cd9286bb001`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/armor/workglove_l.c` — 737B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/armor/workglove_l.c` — 737B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/domains/campus/armor/workglove_l.c` (belongs in `src/`); move others to backups or remove.

### Hash `5514b7062a3efdcaa3aaabfc2d7709a3`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/obj/lever.c` — 436B
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/obj/lever.c` — 436B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/domains/campus/obj/lever.c` (belongs in `src/`); move others to backups or remove.

### Hash `559f253eb45ffa5bf07969798afc4772`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/program_info` — 357B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/program_info` — 357B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/program_info`; choose appropriate directory per project conventions.

### Hash `55a048034596fda8114866daf459722c`
- `mud-references/deadsouls/ds3.8.2/lib/realms/template/area/armor/leather_boot_l.c` — 676B
- `mud-references/deadsouls/ds3.8.2/lib/realms/thurtea/area/armor/leather_boot_l.c` — 676B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/realms/template/area/armor/leather_boot_l.c` (belongs in `src/`); move others to backups or remove.

### Hash `56a6538129b20f11e48701abf3674668`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/users` — 269B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/users` — 269B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/users`; choose appropriate directory per project conventions.

### Hash `56dbe9600dff8ad0406f3ec9bdaf5e05`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/interactive/window_size` — 317B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/window_size` — 317B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/applies/window_size`; choose appropriate directory per project conventions.

### Hash `56e6ae8fae8074ec54637625860e390a`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/DestLimb` — 473B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/DestLimb` — 473B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/DestLimb`; choose appropriate directory per project conventions.

### Hash `572421b1b4d83848d74735fbdae5741e`
- `mud-references/deadsouls/ds3.8.2/bin/mudos.cfg` — 5KB
- `mud-references/deadsouls/ds3.8.2/lib/secure/cfg/mudos.autobak.6666` — 5KB
- `mud-references/deadsouls/ds3.8.2/lib/secure/cfg/mudos.cfg` — 5KB
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/secure/cfg/mudos.autobak.6666`; choose appropriate directory per project conventions.

### Hash `5777db3ac5d822496786f5aed0ffcf78`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/socket_release` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/sockets/socket_release` — 2KB
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/socket_release`; choose appropriate directory per project conventions.

### Hash `57a5fa9f7d36232a4dbc729d3b4a9ec1`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventJoin` — 467B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/clan/eventJoin` — 467B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/leader/eventJoin` — 467B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventJoin`; choose appropriate directory per project conventions.

### Hash `5863b77d2f4b12d815a8b1e6f30ef122`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/AddLimb` — 878B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/AddLimb` — 878B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/AddLimb`; choose appropriate directory per project conventions.

### Hash `58d38c566532af25a6e6779bc3a00e22`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/in_input` — 339B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/in_input` — 339B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/in_input`; choose appropriate directory per project conventions.

### Hash `58dcb469a377f54f6c0903009eadfcc5`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetRace` — 324B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetRace` — 324B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/corpse/GetRace` — 324B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/limb/GetRace` — 324B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/race/GetRace` — 324B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetRace`; choose appropriate directory per project conventions.

### Hash `59130c0571a1fa7c5b33cbb51d1c4adc`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetFuelRequired` — 283B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/burn/SetFuelRequired` — 283B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetFuelRequired`; choose appropriate directory per project conventions.

### Hash `59c08d83862ec2dc13d6eba394f780a7`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/strlen` — 220B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/strings/strlen` — 220B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/strlen`; choose appropriate directory per project conventions.

### Hash `59ed32c7deae5b4a2ff202b9d1579c97`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/filter` — 726B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/general/filter` — 726B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/filter`; choose appropriate directory per project conventions.

### Hash `5a6364518b7a565e95d65392418db827`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetPoints` — 397B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/bonus/SetPoints` — 397B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/potion/SetPoints` — 397B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetPoints`; choose appropriate directory per project conventions.

### Hash `5a70f9a0707054fd6fa01a688d51d64d`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetDrainRate` — 431B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/battery/SetDrainRate` — 431B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/flashlight/SetDrainRate` — 431B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetDrainRate`; choose appropriate directory per project conventions.

### Hash `5b2512aff37913617d06874e93ec66b7`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/tell_room` — 451B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/objects/tell_room` — 451B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/tell_room`; choose appropriate directory per project conventions.

### Hash `5b89281079945388008151e7f7ff77cc`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetMinHeat` — 301B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/burn/SetMinHeat` — 301B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetMinHeat`; choose appropriate directory per project conventions.

### Hash `5c41eb901c9c9b2115a61be21658740c`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetProtect` — 306B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetProtect` — 306B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetProtect`; choose appropriate directory per project conventions.

### Hash `5cd146d830bab86a6c9235ad81d3ca6b`
- `mud-references/deadsouls/ds3.8.2/lib/doc/bguide/chapter06` — 3KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/manual/chapter37` — 3KB
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/bguide/chapter06`; choose appropriate directory per project conventions.

### Hash `5d68cb0047075d703088c17a1a808b47`
- `mud-references/deadsouls/ds3.8.2/lib/verbs/players/include/,withdraw.h` — 135B
- `mud-references/deadsouls/ds3.8.2/lib/verbs/players/include/withdraw.h` — 135B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/verbs/players/include/withdraw.h` (belongs in `src/`); move others to backups or remove.

### Hash `5ddc40c0281183345d677fd2087cc72c`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/catch_tell` — 596B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/interactive/catch_tell` — 596B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/applies/catch_tell`; choose appropriate directory per project conventions.

### Hash `5e6e6351f8c4d4224f8fd8dbc70ee46e`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/inherits` — 355B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/inherits` — 355B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/inherits`; choose appropriate directory per project conventions.

### Hash `5ea00b0fd11e5e09a29601abf8cd9967`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/ModCharge` — 315B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/battery/ModCharge` — 315B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/ModCharge`; choose appropriate directory per project conventions.

### Hash `5f8d4b3c2cffaa89731d7055829400ea`
- `mud-references/deadsouls/ds3.8.2/lib/domains/Ylsrim/armor/leather_armor.c` — 869B
- `mud-references/deadsouls/ds3.8.2/lib/domains/cave/armor/leather_armor.c` — 869B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/domains/cave/armor/leather_armor.c` (belongs in `src/`); move others to backups or remove.

### Hash `5fba9cd62770f622dea44dad2580a160`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/reset_eval_cost` — 277B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/reset_eval_cost` — 277B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/reset_eval_cost`; choose appropriate directory per project conventions.

### Hash `5fd61b39989563631ddb8eee6fe95675`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/get_root_uid` — 350B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/get_root_uid` — 350B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/applies/get_root_uid`; choose appropriate directory per project conventions.

### Hash `5ffc49071979e6925a5e356cab08a2b8`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/AddLead` — 271B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/AddLead` — 271B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/AddLead`; choose appropriate directory per project conventions.

### Hash `604cc67c0d3b452179c6e5958857c584`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetClass` — 260B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/classes/GetClass` — 260B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/damage/GetClass` — 260B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetClass`; choose appropriate directory per project conventions.

### Hash `60f0fe0ffe35e76de3154b92ac81ae10`
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/doors/house_door.c` — 717B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/doors/test.c` — 717B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/domains/town/doors/test.c` (belongs in `src/`); move others to backups or remove.

### Hash `6113f1193baf1c2b8bc9f1e7441d632d`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/obj/357round.c` — 469B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/obj/round.c` — 469B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/obj/357round.c` — 469B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/obj/round.c` — 469B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/domains/campus/obj/round.c` (belongs in `src/`); move others to backups or remove.

### Hash `6277440aab6749d94d631d886dae654c`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetHealRate` — 243B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetHealRate` — 243B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/race/GetHealRate` — 243B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetHealRate`; choose appropriate directory per project conventions.

### Hash `6280bd4cac7c37a49e99b671e80013b0`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/query_notify_fail` — 599B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/query_notify_fail` — 599B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/query_notify_fail`; choose appropriate directory per project conventions.

### Hash `633bba8198e606b6e5f819e839a9c12a`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/cache_stats` — 376B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/internals/cache_stats` — 376B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/cache_stats`; choose appropriate directory per project conventions.

### Hash `639b3b38d6f5f936d8c7899ae30731b4`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/file_length` — 440B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/filesystem/file_length` — 440B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/file_length`; choose appropriate directory per project conventions.

### Hash `6418b7f067634e3a6338afcd3d9217dd`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/max_eval_cost` — 315B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/max_eval_cost` — 315B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/max_eval_cost`; choose appropriate directory per project conventions.

### Hash `6525daab8d3e36b59e30fa3d4ec86908`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/query_idle` — 269B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/query_idle` — 269B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/query_idle`; choose appropriate directory per project conventions.

### Hash `65cf1037fba6b79f7ccd1f3645bc7b63`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/get_char` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/get_char` — 1KB
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/get_char`; choose appropriate directory per project conventions.

### Hash `65f47c605678aac39128a8db2699d639`
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/doors/m2.c` — 575B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/doors/m3.c` — 575B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/doors/m4.c` — 575B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/doors/m5.c` — 575B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/doors/m6.c` — 575B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/domains/town/doors/m5.c` (belongs in `src/`); move others to backups or remove.

### Hash `660086efe6eb5cd3d250560abe0851de`
- `mud-references/deadsouls/ds3.8.2/lib/doc/bguide/chapter03` — 12KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/manual/chapter34` — 12KB
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/bguide/chapter03`; choose appropriate directory per project conventions.

### Hash `660fd492fdd5506e311b4602dd87b384`
- `mud-references/deadsouls/ds3.8.2/bin/addr_server` — 24KB
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/addr_server` — 24KB
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/bin/addr_server`; choose appropriate directory per project conventions.

### Hash `6638d2f804cc28a7da1f7e60c6cff59e`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/link` — 495B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/filesystem/link` — 495B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/link`; choose appropriate directory per project conventions.

### Hash `666648208837042db4465857f0040e27`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetHeartModifier` — 417B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetHeartModifier` — 417B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetHeartModifier`; choose appropriate directory per project conventions.

### Hash `6695bcdcf6b100264687464b80903d46`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/add_action` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/add_action` — 2KB
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/add_action`; choose appropriate directory per project conventions.

### Hash `66b16a1e835b453d251647f9da2bc38c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/learning/room/death.c` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/std/death.c` — 2KB
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/domains/learning/room/death.c` (belongs in `src/`); move others to backups or remove.

### Hash `6712f4b99fde47230c69c7b193375ccc`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/query_ip_name` — 451B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/query_ip_name` — 451B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/query_ip_name`; choose appropriate directory per project conventions.

### Hash `68590318d420e0fa6acf01d87064b9de`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetComposition` — 722B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/clay/SetComposition` — 722B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetComposition`; choose appropriate directory per project conventions.

### Hash `68d6499c44de83b65c8d445c53bf6cd6`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/CanExtinguish` — 309B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/burn/CanExtinguish` — 309B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/CanExtinguish`; choose appropriate directory per project conventions.

### Hash `69c48b6fc0afa93be1770962fb0b567f`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/set_debug_level` — 531B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/internals/set_debug_level` — 531B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/set_debug_level`; choose appropriate directory per project conventions.

### Hash `6a130a9261217688421f27b36b45eb64`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetDrainable` — 348B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/battery/SetDrainable` — 348B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetDrainable`; choose appropriate directory per project conventions.

### Hash `6a182da967f34b378ac90e23bac2a358`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetLead` — 363B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetLead` — 363B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetLead`; choose appropriate directory per project conventions.

### Hash `6ba305a16923b237be9db2253257a6ca`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventMoralAct` — 370B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/classes/eventMoralAct` — 370B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventMoralAct`; choose appropriate directory per project conventions.

### Hash `6bf468d0b2a8db20c3087856508af362`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/throw` — 480B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/calls/throw` — 480B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/throw`; choose appropriate directory per project conventions.

### Hash `6c2e1d7dc2be06732925c63644c44114`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/flush_messages` — 406B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/flush_messages` — 406B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/flush_messages`; choose appropriate directory per project conventions.

### Hash `6c430ff94a736d02e372edbb2abcc250`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/crc32` — 243B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/buffers/crc32` — 243B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/buffers/crc32`; choose appropriate directory per project conventions.

### Hash `6c8b698424e8ea3ac41da34e982241c9`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/armor/wizard_hat.c` — 809B
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/armor/wizard_hat.c` — 809B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/domains/campus/armor/wizard_hat.c` (belongs in `src/`); move others to backups or remove.

### Hash `6d07311413e5eb1f7374db0fb143b6bc`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetLimbParent` — 345B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetLimbParent` — 345B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetLimbParent`; choose appropriate directory per project conventions.

### Hash `6d4e88408bfeafa99c217b23a08e959d`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/tail` — 281B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/filesystem/tail` — 281B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/tail`; choose appropriate directory per project conventions.

### Hash `6d90b59660739184006cdd699dce1eea`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetLeader` — 359B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/clan/GetLeader` — 359B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/follow/GetLeader` — 359B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetLeader`; choose appropriate directory per project conventions.

### Hash `6da24d9548a3a6f13ee9579452038966`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/getuid` — 416B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mudlib/getuid` — 416B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/getuid`; choose appropriate directory per project conventions.

### Hash `6dc6eb41d5c0248cfd3bda47b254bd86`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventCheckProtection` — 505B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/eventCheckProtection` — 505B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventCheckProtection`; choose appropriate directory per project conventions.

### Hash `6dc9564ec21483b1e951eb65ee09e75c`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventHealDamage` — 761B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/eventHealDamage` — 761B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventHealDamage`; choose appropriate directory per project conventions.

### Hash `6e2ab4fca00a3e9da87bb9d048cb96f1`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/next_inventory` — 352B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/objects/next_inventory` — 352B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/next_inventory`; choose appropriate directory per project conventions.

### Hash `6efe7e751946f8abe520778f0651309f`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventSacrifice` — 388B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/chapel/eventSacrifice` — 388B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventSacrifice`; choose appropriate directory per project conventions.

### Hash `6f93ac2ccc5936b754fb4e590dea3922`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/localtime` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/localtime` — 1KB
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/localtime`; choose appropriate directory per project conventions.

### Hash `7020a9f72a57c39f34e500e5cf3c074f`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/evaluate` — 275B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/functions/evaluate` — 275B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/evaluate`; choose appropriate directory per project conventions.

### Hash `706cd9517db66103ed02a780a32f6fe0`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/query_shadowing` — 375B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/calls/query_shadowing` — 375B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/query_shadowing`; choose appropriate directory per project conventions.

### Hash `7149bb04a20516b2c7b19e814d9a89de`
- `mud-references/deadsouls/ds3.8.2/lib/secure/daemon/imc2.c` — 60KB
- `mud-references/deadsouls/ds3.8.2/lib/secure/save/backup/imc2.orig` — 60KB
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/secure/daemon/imc2.c` (belongs in `src/`); move others to backups or remove.

### Hash `7159f0cb76195ee8c94240fd4b1bc3a2`
- `mud-references/deadsouls/ds3.8.2/lib/secure/daemon/update.blank` — 496B
- `mud-references/deadsouls/ds3.8.2/lib/secure/daemon/update.c` — 496B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/secure/daemon/update.blank`; choose appropriate directory per project conventions.

### Hash `71ec3b884dd30d30040fdbdb14f4ac02`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetFirearmType` — 452B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/clip/SetFirearmType` — 452B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/firearm/SetFirearmType` — 452B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/round/SetFirearmType` — 452B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/shell/SetFirearmType` — 452B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetFirearmType`; choose appropriate directory per project conventions.

### Hash `7316a8264df9e694a4d4c2e85662b635`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/obj/lamp.c` — 377B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/obj/lamp.c` — 377B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/domains/campus/obj/lamp.c` (belongs in `src/`); move others to backups or remove.

### Hash `731ebe8d9ff9a3d764c4baa05330f157`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/HealLimb` — 282B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/HealLimb` — 282B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/HealLimb`; choose appropriate directory per project conventions.

### Hash `73376166282403daae9b0392a08511b7`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/epilog` — 619B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/epilog` — 619B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/applies/epilog`; choose appropriate directory per project conventions.

### Hash `73cebaec5b8ee5a28f40c6786f895621`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/memory_info` — 693B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/internals/memory_info` — 693B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/memory_info`; choose appropriate directory per project conventions.

### Hash `73d3cab451dfe4a8c7ff81aad0e7945c`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetDrink` — 224B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetDrink` — 224B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetDrink`; choose appropriate directory per project conventions.

### Hash `74570a5d6befcdfc94f1e49b311038a1`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventInitiate` — 504B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/clan/eventInitiate` — 504B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventInitiate`; choose appropriate directory per project conventions.

### Hash `7520b9dda4d5e4a64699a04bb659db85`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/resolve` — 798B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/resolve` — 798B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/resolve`; choose appropriate directory per project conventions.

### Hash `7533a69c7844a554a3b98ef2e7450605`
- `mud-references/deadsouls/ds3.8.2/bin/driver` — 728KB
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/driver` — 728KB
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/bin/driver`; choose appropriate directory per project conventions.

### Hash `758828e02d94ecf1aad87c41871aa511`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetDrainable` — 288B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/battery/GetDrainable` — 288B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetDrainable`; choose appropriate directory per project conventions.

### Hash `76910f1d324d8e09ea4437a11630b3a4`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/userp` — 234B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/userp` — 234B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/userp`; choose appropriate directory per project conventions.

### Hash `7723dc0f373368b664ff1d95577bb195`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/upper_case` — 354B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/strings/upper_case` — 354B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/upper_case`; choose appropriate directory per project conventions.

### Hash `7735d317a545dc7e767098d15983549f`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/this_player` — 170B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/this_player` — 170B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/this_player`; choose appropriate directory per project conventions.

### Hash `7737054fc8a022b4532200927bea98ab`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/socket_accept` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/sockets/socket_accept` — 2KB
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/socket_accept`; choose appropriate directory per project conventions.

### Hash `7770794ad1137266d71d35ac6d985b22`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/save_ed_setup` — 347B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/save_ed_setup` — 347B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/applies/save_ed_setup`; choose appropriate directory per project conventions.

### Hash `77df6177e16b47e91a38378ebe88639a`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/parse_command` — 9KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/parsing/parse_command` — 9KB
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/applies/parse_command`; choose appropriate directory per project conventions.

### Hash `78c31168e4cb623ad78c3bcc1edc6c03`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/floor` — 250B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/floats/floor` — 250B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/floats/floor`; choose appropriate directory per project conventions.

### Hash `78cfb5c057f8661a85506bc4d182c4be`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/all_previous_objects` — 502B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/all_previous_objects` — 502B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/all_previous_objects`; choose appropriate directory per project conventions.

### Hash `79099adf1f20430470dcf3083f996a56`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/AddAlcohol` — 290B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/AddAlcohol` — 290B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/AddAlcohol`; choose appropriate directory per project conventions.

### Hash `79b22da7300fa3b84455398a1c9e163d`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/export_uid` — 376B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mudlib/export_uid` — 376B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/export_uid`; choose appropriate directory per project conventions.

### Hash `7a4d6192963e2fa8a98d0af867573f22`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/CanRemoveItem` — 354B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/CanRemoveItem` — 354B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/CanRemoveItem`; choose appropriate directory per project conventions.

### Hash `7a73469c5771a49fbf8480e134d2b382`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/match_path` — 475B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mappings/match_path` — 475B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/match_path`; choose appropriate directory per project conventions.

### Hash `7aa86f133adb3ba48b4a2d5d33531b2f`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/RestrictChannel` — 335B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/chat/RestrictChannel` — 335B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/RestrictChannel`; choose appropriate directory per project conventions.

### Hash `7ac48dd97b205e40afb6d647b766527e`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/flag` — 380B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/flag` — 380B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/applies/flag`; choose appropriate directory per project conventions.

### Hash `7b715146261f7f1984fc4f99f79a5cbd`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/query_snooping` — 333B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/query_snooping` — 333B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/query_snooping`; choose appropriate directory per project conventions.

### Hash `7bf9646546703d47f0469ca6e0cca26f`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/armor/foodsmock.c` — 494B
- `mud-references/deadsouls/ds3.8.2/lib/domains/cave/armor/foodsmock.c` — 494B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/domains/campus/armor/foodsmock.c` (belongs in `src/`); move others to backups or remove.

### Hash `7c2881df4b0ffd026450d4669e64f981`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetMagicPoints` — 297B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetMagicPoints` — 297B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetMagicPoints`; choose appropriate directory per project conventions.

### Hash `7c7d4ee32e057dab6fee0306e6082ff0`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetPoison` — 256B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetPoison` — 256B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/poison/GetPoison` — 256B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetPoison`; choose appropriate directory per project conventions.

### Hash `7c8326700818b541e5ace364b823e770`
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/room/pod.c` — 375B
- `mud-references/deadsouls/ds3.8.2/lib/domains/learning/room/pod.c` — 375B
- `mud-references/deadsouls/ds3.8.2/lib/std/pod.c` — 375B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/domains/default/room/pod.c` (belongs in `src/`); move others to backups or remove.

### Hash `7d434806feae300b3a41e38cdd3c76a1`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetBurnRate` — 365B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/burn/SetBurnRate` — 365B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/lamp/SetBurnRate` — 365B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetBurnRate`; choose appropriate directory per project conventions.

### Hash `7e608f9b79b7b64e14b4e8c0a14bb649`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetLimbChildren` — 368B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetLimbChildren` — 368B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetLimbChildren`; choose appropriate directory per project conventions.

### Hash `7ea93485d531b8c2b159bbdacc2bd7e7`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventBuy` — 661B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/eventBuy` — 661B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/vendor/eventBuy` — 661B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventBuy`; choose appropriate directory per project conventions.

### Hash `7f1c3861b9a9472b75ab900c8b09cf21`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/obj/bbucket.c` — 874B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/obj/bbucket.c` — 874B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/obj/trash.c` — 874B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/domains/campus/obj/bbucket.c` (belongs in `src/`); move others to backups or remove.

### Hash `800bc90f02163f5c7e0911da69869fd1`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/slow_shutdown` — 576B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/slow_shutdown` — 576B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/applies/slow_shutdown`; choose appropriate directory per project conventions.

### Hash `805dc87d4ecb4ebfadde4a39cef5cb4e`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetSleeping` — 514B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/SetSleeping` — 514B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetSleeping`; choose appropriate directory per project conventions.

### Hash `80d1d67fdee3a8aa35fe3246b9d46fde`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/previous_object` — 734B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/calls/previous_object` — 734B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/previous_object`; choose appropriate directory per project conventions.

### Hash `80e19eab7e1acf0ca1c73cc20a86499e`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/NewBody` — 303B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/NewBody` — 303B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/race/NewBody` — 303B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/NewBody`; choose appropriate directory per project conventions.

### Hash `80fab548bcd028a81765d4f195d6d7f4`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetFood` — 368B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetFood` — 368B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/fish/GetFood` — 368B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetFood`; choose appropriate directory per project conventions.

### Hash `81207b2e46290fd0b0891b8be6419dd0`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/set_bit` — 525B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/strings/set_bit` — 525B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/set_bit`; choose appropriate directory per project conventions.

### Hash `812c04b1a11cf26d61147c7a151eadfd`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/doors/eledoor1.c` — 642B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/doors/eledoor2.c` — 642B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/doors/eledoor3.c` — 642B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/domains/campus/doors/eledoor1.c` (belongs in `src/`); move others to backups or remove.

### Hash `8193a1c121f034a99c8b0682e03e4dc2`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetRechargeable` — 304B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/battery/GetRechargeable` — 304B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetRechargeable`; choose appropriate directory per project conventions.

### Hash `819ccd02e44eee1c8bf593641d6c1bb0`
- `mud-references/deadsouls/ds3.8.2/lib/doc/bguide/chapter05` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/manual/chapter36` — 2KB
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/bguide/chapter05`; choose appropriate directory per project conventions.

### Hash `81b6d889829b440d6b3b948e7140a908`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/replaceable` — 868B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/replaceable` — 868B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/replaceable`; choose appropriate directory per project conventions.

### Hash `822dbac57d9f7310f17b7bf139fd16e9`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetNoChanColors` — 319B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/chat/GetNoChanColors` — 319B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetNoChanColors`; choose appropriate directory per project conventions.

### Hash `82304eab4d9a495bd06c22403263f21b`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventBurnOut` — 267B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/burn/eventBurnOut` — 267B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventBurnOut`; choose appropriate directory per project conventions.

### Hash `83a006eb4a41719cb20b1d1287663468`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/RestoreLimb` — 798B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/RestoreLimb` — 798B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/RestoreLimb`; choose appropriate directory per project conventions.

### Hash `840fba9ef9b906230c3ade3e3adf73c9`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/CanRelease` — 477B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/clip/CanRelease` — 477B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/container/CanRelease` — 477B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/firearm/CanRelease` — 477B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/fishing/CanRelease` — 477B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/CanRelease`; choose appropriate directory per project conventions.

### Hash `841dfc81184eff03a2424657c77bdc74`
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/room/void.c` — 282B
- `mud-references/deadsouls/ds3.8.2/lib/domains/learning/room/void.c` — 282B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/room/void.c` — 282B
- `mud-references/deadsouls/ds3.8.2/lib/std/void.c` — 282B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/domains/default/room/void.c` (belongs in `src/`); move others to backups or remove.

### Hash `841f2cd1c2bcd229093e4cb859562aef`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/CanSacrifice` — 457B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/chapel/CanSacrifice` — 457B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/CanSacrifice`; choose appropriate directory per project conventions.

### Hash `847e61900a0317240822bb42fd214d45`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/interactive/logon` — 367B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/logon` — 367B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/applies/logon`; choose appropriate directory per project conventions.

### Hash `84905a286119055b4b76c3fe8f41c54d`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetLong` — 502B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetLong` — 502B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/bot/GetLong` — 502B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/creator/GetLong` — 502B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/donate/GetLong` — 502B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/door/GetLong` — 502B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/fuel/GetLong` — 502B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/interactive/GetLong` — 502B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/lamp/GetLong` — 502B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/look/GetLong` — 502B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/npc/GetLong` — 502B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/player/GetLong` — 502B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/room/GetLong` — 502B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/torch/GetLong` — 502B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetLong`; choose appropriate directory per project conventions.

### Hash `856fa4518980a3cda5cd6d1820771d00`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetHealthShort` — 302B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetHealthShort` — 302B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/corpse/GetHealthShort` — 302B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetHealthShort`; choose appropriate directory per project conventions.

### Hash `85b1c7f3884c7304be95f80e334369b3`
- `mud-references/deadsouls/ds3.8.2/lib/domains/Praxis/adm/README` — 472B
- `mud-references/deadsouls/ds3.8.2/lib/domains/Ylsrim/adm/README` — 472B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/adm/README` — 472B
- `mud-references/deadsouls/ds3.8.2/lib/domains/cave/adm/README` — 472B
- `mud-references/deadsouls/ds3.8.2/lib/domains/learning/adm/README` — 472B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/domains/campus/adm/README`; choose appropriate directory per project conventions.

### Hash `85ff34c173168a7760adecfd0eb9ed55`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/filter_array` — 328B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/arrays/filter_array` — 328B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/filter_array`; choose appropriate directory per project conventions.

### Hash `860594c01c843453078de3bde8d5ae79`
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/weap/9mil.c` — 590B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/weap/9mil.c` — 590B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/domains/default/weap/9mil.c` (belongs in `src/`); move others to backups or remove.

### Hash `8613985ec49eb8f757ae6439e879bb2a`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charles/bak2/fblue` — 2B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charles/bak2/fred` — 2B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charles/bak2/fred`; choose appropriate directory per project conventions.

### Hash `87404bb33460125e78468718f166c06f`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/read_bytes` — 467B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/filesystem/read_bytes` — 467B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/read_bytes`; choose appropriate directory per project conventions.

### Hash `876342b72cf041d9fac783a05fa89af5`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/save_object` — 577B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/objects/save_object` — 577B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/save_object`; choose appropriate directory per project conventions.

### Hash `8784a318b3bad100516474f17c102746`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/AddExtraChannels` — 440B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/AddExtraChannels` — 440B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/AddExtraChannels`; choose appropriate directory per project conventions.

### Hash `8787acb609663bf1cabb17249805b182`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventReconnect` — 370B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/eventReconnect` — 370B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/chat/eventReconnect` — 370B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/creator/eventReconnect` — 370B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/interactive/eventReconnect` — 370B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/npc/eventReconnect` — 370B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/player/eventReconnect` — 370B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventReconnect`; choose appropriate directory per project conventions.

### Hash `880d834ab0f1db2a24ed8496e3326e09`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/valid_seteuid` — 503B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/valid_seteuid` — 503B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/applies/valid_seteuid`; choose appropriate directory per project conventions.

### Hash `883031c0c89be303829188837f73f8b5`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/obj/dcell.c` — 549B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/obj/dcell_crappy.c` — 549B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/domains/campus/obj/dcell_crappy.c` (belongs in `src/`); move others to backups or remove.

### Hash `8899f47b1138f491758348b5a90b54b7`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/rm` — 208B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/filesystem/rm` — 208B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/rm`; choose appropriate directory per project conventions.

### Hash `89a2d4dc3fad287c01a7affa2f5df1cc`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetBodyComposition` — 452B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/SetBodyComposition` — 452B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetBodyComposition`; choose appropriate directory per project conventions.

### Hash `8a058366c6f43535274801086d215ef8`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/sort_array` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/arrays/sort_array` — 1KB
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/sort_array`; choose appropriate directory per project conventions.

### Hash `8a9e1a1c8bc615abff597cda4019e670`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/strsrch` — 703B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/strings/strsrch` — 703B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/strsrch`; choose appropriate directory per project conventions.

### Hash `8af49d8025b695fb95583677dd92266b`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetLeader` — 390B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/clan/SetLeader` — 390B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/follow/SetLeader` — 390B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetLeader`; choose appropriate directory per project conventions.

### Hash `8bd79f207cdf58ef04a5713ca8760043`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/log_error` — 591B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/log_error` — 591B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/applies/log_error`; choose appropriate directory per project conventions.

### Hash `8c4ae8d5c2c2799127e6f0f64786a4fd`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/query_snoop` — 268B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/query_snoop` — 268B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/query_snoop`; choose appropriate directory per project conventions.

### Hash `8d0152c306ceb6c0ea0dbc403f9460c1`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/master` — 188B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/objects/master` — 188B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/master`; choose appropriate directory per project conventions.

### Hash `8d27a4e669d10dddb9a87ed6b77d4b8b`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/reclaim_objects` — 649B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/reclaim_objects` — 649B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/reclaim_objects`; choose appropriate directory per project conventions.

### Hash `8e16a47bb5377e0e65ddff7ebf1fc36f`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/query_ed_mode` — 376B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/query_ed_mode` — 376B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/query_ed_mode`; choose appropriate directory per project conventions.

### Hash `8e4057968b8d25081e06b839aa4d3fef`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetPowerType` — 307B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/battery/SetPowerType` — 307B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetPowerType`; choose appropriate directory per project conventions.

### Hash `8e495b329adea2898aa769a90dbb42f6`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/RemoveExtraChannels` — 468B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/RemoveExtraChannels` — 468B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/RemoveExtraChannels`; choose appropriate directory per project conventions.

### Hash `8e572dc3871403128b094be40c87cd8c`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/get_config` — 309B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/internals/get_config` — 309B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/get_config`; choose appropriate directory per project conventions.

### Hash `8ef58ed432656644f9c9e1a8520a6cb8`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventUnjoin` — 450B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/clan/eventUnjoin` — 450B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventUnjoin`; choose appropriate directory per project conventions.

### Hash `8f6dffdd8530665e802320546824e011`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/get_bb_uid` — 393B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/get_bb_uid` — 393B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/applies/get_bb_uid`; choose appropriate directory per project conventions.

### Hash `900ddb90521bbd6cee3507c7dd95e5f5`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetSleeping` — 415B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetSleeping` — 415B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetSleeping`; choose appropriate directory per project conventions.

### Hash `90b07ad6cb8b6517a0c500a13e724eaa`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/write_file` — 288B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/filesystem/write_file` — 288B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/write_file`; choose appropriate directory per project conventions.

### Hash `90e44b317eca9db1d8da426f1ce886a0`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetBurntValue` — 277B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/burn/GetBurntValue` — 277B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetBurntValue`; choose appropriate directory per project conventions.

### Hash `91011f82e119806033f9bc80cc37c6e8`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetSkills` — 702B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/abilities/GetSkills` — 702B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/bonus/GetSkills` — 702B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/potion/GetSkills` — 702B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/spell/GetSkills` — 702B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetSkills`; choose appropriate directory per project conventions.

### Hash `91dcb594352c53d8551f4b2ab85dd981`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/m_delete` — 646B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mappings/m_delete` — 646B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/m_delete`; choose appropriate directory per project conventions.

### Hash `92b9c51fe03b559f33791a8b2c3732e4`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventLight` — 425B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/burn/eventLight` — 425B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/flashlight/eventLight` — 425B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/lamp/eventLight` — 425B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/light/eventLight` — 425B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventLight`; choose appropriate directory per project conventions.

### Hash `931c5aa12d320da5a5a4021bb647c77e`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/InitComposition` — 311B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/clay/InitComposition` — 311B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/InitComposition`; choose appropriate directory per project conventions.

### Hash `94589ceda6f9a8e5e9dedf787b3213e9`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetSkillModifier` — 323B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/classes/GetSkillModifier` — 323B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetSkillModifier`; choose appropriate directory per project conventions.

### Hash `947ce1d70e70a3bc3d2204d5347ccc60`
- `mud-references/deadsouls/ds3.8.2/lib/doc/bguide/chapter07` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/manual/chapter38` — 2KB
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/bguide/chapter07`; choose appropriate directory per project conventions.

### Hash `94a5a4ed576386433d8b4fb8eb3221a3`
- `mud-references/deadsouls/ds3.8.2/lib/doc/bguide/chapter08` — 3KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/manual/chapter39` — 3KB
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/bguide/chapter08`; choose appropriate directory per project conventions.

### Hash `94b600ad56427f0cc2a792b3c1bb5261`
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/weap/m16rifle.c` — 824B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/weap/m16rifle.c` — 824B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/domains/default/weap/m16rifle.c` (belongs in `src/`); move others to backups or remove.

### Hash `94fff4e0f6e1ead527c406b1c725fdd9`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/ceil` — 317B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/floats/ceil` — 317B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/floats/ceil`; choose appropriate directory per project conventions.

### Hash `954362da68c2c9fa4095a0100ff643d2`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/call_other` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/calls/call_other` — 1KB
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/call_other`; choose appropriate directory per project conventions.

### Hash `95840c52542dbbfc53f2426b53063af6`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/children` — 379B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/objects/children` — 379B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/children`; choose appropriate directory per project conventions.

### Hash `963c44efc9230b5c56378afdd6847831`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/socket_bind` — 907B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/sockets/socket_bind` — 907B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/socket_bind`; choose appropriate directory per project conventions.

### Hash `9701a52e0371a0d7305c4e035eef436c`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetMissingLimbs` — 440B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetMissingLimbs` — 440B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetMissingLimbs`; choose appropriate directory per project conventions.

### Hash `977c80c48ab40858d93df5b3fb9098a9`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/generate_source` — 755B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/compile/generate_source` — 755B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/generate_source`; choose appropriate directory per project conventions.

### Hash `97842fdb16db3b3b470f7508569fcc1c`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/environment` — 388B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/objects/environment` — 388B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/environment`; choose appropriate directory per project conventions.

### Hash `97d49c054c47b2950e2a1c293e59f675`
- `mud-references/deadsouls/ds3.8.2/lib/domains/cave/obj/cup.c` — 524B
- `mud-references/deadsouls/ds3.8.2/lib/realms/template/area/obj/cup.c` — 524B
- `mud-references/deadsouls/ds3.8.2/lib/realms/thurtea/area/obj/cup.c` — 524B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/realms/template/area/obj/cup.c` (belongs in `src/`); move others to backups or remove.

### Hash `9854badc76d4495cded4938fa8afee55`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventWear` — 446B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/eventWear` — 446B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventWear`; choose appropriate directory per project conventions.

### Hash `98a357e21c809422614577f7f9c02edd`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/next_bit` — 282B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/strings/next_bit` — 282B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/next_bit`; choose appropriate directory per project conventions.

### Hash `98d38d1c569b534be299750ea991b1b1`
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/testsuite/single/tests/efuns/query_ip_name.c` — 142B
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/testsuite/single/tests/efuns/query_ip_number.c` — 142B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/testsuite/single/tests/efuns/query_ip_name.c` (belongs in `src/`); move others to backups or remove.

### Hash `992f188488f29ca8df46471999df7fe2`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetStats` — 630B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/bonus/GetStats` — 630B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/genetics/GetStats` — 630B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/potion/GetStats` — 630B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetStats`; choose appropriate directory per project conventions.

### Hash `99552a19434c8190963802e655dfcace`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/error` — 332B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/error` — 332B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/error`; choose appropriate directory per project conventions.

### Hash `9983c56fc46f3a8b70dbe0e572510fe7`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/valid_read` — 501B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/valid_read` — 501B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/applies/valid_read`; choose appropriate directory per project conventions.

### Hash `9a481341bb8ff990bc9cd41dd34dbf05`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/CanLight` — 190B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/light/CanLight` — 190B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/CanLight`; choose appropriate directory per project conventions.

### Hash `9a5a27a842540463829cd9839b04822a`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetSkillModifier` — 349B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/classes/SetSkillModifier` — 349B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetSkillModifier`; choose appropriate directory per project conventions.

### Hash `9a7cde74be9702ff8e28470205542194`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/undefinedp` — 680B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mixed/undefinedp` — 680B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/undefinedp`; choose appropriate directory per project conventions.

### Hash `9aa4674827115e65439077604f58002d`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/test_bit` — 242B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/strings/test_bit` — 242B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/test_bit`; choose appropriate directory per project conventions.

### Hash `9af68ba7bd6712fc639f680b029d34f1`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/save_variable` — 222B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/general/save_variable` — 222B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/save_variable`; choose appropriate directory per project conventions.

### Hash `9c4df05e4a9e5e31187f7443cd39a58c`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/query_host_name` — 256B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/query_host_name` — 256B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/query_host_name`; choose appropriate directory per project conventions.

### Hash `9c77aa6b52af750580912656ea886f52`
- `mud-references/deadsouls/ds3.8.2/lib/doc/help/players/map` — 18B
- `mud-references/deadsouls/ds3.8.2/lib/doc/help/players/mapping` — 18B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/help/players/map`; choose appropriate directory per project conventions.

### Hash `9c7f3503c06d9359b830bdc6f25b1834`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/RemoveBonuses` — 255B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/bonus/RemoveBonuses` — 255B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/RemoveBonuses`; choose appropriate directory per project conventions.

### Hash `9c8c7659abfdf1c67fec24875605499a`
- `mud-references/deadsouls/ds3.8.2/lib/domains/Ylsrim/room/furnace.c` — 110B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/room/furnace.c` — 110B
- `mud-references/deadsouls/ds3.8.2/lib/domains/cave/room/furnace.c` — 110B
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/room/furnace.c` — 110B
- `mud-references/deadsouls/ds3.8.2/lib/domains/learning/room/furnace.c` — 110B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/room/furnace.c` — 110B
- `mud-references/deadsouls/ds3.8.2/lib/std/furnace.c` — 110B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/domains/campus/room/furnace.c` (belongs in `src/`); move others to backups or remove.

### Hash `9cbe3e525e02692f34d2f37380aa2e34`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/cp` — 324B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/filesystem/cp` — 324B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/cp`; choose appropriate directory per project conventions.

### Hash `9d41282b55cc6c659ee70d9f1041bef9`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/first_inventory` — 424B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/objects/first_inventory` — 424B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/first_inventory`; choose appropriate directory per project conventions.

### Hash `9d4180f42b2bf33380e71e8ba0e3ec15`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/floatp` — 219B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mixed/floatp` — 219B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/floatp`; choose appropriate directory per project conventions.

### Hash `9d66b6b4f1b8d16e89a5a7ed42e9e460`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetMillimeter` — 415B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/clip/GetMillimeter` — 415B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/firearm/GetMillimeter` — 415B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/round/GetMillimeter` — 415B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/shell/GetMillimeter` — 415B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetMillimeter`; choose appropriate directory per project conventions.

### Hash `9dba4289b44f2547cfb8abf8ab7ca888`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetClanSkill` — 276B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/clan/GetClanSkill` — 276B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetClanSkill`; choose appropriate directory per project conventions.

### Hash `9dbc018c987004858f52f65eb2f58131`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/set_living_name` — 406B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mudlib/set_living_name` — 406B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/set_living_name`; choose appropriate directory per project conventions.

### Hash `9e1e27160be75ab60614e2f22d9d6234`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetWieldingLimbs` — 470B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetWieldingLimbs` — 470B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetWieldingLimbs`; choose appropriate directory per project conventions.

### Hash `9e7750c8dc1c42d705da1286b47cbd16`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/room/freezer.c` — 707B
- `mud-references/deadsouls/ds3.8.2/lib/domains/cave/room/freezer.c` — 707B
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/room/freezer.c` — 707B
- `mud-references/deadsouls/ds3.8.2/lib/domains/learning/room/freezer.c` — 707B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/room/freezer.c` — 707B
- `mud-references/deadsouls/ds3.8.2/lib/std/freezer.c` — 707B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/domains/campus/room/freezer.c` (belongs in `src/`); move others to backups or remove.

### Hash `9ea358b8bf768ca840e3bdc40fb35844`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetReligion` — 281B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/chapel/SetReligion` — 281B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/classes/SetReligion` — 281B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetReligion`; choose appropriate directory per project conventions.

### Hash `a10f7c7f20f9198d8e1d0ecea0e85c00`
- `mud-references/deadsouls/ds3.8.2/lib/realms/template/area/room/sample_room.c` — 623B
- `mud-references/deadsouls/ds3.8.2/lib/realms/thurtea/area/room/sample_room.c` — 623B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/realms/template/area/room/sample_room.c` (belongs in `src/`); move others to backups or remove.

### Hash `a124d50ea0292d372ac75990afa3b624`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/domain_file` — 606B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/domain_file` — 606B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/applies/domain_file`; choose appropriate directory per project conventions.

### Hash `a16ed8bc8b4d2107b8b3a536145666d8`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/AddFood` — 286B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/AddFood` — 286B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/AddFood`; choose appropriate directory per project conventions.

### Hash `a243abe45e2b3ca2989434805b0cf257`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/CanMarry` — 379B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/chapel/CanMarry` — 379B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/interactive/CanMarry` — 379B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/CanMarry`; choose appropriate directory per project conventions.

### Hash `a28b45b89a4c137cdb860c04f2c5712c`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/CanManipulate` — 443B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/CanManipulate` — 443B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/manipulate/CanManipulate` — 443B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/CanManipulate`; choose appropriate directory per project conventions.

### Hash `a3ce3dd4f1adee84e1076af812a867ca`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/allocate_buffer` — 435B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/buffers/allocate_buffer` — 435B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/buffers/allocate_buffer`; choose appropriate directory per project conventions.

### Hash `a4966a240e43c2d459c5bb42b115a42b`
- `mud-references/deadsouls/ds3.8.2/lib/realms/template/area/obj/chest.c` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/realms/thurtea/area/obj/chest.c` — 1KB
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/realms/template/area/obj/chest.c` (belongs in `src/`); move others to backups or remove.

### Hash `a49b933c0e1e7fc5c0878c4bb88248e5`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/ParseHook` — 328B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/ParseHook` — 328B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/ParseHook`; choose appropriate directory per project conventions.

### Hash `a620cad9c1975b15af8b7194c3f80f56`
- `mud-references/deadsouls/ds3.8.2/lib/secure/lib/connect.c` — 30KB
- `mud-references/deadsouls/ds3.8.2/lib/secure/lib/connect.real` — 30KB
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/secure/lib/connect.c` (belongs in `src/`); move others to backups or remove.

### Hash `a68b775e04464837d995dc126f2dbf8f`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/clear_bit` — 353B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/strings/clear_bit` — 353B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/clear_bit`; choose appropriate directory per project conventions.

### Hash `a6cad41d502762f6dd857b18c1c3b2b5`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/explode` — 442B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/strings/explode` — 442B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/explode`; choose appropriate directory per project conventions.

### Hash `a6f438eccf88f34f8dad75bd33a8dc3d`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetMissingLimbParents` — 364B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetMissingLimbParents` — 364B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetMissingLimbParents`; choose appropriate directory per project conventions.

### Hash `a72c2f409b89c062b37bb4823a647bc4`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/RemoveChannel` — 338B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/chat/RemoveChannel` — 338B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/RemoveChannel`; choose appropriate directory per project conventions.

### Hash `a75a592a5331e17a9b04fda333c9d220`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/sscanf` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/strings/sscanf` — 2KB
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/sscanf`; choose appropriate directory per project conventions.

### Hash `a8002df8e451b5adac6d40e4d3588dbe`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventDie` — 714B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/eventDie` — 714B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/bot/eventDie` — 714B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/combat/eventDie` — 714B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/flashlight/eventDie` — 714B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/npc/eventDie` — 714B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/player/eventDie` — 714B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/race/eventDie` — 714B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventDie`; choose appropriate directory per project conventions.

### Hash `a82ca12da75f625e5ca0024368b1c6db`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/shallow_inherit_list` — 436B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/shallow_inherit_list` — 436B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/shallow_inherit_list`; choose appropriate directory per project conventions.

### Hash `a89c233b8ea795172d90ef55c0819e6e`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/connect` — 622B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/connect` — 622B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/applies/connect`; choose appropriate directory per project conventions.

### Hash `a8ab43394f9d5144b4d7e2eadee64862`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/memory_summary` — 566B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/memory_summary` — 566B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/memory_summary`; choose appropriate directory per project conventions.

### Hash `a8b28951dc37e8996c2ef627f84754d8`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/privs_file` — 481B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/privs_file` — 481B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/applies/privs_file`; choose appropriate directory per project conventions.

### Hash `a8bccc376352d585a11566615c19edf7`
- `mud-references/deadsouls/ds3.8.2/lib/realms/template/area/armor/leather_boot_r.c` — 679B
- `mud-references/deadsouls/ds3.8.2/lib/realms/thurtea/area/armor/leather_boot_r.c` — 679B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/realms/template/area/armor/leather_boot_r.c` (belongs in `src/`); move others to backups or remove.

### Hash `a8bd51d7988a252eef09193697006468`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/interactive/net_dead` — 492B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/net_dead` — 492B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/applies/net_dead`; choose appropriate directory per project conventions.

### Hash `a90573d3ca059247561c451d06906ec5`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetAmmoType` — 429B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/clip/GetAmmoType` — 429B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/firearm/GetAmmoType` — 429B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/round/GetAmmoType` — 429B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/shell/GetAmmoType` — 429B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetAmmoType`; choose appropriate directory per project conventions.

### Hash `a97da629b098b75c294dffdc3e463904`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charles/bak2/fgreen` — 3B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charles/bak2/green_wins` — 3B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charles/bak2/fgreen`; choose appropriate directory per project conventions.

### Hash `aa0d3682fda7a28b79ecfc1f4ed14c5c`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventDestruct` — 879B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/bonus/eventDestruct` — 879B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/chat/eventDestruct` — 879B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/clean/eventDestruct` — 879B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/client/eventDestruct` — 879B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/connect/eventDestruct` — 879B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/daemon/eventDestruct` — 879B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/file/eventDestruct` — 879B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/ftp_client/eventDestruct` — 879B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/ftp_data_connection/eventDestruct` — 879B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/interactive/eventDestruct` — 879B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/meal/eventDestruct` — 879B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/npc/eventDestruct` — 879B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/server/eventDestruct` — 879B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventDestruct`; choose appropriate directory per project conventions.

### Hash `aa2cdb0c72af7d1dbe83b678f53aff38`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetAlcohol` — 317B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetAlcohol` — 317B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/race/GetAlcohol` — 317B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetAlcohol`; choose appropriate directory per project conventions.

### Hash `aa978a6224200c4b9da244a2e3f835d3`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/query_verb` — 498B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/parsing/query_verb` — 498B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/parsing/query_verb`; choose appropriate directory per project conventions.

### Hash `aaa5e20ade330ca12e187797dcebe88c`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetWielded` — 520B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetWielded` — 520B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/weapon/GetWielded` — 520B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetWielded`; choose appropriate directory per project conventions.

### Hash `ab934396723ecb5dfa5890f05a6f4375`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/opcprof` — 482B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/internals/opcprof` — 482B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/opcprof`; choose appropriate directory per project conventions.

### Hash `abb6a6db7fc4b623e31697c7f5f07171`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/nullp` — 215B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mixed/nullp` — 215B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/nullp`; choose appropriate directory per project conventions.

### Hash `abc665305bbe1c16d65f0a281f826a2e`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/valid_write` — 548B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/valid_write` — 548B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/applies/valid_write`; choose appropriate directory per project conventions.

### Hash `ac71d0123cfcc9f2515f12daf5896124`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/bufferp` — 218B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mixed/bufferp` — 218B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/bufferp`; choose appropriate directory per project conventions.

### Hash `adac9d6d094ba68ab6a2c5bbc6eced6c`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventLoad` — 543B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/clip/eventLoad` — 543B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/firearm/eventLoad` — 543B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/load/eventLoad` — 543B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/round/eventLoad` — 543B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventLoad`; choose appropriate directory per project conventions.

### Hash `ae27d8acebde2af5853f7db3a1273adb`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/lpc_info` — 301B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/lpc_info` — 301B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/lpc_info`; choose appropriate directory per project conventions.

### Hash `aeb782090160760aa4ec968d0eb64128`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/printf` — 3KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/printf` — 3KB
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/printf`; choose appropriate directory per project conventions.

### Hash `aed4aec48a84be776a2abe88c5e38cb1`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/valid_object` — 627B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/valid_object` — 627B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/applies/valid_object`; choose appropriate directory per project conventions.

### Hash `b074da73cb3aeeba047b254e98568cb1`
- `mud-references/deadsouls/ds3.8.2/lib/realms/template/plan` — 28B
- `mud-references/deadsouls/ds3.8.2/lib/realms/thurtea/.plan` — 28B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/realms/template/plan`; choose appropriate directory per project conventions.

### Hash `b0e11ca11ca0ec83890e6de5d0471d8b`
- `mud-references/deadsouls/ds3.8.2/lib/doc/help/players/channel` — 19B
- `mud-references/deadsouls/ds3.8.2/lib/doc/help/players/chat` — 19B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/help/players/chat`; choose appropriate directory per project conventions.

### Hash `b0e24802f13e852e45e942b03a31520a`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetStats` — 365B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/bonus/SetStats` — 365B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/potion/SetStats` — 365B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetStats`; choose appropriate directory per project conventions.

### Hash `b1b1ab341a697c5ba16ba3cb36bb7e49`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/creator_file` — 872B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/creator_file` — 872B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/applies/creator_file`; choose appropriate directory per project conventions.

### Hash `b1bb32797d3d43a9ca54325efc9763b2`
- `mud-references/deadsouls/ds3.8.2/lib/www/articles/favicon.ico` — 6KB
- `mud-references/deadsouls/ds3.8.2/lib/www/favicon.ico` — 6KB
- `mud-references/deadsouls/ds3.8.2/lib/www/lpmuds/favico.ico` — 6KB
- `mud-references/deadsouls/ds3.8.2/lib/www/lpmuds/favicon.ico` — 6KB
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/www/favicon.ico`; choose appropriate directory per project conventions.

### Hash `b23d6d783677e245b2668c80a9e035cc`
- `mud-references/deadsouls/ds3.8.2/lib/verbs/items/equate.c` — 4KB
- `mud-references/deadsouls/ds3.8.2/lib/verbs/items/judge1.c` — 4KB
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/verbs/items/judge1.c` (belongs in `src/`); move others to backups or remove.

### Hash `b2489618de8d331dab9d866d8a4374a4`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetCanBite` — 398B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/SetCanBite` — 398B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetCanBite`; choose appropriate directory per project conventions.

### Hash `b343541c3a07b63d18ad3314c4eecf6a`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/swap` — 549B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/internals/swap` — 549B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/swap`; choose appropriate directory per project conventions.

### Hash `b4496380ea041f1e3fc96f3feb4b88f6`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetHeat` — 259B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/burn/SetHeat` — 259B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetHeat`; choose appropriate directory per project conventions.

### Hash `b4cab45033104c39ace61ec54e154907`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetMoralityDescription` — 317B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/classes/GetMoralityDescription` — 317B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetMoralityDescription`; choose appropriate directory per project conventions.

### Hash `b4d9a3043a0aa46e24b9e1489fc0a05e`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/read_file` — 510B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/filesystem/read_file` — 510B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/read_file`; choose appropriate directory per project conventions.

### Hash `b53d5d150cf59d22eecdb8b08737b355`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/uptime` — 290B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/uptime` — 290B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/uptime`; choose appropriate directory per project conventions.

### Hash `b5432dd964c3d2f1b0f0a7bd65c2e921`
- `mud-references/deadsouls/ds3.8.2/bin/portbind` — 13KB
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/portbind` — 13KB
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/bin/portbind`; choose appropriate directory per project conventions.

### Hash `b5716eed266cfff3c6ee44dc93c4b4da`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetBurning` — 252B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/burn/GetBurning` — 252B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetBurning`; choose appropriate directory per project conventions.

### Hash `b5d8347e3de49a65f9a5f6fb1aa095d6`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/m_values` — 253B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mappings/m_values` — 253B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/m_values`; choose appropriate directory per project conventions.

### Hash `b5f943ba49ab7a3701850db5f53dde13`
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/testsuite/single/tests/efuns/generate_source.c` — 39B
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/testsuite/single/tests/efuns/get_char.c` — 39B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/testsuite/single/tests/efuns/get_char.c` (belongs in `src/`); move others to backups or remove.

### Hash `b6504ce6c6a46370fbee09b3f247e31c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/learning/room/wiz_hall.c` — 540B
- `mud-references/deadsouls/ds3.8.2/lib/std/wiz_hall.c` — 540B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/domains/learning/room/wiz_hall.c` (belongs in `src/`); move others to backups or remove.

### Hash `b687c3befe1eb33f31e1dbdaf2bc3401`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetDying` — 347B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetDying` — 347B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetDying`; choose appropriate directory per project conventions.

### Hash `b6a0cee39b914d7d3b8cb913a86ead39`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/shadow` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/calls/shadow` — 2KB
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/shadow`; choose appropriate directory per project conventions.

### Hash `b6c62ea291c6f54f4a8c2cd57a90f191`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/ed` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/ed` — 1KB
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/ed`; choose appropriate directory per project conventions.

### Hash `b6f195c9c9996d01e6c9957c3f069946`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/socket_listen` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/sockets/socket_listen` — 1KB
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/socket_listen`; choose appropriate directory per project conventions.

### Hash `b7ebbe0feb97cbc41203779fc0fd9881`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetFingers` — 198B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/armor/SetFingers` — 198B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/worn_storage/SetFingers` — 198B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetFingers`; choose appropriate directory per project conventions.

### Hash `b80f32d4ac636b6b9b006d35adecde28`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/notify_fail` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/notify_fail` — 1KB
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/notify_fail`; choose appropriate directory per project conventions.

### Hash `b969fa6ab5c24b89528d0e327cb07450`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/map_delete` — 760B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mappings/map_delete` — 760B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/map_delete`; choose appropriate directory per project conventions.

### Hash `b9b950e13916a1cbb0d68d000f6e5c79`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/CanReceive` — 595B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/clip/CanReceive` — 595B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/container/CanReceive` — 595B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/corpse/CanReceive` — 595B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/firearm/CanReceive` — 595B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/flashlight/CanReceive` — 595B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/furnace/CanReceive` — 595B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/holder/CanReceive` — 595B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/limb/CanReceive` — 595B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/npc/CanReceive` — 595B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/player/CanReceive` — 595B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/post_office/CanReceive` — 595B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/room/CanReceive` — 595B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/CanReceive`; choose appropriate directory per project conventions.

### Hash `ba072388d8bab14c409d2e8df3aac8fd`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/atan` — 235B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/floats/atan` — 235B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/floats/atan`; choose appropriate directory per project conventions.

### Hash `ba15a546b4b9b1f05e35532883e1e8e7`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/copy` — 488B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/general/copy` — 488B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/copy`; choose appropriate directory per project conventions.

### Hash `ba5ae241c1467e1f4d2cc3d0a9e1696c`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/tan` — 227B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/floats/tan` — 227B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/floats/tan`; choose appropriate directory per project conventions.

### Hash `ba9c1b1eca6711c1f7375e01e9ada955`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/read_buffer` — 844B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/buffers/read_buffer` — 844B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/buffers/read_buffer`; choose appropriate directory per project conventions.

### Hash `bb430d289ac78ca18df0ffd321e2aaf4`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventCollapse` — 267B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/eventCollapse` — 267B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventCollapse`; choose appropriate directory per project conventions.

### Hash `bb7df7795d1d113499da98e6eb739a55`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/refs` — 383B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/internals/refs` — 383B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/refs`; choose appropriate directory per project conventions.

### Hash `bc03444915cd651f42365e03a5972886`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetReligion` — 264B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/chapel/GetReligion` — 264B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/classes/GetReligion` — 264B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetReligion`; choose appropriate directory per project conventions.

### Hash `bc15f138b3af232c7facf43e7841a6e8`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/CanBurn` — 291B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/burn/CanBurn` — 291B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/CanBurn`; choose appropriate directory per project conventions.

### Hash `bc329e8d7330cb55912d6880e5b4612c`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetBonusDuration` — 351B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/bonus/SetBonusDuration` — 351B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetBonusDuration`; choose appropriate directory per project conventions.

### Hash `bc735b92ea9c3bf9d7a55f9fc9891716`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetClanName` — 255B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/clan/GetClanName` — 255B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetClanName`; choose appropriate directory per project conventions.

### Hash `bd422a5670d069042170cb519cb56cdb`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/check_memory` — 392B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/check_memory` — 392B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/check_memory`; choose appropriate directory per project conventions.

### Hash `bd8e6cdb6bf7a4c7716946ef586d0ec2`
- `mud-references/deadsouls/ds3.8.2/lib/daemon/weather.c` — 87B
- `mud-references/deadsouls/ds3.8.2/lib/secure/daemon/politics.c` — 87B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/secure/daemon/politics.c` (belongs in `src/`); move others to backups or remove.

### Hash `be5ed07fa0f125c001417aa5650a0af1`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventExtinguish` — 325B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/burn/eventExtinguish` — 325B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/flashlight/eventExtinguish` — 325B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventExtinguish`; choose appropriate directory per project conventions.

### Hash `befb91c18a96f7980eff4c2f63ef845f`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/capitalize` — 240B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/strings/capitalize` — 240B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/capitalize`; choose appropriate directory per project conventions.

### Hash `bf1f580d02fbc657d21a47c2c41b876e`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/receive` — 475B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/receive` — 475B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/receive`; choose appropriate directory per project conventions.

### Hash `bf92d9b380494c40e7a91678d5919676`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/origin` — 512B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/calls/origin` — 512B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/origin`; choose appropriate directory per project conventions.

### Hash `c027747081674f8d8949ef561e8f59cc`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/ClassMember` — 299B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/classes/ClassMember` — 299B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/ClassMember`; choose appropriate directory per project conventions.

### Hash `c0ce2cf43d3ea8b8fd5a35589e400c32`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/debugmalloc` — 619B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/internals/debugmalloc` — 619B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/debugmalloc`; choose appropriate directory per project conventions.

### Hash `c12affca27ede30a3a6903072d55b619`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/write` — 307B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/write` — 307B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/write`; choose appropriate directory per project conventions.

### Hash `c145e21867c9c26233bb84cb8e9ded26`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetPoints` — 325B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/bonus/GetPoints` — 325B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/potion/GetPoints` — 325B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetPoints`; choose appropriate directory per project conventions.

### Hash `c1cf9ffe12d404efc0e6ac8cbafa1f74`
- `mud-references/deadsouls/ds3.8.2/lib/realms/template/area/npc/fighter.c` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/realms/thurtea/area/npc/fighter.c` — 1KB
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/realms/template/area/npc/fighter.c` (belongs in `src/`); move others to backups or remove.

### Hash `c1d521aca85bd73fa275c8a4b8edae48`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/AddMagicProtection` — 610B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/AddMagicProtection` — 610B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/AddMagicProtection`; choose appropriate directory per project conventions.

### Hash `c1ff3f92d4bf4a176a760887cf8abba2`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/strcmp` — 692B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/strings/strcmp` — 692B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/strcmp`; choose appropriate directory per project conventions.

### Hash `c2030e4ade385e55d40e148f8bc1618a`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventWelcome` — 363B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/clan/eventWelcome` — 363B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventWelcome`; choose appropriate directory per project conventions.

### Hash `c246dd7c92a73bb1685518880709ca72`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/function_exists` — 738B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/function_exists` — 738B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/function_exists`; choose appropriate directory per project conventions.

### Hash `c2920b80768c55b560d5fc4531b1a272`
- `mud-references/deadsouls/ds3.8.2/lib/realms/template/area/room/sample_two.c` — 532B
- `mud-references/deadsouls/ds3.8.2/lib/realms/thurtea/area/room/sample_two.c` — 532B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/realms/template/area/room/sample_two.c` (belongs in `src/`); move others to backups or remove.

### Hash `c318cd77ba1c644427f180f20dc963bc`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/query_load_average` — 299B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/internals/query_load_average` — 299B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/query_load_average`; choose appropriate directory per project conventions.

### Hash `c32bca7cbeca84128222b75e91e6d6bc`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/lower_case` — 272B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/strings/lower_case` — 272B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/lower_case`; choose appropriate directory per project conventions.

### Hash `c3878d3527159a9208f6ada5e6edfa4c`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/find_object` — 364B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/objects/find_object` — 364B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/find_object`; choose appropriate directory per project conventions.

### Hash `c3b686d61e113161fdcdee36d7542139`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetResistance` — 350B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetResistance` — 350B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/genetics/GetResistance` — 350B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/race/GetResistance` — 350B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetResistance`; choose appropriate directory per project conventions.

### Hash `c4fc85e761a68f85ec7da600d329570a`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetClan` — 277B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/classes/SetClan` — 277B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetClan`; choose appropriate directory per project conventions.

### Hash `c5372160a33b9e30c05178914e0aa0c2`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/interactive/receive_message` — 561B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/receive_message` — 561B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/applies/receive_message`; choose appropriate directory per project conventions.

### Hash `c56032742ce6a143dcdf5070ec6a3ddf`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetFuelRequired` — 280B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/burn/GetFuelRequired` — 280B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetFuelRequired`; choose appropriate directory per project conventions.

### Hash `c5ccaf98c7194630ce842547981c62fd`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/asin` — 228B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/floats/asin` — 228B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/floats/asin`; choose appropriate directory per project conventions.

### Hash `c613dc41f17acda24e13030f6237df20`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/to_int` — 522B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/floats/to_int` — 522B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/floats/to_int`; choose appropriate directory per project conventions.

### Hash `c6466da35bf3294ad778113c9adc0b42`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/named_livings` — 388B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/named_livings` — 388B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/named_livings`; choose appropriate directory per project conventions.

### Hash `c6b56aa2cfad55be1629bba9d1c5c61f`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/get_dir` — 930B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/filesystem/get_dir` — 930B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/get_dir`; choose appropriate directory per project conventions.

### Hash `c6fdd8190df8c128463766c432876425`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/author_stats` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mudlib/author_stats` — 2KB
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/author_stats`; choose appropriate directory per project conventions.

### Hash `c7d899ca2e52811e71fe4f25a20f31ee`
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/doors/west.c` — 719B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/doors/down.c` — 719B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/doors/south.c` — 719B
- `mud-references/deadsouls/ds3.8.2/lib/obj/door.c` — 719B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/obj/door.c` (belongs in `src/`); move others to backups or remove.

### Hash `c9406b6c7024bb92ae0751cdc4e85f34`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/set_reset` — 495B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/set_reset` — 495B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/set_reset`; choose appropriate directory per project conventions.

### Hash `c993f181eb34b7796fc28c2644fe6cc5`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/commands` — 620B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/commands` — 620B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/commands`; choose appropriate directory per project conventions.

### Hash `ca2110d11d749737460221436a5eccd2`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventUnload` — 549B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/clip/eventUnload` — 549B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/firearm/eventUnload` — 549B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/load/eventUnload` — 549B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/round/eventUnload` — 549B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventUnload`; choose appropriate directory per project conventions.

### Hash `cad241addfd6dd52862705e9b23235d0`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/wizardp` — 334B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/wizardp` — 334B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/wizardp`; choose appropriate directory per project conventions.

### Hash `cb27c0ee5056ebc1e28b1504a7c1bace`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetClass` — 412B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/classes/SetClass` — 412B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/damage/SetClass` — 412B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/npc/SetClass` — 412B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/player/SetClass` — 412B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetClass`; choose appropriate directory per project conventions.

### Hash `cb928678529fff7db7f3ccd01a839646`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/set_hide` — 569B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/objects/set_hide` — 569B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/set_hide`; choose appropriate directory per project conventions.

### Hash `cbde7ab6140b139ac37eb8bd2e6ffa11`
- `mud-references/deadsouls/ds3.8.2/lib/realms/template/area/obj/watch.c` — 3KB
- `mud-references/deadsouls/ds3.8.2/lib/realms/thurtea/area/obj/watch.c` — 3KB
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/realms/template/area/obj/watch.c` (belongs in `src/`); move others to backups or remove.

### Hash `cbf50cb1322a84fc43b61e727713665e`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/call_out` — 883B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/calls/call_out` — 883B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/call_out`; choose appropriate directory per project conventions.

### Hash `cc2026f6da17328d5107ab48f176e56d`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/in_edit` — 326B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/in_edit` — 326B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/in_edit`; choose appropriate directory per project conventions.

### Hash `cc2dfabaad6fa3a1de1b6dab0a106e3f`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/catch` — 644B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/calls/catch` — 644B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/catch`; choose appropriate directory per project conventions.

### Hash `cc6383c1934085e78acc5b5e0789bcec`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/repeat_string` — 427B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/strings/repeat_string` — 427B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/repeat_string`; choose appropriate directory per project conventions.

### Hash `cd7c1e479ef481f358ae9a7cdbb66324`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/input_to` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/input_to` — 1KB
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/input_to`; choose appropriate directory per project conventions.

### Hash `cd88612b51673bcb6a837c647e3d281d`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/make_path_absolute` — 238B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/make_path_absolute` — 238B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/applies/make_path_absolute`; choose appropriate directory per project conventions.

### Hash `cdc1f6db93dc091809b4d70708047b03`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetMelee` — 380B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/SetMelee` — 380B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetMelee`; choose appropriate directory per project conventions.

### Hash `cdced6def99c18c3af42515899bbc03a`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/AddPoison` — 299B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/AddPoison` — 299B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/poison/AddPoison` — 299B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/AddPoison`; choose appropriate directory per project conventions.

### Hash `ce4733e33a8f21b6781f76cfd64a1a52`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetCellType` — 372B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/battery/GetCellType` — 372B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/flashlight/GetCellType` — 372B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetCellType`; choose appropriate directory per project conventions.

### Hash `cf44b416f721e5b51ad13c9e01c73df8`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetMorality` — 251B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/classes/GetMorality` — 251B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/spell/GetMorality` — 251B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetMorality`; choose appropriate directory per project conventions.

### Hash `cfad518faac20b536a76f52834fd6b83`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/parse_command_plural_id_list` — 361B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/parsing/parse_command_plural_id_list` — 361B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/applies/parse_command_plural_id_list`; choose appropriate directory per project conventions.

### Hash `cfcd208495d565ef66e7dff9f98764da`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charles/bak2/bak1/percent` — 1B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charles/bak2/percent` — 1B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charles/percent` — 1B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charly/bak/percent` — 1B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charly/percent` — 1B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charles/percent`; choose appropriate directory per project conventions.

### Hash `d01eb0b6381b2e78203ceb60101f536f`
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/virtual/server.c` — 778B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/virtual/server.c` — 778B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/domains/default/virtual/server.c` (belongs in `src/`); move others to backups or remove.

### Hash `d0adacd593e713901b6de65d63cc3420`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetCaffeine` — 305B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetCaffeine` — 305B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetCaffeine`; choose appropriate directory per project conventions.

### Hash `d1a07c5c726526733305eaaf2c27bd3f`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/inherit_list` — 406B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/inherit_list` — 406B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/inherit_list`; choose appropriate directory per project conventions.

### Hash `d1e9a0527af58109d0cee7ffabe0c3d3`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/ChangeClass` — 311B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/classes/ChangeClass` — 311B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/ChangeClass`; choose appropriate directory per project conventions.

### Hash `d26337bd28e7a8fc158cb4d8fc418381`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/ed_cmd` — 279B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/ed_cmd` — 279B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/ed_cmd`; choose appropriate directory per project conventions.

### Hash `d26e252c21284e8a898db487b532a517`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/acos` — 246B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/floats/acos` — 246B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/floats/acos`; choose appropriate directory per project conventions.

### Hash `d41d8cd98f00b204e9800998ecf8427e`
- `docs/duplicate-commands.txt` — 0B
- `docs/lpc-files-in-src.txt` — 0B
- `docs/potential-duplicate-rooms.txt` — 0B
- `lib/domains/forest/rooms/void.lpc` — 0B
- `lib/log/command_debug.log` — 0B
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/Dependencies` — 0B
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/files` — 0B
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/mallocwrapper.c` — 0B
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/packages/debug.h` — 0B
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/packages/debug_spec.c` — 0B
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/packages/dslib.c` — 0B
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/packages/dslib_spec.c` — 0B
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/testsuite/clone/readme` — 0B
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/testsuite/single/tests/efuns/has_errors.c` — 0B
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/testsuite/single/tests/efuns/inh0.c` — 0B
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/testsuite/single/tests/efuns/readme` — 0B
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/testsuite/test_control.c` — 0B
- `mud-references/deadsouls/ds3.8.2/lib/doc/build/ed.hup` — 0B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/socket_error.h` — 0B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/sockets/socket_error.h` — 0B
- `mud-references/deadsouls/log/runtime` — 0B
**Recommendation:** Canonical: `lib/domains/forest/rooms/void.lpc` (belongs in `lib/`); move others to backups or remove.

### Hash `d4c80892767b3a26a7e7ef3058441856`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/RemoveMagicProtection` — 363B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/RemoveMagicProtection` — 363B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/RemoveMagicProtection`; choose appropriate directory per project conventions.

### Hash `d4d9c8c517835cae9d2bb4a321e4fb13`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/objects` — 833B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/objects/objects` — 833B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/objects`; choose appropriate directory per project conventions.

### Hash `d4f1ea4f8690d7c86baa62cf42d3e62f`
- `lib/cmds/players/emote.c` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/cmds/players/emote.c` — 1KB
**Recommendation:** Canonical: `lib/cmds/players/emote.c` (belongs in `src/`); move others to backups or remove.

### Hash `d506bba74b8674e9628b4a3361f10d1b`
- `mud-references/deadsouls/ds3.8.2/lib/realms/template/evaldefs.h` — 315B
- `mud-references/deadsouls/ds3.8.2/lib/realms/thurtea/evaldefs.h` — 315B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/realms/template/evaldefs.h` (belongs in `src/`); move others to backups or remove.

### Hash `d586e968fcd29ed3cb66b50b26e0f752`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetMoJo` — 306B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetMoJo` — 306B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetMoJo`; choose appropriate directory per project conventions.

### Hash `d58c167c4cecf3d0ee4a91d9acbb5d95`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/checkCollapse` — 336B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/checkCollapse` — 336B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/checkCollapse`; choose appropriate directory per project conventions.

### Hash `d62a1205d5b383adeb427288b6042592`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/unique_mapping` — 463B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mappings/unique_mapping` — 463B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/unique_mapping`; choose appropriate directory per project conventions.

### Hash `d698a16ef748a7b9842b28f4baaa8803`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/socket_acquire` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/sockets/socket_acquire` — 1KB
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/socket_acquire`; choose appropriate directory per project conventions.

### Hash `d6bef9f8ee8de8df27755603fccaf76f`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/AddExperiencePoints` — 370B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/AddExperiencePoints` — 370B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/AddExperiencePoints`; choose appropriate directory per project conventions.

### Hash `d71314962ae9db0df3f7121307b007b7`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/obj/simple_chair.c` — 361B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/obj/simple_chair.c` — 361B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/domains/campus/obj/simple_chair.c` (belongs in `src/`); move others to backups or remove.

### Hash `d758d4015b7eaa18e841305c78039b00`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/AddSkillPoints` — 613B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/abilities/AddSkillPoints` — 613B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/classes/AddSkillPoints` — 613B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/AddSkillPoints`; choose appropriate directory per project conventions.

### Hash `d77b80f1484d7636e61e91ab627fc70e`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/exec` — 833B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/exec` — 833B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/exec`; choose appropriate directory per project conventions.

### Hash `d8c6c970963e420964a38b3f9e703ee7`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/obj/9mmclip.c` — 649B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/obj/clip.c` — 649B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/domains/campus/obj/clip.c` (belongs in `src/`); move others to backups or remove.

### Hash `d8d77109f4a24efc3bd53d7cabb7ee35`
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/insttest` — 9B
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/tmp/insttest` — 9B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/insttest`; choose appropriate directory per project conventions.

### Hash `d8f2fa1b300238a06b2fdc775fc28402`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetHeartRate` — 261B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetHeartRate` — 261B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/race/GetHeartRate` — 261B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetHeartRate`; choose appropriate directory per project conventions.

### Hash `d95ebce23a6e559c789983138cfefbab`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/TODO` — 905B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/parsing/TODO` — 905B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/parsing/TODO`; choose appropriate directory per project conventions.

### Hash `d9fb0fc846a4f1d7a074cf9043a6f399`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetClanName` — 302B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/clan/SetClanName` — 302B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetClanName`; choose appropriate directory per project conventions.

### Hash `db1312091c959458482b5f4cc425ae93`
- `mud-references/deadsouls/ds3.8.2/lib/realms/template/cmds/custom.c` — 118B
- `mud-references/deadsouls/ds3.8.2/lib/realms/thurtea/cmds/custom.c` — 118B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/realms/template/cmds/custom.c` (belongs in `src/`); move others to backups or remove.

### Hash `dc50cb3321df57d550e46a4022c631bc`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/sqrt` — 332B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/floats/sqrt` — 332B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/floats/sqrt`; choose appropriate directory per project conventions.

### Hash `dc905072ba8e4c04ff4086ca5b3293ca`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/allocate` — 264B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/arrays/allocate` — 264B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/allocate`; choose appropriate directory per project conventions.

### Hash `dd74e41e1b9e4d95fc4f0fd69061f0f5`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/reg_assoc` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/strings/reg_assoc` — 2KB
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/reg_assoc`; choose appropriate directory per project conventions.

### Hash `dd8080d40e2bbd11ff2b9872ba0c103e`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetRandomLimb` — 304B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetRandomLimb` — 304B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetRandomLimb`; choose appropriate directory per project conventions.

### Hash `ddcadd40043eab174857e03a61278132`
- `mud-references/deadsouls/ds3.8.2/lib/www/lpmuds/index.html` — 7KB
- `mud-references/deadsouls/ds3.8.2/lib/www/lpmuds/index.php` — 7KB
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/www/lpmuds/index.html`; choose appropriate directory per project conventions.

### Hash `de30a07094f9b905e705d37ef4c5dce1`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/functions` — 892B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/functions` — 892B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/functions`; choose appropriate directory per project conventions.

### Hash `df653d48b4e1d742efa9103781e8f575`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/pointerp` — 192B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mixed/pointerp` — 192B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/pointerp`; choose appropriate directory per project conventions.

### Hash `e001d41c7dbca6bd66b08a2626cff6d9`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/remove_interactive` — 457B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/remove_interactive` — 457B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/remove_interactive`; choose appropriate directory per project conventions.

### Hash `e04e2a8cfdddf217e098e56dcd342389`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/filter_mapping` — 341B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mappings/filter_mapping` — 341B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/filter_mapping`; choose appropriate directory per project conventions.

### Hash `e04fb1db1221de3871de8afd1e45a234`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetEncumbrance` — 489B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetEncumbrance` — 489B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetEncumbrance`; choose appropriate directory per project conventions.

### Hash `e054494a50d69e935ad469dd41be6f29`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/armor/cap.c` — 546B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/armor/cap.c` — 546B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/domains/campus/armor/cap.c` (belongs in `src/`); move others to backups or remove.

### Hash `e0d6925a932cfcce02341af1f14009a6`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/CanFly` — 466B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/CanFly` — 466B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/room/CanFly` — 466B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/virt_sky/CanFly` — 466B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/CanFly`; choose appropriate directory per project conventions.

### Hash `e0eeaf96e167e9604907968ce0b94d40`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/heart_beats` — 344B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/objects/heart_beats` — 344B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/heart_beats`; choose appropriate directory per project conventions.

### Hash `e11726d60179a7442fbcc4dc6650d22c`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/restore_variable` — 314B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/general/restore_variable` — 314B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/restore_variable`; choose appropriate directory per project conventions.

### Hash `e257646ea8caa3c3fab6e782aa35b509`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/room/death.c` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/room/death.c` — 2KB
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/domains/campus/room/death.c` (belongs in `src/`); move others to backups or remove.

### Hash `e26b04c6d51c9d94c308c15513efab54`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/debug_info` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/internals/debug_info` — 2KB
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/debug_info`; choose appropriate directory per project conventions.

### Hash `e28b963f4937446c6d78666920079419`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/destruct` — 523B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/objects/destruct` — 523B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/destruct`; choose appropriate directory per project conventions.

### Hash `e2b5d2dfbc45aab4a9ea947b6d21253b`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetSacrificeType` — 412B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/chapel/SetSacrificeType` — 412B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetSacrificeType`; choose appropriate directory per project conventions.

### Hash `e2eaec58fb55b38dcfb3fcead02808cd`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetBonuses` — 305B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/bonus/SetBonuses` — 305B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetBonuses`; choose appropriate directory per project conventions.

### Hash `e332d4aa2f0280f654f0a520ab751a7e`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/AddDrink` — 289B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/AddDrink` — 289B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/AddDrink`; choose appropriate directory per project conventions.

### Hash `e4121d0ad96eb14b70c7828b9f0a7490`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/cos` — 309B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/floats/cos` — 309B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/floats/cos`; choose appropriate directory per project conventions.

### Hash `e4161bdd57e6553cada20129d2cd5610`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/ctime` — 282B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/ctime` — 282B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/ctime`; choose appropriate directory per project conventions.

### Hash `e424f5ed6d221bdf6f0fdb0cc3114b45`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/sizeof` — 269B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/general/sizeof` — 269B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/sizeof`; choose appropriate directory per project conventions.

### Hash `e46783167acf8891bcf43dc10af638b0`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/CanWear` — 557B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/CanWear` — 557B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/CanWear`; choose appropriate directory per project conventions.

### Hash `e4c3f9e9ca4b9214253bc647226eafba`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/armor/workboot_r.c` — 663B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/armor/workboot_r.c` — 663B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/domains/campus/armor/workboot_r.c` (belongs in `src/`); move others to backups or remove.

### Hash `e72a43d4c26115d165fa5b9c003c0d54`
- `mud-references/deadsouls/ds3.8.2/lib/domains/cave/armor/pants.c` — 561B
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/armor/pants.c` — 561B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/domains/default/armor/pants.c` (belongs in `src/`); move others to backups or remove.

### Hash `e880885b2ac488553e9937c4673835b0`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/implode` — 712B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/strings/implode` — 712B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/implode`; choose appropriate directory per project conventions.

### Hash `ea0936da70690648218dd6e5767a9f35`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/values` — 466B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mappings/values` — 466B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/values`; choose appropriate directory per project conventions.

### Hash `ea0b7ff8b46b4fc097d96dac1da3dcde`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetPacifist` — 360B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetPacifist` — 360B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetPacifist`; choose appropriate directory per project conventions.

### Hash `eb78fb744dee376c942f426f1318b31b`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetClanObject` — 294B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/clan/GetClanObject` — 294B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetClanObject`; choose appropriate directory per project conventions.

### Hash `eb9482738700be6a50ce3a8bd919b2a0`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/keys` — 554B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mappings/keys` — 554B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/keys`; choose appropriate directory per project conventions.

### Hash `ebcd06f6988d14778efa0a4a6471125d`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventReceiveThrow` — 323B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/eventReceiveThrow` — 323B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventReceiveThrow`; choose appropriate directory per project conventions.

### Hash `ebde4aadc79e63afe9244844bf3d2f96`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/present` — 643B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/objects/present` — 643B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/present`; choose appropriate directory per project conventions.

### Hash `eceda4b1a0a4e45f8c11cb7b7d60ee33`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventUse` — 426B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/battery/eventUse` — 426B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/flashlight/eventUse` — 426B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/player/eventUse` — 426B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventUse`; choose appropriate directory per project conventions.

### Hash `eda67e9ad3f7b21056a005d4c580bb2e`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/functionp` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mixed/functionp` — 1KB
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/functionp`; choose appropriate directory per project conventions.

### Hash `eddce88e196836d99021f64df9a5026f`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/retrieve_ed_setup` — 304B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/retrieve_ed_setup` — 304B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/applies/retrieve_ed_setup`; choose appropriate directory per project conventions.

### Hash `edf0351cb65845a1efcc869f66781118`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/time` — 271B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/time` — 271B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/time`; choose appropriate directory per project conventions.

### Hash `ee0a0f774fa43daec35352036b9b96a9`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetMaxStaminaPoints` — 396B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetMaxStaminaPoints` — 396B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/race/GetMaxStaminaPoints` — 396B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetMaxStaminaPoints`; choose appropriate directory per project conventions.

### Hash `eeb0821dfe8b7e7759415b43dc8f5d4e`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetExperiencePoints` — 269B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetExperiencePoints` — 269B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetExperiencePoints`; choose appropriate directory per project conventions.

### Hash `eefabaa3c6dfbf72e4a396bc918bb918`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/set_eval_limit` — 477B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/set_eval_limit` — 477B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/set_eval_limit`; choose appropriate directory per project conventions.

### Hash `f08ccf999cda8b28ed77c77a8debb7ff`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/tell_object` — 386B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/objects/tell_object` — 386B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/tell_object`; choose appropriate directory per project conventions.

### Hash `f0baae8ec53611db60a0a427fd2e835b`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetDeathEvents` — 463B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/SetDeathEvents` — 463B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetDeathEvents`; choose appropriate directory per project conventions.

### Hash `f2385a50da960516d7eef4e578022cd9`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/interactive/telnet_suboption` — 687B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/telnet_suboption` — 687B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/applies/telnet_suboption`; choose appropriate directory per project conventions.

### Hash `f2938c68f2308a73baea97d97c2553fe`
- `mud-references/deadsouls/ds3.8.2/lib/daemon/tmp/foo.txt` — 36B
- `mud-references/deadsouls/ds3.8.2/lib/estates/foo.txt` — 36B
- `mud-references/deadsouls/ds3.8.2/lib/ftp/foo.txt` — 36B
- `mud-references/deadsouls/ds3.8.2/lib/log/adm/foo.txt` — 36B
- `mud-references/deadsouls/ds3.8.2/lib/log/archive/foo.txt` — 36B
- `mud-references/deadsouls/ds3.8.2/lib/log/chan/foo.txt` — 36B
- `mud-references/deadsouls/ds3.8.2/lib/log/errors/foo.txt` — 36B
- `mud-references/deadsouls/ds3.8.2/lib/log/law/adm/foo.txt` — 36B
- `mud-references/deadsouls/ds3.8.2/lib/log/law/email/foo.txt` — 36B
- `mud-references/deadsouls/ds3.8.2/lib/log/law/names/foo.txt` — 36B
- `mud-references/deadsouls/ds3.8.2/lib/log/law/sites-misc/foo.txt` — 36B
- `mud-references/deadsouls/ds3.8.2/lib/log/law/sites-register/foo.txt` — 36B
- `mud-references/deadsouls/ds3.8.2/lib/log/law/sites-tempban/foo.txt` — 36B
- `mud-references/deadsouls/ds3.8.2/lib/log/law/sites-watch/foo.txt` — 36B
- `mud-references/deadsouls/ds3.8.2/lib/log/open/foo.txt` — 36B
- `mud-references/deadsouls/ds3.8.2/lib/log/reports/foo.txt` — 36B
- `mud-references/deadsouls/ds3.8.2/lib/log/router/foo.txt` — 36B
- `mud-references/deadsouls/ds3.8.2/lib/log/secure/foo.txt` — 36B
- `mud-references/deadsouls/ds3.8.2/lib/log/watch/foo.txt` — 36B
- `mud-references/deadsouls/ds3.8.2/lib/secure/log/adm/foo.txt` — 36B
- `mud-references/deadsouls/ds3.8.2/lib/secure/log/bak/foo.txt` — 36B
- `mud-references/deadsouls/ds3.8.2/lib/secure/log/intermud/foo.txt` — 36B
- `mud-references/deadsouls/ds3.8.2/lib/secure/log/network/foo.txt` — 36B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/secure/log/adm/foo.txt`; choose appropriate directory per project conventions.

### Hash `f3cad51142a85739f68a70c60bd8152e`
- `mud-references/deadsouls/ds3.8.2/lib/obj/deed.c` — 450B
- `mud-references/deadsouls/ds3.8.2/lib/obj/order.c` — 450B
- `mud-references/deadsouls/ds3.8.2/lib/obj/thing.c` — 450B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/obj/order.c` (belongs in `src/`); move others to backups or remove.

### Hash `f3f0ad5fd1d78623c3ff14043d8e2d60`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/obj/45round.c` — 494B
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/obj/45round.c` — 494B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/domains/campus/obj/45round.c` (belongs in `src/`); move others to backups or remove.

### Hash `f4809d47f36b9f6d2f6296805c5d42bd`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetCellType` — 411B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/battery/SetCellType` — 411B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/flashlight/SetCellType` — 411B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetCellType`; choose appropriate directory per project conventions.

### Hash `f500f49bec5031d843f8f933b44a6437`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/new` — 309B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/objects/new` — 309B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/new`; choose appropriate directory per project conventions.

### Hash `f522234ab951b88888d43f91a6f1709b`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetMelee` — 327B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetMelee` — 327B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetMelee`; choose appropriate directory per project conventions.

### Hash `f58def1963c872d815582f33a669fe4c`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/crash` — 637B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/crash` — 637B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/applies/crash`; choose appropriate directory per project conventions.

### Hash `f637d6986eb2e072571aae9790b690b9`
- `mud-references/deadsouls/ds3.8.2/lib/realms/template/profile` — 21B
- `mud-references/deadsouls/ds3.8.2/lib/realms/thurtea/.profile` — 21B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/realms/template/profile`; choose appropriate directory per project conventions.

### Hash `f71120bb64673d6c610318bc2099ec0e`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/query_ip_port` — 541B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/query_ip_port` — 541B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/query_ip_port`; choose appropriate directory per project conventions.

### Hash `f7438590da31cd68731bde1ca1211260`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventMarry` — 301B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/chapel/eventMarry` — 301B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/interactive/eventMarry` — 301B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventMarry`; choose appropriate directory per project conventions.

### Hash `f773f3550053d158844a804be93632cb`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/log` — 236B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/floats/log` — 236B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/floats/log`; choose appropriate directory per project conventions.

### Hash `f890787fe0e1f55007e0865d929af6a6`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetMaxHealthPoints` — 459B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetMaxHealthPoints` — 459B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/combat/GetMaxHealthPoints` — 459B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/living/GetMaxHealthPoints` — 459B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/npc/GetMaxHealthPoints` — 459B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/race/GetMaxHealthPoints` — 459B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetMaxHealthPoints`; choose appropriate directory per project conventions.

### Hash `f8e2e9648c401541e91fa38ad4d5b771`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/AddHeartModifier` — 392B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/AddHeartModifier` — 392B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/AddHeartModifier`; choose appropriate directory per project conventions.

### Hash `f99fe7a7fe6888e2b5f0222acdbb8a50`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/remove_action` — 543B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/remove_action` — 543B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/remove_action`; choose appropriate directory per project conventions.

### Hash `f9b4f3252e4a1f3f2987019ecb7c5982`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/seteuid` — 568B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mudlib/seteuid` — 568B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/seteuid`; choose appropriate directory per project conventions.

### Hash `f9e9894a6b2269535ac12163ed32582f`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/AddMoJo` — 308B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/AddMoJo` — 308B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/AddMoJo`; choose appropriate directory per project conventions.

### Hash `fa2d8ca24697726e2423fce8f3f1e773`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/set_heart_beat` — 638B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/objects/set_heart_beat` — 638B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/set_heart_beat`; choose appropriate directory per project conventions.

### Hash `fa50346abba2827447fba156ee3b5bb2`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/valid_hide` — 642B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/valid_hide` — 642B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/applies/valid_hide`; choose appropriate directory per project conventions.

### Hash `fbe41eff690e838c4d5210c9e48e79dd`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/file_size` — 290B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/filesystem/file_size` — 290B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/file_size`; choose appropriate directory per project conventions.

### Hash `fc1c9b32d984c321fc44c9eb90d952d8`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/restore_object` — 504B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/objects/restore_object` — 504B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/restore_object`; choose appropriate directory per project conventions.

### Hash `fca6b1b16a2b6a3179fc4a0c7941c439`
- `mud-references/deadsouls/ds3.8.2/lib/realms/template/adm/remote.c` — 77B
- `mud-references/deadsouls/ds3.8.2/lib/realms/thurtea/adm/remote.c` — 77B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/realms/template/adm/remote.c` (belongs in `src/`); move others to backups or remove.

### Hash `fccaa4ab8f04f988c994ae9bbf8e2099`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/typeof` — 451B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/general/typeof` — 451B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/typeof`; choose appropriate directory per project conventions.

### Hash `fd22d8385da295324cd18f0fc4a8df0c`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/AddFingers` — 440B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/AddFingers` — 440B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/AddFingers`; choose appropriate directory per project conventions.

### Hash `fd31b0f1e73508f3ad4bd42c4eced83e`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/living` — 349B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mudlib/living` — 349B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/living`; choose appropriate directory per project conventions.

### Hash `fd6a513213d3eaa37dc784e3d67ea80b`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/dump_file_descriptors` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/internals/dump_file_descriptors` — 1KB
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/dump_file_descriptors`; choose appropriate directory per project conventions.

### Hash `fdb33fe0b9716c8444e41e147cfd75cd`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventFall` — 324B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/eventFall` — 324B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/position/eventFall` — 324B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventFall`; choose appropriate directory per project conventions.

### Hash `fed23ef0ec8e55f7e26c955861028bcd`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/valid_override` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/valid_override` — 1KB
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/doc/applies/valid_override`; choose appropriate directory per project conventions.

### Hash `ff252b1ac8a56b2b97f04f95f7e3a1d0`
- `mud-references/deadsouls/ds3.8.2/lib/realms/template/area/obj/key.c` — 375B
- `mud-references/deadsouls/ds3.8.2/lib/realms/thurtea/area/obj/key.c` — 375B
**Recommendation:** Canonical: `mud-references/deadsouls/ds3.8.2/lib/realms/template/area/obj/key.c` (belongs in `src/`); move others to backups or remove.

## Section 3: Likely Duplicates (Same Name + Same Size)

### `357round.c` — 469B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/obj/357round.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/obj/357round.c`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `45round.c` — 494B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/obj/45round.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/obj/45round.c`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `9mil.c` — 590B
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/weap/9mil.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/weap/9mil.c`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `9mmround.c` — 442B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/obj/9mmround.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/obj/9mmround.c`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `AddAlcohol` — 290B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/AddAlcohol`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/AddAlcohol`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `AddCaffeine` — 355B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/AddCaffeine`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/AddCaffeine`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `AddChannel` — 320B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/AddChannel`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/chat/AddChannel`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `AddDrink` — 289B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/AddDrink`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/AddDrink`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `AddExperiencePoints` — 370B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/AddExperiencePoints`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/AddExperiencePoints`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `AddExtraChannels` — 440B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/AddExtraChannels`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/AddExtraChannels`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `AddFingers` — 440B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/AddFingers`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/AddFingers`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `AddFood` — 286B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/AddFood`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/AddFood`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `AddHP` — 268B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/AddHP`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/AddHP`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `AddHealthPoints` — 813B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/AddHealthPoints`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/AddHealthPoints`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/player/AddHealthPoints`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `AddHeartModifier` — 392B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/AddHeartModifier`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/AddHeartModifier`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `AddLead` — 271B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/AddLead`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/AddLead`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `AddLimb` — 878B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/AddLimb`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/AddLimb`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `AddMagicPoints` — 299B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/AddMagicPoints`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/AddMagicPoints`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `AddMagicProtection` — 610B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/AddMagicProtection`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/AddMagicProtection`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `AddMoJo` — 308B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/AddMoJo`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/AddMoJo`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `AddPoison` — 299B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/AddPoison`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/AddPoison`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/poison/AddPoison`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `AddQuestPoints` — 324B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/AddQuestPoints`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/AddQuestPoints`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `AddSacrificeType` — 421B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/AddSacrificeType`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/chapel/AddSacrificeType`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `AddSkillPoints` — 613B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/AddSkillPoints`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/abilities/AddSkillPoints`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/classes/AddSkillPoints`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `CanBurn` — 291B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/CanBurn`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/burn/CanBurn`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `CanExtinguish` — 309B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/CanExtinguish`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/burn/CanExtinguish`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `CanFly` — 466B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/CanFly`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/CanFly`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/room/CanFly`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/virt_sky/CanFly`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `CanJoin` — 328B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/CanJoin`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/clan/CanJoin`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `CanLight` — 190B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/CanLight`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/light/CanLight`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `CanManipulate` — 443B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/CanManipulate`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/CanManipulate`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/manipulate/CanManipulate`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `CanMarry` — 379B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/CanMarry`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/chapel/CanMarry`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/interactive/CanMarry`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `CanReceive` — 595B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/CanReceive`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/clip/CanReceive`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/container/CanReceive`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/corpse/CanReceive`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/firearm/CanReceive`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/flashlight/CanReceive`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/furnace/CanReceive`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/holder/CanReceive`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/limb/CanReceive`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/npc/CanReceive`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/player/CanReceive`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/post_office/CanReceive`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/room/CanReceive`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `CanRelease` — 477B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/CanRelease`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/clip/CanRelease`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/container/CanRelease`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/firearm/CanRelease`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/fishing/CanRelease`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `CanRemoveItem` — 354B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/CanRemoveItem`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/CanRemoveItem`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `CanSacrifice` — 457B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/CanSacrifice`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/chapel/CanSacrifice`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `CanWear` — 557B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/CanWear`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/CanWear`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `ChangeClass` — 311B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/ChangeClass`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/classes/ChangeClass`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `ClassMember` — 299B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/ClassMember`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/classes/ClassMember`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `DestLimb` — 473B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/DestLimb`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/DestLimb`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `GetAffectLong` — 445B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetAffectLong`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetAffectLong`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/clan/GetAffectLong`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `GetAlcohol` — 317B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetAlcohol`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetAlcohol`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/race/GetAlcohol`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `GetAllowSacrifice` — 386B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetAllowSacrifice`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/chapel/GetAllowSacrifice`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `GetAmmoType` — 429B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetAmmoType`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/clip/GetAmmoType`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/firearm/GetAmmoType`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/round/GetAmmoType`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/shell/GetAmmoType`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `GetBaseStatLevel` — 434B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetBaseStatLevel`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/classes/GetBaseStatLevel`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/combat/GetBaseStatLevel`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/genetics/GetBaseStatLevel`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `GetBodyComposition` — 309B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetBodyComposition`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetBodyComposition`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `GetBonusDuration` — 310B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetBonusDuration`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/bonus/GetBonusDuration`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `GetBurnRate` — 261B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetBurnRate`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/burn/GetBurnRate`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/lamp/GetBurnRate`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `GetBurning` — 252B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetBurning`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/burn/GetBurning`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `GetBurntValue` — 277B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetBurntValue`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/burn/GetBurntValue`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `GetCaffeine` — 305B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetCaffeine`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetCaffeine`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `GetCaliber` — 410B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetCaliber`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/clip/GetCaliber`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/firearm/GetCaliber`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/round/GetCaliber`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/shell/GetCaliber`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `GetCanBite` — 329B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetCanBite`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetCanBite`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `GetCapName` — 294B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetCapName`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetCapName`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/connect/GetCapName`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/id/GetCapName`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/npc/GetCapName`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/player/GetCapName`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `GetCellType` — 372B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetCellType`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/battery/GetCellType`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/flashlight/GetCellType`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `GetChannels` — 327B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetChannels`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/chat/GetChannels`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `GetCharge` — 318B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetCharge`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/battery/GetCharge`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `GetClan` — 243B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetClan`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/classes/GetClan`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `GetClanName` — 255B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetClanName`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/clan/GetClanName`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `GetClanObject` — 294B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetClanObject`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/clan/GetClanObject`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `GetClanSkill` — 276B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetClanSkill`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/clan/GetClanSkill`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `GetClass` — 260B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetClass`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/classes/GetClass`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/damage/GetClass`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `GetDeathEvents` — 459B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetDeathEvents`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetDeathEvents`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `GetDrainRate` — 328B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetDrainRate`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/battery/GetDrainRate`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `GetDrainable` — 288B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetDrainable`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/battery/GetDrainable`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `GetDrink` — 224B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetDrink`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetDrink`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `GetDying` — 347B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetDying`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetDying`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `GetEncumbrance` — 489B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetEncumbrance`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetEncumbrance`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `GetEquippedLimbs` — 326B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetEquippedLimbs`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetEquippedLimbs`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `GetExperiencePoints` — 269B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetExperiencePoints`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetExperiencePoints`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `GetExtraChannels` — 440B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetExtraChannels`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetExtraChannels`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `GetFingers` — 427B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetFingers`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/armor/GetFingers`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetFingers`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/worn_storage/GetFingers`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `GetFirearmType` — 432B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetFirearmType`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/clip/GetFirearmType`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/firearm/GetFirearmType`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/round/GetFirearmType`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/shell/GetFirearmType`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `GetFood` — 368B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetFood`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetFood`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/fish/GetFood`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `GetFuelRequired` — 280B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetFuelRequired`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/burn/GetFuelRequired`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `GetHealRate` — 243B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetHealRate`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetHealRate`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/race/GetHealRate`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `GetHealthPoints` — 396B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetHealthPoints`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetHealthPoints`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `GetHealthShort` — 302B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetHealthShort`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetHealthShort`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/corpse/GetHealthShort`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `GetHeartModifier` — 417B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetHeartModifier`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetHeartModifier`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `GetHeartRate` — 261B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetHeartRate`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetHeartRate`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/race/GetHeartRate`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `GetHeat` — 250B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetHeat`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/burn/GetHeat`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `GetLead` — 363B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetLead`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetLead`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `GetLeader` — 359B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetLeader`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/clan/GetLeader`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/follow/GetLeader`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `GetLimbChildren` — 368B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetLimbChildren`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetLimbChildren`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `GetLimbClass` — 343B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetLimbClass`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetLimbClass`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `GetLimbParent` — 345B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetLimbParent`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetLimbParent`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `GetLimbs` — 243B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetLimbs`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetLimbs`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `GetLong` — 502B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetLong`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetLong`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/bot/GetLong`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/creator/GetLong`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/donate/GetLong`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/door/GetLong`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/fuel/GetLong`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/interactive/GetLong`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/lamp/GetLong`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/look/GetLong`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/npc/GetLong`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/player/GetLong`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/room/GetLong`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/torch/GetLong`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `GetMagicPoints` — 297B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetMagicPoints`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetMagicPoints`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `GetMaxHealthPoints` — 459B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetMaxHealthPoints`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetMaxHealthPoints`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/combat/GetMaxHealthPoints`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/living/GetMaxHealthPoints`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/npc/GetMaxHealthPoints`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/race/GetMaxHealthPoints`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `GetMaxMagicPoints` — 396B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetMaxMagicPoints`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetMaxMagicPoints`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/race/GetMaxMagicPoints`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `GetMaxStaminaPoints` — 396B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetMaxStaminaPoints`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetMaxStaminaPoints`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/race/GetMaxStaminaPoints`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `GetMelee` — 327B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetMelee`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetMelee`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `GetMillimeter` — 415B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetMillimeter`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/clip/GetMillimeter`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/firearm/GetMillimeter`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/round/GetMillimeter`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/shell/GetMillimeter`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `GetMinHeat` — 292B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetMinHeat`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/burn/GetMinHeat`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `GetMissingLimbParent` — 356B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetMissingLimbParent`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetMissingLimbParent`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `GetMissingLimbParents` — 364B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetMissingLimbParents`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetMissingLimbParents`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `GetMissingLimbs` — 440B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetMissingLimbs`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetMissingLimbs`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `GetMoJo` — 306B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetMoJo`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetMoJo`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `GetMorality` — 251B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetMorality`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/classes/GetMorality`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/spell/GetMorality`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `GetMoralityDescription` — 317B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetMoralityDescription`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/classes/GetMoralityDescription`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `GetName` — 369B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetName`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetName`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/creator/GetName`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/id/GetName`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/interactive/GetName`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/messages/GetName`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/npc/GetName`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/player/GetName`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `GetNoChanColors` — 319B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetNoChanColors`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/chat/GetNoChanColors`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `GetPacifist` — 360B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetPacifist`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetPacifist`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `GetPoints` — 325B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetPoints`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/bonus/GetPoints`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/potion/GetPoints`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `GetPoison` — 256B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetPoison`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetPoison`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/poison/GetPoison`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `GetProtect` — 306B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetProtect`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetProtect`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `GetQuestPoints` — 273B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetQuestPoints`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetQuestPoints`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `GetRace` — 324B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetRace`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetRace`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/corpse/GetRace`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/limb/GetRace`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/race/GetRace`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `GetRandomLimb` — 304B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetRandomLimb`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetRandomLimb`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `GetRechargeable` — 304B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetRechargeable`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/battery/GetRechargeable`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `GetReligion` — 264B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetReligion`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/chapel/GetReligion`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/classes/GetReligion`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `GetResistance` — 350B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetResistance`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetResistance`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/genetics/GetResistance`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/race/GetResistance`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `GetRestrictedChannels` — 315B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetRestrictedChannels`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/chat/GetRestrictedChannels`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `GetSacrificeType` — 418B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetSacrificeType`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/chapel/GetSacrificeType`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `GetSkillModifier` — 323B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetSkillModifier`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/classes/GetSkillModifier`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `GetSkills` — 702B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetSkills`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/abilities/GetSkills`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/bonus/GetSkills`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/potion/GetSkills`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/spell/GetSkills`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `GetSleeping` — 415B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetSleeping`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetSleeping`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `GetStaminaPoints` — 293B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetStaminaPoints`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetStaminaPoints`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `GetStats` — 630B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetStats`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/bonus/GetStats`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/genetics/GetStats`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/potion/GetStats`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `GetTorso` — 320B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetTorso`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetTorso`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `GetWielded` — 520B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetWielded`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetWielded`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/weapon/GetWielded`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `GetWieldingLimbs` — 470B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetWieldingLimbs`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetWieldingLimbs`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `GetWorn` — 588B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/GetWorn`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/GetWorn`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/equip/GetWorn`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `HandleTeller` — 557B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/HandleTeller`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/bank/HandleTeller`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `HealLimb` — 282B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/HealLimb`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/HealLimb`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `InitComposition` — 311B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/InitComposition`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/clay/InitComposition`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `ModCharge` — 315B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/ModCharge`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/battery/ModCharge`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `NewBody` — 303B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/NewBody`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/NewBody`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/race/NewBody`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `ParseHook` — 328B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/ParseHook`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/ParseHook`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `README` — 472B
- `mud-references/deadsouls/ds3.8.2/lib/domains/Praxis/adm/README`
- `mud-references/deadsouls/ds3.8.2/lib/domains/Ylsrim/adm/README`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/adm/README`
- `mud-references/deadsouls/ds3.8.2/lib/domains/cave/adm/README`
- `mud-references/deadsouls/ds3.8.2/lib/domains/learning/adm/README`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `RemoveBonuses` — 255B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/RemoveBonuses`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/bonus/RemoveBonuses`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `RemoveChannel` — 338B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/RemoveChannel`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/chat/RemoveChannel`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `RemoveExtraChannels` — 468B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/RemoveExtraChannels`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/RemoveExtraChannels`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `RemoveLimb` — 486B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/RemoveLimb`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/RemoveLimb`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `RemoveMagicProtection` — 363B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/RemoveMagicProtection`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/RemoveMagicProtection`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `RestoreLimb` — 798B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/RestoreLimb`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/RestoreLimb`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `RestrictChannel` — 335B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/RestrictChannel`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/chat/RestrictChannel`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `SetAllowSacrifice` — 388B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetAllowSacrifice`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/chapel/SetAllowSacrifice`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `SetAmmoType` — 445B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetAmmoType`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/clip/SetAmmoType`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/firearm/SetAmmoType`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/round/SetAmmoType`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/shell/SetAmmoType`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `SetBodyComposition` — 452B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetBodyComposition`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/SetBodyComposition`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `SetBonusDuration` — 351B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetBonusDuration`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/bonus/SetBonusDuration`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `SetBonuses` — 305B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetBonuses`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/bonus/SetBonuses`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `SetBurnRate` — 365B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetBurnRate`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/burn/SetBurnRate`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/lamp/SetBurnRate`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `SetCaliber` — 468B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetCaliber`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/clip/SetCaliber`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/firearm/SetCaliber`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/round/SetCaliber`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/shell/SetCaliber`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `SetCanBite` — 398B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetCanBite`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/SetCanBite`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `SetCellType` — 411B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetCellType`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/battery/SetCellType`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/flashlight/SetCellType`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `SetCharge` — 338B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetCharge`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/battery/SetCharge`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `SetClan` — 277B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetClan`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/classes/SetClan`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `SetClanName` — 302B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetClanName`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/clan/SetClanName`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `SetClanObject` — 323B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetClanObject`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/clan/SetClanObject`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `SetClanSkill` — 272B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetClanSkill`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/clan/SetClanSkill`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `SetClass` — 412B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetClass`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/classes/SetClass`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/damage/SetClass`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/npc/SetClass`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/player/SetClass`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `SetComposition` — 722B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetComposition`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/clay/SetComposition`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `SetDeathEvents` — 463B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetDeathEvents`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/SetDeathEvents`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `SetDrainRate` — 431B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetDrainRate`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/battery/SetDrainRate`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/flashlight/SetDrainRate`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `SetDrainable` — 348B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetDrainable`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/battery/SetDrainable`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `SetExtraChannels` — 437B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetExtraChannels`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/SetExtraChannels`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `SetFingers` — 198B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetFingers`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/armor/SetFingers`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/worn_storage/SetFingers`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `SetFirearmType` — 452B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetFirearmType`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/clip/SetFirearmType`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/firearm/SetFirearmType`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/round/SetFirearmType`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/shell/SetFirearmType`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `SetFuelRequired` — 283B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetFuelRequired`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/burn/SetFuelRequired`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `SetHeat` — 259B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetHeat`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/burn/SetHeat`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `SetLeader` — 390B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetLeader`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/clan/SetLeader`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/follow/SetLeader`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `SetMelee` — 380B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetMelee`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/SetMelee`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `SetMillimeter` — 487B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetMillimeter`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/clip/SetMillimeter`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/firearm/SetMillimeter`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/round/SetMillimeter`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/shell/SetMillimeter`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `SetMinHeat` — 301B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetMinHeat`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/burn/SetMinHeat`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `SetMorality` — 253B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetMorality`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/classes/SetMorality`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/spell/SetMorality`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `SetNoChanColors` — 345B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetNoChanColors`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/chat/SetNoChanColors`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `SetPacifist` — 282B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetPacifist`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/SetPacifist`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `SetPoints` — 397B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetPoints`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/bonus/SetPoints`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/potion/SetPoints`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `SetPowerType` — 307B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetPowerType`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/battery/SetPowerType`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `SetProtect` — 329B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetProtect`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/SetProtect`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `SetRechargeable` — 296B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetRechargeable`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/battery/SetRechargeable`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `SetReligion` — 281B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetReligion`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/chapel/SetReligion`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/classes/SetReligion`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `SetSacrificeType` — 412B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetSacrificeType`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/chapel/SetSacrificeType`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `SetSkillModifier` — 349B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetSkillModifier`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/classes/SetSkillModifier`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `SetSkills` — 480B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetSkills`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/bonus/SetSkills`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/potion/SetSkills`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/spell/SetSkills`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `SetSleeping` — 514B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetSleeping`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/SetSleeping`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `SetStats` — 365B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/SetStats`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/bonus/SetStats`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/potion/SetStats`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `Spent` — 262B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/Spent`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/battery/Spent`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `TODO` — 905B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/TODO`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/parsing/TODO`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `UnrestrictChannel` — 341B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/UnrestrictChannel`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/chat/UnrestrictChannel`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `acos` — 246B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/acos`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/floats/acos`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `add_action` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/add_action`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/add_action`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `addr_server` — 24KB
- `mud-references/deadsouls/ds3.8.2/bin/addr_server`
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/addr_server`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `all_inventory` — 386B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/all_inventory`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/objects/all_inventory`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `all_previous_objects` — 502B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/all_previous_objects`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/all_previous_objects`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `allocate` — 264B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/allocate`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/arrays/allocate`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `allocate_buffer` — 435B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/allocate_buffer`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/buffers/allocate_buffer`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `allocate_mapping` — 798B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/allocate_mapping`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mappings/allocate_mapping`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `arrayp` — 156B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/arrayp`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mixed/arrayp`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `asin` — 228B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/asin`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/floats/asin`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `atan` — 235B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/atan`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/floats/atan`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `author_file` — 665B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/author_file`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/author_file`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `author_stats` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/author_stats`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mudlib/author_stats`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `bandanna.c` — 598B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/armor/bandanna.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/armor/bandanna.c`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `bboard.c` — 101B
- `mud-references/deadsouls/ds3.8.2/lib/secure/lib/bboard.c`
- `mud-references/deadsouls/ds3.8.2/lib/std/board/bboard.c`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `bbucket.c` — 874B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/obj/bbucket.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/cave/obj/bbucket.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/obj/bbucket.c`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `bind` — 521B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/bind`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/functions/bind`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `blue_wins` — 5B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charles/blue_wins`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charly/bak/blue_wins`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charly/blue_wins`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `bufferp` — 218B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/bufferp`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mixed/bufferp`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `cache_stats` — 376B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/cache_stats`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/internals/cache_stats`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `call_other` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/call_other`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/calls/call_other`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `call_out` — 883B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/call_out`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/calls/call_out`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `call_out_info` — 792B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/call_out_info`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/call_out_info`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `call_stack` — 532B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/call_stack`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/calls/call_stack`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `cap.c` — 546B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/armor/cap.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/armor/cap.c`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `capitalize` — 240B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/capitalize`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/strings/capitalize`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `case.c` — 717B
- `mud-references/deadsouls/ds3.8.2/lib/realms/template/area/obj/case.c`
- `mud-references/deadsouls/ds3.8.2/lib/realms/thurtea/area/obj/case.c`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `catch` — 644B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/catch`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/calls/catch`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `catch_tell` — 596B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/catch_tell`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/interactive/catch_tell`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `ceil` — 317B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/ceil`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/floats/ceil`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `chainmail.c` — 630B
- `mud-references/deadsouls/ds3.8.2/lib/realms/template/area/armor/chainmail.c`
- `mud-references/deadsouls/ds3.8.2/lib/realms/thurtea/area/armor/chainmail.c`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `chat_command` — 411B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/chat_command`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/chat/chat_command`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `checkCollapse` — 336B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/checkCollapse`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/checkCollapse`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `check_memory` — 392B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/check_memory`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/check_memory`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `chest.c` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/realms/template/area/obj/chest.c`
- `mud-references/deadsouls/ds3.8.2/lib/realms/thurtea/area/obj/chest.c`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `children` — 379B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/children`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/objects/children`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `classp` — 190B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/classp`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mixed/classp`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `clear_bit` — 353B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/clear_bit`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/strings/clear_bit`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `clone_object` — 513B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/clone_object`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/objects/clone_object`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `clonep` — 697B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/clonep`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/objects/clonep`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `command` — 567B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/command`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/command`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `commands` — 620B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/commands`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/commands`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `compile_object` — 1008B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/compile_object`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/compile_object`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `connect` — 622B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/connect`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/connect`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `copy` — 488B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/copy`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/general/copy`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `cos` — 309B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/cos`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/floats/cos`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `cp` — 324B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/cp`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/filesystem/cp`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `crash` — 637B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/crash`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/crash`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `crc32` — 243B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/crc32`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/buffers/crc32`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `creator_file` — 872B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/creator_file`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/creator_file`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `crypt` — 311B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/crypt`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/strings/crypt`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `ctime` — 282B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/ctime`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/ctime`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `cup.c` — 524B
- `mud-references/deadsouls/ds3.8.2/lib/domains/cave/obj/cup.c`
- `mud-references/deadsouls/ds3.8.2/lib/realms/template/area/obj/cup.c`
- `mud-references/deadsouls/ds3.8.2/lib/realms/thurtea/area/obj/cup.c`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `custom.c` — 118B
- `mud-references/deadsouls/ds3.8.2/lib/realms/template/cmds/custom.c`
- `mud-references/deadsouls/ds3.8.2/lib/realms/thurtea/cmds/custom.c`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `dagger.c` — 520B
- `mud-references/deadsouls/ds3.8.2/lib/domains/cave/weap/dagger.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/weap/dagger.c`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `death.c` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/room/death.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/room/death.c`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `death.c` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/domains/learning/room/death.c`
- `mud-references/deadsouls/ds3.8.2/lib/std/death.c`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `debug_info` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/debug_info`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/internals/debug_info`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `debug_message` — 273B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/debug_message`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/debug_message`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `debugmalloc` — 619B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/debugmalloc`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/internals/debugmalloc`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `deep_inherit_list` — 300B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/deep_inherit_list`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/deep_inherit_list`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `deep_inventory` — 429B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/deep_inventory`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/objects/deep_inventory`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `destruct` — 523B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/destruct`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/objects/destruct`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `disable_commands` — 237B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/disable_commands`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/disable_commands`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `disable_wizard` — 263B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/disable_wizard`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/disable_wizard`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `domain_file` — 606B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/domain_file`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/domain_file`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `domain_stats` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/domain_stats`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mudlib/domain_stats`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `driver` — 728KB
- `mud-references/deadsouls/ds3.8.2/bin/driver`
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/driver`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `dump_file_descriptors` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/dump_file_descriptors`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/internals/dump_file_descriptors`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `dump_prog` — 618B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/dump_prog`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/internals/dump_prog`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `dump_socket_status` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/dump_socket_status`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/internals/dump_socket_status`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `dumpallobj` — 485B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/dumpallobj`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/internals/dumpallobj`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `ed` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/ed`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/ed`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `ed_cmd` — 279B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/ed_cmd`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/ed_cmd`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `ed_start` — 581B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/ed_start`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/ed_start`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `emote.c` — 1KB
- `lib/cmds/players/emote.c`
- `mud-references/deadsouls/ds3.8.2/lib/cmds/players/emote.c`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `enable_commands` — 531B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/enable_commands`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/enable_commands`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `enable_wizard` — 934B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/enable_wizard`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/enable_wizard`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `environment` — 388B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/environment`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/objects/environment`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `epilog` — 619B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/epilog`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/epilog`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `error` — 332B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/error`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/error`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `error_handler` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/error_handler`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/error_handler`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `eval_cost` — 305B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/eval_cost`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/eval_cost`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `evaldefs.h` — 315B
- `mud-references/deadsouls/ds3.8.2/lib/realms/template/evaldefs.h`
- `mud-references/deadsouls/ds3.8.2/lib/realms/thurtea/evaldefs.h`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `evaluate` — 275B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/evaluate`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/functions/evaluate`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `eventBring` — 390B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventBring`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/clan/eventBring`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `eventBurnOut` — 267B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventBurnOut`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/burn/eventBurnOut`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `eventBuy` — 661B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventBuy`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/eventBuy`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/vendor/eventBuy`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `eventCharge` — 278B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventCharge`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/battery/eventCharge`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `eventCheckHealing` — 449B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventCheckHealing`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/eventCheckHealing`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `eventCheckProtection` — 505B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventCheckProtection`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/eventCheckProtection`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `eventCollapse` — 267B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventCollapse`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/eventCollapse`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `eventCompareLimbs` — 333B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventCompareLimbs`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/eventCompareLimbs`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `eventCompleteHeal` — 463B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventCompleteHeal`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/eventCompleteHeal`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `eventDestruct` — 879B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventDestruct`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/bonus/eventDestruct`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/chat/eventDestruct`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/clean/eventDestruct`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/client/eventDestruct`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/connect/eventDestruct`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/daemon/eventDestruct`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/file/eventDestruct`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/ftp_client/eventDestruct`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/ftp_data_connection/eventDestruct`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/interactive/eventDestruct`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/meal/eventDestruct`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/npc/eventDestruct`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/server/eventDestruct`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `eventDie` — 714B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventDie`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/eventDie`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/bot/eventDie`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/combat/eventDie`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/flashlight/eventDie`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/npc/eventDie`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/player/eventDie`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/race/eventDie`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `eventDrain` — 281B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventDrain`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/battery/eventDrain`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `eventExtinguish` — 325B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventExtinguish`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/burn/eventExtinguish`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/flashlight/eventExtinguish`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `eventFall` — 324B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventFall`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/eventFall`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/position/eventFall`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `eventHealDamage` — 761B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventHealDamage`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/eventHealDamage`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `eventInitiate` — 504B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventInitiate`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/clan/eventInitiate`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `eventJoin` — 467B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventJoin`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/clan/eventJoin`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/leader/eventJoin`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `eventLight` — 425B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventLight`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/burn/eventLight`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/flashlight/eventLight`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/lamp/eventLight`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/light/eventLight`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `eventLoad` — 543B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventLoad`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/clip/eventLoad`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/firearm/eventLoad`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/load/eventLoad`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/round/eventLoad`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `eventMarry` — 301B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventMarry`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/chapel/eventMarry`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/interactive/eventMarry`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `eventMoralAct` — 370B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventMoralAct`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/classes/eventMoralAct`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `eventReceiveDamage` — 476B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventReceiveDamage`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/armor/eventReceiveDamage`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/eventReceiveDamage`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/combat/eventReceiveDamage`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/deterioration/eventReceiveDamage`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/worn_storage/eventReceiveDamage`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `eventReceiveThrow` — 323B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventReceiveThrow`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/eventReceiveThrow`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `eventReconnect` — 370B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventReconnect`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/eventReconnect`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/chat/eventReconnect`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/creator/eventReconnect`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/interactive/eventReconnect`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/npc/eventReconnect`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/player/eventReconnect`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `eventRemoveItem` — 347B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventRemoveItem`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/eventRemoveItem`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `eventRetire` — 470B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventRetire`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/clan/eventRetire`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `eventSacrifice` — 388B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventSacrifice`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/chapel/eventSacrifice`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `eventUnjoin` — 450B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventUnjoin`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/clan/eventUnjoin`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `eventUnload` — 549B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventUnload`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/clip/eventUnload`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/firearm/eventUnload`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/load/eventUnload`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/round/eventUnload`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `eventUse` — 426B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventUse`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/battery/eventUse`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/flashlight/eventUse`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/player/eventUse`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `eventWear` — 446B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventWear`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/body/eventWear`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `eventWelcome` — 363B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/eventWelcome`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/clan/eventWelcome`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `exec` — 833B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/exec`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/exec`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `exp` — 240B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/exp`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/floats/exp`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `explode` — 442B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/explode`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/strings/explode`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `export_uid` — 376B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/export_uid`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mudlib/export_uid`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `favicon.ico` — 6KB
- `mud-references/deadsouls/ds3.8.2/lib/www/articles/favicon.ico`
- `mud-references/deadsouls/ds3.8.2/lib/www/favicon.ico`
- `mud-references/deadsouls/ds3.8.2/lib/www/lpmuds/favicon.ico`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `fblue` — 2B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charles/bak2/bak1/fblue`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charles/bak2/fblue`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `fblue` — 5B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charly/bak/fblue`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charly/fblue`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `fetch_variable` — 424B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/fetch_variable`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/general/fetch_variable`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `fgreen` — 5B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charly/bak/fgreen`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charly/fgreen`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `fighter.c` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/realms/template/area/npc/fighter.c`
- `mud-references/deadsouls/ds3.8.2/lib/realms/thurtea/area/npc/fighter.c`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `file_length` — 440B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/file_length`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/filesystem/file_length`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `file_name` — 650B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/file_name`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/objects/file_name`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `file_size` — 290B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/file_size`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/filesystem/file_size`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `filter` — 726B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/filter`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/general/filter`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `filter_array` — 328B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/filter_array`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/arrays/filter_array`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `filter_mapping` — 341B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/filter_mapping`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mappings/filter_mapping`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `find_call_out` — 425B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/find_call_out`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/find_call_out`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `find_living` — 614B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/find_living`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mudlib/find_living`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `find_object` — 364B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/find_object`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/objects/find_object`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `find_player` — 304B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/find_player`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/find_player`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `first_inventory` — 424B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/first_inventory`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/objects/first_inventory`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `flag` — 380B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/flag`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/flag`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `floatp` — 219B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/floatp`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mixed/floatp`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `floor` — 250B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/floor`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/floats/floor`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `flush_messages` — 406B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/flush_messages`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/flush_messages`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `foo.txt` — 36B
- `mud-references/deadsouls/ds3.8.2/lib/daemon/tmp/foo.txt`
- `mud-references/deadsouls/ds3.8.2/lib/estates/foo.txt`
- `mud-references/deadsouls/ds3.8.2/lib/ftp/foo.txt`
- `mud-references/deadsouls/ds3.8.2/lib/log/adm/foo.txt`
- `mud-references/deadsouls/ds3.8.2/lib/log/archive/foo.txt`
- `mud-references/deadsouls/ds3.8.2/lib/log/chan/foo.txt`
- `mud-references/deadsouls/ds3.8.2/lib/log/errors/foo.txt`
- `mud-references/deadsouls/ds3.8.2/lib/log/law/adm/foo.txt`
- `mud-references/deadsouls/ds3.8.2/lib/log/law/email/foo.txt`
- `mud-references/deadsouls/ds3.8.2/lib/log/law/names/foo.txt`
- `mud-references/deadsouls/ds3.8.2/lib/log/law/sites-misc/foo.txt`
- `mud-references/deadsouls/ds3.8.2/lib/log/law/sites-register/foo.txt`
- `mud-references/deadsouls/ds3.8.2/lib/log/law/sites-tempban/foo.txt`
- `mud-references/deadsouls/ds3.8.2/lib/log/law/sites-watch/foo.txt`
- `mud-references/deadsouls/ds3.8.2/lib/log/open/foo.txt`
- `mud-references/deadsouls/ds3.8.2/lib/log/reports/foo.txt`
- `mud-references/deadsouls/ds3.8.2/lib/log/router/foo.txt`
- `mud-references/deadsouls/ds3.8.2/lib/log/secure/foo.txt`
- `mud-references/deadsouls/ds3.8.2/lib/log/watch/foo.txt`
- `mud-references/deadsouls/ds3.8.2/lib/secure/log/adm/foo.txt`
- `mud-references/deadsouls/ds3.8.2/lib/secure/log/bak/foo.txt`
- `mud-references/deadsouls/ds3.8.2/lib/secure/log/intermud/foo.txt`
- `mud-references/deadsouls/ds3.8.2/lib/secure/log/network/foo.txt`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `foodsmock.c` — 494B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/armor/foodsmock.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/cave/armor/foodsmock.c`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `fred` — 2B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charles/bak2/bak1/fred`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charles/bak2/fred`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `fred` — 5B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charly/bak/fred`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charly/fred`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `freezer.c` — 707B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/room/freezer.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/cave/room/freezer.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/room/freezer.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/learning/room/freezer.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/room/freezer.c`
- `mud-references/deadsouls/ds3.8.2/lib/std/freezer.c`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `function_exists` — 738B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/function_exists`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/function_exists`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `function_owner` — 266B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/function_owner`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/functions/function_owner`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `function_profile` — 847B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/function_profile`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/function_profile`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `functionp` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/functionp`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mixed/functionp`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `functions` — 892B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/functions`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/functions`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `furnace.c` — 110B
- `mud-references/deadsouls/ds3.8.2/lib/domains/Ylsrim/room/furnace.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/room/furnace.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/cave/room/furnace.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/room/furnace.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/learning/room/furnace.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/room/furnace.c`
- `mud-references/deadsouls/ds3.8.2/lib/std/furnace.c`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `generate_source` — 755B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/generate_source`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/compile/generate_source`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `get_bb_uid` — 393B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/get_bb_uid`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/get_bb_uid`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `get_char` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/get_char`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/get_char`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `get_config` — 309B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/get_config`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/internals/get_config`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `get_dir` — 930B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/get_dir`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/filesystem/get_dir`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `get_root_uid` — 350B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/get_root_uid`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/get_root_uid`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `get_save_file_name` — 411B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/get_save_file_name`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/get_save_file_name`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `geteuid` — 625B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/geteuid`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mudlib/geteuid`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `getuid` — 416B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/getuid`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mudlib/getuid`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `green_wins` — 3B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charles/bak2/bak1/green_wins`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charles/bak2/green_wins`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `green_wins` — 5B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charles/green_wins`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charly/bak/green_wins`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charly/green_wins`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `heart_beat_info` — 316B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/heart_beat_info`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/objects/heart_beat_info`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `heart_beats` — 344B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/heart_beats`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/objects/heart_beats`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `implode` — 712B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/implode`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/strings/implode`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `in_edit` — 326B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/in_edit`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/in_edit`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `in_input` — 339B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/in_input`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/in_input`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `index` — 171B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/compile/index`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/numbers/index`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `index` — 565B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/index`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/index`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `inherit_list` — 406B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/inherit_list`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/inherit_list`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `inherits` — 355B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/inherits`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/inherits`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `input_to` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/input_to`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/input_to`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `insttest` — 9B
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/insttest`
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/tmp/insttest`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `interactive` — 323B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/interactive`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/interactive`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `intp` — 221B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/intp`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mixed/intp`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `key.c` — 375B
- `mud-references/deadsouls/ds3.8.2/lib/realms/template/area/obj/key.c`
- `mud-references/deadsouls/ds3.8.2/lib/realms/thurtea/area/obj/key.c`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `keys` — 554B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/keys`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mappings/keys`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `lamp.c` — 377B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/obj/lamp.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/obj/lamp.c`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `leather_armor.c` — 869B
- `mud-references/deadsouls/ds3.8.2/lib/domains/Ylsrim/armor/leather_armor.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/cave/armor/leather_armor.c`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `leather_boot_l.c` — 676B
- `mud-references/deadsouls/ds3.8.2/lib/realms/template/area/armor/leather_boot_l.c`
- `mud-references/deadsouls/ds3.8.2/lib/realms/thurtea/area/armor/leather_boot_l.c`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `leather_boot_r.c` — 679B
- `mud-references/deadsouls/ds3.8.2/lib/realms/template/area/armor/leather_boot_r.c`
- `mud-references/deadsouls/ds3.8.2/lib/realms/thurtea/area/armor/leather_boot_r.c`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `lever.c` — 436B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/obj/lever.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/obj/lever.c`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `link` — 495B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/link`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/filesystem/link`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `living` — 349B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/living`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mudlib/living`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `livings` — 369B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/livings`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mudlib/livings`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `load_object` — 510B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/load_object`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/objects/load_object`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `localtime` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/localtime`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/localtime`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `log` — 236B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/log`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/floats/log`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `log_error` — 591B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/log_error`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/log_error`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `logon` — 367B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/interactive/logon`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/logon`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `lower_case` — 272B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/lower_case`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/strings/lower_case`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `lpc_info` — 301B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/lpc_info`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/lpc_info`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `m16rifle.c` — 824B
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/weap/m16rifle.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/weap/m16rifle.c`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `m_delete` — 646B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/m_delete`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mappings/m_delete`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `m_indices` — 249B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/m_indices`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mappings/m_indices`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `m_values` — 253B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/m_values`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mappings/m_values`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `make_path_absolute` — 238B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/make_path_absolute`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/make_path_absolute`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `malloc_status` — 488B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/malloc_status`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/internals/malloc_status`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `map` — 708B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/map`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/general/map`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `map_array` — 286B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/map_array`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/arrays/map_array`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `map_delete` — 760B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/map_delete`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mappings/map_delete`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `map_mapping` — 671B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/map_mapping`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mappings/map_mapping`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `mapp` — 189B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/mapp`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mixed/mapp`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `master` — 188B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/master`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/objects/master`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `match.c` — 519B
- `mud-references/deadsouls/ds3.8.2/lib/domains/cave/obj/match.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/obj/match.c`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `match_path` — 475B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/match_path`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mappings/match_path`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `max_eval_cost` — 315B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/max_eval_cost`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/max_eval_cost`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `member_array` — 503B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/member_array`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/arrays/member_array`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `memory_info` — 693B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/memory_info`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/internals/memory_info`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `memory_summary` — 566B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/memory_summary`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/memory_summary`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `message` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/message`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/message`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `mkdir` — 227B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/mkdir`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/filesystem/mkdir`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `move_object` — 257B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/move_object`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/objects/move_object`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `mud_status` — 483B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/mud_status`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/internals/mud_status`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `mudos.cfg` — 5KB
- `mud-references/deadsouls/ds3.8.2/bin/mudos.cfg`
- `mud-references/deadsouls/ds3.8.2/lib/secure/cfg/mudos.cfg`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `named_livings` — 388B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/named_livings`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/named_livings`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `net_dead` — 492B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/interactive/net_dead`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/net_dead`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `network_stats` — 3B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/network_stats`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/sockets/network_stats`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `new` — 309B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/new`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/objects/new`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `next_bit` — 282B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/next_bit`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/strings/next_bit`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `next_inventory` — 352B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/next_inventory`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/objects/next_inventory`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `notify_fail` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/notify_fail`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/notify_fail`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `nullp` — 215B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/nullp`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mixed/nullp`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `object_name` — 377B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/object_name`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/object_name`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `objectp` — 195B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/objectp`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mixed/objectp`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `objects` — 833B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/objects`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/objects/objects`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `opcprof` — 482B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/opcprof`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/internals/opcprof`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `origin` — 512B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/origin`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/calls/origin`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `origin.h` — 530B
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/include/origin.h`
- `mud-references/deadsouls/ds3.8.2/lib/secure/include/origin.h`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `pants.c` — 561B
- `mud-references/deadsouls/ds3.8.2/lib/domains/cave/armor/pants.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/armor/pants.c`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `parse_command` — 9KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/parse_command`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/parsing/parse_command`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `parse_command_adjectiv_id_list` — 369B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/parse_command_adjectiv_id_list`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/parsing/parse_command_adjectiv_id_list`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `parse_command_all_word` — 278B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/parse_command_all_word`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/parse_command_all_word`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `parse_command_id_list` — 340B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/parse_command_id_list`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/parsing/parse_command_id_list`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `parse_command_plural_id_list` — 361B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/parse_command_plural_id_list`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/parsing/parse_command_plural_id_list`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `parse_command_prepos_list` — 309B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/parse_command_prepos_list`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/parse_command_prepos_list`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `percent` — 1B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charles/bak2/bak1/percent`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charles/bak2/percent`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charles/percent`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charly/bak/percent`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charly/percent`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `pin.c` — 393B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/obj/pin.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/obj/pin.c`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `pitcher.c` — 651B
- `mud-references/deadsouls/ds3.8.2/lib/realms/template/area/obj/pitcher.c`
- `mud-references/deadsouls/ds3.8.2/lib/realms/thurtea/area/obj/pitcher.c`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `pluralize` — 297B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/pluralize`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/strings/pluralize`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `pod.c` — 375B
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/room/pod.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/learning/room/pod.c`
- `mud-references/deadsouls/ds3.8.2/lib/std/pod.c`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `pointerp` — 192B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/pointerp`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mixed/pointerp`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `portbind` — 13KB
- `mud-references/deadsouls/ds3.8.2/bin/portbind`
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/portbind`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `pow` — 260B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/pow`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/floats/pow`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `preload` — 533B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/preload`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/preload`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `present` — 643B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/present`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/objects/present`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `previous_object` — 734B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/previous_object`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/calls/previous_object`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `print.css` — 60B
- `mud-references/deadsouls/ds3.8.2/lib/www/lpmuds/print.css`
- `mud-references/deadsouls/ds3.8.2/lib/www/print.css`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `printf` — 3KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/printf`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/printf`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `privs_file` — 481B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/privs_file`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/privs_file`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `process_input` — 851B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/interactive/process_input`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/process_input`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `program_info` — 357B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/program_info`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/program_info`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `query_ed_mode` — 376B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/query_ed_mode`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/query_ed_mode`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `query_heart_beat` — 401B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/query_heart_beat`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/objects/query_heart_beat`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `query_host_name` — 256B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/query_host_name`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/query_host_name`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `query_idle` — 269B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/query_idle`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/query_idle`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `query_ip_name` — 451B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/query_ip_name`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/query_ip_name`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `query_ip_number` — 299B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/query_ip_number`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/query_ip_number`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `query_ip_port` — 541B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/query_ip_port`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/query_ip_port`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `query_load_average` — 299B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/query_load_average`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/internals/query_load_average`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `query_notify_fail` — 599B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/query_notify_fail`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/query_notify_fail`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `query_num` — 3B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/query_num`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/numbers/query_num`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `query_privs` — 444B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/query_privs`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mudlib/query_privs`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `query_shadowing` — 375B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/query_shadowing`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/calls/query_shadowing`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `query_snoop` — 268B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/query_snoop`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/query_snoop`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `query_snooping` — 333B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/query_snooping`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/query_snooping`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `query_verb` — 498B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/query_verb`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/parsing/query_verb`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `random` — 204B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/random`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/numbers/random`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `read_buffer` — 844B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/read_buffer`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/buffers/read_buffer`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `read_bytes` — 467B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/read_bytes`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/filesystem/read_bytes`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `read_file` — 510B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/read_file`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/filesystem/read_file`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `readme` — 0B
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/testsuite/clone/readme`
- `mud-references/deadsouls/ds3.8.2/fluffos-2.23-ds03/testsuite/single/tests/efuns/readme`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `receive` — 475B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/receive`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/receive`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `receive_message` — 561B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/interactive/receive_message`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/receive_message`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `receive_snoop` — 458B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/interactive/receive_snoop`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/receive_snoop`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `reclaim_objects` — 649B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/reclaim_objects`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/reclaim_objects`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `red_wins` — 5B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charles/red_wins`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charly/bak/red_wins`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charly/red_wins`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `refs` — 383B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/refs`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/internals/refs`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `reg_assoc` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/reg_assoc`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/strings/reg_assoc`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `regexp` — 4KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/regexp`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/strings/regexp`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `reload_object` — 517B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/reload_object`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/objects/reload_object`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `remote.c` — 77B
- `mud-references/deadsouls/ds3.8.2/lib/realms/template/adm/remote.c`
- `mud-references/deadsouls/ds3.8.2/lib/realms/thurtea/adm/remote.c`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `remove_action` — 543B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/remove_action`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/remove_action`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `remove_call_out` — 541B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/remove_call_out`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/calls/remove_call_out`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `remove_interactive` — 457B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/remove_interactive`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/remove_interactive`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `remove_shadow` — 423B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/remove_shadow`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/calls/remove_shadow`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `rename` — 207B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/rename`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/filesystem/rename`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `repeat_string` — 427B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/repeat_string`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/strings/repeat_string`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `replace_program` — 901B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/replace_program`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/replace_program`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `replace_string` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/replace_string`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/strings/replace_string`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `replaceable` — 868B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/replaceable`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/replaceable`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `reset_eval_cost` — 277B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/reset_eval_cost`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/reset_eval_cost`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `resolve` — 798B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/resolve`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/resolve`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `restore_object` — 504B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/restore_object`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/objects/restore_object`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `restore_variable` — 314B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/restore_variable`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/general/restore_variable`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `retrieve_ed_setup` — 304B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/retrieve_ed_setup`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/retrieve_ed_setup`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `returnChannels` — 338B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/returnChannels`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/chat/returnChannels`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `rm` — 208B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/rm`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/filesystem/rm`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `rmdir` — 160B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/rmdir`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/filesystem/rmdir`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `round.c` — 469B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/obj/round.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/obj/round.c`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `runs` — 3B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charles/bak2/bak1/runs`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charles/bak2/runs`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `runs` — 5B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charles/runs`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charly/bak/runs`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `rusage` — 964B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/rusage`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/internals/rusage`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `sample_room.c` — 623B
- `mud-references/deadsouls/ds3.8.2/lib/realms/template/area/room/sample_room.c`
- `mud-references/deadsouls/ds3.8.2/lib/realms/thurtea/area/room/sample_room.c`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `sample_two.c` — 532B
- `mud-references/deadsouls/ds3.8.2/lib/realms/template/area/room/sample_two.c`
- `mud-references/deadsouls/ds3.8.2/lib/realms/thurtea/area/room/sample_two.c`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `save_ed_setup` — 347B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/save_ed_setup`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/save_ed_setup`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `save_object` — 577B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/save_object`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/objects/save_object`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `save_variable` — 222B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/save_variable`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/general/save_variable`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `say` — 712B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/say`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/say`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `server.c` — 778B
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/virtual/server.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/virtual/server.c`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `set_author` — 776B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/set_author`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mudlib/set_author`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `set_bit` — 525B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/set_bit`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/strings/set_bit`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `set_debug_level` — 531B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/set_debug_level`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/internals/set_debug_level`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `set_eval_limit` — 477B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/set_eval_limit`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/set_eval_limit`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `set_heart_beat` — 638B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/set_heart_beat`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/objects/set_heart_beat`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `set_hide` — 569B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/set_hide`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/objects/set_hide`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `set_light` — 608B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/set_light`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mudlib/set_light`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `set_living_name` — 406B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/set_living_name`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mudlib/set_living_name`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `set_malloc_mask` — 520B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/set_malloc_mask`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/internals/set_malloc_mask`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `set_privs` — 371B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/set_privs`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mudlib/set_privs`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `set_reset` — 495B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/set_reset`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/set_reset`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `set_this_player` — 487B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/set_this_player`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/set_this_player`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `seteuid` — 568B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/seteuid`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mudlib/seteuid`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `shadow` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/shadow`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/calls/shadow`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `shallow_inherit_list` — 436B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/shallow_inherit_list`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/shallow_inherit_list`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `shout` — 272B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/shout`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/shout`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `shutdown` — 951B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/shutdown`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/shutdown`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `simple_chair.c` — 361B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/obj/simple_chair.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/obj/simple_chair.c`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `sin` — 291B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/sin`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/floats/sin`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `sizeof` — 269B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/sizeof`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/general/sizeof`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `slow_shutdown` — 576B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/slow_shutdown`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/slow_shutdown`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `snoop` — 805B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/snoop`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/snoop`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `socket_accept` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/socket_accept`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/sockets/socket_accept`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `socket_acquire` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/socket_acquire`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/sockets/socket_acquire`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `socket_address` — 578B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/socket_address`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/sockets/socket_address`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `socket_bind` — 907B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/socket_bind`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/sockets/socket_bind`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `socket_close` — 547B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/socket_close`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/sockets/socket_close`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `socket_connect` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/socket_connect`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/sockets/socket_connect`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `socket_create` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/socket_create`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/sockets/socket_create`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `socket_error` — 465B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/socket_error`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/sockets/socket_error`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `socket_error.h` — 0B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/socket_error.h`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/sockets/socket_error.h`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `socket_listen` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/socket_listen`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/sockets/socket_listen`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `socket_release` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/socket_release`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/sockets/socket_release`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `socket_write` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/socket_write`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/sockets/socket_write`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `sort_array` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/sort_array`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/arrays/sort_array`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `sprintf` — 3KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/sprintf`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/strings/sprintf`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `sqrt` — 332B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/sqrt`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/floats/sqrt`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `sscanf` — 2KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/sscanf`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/strings/sscanf`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `stat` — 514B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/stat`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/filesystem/stat`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `stays` — 5B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charly/bak/stays`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charly/stays`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `store_variable` — 475B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/store_variable`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/general/store_variable`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `strcmp` — 692B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/strcmp`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/strings/strcmp`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `stringp` — 211B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/stringp`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mixed/stringp`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `strlen` — 220B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/strlen`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/strings/strlen`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `strsrch` — 703B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/strsrch`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/strings/strsrch`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `swap` — 549B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/swap`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/internals/swap`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `switches` — 5B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charles/switches`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charly/bak/switches`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charly/switches`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `sword.c` — 469B
- `mud-references/deadsouls/ds3.8.2/lib/realms/template/area/weap/sword.c`
- `mud-references/deadsouls/ds3.8.2/lib/realms/thurtea/area/weap/sword.c`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `sword.c` — 509B
- `mud-references/deadsouls/ds3.8.2/lib/domains/cave/weap/sword.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/weap/sword.c`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `table.c` — 591B
- `mud-references/deadsouls/ds3.8.2/lib/realms/template/area/obj/table.c`
- `mud-references/deadsouls/ds3.8.2/lib/realms/thurtea/area/obj/table.c`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `tail` — 281B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/tail`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/filesystem/tail`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `tan` — 227B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/tan`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/floats/tan`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `tell_object` — 386B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/tell_object`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/objects/tell_object`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `tell_room` — 451B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/tell_room`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/objects/tell_room`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `teller_check` — 355B
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/all/teller_check`
- `mud-references/deadsouls/ds3.8.2/lib/doc/lfun/lib/bank/teller_check`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `telnet_suboption` — 687B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/interactive/telnet_suboption`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/telnet_suboption`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `terminal_colour` — 625B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/terminal_colour`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/strings/terminal_colour`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `terminal_type` — 395B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/interactive/terminal_type`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/terminal_type`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `test_bit` — 242B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/test_bit`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/strings/test_bit`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `thing.c` — 450B
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/obj/thing.c`
- `mud-references/deadsouls/ds3.8.2/lib/obj/thing.c`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `this_interactive` — 392B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/this_interactive`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/this_interactive`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `this_object` — 315B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/this_object`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/calls/this_object`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `this_player` — 170B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/this_player`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/this_player`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `this_user` — 592B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/this_user`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/this_user`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `throw` — 480B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/throw`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/calls/throw`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `time` — 271B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/time`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/time`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `time_expression` — 508B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/time_expression`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/internals/time_expression`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `to_float` — 277B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/to_float`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/numbers/to_float`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `to_int` — 522B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/to_int`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/floats/to_int`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `torch.c` — 615B
- `mud-references/deadsouls/ds3.8.2/lib/domains/cave/obj/torch.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/obj/torch.c`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `trace` — 771B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/trace`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/internals/trace`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `traceprefix` — 409B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/traceprefix`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/internals/traceprefix`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `typeof` — 451B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/typeof`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/general/typeof`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `undefinedp` — 680B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/undefinedp`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mixed/undefinedp`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `unique_array` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/unique_array`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/arrays/unique_array`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `unique_mapping` — 463B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/unique_mapping`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mappings/unique_mapping`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `upper_case` — 354B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/upper_case`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/strings/upper_case`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `uptime` — 290B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/uptime`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/uptime`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `userp` — 234B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/userp`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/userp`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `users` — 269B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/users`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/users`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `valid_bind` — 416B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/valid_bind`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/valid_bind`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `valid_compile_to_c` — 418B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/valid_compile_to_c`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/valid_compile_to_c`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `valid_hide` — 642B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/valid_hide`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/valid_hide`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `valid_link` — 450B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/valid_link`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/valid_link`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `valid_object` — 627B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/valid_object`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/valid_object`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `valid_override` — 1KB
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/valid_override`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/valid_override`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `valid_read` — 501B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/valid_read`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/valid_read`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `valid_save_binary` — 570B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/valid_save_binary`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/valid_save_binary`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `valid_seteuid` — 503B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/valid_seteuid`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/valid_seteuid`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `valid_shadow` — 585B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/valid_shadow`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/valid_shadow`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `valid_socket` — 961B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/valid_socket`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/valid_socket`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `valid_write` — 548B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/master/valid_write`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/valid_write`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `values` — 466B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/values`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/mappings/values`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `variables` — 800B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/variables`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/system/variables`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `virtualp` — 374B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/virtualp`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/objects/virtualp`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `void.c` — 282B
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/room/void.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/learning/room/void.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/room/void.c`
- `mud-references/deadsouls/ds3.8.2/lib/std/void.c`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `void.c` — 366B
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/virtual/void.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/virtual/void.c`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `watch.c` — 3KB
- `mud-references/deadsouls/ds3.8.2/lib/realms/template/area/obj/watch.c`
- `mud-references/deadsouls/ds3.8.2/lib/realms/thurtea/area/obj/watch.c`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `water.c` — 536B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/meals/water.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/meals/water.c`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `window_size` — 317B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/interactive/window_size`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/window_size`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `wins` — 3B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charles/bak2/bak1/wins`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charles/bak2/wins`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `wins` — 5B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charles/wins`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charly/bak/wins`
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/txt/ai/charly/wins`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `wiz_hall.c` — 540B
- `mud-references/deadsouls/ds3.8.2/lib/domains/learning/room/wiz_hall.c`
- `mud-references/deadsouls/ds3.8.2/lib/std/wiz_hall.c`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `wizard_hat.c` — 809B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/armor/wizard_hat.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/default/armor/wizard_hat.c`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `wizardp` — 334B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/wizardp`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/wizardp`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `workboot_l.c` — 660B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/armor/workboot_l.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/armor/workboot_l.c`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `workboot_r.c` — 663B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/armor/workboot_r.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/armor/workboot_r.c`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `workglove_l.c` — 737B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/armor/workglove_l.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/armor/workglove_l.c`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `workglove_r.c` — 749B
- `mud-references/deadsouls/ds3.8.2/lib/domains/campus/armor/workglove_r.c`
- `mud-references/deadsouls/ds3.8.2/lib/domains/town/armor/workglove_r.c`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `workroom.c` — 4KB
- `mud-references/deadsouls/ds3.8.2/lib/realms/template/workroom.c`
- `mud-references/deadsouls/ds3.8.2/lib/realms/thurtea/workroom.c`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `write` — 307B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/write`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/interactive/write`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `write_buffer` — 594B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/write_buffer`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/buffers/write_buffer`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `write_bytes` — 306B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/write_bytes`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/filesystem/write_bytes`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `write_file` — 288B
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/all/write_file`
- `mud-references/deadsouls/ds3.8.2/lib/doc/efun/filesystem/write_file`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

### `write_prompt` — 366B
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/interactive/write_prompt`
- `mud-references/deadsouls/ds3.8.2/lib/doc/applies/write_prompt`
**Note:** These have the same filename and size but may differ in content. Verify with `diff` or by checking MD5.

## Section 4: Consolidation Guide

Proper directory structure (recommended):

| Directory | Purpose |
|---|---|
| `src/` | C driver source |
| `lib/` | LPC game library sources |
| `lib/include/` | LPC headers and shared include files |
| `config/` | Configuration files |
| `docs/` | Documentation |
| `scripts/` | Shell and helper scripts |
| `tests/` | Test suites |
| `tools/` | Development tools and utilities |

Cleanup strategy:

1. Verify differences with `diff -u fileA fileB` or `cmp` before removing anything.
2. Determine canonical location using project conventions (see above).
3. Move duplicates to a backup folder or replace with symlinks if appropriate:

```sh
mkdir -p archived-md/duplicates-backup
mv path/to/duplicate archived-md/duplicates-backup/
ln -s ../src/file.c path/to/duplicate
```

4. Update references in `Makefile` and include paths as needed.
5. Rebuild and run tests (`make`, `make test`).
6. Commit changes in a single, reviewable commit for easy rollback.

## Section 5: Summary Statistics

- Total files scanned: **6142**
- Number of filename duplicates (same name in multiple locations): **1095**
- Number of content-duplicates (identical MD5 hash groups): **621**
- Number of likely duplicates (same name + same size): **608**
