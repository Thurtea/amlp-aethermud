#include "magic.h"
#include "chargen.h"
#include "session_internal.h"
#include "room.h"
#include "npc.h"
#include "vm.h"
#include "object.h"
#include "efun.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

extern PlayerSession *sessions[];

/* Forward declaration */
void send_to_player(PlayerSession *session, const char *format, ...);

/* =============== MAGIC SPELLS DATABASE =============== */

MagicSpell MAGIC_SPELLS[35] = {
    /* WARLOCK GRADE SPELLS (0-7) - Level 1-5 */
    {
        .id = 0, .name = "Magic Armor", .description = "AR +4, 1d6 armor per caster level",
        .lpc_id = "magic_armor",
        .ppe_cost = 1, .ppe_per_round = 0, .duration_rounds = 60, .base_damage = 0,
        .damage_dice = 0, .damage_sides = 0, .is_mega_damage = false, .range_feet = 0,
        .area_effect_feet = 0, .school = SPELL_WARLOCK, .level_name = "Level 1",
        .casting_time_rounds = 1, .can_overwhelm = false, .is_ritual = false,
        .is_passive_bonus = false, .keywords = "defense armor protection"
    },
    {
        .id = 1, .name = "Detect Magic", .description = "Sense magical auras in area",
        .lpc_id = "detect_magic",
        .ppe_cost = 1, .ppe_per_round = 0, .duration_rounds = 10, .base_damage = 0,
        .damage_dice = 0, .damage_sides = 0, .is_mega_damage = false, .range_feet = 100,
        .area_effect_feet = 50, .school = SPELL_WARLOCK, .level_name = "Level 1",
        .casting_time_rounds = 1, .can_overwhelm = false, .is_ritual = false,
        .is_passive_bonus = false, .keywords = "sense detect magic aura"
    },
    {
        .id = 2, .name = "Light", .description = "Create bright magical light source",
        .lpc_id = "light",
        .ppe_cost = 1, .ppe_per_round = 0, .duration_rounds = 120, .base_damage = 0,
        .damage_dice = 0, .damage_sides = 0, .is_mega_damage = false, .range_feet = 50,
        .area_effect_feet = 20, .school = SPELL_WARLOCK, .level_name = "Level 1",
        .casting_time_rounds = 1, .can_overwhelm = false, .is_ritual = false,
        .is_passive_bonus = false, .keywords = "light illumination utility"
    },
    {
        .id = 3, .name = "Mend", .description = "Repair broken item",
        .lpc_id = "mend",
        .ppe_cost = 2, .ppe_per_round = 0, .duration_rounds = 1, .base_damage = 0,
        .damage_dice = 0, .damage_sides = 0, .is_mega_damage = false, .range_feet = 10,
        .area_effect_feet = 0, .school = SPELL_WARLOCK, .level_name = "Level 2",
        .casting_time_rounds = 2, .can_overwhelm = false, .is_ritual = true,
        .is_passive_bonus = false, .keywords = "repair utility craft"
    },
    {
        .id = 4, .name = "Magic Shield", .description = "Protective barrier, +2 AR",
        .lpc_id = "magic_shield",
        .ppe_cost = 2, .ppe_per_round = 1, .duration_rounds = -1, .base_damage = 0,
        .damage_dice = 0, .damage_sides = 0, .is_mega_damage = false, .range_feet = 0,
        .area_effect_feet = 0, .school = SPELL_WARLOCK, .level_name = "Level 2",
        .casting_time_rounds = 1, .can_overwhelm = false, .is_ritual = false,
        .is_passive_bonus = true, .keywords = "defense shield protection"
    },
    {
        .id = 5, .name = "Identify", .description = "Learn item properties and history",
        .lpc_id = "identify",
        .ppe_cost = 3, .ppe_per_round = 0, .duration_rounds = 1, .base_damage = 0,
        .damage_dice = 0, .damage_sides = 0, .is_mega_damage = false, .range_feet = 10,
        .area_effect_feet = 0, .school = SPELL_WARLOCK, .level_name = "Level 3",
        .casting_time_rounds = 2, .can_overwhelm = false, .is_ritual = false,
        .is_passive_bonus = false, .keywords = "knowledge sense identify magic"
    },
    {
        .id = 6, .name = "Alarm", .description = "Set magical trap on object/location",
        .lpc_id = "alarm",
        .ppe_cost = 2, .ppe_per_round = 0, .duration_rounds = -1, .base_damage = 0,
        .damage_dice = 0, .damage_sides = 0, .is_mega_damage = false, .range_feet = 0,
        .area_effect_feet = 0, .school = SPELL_WARLOCK, .level_name = "Level 2",
        .casting_time_rounds = 1, .can_overwhelm = false, .is_ritual = false,
        .is_passive_bonus = false, .keywords = "defense trap security"
    },
    {
        .id = 7, .name = "Dispel Magic Barrier", .description = "Remove magical protections",
        .lpc_id = "dispel_magic_barrier",
        .ppe_cost = 4, .ppe_per_round = 0, .duration_rounds = 1, .base_damage = 0,
        .damage_dice = 0, .damage_sides = 0, .is_mega_damage = false, .range_feet = 50,
        .area_effect_feet = 0, .school = SPELL_WARLOCK, .level_name = "Level 4",
        .casting_time_rounds = 2, .can_overwhelm = true, .is_ritual = false,
        .is_passive_bonus = false, .keywords = "magic dispel breaker"
    },

    /* MYSTIC/WARLOCK SPELLS (8-15) - Level 5-10 */
    {
        .id = 8, .name = "Fireball", .description = "4d6 MD in 10-foot radius",
        .lpc_id = "fireball",
        .ppe_cost = 5, .ppe_per_round = 0, .duration_rounds = 1, .base_damage = 0,
        .damage_dice = 4, .damage_sides = 6, .is_mega_damage = true, .range_feet = 150,
        .area_effect_feet = 10, .school = SPELL_MYSTIC, .level_name = "Level 5",
        .casting_time_rounds = 2, .can_overwhelm = true, .is_ritual = false,
        .is_passive_bonus = false, .keywords = "damage fire combat"
    },
    {
        .id = 9, .name = "Lightning Bolt", .description = "2d6 MD ranged electrical bolt",
        .lpc_id = "lightning_bolt",
        .ppe_cost = 5, .ppe_per_round = 0, .duration_rounds = 1, .base_damage = 0,
        .damage_dice = 2, .damage_sides = 6, .is_mega_damage = true, .range_feet = 200,
        .area_effect_feet = 0, .school = SPELL_MYSTIC, .level_name = "Level 5",
        .casting_time_rounds = 1, .can_overwhelm = true, .is_ritual = false,
        .is_passive_bonus = false, .keywords = "damage lightning combat"
    },
    {
        .id = 10, .name = "Teleport", .description = "Move to known location (up to 1 mile)",
        .lpc_id = "teleport",
        .ppe_cost = 8, .ppe_per_round = 0, .duration_rounds = 1, .base_damage = 0,
        .damage_dice = 0, .damage_sides = 0, .is_mega_damage = false, .range_feet = -1,
        .area_effect_feet = 0, .school = SPELL_MYSTIC, .level_name = "Level 8",
        .casting_time_rounds = 3, .can_overwhelm = false, .is_ritual = false,
        .is_passive_bonus = false, .keywords = "movement travel teleport"
    },
    {
        .id = 11, .name = "Ice Shards", .description = "3d6 MD frozen projectiles",
        .lpc_id = "ice_shards",
        .ppe_cost = 4, .ppe_per_round = 0, .duration_rounds = 1, .base_damage = 0,
        .damage_dice = 3, .damage_sides = 6, .is_mega_damage = true, .range_feet = 120,
        .area_effect_feet = 8, .school = SPELL_MYSTIC, .level_name = "Level 5",
        .casting_time_rounds = 1, .can_overwhelm = true, .is_ritual = false,
        .is_passive_bonus = false, .keywords = "damage ice cold combat"
    },
    {
        .id = 12, .name = "Web of Protection", .description = "Immobilize enemies in area",
        .lpc_id = "web_of_protection",
        .ppe_cost = 3, .ppe_per_round = 1, .duration_rounds = -1, .base_damage = 0,
        .damage_dice = 0, .damage_sides = 0, .is_mega_damage = false, .range_feet = 60,
        .area_effect_feet = 20, .school = SPELL_MYSTIC, .level_name = "Level 5",
        .casting_time_rounds = 2, .can_overwhelm = false, .is_ritual = false,
        .is_passive_bonus = false, .keywords = "control crowd restrain"
    },
    {
        .id = 13, .name = "Summon Lesser Creature", .description = "Call elemental (1d4 rounds)",
        .lpc_id = "summon_lesser_creature",
        .ppe_cost = 6, .ppe_per_round = 0, .duration_rounds = -1, .base_damage = 0,
        .damage_dice = 0, .damage_sides = 0, .is_mega_damage = false, .range_feet = 30,
        .area_effect_feet = 0, .school = SPELL_MYSTIC, .level_name = "Level 6",
        .casting_time_rounds = 3, .can_overwhelm = false, .is_ritual = true,
        .is_passive_bonus = false, .keywords = "summon creature elemental"
    },
    {
        .id = 14, .name = "Frenzy", .description = "Target attacks faster (+3 attacks)",
        .lpc_id = "frenzy",
        .ppe_cost = 4, .ppe_per_round = 0, .duration_rounds = 6, .base_damage = 0,
        .damage_dice = 0, .damage_sides = 0, .is_mega_damage = false, .range_feet = 30,
        .area_effect_feet = 0, .school = SPELL_BATTLE_MAGE, .level_name = "Level 5",
        .casting_time_rounds = 1, .can_overwhelm = false, .is_ritual = false,
        .is_passive_bonus = false, .keywords = "buff combat speed"
    },
    {
        .id = 15, .name = "Mirror Image", .description = "Create 1d4 duplicate illusions",
        .lpc_id = "mirror_image",
        .ppe_cost = 4, .ppe_per_round = 0, .duration_rounds = 20, .base_damage = 0,
        .damage_dice = 0, .damage_sides = 0, .is_mega_damage = false, .range_feet = 0,
        .area_effect_feet = 0, .school = SPELL_MYSTIC, .level_name = "Level 6",
        .casting_time_rounds = 2, .can_overwhelm = false, .is_ritual = false,
        .is_passive_bonus = false, .keywords = "defense illusion deception"
    },

    /* WIZARD GRADE SPELLS (16-25) - Level 10-15 */
    {
        .id = 16, .name = "Rift Teleportation", .description = "Open dimensional portal (50 feet)",
        .lpc_id = "rift_teleportation",
        .ppe_cost = 10, .ppe_per_round = 0, .duration_rounds = 10, .base_damage = 0,
        .damage_dice = 0, .damage_sides = 0, .is_mega_damage = false, .range_feet = -1,
        .area_effect_feet = 0, .school = SPELL_WIZARD, .level_name = "Level 10",
        .casting_time_rounds = 4, .can_overwhelm = false, .is_ritual = false,
        .is_passive_bonus = false, .keywords = "movement teleport rift"
    },
    {
        .id = 17, .name = "Magic Missile", .description = "1d6+1 per missile (up to IQ missiles)",
        .lpc_id = "magic_missile",
        .ppe_cost = 3, .ppe_per_round = 0, .duration_rounds = 1, .base_damage = 0,
        .damage_dice = 1, .damage_sides = 6, .is_mega_damage = true, .range_feet = 200,
        .area_effect_feet = 0, .school = SPELL_WIZARD, .level_name = "Level 4",
        .casting_time_rounds = 1, .can_overwhelm = true, .is_ritual = false,
        .is_passive_bonus = false, .keywords = "damage magic combat"
    },
    {
        .id = 18, .name = "Plague", .description = "Disease spreads to enemies in area",
        .lpc_id = "plague",
        .ppe_cost = 8, .ppe_per_round = 0, .duration_rounds = -1, .base_damage = 0,
        .damage_dice = 0, .damage_sides = 0, .is_mega_damage = false, .range_feet = 100,
        .area_effect_feet = 30, .school = SPELL_WIZARD, .level_name = "Level 12",
        .casting_time_rounds = 3, .can_overwhelm = false, .is_ritual = true,
        .is_passive_bonus = false, .keywords = "damage disease poison"
    },
    {
        .id = 19, .name = "Summon Greater Creature", .description = "Call powerful demon",
        .lpc_id = "summon_greater_creature",
        .ppe_cost = 10, .ppe_per_round = 0, .duration_rounds = -1, .base_damage = 0,
        .damage_dice = 0, .damage_sides = 0, .is_mega_damage = false, .range_feet = 50,
        .area_effect_feet = 0, .school = SPELL_WIZARD, .level_name = "Level 12",
        .casting_time_rounds = 5, .can_overwhelm = false, .is_ritual = true,
        .is_passive_bonus = false, .keywords = "summon creature demon"
    },
    {
        .id = 20, .name = "Meteor Storm", .description = "6d6 MD over 30-foot radius",
        .lpc_id = "meteor_storm",
        .ppe_cost = 12, .ppe_per_round = 0, .duration_rounds = 1, .base_damage = 0,
        .damage_dice = 6, .damage_sides = 6, .is_mega_damage = true, .range_feet = 300,
        .area_effect_feet = 30, .school = SPELL_WIZARD, .level_name = "Level 15",
        .casting_time_rounds = 3, .can_overwhelm = true, .is_ritual = false,
        .is_passive_bonus = false, .keywords = "damage fire area combat"
    },
    {
        .id = 21, .name = "Time Dilation", .description = "Move at 2x speed for 1d6 rounds",
        .lpc_id = "time_dilation",
        .ppe_cost = 10, .ppe_per_round = 0, .duration_rounds = 6, .base_damage = 0,
        .damage_dice = 0, .damage_sides = 0, .is_mega_damage = false, .range_feet = 0,
        .area_effect_feet = 0, .school = SPELL_WIZARD, .level_name = "Level 12",
        .casting_time_rounds = 2, .can_overwhelm = false, .is_ritual = false,
        .is_passive_bonus = false, .keywords = "buff speed movement time"
    },
    {
        .id = 22, .name = "Stone to Flesh", .description = "Reverse petrification curse",
        .lpc_id = "stone_to_flesh",
        .ppe_cost = 7, .ppe_per_round = 0, .duration_rounds = 1, .base_damage = 0,
        .damage_dice = 0, .damage_sides = 0, .is_mega_damage = false, .range_feet = 50,
        .area_effect_feet = 0, .school = SPELL_RITUAL, .level_name = "Level 10",
        .casting_time_rounds = 3, .can_overwhelm = false, .is_ritual = true,
        .is_passive_bonus = false, .keywords = "heal restore cure curse"
    },
    {
        .id = 23, .name = "Healing Circle", .description = "Heal all allies 3d6 HP",
        .lpc_id = "healing_circle",
        .ppe_cost = 6, .ppe_per_round = 0, .duration_rounds = 1, .base_damage = 0,
        .damage_dice = 3, .damage_sides = 6, .is_mega_damage = false, .range_feet = 50,
        .area_effect_feet = 30, .school = SPELL_RITUAL, .level_name = "Level 10",
        .casting_time_rounds = 2, .can_overwhelm = true, .is_ritual = false,
        .is_passive_bonus = false, .keywords = "heal recovery restoration"
    },
    {
        .id = 24, .name = "Enchant Item", .description = "Add magic bonuses to equipment",
        .lpc_id = "enchant_item",
        .ppe_cost = 5, .ppe_per_round = 0, .duration_rounds = -1, .base_damage = 0,
        .damage_dice = 0, .damage_sides = 0, .is_mega_damage = false, .range_feet = 0,
        .area_effect_feet = 0, .school = SPELL_RITUAL, .level_name = "Level 8",
        .casting_time_rounds = 4, .can_overwhelm = false, .is_ritual = true,
        .is_passive_bonus = false, .keywords = "item craft enchantment"
    },
    {
        .id = 25, .name = "Scrying", .description = "See through remote scrying orb",
        .lpc_id = "scrying",
        .ppe_cost = 4, .ppe_per_round = 1, .duration_rounds = -1, .base_damage = 0,
        .damage_dice = 0, .damage_sides = 0, .is_mega_damage = false, .range_feet = 5280,
        .area_effect_feet = 0, .school = SPELL_WIZARD, .level_name = "Level 8",
        .casting_time_rounds = 2, .can_overwhelm = false, .is_ritual = false,
        .is_passive_bonus = false, .keywords = "vision sense remote scry"
    },

    /* BATTLE MAGE SPELLS (26-31) - Combat Focused */
    {
        .id = 26, .name = "Power Fist", .description = "+2d6 damage to melee attack",
        .lpc_id = "power_fist",
        .ppe_cost = 3, .ppe_per_round = 0, .duration_rounds = 1, .base_damage = 0,
        .damage_dice = 2, .damage_sides = 6, .is_mega_damage = true, .range_feet = 0,
        .area_effect_feet = 0, .school = SPELL_BATTLE_MAGE, .level_name = "Level 3",
        .casting_time_rounds = 1, .can_overwhelm = false, .is_ritual = false,
        .is_passive_bonus = false, .keywords = "damage combat melee buff"
    },
    {
        .id = 27, .name = "Armor Enhancement", .description = "+50 MDC armor temporarily",
        .lpc_id = "armor_enhancement",
        .ppe_cost = 4, .ppe_per_round = 0, .duration_rounds = 10, .base_damage = 0,
        .damage_dice = 0, .damage_sides = 0, .is_mega_damage = false, .range_feet = 0,
        .area_effect_feet = 0, .school = SPELL_BATTLE_MAGE, .level_name = "Level 4",
        .casting_time_rounds = 1, .can_overwhelm = false, .is_ritual = false,
        .is_passive_bonus = true, .keywords = "defense armor protection"
    },
    {
        .id = 28, .name = "Smite", .description = "+4d6 damage on next attack",
        .lpc_id = "smite",
        .ppe_cost = 5, .ppe_per_round = 0, .duration_rounds = 2, .base_damage = 0,
        .damage_dice = 4, .damage_sides = 6, .is_mega_damage = true, .range_feet = 0,
        .area_effect_feet = 0, .school = SPELL_BATTLE_MAGE, .level_name = "Level 6",
        .casting_time_rounds = 1, .can_overwhelm = true, .is_ritual = false,
        .is_passive_bonus = false, .keywords = "damage combat buff attack"
    },
    {
        .id = 29, .name = "Protective Circle", .description = "Shield allies, +3 AR",
        .lpc_id = "protective_circle",
        .ppe_cost = 6, .ppe_per_round = 1, .duration_rounds = -1, .base_damage = 0,
        .damage_dice = 0, .damage_sides = 0, .is_mega_damage = false, .range_feet = 20,
        .area_effect_feet = 15, .school = SPELL_BATTLE_MAGE, .level_name = "Level 7",
        .casting_time_rounds = 2, .can_overwhelm = false, .is_ritual = false,
        .is_passive_bonus = true, .keywords = "defense protection area"
    },
    {
        .id = 30, .name = "Spell Reflection", .description = "Bounce magical attacks",
        .lpc_id = "spell_reflection",
        .ppe_cost = 5, .ppe_per_round = 1, .duration_rounds = -1, .base_damage = 0,
        .damage_dice = 0, .damage_sides = 0, .is_mega_damage = false, .range_feet = 0,
        .area_effect_feet = 0, .school = SPELL_WIZARD, .level_name = "Level 9",
        .casting_time_rounds = 2, .can_overwhelm = false, .is_ritual = false,
        .is_passive_bonus = true, .keywords = "defense protection magic"
    },
    {
        .id = 31, .name = "Combat Healing", .description = "Heal 2d6 HP during fight",
        .lpc_id = "combat_healing",
        .ppe_cost = 3, .ppe_per_round = 0, .duration_rounds = 1, .base_damage = 0,
        .damage_dice = 2, .damage_sides = 6, .is_mega_damage = false, .range_feet = 0,
        .area_effect_feet = 0, .school = SPELL_BATTLE_MAGE, .level_name = "Level 3",
        .casting_time_rounds = 1, .can_overwhelm = true, .is_ritual = false,
        .is_passive_bonus = false, .keywords = "heal recovery restoration"
    },

    /* RITUAL/CEREMONIAL SPELLS (32-33) */
    {
        .id = 32, .name = "Ritual Healing", .description = "Cure disease, poison, curses",
        .lpc_id = "ritual_healing",
        .ppe_cost = 4, .ppe_per_round = 0, .duration_rounds = 1, .base_damage = 0,
        .damage_dice = 0, .damage_sides = 0, .is_mega_damage = false, .range_feet = 0,
        .area_effect_feet = 0, .school = SPELL_RITUAL, .level_name = "Level 5",
        .casting_time_rounds = 3, .can_overwhelm = false, .is_ritual = true,
        .is_passive_bonus = false, .keywords = "heal cure disease poison"
    },
    {
        .id = 33, .name = "Resurrection", .description = "Bring character back from death",
        .lpc_id = "resurrection",
        .ppe_cost = 20, .ppe_per_round = 0, .duration_rounds = 1, .base_damage = 0,
        .damage_dice = 0, .damage_sides = 0, .is_mega_damage = false, .range_feet = 0,
        .area_effect_feet = 0, .school = SPELL_RITUAL, .level_name = "Level 20",
        .casting_time_rounds = 10, .can_overwhelm = false, .is_ritual = true,
        .is_passive_bonus = false, .keywords = "heal restore resurrection"
    },

    /* ENERGY BOLT (34) - Single-target concentrated MD blast */
    {
        .id = 34, .name = "Energy Bolt", .description = "1d6+2 MD concentrated energy blast",
        .lpc_id = "energy_bolt",
        .ppe_cost = 3, .ppe_per_round = 0, .duration_rounds = 1, .base_damage = 2,
        .damage_dice = 1, .damage_sides = 6, .is_mega_damage = true, .range_feet = 200,
        .area_effect_feet = 0, .school = SPELL_WIZARD, .level_name = "Level 3",
        .casting_time_rounds = 1, .can_overwhelm = true, .is_ritual = false,
        .is_passive_bonus = false, .keywords = "damage energy combat bolt"
    }
};

