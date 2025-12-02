#pragma once
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include "tokens.h"

namespace frontend {
    using std::string;
    using std::vector;
    using std::unique_ptr;

    // Forward declarations
    struct ASTNode;
    struct TypeNode;
    struct Decl;
    struct Stmt;
    struct Expr;
    struct CompoundStmt;
    struct VarDecl;

    inline void indent_print(std::ostream& out, int indent) {
        for (int i = 0; i < indent; i++) out.put(' ');
    }

    struct ASTNode {
        virtual ~ASTNode() = default;
        virtual void print(std::ostream& out, int indent = 0) const = 0;
    };

    struct TypeNode : ASTNode {
        string name;
        bool is_builtin = true;
        TypeNode() = default;
        TypeNode(const string& n, bool builtin = true) : name(n), is_builtin(builtin) {}
        void print(std::ostream& out, int indent = 0) const override;
    };

    struct Decl : ASTNode {};

    struct StructDecl : Decl {
        string name;
        vector<std::pair<unique_ptr<TypeNode>, string>> fields;
        void print(std::ostream& out, int indent = 0) const override;
    };

    struct VarDecl : Decl {
        unique_ptr<TypeNode> type;
        string name;
        unique_ptr<Expr> init;
        void print(std::ostream& out, int indent = 0) const override;  // Только объявление
    };

    struct Stmt : ASTNode {};

    struct Expr : ASTNode {
        TypeNode* inferred_type = nullptr;
        virtual ~Expr() = default;
    };

    struct CompoundStmt : Stmt {
        vector<unique_ptr<Stmt>> stmts;
        void print(std::ostream& out, int indent = 0) const override;
    };

    struct FunctionDecl : Decl {
        unique_ptr<TypeNode> ret_type;
        string name;
        vector<std::pair<unique_ptr<TypeNode>, string>> params;
        unique_ptr<CompoundStmt> body;
        void print(std::ostream& out, int indent = 0) const override;
    };

    struct EmptyStmt : Stmt {
        void print(std::ostream& out, int indent = 0) const override;
    };

    struct ExprStmt : Stmt {
        unique_ptr<Expr> expr;
        ExprStmt(unique_ptr<Expr> e) : expr(std::move(e)) {}
        void print(std::ostream& out, int indent = 0) const override;
    };

    struct IfStmt : Stmt {
        unique_ptr<Expr> condition;
        unique_ptr<Stmt> thenBranch;
        unique_ptr<Stmt> elseBranch;

        IfStmt(unique_ptr<Expr> cond, unique_ptr<Stmt> then, unique_ptr<Stmt> els = nullptr)
            : condition(std::move(cond)), thenBranch(std::move(then)), elseBranch(std::move(els)) {}

        void print(std::ostream& out, int indent = 0) const override;
    };

    struct WhileStmt : Stmt {
        unique_ptr<Expr> condition;
        unique_ptr<Stmt> body;

        WhileStmt(unique_ptr<Expr> cond, unique_ptr<Stmt> b)
            : condition(std::move(cond)), body(std::move(b)) {}

        void print(std::ostream& out, int indent = 0) const override;
    };
} 