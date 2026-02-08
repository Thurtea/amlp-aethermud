# Build Diagnostics Documentation

**Quick Reference**: See [diagnostics/quick-reference.md](quick-reference.md) for immediate lookup

This directory contains detailed explanations for all compiler warnings and errors that may occur during the AMLP driver build process.

## Purpose

During compilation, you may see warnings in the terminal output. While the build may succeed, understanding these warnings helps:
- Identify potential bugs before they manifest
- Maintain code quality
- Decide which warnings to suppress vs. fix
- Onboard new developers to the codebase

## Warning Categories

### 🟡 Low Priority (Safe to Ignore)
These warnings indicate minor issues that don't affect functionality:
- [Unused Parameters](unused-parameter.md) - Function parameters not used in implementation
- [Unused Variables](unused-variable.md) - Declared but never referenced

### 🟠 Medium Priority (Good Practice to Fix)
These warnings suggest code that could be improved:
- [Sign Comparison](sign-compare.md) - Comparing signed/unsigned integers
- [Missing Field Initializers](missing-field-initializers.md) - Struct fields not explicitly initialized
- [Format Truncation](format-truncation.md) - String operations that might truncate

### 🔴 High Priority (Should Be Fixed)
These warnings indicate potential bugs:
- [Address Check Warnings](address-check.md) - Checking if array address is NULL (always true)
- [Zero-Length Format String](zero-length-format.md) - Empty format strings in printf-family functions

### ⛔ Critical (Must Be Fixed)
These are compilation errors that prevent the build:
- [Undeclared Identifiers](undeclared-identifier.md) - Using undefined functions/constants
- [Type Mismatches](type-mismatch.md) - Incompatible pointer/integer conversions

## Current Build Status

**Last Successful Build**: February 4, 2026
**Warnings**: 50+
**Errors**: 0
**Binary Size**: 889KB

## Common Fixes Applied

1. **GC_STRING → GC_TYPE_STRING** ([vm.c:871, 879](../src/vm.c))
   - Fixed undeclared identifier error
   - Correct constant name from gc.h

2. **array_size → array_length** ([vm.c:889](../src/vm.c))
   - Fixed undeclared function error
   - Correct API function name

## How to Use This Documentation

When you see a warning during compilation:

1. **Note the warning type** (e.g., `-Wunused-parameter`)
2. **Click the file path** in your terminal to open the source file
3. **Find the detailed guide** in this directory matching the warning flag
4. **Decide action**: Fix now, suppress, or defer to cleanup phase

## Example Terminal Output

```
src/chargen.c:573:49: warning: unused parameter 'args' [-Wunused-parameter]
 573 | void cmd_stats(PlayerSession *sess, const char *args) {
      |                                     ~~~~~~~~~~~~^~~~
```

**To investigate**: Open [unused-parameter.md](unused-parameter.md)

## Suppressing Warnings

If you determine a warning is not applicable, you can suppress it:

```c
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
void my_function(int unused_param) {
    // Implementation doesn't use unused_param
}
#pragma GCC diagnostic pop
```

Or use `__attribute__((unused))`:

```c
void my_function(__attribute__((unused)) int param) {
    // Compiler won't warn about param
}
```

## Contributing

When adding new code that generates warnings:
1. Check if the warning is documented here
2. Follow the recommended fix if available
3. If it's a new warning type, document it
4. Update [quick-reference.md](quick-reference.md)

## Files in This Directory

| File | Description |
|------|-------------|
| [README.md](README.md) | This overview document |
| [quick-reference.md](quick-reference.md) | Table of all warnings with one-line solutions |
| [unused-parameter.md](unused-parameter.md) | Detailed guide for `-Wunused-parameter` |
| [unused-variable.md](unused-variable.md) | Detailed guide for `-Wunused-but-set-variable` |
| [sign-compare.md](sign-compare.md) | Detailed guide for `-Wsign-compare` |
| [format-truncation.md](format-truncation.md) | Detailed guide for `-Wformat-truncation` |
| [missing-field-initializers.md](missing-field-initializers.md) | Detailed guide for `-Wmissing-field-initializers` |
| [address-check.md](address-check.md) | Detailed guide for `-Waddress` |
| [zero-length-format.md](zero-length-format.md) | Detailed guide for `-Wformat-zero-length` |
| [undeclared-identifier.md](undeclared-identifier.md) | Critical error guide |

---

**Navigation**: [↑ Top](#build-diagnostics-documentation) | [Quick Reference →](quick-reference.md)
