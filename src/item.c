#include "item.h"
#include "chargen.h"
#include "room.h"
#include "session_internal.h"
#include "debug.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <strings.h>

/* External function declaration */
extern void send_to_player(PlayerSession *sess, const char *fmt, ...);

/* Item Template Database */
Item ITEM_TEMPLATES[TOTAL_ITEM_TEMPLATES];

/* Initialize item system and database */
void item_init(void) {
    DEBUG_LOG("Initializing item system...");
    
    /* ========== MELEE WEAPONS (0-9) ========== */
    
    /* 0: Vibro-Knife */
    ITEM_TEMPLATES[0] = (Item){
        .id = 0, .name = strdup("Vibro-Knife"), .description = strdup("A small vibrating energy blade, quick and deadly"),
        .type = ITEM_WEAPON_MELEE, .weapon_type = WEAPON_KNIFE, .weight = 2, .value = 5000,
        .stats = {.damage_dice = 1, .damage_sides = 6, .damage_bonus = 0, .strike_bonus = 1, .is_mega_damage = true}
    };
    
    /* 1: Vibro-Blade */
    ITEM_TEMPLATES[1] = (Item){
        .id = 1, .name = strdup("Vibro-Blade"), .description = strdup("Standard vibrating energy blade, reliable and effective"),
        .type = ITEM_WEAPON_MELEE, .weapon_type = WEAPON_SWORD, .weight = 5, .value = 10000,
        .stats = {.damage_dice = 2, .damage_sides = 4, .damage_bonus = 0, .strike_bonus = 0, .is_mega_damage = true}
    };
    
    /* 2: Vibro-Sword */
    ITEM_TEMPLATES[2] = (Item){
        .id = 2, .name = strdup("Vibro-Sword"), .description = strdup("High-quality vibrating sword, balanced and powerful"),
        .type = ITEM_WEAPON_MELEE, .weapon_type = WEAPON_SWORD, .weight = 8, .value = 15000,
        .stats = {.damage_dice = 2, .damage_sides = 6, .damage_bonus = 0, .strike_bonus = 0, .is_mega_damage = true}
    };
    
    /* 3: Vibro-Axe */
    ITEM_TEMPLATES[3] = (Item){
        .id = 3, .name = strdup("Vibro-Axe"), .description = strdup("Heavy vibrating axe, devastating but slow"),
        .type = ITEM_WEAPON_MELEE, .weapon_type = WEAPON_AXE, .weight = 12, .value = 18000,
        .stats = {.damage_dice = 3, .damage_sides = 6, .damage_bonus = 0, .strike_bonus = -1, .is_mega_damage = true}
    };
    
    /* 4: Psi-Sword */
    ITEM_TEMPLATES[4] = (Item){
        .id = 4, .name = strdup("Psi-Sword"), .description = strdup("Psychic energy blade, light as thought and deadly"),
        .type = ITEM_WEAPON_MELEE, .weapon_type = WEAPON_SWORD, .weight = 1, .value = 25000,
        .stats = {.damage_dice = 4, .damage_sides = 6, .damage_bonus = 0, .strike_bonus = 2, .is_mega_damage = true}
    };
    
    /* 5: Neural Mace */
    ITEM_TEMPLATES[5] = (Item){
        .id = 5, .name = strdup("Neural Mace"), .description = strdup("Stun weapon that disrupts nervous system"),
        .type = ITEM_WEAPON_MELEE, .weapon_type = WEAPON_AXE, .weight = 6, .value = 12000,
        .stats = {.damage_dice = 1, .damage_sides = 6, .damage_bonus = 0, .strike_bonus = 0, .is_mega_damage = true}
    };
    
    /* 6: Wooden Club */
    ITEM_TEMPLATES[6] = (Item){
        .id = 6, .name = strdup("Wooden Club"), .description = strdup("Primitive wooden weapon, basic but functional"),
        .type = ITEM_WEAPON_MELEE, .weapon_type = WEAPON_AXE, .weight = 4, .value = 10,
        .stats = {.damage_dice = 1, .damage_sides = 4, .damage_bonus = 0, .strike_bonus = 0, .is_mega_damage = false}
    };
    
    /* 7: Steel Knife */
    ITEM_TEMPLATES[7] = (Item){
        .id = 7, .name = strdup("Steel Knife"), .description = strdup("Pre-Rifts steel blade, common and simple"),
        .type = ITEM_WEAPON_MELEE, .weapon_type = WEAPON_KNIFE, .weight = 1, .value = 50,
        .stats = {.damage_dice = 1, .damage_sides = 6, .damage_bonus = 0, .strike_bonus = 0, .is_mega_damage = false}
    };
    
    /* 8: Steel Sword */
    ITEM_TEMPLATES[8] = (Item){
        .id = 8, .name = strdup("Steel Sword"), .description = strdup("Pre-Rifts steel sword, still useful for SDC foes"),
        .type = ITEM_WEAPON_MELEE, .weapon_type = WEAPON_SWORD, .weight = 5, .value = 200,
        .stats = {.damage_dice = 2, .damage_sides = 6, .damage_bonus = 0, .strike_bonus = 0, .is_mega_damage = false}
    };
    
    /* 9: Power Fist */
    ITEM_TEMPLATES[9] = (Item){
        .id = 9, .name = strdup("Power Fist"), .description = strdup("Powered gauntlet weapon, packs a punch"),
        .type = ITEM_WEAPON_MELEE, .weapon_type = WEAPON_UNARMED, .weight = 7, .value = 8000,
        .stats = {.damage_dice = 2, .damage_sides = 4, .damage_bonus = 0, .strike_bonus = 1, .is_mega_damage = true}
    };
    
    /* ========== ENERGY WEAPONS (10-17) ========== */
    
    /* 10: NG-33 Laser Pistol */
    ITEM_TEMPLATES[10] = (Item){
        .id = 10, .name = strdup("NG-33 Laser Pistol"), .description = strdup("Northern Gun laser sidearm, reliable and accurate"),
        .type = ITEM_WEAPON_RANGED, .weapon_type = WEAPON_PISTOL, .weight = 3, .value = 8000,
        .stats = {.damage_dice = 2, .damage_sides = 6, .damage_bonus = 0, .strike_bonus = 1, .is_mega_damage = true}
    };
    
    /* 11: NG-57 Ion Blaster */
    ITEM_TEMPLATES[11] = (Item){
        .id = 11, .name = strdup("NG-57 Ion Blaster"), .description = strdup("Heavy ion pistol, powerful but energy-hungry"),
        .type = ITEM_WEAPON_RANGED, .weapon_type = WEAPON_PISTOL, .weight = 5, .value = 12000,
        .stats = {.damage_dice = 3, .damage_sides = 6, .damage_bonus = 0, .strike_bonus = 0, .is_mega_damage = true}
    };
    
    /* 12: Wilk's Laser Rifle */
    ITEM_TEMPLATES[12] = (Item){
        .id = 12, .name = strdup("Wilk's Laser Rifle"), .description = strdup("Wilk's standard laser rifle, excellent balance of power and range"),
        .type = ITEM_WEAPON_RANGED, .weapon_type = WEAPON_RIFLE, .weight = 8, .value = 16000,
        .stats = {.damage_dice = 3, .damage_sides = 6, .damage_bonus = 0, .strike_bonus = 0, .is_mega_damage = true}
    };
    
    /* 13: CP-40 Pulse Rifle */
    ITEM_TEMPLATES[13] = (Item){
        .id = 13, .name = strdup("CP-40 Pulse Rifle"), .description = strdup("Burst-fire pulse laser, rapid damage output"),
        .type = ITEM_WEAPON_RANGED, .weapon_type = WEAPON_RIFLE, .weight = 10, .value = 20000,
        .stats = {.damage_dice = 4, .damage_sides = 6, .damage_bonus = 0, .strike_bonus = 0, .is_mega_damage = true}
    };
    
    /* 14: NG-101 Rail Gun */
    ITEM_TEMPLATES[14] = (Item){
        .id = 14, .name = strdup("NG-101 Rail Gun"), .description = strdup("Electromagnetic rail gun, anti-armor capability"),
        .type = ITEM_WEAPON_RANGED, .weapon_type = WEAPON_HEAVY, .weight = 15, .value = 40000,
        .stats = {.damage_dice = 1, .damage_sides = 4, .damage_bonus = 0, .strike_bonus = -1, .is_mega_damage = true}
    };
    
    /* 15: Coalition C-12 Laser */
    ITEM_TEMPLATES[15] = (Item){
        .id = 15, .name = strdup("Coalition C-12 Laser"), .description = strdup("CS standard issue laser rifle, Coalition workhorse"),
        .type = ITEM_WEAPON_RANGED, .weapon_type = WEAPON_RIFLE, .weight = 9, .value = 18000,
        .stats = {.damage_dice = 2, .damage_sides = 6, .damage_bonus = 0, .strike_bonus = 0, .is_mega_damage = true}
    };
    
    /* 16: Plasma Ejector */
    ITEM_TEMPLATES[16] = (Item){
        .id = 16, .name = strdup("Plasma Ejector"), .description = strdup("Heavy plasma weapon, devastating area damage"),
        .type = ITEM_WEAPON_RANGED, .weapon_type = WEAPON_HEAVY, .weight = 20, .value = 60000,
        .stats = {.damage_dice = 1, .damage_sides = 6, .damage_bonus = 0, .strike_bonus = -2, .is_mega_damage = true}
    };
    
    /* 17: Particle Beam Rifle */
    ITEM_TEMPLATES[17] = (Item){
        .id = 17, .name = strdup("Particle Beam Rifle"), .description = strdup("Precise particle beam, excellent accuracy"),
        .type = ITEM_WEAPON_RANGED, .weapon_type = WEAPON_ENERGY, .weight = 12, .value = 50000,
        .stats = {.damage_dice = 1, .damage_sides = 4, .damage_bonus = 0, .strike_bonus = 2, .is_mega_damage = true}
    };
    
    /* ========== CONVENTIONAL WEAPONS (18-22) ========== */
    
    /* 18: .45 Pistol */
    ITEM_TEMPLATES[18] = (Item){
        .id = 18, .name = strdup(".45 Pistol"), .description = strdup("Pre-Rifts .45 caliber pistol, reliable sidearm"),
        .type = ITEM_WEAPON_RANGED, .weapon_type = WEAPON_PISTOL, .weight = 3, .value = 500,
        .stats = {.damage_dice = 4, .damage_sides = 6, .damage_bonus = 0, .strike_bonus = 0, .is_mega_damage = false}
    };
    
    /* 19: 9mm Pistol */
    ITEM_TEMPLATES[19] = (Item){
        .id = 19, .name = strdup("9mm Pistol"), .description = strdup("Light 9mm pistol, easy to conceal"),
        .type = ITEM_WEAPON_RANGED, .weapon_type = WEAPON_PISTOL, .weight = 2, .value = 300,
        .stats = {.damage_dice = 3, .damage_sides = 6, .damage_bonus = 0, .strike_bonus = 1, .is_mega_damage = false}
    };
    
    /* 20: Combat Shotgun */
    ITEM_TEMPLATES[20] = (Item){
        .id = 20, .name = strdup("Combat Shotgun"), .description = strdup("Pump-action shotgun, devastating at close range"),
        .type = ITEM_WEAPON_RANGED, .weapon_type = WEAPON_RIFLE, .weight = 8, .value = 800,
        .stats = {.damage_dice = 5, .damage_sides = 6, .damage_bonus = 0, .strike_bonus = -1, .is_mega_damage = false}
    };
    
    /* 21: Hunting Rifle */
    ITEM_TEMPLATES[21] = (Item){
        .id = 21, .name = strdup("Hunting Rifle"), .description = strdup("Long-range hunting rifle, excellent accuracy"),
        .type = ITEM_WEAPON_RANGED, .weapon_type = WEAPON_RIFLE, .weight = 9, .value = 1000,
        .stats = {.damage_dice = 5, .damage_sides = 6, .damage_bonus = 0, .strike_bonus = 1, .is_mega_damage = false}
    };
    
    /* 22: Assault Rifle */
    ITEM_TEMPLATES[22] = (Item){
        .id = 22, .name = strdup("Assault Rifle"), .description = strdup("Military assault rifle, burst-fire capable"),
        .type = ITEM_WEAPON_RANGED, .weapon_type = WEAPON_RIFLE, .weight = 10, .value = 1500,
        .stats = {.damage_dice = 5, .damage_sides = 6, .damage_bonus = 0, .strike_bonus = 0, .is_mega_damage = false}
    };
    
    /* ========== SPECIAL WEAPONS (23-24) ========== */
    
    /* 23: Boom Gun */
    ITEM_TEMPLATES[23] = (Item){
        .id = 23, .name = strdup("Boom Gun"), .description = strdup("Glitter Boy arm cannon, legendary firepower"),
        .type = ITEM_WEAPON_RANGED, .weapon_type = WEAPON_HEAVY, .weight = 50, .value = 200000,
        .stats = {.damage_dice = 3, .damage_sides = 6, .damage_bonus = 0, .strike_bonus = 0, .is_mega_damage = true}
    };
    
    /* 24: TW Fire Bolt Staff */
    ITEM_TEMPLATES[24] = (Item){
        .id = 24, .name = strdup("TW Fire Bolt Staff"), .description = strdup("Techno-Wizard fire staff, channels magical flame"),
        .type = ITEM_WEAPON_RANGED, .weapon_type = WEAPON_STAFF, .weight = 4, .value = 30000,
        .stats = {.damage_dice = 6, .damage_sides = 6, .damage_bonus = 0, .strike_bonus = 1, .is_mega_damage = true}
    };
    
    /* ========== ARMOR (25-39) ========== */
    
    /* 25: Leather Jacket */
    ITEM_TEMPLATES[25] = (Item){
        .id = 25, .name = strdup("Leather Jacket"), .description = strdup("Heavy leather jacket, basic protection"),
        .type = ITEM_ARMOR, .weight = 5, .value = 100,
        .stats = {.ar = 10, .sdc_mdc = 20, .dodge_bonus = 0, .is_mega_damage = false}
    };
    
    /* 26: Urban Warrior EBA */
    ITEM_TEMPLATES[26] = (Item){
        .id = 26, .name = strdup("Urban Warrior EBA"), .description = strdup("Light environmental body armor for city operations"),
        .type = ITEM_ARMOR, .weight = 12, .value = 15000,
        .stats = {.ar = 12, .sdc_mdc = 40, .dodge_bonus = 1, .is_mega_damage = false}
    };
    
    /* 27: Light EBA */
    ITEM_TEMPLATES[27] = (Item){
        .id = 27, .name = strdup("Light EBA"), .description = strdup("Light environmental body armor, good mobility"),
        .type = ITEM_ARMOR, .weight = 15, .value = 20000,
        .stats = {.ar = 14, .sdc_mdc = 60, .dodge_bonus = 0, .is_mega_damage = true}
    };
    
    /* 28: Huntsman Armor */
    ITEM_TEMPLATES[28] = (Item){
        .id = 28, .name = strdup("Huntsman Armor"), .description = strdup("Wilderness armor, enhances stealth"),
        .type = ITEM_ARMOR, .weight = 14, .value = 22000,
        .stats = {.ar = 13, .sdc_mdc = 50, .dodge_bonus = 0, .parry_bonus = 0, .is_mega_damage = true}
    };
    
    /* 29: Bushman Armor */
    ITEM_TEMPLATES[29] = (Item){
        .id = 29, .name = strdup("Bushman Armor"), .description = strdup("Light wilderness armor, excellent mobility"),
        .type = ITEM_ARMOR, .weight = 13, .value = 18000,
        .stats = {.ar = 13, .sdc_mdc = 45, .dodge_bonus = 1, .is_mega_damage = true}
    };
    
    /* 30: Plastic-Man Armor */
    ITEM_TEMPLATES[30] = (Item){
        .id = 30, .name = strdup("Plastic-Man Armor"), .description = strdup("Standard EBA, reliable protection"),
        .type = ITEM_ARMOR, .weight = 18, .value = 25000,
        .stats = {.ar = 15, .sdc_mdc = 80, .dodge_bonus = 0, .is_mega_damage = true}
    };
    
    /* 31: NG-A7 Armor */
    ITEM_TEMPLATES[31] = (Item){
        .id = 31, .name = strdup("NG-A7 Armor"), .description = strdup("Northern Gun armor, well-balanced design"),
        .type = ITEM_ARMOR, .weight = 19, .value = 28000,
        .stats = {.ar = 16, .sdc_mdc = 90, .dodge_bonus = 0, .is_mega_damage = true}
    };
    
    /* 32: Coalition Dead Boy Armor */
    ITEM_TEMPLATES[32] = (Item){
        .id = 32, .name = strdup("Coalition Dead Boy Armor"), .description = strdup("CS standard grunt armor, intimidating skull design"),
        .type = ITEM_ARMOR, .weight = 20, .value = 30000,
        .stats = {.ar = 17, .sdc_mdc = 100, .dodge_bonus = 0, .is_mega_damage = true}
    };
    
    /* 33: Juicer Plate Armor */
    ITEM_TEMPLATES[33] = (Item){
        .id = 33, .name = strdup("Juicer Plate Armor"), .description = strdup("Light armor for enhanced reflexes, doesn't slow Juicers"),
        .type = ITEM_ARMOR, .weight = 16, .value = 32000,
        .stats = {.ar = 15, .sdc_mdc = 70, .dodge_bonus = 3, .is_mega_damage = true}
    };
    
    /* 34: Cyber-Knight Armor */
    ITEM_TEMPLATES[34] = (Item){
        .id = 34, .name = strdup("Cyber-Knight Armor"), .description = strdup("Psionically enhanced armor, aids in parrying"),
        .type = ITEM_ARMOR, .weight = 17, .value = 35000,
        .stats = {.ar = 16, .sdc_mdc = 85, .parry_bonus = 2, .is_mega_damage = true}
    };
    
    /* 35: Coalition Enforcer Armor */
    ITEM_TEMPLATES[35] = (Item){
        .id = 35, .name = strdup("Coalition Enforcer Armor"), .description = strdup("Heavy CS armor for frontline troops"),
        .type = ITEM_ARMOR, .weight = 25, .value = 40000,
        .stats = {.ar = 18, .sdc_mdc = 120, .dodge_bonus = 0, .is_mega_damage = true}
    };
    
    /* 36: Triax X-10 Predator Armor */
    ITEM_TEMPLATES[36] = (Item){
        .id = 36, .name = strdup("Triax X-10 Predator Armor"), .description = strdup("German power armor, advanced technology"),
        .type = ITEM_ARMOR, .weight = 28, .value = 50000,
        .stats = {.ar = 18, .sdc_mdc = 130, .dodge_bonus = 0, .is_mega_damage = true}
    };
    
    /* 37: Glitter Boy Armor */
    ITEM_TEMPLATES[37] = (Item){
        .id = 37, .name = strdup("Glitter Boy Armor"), .description = strdup("Legendary pre-Rifts power armor, nearly indestructible"),
        .type = ITEM_ARMOR, .weight = 50, .value = 500000,
        .stats = {.ar = 20, .sdc_mdc = 770, .dodge_bonus = 0, .is_mega_damage = true}
    };
    
    /* 38: Samurai EBA */
    ITEM_TEMPLATES[38] = (Item){
        .id = 38, .name = strdup("Samurai EBA"), .description = strdup("Japanese-designed armor with traditional aesthetics"),
        .type = ITEM_ARMOR, .weight = 22, .value = 38000,
        .stats = {.ar = 17, .sdc_mdc = 110, .dodge_bonus = 0, .is_mega_damage = true}
    };
    
    /* 39: SAMAS Power Armor */
    ITEM_TEMPLATES[39] = (Item){
        .id = 39, .name = strdup("SAMAS Power Armor"), .description = strdup("Coalition flying power armor, flight capable"),
        .type = ITEM_ARMOR, .weight = 35, .value = 75000,
        .stats = {.ar = 19, .sdc_mdc = 200, .dodge_bonus = 0, .is_mega_damage = true}
    };
    
    /* ========== CONSUMABLES (40-49) ========== */
    
    /* 40: Healing Potion */
    ITEM_TEMPLATES[40] = (Item){
        .id = 40, .name = strdup("Healing Potion"), .description = strdup("Magical healing elixir, restores health"),
        .type = ITEM_CONSUMABLE, .weight = 1, .value = 500,
        .stats = {.hp_restore = 12, .damage_dice = 2, .damage_sides = 6}
    };
    
    /* 41: MDC Repair Kit */
    ITEM_TEMPLATES[41] = (Item){
        .id = 41, .name = strdup("MDC Repair Kit"), .description = strdup("Nano-repair kit for mega-damage armor"),
        .type = ITEM_CONSUMABLE, .weight = 2, .value = 1000,
        .stats = {.hp_restore = 18, .damage_dice = 3, .damage_sides = 6}
    };
    
    /* 42: SDC Bandage */
    ITEM_TEMPLATES[42] = (Item){
        .id = 42, .name = strdup("SDC Bandage"), .description = strdup("First aid bandages for structural damage"),
        .type = ITEM_CONSUMABLE, .weight = 1, .value = 50,
        .stats = {.hp_restore = 7, .damage_dice = 2, .damage_sides = 6}
    };
    
    /* 43: Stimpack */
    ITEM_TEMPLATES[43] = (Item){
        .id = 43, .name = strdup("Stimpack"), .description = strdup("Chemical stimulant, boosts speed temporarily"),
        .type = ITEM_CONSUMABLE, .weight = 1, .value = 200,
        .stats = {.damage_dice = 0, .damage_sides = 0}
    };
    
    /* 44: Psi-Booster */
    ITEM_TEMPLATES[44] = (Item){
        .id = 44, .name = strdup("Psi-Booster"), .description = strdup("Psychic energy crystal, restores ISP"),
        .type = ITEM_CONSUMABLE, .weight = 1, .value = 800,
        .stats = {.isp_restore = 18, .damage_dice = 3, .damage_sides = 6}
    };
    
    /* 45: PPE Crystal */
    ITEM_TEMPLATES[45] = (Item){
        .id = 45, .name = strdup("PPE Crystal"), .description = strdup("Potential Psychic Energy crystal, restores PPE"),
        .type = ITEM_CONSUMABLE, .weight = 1, .value = 1000,
        .stats = {.ppe_restore = 18, .damage_dice = 3, .damage_sides = 6}
    };
    
    /* 46: Antidote */
    ITEM_TEMPLATES[46] = (Item){
        .id = 46, .name = strdup("Antidote"), .description = strdup("Universal antitoxin, cures most poisons"),
        .type = ITEM_CONSUMABLE, .weight = 1, .value = 300,
        .stats = {.damage_dice = 0, .damage_sides = 0}
    };
    
    /* 47: Rad-Away */
    ITEM_TEMPLATES[47] = (Item){
        .id = 47, .name = strdup("Rad-Away"), .description = strdup("Radiation purge agent, removes contamination"),
        .type = ITEM_CONSUMABLE, .weight = 1, .value = 400,
        .stats = {.damage_dice = 0, .damage_sides = 0}
    };
    
    /* 48: Food Ration */
    ITEM_TEMPLATES[48] = (Item){
        .id = 48, .name = strdup("Food Ration"), .description = strdup("Preserved military ration, satisfies hunger"),
        .type = ITEM_CONSUMABLE, .weight = 2, .value = 20,
        .stats = {.damage_dice = 0, .damage_sides = 0}
    };
    
    /* 49: Water Canteen */
    ITEM_TEMPLATES[49] = (Item){
        .id = 49, .name = strdup("Water Canteen"), .description = strdup("Filtered water canteen, quenches thirst"),
        .type = ITEM_CONSUMABLE, .weight = 3, .value = 10,
        .stats = {.damage_dice = 0, .damage_sides = 0}
    };
    
    /* 50: Techno-Wizard Flaming Sword Hilt */
    ITEM_TEMPLATES[50] = (Item){
        .id = 50, .name = strdup("Techno-Wizard Hilt"),
        .description = strdup("An ornate metallic sword hilt covered in glowing runes and techno-magical circuitry. Etched on the pommel: 'Charge with P.P.E.'"),
        .type = ITEM_WEAPON_MELEE, .weapon_type = WEAPON_SWORD, .weight = 2, .value = 5000,
        .stats = {.damage_dice = 1, .damage_sides = 4, .damage_bonus = 0,
                  .is_mega_damage = false, .strike_bonus = 0},
        .ppe_stored = 0, .ppe_max_storage = 20, .charged = 0
    };

    DEBUG_LOG("Initialized %d item templates", TOTAL_ITEM_TEMPLATES);
}

