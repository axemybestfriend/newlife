
#include <iostream>
#include <fstream>
#include <functional>
#include "parser.h"
#include "semantic.h"

using namespace frontend;

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <source_file>\n";
        return 1;
    }
    std::string fname = argv[1];
    try {
        Parser parser(fname);
        auto tu = parser.parse();

        std::cout << "=== AST ===\n";
        tu->print(std::cout, 0);

        // show parser errors if any
        if (!parser.getErrors().empty()) {
            std::cout << "\nParser errors:\n";
            for (auto& e : parser.getErrors()) std::cout << e << "\n";
        }

        // semantic analysis
        Semantic sem;
        sem.analyze(tu.get());

        std::cout << "\n=== Symbol Table (Global Scope) ===\n";
        // Print global symbols simple
        Scope* g = sem.getGlobalScope();
        std::function<void(Scope*, int)> printScope = [&](Scope* s, int lvl) {
            std::string ind(lvl * 2, ' ');
            std::cout << ind << s->name << ":\n";
            for (auto& p : s->syms) {
                Sym* sym = p.second.get();
                std::cout << ind << "  " << sym->name << " : ";
                std::cout << sym->type.toString() << "\n";
                if (sym->kind == Sym::SYM_STRUCT) {
                    for (auto& f : sym->fields) {
                        std::cout << ind << "    " << f.first << " : " << f.second.toString() << "\n";
                    }
                }
            }
            for (auto& c : s->children) printScope(c.get(), lvl + 1);
        };
        printScope(g, 0);

        std::cout << "\n=== Semantic Errors ===\n";
        if (sem.getErrors().empty()) std::cout << "No semantic errors.\n";
        else {
            for (auto& e : sem.getErrors()) std::cout << e << "\n";
        }
    }
    catch (const std::exception& ex) {
        std::cerr << "Fatal: " << ex.what() << "\n";
        return 2;
    }
    return 0;
}
