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
├── src/
├── Makefile
└── README.md

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
