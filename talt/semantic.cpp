// semantic.cpp
#include "semantic.h"
#include <sstream>

namespace frontend {

    std::string SemType::toString() const {
        switch (kind) {
        case K_SHORT: return "short";
        case K_INT: return "int";
        case K_LONG: return "long";
        case K_FLOAT: return "float";
        case K_STRUCT: return "struct " + struct_name;
        default: return "undef";
        }
    }

    bool SemType::same(const SemType& o) const {
        if (kind != o.kind) return false;
        if (kind == K_STRUCT) return struct_name == o.struct_name;
        return true;
    }

    Semantic::Semantic() {
        global = std::make_unique<Scope>(nullptr, "<global>");
        cur = global.get();
    }

    Semantic::~Semantic() {}

    void Semantic::enterScope(const std::string& name) {
        cur->children.push_back(std::make_unique<Scope>(cur, name));
        cur = cur->children.back().get();
    }

    void Semantic::leaveScope() {
        if (cur->parent) cur = cur->parent;
    }

    Sym* Semantic::find(const std::string& name) {
        Scope* s = cur;
        while (s) {
            auto it = s->syms.find(name);
            if (it != s->syms.end()) return it->second.get();
            s = s->parent;
        }
        return nullptr;
    }

    Sym* Semantic::findInCurrent(const std::string& name) {
        auto it = cur->syms.find(name);
        if (it != cur->syms.end()) return it->second.get();
        return nullptr;
    }

    bool Semantic::declareSymbol(std::unique_ptr<Sym> sym, int line) {
        if (findInCurrent(sym->name)) {
            errors.push_back(fmt_line(line) + " Duplicate declaration of '" + sym->name + "'");
            return false;
        }
        cur->syms[sym->name] = std::move(sym);
        return true;
    }

    void Semantic::analyze(TranslationUnit* tu) {
        // First pass: declare all structs (so types are known even if used later)
        for (auto& dptr : tu->decls) {
            if (auto sd = dynamic_cast<StructDecl*>(dptr.get())) {
                processStructDecl(sd);
            }
        }
        // Second pass: process all declarations (vars, functions)
        for (auto& dptr : tu->decls) {
            processDecl(dptr.get());
        }
        // If function main present, process it body; otherwise process top-level statements
        bool found_main = false;
        for (auto& dptr : tu->decls) {
            if (auto fd = dynamic_cast<FunctionDecl*>(dptr.get())) {
                if (fd->name == "main") {
                    found_main = true;
                    processFunctionDecl(fd);
                }
            }
        }
        if (!found_main) {
            // process top-level statements
            for (auto& s : tu->toplevel_stmts) processStmt(s.get());
        }
    }

    void Semantic::processDecl(Decl* d) {
        if (auto sd = dynamic_cast<StructDecl*>(d)) {
            // already declared in first pass; but ensure duplicate handled
            // nothing else here
        }
        else if (auto vd = dynamic_cast<VarDecl*>(d)) {
            processVarDecl(vd);
        }
        else if (auto fd = dynamic_cast<FunctionDecl*>(d)) {
            processFunctionDecl(fd);
        }
        else {
            // unknown decl
        }
    }

    void Semantic::processStructDecl(StructDecl* sd) {
        // attempt to declare struct type in current scope
        auto sym = std::make_unique<Sym>(sd->name, Sym::SYM_STRUCT);
        sym->type = SemType::make_struct(sd->name);
        for (auto& f : sd->fields) {
            // map type name to SemType
            SemType st;
            if (f.first->is_builtin) {
                string tn = f.first->name;
                if (tn == "short") st = SemType::make_builtin(SemType::K_SHORT);
                else if (tn == "int") st = SemType::make_builtin(SemType::K_INT);
                else if (tn == "long") st = SemType::make_builtin(SemType::K_LONG);
                else if (tn == "float") st = SemType::make_builtin(SemType::K_FLOAT);
                else st = SemType::make_builtin(SemType::K_INT);
            }
            else {
                st = SemType::make_struct(f.first->name);
            }
            if (sym->fields.find(f.second) != sym->fields.end()) {
                errors.push_back("Duplicate field '" + f.second + "' in struct '" + sd->name + "'");
            }
            else {
                sym->fields[f.second] = st;
            }
        }
        // add to current scope
        declareSymbol(std::move(sym), 0);
    }

