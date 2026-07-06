zhshell
A modular, lightweight, POSIX-compliant mini-shell implemented in C++17.
This project is a hands-on exploration of Linux system programming, process management, file descriptors, and command-line parsing. The shell is organized into modular stages—Lexer → Parser → Executor—making the codebase highly readable, maintainable, and easy to extend.
 Features
Process Lifecycle Management: Utilizes fork(), execvp(), and waitpid() to safely execute and manage external programs.
Dynamic PATH Resolution: Dynamically locates system executables using the system's PATH environment variable.
Argument & Quote Parsing: Accurately parses command arguments while preserving literal whitespaces enclosed within single (') and double (") quotes.
Built-in Commands: Native support for essential shell operations:
cd — Change directory
pwd — Print working directory
echo — Output text arguments
exit — Terminate the shell session
Pipeline Support: Supports chaining multiple commands sequentially using UNIX pipes (|).
ls -la | grep txt | wc -l


Command History & Navigation: Integrated with the GNU Readline library to provide seamless arrow-key history scrolling and line editing.
 Project Structure
zhshell/
├── include/            # Header files
│   ├── builtin.h
│   ├── executor.h
│   ├── lexer.h
│   ├── parser.h
│   └── shell.h
├── src/                # Source implementations
│   ├── builtin.cpp
│   ├── executor.cpp
│   ├── lexer.cpp
│   ├── main.cpp
│   ├── parser.cpp
│   └── shell.cpp
├── Makefile            # Build configuration
└── README.md           # Documentation


 Requirements
OS: Linux (Developed and tested heavily on Arch Linux)
Compiler: GCC/G++ with full C++17 support
Build System: GNU Make
Libraries: GNU Readline
 Installation
1. Install Dependencies
On Arch Linux, run the following to grab the essential toolchain and development libraries:
sudo pacman -S gcc make readline


2. Clone the Repository
git clone [https://github.com/](https://github.com/)<your-username>/zhshell.git
cd zhshell


3. Build the Project
Compile the executable using the provided Makefile:
make


This compiles the source files into an obj/ directory and outputs the final production binary into the root directory as:
zhshell


 Usage
Launch your new custom shell directly from the terminal:
./zhshell


Example Commands
External Commands
zhshell$ ls -la
zhshell$ uname -a
zhshell$ mkdir sandbox


Built-in Commands
zhshell$ pwd
zhshell$ cd sandbox
zhshell$ pwd


Quote Parsing
zhshell$ echo "Hello      World"


Pipelines
zhshell$ ls -la | grep sandbox


Exit
To exit the shell safely, type exit or send an EOF signal:
zhshell$ exit


(Alternatively, press Ctrl + D)
 Cleaning Up
To strip away all generated object binaries and start a fresh compilation pipeline:
make clean


 Future Improvements
[ ] I/O Redirection: Support for standard input/output redirection stream overrides (>, <, >>).
[ ] Environment Variable Expansion: Dynamic variable evaluation (e.g., $HOME, $PATH).
[ ] Background Processing: Support asynchronous execution using the background ampersand operator (&).
[ ] Signal Handling: Graceful handling of Unix signals like Ctrl + C (SIGINT) and Ctrl + Z (SIGTSTP).
[ ] Wildcard Expansion: Native filename globbing capabilities using wildcards (*).