/* Create a new item instance from template */
Item* item_create(int template_id) {
    if (template_id < 0 || template_id >= TOTAL_ITEM_TEMPLATES) {
        ERROR_LOG("Invalid template ID: %d", template_id);
        return NULL;
    }
    
    Item *item = (Item*)malloc(sizeof(Item));
    if (!item) return NULL;
    
    *item = ITEM_TEMPLATES[template_id];
    item->name = strdup(ITEM_TEMPLATES[template_id].name);
    item->description = strdup(ITEM_TEMPLATES[template_id].description);
    item->is_equipped = false;
    item->stack_count = 1;
    item->current_durability = item->stats.sdc_mdc;
    item->next = NULL;
    
    return item;
}

/* Free an item and its allocated memory */
void item_free(Item *item) {
    if (!item) return;
    if (item->name) free(item->name);
    if (item->description) free(item->description);
    free(item);
}

/* Clone an item */
Item* item_clone(Item *item) {
    if (!item) return NULL;
    return item_create(item->id);
}

/* Find item template by ID */
Item* item_find_by_id(int id) {
    if (id < 0 || id >= TOTAL_ITEM_TEMPLATES) return NULL;
    return &ITEM_TEMPLATES[id];
}

/* Find item template by name */
Item* item_find_by_name(const char *name) {
    if (!name) return NULL;
    
    for (int i = 0; i < TOTAL_ITEM_TEMPLATES; i++) {
        if (strcasecmp(ITEM_TEMPLATES[i].name, name) == 0) {
            return &ITEM_TEMPLATES[i];
        }
    }
    return NULL;
}