    void Semantic::processVarDecl(VarDecl* vd) {
        SemType t;
        if (vd->type->is_builtin) {
            string tn = vd->type->name;
            if (tn == "short") t = SemType::make_builtin(SemType::K_SHORT);
            else if (tn == "int") t = SemType::make_builtin(SemType::K_INT);
            else if (tn == "long") t = SemType::make_builtin(SemType::K_LONG);
            else if (tn == "float") t = SemType::make_builtin(SemType::K_FLOAT);
            else t = SemType::make_builtin(SemType::K_INT);
        }
        else {
            // struct type: ensure declared
            Sym* s = find(vd->type->name);
            if (!s || s->kind != Sym::SYM_STRUCT) {
                errors.push_back("Use of unknown struct type '" + vd->type->name + "'");
                t = SemType::make_struct(vd->type->name); // still create to allow further checks
            }
            else {
                t = SemType::make_struct(vd->type->name);
            }
        }
        auto sym = std::make_unique<Sym>(vd->name, Sym::SYM_VAR);
        sym->type = t;
        if (!declareSymbol(std::move(sym), 0)) {
            // duplicate declared handled
        }
        // initializer
        if (vd->init) {
            SemType rt = processExpr(vd->init.get());
            // check assignment compatibility
            if (t.kind == SemType::K_STRUCT || rt.kind == SemType::K_STRUCT) {
                if (!t.same(rt)) {
                    errors.push_back("Initializer type incompatible for variable '" + vd->name + "'");
                }
            }
            else {
                if (t.isFloat() && rt.isInteger()) {
                    // ok
                }
                else if (t.isInteger() && rt.isFloat()) {
                    errors.push_back("Possible loss of data: assigning float to integer '" + vd->name + "'");
                }
            }
        }
    }

    void Semantic::processFunctionDecl(FunctionDecl* fd) {
        // declare function name in current scope as var-like (so uses error on duplicate)
        auto sym = std::make_unique<Sym>(fd->name, Sym::SYM_VAR);
        // set function return type in sym->type for 'main' we set int
        if (fd->ret_type->is_builtin) {
            string tn = fd->ret_type->name;
            if (tn == "int") sym->type = SemType::make_builtin(SemType::K_INT);
            else if (tn == "float") sym->type = SemType::make_builtin(SemType::K_FLOAT);
            else if (tn == "short") sym->type = SemType::make_builtin(SemType::K_SHORT);
            else if (tn == "long") sym->type = SemType::make_builtin(SemType::K_LONG);
        }
        else {
            sym->type = SemType::make_struct(fd->ret_type->name);
        }
        declareSymbol(std::move(sym), 0);

        // Enter function scope
        enterScope("function:" + fd->name);
        // declare parameters if any (not used in our subset)
        for (auto& p : fd->params) {
            SemType pt;
            if (p.first->is_builtin) {
                string tn = p.first->name;
                if (tn == "int") pt = SemType::make_builtin(SemType::K_INT);
                else if (tn == "float") pt = SemType::make_builtin(SemType::K_FLOAT);
                else if (tn == "short") pt = SemType::make_builtin(SemType::K_SHORT);
                else if (tn == "long") pt = SemType::make_builtin(SemType::K_LONG);
            }
            else {
                pt = SemType::make_struct(p.first->name);
            }
            auto ps = std::make_unique<Sym>(p.second, Sym::SYM_PARAM);
            ps->type = pt;
            declareSymbol(std::move(ps), 0);
        }
        // process function body
        if (fd->body) processCompoundStmt(fd->body.get());
        leaveScope();
    }

    void Semantic::processStmt(Stmt* s) {
        if (!s) return;
        if (auto cs = dynamic_cast<CompoundStmt*>(s)) processCompoundStmt(cs);
        else if (auto fs = dynamic_cast<ForStmt*>(s)) processForStmt(fs);
        else if (auto vds = dynamic_cast<VarDeclStmt*>(s)) processVarDeclStmt(vds);
        else if (auto es = dynamic_cast<ExprStmt*>(s)) processExprStmt(es);
        else if (auto es2 = dynamic_cast<EmptyStmt*>(s)) processEmptyStmt(es2);
        else {
            // other stmts not used
        }
    }

    void Semantic::processCompoundStmt(CompoundStmt* cs) {
        enterScope("<compound>");
        for (auto& st : cs->stmts) processStmt(st.get());
        leaveScope();
    }

    void Semantic::processForStmt(ForStmt* fs) {
        enterScope("<for>");
        if (fs->init) processStmt(fs->init.get());
        if (fs->cond) {
            SemType ct = processExpr(fs->cond.get());
            if (!ct.isScalar()) errors.push_back("For condition must be scalar type");
        }
        if (fs->upd) processExpr(fs->upd.get());
        if (fs->body) processStmt(fs->body.get());
        leaveScope();
    }

    void Semantic::processVarDeclStmt(VarDeclStmt* vds) {
        processVarDecl(vds->decl.get());
    }

    void Semantic::processExprStmt(ExprStmt* es) {
        processExpr(es->expr.get());
    }

    void Semantic::processEmptyStmt(EmptyStmt*) {
        // nothing
    }

