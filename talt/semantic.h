// semantic.h
#pragma once
#include "ast.h"
#include <string>
#include <vector>
#include <map>

namespace frontend {

    // Simplified Type representation for semantic checks
    struct SemType {
        enum Kind { K_UNDEF, K_SHORT, K_INT, K_LONG, K_FLOAT, K_STRUCT } kind = K_UNDEF;
        std::string struct_name; // if K_STRUCT
        static SemType make_builtin(Kind k) { SemType t; t.kind = k; return t; }
        static SemType make_struct(const std::string& n) { SemType t; t.kind = K_STRUCT; t.struct_name = n; return t; }
        std::string toString() const;
        bool isInteger() const { return kind == K_SHORT || kind == K_INT || kind == K_LONG; }
        bool isFloat() const { return kind == K_FLOAT; }
        bool isScalar() const { return isInteger() || isFloat(); }
        bool same(const SemType& o) const;
    };

    // Symbol in table
    struct Sym {
        enum Kind { SYM_VAR, SYM_STRUCT, SYM_PARAM } kind;
        std::string name;
        SemType type;
        std::map<std::string, SemType> fields; // for struct
        Sym(std::string n = "", Kind k = SYM_VAR) : kind(k), name(n) {}
    };

    // Scope with symbols
    struct Scope {
        Scope* parent = nullptr;
        std::vector<std::unique_ptr<Scope>> children;
        std::map<std::string, std::unique_ptr<Sym>> syms;
        std::string name;
        Scope(Scope* p = nullptr, const std::string& n = "<scope>") : parent(p), name(n) {}
    };

    // Semantic analyzer: builds table, checks rules, collects errors
    class Semantic {
    public:
        Semantic();
        ~Semantic();

        void analyze(TranslationUnit* tu);

        // After analysis:
        const std::vector<std::string>& getErrors() const { return errors; }
        Scope* getGlobalScope() const { return global.get(); }

    private:
        std::unique_ptr<Scope> global;
        Scope* cur; // current scope pointer
        std::vector<std::string> errors;

        // helpers
        void enterScope(const std::string& name = "<block>");
        void leaveScope();

        // declaration processing
        void processDecl(Decl* d);
        void processStructDecl(StructDecl* sd);
        void processVarDecl(VarDecl* vd);
        void processFunctionDecl(FunctionDecl* fd);

        // statement processing
        void processStmt(Stmt* s);
        void processCompoundStmt(CompoundStmt* cs);
        void processForStmt(ForStmt* fs);
        void processVarDeclStmt(VarDeclStmt* vds);
        void processExprStmt(ExprStmt* es);
        void processEmptyStmt(EmptyStmt* es);

        // expression processing (returns SemType)
        SemType processExpr(Expr* e);

        // lookup
        Sym* find(const std::string& name);
        Sym* findInCurrent(const std::string& name);

        // symbol insertion
        bool declareSymbol(std::unique_ptr<Sym> sym, int line);

        // utils
        std::string fmt_line(int line) const { return "Line " + std::to_string(line) + ":"; }
    };

} // namespace frontend