int MAGIC_SPELL_COUNT = 35;

/* =============== INITIALIZATION =============== */

void magic_init(void) {
    /* Verify spell database is loaded */
    if (MAGIC_SPELL_COUNT != 35) {
        fprintf(stderr, "WARNING: Magic database count mismatch! Expected 35, got %d\n",
                MAGIC_SPELL_COUNT);
    }
}

/* =============== SPELL LOOKUP =============== */

MagicSpell* magic_find_spell_by_id(int spell_id) {
    if (spell_id < 0 || spell_id >= MAGIC_SPELL_COUNT) {
        return NULL;
    }
    return &MAGIC_SPELLS[spell_id];
}

MagicSpell* magic_find_spell_by_name(const char *name) {
    if (!name) return NULL;

    for (int i = 0; i < MAGIC_SPELL_COUNT; i++) {
        if (strcasecmp(MAGIC_SPELLS[i].name, name) == 0) {
            return &MAGIC_SPELLS[i];
        }
    }
    return NULL;
}

MagicSpell* magic_find_spell_by_lpc_id(const char *lpc_id) {
    if (!lpc_id) return NULL;

    for (int i = 0; i < MAGIC_SPELL_COUNT; i++) {
        if (MAGIC_SPELLS[i].lpc_id &&
            strcasecmp(MAGIC_SPELLS[i].lpc_id, lpc_id) == 0) {
            return &MAGIC_SPELLS[i];
        }
    }
    return NULL;
}

