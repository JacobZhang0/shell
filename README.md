# Tiny Shell (wip)

A small C program that builds shell-style command arguments from user input. Written on macOS using Clang and LLDB.

This project currently implements command parsing and basic command execution.

## What it does right now
- Reads input using `fgets()` 
- Removes the trailing newline
- Tokenizes the command line using `strtok()`
- Constructs an argv-style array `char *my_argv[]`
- Executes commands by spawning child processes with `fork()` and `execvp()`

### Example
**Input:** `ls -l /tmp`
**Output:** Runs the `ls` command and prints directory contents.


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
- [ ] Pipelines using `pipe()`
- [ ] I/O redirection using `dup2()`
- [ ] Signal handling (`SIGINT`)
- [ ] Built-in commands (`cd`, `exit`)
