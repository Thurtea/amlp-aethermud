# Unused Variable Warning (-Wunused-but-set-variable)

**Warning Flag**: `-Wunused-but-set-variable`  
**Priority**: 🟡 Low  
**Affects Build**: No (warning only)  
**Affects Runtime**: No (but indicates dead code)

## What It Means

A variable is declared and assigned a value, but that value is never used. This is different from `-Wunused-variable` (declared but never assigned).

## Example Warning

```
src/parser.c:1204:9: warning: variable 'is_public' set but not used [-Wunused-but-set-variable]
 1204 |     int is_public = 0;
      |         ^~~~~~~~~
```

## The Problem

```c
void parser_parse_declaration(Parser *p) {
    int is_public = 0;  // Declared and initialized
    
    if (token_matches("public")) {
        is_public = 1;  // Set to 1
    }
    
    // ... rest of function
    // is_public is NEVER USED after this!
}
```

**Why this happens**: The code was intended to check visibility, but the implementation isn't finished.

## Affected Files in AMLP

### src/parser.c:1204

```c
void parser_parse_declaration(Parser *p) {
    int is_public = 0;
    
    // Parse visibility modifiers
    if (token_matches("public")) {
        is_public = 1;
    }
    
    // TODO: Actually use is_public flag for access control
    // Currently: All declarations are treated the same way
}
```

**Impact**: Public/private declarations not enforced (feature not implemented)

### src/efun.c:1002

```c
int efun_clone_object(VM *vm) {
    Object *o = /* ... */;
    int has_process = obj_get_method(o, "process_command") ? 1 : 0;
    
    // Variable set but never checked
    // Maybe was meant for optimization or validation?
    
    return clone_success;
}
```

**Impact**: Unknown (likely incomplete feature)

### src/skills.c:829

```c
int occ_assign_skills(Character *c, const char *occ_name) {
    int i, j;  // Both declared
    
    for (i = 0; i < num_skills; i++) {
        // ... assign skills
    }
    
    // j is never used!
}
```

**Impact**: None (leftover from refactoring)

## Solutions

### Solution 1: Remove Variable (If Truly Unused)

```c
// OLD
int occ_assign_skills(Character *c, const char *occ_name) {
    int i, j;  // j unused
    for (i = 0; i < num_skills; i++) {

// NEW
int occ_assign_skills(Character *c, const char *occ_name) {
    int i;  // Removed j
    for (i = 0; i < num_skills; i++) {
```

**Pros**: Clean, removes dead code  
**Cons**: If you needed it for future implementation, have to re-add

### Solution 2: Mark as Unused

```c
// If keeping for future implementation
int is_public = 0;
(void)is_public;  // Suppress warning
```

**Pros**: Keeps variable for future use  
**Cons**: Still dead code

### Solution 3: Implement the Feature

```c
// Best solution - actually use the variable!
void parser_parse_declaration(Parser *p) {
    int is_public = 0;
    
    if (token_matches("public")) {
        is_public = 1;
    }
    
    // NOW USE IT:
    if (is_public) {
        mark_declaration_public(p->current_decl);
    } else {
        mark_declaration_private(p->current_decl);
    }
}
```

**Pros**: Completes the feature  
**Cons**: Requires actual implementation work

## Recommended Fix for AMLP

### parser.c:1204 - Keep for Future Implementation

```c
void parser_parse_declaration(Parser *p) {
    int is_public = 0;
    
    if (token_matches("public")) {
        is_public = 1;
    }
    
    // TODO: Implement visibility control
    (void)is_public;  // Suppress warning until implemented
    
    // ... rest of parsing
}
```

### efun.c:1002 - Remove or Use

```c
// If has_process was meant for something, implement it:
int efun_clone_object(VM *vm) {
    Object *o = /* ... */;
    int has_process = obj_get_method(o, "process_command") ? 1 : 0;
    
    // Maybe it was meant for this?
    if (has_process) {
        setup_command_processing(o);
    }
    
    return clone_success;
}
```

Or just remove:
```c
int efun_clone_object(VM *vm) {
    Object *o = /* ... */;
    // Removed has_process variable
    return clone_success;
}
```

### skills.c:829 - Remove j

```c
// OLD
int occ_assign_skills(Character *c, const char *occ_name) {
    int i, j;

// NEW
int occ_assign_skills(Character *c, const char *occ_name) {
    int i;
```

## Difference vs -Wunused-variable

| Warning | Variable State | Example |
|---------|---------------|---------|
| `-Wunused-variable` | Declared, never assigned | `int x;` (never used at all) |
| `-Wunused-but-set-variable` | Declared, assigned, never read | `int x = 5;` (value never used) |

## Testing Impact

**Does this affect gameplay?**

**No** - Unused variables don't affect runtime behavior. They just:
- Waste stack space (tiny amount)
- Indicate incomplete features
- Make code harder to understand

## Why Keep Dead Code?

Sometimes unused variables indicate:
1. **Incomplete features**: `is_public` for access control
2. **Debugging artifacts**: Variables used during development
3. **Refactoring leftovers**: Old code structure remnants
4. **Future expansion**: Placeholders for planned features

## Files Affected

| File | Line | Variable | Function | Likely Reason |
|------|------|----------|----------|---------------|
| src/parser.c | 1204 | `is_public` | parser_parse_declaration | Feature incomplete |
| src/efun.c | 1002 | `has_process` | efun_clone_object | Feature incomplete or removed |
| src/skills.c | 829 | `j` | occ_assign_skills | Refactoring leftover |

**Total**: 3 instances

---

**Navigation**: [← Quick Reference](quick-reference.md) | [← README](README.md)