KnownSpell* magic_find_known_spell(struct Character *ch, int spell_id) {
    if (!ch || !ch->magic.spells) return NULL;
    
    for (int i = 0; i < ch->magic.spell_count; i++) {
        if (ch->magic.spells[i].spell_id == spell_id) {
            return &ch->magic.spells[i];
        }
    }
    return NULL;
}

/* =============== ABILITY MANAGEMENT =============== */

void magic_init_abilities(struct Character *ch) {
    if (!ch) return;
    
    ch->magic.spells = NULL;
    ch->magic.spell_count = 0;
    
    /* Calculate PPE based on ME and IQ */
    ch->magic.ppe_base = (ch->stats.me * 2) + (ch->stats.iq / 2);
    ch->magic.ppe_max = ch->magic.ppe_base;
    ch->magic.ppe_current = ch->magic.ppe_max;
    ch->magic.ppe_recovery_rate = (ch->stats.me / 10) + 1;
    
    ch->magic.is_casting = false;
    ch->magic.casting_spell_id = -1;
    ch->magic.casting_rounds_remaining = 0;
    
    ch->magic.is_meditating = false;
    ch->magic.meditation_rounds_active = 0;
}

void magic_free_abilities(struct Character *ch) {
    if (!ch) return;
    
    if (ch->magic.spells) {
        free(ch->magic.spells);
        ch->magic.spells = NULL;
    }
    ch->magic.spell_count = 0;
}

