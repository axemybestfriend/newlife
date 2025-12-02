#pragma once
// lexer.h
#pragma once

#include <string>
#include <vector>
#include <cctype>
#include <fstream>
#include "tokens.h"

namespace frontend {

    class Lexer {
    public:
        explicit Lexer(const std::string& filename);

        Token next();       // получить следующий токен
        Token peek();       // посмотреть следующий токен, не потребляя

    private:
        std::string src;    // весь текст файла
        size_t pos = 0;     // текущая позиция в src
        int line = 1;       // текущая строка
        int col = 1;        // текущая колонка

        char current() const;        // текущий символ
        char lookahead() const;      // следующий символ
        void advance();              // перейти к следующему символу

        Token make_token(TokenKind kind, const std::string& text, int line0, int col0);

        void skip_whitespace();
        Token lex_number();
        Token lex_identifier_or_keyword();
        Token lex_operator();

        bool match(char c);                // попробовать потребить символ c
        bool match_str(const std::string& s);  // попробовать потребить строку s
    };

} // namespace frontend
