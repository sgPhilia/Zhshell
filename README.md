# zhshell

A modular, lightweight, POSIX-compliant mini-shell implemented in C++17.

This project explores Linux system programming, process management, file descriptors, and command-line parsing.

Architecture: Lexer → Parser → Executor.

---

## Features

- Process management using fork(), execvp(), waitpid()
- Dynamic PATH resolution
- Argument and quote parsing (' and ")
- Built-in commands: cd, pwd, echo, exit
- Pipeline support (|):
  ls -la | grep txt | wc -l
- Command history via GNU Readline

---

## Project Structure

zhshell/
├── include/
│   ├── builtin.h     # Built-in command declarations (cd, pwd, etc.)
│   ├── executor.h    # Process management and execution logic
│   ├── lexer.h       # Tokenizer and string chunking definitions
│   ├── parser.h      # Command and Pipeline structural layout
│   └── shell.h       # Main REPL loop and shell configurations
├── src/
│   ├── builtin.cpp   # Implementation of built-in functions
│   ├── executor.cpp  # Forking, execution, and multi-pipe routing
│   ├── lexer.cpp     # State-machine based lexical analyzer
│   ├── main.cpp      # Application entry point
│   ├── parser.cpp    # Syntactic abstraction layer
│   └── shell.cpp     # Read-Eval-Print-Loop (REPL) orchestration
├── Makefile          # Build Automation configuration
└── README.md         # Documentation

---

## Requirements

- Linux
- GCC/G++ (C++17)
- GNU Make
- GNU Readline

---

## Build

make

---

## Run

./zhshell

---

## Clean

make clean

---

## Future Improvements

- I/O redirection
- Environment variables
- Background processes
- Signal handling
- Wildcards