/* Convert item type to string */
const char* item_type_to_string(ItemType type) {
    switch (type) {
        case ITEM_WEAPON_MELEE: return "Melee Weapon";
        case ITEM_WEAPON_RANGED: return "Ranged Weapon";
        case ITEM_ARMOR: return "Armor";
        case ITEM_CONSUMABLE: return "Consumable";
        case ITEM_ACCESSORY: return "Accessory";
        case ITEM_TOOL: return "Tool";
        case ITEM_QUEST: return "Quest Item";
        case ITEM_MISC: return "Miscellaneous";
        default: return "Unknown";
    }
}

/* Convert weapon type to string */
const char* weapon_type_to_string(WeaponType type) {
    switch (type) {
        case WEAPON_UNARMED: return "Unarmed";
        case WEAPON_SWORD: return "Sword";
        case WEAPON_AXE: return "Axe";
        case WEAPON_KNIFE: return "Knife";
        case WEAPON_PISTOL: return "Pistol";
        case WEAPON_RIFLE: return "Rifle";
        case WEAPON_ENERGY: return "Energy Weapon";
        case WEAPON_HEAVY: return "Heavy Weapon";
        case WEAPON_STAFF: return "Staff";
        default: return "Unknown";
    }
}

/* ========== INVENTORY FUNCTIONS ========== */

