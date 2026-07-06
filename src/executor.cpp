#include "executor.h"
#include "builtin.h"
#include <fcntl.h>
#include <unistd.h>    
#include <sys/wait.h>  
#include <iostream>    

int execute_command(const Command& cmd) {
    if (cmd.args.empty()) return 0;

    if (is_builtin(cmd.args[0])) {
        return execute_builtin(cmd);
    }

    std::vector<char*> argv;
    for (const auto& arg : cmd.args) {
        argv.push_back(const_cast<char*>(arg.c_str()));
    }
    argv.push_back(nullptr);

    pid_t pid = fork();
    if (pid == 0) {
        if (execvp(argv[0], argv.data()) == -1) {
            std::cerr << "zhshell: command not found: " << argv[0] << std::endl;
            exit(EXIT_FAILURE);
        }
    } else if (pid < 0) {
        std::cerr << "zhshell: failed to fork process" << std::endl;
        return -1;
    } else {
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) {
            return WEXITSTATUS(status);
        }
    }
    return 0;
}

int execute_pipeline(const Pipeline& pipeline) {
    if (pipeline.commands.size() == 1) {
        return execute_command(pipeline.commands[0]);
    }

    size_t num_cmds = pipeline.commands.size();
    int pipefds[2 * (num_cmds - 1)];

    for (size_t i = 0; i < num_cmds - 1; i++) {
        if (pipe(pipefds + i * 2) < 0) {
            std::cerr << "zhshell: pipe creation failed" << std::endl;
            return -1;
        }
    }

    for (size_t i = 0; i < num_cmds; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            if (i != 0) {
                dup2(pipefds[(i - 1) * 2], 0);
            }
            if (i != num_cmds - 1) {
                dup2(pipefds[i * 2 + 1], 1);
            }

            for (size_t j = 0; j < 2 * (num_cmds - 1); j++) {
                close(pipefds[j]);
            }

            std::vector<char*> argv;
            for (const auto& arg : pipeline.commands[i].args) {
                argv.push_back(const_cast<char*>(arg.c_str()));
            }
            argv.push_back(nullptr);

            if (execvp(argv[0], argv.data()) == -1) {
                std::cerr << "zhshell: exec failed" << std::endl;
                exit(EXIT_FAILURE);
            }
        }
    }

    for (size_t i = 0; i < 2 * (num_cmds - 1); i++) {
        close(pipefds[i]);
    }

    for (size_t i = 0; i < num_cmds; i++) {
        wait(nullptr);
    }

    return 0;
}