void magic_learn_spell(struct Character *ch, int spell_id) {
    if (!ch) return;
    
    /* Check if already knows spell */
    if (magic_find_known_spell(ch, spell_id)) {
        return;  /* Already knows this spell */
    }
    
    /* Expand spells array */
    ch->magic.spell_count++;
    ch->magic.spells = realloc(ch->magic.spells, sizeof(KnownSpell) * ch->magic.spell_count);
    
    /* Add new spell at rank 1 */
    KnownSpell *new_spell = &ch->magic.spells[ch->magic.spell_count - 1];
    new_spell->spell_id = spell_id;
    new_spell->rank = 1;
    new_spell->total_casts = 0;
    new_spell->last_cast = time(NULL);
}

void magic_add_starting_spells(struct Character *ch, const char *occ_name) {
    if (!ch || !occ_name) return;
    
    if (strcasecmp(occ_name, "Ley Line Walker") == 0) {
        magic_learn_spell(ch, 0);   /* Magic Armor */
        magic_learn_spell(ch, 1);   /* Detect Magic */
        magic_learn_spell(ch, 2);   /* Light */
        magic_learn_spell(ch, 8);   /* Fireball */
        magic_learn_spell(ch, 9);   /* Lightning Bolt */
        magic_learn_spell(ch, 34);  /* Energy Bolt */
        ch->magic.ppe_max = 50;
        ch->magic.ppe_current = 50;
    }
    else if (strcasecmp(occ_name, "Warlock") == 0) {
        magic_learn_spell(ch, 0);   /* Magic Armor */
        magic_learn_spell(ch, 1);   /* Detect Magic */
        magic_learn_spell(ch, 7);   /* Dispel Magic Barrier */
        magic_learn_spell(ch, 6);   /* Alarm */
        magic_learn_spell(ch, 8);   /* Fireball */
        ch->magic.ppe_max = 45;
        ch->magic.ppe_current = 45;
    }
    else if (strcasecmp(occ_name, "Mystic Wizard") == 0) {
        magic_learn_spell(ch, 0);   /* Magic Armor */
        magic_learn_spell(ch, 1);   /* Detect Magic */
        magic_learn_spell(ch, 8);   /* Fireball */
        magic_learn_spell(ch, 9);   /* Lightning Bolt */
        magic_learn_spell(ch, 10);  /* Teleport */
        magic_learn_spell(ch, 12);  /* Web of Protection */
        ch->magic.ppe_max = 60;
        ch->magic.ppe_current = 60;
    }
    else if (strcasecmp(occ_name, "Techno-Wizard") == 0) {
        magic_learn_spell(ch, 0);   /* Magic Armor */
        magic_learn_spell(ch, 5);   /* Identify */
        magic_learn_spell(ch, 3);   /* Mend */
        magic_learn_spell(ch, 24);  /* Enchant Item */
        ch->magic.ppe_max = 40;
        ch->magic.ppe_current = 40;
    }
    else if (strcasecmp(occ_name, "Mystic") == 0) {
        magic_learn_spell(ch, 0);   /* Magic Armor */
        magic_learn_spell(ch, 1);   /* Detect Magic */
        magic_learn_spell(ch, 2);   /* Light */
        magic_learn_spell(ch, 8);   /* Fireball */
        ch->magic.ppe_max = 40;
        ch->magic.ppe_current = 40;
    }
    else if (strcasecmp(occ_name, "Shifter") == 0) {
        magic_learn_spell(ch, 1);   /* Detect Magic */
        magic_learn_spell(ch, 10);  /* Teleport */
        magic_learn_spell(ch, 0);   /* Magic Armor */
        ch->magic.ppe_max = 45;
        ch->magic.ppe_current = 45;
    }
    /* Vagabond, Headhunter, and other non-magic classes: no starting spells */
}

