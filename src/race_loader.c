/* race_loader.c - basic race and O.C.C. application utilities
 *
 * Provides a small set of rules to apply bonuses and attribute changes
 * based on the selected race and O.C.C. This file is intentionally
 * small and designed to be extended later to parse external LPC files
 * (e.g., from lib/races/ and lib/occs/) if desired.
 */

#include "race_loader.h"
#include "chargen.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

/* Helper: case-insensitive substring check */
static int strcontains_ci(const char *hay, const char *need) {
    if (!hay || !need) return 0;
    size_t hn = strlen(hay), nn = strlen(need);
    if (nn == 0) return 1;
    for (size_t i = 0; i + nn <= hn; i++) {
        size_t j;
        for (j = 0; j < nn; j++) {
            if (tolower((unsigned char)hay[i+j]) != tolower((unsigned char)need[j])) break;
        }
        if (j == nn) return 1;
    }
    return 0;
}

/* Safely add a natural weapon string to character if room */
static void add_natural_weapon(Character *ch, const char *name) {
    if (!ch || !name) return;
    if (ch->natural_weapon_count < 0) ch->natural_weapon_count = 0;
    if (ch->natural_weapon_count >= 8) return;
    ch->natural_weapons[ch->natural_weapon_count] = strdup(name);
    ch->natural_weapon_count++;
}

/* Simple LPC extractors */
char *lpc_extract_string(const char *buf, const char *snake, const char *pascal) {
    if (!buf) return NULL;
    const char *p = NULL;
    if (snake && (p = strstr(buf, snake))) ;
    if (!p && pascal && (p = strstr(buf, pascal))) ;
    if (!p) return NULL;
    /* find first '"' after the token */
    const char *q = strchr(p, '(');
    if (!q) return NULL;
    q = strchr(q, '"');
    if (!q) return NULL;
    q++;
    const char *end = strchr(q, '"');
    if (!end) return NULL;
    size_t len = end - q;
    char *out = malloc(len + 1);
    if (!out) return NULL;
    memcpy(out, q, len);
    out[len] = '\0';
    return out;
}

int lpc_extract_int(const char *buf, const char *snake, const char *pascal, int default_val) {
    if (!buf) return default_val;
    const char *p = NULL;
    if (snake && (p = strstr(buf, snake))) ;
    if (!p && pascal && (p = strstr(buf, pascal))) ;
    if (!p) return default_val;
    const char *q = strchr(p, '(');
    if (!q) return default_val;
    /* scan integer after '(' */
    int v = default_val;
    if (sscanf(q, "(%d", &v) == 1) return v;
    return default_val;
}

/* Read entire file into buffer, caller must free */
static char *read_file_to_buffer(const char *path) {
    FILE *f = fopen(path, "rb");
    if (!f) return NULL;
    if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return NULL; }
    long sz = ftell(f);
    if (sz < 0) { fclose(f); return NULL; }
    rewind(f);
    char *buf = malloc((size_t)sz + 1);
    if (!buf) { fclose(f); return NULL; }
    size_t got = fread(buf, 1, (size_t)sz, f);
    buf[got] = '\0';
    fclose(f);
    return buf;
}

