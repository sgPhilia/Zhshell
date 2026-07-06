#include "lexer.h"
#include <sstream>

std::vector<Token> tokenize(const std::string& input) {
    std::vector<Token> tokens;
    std::string current_word = "";
    bool in_quotes = false;
    char quote_char = 0;

    for (size_t i = 0; i < input.length(); ++i) {
        char c = input[i];

        if ((c == '"' || c == '\'') && (!in_quotes || quote_char == c)) {
            if (in_quotes) {
                in_quotes = false;
                quote_char = 0;
            } else {
                in_quotes = true;
                quote_char = c;
            }
            continue;
        }

        if (in_quotes) {
            current_word += c;
            continue;
        }

        if (c == ' ' || c == '\t') {
            if (!current_word.empty()) {
                tokens.push_back({TOKEN_WORD, current_word});
                current_word = "";
            }
        } else if (c == '|') {
            if (!current_word.empty()) {
                tokens.push_back({TOKEN_WORD, current_word});
                current_word = "";
            }
            // ตรวจสอบ && หรือ || ในอนาคต (Phase 11)
            tokens.push_back({TOKEN_PIPE, "|"});
        } else if (c == '>') {
            if (!current_word.empty()) {
                tokens.push_back({TOKEN_WORD, current_word});
                current_word = "";
            }
            if (i + 1 < input.length() && input[i + 1] == '>') {
                tokens.push_back({TOKEN_REDIRECT_REPLACE, ">>"}); // Append Mode
                i++;
            } else {
                tokens.push_back({TOKEN_REDIRECT_OUT, ">"});
            }
        } else if (c == '<') {
            if (!current_word.empty()) {
                tokens.push_back({TOKEN_WORD, current_word});
                current_word = "";
            }
            tokens.push_back({TOKEN_REDIRECT_IN, "<"});
        } else {
            current_word += c;
        }
    }

    if (!current_word.empty()) {
        tokens.push_back({TOKEN_WORD, current_word});
    }

    tokens.push_back({TOKEN_EOF, ""});
    return tokens;
}