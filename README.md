# 📘 Overview
**Pipex** is a project from the **42 curriculum** that aims to simulate how shell pipelines work under the hood.
<br>
It reproduces the behavior of chaining commands such as:
```bash
$ < infile cmd1 | cmd2 > outfile
```
You’ll learn how data flows between processes, how file descriptors are duplicated, and how system calls like `pipe()`, `fork()`, `dup2()`, and `execve()` work together to achieve redirection and communication between commands.
<br>

The **bonus part** extends this functionality to support:
- **Multiple pipelines**, allowing commands like:
```bash
$ < infile cmd1 | cmd2 | cmd3 | cmd4 > outfile
```
- **Here Document** (here_doc) mode, replicating:
```bash
$ cmd << LIMITER | cmd1 | cmd2 > outfile
```
This lets users feed input directly from the terminal until a specific *limiter* word is encountered.


# 🧠 Key Concepts
- **UNIX processes** – creation and management using `fork()`

- **Pipes** – enabling communication between multiple processes

- **File descriptors** – redirection using `dup2()`

- **Command execution** – using `execve()` to run shell commands

- **Error handling** – robust management of system call failures

- **Multiple pipelines (Bonus)** – dynamic handling of an arbitrary number of commands

- **Here Document (Bonus)** – simulates shell’s << operator to read input until a limiter


# ⚙️ Usage
### 🔧 Compilation
Use the provided **Makefile** to compile the project:
```bash
make
```
This will generate the `pipex` executable.

### ▶️ Execution
#### Mandatory part
```bash
./pipex infile "cmd1" "cmd2" outfile
```
Equivalent to:
```bash
< infile cmd1 | cmd2 > outfile
```
#### Bonus part: Multiple Pipelines
```bash
./pipex infile "cmd1" "cmd2" "cmd3" ... "cmdN" outfile
```
Equivalent to:
```bash
< infile cmd1 | cmd2 | cmd3 | ... | cmdN > outfile
```
#### Bonus part: Here Document
```bash
./pipex here_doc LIMITER "cmd1" "cmd2" outfile
```
Equivalent to:
```bash
cmd1 << LIMITER | cmd2 >> outfile
```

# 📁 Project Structure
```bash
pipex/
├── bonus/
│   └── *.c                # Source files for the bonus version (multiple pipelines + here_doc)
│
├── srcs/
│   └── *.c                # Source files for the mandatory part
│
├── get_next_line/
│   ├── get_next_line.c    # Reads one line from a file descriptor
│   ├── get_next_line_utils.c
│   └── get_next_line.h
│
├── libft/
│   ├── ft_*.c             # Custom library functions
│   ├── libft.h
│   └── Makefile
│
├── infile.txt             # Example input file used for testing
├── outfile.txt            # Example output file for testing
├── infos.txt              # Theoretical notes (system calls, file descriptors, etc.)
├── Makefile               # Compilation rules
└── README.md

```
# 🧩 Example
### Mandatory
```bash
./pipex infile "grep error" "wc -l" outfile
```

Equivalent shell behavior:
```bash
< infile grep error | wc -l > outfile
```

### Bonus (Multiple pipes)
```bash
./pipex infile "cat" "grep error" "sort" "uniq" outfile
```

Equivalent shell behavior:
```bash
< infile cat | grep error | sort | uniq > outfile
```
### Bonus (Here Document)
```bash
./pipex here_doc END "cat" "wc -l" outfile
```
# 📜 License
This project is part of the **42 Common Core** curriculum and is for educational purposes.
