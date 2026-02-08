# Format Truncation Warning (-Wformat-truncation)

**Warning Flag**: `-Wformat-truncation`  
**Priority**: 🟠 Medium  
**Affects Build**: No (warning only)  
**Affects Runtime**: Yes (data loss if buffer too small)

## What It Means

The compiler detects that `snprintf()` output may exceed the destination buffer size, causing the result to be truncated (cut off).

## Example Warning

```
src/chargen.c:903:41: warning: '.bak' directive output may be truncated 
                                writing 4 bytes into a region of size between 1 and 512 
                                [-Wformat-truncation=]
  903 |     snprintf(backup, sizeof(backup), "%s.bak", filepath);
      |                                         ^~~~
src/chargen.c:903:5: note: 'snprintf' output between 5 and 516 bytes 
                             into a destination of size 512
  903 |     snprintf(backup, sizeof(backup), "%s.bak", filepath);
      |     ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
```

## The Problem

### What GCC Is Calculating

```c
char backup[512];
snprintf(backup, sizeof(backup), "%s.bak", filepath);

// GCC analysis:
// - filepath could be up to 511 bytes (if it's char[512])
// - ".bak" adds 4 bytes
// - Total: 511 + 4 = 515 bytes needed
// - Buffer only holds 512 bytes
// - Result: Truncation possible
```

### When This Matters

If `filepath` is close to 512 characters:
```c
// filepath = "/very/long/path/.../character_name.json" (508 chars)
// backup needs 508 + 4 (".bak") = 512 bytes
// snprintf truncates to fit: "...character_name.js" (no ".bak"!)
```

**Result**: Backup file has wrong extension, might overwrite original!

## Affected Files in AMLP

### src/chargen.c:903 (Backup File Path)

```c
void save_character(Character *c, const char *filepath) {
    char backup[512];
    
    // If filepath is long, this might truncate .bak
    snprintf(backup, sizeof(backup), "%s.bak", filepath);
    
    rename(filepath, backup);  // Rename original to backup
    // ... save new version
}
```

**Impact**: 
- If truncated, backup might have wrong name
- Could overwrite original instead of backing up
- File corruption risk in edge cases

### src/server.c:69 (File Browser)

```
src/server.c:69:52: warning: '%s' directive output may be truncated 
                             writing up to 255 bytes into a region of size between 0 and 1023
   69 |         snprintf(item_path, sizeof(item_path), "%s/%s", full_path, entry->d_name);
```

```c
void cmd_ls_filesystem(PlayerSession *sess, const char *full_path) {
    char item_path[1024];
    struct dirent *entry;
    
    while ((entry = readdir(dir)) != NULL) {
        // full_path could be 1023 chars + "/" + filename (255) = 1279 chars
        snprintf(item_path, sizeof(item_path), "%s/%s", full_path, entry->d_name);
        // Truncates to 1024 chars
    }
}
```

**Impact**:
- Long directory paths may not list correctly
- stat() calls on truncated paths will fail
- Files appear missing in deep directories

### src/server.c:75, 77 (Directory Display)

```
src/server.c:75:52: warning: '/\r\n' directive output may be truncated 
                             writing 3 bytes into a region of size between 1 and 226
   75 |                 snprintf(line, sizeof(line), "%-30s/\r\n", entry->d_name);
```

```c
char line[256];
snprintf(line, sizeof(line), "%-30s/\r\n", entry->d_name);  // Folder
snprintf(line, sizeof(line), "%-30s\r\n", entry->d_name);   // File
```