/* Initialize inventory */
void inventory_init(Inventory *inv, int ps_stat) {
    if (!inv) return;
    inv->items = NULL;
    inv->total_weight = 0;
    inv->max_weight = ps_stat * 10; /* PS * 10 lbs capacity */
    inv->item_count = 0;
}

/* Add item to inventory */
bool inventory_add(Inventory *inv, Item *item) {
    if (!inv || !item) return false;
    
    /* Check weight limit */
    if (inv->total_weight + item->weight > inv->max_weight) {
        return false;
    }
    
    /* Add to linked list */
    item->next = inv->items;
    inv->items = item;
    inv->total_weight += item->weight;
    inv->item_count++;
    
    return true;
}

/* Remove item from inventory by name */
Item* inventory_remove(Inventory *inv, const char *item_name) {
    if (!inv || !item_name || !inv->items) return NULL;
    Item *prev = NULL;
    Item *curr = inv->items;

    /* If argument starts with a digit, treat it as a 1-based inventory index */
    if (isdigit((unsigned char)item_name[0])) {
        int idx = atoi(item_name);
        if (idx <= 0 || idx > inv->item_count) return NULL;

        int i = 1;
        while (curr) {
            if (i == idx) {
                if (prev) prev->next = curr->next;
                else inv->items = curr->next;

                inv->total_weight -= curr->weight;
                inv->item_count--;
                curr->next = NULL;
                return curr;
            }
            prev = curr;
            curr = curr->next;
            i++;
        }
        return NULL;
    }

    /* Try exact match first (case-insensitive) */
    prev = NULL;
    curr = inv->items;
    while (curr) {
        if (curr->name && strcasecmp(curr->name, item_name) == 0) {
            if (prev) prev->next = curr->next;
            else inv->items = curr->next;

            inv->total_weight -= curr->weight;
            inv->item_count--;
            curr->next = NULL;
            return curr;
        }
        prev = curr;
        curr = curr->next;
    }

    /* Try partial substring match (case-insensitive) */
    char lower_search[256];
    strncpy(lower_search, item_name, sizeof(lower_search) - 1);
    lower_search[sizeof(lower_search) - 1] = '\0';
    for (char *p = lower_search; *p; p++) *p = tolower((unsigned char)*p);

    prev = NULL;
    curr = inv->items;
    while (curr) {
        if (curr->name) {
            char lower_name[256];
            strncpy(lower_name, curr->name, sizeof(lower_name) - 1);
            lower_name[sizeof(lower_name) - 1] = '\0';
            for (char *q = lower_name; *q; q++) *q = tolower((unsigned char)*q);

            if (strstr(lower_name, lower_search) != NULL) {
                if (prev) prev->next = curr->next;
                else inv->items = curr->next;

                inv->total_weight -= curr->weight;
                inv->item_count--;
                curr->next = NULL;
                return curr;
            }
        }
        prev = curr;
        curr = curr->next;
    }

    return NULL;
}

