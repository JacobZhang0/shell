# Tiny Shell (wip)

A small C program that builds shell-style command arguments from user input. Written on macOS using Clang and LLDB.

This project currently implements only command parsing. Command execution is not implemented yet.

## What it does right now
- Reads input using `fgets()` 
- Removes the trailing newline
- Tokenizes the command line using `strtok()`
- Constructs an argv-style array `char *my_argv[]`
- Stores pointers directly into the original input buffer (no additional allocations or string copies)

### Example
**Input:** `ls -l /tmp`
**Output:** `my_argv = ["ls", "-l", "/tmp", NULL]`

At this point, the shell only builds the argument structure required for `execvp()`.

## Usage
To compile and run the project locally on macOS:

```bash
# Compile with Clang
clang -Wall -Wextra -g sh.c -o sh

# Run the program
./sh
```

## Next Steps
- [ ] Process execution with `fork()` and `execvp()`
- [ ] Pipelines using `pipe()`
- [ ] I/O redirection using `dup2()`
- [ ] Signal handling (`SIGINT`)
- [ ] Built-in commands (`cd`, `exit`)
