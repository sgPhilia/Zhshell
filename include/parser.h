#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include <vector>
#include <string>

struct Command {
    std::vector<std::string> args;
    std::string input_file;
    std::string output_file;
    bool append_output = false;
    bool background = false;
};

struct Pipeline {
    std::vector<Command> commands;
};

Pipeline parse_tokens(const std::vector<Token>& tokens);

#endif