/* Find item in inventory */
Item* inventory_find(Inventory *inv, const char *item_name) {
    if (!inv || !item_name || !item_name[0]) return NULL;

    /* If argument starts with a digit, treat it as a 1-based inventory index */
    if (isdigit((unsigned char)item_name[0])) {
        int idx = atoi(item_name);
        if (idx <= 0 || idx > inv->item_count) return NULL;

        Item *curr = inv->items;
        int i = 1;
        while (curr) {
            if (i == idx) return curr;
            curr = curr->next;
            i++;
        }
        return NULL;
    }

    /* Try exact match first (case-insensitive) */
    Item *curr = inv->items;
    while (curr) {
        if (curr->name && strcasecmp(curr->name, item_name) == 0) {
            return curr;
        }
        curr = curr->next;
    }

    /* Try partial substring match (case-insensitive) */
    char lower_search[256];
    strncpy(lower_search, item_name, sizeof(lower_search) - 1);
    lower_search[sizeof(lower_search) - 1] = '\0';
    for (char *p = lower_search; *p; p++) *p = tolower((unsigned char)*p);

    curr = inv->items;
    while (curr) {
        if (curr->name) {
            char lower_name[256];
            strncpy(lower_name, curr->name, sizeof(lower_name) - 1);
            lower_name[sizeof(lower_name) - 1] = '\0';
            for (char *q = lower_name; *q; q++) *q = tolower((unsigned char)*q);

            if (strstr(lower_name, lower_search) != NULL) {
                return curr;
            }
        }
        curr = curr->next;
    }

    return NULL;
}

