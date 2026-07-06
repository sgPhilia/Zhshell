#include "parser.h"

Pipeline parse_tokens(const std::vector<Token>& tokens) {
    Pipeline pipeline;
    Command current_cmd;

    for (const auto& token : tokens) {
        if (token.type == TOKEN_WORD) {
            // Phase 7: Environment Variable expansion ($HOME, $USER) สามารถทำตรงนี้ได้
            current_cmd.args.push_back(token.value);
        } else if (token.type == TOKEN_PIPE) {
            pipeline.commands.push_back(current_cmd);
            current_cmd = Command(); // เคลียร์ค่าทำอันใหม่
        } else if (token.type == TOKEN_EOF) {
            if (!current_cmd.args.empty()) {
                pipeline.commands.push_back(current_cmd);
            }
        }
        // หมายเหตุ: สำหรับ Phase 8 (Redirection) สามารถขยายเงื่อนไขตรวจเช็ค TOKEN_REDIRECT
        // แล้วดึง Token ถัดไปมาใส่ใน input_file หรือ output_file ได้จากจุดนี้
    }

    return pipeline;
}