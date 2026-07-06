#ifndef BUILTIN_H
#define BUILTIN_H

#include "parser.h"

bool is_builtin(const std::string& cmd);
int execute_builtin(const Command& cmd);

#endif