**Impact**:
- Filenames over 253 chars truncate
- Display only (doesn't affect functionality)
- Linux allows 255 char filenames, so possible

### src/server.c:119 (Empty Directory)

```
src/server.c:119:48: warning: zero-length gnu_printf format string [-Wformat-zero-length]
  119 |             snprintf(new_dir, sizeof(new_dir), "");
      |                                                ^~
```

**This is special** - see [zero-length-format.md](zero-length-format.md)

## Solutions

### Solution 1: Increase Buffer Size

```c
// OLD
char backup[512];

// NEW
char backup[1024];  // Room for long paths + ".bak"
```

**Pros**: Simple, handles longer paths  
**Cons**: Uses more stack memory

### Solution 2: Check Return Value

```c
char backup[512];
int result = snprintf(backup, sizeof(backup), "%s.bak", filepath);

if (result >= sizeof(backup)) {
    // Truncation occurred!
    fprintf(stderr, "Error: filepath too long for backup\n");
    return -1;
}
```

**Pros**: Detects the problem at runtime  
**Cons**: Doesn't prevent it, just detects

### Solution 3: Dynamic Allocation

```c
// Calculate needed size
size_t needed = strlen(filepath) + 5;  // +5 for ".bak\0"
char *backup = malloc(needed);

snprintf(backup, needed, "%s.bak", filepath);
// ... use backup
free(backup);
```

**Pros**: Always enough space  
**Cons**: malloc/free overhead, can fail

### Solution 4: PATH_MAX Constant

```c
#include <limits.h>

char backup[PATH_MAX];  // Usually 4096 on Linux
snprintf(backup, sizeof(backup), "%s.bak", filepath);
```

**Pros**: System-defined maximum path length  
**Cons**: Very large stack allocation (4KB+)

## Recommended Fix for AMLP

### For chargen.c:903 (Critical - Backup File)

```c
void save_character(Character *c, const char *filepath) {
    // Use PATH_MAX or larger buffer
    char backup[1024];  // Increased from 512
    int ret = snprintf(backup, sizeof(backup), "%s.bak", filepath);
    
    if (ret >= sizeof(backup)) {
        fprintf(stderr, "Error: Character path too long\n");
        return;  // Don't risk corrupting data
    }
    
    rename(filepath, backup);
    // ... rest of save logic
}
```

### For server.c:69 (File Browser)

```c
void cmd_ls_filesystem(PlayerSession *sess, const char *full_path) {
    char item_path[PATH_MAX];  // Use system maximum
    
    while ((entry = readdir(dir)) != NULL) {
        int ret = snprintf(item_path, sizeof(item_path), "%s/%s", 
                          full_path, entry->d_name);
        
        if (ret >= sizeof(item_path)) {
            continue;  // Skip files with too-long paths
        }
        
        // ... stat and display
    }
}
```

### For server.c:75, 77 (Display Only)

```c
char line[300];  // Increased from 256 (handles 255-char names + formatting)
snprintf(line, sizeof(line), "%-30s/\r\n", entry->d_name);
```

Or truncate filename for display:
```c
char display_name[32];
snprintf(display_name, sizeof(display_name), "%.30s", entry->d_name);
snprintf(line, sizeof(line), "%-30s/\r\n", display_name);
```

## Testing Impact

**Does this affect gameplay?**

| Location | Severity | Scenario |
|----------|----------|----------|
| chargen.c:903 | 🔴 High | Player with very long character name loses backup on save |
| server.c:69 | 🟠 Medium | Files in deep directories don't show in file browser |
| server.c:75,77 | 🟢 Low | Long filenames display truncated (cosmetic) |

## Real-World Example

### Triggering chargen.c:903 Bug

```bash
# Character save path
/home/thurtea/amlp-driver/save/characters/VeryLongCharacterNameThatSomeoneMightChoose_Level99_Headhunter_Coalition_Elite_Squad_Commander_With_Many_Titles_And_Achievements_This_Is_Getting_Really_Long_Now_But_You_Get_The_Idea_Right_Question_Mark_Exclamation_Point_And_Some_More_Text_To_Reach_512_Characters_Total_Path_Length_Including_Directory_Names_Which_Could_Also_Be_Quite_Long_Especially_If_Someone_Creates_Nested_Subdirectories_For_Organization_Purposes_Like_By_OCC_Then_By_Level_Range_Then_By_Player_Name_This_Kind_Of_Deep_Nesting_Is_Common_In_Some_Organizational_Systems.json

# When trying to backup:
# Needs: 512 + 4 (".bak") = 516 bytes
# Has: 512 bytes
# Result: Truncates, backup file named incorrectly
```

## Prevention Strategy

1. **Character creation**: Limit username to reasonable length (32-64 chars)
2. **Save paths**: Keep directory structure shallow
3. **Validation**: Check path lengths before operations

## Files Affected

| File | Line | Function | Buffer | Issue |
|------|------|----------|--------|-------|
| src/chargen.c | 903 | save_character | 512 | filepath + ".bak" might exceed 512 |
| src/server.c | 69 | cmd_ls_filesystem | 1024 | full_path + "/" + filename might exceed 1024 |
| src/server.c | 75 | cmd_ls_filesystem | 256 | filename + "/\r\n" might exceed 256 |
| src/server.c | 77 | cmd_ls_filesystem | 256 | filename + "\r\n" might exceed 256 |

**Total**: 4 instances (1 critical, 3 low-priority)

---

**Navigation**: [← Quick Reference](quick-reference.md) | [← README](README.md)
