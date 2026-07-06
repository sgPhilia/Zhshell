#include "builtin.h"
#include <iostream>
#include <unistd.h>
#include <cstdlib>

bool is_builtin(const std::string& cmd) {
    return (cmd == "cd" || cmd == "pwd" || cmd == "exit" || cmd == "echo");
}

int execute_builtin(const Command& cmd) {
    if (cmd.args[0] == "exit") {
        std::cout << "Exiting zhshell..." << std::endl;
        exit(0);
    } 
    else if (cmd.args[0] == "cd") {
        std::string target_dir = (cmd.args.size() > 1) ? cmd.args[1] : std::getenv("HOME");
        if (chdir(target_dir.c_str()) != 0) {
            perror("zhshell: cd");
            return 1;
        }
        return 0;
    } 
    else if (cmd.args[0] == "pwd") {
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd)) != nullptr) {
            std::cout << cwd << std::endl;
            return 0;
        }
        return 1;
    } 
    else if (cmd.args[0] == "echo") {
        for (size_t i = 1; i < cmd.args.size(); ++i) {
            std::cout << cmd.args[i] << (i == cmd.args.size() - 1 ? "" : " ");
        }
        std::cout << std::endl;
        return 0;
    }
    return -1;
}