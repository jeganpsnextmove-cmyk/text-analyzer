# C Preprocessing Stage Analysis for text_analyzer.c

## What Happens During Preprocessing

The C preprocessor processes your code BEFORE compilation. Here's what gets expanded and replaced:

---

## 1. HEADER FILE INCLUSIONS (#include)

### Original Code:
```c
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
```

### What Gets Expanded:
The preprocessor **inserts the entire contents** of these header files into your source:

#### `#include<stdio.h>` expands to:
- Function declarations: `printf()`, `fgets()`, `fprintf()`, etc.
- Macros: `NULL`, `EOF`, `SEEK_SET`, `SEEK_END`, etc.
- Type definitions: `FILE`, `size_t`, etc.
- Example snippet:
```c
int printf(const char *format, ...);
int fprintf(FILE *stream, const char *format, ...);
#define NULL ((void *)0)
#define EOF (-1)
typedef struct { /* internal structure */ } FILE;
```

#### `#include<string.h>` expands to:
- Function declarations: `strlen()`, `strcpy()`, `strcmp()`, `memcpy()`, etc.
- Example:
```c
size_t strlen(const char *s);
char *strcpy(char *dest, const char *src);
int strcmp(const char *s1, const char *s2);
```

#### `#include<stdlib.h>` expands to:
- Function declarations: `malloc()`, `realloc()`, `free()`, `exit()`, etc.
- Macros: `NULL`, `RAND_MAX`, etc.
- Example:
```c
void *malloc(size_t size);
void *realloc(void *ptr, size_t size);
void free(void *ptr);
void exit(int status);
```

---

## 2. TYPEDEF EXPANSION

### Original Code:
```c
typedef struct
{
    int characters;
    int words;
    int sentences;
    int paragraphs;
    char longest_word[100];
    int char_max_count;
} Result;
```

### What Happens:
The preprocessor **creates a type alias** `Result`. Anywhere you use `Result`, it's replaced with `struct { int characters; int words; ... }` during preprocessing.

Example replacements in code:
```c
// Original:
Result analyze(char text[])

// After preprocessing becomes a reference to the struct type
struct Result_struct { ... } analyze(char text[])
```

---

## 3. MACRO REPLACEMENTS IN YOUR CODE

### Preprocessor Directives Used:
**Your code doesn't use explicit macros (like `#define`)**, but the included headers define many that are used implicitly:

#### From stdio.h:
- `NULL` → `((void *)0)` appears in code
- `EOF` → `-1` (used in file operations)

#### From stdlib.h:
- `NULL` → `((void *)0)` (used in `malloc`, `realloc`)

#### From string.h:
- No visible macros, just function declarations

---

## 4. COMPLETE PREPROCESSING WORKFLOW

Here's the exact order of what your preprocessor does:

```
1. Read text_analyzer.c
2. Process #include<stdio.h>
   └─ Insert entire stdio.h content
3. Process #include<string.h>
   └─ Insert entire string.h content
4. Process #include<stdlib.h>
   └─ Insert entire stdlib.h content
5. Process typedef struct Result
   └─ Create type alias (no expansion, just registration)
6. Keep rest of code as-is
7. Output PREPROCESSED code ready for compiler
```

---

## 5. EXPANDED FILE OVERVIEW

After preprocessing, your file would look like:

```
[ENTIRE stdio.h CONTENT]
[ENTIRE string.h CONTENT]  
[ENTIRE stdlib.h CONTENT]

typedef struct { ... } Result;

// Your actual functions and code follow...
char *read_input(char *text, int *capacity) { ... }
Result analyze(char text[]) { ... }
void print_result(Result r) { ... }
int main() { ... }
```

The preprocessed file is typically **5,000-10,000 lines** (mostly from headers).

---

## 6. HOW TO VIEW ACTUAL PREPROCESSED OUTPUT

To see the actual preprocessed code on your system:

### Command:
```powershell
gcc -E text_analyzer.c -o text_analyzer_preprocessed.i
```

This creates `text_analyzer_preprocessed.i` showing EXACTLY what the compiler sees.

---

## 7. SUMMARY TABLE

| Item | Original | After Preprocessing |
|------|----------|-------------------|
| `#include<stdio.h>` | Directive | All stdio.h code inserted |
| `#include<string.h>` | Directive | All string.h code inserted |
| `#include<stdlib.h>` | Directive | All stdlib.h code inserted |
| `Result` | Type alias | Type alias available for use |
| `printf()`, `malloc()`, etc. | Undefined | Declarations visible |
| `NULL` | Undefined | `((void *)0)` |
| Function bodies | Same | Same |
| Comments | Present | **REMOVED** |

---

## KEY POINTS

✅ **Expanded**: Header file contents, macro definitions  
✅ **Replaced**: Macro usages with their definitions  
✅ **Removed**: Comments and preprocessor directives  
✅ **Kept**: Your actual C code and typedef structure

