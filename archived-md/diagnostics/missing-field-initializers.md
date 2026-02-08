# Missing Field Initializers (-Wmissing-field-initializers)

**Warning Flag**: `-Wmissing-field-initializers`  
**Priority**: 🟠 Medium  
**Affects Build**: No (warning only)  
**Affects Runtime**: Yes (uninitialized fields may have garbage values)

## What It Means

When initializing a struct, some fields are explicitly initialized while others are left out, potentially containing garbage values.

## Example Warning

```
src/combat.c:364:5: warning: missing initializer for field 'hp_damage' of 'DamageResult' 
                             [-Wmissing-field-initializers]
  364 |     DamageResult result = {0, false, false, 0, 0};
      |     ^~~~~~~~~~~~
src/combat.h:56:9: note: 'hp_damage' declared here
   56 |     int hp_damage;
      |         ^~~~~~~~~
```

## The Problem

### Struct Definition (combat.h)

```c
typedef struct {
    int total_damage;           // Field 1
    bool critical_hit;          // Field 2
    bool critical_failure;      // Field 3
    int mdc_damage;             // Field 4
    int sdc_damage;             // Field 5
    int hp_damage;              // Field 6 - Missing from initializer!
} DamageResult;
```

### Initialization (combat.c)

```c
// Only initializes first 5 fields
DamageResult result = {0, false, false, 0, 0};

// Field mapping:
// total_damage = 0       ✓
// critical_hit = false   ✓
// critical_failure = false ✓
// mdc_damage = 0         ✓
// sdc_damage = 0         ✓
// hp_damage = ???        ✗ UNINITIALIZED!
```

### What Happens

`hp_damage` contains whatever value was in that memory location. Could be:
- 0 (if you're lucky)
- 42
- -127853
- Any random value

## Why This Is Dangerous

```c
DamageResult apply_damage(Character *target) {
    DamageResult result = {0, false, false, 0, 0};  // hp_damage uninitialized
    
    result.mdc_damage = 10;
    
    // Later code checks hp_damage
    if (result.hp_damage > 0) {  // Random value!
        target->hp -= result.hp_damage;  // Subtract random damage!
    }
    
    return result;
}
```

**Result**: Characters randomly take extra damage or heal unexpectedly.

## Affected Files in AMLP

### src/combat.c:364 (Melee Attack)

```c
DamageResult combat_attack_melee(CombatParticipant *attacker, 
                                  CombatParticipant *defender) {
    // ...
    DamageResult result = {0, false, false, 0, 0};
    // Missing: hp_damage
    
    // Later uses result.hp_damage without setting it!
}
```

### src/combat.c:459 (Ranged Attack)

```c
DamageResult combat_attack_ranged(CombatParticipant *attacker, 
                                   CombatParticipant *defender) {
    // ...
    DamageResult result = {0, false, false, 0, 0};
    // Missing: hp_damage
}
```

## Solutions

### Solution 1: Add Missing Field (Recommended)

```c
// OLD
DamageResult result = {0, false, false, 0, 0};

// NEW
DamageResult result = {0, false, false, 0, 0, 0};
//                                            ^
//                                        hp_damage
```

**Pros**: Explicit, all fields initialized  
**Cons**: Positional (must match struct order exactly)

### Solution 2: Zero-Initialize Everything

```c
// OLD
DamageResult result = {0, false, false, 0, 0};

// NEW
DamageResult result = {0};  // All fields set to 0/false/NULL
```

**Pros**: Concise, works for any number of fields  
**Cons**: All fields get 0, might not be desired default

### Solution 3: Designated Initializers (C99+)

```c
// OLD
DamageResult result = {0, false, false, 0, 0};

// NEW (Best - Order doesn't matter!)
DamageResult result = {
    .total_damage = 0,
    .critical_hit = false,
    .critical_failure = false,
    .mdc_damage = 0,
    .sdc_damage = 0,
    .hp_damage = 0
};
```

**Pros**: Self-documenting, order-independent, catches field additions  
**Cons**: Verbose (but clearer)

### Solution 4: memset

```c
DamageResult result;
memset(&result, 0, sizeof(result));
```

**Pros**: Guarantees all bytes are 0  
**Cons**: Overkill, harder to read

## Recommended Fix for AMLP

### combat.c:364 and 459

```c
// Change both locations to designated initializers
DamageResult result = {
    .total_damage = 0,
    .critical_hit = false,
    .critical_failure = false,
    .mdc_damage = 0,
    .sdc_damage = 0,
    .hp_damage = 0
};
```

Or simply:
```c
DamageResult result = {0};  // All fields zeroed
```

## Testing Impact

**Does this affect gameplay?**

**Yes, potentially!**

- **Melee combat**: `hp_damage` might be random, causing:
  - Unexpected damage amounts
  - Healing instead of damage (if negative)
  - One-shot kills (if huge positive value)

- **Ranged combat**: Same issues

**Current state**: The code might be setting `hp_damage` later, so it works by accident. But it's a bug waiting to happen.

## Verification

Check if `hp_damage` is set before use:

```bash
cd /home/thurtea/amlp-driver/src
grep -A 20 "DamageResult result = {0, false, false, 0, 0};" combat.c
```

Look for lines like:
```c
result.hp_damage = ...;
```

If found, the warning is less critical (but should still fix initialization).  
If not found, this is a **critical bug**.

## Full Fix Example

```c
// Function: combat_attack_melee (Line 364)
DamageResult combat_attack_melee(CombatParticipant *attacker, 
                                  CombatParticipant *defender) {
    // Initialize ALL fields
    DamageResult result = {
        .total_damage = 0,
        .critical_hit = false,
        .critical_failure = false,
        .mdc_damage = 0,
        .sdc_damage = 0,
        .hp_damage = 0
    };
    
    // Roll to hit
    int roll = roll_d20();
    
    if (roll == 20) {
        result.critical_hit = true;
        result.total_damage = calculate_damage(attacker) * 2;
    } else if (roll == 1) {
        result.critical_failure = true;
        return result;
    } else {
        result.total_damage = calculate_damage(attacker);
    }
    
    // Apply damage to appropriate damage track
    if (defender->has_mdc_armor) {
        result.mdc_damage = result.total_damage;
    } else {
        result.sdc_damage = result.total_damage;
    }
    
    return result;
}
```

## Struct Review

When adding new fields to `DamageResult`:

```c
// combat.h
typedef struct {
    int total_damage;
    bool critical_hit;
    bool critical_failure;
    int mdc_damage;
    int sdc_damage;
    int hp_damage;
    // NEW FIELD:
    bool called_shot;  // <-- Don't forget to initialize this!
} DamageResult;
```

With designated initializers, you'll get a compiler error if you forget:
```c
DamageResult result = {
    .total_damage = 0,
    .critical_hit = false,
    .critical_failure = false,
    .mdc_damage = 0,
    .sdc_damage = 0,
    .hp_damage = 0
    // .called_shot = ???  <-- Forgot this, but still compiles!
};
```

But at least the field names are visible for review.

## Files Affected

| File | Line | Function | Missing Field |
|------|------|----------|---------------|
| src/combat.c | 364 | combat_attack_melee | `hp_damage` |
| src/combat.c | 459 | combat_attack_ranged | `hp_damage` |

**Total**: 2 instances

---

**Navigation**: [← Quick Reference](quick-reference.md) | [← README](README.md)
