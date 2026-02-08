# Sign Comparison Warning (-Wsign-compare)

**Warning Flag**: `-Wsign-compare`  
**Priority**: 🟠 Medium  
**Affects Build**: No (warning only)  
**Affects Runtime**: Potentially (edge cases)

## What It Means

Comparing a signed integer (`int`) with an unsigned integer (`unsigned int`, `size_t`) can lead to unexpected behavior when the signed value is negative.

## Example Warning

```
src/skills.c:772:19: warning: comparison of integer expressions of different signedness: 
                             'int' and 'long unsigned int' [-Wsign-compare]
  772 |     for (i = 0; i < TOTAL_SKILLS; i++) {
      |                   ^
```

## The Problem

### How Signed/Unsigned Comparison Works

When comparing signed and unsigned integers, the **signed value is converted to unsigned**, which can cause problems:

```c
int a = -1;
size_t b = 5;

if (a < b) {  // You expect: true (-1 < 5)
    // But this does NOT execute!
}

// Why? -1 converted to unsigned becomes a huge number (4294967295 on 32-bit)
// So the comparison becomes: 4294967295 < 5 = false
```

### AMLP Example

```c
#define TOTAL_SKILLS 150  // This is size_t (unsigned)

for (int i = 0; i < TOTAL_SKILLS; i++) {
    // Works fine here because i is never negative
    // But the compiler warns about mixed signedness
}
```

## When This Is Dangerous

### Scenario 1: Negative Loop Counter

```c
for (int i = some_value; i < TOTAL_SKILLS; i++) {
    // If some_value is negative, i < TOTAL_SKILLS converts i to unsigned
    // -1 becomes 4294967295, which is > TOTAL_SKILLS
    // Loop never executes!
}
```

### Scenario 2: Subtraction Results

```c
int result = array_length(arr) - 10;  // Might be negative
if (result < TOTAL_SKILLS) {  // Dangerous if result < 0
    // Unexpected behavior
}
```

## Affected Files in AMLP

### src/skills.c (5 instances)

**All involve comparing `int` loop variables with `TOTAL_SKILLS` (size_t)**

```c
// Line 772
for (i = 0; i < TOTAL_SKILLS; i++) {

// Line 787
if (id < 0 || id >= TOTAL_SKILLS) return NULL;

// Line 796
for (i = 0; i < TOTAL_SKILLS; i++) {

// Line 810
for (i = 0; i < TOTAL_SKILLS; i++) {

// Line 820
if (skill_id < 0 || skill_id >= TOTAL_SKILLS) return "Unknown";
```

### src/chargen.c (7 instances)

**All involve comparing with `NUM_RACES` (size_t)**

```c
// Line 283
if (end > NUM_RACES) end = NUM_RACES;

// Line 294
if (end < NUM_RACES) {

// Lines 469, 480, 500, 511, 522
// Similar comparisons with NUM_RACES in race selection code
```

### src/driver.c (1 instance)

```c
// Line 212
session ? session->state : -1,  // Mixing SessionState enum with -1
```

## Solutions

### Solution 1: Change Loop Variable Type (Recommended)

```c
// OLD
int i;
for (i = 0; i < TOTAL_SKILLS; i++) {

// NEW
size_t i;
for (i = 0; i < TOTAL_SKILLS; i++) {
```

**Pros**: Type-correct, no warning  
**Cons**: Need to audit code that uses `i` (might expect int)

### Solution 2: Cast the Comparison

```c
// OLD
for (i = 0; i < TOTAL_SKILLS; i++) {

// NEW
for (i = 0; i < (int)TOTAL_SKILLS; i++) {
```

**Pros**: Quick fix, preserves existing type  
**Cons**: Overflow if TOTAL_SKILLS > INT_MAX (not a problem with 150 skills)

### Solution 3: Explicit Range Check

```c
// OLD
if (id < 0 || id >= TOTAL_SKILLS) return NULL;

// NEW
if (id < 0 || (size_t)id >= TOTAL_SKILLS) return NULL;
```

**Pros**: Clear intent, handles negative values correctly  
**Cons**: Verbose

### Solution 4: Use Unsigned From Start

