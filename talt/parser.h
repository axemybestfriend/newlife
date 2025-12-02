// parser.h
#pragma once
#include "lexer.h"
#include "ast.h"
#include <memory>

namespace frontend {

    class Parser {
    public:
        explicit Parser(const std::string& filename);
        std::unique_ptr<TranslationUnit> parse();

        // Access semantic errors collected during parsing (basic)
        const std::vector<std::string>& getErrors() const { return errors; }

    private:
        Lexer lex;
        Token cur;
        std::vector<std::string> errors;

        void next();
        bool accept(TokenKind k);
        bool expect(TokenKind k, const std::string& msg);

        // Parsing functions
        std::unique_ptr<TranslationUnit> parseTranslationUnit();

        std::unique_ptr<Decl> parseDecl();
        std::unique_ptr<StructDecl> parseStructDecl();
        std::unique_ptr<VarDecl> parseVarDecl(bool allowInit = true);

        std::unique_ptr<Stmt> parseStmt();
        std::unique_ptr<CompoundStmt> parseCompoundStmt();
        std::unique_ptr<Stmt> parseForStmt();
        std::unique_ptr<Stmt> parseSimpleStmt(); // expr-stmt or decl-stmt

        std::unique_ptr<Expr> parseExpression();
        std::unique_ptr<Expr> parseAssign();
        std::unique_ptr<Expr> parseBinary(int min_prec = 0);
        std::unique_ptr<Expr> parseUnary();
        std::unique_ptr<Expr> parsePrimary();

        // Helpers
        bool isTypeName(const Token& t);
        std::string tokenText(const Token& t) const { return t.text; }

        // operator precedence
        int getPrecedence(const std::string& op) const;
    };

} // namespace frontend
