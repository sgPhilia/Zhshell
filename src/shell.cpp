#include "shell.h"
#include "lexer.h"
#include "parser.h"
#include "executor.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <cstdlib>

void init_shell() {
    // Phase 14: จัดการสัญญาณเริ่มต้น (เช่น ignore Ctrl+C ใน Parent)
    // สามารถขยายผลใน signal.cpp ได้
    using_history();
}

void shell_loop() {
    char* input_line;

    // Phase 1: Infinite Loop & Input Handling
    while (true) {
        input_line = readline(PROMPT_COLOR);

        // Ctrl+D ส่งค่า NULL กลับมา
        if (!input_line) {
            std::cout << "\nGoodbye!" << std::endl;
            break;
        }

        std::string input(input_line);
        free(input_line); // คืนหน่วยความจำของ readline

        if (input.empty() || input.find_first_not_of(" \t\n\v\f\r") == std::string::npos) {
            continue;
        }

        // เพิ่มเข้า History (Phase 15)
        add_history(input.c_str());

        // Pipeline การประมวลผล (ตามสถาปัตยกรรมที่คุณวางไว้)
        std::vector<Token> tokens = tokenize(input);
        Pipeline pipeline = parse_tokens(tokens);
        
        if (!pipeline.commands.empty()) {
            execute_pipeline(pipeline);
        }
    }
}