/* Get total inventory weight */
int inventory_get_weight(Inventory *inv) {
    if (!inv) return 0;
    return inv->total_weight;
}

/* Check if can carry additional weight */
bool inventory_can_carry(Inventory *inv, int additional_weight) {
    if (!inv) return false;
    return (inv->total_weight + additional_weight) <= inv->max_weight;
}

/* Free all inventory items */
void inventory_free(Inventory *inv) {
    if (!inv) return;
    
    Item *curr = inv->items;
    while (curr) {
        Item *next = curr->next;
        item_free(curr);
        curr = next;
    }
    
    inv->items = NULL;
    inv->total_weight = 0;
    inv->item_count = 0;
}

/* Display inventory to player */
void inventory_display(struct PlayerSession *sess) {
    if (!sess) return;
    
    Character *ch = &sess->character;
    char buf[2048];
    snprintf(buf, sizeof(buf), "\n=== INVENTORY ===\n");
    send_to_player(sess, buf);
    
    if (!ch->inventory.items) {
        send_to_player(sess, "Your inventory is empty.\n");
    } else {
        Item *curr = ch->inventory.items;
        int count = 1;
        while (curr) {
            const char *dmg_type = curr->stats.is_mega_damage ? "MD" : "SDC";
            
            /* Add indefinite article (a/an) with formatted (lowercase) name */
            const char *name = curr->name;
            char name_buf[256];
            if (name && name[0]) {
                char fmt[256];
                format_item_name(name, fmt, sizeof(fmt));
                char first = fmt[0];
                if (first == 'a' || first == 'e' || first == 'i' || first == 'o' || first == 'u') {
                    snprintf(name_buf, sizeof(name_buf), "An %s", fmt);
                } else {
                    snprintf(name_buf, sizeof(name_buf), "A %s", fmt);
                }
            } else {
                snprintf(name_buf, sizeof(name_buf), "%s", name ? name : "item");
            }

            if (curr->type == ITEM_WEAPON_MELEE || curr->type == ITEM_WEAPON_RANGED) {
                snprintf(buf, sizeof(buf), "%d. %s - %dd%d %s (%d lbs, %d cr)\n",
                    count++, name_buf,
                    curr->stats.damage_dice, curr->stats.damage_sides, dmg_type,
                    curr->weight, curr->value);
            } else if (curr->type == ITEM_ARMOR) {
                snprintf(buf, sizeof(buf), "%d. %s - AR %d, %d %s (%d lbs, %d cr)\n",
                    count++, name_buf, curr->stats.ar, curr->current_durability, dmg_type,
                    curr->weight, curr->value);
            } else {
                snprintf(buf, sizeof(buf), "%d. %s (%d lbs, %d cr)\n",
                    count++, name_buf, curr->weight, curr->value);
            }
            send_to_player(sess, buf);
            curr = curr->next;
        }
    }
    
    snprintf(buf, sizeof(buf), "\nCarrying: %d/%d lbs (%d items)\n",
        ch->inventory.total_weight, ch->inventory.max_weight, ch->inventory.item_count);
    send_to_player(sess, buf);
}

/* ========== EQUIPMENT FUNCTIONS ========== */

/* Initialize equipment slots */
void equipment_init(EquipmentSlots *eq) {
    if (!eq) return;
    eq->weapon_primary = NULL;
    eq->weapon_secondary = NULL;
    eq->armor = NULL;
    eq->accessory1 = NULL;
    eq->accessory2 = NULL;
    eq->accessory3 = NULL;
}

/* Equip an item */
bool equipment_equip(struct Character *ch, struct PlayerSession *sess, Item *item) {
    if (!ch || !item) return false;
    
    EquipmentSlots *eq = &ch->equipment;
    
    /* Handle based on item type */
    if (item->type == ITEM_WEAPON_MELEE || item->type == ITEM_WEAPON_RANGED) {
        /* Equip weapon to primary slot (or secondary if primary occupied) */
        if (!eq->weapon_primary) {
            eq->weapon_primary = item;
        } else if (!eq->weapon_secondary) {
            eq->weapon_secondary = item;
        } else {
            if (sess) send_to_player(sess, "Your weapon slots are full. Unequip something first.\n");
            return false;
        }
    } else if (item->type == ITEM_ARMOR) {
        if (eq->armor) {
            if (sess) send_to_player(sess, "You are already wearing armor. Unequip it first.\n");
            return false;
        }
        eq->armor = item;
    } else if (item->type == ITEM_ACCESSORY) {
        if (!eq->accessory1) {
            eq->accessory1 = item;
        } else if (!eq->accessory2) {
            eq->accessory2 = item;
        } else if (!eq->accessory3) {
            eq->accessory3 = item;
        } else {
            if (sess) send_to_player(sess, "All accessory slots are full.\n");
            return false;
        }
    } else {
        if (sess) send_to_player(sess, "You cannot equip that type of item.\n");
        return false;
    }
    
    item->is_equipped = true;
    return true;
}