/* =============== PPE MANAGEMENT =============== */

int magic_get_ppe_max(struct Character *ch) {
    if (!ch) return 0;
    return ch->magic.ppe_max;
}

int magic_get_ppe_current(struct Character *ch) {
    if (!ch) return 0;
    return ch->magic.ppe_current;
}

void magic_set_ppe_current(struct Character *ch, int amount) {
    if (!ch) return;
    if (amount < 0) amount = 0;
    if (amount > ch->magic.ppe_max) amount = ch->magic.ppe_max;
    ch->magic.ppe_current = amount;
}

void magic_recover_ppe(struct Character *ch, int amount) {
    if (!ch) return;
    ch->magic.ppe_current += amount;
    if (ch->magic.ppe_current > ch->magic.ppe_max) {
        ch->magic.ppe_current = ch->magic.ppe_max;
    }
}

void magic_spend_ppe(struct Character *ch, int amount) {
    if (!ch) return;
    ch->magic.ppe_current -= amount;
    if (ch->magic.ppe_current < 0) {
        ch->magic.ppe_current = 0;
    }
}

bool magic_can_cast_spell(struct Character *ch, int spell_id) {
    if (!ch) return false;
    
    MagicSpell *spell = magic_find_spell_by_id(spell_id);
    if (!spell) return false;
    
    /* Check if knows spell */
    if (!magic_find_known_spell(ch, spell_id)) {
        return false;
    }
    
    /* Check PPE cost */
    if (ch->magic.ppe_current < spell->ppe_cost) {
        return false;
    }
    
    return true;
}

/* =============== SPELL CASTING (STUB) =============== */

bool magic_start_casting(PlayerSession *sess, struct Character *ch,
                         int spell_id, const char *target_name) {
    if (!sess || !ch) return false;
    
    if (!magic_can_cast_spell(ch, spell_id)) {
        send_to_player(sess, "You don't have enough PPE to cast that spell.\n");
        return false;
    }
    
    MagicSpell *spell = magic_find_spell_by_id(spell_id);
    if (!spell) return false;
    
    /* Begin casting */
    ch->magic.is_casting = true;
    ch->magic.casting_spell_id = spell_id;
    ch->magic.casting_rounds_remaining = spell->casting_time_rounds;
    
    send_to_player(sess, "You begin casting %s...\n", spell->name);
    
    return true;
}

bool magic_continue_casting(struct Character *ch) {
    if (!ch || !ch->magic.is_casting) return false;
    
    ch->magic.casting_rounds_remaining--;
    return ch->magic.casting_rounds_remaining > 0;
}

/* Apply 1d6 chain lightning to the nearest other target in the room,
 * excluding the primary NPC/player targets already struck. */