void load_race_data(const char *race_name, Character *ch) {
    if (!race_name || !ch) return;
    char path[512];
    /* map race name to filename: lowercase, replace spaces with '_' */
    char fname[256];
    size_t j = 0;
    fprintf(stderr, "DEBUG: Loading race data for '%s'\n", race_name);
    for (size_t i = 0; i < strlen(race_name) && j + 1 < sizeof(fname); i++) {
        char c = race_name[i];
        if (c == ' ') fname[j++] = '_';
        else fname[j++] = tolower((unsigned char)c);
    }
    fname[j] = '\0';
    snprintf(path, sizeof(path), "lib/races/%s.lpc", fname);
    fprintf(stderr, "DEBUG: Race file path: %s\n", path);
    char *buf = read_file_to_buffer(path);
    if (!buf) {
        fprintf(stderr, "DEBUG: Failed to read race file: %s\n", path);
        return;
    }
    fprintf(stderr, "DEBUG: Successfully read race file (%zu bytes)\n", strlen(buf));

    /* health type */
    char *ht = lpc_extract_string(buf, "set_mdc_natural_attacks(", "SetMDCNaturalAttacks(");
    if (ht) { fprintf(stderr, "DEBUG: found mdc_natural_attacks token\n"); free(ht); /* boolean-like, ignore */ }
    /* prefer explicit base MDC/hp/sdc fields */
    int base_mdc = lpc_extract_int(buf, "set_base_mdc(", "SetBaseMDC(", 0);
    if (base_mdc > 0) {
        fprintf(stderr, "DEBUG: Extracted base_mdc=%d\n", base_mdc);
        ch->health_type = MDC_ONLY;
        ch->mdc = ch->max_mdc = base_mdc;
    }

    int base_ppe = lpc_extract_int(buf, "set_base_ppe(", "SetBasePPE(", 0);
    if (base_ppe > 0) {
        fprintf(stderr, "DEBUG: Extracted base_ppe=%d\n", base_ppe);
        ch->max_ppe = ch->ppe = base_ppe;
    }

    int base_isp = lpc_extract_int(buf, "set_base_isp(", "SetBaseISP(", 0);
    if (base_isp > 0) {
        fprintf(stderr, "DEBUG: Extracted base_isp=%d\n", base_isp);
        ch->max_isp = ch->isp = base_isp;
    }

    int base_hp = lpc_extract_int(buf, "set_base_hp(", "SetBaseHP(", 0);
    if (base_hp > 0) {
        fprintf(stderr, "DEBUG: Extracted base_hp=%d\n", base_hp);
        ch->max_hp += base_hp;
        ch->hp += base_hp;
    }

    int base_sdc = lpc_extract_int(buf, "set_base_sdc(", "SetBaseSDC(", 0);
    if (base_sdc > 0) {
        fprintf(stderr, "DEBUG: Extracted base_sdc=%d\n", base_sdc);
        ch->max_sdc += base_sdc;
        ch->sdc += base_sdc;
    }

    /* parse add_natural_weapon occurrences: add_natural_weapon("name", d, s, bonus) */
    const char *scan = buf;
    while ((scan = strstr(scan, "add_natural_weapon(")) != NULL) {
        const char *p = strchr(scan, '(');
        if (!p) break;
        p++;
        /* Expect: "name", int, int, int */
        char wname[128] = {0};
        int d = 0, s = 0, b = 0;
        /* Find first '"' */
        const char *qs = strchr(p, '"');
        if (!qs) { scan = p; continue; }
        qs++;
        const char *qe = strchr(qs, '"');
        if (!qe) { scan = p; continue; }
        size_t wn = qe - qs;
        if (wn >= sizeof(wname)) wn = sizeof(wname)-1;
        memcpy(wname, qs, wn);
        wname[wn] = '\0';
        /* sscanf remaining part for three ints */
        if (sscanf(qe+1, " , %d , %d , %d", &d, &s, &b) < 1) {
            /* fallback: try to parse numbers with any separators */
            int got = sscanf(qe+1, " , %d , %d , %d", &d, &s, &b);
            (void)got;
        }
        /* add natural weapon name (damage ignored for now) */
        fprintf(stderr, "DEBUG: Found natural weapon: %s (d=%d,s=%d,b=%d)\n", wname, d, s, b);
        add_natural_weapon(ch, wname);
        scan = qe + 1;
    }

    fprintf(stderr, "DEBUG: Race data loading complete for '%s'\n", race_name);
    free(buf);
}