/* Unequip an item by slot name */
Item* equipment_unequip(struct Character *ch, const char *slot_name) {
    if (!ch || !slot_name) return NULL;
    
    EquipmentSlots *eq = &ch->equipment;
    Item *item = NULL;
    
    if (strcasecmp(slot_name, "weapon") == 0 || strcasecmp(slot_name, "primary") == 0) {
        item = eq->weapon_primary;
        eq->weapon_primary = NULL;
    } else if (strcasecmp(slot_name, "secondary") == 0) {
        item = eq->weapon_secondary;
        eq->weapon_secondary = NULL;
    } else if (strcasecmp(slot_name, "armor") == 0) {
        item = eq->armor;
        eq->armor = NULL;
    } else if (strcasecmp(slot_name, "accessory1") == 0 || strcasecmp(slot_name, "acc1") == 0) {
        item = eq->accessory1;
        eq->accessory1 = NULL;
    } else if (strcasecmp(slot_name, "accessory2") == 0 || strcasecmp(slot_name, "acc2") == 0) {
        item = eq->accessory2;
        eq->accessory2 = NULL;
    } else if (strcasecmp(slot_name, "accessory3") == 0 || strcasecmp(slot_name, "acc3") == 0) {
        item = eq->accessory3;
        eq->accessory3 = NULL;
    }
    
    if (item) {
        item->is_equipped = false;
    }
    
    return item;
}

/* Get equipment bonuses */
void equipment_get_bonuses(EquipmentSlots *eq, int *strike, int *parry, int *dodge, int *ar) {
    if (!eq) return;
    
    *strike = 0;
    *parry = 0;
    *dodge = 0;
    *ar = 0;
    
    /* Weapon bonuses */
    if (eq->weapon_primary) {
        *strike += eq->weapon_primary->stats.strike_bonus;
        *parry += eq->weapon_primary->stats.parry_bonus;
    }
    if (eq->weapon_secondary) {
        *strike += eq->weapon_secondary->stats.strike_bonus;
        *parry += eq->weapon_secondary->stats.parry_bonus;
    }
    
    /* Armor bonuses */
    if (eq->armor) {
        *ar = eq->armor->stats.ar;
        *dodge += eq->armor->stats.dodge_bonus;
        *parry += eq->armor->stats.parry_bonus;
    }
    
    /* Accessory bonuses */
    if (eq->accessory1) {
        *strike += eq->accessory1->stats.strike_bonus;
        *parry += eq->accessory1->stats.parry_bonus;
        *dodge += eq->accessory1->stats.dodge_bonus;
    }
    if (eq->accessory2) {
        *strike += eq->accessory2->stats.strike_bonus;
        *parry += eq->accessory2->stats.parry_bonus;
        *dodge += eq->accessory2->stats.dodge_bonus;
    }
    if (eq->accessory3) {
        *strike += eq->accessory3->stats.strike_bonus;
        *parry += eq->accessory3->stats.parry_bonus;
        *dodge += eq->accessory3->stats.dodge_bonus;
    }
}

/* Check if character can equip item (placeholder) */
bool equipment_can_equip(struct Character *ch, Item *item) {
    if (!ch || !item) return false;
    /* Future: Check OCC restrictions, level requirements, etc. */
    return true;
}

/* Free equipment slots */
void equipment_free(EquipmentSlots *eq) {
    if (!eq) return;
    /* Items are owned by inventory, just clear pointers */
    eq->weapon_primary = NULL;
    eq->weapon_secondary = NULL;
    eq->armor = NULL;
    eq->accessory1 = NULL;
    eq->accessory2 = NULL;
    eq->accessory3 = NULL;
}

/* Display equipped items */
void equipment_display(struct PlayerSession *sess) {
    if (!sess) return;
    
    Character *ch = &sess->character;
    char buf[1024];
    EquipmentSlots *eq = &ch->equipment;
    
    send_to_player(sess, "\n=== EQUIPPED ITEMS ===\n");
    
    if (eq->weapon_primary) {
        snprintf(buf, sizeof(buf), "Primary Weapon: %s (%dd%d %s)\n",
            eq->weapon_primary->name,
            eq->weapon_primary->stats.damage_dice,
            eq->weapon_primary->stats.damage_sides,
            eq->weapon_primary->stats.is_mega_damage ? "MD" : "SDC");
        send_to_player(sess, buf);
    } else {
        send_to_player(sess, "Primary Weapon: (none)\n");
    }
    
    if (eq->weapon_secondary) {
        snprintf(buf, sizeof(buf), "Secondary Weapon: %s (%dd%d %s)\n",
            eq->weapon_secondary->name,
            eq->weapon_secondary->stats.damage_dice,
            eq->weapon_secondary->stats.damage_sides,
            eq->weapon_secondary->stats.is_mega_damage ? "MD" : "SDC");
        send_to_player(sess, buf);
    } else {
        send_to_player(sess, "Secondary Weapon: (none)\n");
    }
    
    if (eq->armor) {
        snprintf(buf, sizeof(buf), "Armor: %s (AR %d, %d/%d %s)\n",
            eq->armor->name, eq->armor->stats.ar,
            eq->armor->current_durability, eq->armor->stats.sdc_mdc,
            eq->armor->stats.is_mega_damage ? "MDC" : "SDC");
        send_to_player(sess, buf);
    } else {
        send_to_player(sess, "Armor: (none)\n");
    }
    
    /* Show bonuses */
    int strike, parry, dodge, ar;
    equipment_get_bonuses(eq, &strike, &parry, &dodge, &ar);
    
    snprintf(buf, sizeof(buf), "\nBonuses from Equipment:\n");
    send_to_player(sess, buf);
    snprintf(buf, sizeof(buf), "  Strike: +%d, Parry: +%d, Dodge: +%d, AR: %d\n",
        strike, parry, dodge, ar);
    send_to_player(sess, buf);
}

/* ========== TECHNO-WIZARD HILT COMMANDS ========== */

