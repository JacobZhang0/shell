# Tiny Shell (wip)

A small C program that builds shell-style command arguments from user input. Written on macOS using Clang and LLDB.

This project currently implements command parsing, process lifecycles, signal handling, parent-level built-ins, and file stream redirection.

## What it does right now
- Reads input using `fgets()` with pointer protection against blank lines/empty returns
- Cleans trailing newlines dynamically via string span offsets
- Tokenizes raw buffer layouts into an optimized, `NULL`-terminated pointer array (`my_argv[]`)
- Fork-replicates running processes (`fork()`) and overwrites child execution space with `execvp()`
- Pauses parent contexts securely via kernel-level `wait(NULL)` to maintain interface synchronization
- Supports native path manipulation built-ins (`cd`, `exit`) with full `$HOME` environment fallback protection
- Intercepts physical keyboard interrupts (`Ctrl-C`) using modern, restart-safe `sigaction` structures
- Swaps hardware plumbing streams (File Descriptors 0 and 1) to support robust I/O file redirection (`<` and `>`) using `open()` and bitwise-configured kernel permissions

### Example
**Input:** `ls -la > files.txt`
**Output:** Creates or overwrites `files.txt` with a long-form directory listing instead of outputting to the screen.

## Usage
To compile and run the project locally on macOS:

```bash
# Compile with Clang
clang -Wall -Wextra -g sh.c -o sh

# Run the program
./sh
```

## Next Steps
- [x] Process execution with `fork()` and `execvp()`
- [x] Built-in commands (`cd`, `exit`)
- [ ] Pipelines using `pipe()`
- [x] I/O redirection using `dup2()`
- [x] Signal handling (`SIGINT`)