static void magic_chain_lightning(PlayerSession *caster,
                                   NPC *exclude_npc,
                                   PlayerSession *exclude_player,
                                   Room *room) {
    if (!caster || !room) return;

    NPC *chain_npc = NULL;
    PlayerSession *chain_player = NULL;

    /* Prefer chaining to another NPC first */
    for (int i = 0; i < room->num_npcs && !chain_npc; i++) {
        NPC *n = room->npcs[i];
        if (n && n->is_alive && n != exclude_npc) chain_npc = n;
    }
    if (!chain_npc) {
        for (int i = 0; i < room->num_players && !chain_player; i++) {
            PlayerSession *p = room->players[i];
            if (p && p != caster && p != exclude_player && p->state == STATE_PLAYING)
                chain_player = p;
        }
    }

    if (!chain_npc && !chain_player) return;

    int chain_dmg = 1 + (rand() % 6);  /* 1d6 chain damage (half of 2d6) */

    if (chain_npc) {
        char display[64];
        snprintf(display, sizeof(display), "%s", chain_npc->name);
        display[0] = (char)toupper((unsigned char)display[0]);
        send_to_player(caster, "Lightning arcs to %s for %d M.D.C.!\n",
                       display, chain_dmg);
        chain_npc->character.mdc -= chain_dmg;
        if (chain_npc->character.mdc < 0) chain_npc->character.mdc = 0;
        if (chain_npc->character.mdc == 0)
            npc_handle_death(chain_npc, caster);
    } else {
        send_to_player(caster, "Lightning arcs to %s for %d M.D.!\n",
                       chain_player->username, chain_dmg);
        send_to_player(chain_player, "%s's lightning bolt chains to you for %d M.D.!\n",
                       caster->username, chain_dmg);
        if (chain_player->character.health_type == MDC_ONLY) {
            chain_player->character.mdc -= chain_dmg;
            if (chain_player->character.mdc < 0) chain_player->character.mdc = 0;
        } else {
            int sdc_eq = chain_dmg * 100;
            if (sdc_eq >= chain_player->character.sdc) {
                sdc_eq -= chain_player->character.sdc;
                chain_player->character.sdc = 0;
                chain_player->character.hp -= sdc_eq;
                if (chain_player->character.hp < 0) chain_player->character.hp = 0;
            } else {
                chain_player->character.sdc -= sdc_eq;
            }
        }
        if (chain_player->character.hp <= 0 || chain_player->character.mdc <= 0)
            handle_player_death(chain_player, caster, NULL);
    }
}

bool magic_complete_cast(PlayerSession *sess, struct Character *ch) {
    if (!sess || !ch) return false;

    if (!ch->magic.is_casting) return false;

    int spell_id = ch->magic.casting_spell_id;
    MagicSpell *spell = magic_find_spell_by_id(spell_id);

    if (!spell) {
        send_to_player(sess, "Casting failed - unknown spell.\n");
        magic_interrupt_cast(ch);
        return false;
    }

    /* Spend PPE */
    magic_spend_ppe(ch, spell->ppe_cost);
    magic_record_spell_cast(ch, spell_id);

    /* Resolve target: explicit spell_target/spell_target_npc > combat_target > NULL (self) */
    PlayerSession *target_sess = NULL;
    NPC *target_npc = NULL;

    if (sess->spell_target_npc) {
        target_npc = sess->spell_target_npc;
    } else if (sess->spell_target) {
        target_sess = sess->spell_target;
    } else if (sess->in_combat && sess->combat_target) {
        target_sess = sess->combat_target;
    }

    /* Apply the spell effect — area vs. single target */
    if (spell->area_effect_feet > 0 && sess->current_room) {
        /* Area-effect spell (e.g. Fireball): hit all enemies in the room */
        Room *room = sess->current_room;
        int hit_count = 0;

        send_to_player(sess, "Your %s erupts in a %d-foot radius!\n",
                       spell->name, spell->area_effect_feet);

        for (int i = 0; i < room->num_npcs; i++) {
            NPC *n = room->npcs[i];
            if (n && n->is_alive) {
                magic_apply_effect_npc(sess, n, spell);
                hit_count++;
            }
        }
        for (int i = 0; i < room->num_players; i++) {
            PlayerSession *p = room->players[i];
            if (p && p != sess && p->state == STATE_PLAYING) {
                magic_apply_effect(sess, p, spell);
                hit_count++;
            }
        }
        if (hit_count == 0)
            send_to_player(sess, "Your %s detonates but finds no targets!\n", spell->name);

    } else if (target_npc) {
        /* Single-target NPC */
        magic_apply_effect_npc(sess, target_npc, spell);
        /* Lightning Bolt chains to a 2nd target */
        if (spell->id == 9 && sess->current_room)
            magic_chain_lightning(sess, target_npc, NULL, sess->current_room);

    } else {
        /* Single-target player (or self-cast) */
        magic_apply_effect(sess, target_sess, spell);
        /* Lightning Bolt chains to a 2nd target */
        if (spell->id == 9 && sess->current_room)
            magic_chain_lightning(sess, NULL, target_sess, sess->current_room);
    }

    /* Clear spell targets after use */
    sess->spell_target = NULL;
    sess->spell_target_npc = NULL;

    /* Broadcast to room */
    if (sess->current_room) {
        char room_msg[256];
        snprintf(room_msg, sizeof(room_msg), "%s completes a spell: %s!\r\n",
                 sess->username, spell->name);
        room_broadcast(sess->current_room, room_msg, sess);
    }

    /* Clean up casting state */
    ch->magic.is_casting = false;
    ch->magic.casting_spell_id = -1;
    ch->magic.casting_rounds_remaining = 0;

    return true;
}

/* =============== SPELL EFFECT APPLICATION =============== */