/* Find a TW hilt in player's inventory or equipment */
static Item* find_tw_hilt(Character *ch) {
    /* Check equipped weapons first */
    if (ch->equipment.weapon_primary && ch->equipment.weapon_primary->id == 50)
        return ch->equipment.weapon_primary;
    if (ch->equipment.weapon_secondary && ch->equipment.weapon_secondary->id == 50)
        return ch->equipment.weapon_secondary;
    /* Check inventory */
    for (Item *it = ch->inventory.items; it; it = it->next) {
        if (it->id == 50) return it;
    }
    return NULL;
}

void cmd_charge(PlayerSession *sess, const char *args) {
    if (!sess) return;
    Character *ch = &sess->character;

    Item *hilt = find_tw_hilt(ch);
    if (!hilt) {
        send_to_player(sess, "You don't have a Techno-Wizard Hilt to charge.\n");
        return;
    }

    int player_ppe = ch->ppe;
    if (player_ppe < 1) {
        send_to_player(sess, "You don't have enough P.P.E. to charge the hilt!\n");
        return;
    }

    /* Parse amount from args (e.g. "charge hilt with 10 ppe" or "charge 10") */
    int amount = 10; /* default */
    if (args && *args) {
        int parsed = 0;
        if (sscanf(args, "%d", &parsed) == 1 && parsed > 0) {
            amount = parsed;
        } else {
            /* Try parsing "hilt with N ppe" pattern */
            sscanf(args, "hilt with %d", &parsed);
            if (parsed > 0) amount = parsed;
        }
    }

    /* Cap at available PPE */
    if (amount > player_ppe) amount = player_ppe;

    /* Cap at hilt capacity */
    int space = hilt->ppe_max_storage - hilt->ppe_stored;
    if (space <= 0) {
        send_to_player(sess, "The hilt is already fully charged! (%d/%d PPE)\n",
                       hilt->ppe_stored, hilt->ppe_max_storage);
        return;
    }
    if (amount > space) amount = space;

    /* Transfer PPE */
    ch->ppe -= amount;
    if (ch->magic.ppe_current > ch->ppe)
        ch->magic.ppe_current = ch->ppe;
    hilt->ppe_stored += amount;

    send_to_player(sess, "You channel %d P.P.E. into the hilt!\n", amount);
    send_to_player(sess, "The runes on the hilt glow brightly as they absorb your magical energy.\n");
    send_to_player(sess, "Hilt P.P.E.: %d/%d\n", hilt->ppe_stored, hilt->ppe_max_storage);

    Room *room = sess->current_room;
    if (room) {
        char msg[256];
        snprintf(msg, sizeof(msg),
                 "%s's hands glow with magical energy as they channel P.P.E. into a hilt.\r\n",
                 sess->username);
        room_broadcast(room, msg, sess);
    }

    if (hilt->ppe_stored >= 10 && !hilt->charged) {
        send_to_player(sess, "\nThe hilt has enough energy to activate!\n");
        send_to_player(sess, "Type 'activate hilt' to ignite the flaming blade.\n");
    }
}

void cmd_activate(PlayerSession *sess, const char *args) {
    if (!sess) return;
    Character *ch = &sess->character;

    Item *hilt = find_tw_hilt(ch);
    if (!hilt) {
        send_to_player(sess, "You don't have a Techno-Wizard Hilt.\n");
        return;
    }

    if (hilt->charged) {
        send_to_player(sess, "The blade is already active!\n");
        return;
    }

    if (hilt->ppe_stored < 10) {
        send_to_player(sess, "The hilt doesn't have enough P.P.E. to activate! (Need 10, have %d)\n",
                       hilt->ppe_stored);
        send_to_player(sess, "Use 'charge hilt with ppe' or 'charge 10' to add energy.\n");
        return;
    }

    /* Activate the blade */
    hilt->charged = 1;
    free(hilt->name);
    hilt->name = strdup("Flaming TW Sword");
    free(hilt->description);
    hilt->description = strdup(
        "A techno-wizard weapon blazing with a three-foot blade of pure flame! "
        "The blade crackles and hisses, casting flickering red light.");
    hilt->stats.damage_dice = 3;
    hilt->stats.damage_sides = 6;
    hilt->stats.damage_bonus = 6;
    hilt->stats.is_mega_damage = true;
    hilt->stats.strike_bonus = 2;

    send_to_player(sess, "\nWHOOOOSH!\n");
    send_to_player(sess, "A blazing blade of flame erupts from the hilt!\n");
    send_to_player(sess, "You now wield a flaming techno-wizard sword! (3d6+6 M.D.)\n");

    Room *room = sess->current_room;
    if (room) {
        char msg[256];
        snprintf(msg, sizeof(msg),
                 "A blade of pure flame erupts from %s's hilt with a thunderous WHOOSH!\r\n",
                 sess->username);
        room_broadcast(room, msg, sess);
    }
}

void cmd_deactivate(PlayerSession *sess, const char *args) {
    if (!sess) return;
    Character *ch = &sess->character;

    Item *hilt = find_tw_hilt(ch);
    if (!hilt || !hilt->charged) {
        send_to_player(sess, "You don't have an active blade to deactivate.\n");
        return;
    }

    hilt->charged = 0;
    free(hilt->name);
    hilt->name = strdup("Techno-Wizard Hilt");
    free(hilt->description);
    hilt->description = strdup(
        "An ornate metallic sword hilt covered in glowing runes and techno-magical circuitry. "
        "Etched on the pommel: 'Charge with P.P.E.'");
    hilt->stats.damage_dice = 1;
    hilt->stats.damage_sides = 4;
    hilt->stats.damage_bonus = 0;
    hilt->stats.is_mega_damage = false;
    hilt->stats.strike_bonus = 0;

    send_to_player(sess, "The flaming blade dissipates with a soft hiss.\n");
    send_to_player(sess, "Hilt P.P.E. remaining: %d/%d\n", hilt->ppe_stored, hilt->ppe_max_storage);

    Room *room = sess->current_room;
    if (room) {
        char msg[256];
        snprintf(msg, sizeof(msg),
                 "The flaming blade on %s's sword dissipates.\r\n", sess->username);
        room_broadcast(room, msg, sess);
    }
}
