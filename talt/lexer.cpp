#include "lexer.h"
#include <stdexcept>

namespace frontend {

    Lexer::Lexer(const std::string& filename) {
        std::ifstream in(filename);
        if (!in.is_open())
            throw std::runtime_error("Cannot open file: " + filename);

        src.assign(std::istreambuf_iterator<char>(in),
            std::istreambuf_iterator<char>());
    }

    char Lexer::current() const {
        return (pos < src.size() ? src[pos] : '\0');
    }

    char Lexer::lookahead() const {
        return (pos + 1 < src.size() ? src[pos + 1] : '\0');
    }

    void Lexer::advance() {
        if (pos < src.size()) {
            if (src[pos] == '\n') {
                line++;
                col = 1;
            }
            else {
                col++;
            }
            pos++;
        }
    }

    bool Lexer::match(char c) {
        if (current() == c) {
            advance();
            return true;
        }
        return false;
    }

    bool Lexer::match_str(const std::string& s) {
        if (src.substr(pos, s.size()) == s) {
            for (size_t i = 0; i < s.size(); i++) advance();
            return true;
        }
        return false;
    }

    Token Lexer::make_token(TokenKind kind, const std::string& text, int line0, int col0) {
        return Token(kind, text, line0, col0);
    }

    void Lexer::skip_whitespace() {
        while (true) {
            if (isspace(current())) {
                advance();
                continue;
            }
            // комментарии
            if (current() == '/' && lookahead() == '/') {
                while (current() != '\n' && current() != '\0') advance();
                continue;
            }
            if (current() == '/' && lookahead() == '*') {
                advance(); advance();
                while (!(current() == '*' && lookahead() == '/') && current() != '\0') {
                    advance();
                }
                if (current() == '*' && lookahead() == '/') {
                    advance(); advance();
                }
                continue;
            }
            break;
        }
    }

    Token Lexer::lex_number() {
        int line0 = line, col0 = col;
        std::string buf;

        bool has_dot = false;
        bool has_exp = false;

        while (isdigit(current()) || current() == '.' || current() == 'e' || current() == 'E' || current() == '+' || current() == '-') {
            if (current() == '.') {
                if (has_dot) break;
                has_dot = true;
            }
            if (current() == 'e' || current() == 'E') {
                if (has_exp) break;
                has_exp = true;
            }
            buf.push_back(current());
            advance();
        }

        return make_token(TokenKind::TK_NUMBER, buf, line0, col0);
    }

    Token Lexer::lex_identifier_or_keyword() {
        int line0 = line, col0 = col;
        std::string buf;

        while (isalnum(current()) || current() == '_') {
            buf.push_back(current());
            advance();
        }

        if (is_keyword_struct(buf))
            return make_token(TokenKind::TK_KW_STRUCT, buf, line0, col0);
        if (is_keyword_for(buf))
            return make_token(TokenKind::TK_KW_FOR, buf, line0, col0);
        if (buf == "short")
            return make_token(TokenKind::TK_KW_SHORT, buf, line0, col0);
        if (buf == "int")
            return make_token(TokenKind::TK_KW_INT, buf, line0, col0);
        if (buf == "long")
            return make_token(TokenKind::TK_KW_LONG, buf, line0, col0);
        if (buf == "float")
            return make_token(TokenKind::TK_KW_FLOAT, buf, line0, col0);

        return make_token(TokenKind::TK_IDENT, buf, line0, col0);
    }

    Token Lexer::lex_operator() {
        int line0 = line, col0 = col;

        // много символов
        if (match_str("<<")) return make_token(TokenKind::TK_SHL, "<<", line0, col0);
        if (match_str(">>")) return make_token(TokenKind::TK_SHR, ">>", line0, col0);
        if (match_str("<=")) return make_token(TokenKind::TK_LE, "<=", line0, col0);
        if (match_str(">=")) return make_token(TokenKind::TK_GE, ">=", line0, col0);
        if (match_str("==")) return make_token(TokenKind::TK_EQ, "==", line0, col0);
        if (match_str("!=")) return make_token(TokenKind::TK_NE, "!=", line0, col0);

        // один символ
        char c = current();
        advance();
        switch (c) {
        case ';': return make_token(TokenKind::TK_SEMI, ";", line0, col0);
        case '(': return make_token(TokenKind::TK_LPAREN, "(", line0, col0);
        case ')': return make_token(TokenKind::TK_RPAREN, ")", line0, col0);
        case '{': return make_token(TokenKind::TK_LBRACE, "{", line0, col0);
        case '}': return make_token(TokenKind::TK_RBRACE, "}", line0, col0);
        case ',': return make_token(TokenKind::TK_COMMA, ",", line0, col0);
        case '.': return make_token(TokenKind::TK_DOT, ".", line0, col0);
        case '=': return make_token(TokenKind::TK_ASSIGN, "=", line0, col0);
        case '+': return make_token(TokenKind::TK_PLUS, "+", line0, col0);
        case '-': return make_token(TokenKind::TK_MINUS, "-", line0, col0);
        case '*': return make_token(TokenKind::TK_MUL, "*", line0, col0);
        case '/': return make_token(TokenKind::TK_DIV, "/", line0, col0);
        case '%': return make_token(TokenKind::TK_MOD, "%", line0, col0);
        case '&': return make_token(TokenKind::TK_AMP, "&", line0, col0);
        case '|': return make_token(TokenKind::TK_PIPE, "|", line0, col0);
        case '^': return make_token(TokenKind::TK_CARET, "^", line0, col0);
        case '<': return make_token(TokenKind::TK_LT, "<", line0, col0);
        case '>': return make_token(TokenKind::TK_GT, ">", line0, col0);
        }

        return make_token(TokenKind::TK_UNKNOWN, std::string(1, c), line0, col0);
    }

    Token Lexer::next() {
        skip_whitespace();

        int line0 = line, col0 = col;
        char c = current();

        if (c == '\0')
            return Token(TokenKind::TK_EOF, "", line0, col0);

        if (isdigit(c))
            return lex_number();

        if (isalpha(c) || c == '_')
            return lex_identifier_or_keyword();

        return lex_operator();
    }

    Token Lexer::peek() {
        size_t saved_pos = pos;
        int saved_line = line;
        int saved_col = col;
        Token t = next();
        pos = saved_pos;
        line = saved_line;
        col = saved_col;
        return t;
    }

} // namespace frontend