void magic_apply_effect(PlayerSession *caster, PlayerSession *target,
                        MagicSpell *spell) {
    if (!caster || !spell) return;

    Character *caster_ch = &caster->character;
    Character *target_ch = target ? &target->character : NULL;
    const char *target_name = target ? target->username : caster->username;

    /* --- Damage spells --- */
    if (spell->damage_dice > 0 && spell->damage_sides > 0) {
        /* Need a valid target that isn't the caster for offensive spells */
        if (!target || target == caster) {
            send_to_player(caster,
                "You must be in combat to cast %s offensively.\n", spell->name);
            return;
        }

        /* Roll damage */
        int damage = 0;
        for (int i = 0; i < spell->damage_dice; i++) {
            damage += (rand() % spell->damage_sides) + 1;
        }
        /* Base damage bonus (e.g. Energy Bolt +2) */
        damage += spell->base_damage;

        /* Rank bonus: +1 damage per rank above 1 */
        KnownSpell *ks = magic_find_known_spell(caster_ch, spell->id);
        if (ks && ks->rank > 1) {
            damage += ks->rank - 1;
        }

        /* Check for healing keywords */
        if (strstr(spell->keywords, "heal") != NULL) {
            /* Healing spell: apply to target (or caster if self-targeted) */
            PlayerSession *heal_target = target ? target : caster;
            Character *heal_ch = &heal_target->character;

            if (heal_ch->health_type == MDC_ONLY) {
                heal_ch->mdc += damage;
                if (heal_ch->mdc > heal_ch->max_mdc) heal_ch->mdc = heal_ch->max_mdc;
                send_to_player(caster, "Your %s restores %d M.D.C. to %s!\n",
                               spell->name, damage, heal_target->username);
            } else {
                heal_ch->hp += damage;
                if (heal_ch->hp > heal_ch->max_hp) heal_ch->hp = heal_ch->max_hp;
                send_to_player(caster, "Your %s heals %s for %d HP!\n",
                               spell->name, heal_target->username, damage);
            }
            if (heal_target != caster) {
                send_to_player(heal_target,
                    "%s's %s heals you for %d!\n",
                    caster->username, spell->name, damage);
            }
            return;
        }

        /* Offensive damage */
        if (spell->is_mega_damage) {
            /* MDC damage - apply to MDC pool first, overflow to SDC/HP */
            if (target_ch->health_type == MDC_ONLY) {
                /* Godmode check */
                if (target->is_godmode) {
                    send_to_player(caster,
                        "Your %s fizzles against %s's divine protection!\n",
                        spell->name, target_name);
                    return;
                }
                target_ch->mdc -= damage;
                if (target_ch->mdc < 0) target_ch->mdc = 0;
                send_to_player(caster,
                    "Your %s blasts %s for %d M.D.C.!\n",
                    spell->name, target_name, damage);
                send_to_player(target,
                    "%s's %s hits you for %d M.D.C.!\n",
                    caster->username, spell->name, damage);
            } else {
                /* MDC spell vs SDC creature: x100 conversion */
                int sdc_damage = damage * 100;
                if (target->is_godmode) {
                    send_to_player(caster,
                        "Your %s fizzles against %s's divine protection!\n",
                        spell->name, target_name);
                    return;
                }
                /* Apply to SDC first, overflow to HP */
                if (sdc_damage > 0 && target_ch->sdc > 0) {
                    if (sdc_damage >= target_ch->sdc) {
                        sdc_damage -= target_ch->sdc;
                        target_ch->sdc = 0;
                    } else {
                        target_ch->sdc -= sdc_damage;
                        sdc_damage = 0;
                    }
                }
                if (sdc_damage > 0) {
                    target_ch->hp -= sdc_damage;
                    if (target_ch->hp < 0) target_ch->hp = 0;
                }
                send_to_player(caster,
                    "Your %s devastates %s for %d M.D. (%d S.D.C. equivalent)!\n",
                    spell->name, target_name, damage, damage * 100);
                send_to_player(target,
                    "%s's %s devastates you for %d M.D.!\n",
                    caster->username, spell->name, damage);
            }
        } else {
            /* SDC damage */
            if (target->is_godmode) {
                send_to_player(caster,
                    "Your %s fizzles against %s's divine protection!\n",
                    spell->name, target_name);
                return;
            }
            int remaining = damage;
            if (remaining > 0 && target_ch->sdc > 0) {
                if (remaining >= target_ch->sdc) {
                    remaining -= target_ch->sdc;
                    target_ch->sdc = 0;
                } else {
                    target_ch->sdc -= remaining;
                    remaining = 0;
                }
            }
            if (remaining > 0) {
                target_ch->hp -= remaining;
                if (target_ch->hp < 0) target_ch->hp = 0;
            }
            send_to_player(caster,
                "Your %s hits %s for %d S.D.C.!\n",
                spell->name, target_name, damage);
            send_to_player(target,
                "%s's %s hits you for %d S.D.C.!\n",
                caster->username, spell->name, damage);
        }

        /* Check for death */
        if (target_ch->hp <= 0) {
            send_to_player(caster, "%s collapses from your spell!\n", target_name);
            handle_player_death(target, caster, NULL);
        }
        return;
    }

    /* --- Passive/buff spells --- */
    if (spell->is_passive_bonus) {
        send_to_player(caster,
            "You cast %s! %s\n", spell->name, spell->description);
        return;
    }

    /* --- Utility/other spells --- */
    send_to_player(caster,
        "You cast %s. %s\n", spell->name, spell->description);
}

/* Apply spell effect to an NPC target */
void magic_apply_effect_npc(PlayerSession *caster, NPC *target, MagicSpell *spell) {
    if (!caster || !target || !spell) return;

    Character *caster_ch = &caster->character;
    Character *target_ch = &target->character;
    char display[64];
    snprintf(display, sizeof(display), "%s", target->name);
    display[0] = (char)toupper((unsigned char)display[0]);

    /* Only handle damage spells on NPCs */
    if (spell->damage_dice <= 0 || spell->damage_sides <= 0) {
        send_to_player(caster, "That spell has no effect on %s.\n", display);
        return;
    }

    /* Roll damage */
    int damage = 0;
    for (int i = 0; i < spell->damage_dice; i++) {
        damage += (rand() % spell->damage_sides) + 1;
    }
    /* Base damage bonus (e.g. Energy Bolt +2) */
    damage += spell->base_damage;

    /* Rank bonus */
    KnownSpell *ks = magic_find_known_spell(caster_ch, spell->id);
    if (ks && ks->rank > 1) {
        damage += ks->rank - 1;
    }

    /* Apply damage based on health type */
    if (target_ch->health_type == MDC_ONLY) {
        if (spell->is_mega_damage) {
            target_ch->mdc -= damage;
            if (target_ch->mdc < 0) target_ch->mdc = 0;
            send_to_player(caster, "Your %s blasts %s for %d M.D.C.!\n",
                           spell->name, display, damage);
        } else {
            /* SDC spell vs MDC creature: 1/100 */
            int md = damage / 100;
            if (md < 1) md = 1;
            target_ch->mdc -= md;
            if (target_ch->mdc < 0) target_ch->mdc = 0;
            send_to_player(caster, "Your %s barely scratches %s for %d M.D.C.!\n",
                           spell->name, display, md);
        }
    } else {
        /* SDC/HP creature */
        int remaining = damage;
        if (spell->is_mega_damage) remaining *= 100;
        if (remaining > 0 && target_ch->sdc > 0) {
            if (remaining >= target_ch->sdc) {
                remaining -= target_ch->sdc;
                target_ch->sdc = 0;
            } else {
                target_ch->sdc -= remaining;
                remaining = 0;
            }
        }
        if (remaining > 0) {
            target_ch->hp -= remaining;
            if (target_ch->hp < 0) target_ch->hp = 0;
        }
        send_to_player(caster, "Your %s hits %s for %d damage!\n",
                       spell->name, display, damage);
    }

    /* Check for death */
    bool dead = false;
    if (target_ch->health_type == MDC_ONLY) {
        dead = (target_ch->mdc <= 0);
    } else {
        dead = (target_ch->hp <= 0);
    }

    if (dead) {
        npc_handle_death(target, caster);
    }
}

