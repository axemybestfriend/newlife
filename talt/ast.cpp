#include "ast.h"

namespace frontend {

    void TypeNode::print(std::ostream& out, int indent) const {
        indent_print(out, indent);
        out << "Type: " << name << (is_builtin ? " (builtin)" : " (struct)") << "\n";
    }

    void StructDecl::print(std::ostream& out, int indent) const {
        indent_print(out, indent);
        out << "StructDecl: " << name << "\n";
        for (auto& f : fields) {
            if (f.first) f.first->print(out, indent + 2);
            indent_print(out, indent + 2);
            out << "Field: " << f.second << "\n";
        }
    }

    void VarDecl::print(std::ostream& out, int indent) const {
        indent_print(out, indent);
        out << "VarDecl: " << name << "\n";
        if (type) type->print(out, indent + 2);
        if (init) {
            indent_print(out, indent + 2); out << "Initializer:\n";
            init->print(out, indent + 4);
        }
    }

    void CompoundStmt::print(std::ostream& out, int indent) const {
        indent_print(out, indent); out << "CompoundStmt {\n";
        for (auto& s : stmts) if (s) s->print(out, indent + 2);
        indent_print(out, indent); out << "}\n";
    }

    void FunctionDecl::print(std::ostream& out, int indent) const {
        indent_print(out, indent);
        out << "FunctionDecl: " << name << "\n";
        if (ret_type) ret_type->print(out, indent + 2);
        if (!params.empty()) {
            indent_print(out, indent + 2); out << "Params:\n";
            for (auto& p : params) {
                if (p.first) p.first->print(out, indent + 4);
                indent_print(out, indent + 4); out << "Name: " << p.second << "\n";
            }
        }
        if (body) {
            indent_print(out, indent + 2); out << "Body:\n";
            body->print(out, indent + 4);
        }
    }

    void IfStmt::print(std::ostream& out, int indent) const {
        indent_print(out, indent); out << "IfStmt\n";
        if (condition) condition->print(out, indent + 2);
        if (thenBranch) thenBranch->print(out, indent + 2);
        if (elseBranch) {
            indent_print(out, indent); out << "Else\n";
            elseBranch->print(out, indent + 2);
        }
    }

    void WhileStmt::print(std::ostream& out, int indent) const {
        indent_print(out, indent); out << "WhileStmt\n";
        if (condition) condition->print(out, indent + 2);
        if (body) body->print(out, indent + 2);
    }

} 