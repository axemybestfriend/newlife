#pragma once

#include <string>

namespace frontend {

    // Вид токена
    enum class TokenKind {
        TK_EOF,
        TK_IDENT,
        TK_NUMBER,     // integer or float literal
        TK_SEMI,       // ;
        TK_LPAREN,     // (
        TK_RPAREN,     // )
        TK_LBRACE,     // {
        TK_RBRACE,     // }
        TK_COMMA,      // ,
        TK_DOT,        // .
        TK_ASSIGN,     // =
        TK_PLUS, TK_MINUS, TK_MUL, TK_DIV, TK_MOD,
        TK_AMP, TK_PIPE, TK_CARET,
        TK_SHL, TK_SHR, // << >>
        TK_LT, TK_GT, TK_LE, TK_GE, TK_EQ, TK_NE,
        TK_KW_STRUCT,
        TK_KW_FOR,
        TK_KW_SHORT, TK_KW_INT, TK_KW_LONG, TK_KW_FLOAT,
        TK_UNKNOWN
    };

    // Информация о токене (лексема, тип, позиция)
    struct Token {
        TokenKind kind = TokenKind::TK_UNKNOWN;
        std::string text; // исходная лексема
        int line = 1;     // номер строки в исходном файле
        int col = 1;     // номер колонки (опционально)

        Token() = default;
        Token(TokenKind k, std::string t, int l = 1, int c = 1)
            : kind(k), text(std::move(t)), line(l), col(c) {}
    };

    // Утилиты
    inline bool is_keyword_struct(const std::string& s) { return s == "struct"; }
    inline bool is_keyword_for(const std::string& s) { return s == "for"; }
    inline bool is_type_keyword(const std::string& s) {
        return s == "short" || s == "int" || s == "long" || s == "float";
    }

} // namespace frontend