void magic_interrupt_cast(struct Character *ch) {
    if (!ch) return;
    ch->magic.is_casting = false;
    ch->magic.casting_spell_id = -1;
    ch->magic.casting_rounds_remaining = 0;
}

/* =============== SPELL COMMAND HANDLER =============== */

bool magic_spell_command(PlayerSession *sess, const char *cmd,
                         const char *args) {
    if (!sess || !cmd) return false;

    /* Look up spell by lpc_id (e.g. "fireball", "magic_missile") */
    MagicSpell *spell = magic_find_spell_by_lpc_id(cmd);
    if (!spell) return false;

    /* Check if the player knows this spell */
    Character *ch = &sess->character;
    if (!magic_find_known_spell(ch, spell->id)) {
        return false;  /* Don't claim the command if they don't know it */
    }

    /* Resolve target from args */
    sess->spell_target = NULL;
    sess->spell_target_npc = NULL;

    if (args && *args) {
        Room *room = sess->current_room;
        if (room) {
            PlayerSession *tp = NULL;
            NPC *tn = NULL;
            int res = resolve_target(room, args, sess, &tp, &tn);
            if (res == 1) {
                sess->spell_target = tp;
            } else if (res == 2) {
                sess->spell_target_npc = tn;
            } else {
                send_to_player(sess, "You don't see '%s' here.\n", args);
                return true;
            }
        }
    } else if (sess->in_combat && sess->combat_target) {
        sess->spell_target = sess->combat_target;
    }
    /* else: spell_target stays NULL (self-cast) */

    /* Start casting */
    magic_start_casting(sess, ch, spell->id, args ? args : "");
    return true;
}

/* =============== DISPLAY =============== */

void magic_display_spells(PlayerSession *sess) {
    if (!sess) return;
    
    Character *ch = &sess->character;
    
    send_to_player(sess, "=== KNOWN SPELLS ===\n");
    
    if (ch->magic.spell_count == 0) {
        send_to_player(sess, "You have no magic spells.\n");
        return;
    }
    
    for (int i = 0; i < ch->magic.spell_count; i++) {
        KnownSpell *ks = &ch->magic.spells[i];
        MagicSpell *spell = magic_find_spell_by_id(ks->spell_id);
        
        if (spell) {
            send_to_player(sess, "%d. %s (%d PPE) [RANK %d] - %s\n   %s\n",
                           i + 1, spell->name, spell->ppe_cost, ks->rank, spell->level_name,
                           spell->description);
        }
    }
    
    send_to_player(sess, "\n");
}

void magic_display_ppe(PlayerSession *sess) {
    if (!sess) return;
    
    Character *ch = &sess->character;
    int recovery = ch->magic.ppe_recovery_rate;
    
    send_to_player(sess, "PPE: %d/%d (%d%%) - +%d per round\n",
                   ch->magic.ppe_current, ch->magic.ppe_max,
                   (ch->magic.ppe_current * 100) / ch->magic.ppe_max,
                   recovery);
}

/* =============== ADVANCEMENT =============== */

void magic_record_spell_cast(struct Character *ch, int spell_id) {
    if (!ch) return;
    
    KnownSpell *ks = magic_find_known_spell(ch, spell_id);
    if (!ks) return;
    
    ks->total_casts++;
    ks->last_cast = time(NULL);
    
    magic_check_spell_rank_advance(ch, spell_id);
}

void magic_check_spell_rank_advance(struct Character *ch, int spell_id) {
    if (!ch) return;
    
    KnownSpell *ks = magic_find_known_spell(ch, spell_id);
    if (!ks) return;
    
    /* Advancement table: 40, 60, 80, 100, 120, 140, 160, 180, 200 casts */
    int advancement_table[] = {0, 40, 60, 80, 100, 120, 140, 160, 180, 200};
    
    for (int rank = 1; rank < 10; rank++) {
        if (ks->rank == rank && ks->total_casts >= advancement_table[rank + 1]) {
            ks->rank++;
            return;
        }
    }
}

/* =============== TICKS =============== */

void magic_spell_tick(struct Character *ch, struct PlayerSession *sess) {
    if (!ch || !sess) return;

    /* Recover PPE naturally each round */
    magic_recover_ppe(ch, ch->magic.ppe_recovery_rate);

    /* Handle active casting */
    if (ch->magic.is_casting && ch->magic.casting_rounds_remaining > 0) {
        ch->magic.casting_rounds_remaining--;
        if (ch->magic.casting_rounds_remaining <= 0) {
            /* Casting complete - trigger the spell */
            magic_complete_cast(sess, ch);
        } else {
            MagicSpell *spell = magic_find_spell_by_id(ch->magic.casting_spell_id);
            if (spell) {
                send_to_player(sess, "You continue casting %s... (%d rounds remaining)\n",
                               spell->name, ch->magic.casting_rounds_remaining);
            }
        }
    }
}

void magic_meditate_tick(struct Character *ch) {
    if (!ch) return;

    if (ch->magic.is_meditating && ch->magic.meditation_rounds_active > 0) {
        /* Recover +1d6 PPE per meditation round */
        int recover = 1 + (rand() % 6);  /* 1d6 */
        magic_recover_ppe(ch, recover);
        ch->magic.meditation_rounds_active--;

        if (ch->magic.meditation_rounds_active <= 0) {
            ch->magic.is_meditating = false;
        }
    }
}
