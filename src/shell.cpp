#include "shell.h"
#include "lexer.h"
#include "parser.h"
#include "executor.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <cstdlib>

void init_shell() {
    using_history();
}

void shell_loop() {
    char* input_line;

    while (true) {
        input_line = readline(PROMPT_COLOR);

        if (!input_line) {
            std::cout << "\nGoodbye!" << std::endl;
            break;
        }

        std::string input(input_line);

        if (input.empty() || input.find_first_not_of(" \t\n\v\f\r") == std::string::npos) {
            continue;
        }

        add_history(input.c_str());

        std::vector<Token> tokens = tokenize(input);
        Pipeline pipeline = parse_tokens(tokens);
        
        if (!pipeline.commands.empty()) {
            execute_pipeline(pipeline);
        }
    }
}