void load_occ_data(const char *occ_name, Character *ch) {
    if (!occ_name || !ch) return;
    char path[512];
    char fname[256];
    size_t j = 0;
    fprintf(stderr, "DEBUG: Loading OCC data for '%s'\n", occ_name);
    for (size_t i = 0; i < strlen(occ_name) && j + 1 < sizeof(fname); i++) {
        char c = occ_name[i];
        if (c == ' ') fname[j++] = '_';
        else fname[j++] = tolower((unsigned char)c);
    }
    fname[j] = '\0';
    snprintf(path, sizeof(path), "lib/occs/%s.lpc", fname);
    fprintf(stderr, "DEBUG: OCC file path: %s\n", path);
    char *buf = read_file_to_buffer(path);
    if (!buf) {
        fprintf(stderr, "DEBUG: Failed to read OCC file: %s\n", path);
        return;
    }
    fprintf(stderr, "DEBUG: Successfully read OCC file (%zu bytes)\n", strlen(buf));

    int base_sdc = lpc_extract_int(buf, "set_base_sdc(", "SetBaseSDC(", 0);
    if (base_sdc > 0) { fprintf(stderr, "DEBUG: Extracted occ base_sdc=%d\n", base_sdc); ch->max_sdc += base_sdc; ch->sdc += base_sdc; }

    int base_isp = lpc_extract_int(buf, "set_base_isp(", "SetBaseISP(", 0);
    if (base_isp > 0) { fprintf(stderr, "DEBUG: Extracted occ base_isp=%d\n", base_isp); ch->max_isp = ch->isp = base_isp; }

    int base_ppe = lpc_extract_int(buf, "set_base_ppe(", "SetBasePPE(", 0);
    if (base_ppe > 0) { fprintf(stderr, "DEBUG: Extracted occ base_ppe=%d\n", base_ppe); ch->max_ppe = ch->ppe = base_ppe; }

    /* parse sdc/isp/ppe bonuses if present */
    int sdc_bonus = lpc_extract_int(buf, "set_sdc_bonus(", "SetSDCBonus(", 0);
    if (sdc_bonus) { fprintf(stderr, "DEBUG: Extracted occ sdc_bonus=%d\n", sdc_bonus); ch->sdc += sdc_bonus; ch->max_sdc += sdc_bonus; }

    int isp_bonus = lpc_extract_int(buf, "set_isp_bonus(", "SetISPBonus(", 0);
    if (isp_bonus) { fprintf(stderr, "DEBUG: Extracted occ isp_bonus=%d\n", isp_bonus); ch->isp += isp_bonus; ch->max_isp += isp_bonus; }

    int ppe_bonus = lpc_extract_int(buf, "set_ppe_bonus(", "SetPPEBonus(", 0);
    if (ppe_bonus) { fprintf(stderr, "DEBUG: Extracted occ ppe_bonus=%d\n", ppe_bonus); ch->ppe += ppe_bonus; ch->max_ppe += ppe_bonus; }

    fprintf(stderr, "DEBUG: OCC data loading complete for '%s'\n", occ_name);
    free(buf);
}

void apply_race_and_occ(PlayerSession *sess) {
    if (!sess) return;
    Character *ch = &sess->character;

    /* Defensive defaults */
    if (!ch->race) ch->race = strdup("Human");
    if (!ch->occ) ch->occ = strdup("None");

    /* Reset any temporary bonuses we manage here */
    ch->health_type = HP_SDC;
    /* Do not clobber saved MDC/ISP/PPE if already set by load */

    /* Race rules */
    if (strcontains_ci(ch->race, "Dragon") || strcontains_ci(ch->race, "Dragon Hatchling")) {
        ch->health_type = MDC_ONLY;
        ch->mdc = ch->max_mdc = (ch->max_mdc > 0) ? ch->max_mdc : 40;
        add_natural_weapon(ch, "Claw");
    } else if (strcontains_ci(ch->race, "Atlantean")) {
        ch->max_ppe = ch->ppe = (ch->max_ppe > 0) ? ch->max_ppe : 10;
    } else if (strcontains_ci(ch->race, "Dwarf") || strcontains_ci(ch->race, "Orc") ) {
        /* Tough races get extra SDC */
        ch->sdc += 5;
        ch->max_sdc += 5;
    } else {
        /* Default: no special changes */
    }

    /* O.C.C. rules */
    if (strcontains_ci(ch->occ, "Juicer")) {
        ch->hp += 20;
        ch->max_hp += 20;
        ch->sdc += 10;
        ch->max_sdc += 10;
    }

    if (strcontains_ci(ch->occ, "Mind Melter") || strcontains_ci(ch->occ, "Mind Melter")) {
        ch->max_isp = ch->isp = (ch->max_isp > 0) ? ch->max_isp : 20;
    }

    if (strcontains_ci(ch->occ, "Ley Line" ) || strcontains_ci(ch->occ, "Walker") ||
        strcontains_ci(ch->occ, "Mystic") || strcontains_ci(ch->occ, "Warlock")) {
        ch->max_ppe = ch->ppe = (ch->max_ppe > 0) ? ch->max_ppe : 15;
    }

    /* Ensure HP/MDC/SDC values are consistent */
    if (ch->health_type == MDC_ONLY) {
        if (ch->mdc <= 0) ch->mdc = ch->max_mdc = 10;
        /* keep hp/sdc but they will be ignored by display when MDC_ONLY */
    } else {
        if (ch->max_hp <= 0) ch->max_hp = ch->hp = 5 + ch->stats.pe;
        if (ch->max_sdc <= 0) ch->max_sdc = ch->sdc = 20;
    }

    /* Ensure bounds on ISP/PPE */
    if (ch->max_isp < 0) ch->max_isp = 0;
    if (ch->isp < 0) ch->isp = 0;
    if (ch->max_ppe < 0) ch->max_ppe = 0;
    if (ch->ppe < 0) ch->ppe = 0;
}
