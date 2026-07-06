#include "parser.h"

Pipeline parse_tokens(const std::vector<Token>& tokens) {
    Pipeline pipeline;
    Command current_cmd;

    for (const auto& token : tokens) {
        if (token.type == TOKEN_WORD) {
            current_cmd.args.push_back(token.value);
        } else if (token.type == TOKEN_PIPE) {
            pipeline.commands.push_back(current_cmd);
            current_cmd = Command();
        } else if (token.type == TOKEN_EOF) {
            if (!current_cmd.args.empty()) {
                pipeline.commands.push_back(current_cmd);
            }
        }
    }

    return pipeline;
}