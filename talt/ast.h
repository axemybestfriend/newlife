// ast.h (updated with FunctionDecl)
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
    using std::make_unique;

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
        void print(std::ostream& out, int indent = 0) const override {
            indent_print(out, indent);
            out << "Type: " << name << (is_builtin ? " (builtin)" : " (struct)") << "\n";
        }
    };

    struct Decl : ASTNode {};

    struct StructDecl : Decl {
        string name;
        vector<std::pair<std::unique_ptr<TypeNode>, string>> fields;
        void print(std::ostream& out, int indent = 0) const override {
            indent_print(out, indent);
            out << "StructDecl: " << name << "\n";
            for (auto& f : fields) {
                f.first->print(out, indent + 2);
                indent_print(out, indent + 2);
                out << "Field: " << f.second << "\n";
            }
        }
    };

    struct VarDecl : Decl {
        std::unique_ptr<TypeNode> type;
        string name;
        std::unique_ptr<struct Expr> init;
        void print(std::ostream& out, int indent = 0) const override {
            indent_print(out, indent);
            out << "VarDecl: " << name << "\n";
            type->print(out, indent + 2);
            if (init) {
                indent_print(out, indent + 2); out << "Initializer:\n";
                init->print(out, indent + 4);
            }
        }
    };

    struct FunctionDecl : Decl {
        std::unique_ptr<TypeNode> ret_type;
        string name;
        vector<std::pair<std::unique_ptr<TypeNode>, string>> params;
        std::unique_ptr<struct CompoundStmt> body;
        void print(std::ostream& out, int indent = 0) const override {
            indent_print(out, indent);
            out << "FunctionDecl: " << name << "\n";
            ret_type->print(out, indent + 2);
            if (!params.empty()) {
                indent_print(out, indent + 2); out << "Params:\n";
                for (auto& p : params) {
                    p.first->print(out, indent + 4);
                    indent_print(out, indent + 4); out << "Name: " << p.second << "\n";
                }
            }
            if (body) {
                indent_print(out, indent + 2); out << "Body:\n";
                body->print(out, indent + 4);
            }
        }
    };

    // Statements and expressions (same as earlier)
    struct Stmt : ASTNode {};
    struct Expr : ASTNode { TypeNode* inferred_type = nullptr; };

    struct EmptyStmt : Stmt {
        void print(std::ostream& out, int indent = 0) const override {
            indent_print(out, indent); out << "EmptyStmt\n";
        }
    };

    struct CompoundStmt : Stmt {
        vector<std::unique_ptr<Stmt>> stmts;
        void print(std::ostream& out, int indent = 0) const override {
            indent_print(out, indent); out << "CompoundStmt {\n";
            for (auto& s : stmts) s->print(out, indent + 2);
            indent_print(out, indent); out << "}\n";
        }
    };

    struct ExprStmt : Stmt {
        std::unique_ptr<Expr> expr;
        ExprStmt(std::unique_ptr<Expr> e) : expr(std::move(e)) {}
        void print(std::ostream& out, int indent = 0) const override {
            indent_print(out, indent); out << "ExprStmt:\n";
            expr->print(out, indent + 2);
        }
    };

    struct ForStmt : Stmt {
        std::unique_ptr<Stmt> init;
        std::unique_ptr<Expr> cond;
        std::unique_ptr<Expr> upd;
        std::unique_ptr<Stmt> body;
        void print(std::ostream& out, int indent = 0) const override {
            indent_print(out, indent); out << "ForStmt:\n";
            indent_print(out, indent + 2); out << "Init:\n";
            if (init) init->print(out, indent + 4);
            indent_print(out, indent + 2); out << "Cond:\n";
            if (cond) cond->print(out, indent + 4);
            indent_print(out, indent + 2); out << "Update:\n";
            if (upd) upd->print(out, indent + 4);
            indent_print(out, indent + 2); out << "Body:\n";
            if (body) body->print(out, indent + 4);
        }
    };

    struct VarDeclStmt : Stmt {
        std::unique_ptr<VarDecl> decl;
        VarDeclStmt(std::unique_ptr<VarDecl> d) : decl(std::move(d)) {}
        void print(std::ostream& out, int indent = 0) const override {
            indent_print(out, indent); out << "VarDeclStmt:\n";
            decl->print(out, indent + 2);
        }
    };

    struct Literal : Expr {
        string lexeme;
        bool is_float = false;
        Literal(const string& l = "", bool f = false) : lexeme(l), is_float(f) {}
        void print(std::ostream& out, int indent = 0) const override {
            indent_print(out, indent); out << "Literal: " << lexeme << (is_float ? " (float)" : " (int)") << "\n";
        }
    };

    struct Ident : Expr {
        string name;
        Ident(const string& n) : name(n) {}
        void print(std::ostream& out, int indent = 0) const override {
            indent_print(out, indent); out << "Ident: " << name << "\n";
        }
    };

    struct FieldAccess : Expr {
        std::unique_ptr<Expr> base;
        string field;
        FieldAccess(std::unique_ptr<Expr> b, const string& f) : base(std::move(b)), field(f) {}
        void print(std::ostream& out, int indent = 0) const override {
            indent_print(out, indent); out << "FieldAccess:\n";
            base->print(out, indent + 2);
            indent_print(out, indent + 2); out << "Field: " << field << "\n";
        }
    };

    struct BinaryExpr : Expr {
        string op;
        std::unique_ptr<Expr> lhs, rhs;
        BinaryExpr(std::unique_ptr<Expr> l, const string& o, std::unique_ptr<Expr> r)
            : op(o), lhs(std::move(l)), rhs(std::move(r)) {}
        void print(std::ostream& out, int indent = 0) const override {
            indent_print(out, indent); out << "BinaryExpr: " << op << "\n";
            lhs->print(out, indent + 2);
            rhs->print(out, indent + 2);
        }
    };

    struct UnaryExpr : Expr {
        string op;
        std::unique_ptr<Expr> operand;
        UnaryExpr(const string& o, std::unique_ptr<Expr> e) : op(o), operand(std::move(e)) {}
        void print(std::ostream& out, int indent = 0) const override {
            indent_print(out, indent); out << "UnaryExpr: " << op << "\n";
            operand->print(out, indent + 2);
        }
    };

    struct AssignmentExpr : Expr {
        std::unique_ptr<Expr> target;
        std::unique_ptr<Expr> value;
        AssignmentExpr(std::unique_ptr<Expr> t, std::unique_ptr<Expr> v) : target(std::move(t)), value(std::move(v)) {}
        void print(std::ostream& out, int indent = 0) const override {
            indent_print(out, indent); out << "Assignment:\n";
            target->print(out, indent + 2);
            value->print(out, indent + 2);
        }
    };

    struct TranslationUnit : ASTNode {
        vector<std::unique_ptr<Decl>> decls;
        vector<std::unique_ptr<Stmt>> toplevel_stmts;
        void print(std::ostream& out, int indent = 0) const override {
            indent_print(out, indent); out << "TranslationUnit:\n";
            for (auto& d : decls) d->print(out, indent + 2);
            for (auto& s : toplevel_stmts) s->print(out, indent + 2);
        }
    };

}