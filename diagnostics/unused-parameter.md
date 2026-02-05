# Unused Parameter Warning (-Wunused-parameter)

**Warning Flag**: `-Wunused-parameter`  
**Priority**: 🟡 Low  
**Affects Build**: No (warning only)  
**Affects Runtime**: No

## What It Means

The function declares a parameter that is never used in its implementation.

## Example Warning

```
src/chargen.c:573:49: warning: unused parameter 'args' [-Wunused-parameter]
 573 | void cmd_stats(PlayerSession *sess, const char *args) {
      |                                     ~~~~~~~~~~~~^~~~
```

## Why This Happens in AMLP

Many command functions follow a standard signature pattern:
```c
void cmd_name(PlayerSession *sess, const char *args)
```

But some commands (like `stats`, `skills`, `inventory`) don't need the `args` parameter because they don't take user input.

### Examples from Our Codebase

**chargen.c** - Display commands that don't parse arguments:
- `cmd_stats()` - Shows character stats
- `cmd_skills()` - Lists all skills
- `cmd_inventory()` - Shows items
- `cmd_worn()` - Shows equipped items
- `cmd_powers()` - Lists psionic powers
- `cmd_spells()` - Lists magic spells

**room.c** - Simple commands:
- `cmd_look()` - Default room description (doesn't need target)

**wiz_tools.c** - Stub functions:
- `assign_primary_skills()` - Not yet fully implemented

## Is This A Problem?

**No, for most cases**. This is a design choice where:
1. All command functions share the same signature for consistency
2. The command dispatcher expects this signature
3. Not all commands need all parameters

## Solutions (Choose One)

### Solution 1: Explicit Void Cast (Recommended)
```c
void cmd_stats(PlayerSession *sess, const char *args) {
    (void)args;  // Explicitly mark as intentionally unused
    // ... rest of implementation
}
```

**Pros**: Clear intent, portable, no pragma clutter  
**Cons**: Extra line of code

### Solution 2: GCC Attribute
```c
void cmd_stats(PlayerSession *sess, __attribute__((unused)) const char *args) {
    // ... implementation
}
```

**Pros**: Self-documenting in signature  
**Cons**: GCC-specific, makes signature harder to read

### Solution 3: Pragma Block (For Multiple Functions)
```c
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

void cmd_stats(PlayerSession *sess, const char *args) {
    // ...
}

void cmd_skills(PlayerSession *sess, const char *args) {
    // ...
}

#pragma GCC diagnostic pop
```

**Pros**: Handles many functions at once  
**Cons**: Hides legitimate warnings in that block

### Solution 4: Remove Parameter Name (C11)
```c
void cmd_stats(PlayerSession *sess, const char * /*args*/) {
    // ... implementation
}
```

**Pros**: Clear it's intentional  
**Cons**: Makes debugging harder (no parameter name in stack traces)

## Recommended Fix for AMLP

**For chargen.c display commands**: Use Solution 1 (void cast)

```c
void cmd_stats(PlayerSession *sess, const char *args) {
    (void)args;  // Standard command signature, args not needed
    
    if (!sess || !sess->character) return;
    // ... existing implementation
}
```

**For future-implemented functions (wiz_tools.c)**: Keep as-is until implementation complete

## Batch Fix Script

To fix all chargen.c instances at once:

```bash
cd /home/thurtea/amlp-driver/src

# Add (void)args; to functions
sed -i '/^void cmd_stats/,/^{/a\    (void)args;' chargen.c
sed -i '/^void cmd_skills/,/^{/a\    (void)args;' chargen.c
# ... repeat for other functions
```

## Makefile Integration

Does **NOT** affect build success:
```
╠════════════════════════════════════════════════════════════════════════════╣
║  Warnings:       50                                                        ║
║  Errors:         0                                                         ║
╚════════════════════════════════════════════════════════════════════════════╝
```

## When To Actually Fix This

**Fix if**:
- Preparing for production release
- Want zero-warning builds
- Code review requires it

**Don't fix if**:
- Actively developing new features
- Parameters might be used in future implementation
- Function is a stub/placeholder

## Related Warnings

- `-Wunused-variable` - Similar but for local variables
- `-Wunused-but-set-variable` - Variable is assigned but never read

## Files Affected

| File | Count | Functions |
|------|-------|-----------|
| src/chargen.c | 15+ | cmd_stats, cmd_skills, cmd_strike, cmd_shoot, cmd_dodge, cmd_flee, cmd_inventory, cmd_worn, cmd_powers, cmd_isp, cmd_spells, cmd_ppe, cmd_meditate |
| src/room.c | 1 | cmd_look |
| src/wiz_tools.c | 4 | assign_primary_skills, display_occ_skills, cmd_demotion, cmd_tattoo_gun |
| src/psionics.c | 1 | psionics_activate_power |
| src/magic.c | 1 | magic_start_casting |

**Total**: 25+ instances

---

**Navigation**: [← Quick Reference](quick-reference.md) | [← README](README.md)
