#ifndef SHELL_H
#define SHELL_H

#include <iostream>
#include <string>
#include <vector>

#define PROMPT_COLOR "\033[1;32mzhshell$ \033[0m"

void init_shell();
void shell_loop();

#endif