```c
// Change function signature
// OLD: int skill_get_by_id(int id)
// NEW: int skill_get_by_id(size_t id)
```

**Pros**: Prevents negative values entirely  
**Cons**: Requires API change, affects callers

## Recommended Fix for AMLP

### For skills.c (Loop Variables)

```c
// Change all loop variables from int to size_t
size_t i;
for (i = 0; i < TOTAL_SKILLS; i++) {
    // ...
}
```

### For skills.c (Bounds Checks)

```c
// Keep the negative check, but cast for comparison
if (id < 0 || (size_t)id >= TOTAL_SKILLS) return NULL;
```

### For chargen.c (Race Bounds)

```c
// Cast NUM_RACES to int (it's always < INT_MAX)
if (end > (int)NUM_RACES) end = (int)NUM_RACES;
```

Or better - make `end` unsigned:
```c
size_t end = page * 5;  // Instead of int end
```

## Full Fix Example: skills.c

```c
// Function: skill_init (Line 772)
void skill_init(void) {
    // OLD: int i;
    size_t i;
    for (i = 0; i < TOTAL_SKILLS; i++) {
        printf("Skill %zu: %s\n", i, all_skills[i].name);
    }
}

// Function: skill_get_by_id (Line 787)
const Skill* skill_get_by_id(int id) {
    // Keep negative check, cast for unsigned comparison
    if (id < 0 || (size_t)id >= TOTAL_SKILLS) return NULL;
    return &all_skills[id];
}

// Function: skill_get_by_name (Line 796)
const Skill* skill_get_by_name(const char *name) {
    size_t i;  // Changed from int
    for (i = 0; i < TOTAL_SKILLS; i++) {
        if (strcasecmp(all_skills[i].name, name) == 0) {
            return &all_skills[i];
        }
    }
    return NULL;
}
```

## Testing Impact

**Does this affect gameplay?**

**Current code: No** - All comparisons are with positive values starting from 0, so no actual bug exists.

**If changed incorrectly: Yes** - Could cause:
- Loops that never execute
- Out-of-bounds array access
- Skills/races not found

## Edge Case: What If Someone Passes -1?

```c
const Skill* skill = skill_get_by_id(-1);

// With current code (int comparison):
// -1 < 0 is true, so returns NULL ✓ Correct

// With naive unsigned change:
// size_t id = (size_t)(-1) => 18446744073709551615
// This would bypass the bounds check! ✗ Bug

// With recommended fix:
if (id < 0 || (size_t)id >= TOTAL_SKILLS) return NULL;
// -1 < 0 is still true, returns NULL ✓ Correct
```

## Batch Fix Script

```bash
cd /home/thurtea/amlp-driver/src

# Skills.c - Change loop variables
sed -i 's/int i;/size_t i;/g' skills.c

# Skills.c - Fix bounds checks
sed -i 's/id >= TOTAL_SKILLS/(size_t)id >= TOTAL_SKILLS/g' skills.c
sed -i 's/skill_id >= TOTAL_SKILLS/(size_t)skill_id >= TOTAL_SKILLS/g' skills.c

# Chargen.c - Cast NUM_RACES
sed -i 's/> NUM_RACES/> (int)NUM_RACES/g' chargen.c
sed -i 's/< NUM_RACES/< (int)NUM_RACES/g' chargen.c
sed -i 's/<= NUM_RACES/<= (int)NUM_RACES/g' chargen.c
```

## Files Affected

| File | Count | Issue |
|------|-------|-------|
| src/skills.c | 5 | Loop vars and bounds checks with `TOTAL_SKILLS` |
| src/chargen.c | 7 | Race selection with `NUM_RACES` |
| src/driver.c | 1 | Enum vs -1 in ternary |

**Total**: 13 instances

## When To Actually Fix This

**Fix if**:
- Adding new code that might pass negative values
- Loop behavior seems wrong (doesn't execute)
- Preparing for production (warning cleanup)

**Don't fix if**:
- Current code works correctly
- You're unsure about type changes rippling through code
- You're actively developing new features

---

**Navigation**: [← Quick Reference](quick-reference.md) | [← README](README.md)