    SemType Semantic::processExpr(Expr* e) {
        if (!e) return SemType::make_builtin(SemType::K_INT);
        if (auto lit = dynamic_cast<Literal*>(e)) {
            if (lit->is_float) return SemType::make_builtin(SemType::K_FLOAT);
            return SemType::make_builtin(SemType::K_INT);
        }
        if (auto id = dynamic_cast<Ident*>(e)) {
            Sym* s = find(id->name);
            if (!s) {
                errors.push_back("Use of undeclared identifier '" + id->name + "'");
                return SemType::make_builtin(SemType::K_UNDEF);
            }
            return s->type;
        }
        if (auto fa = dynamic_cast<FieldAccess*>(e)) {
            // base must evaluate to struct type
            // base can be Ident or another FieldAccess
            // process base first
            SemType base_t = processExpr(fa->base.get());
            if (base_t.kind != SemType::K_STRUCT) {
                errors.push_back("Left of '.' is not a struct");
                return SemType::make_builtin(SemType::K_UNDEF);
            }
            // find struct definition
            Sym* s = find(base_t.struct_name);
            if (!s || s->kind != Sym::SYM_STRUCT) {
                errors.push_back("Struct type '" + base_t.struct_name + "' not declared");
                return SemType::make_builtin(SemType::K_UNDEF);
            }
            auto it = s->fields.find(fa->field);
            if (it == s->fields.end()) {
                errors.push_back("Struct '" + s->name + "' has no field '" + fa->field + "'");
                return SemType::make_builtin(SemType::K_UNDEF);
            }
            return it->second;
        }
        if (auto asg = dynamic_cast<AssignmentExpr*>(e)) {
            // target must be Ident or FieldAccess
            SemType ltype = SemType::make_builtin(SemType::K_UNDEF);
            if (auto tid = dynamic_cast<Ident*>(asg->target.get())) {
                Sym* s = find(tid->name);
                if (!s) {
                    errors.push_back("Left side of assignment: undeclared identifier '" + tid->name + "'");
                }
                else if (s->kind != Sym::SYM_VAR && s->kind != Sym::SYM_PARAM) {
                    errors.push_back("Left side of assignment is not a variable: '" + tid->name + "'");
                }
                else {
                    ltype = s->type;
                }
            }
            else if (auto tf = dynamic_cast<FieldAccess*>(asg->target.get())) {
                ltype = processExpr(tf);
            }
            else {
                errors.push_back("Invalid left side of assignment");
            }
            SemType rtype = processExpr(asg->value.get());
            // check compatibility
            if (ltype.kind == SemType::K_STRUCT || rtype.kind == SemType::K_STRUCT) {
                if (!ltype.same(rtype)) {
                    errors.push_back("Incompatible struct types in assignment");
                }
            }
            else {
                if (ltype.isFloat() && rtype.isInteger()) {
                    // ok
                }
                else if (ltype.isInteger() && rtype.isFloat()) {
                    errors.push_back("Possible loss of data: assigning float to integer");
                }
            }
            return rtype;
        }
        if (auto be = dynamic_cast<BinaryExpr*>(e)) {
            SemType L = processExpr(be->lhs.get());
            SemType R = processExpr(be->rhs.get());
            string op = be->op;
            if (op == "&" || op == "|" || op == "^" || op == "<<" || op == ">>") {
                if (!L.isInteger() || !R.isInteger()) {
                    errors.push_back("Bitwise operator '" + op + "' used with non-integer operand");
                    return SemType::make_builtin(SemType::K_UNDEF);
                }
                if (L.kind == SemType::K_LONG || R.kind == SemType::K_LONG) return SemType::make_builtin(SemType::K_LONG);
                if (L.kind == SemType::K_INT || R.kind == SemType::K_INT) return SemType::make_builtin(SemType::K_INT);
                return SemType::make_builtin(SemType::K_SHORT);
            }
            if (op == "+" || op == "-" || op == "*" || op == "/" || op == "%") {
                if (L.isFloat() || R.isFloat()) return SemType::make_builtin(SemType::K_FLOAT);
                if (L.kind == SemType::K_LONG || R.kind == SemType::K_LONG) return SemType::make_builtin(SemType::K_LONG);
                if (L.kind == SemType::K_INT || R.kind == SemType::K_INT) return SemType::make_builtin(SemType::K_INT);
                return SemType::make_builtin(SemType::K_SHORT);
            }
            if (op == "<" || op == ">" || op == "<=" || op == ">=" || op == "==" || op == "!=") {
                if (!(L.isScalar() && R.isScalar())) {
                    errors.push_back("Comparison '" + op + "' applied to non-scalar types");
                }
                return SemType::make_builtin(SemType::K_INT);
            }
        }
        if (auto ue = dynamic_cast<UnaryExpr*>(e)) {
            return processExpr(ue->operand.get());
        }
        // fallback
        return SemType::make_builtin(SemType::K_INT);
    }

} // namespace frontend
