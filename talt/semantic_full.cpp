
#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

/*** LEXER ***/

enum TokenKind {
    TK_EOF,
    TK_IDENT,
    TK_NUMBER,     // integer or float
    TK_SEMI,       // ;
    TK_LPAREN,     // (
    TK_RPAREN,     // )
    TK_LBRACE,     // {
    TK_RBRACE,     // }
    TK_COMMA,      // ,
    TK_DOT,        // .
    TK_ASSIGN,     // =
    TK_PLUS, TK_MINUS, TK_MUL, TK_DIV, TK_MOD,
    TK_AMP, TK_PIPE, TK_CARET, TK_SHL, TK_SHR,
    TK_LT, TK_GT, TK_LE, TK_GE, TK_EQ, TK_NE,
    TK_KW_STRUCT,
    TK_KW_FOR,
    TK_KW_SHORT, TK_KW_INT, TK_KW_LONG, TK_KW_FLOAT,
    TK_UNKNOWN
};

struct Token {
    TokenKind kind;
    string text;
    int line;
};

struct Lexer {
    string src;
    size_t pos = 0;
    int line = 1;
    Lexer(const string& s) : src(s), pos(0), line(1) {}

    bool starts_with(const string& pat) {
        return src.compare(pos, pat.size(), pat) == 0;
    }

    char peek() {
        if (pos >= src.size()) return '\0';
        return src[pos];
    }
    char getc() {
        if (pos >= src.size()) return '\0';
        char c = src[pos++];
        if (c == '\n') ++line;
        return c;
    }
    void skip_ws() {
        while (true) {
            char c = peek();
            if (c == ' ' || c == '\t' || c == '\r') { getc(); continue; }
            if (c == '\n') { getc(); continue; }
            if (starts_with("//")) {
                while (peek() != '\n' && peek() != '\0') getc();
                continue;
            }
            if (starts_with("/*")) {
                getc(); getc();
                while (!starts_with("*/") && peek() != '\0') getc();
                if (starts_with("*/")) { getc(); getc(); }
                continue;
            }
            break;
        }
    }

    Token next() {
        skip_ws();
        Token t;
        t.line = line;
        char c = peek();
        if (c == '\0') { t.kind = TK_EOF; t.text = ""; return t; }
        // identifiers / keywords
        if (isalpha(c) || c == '_') {
            string id;
            while (isalnum(peek()) || peek() == '_') id.push_back(getc());
            t.text = id;
            if (id == "struct") t.kind = TK_KW_STRUCT;
            else if (id == "for") t.kind = TK_KW_FOR;
            else if (id == "short") t.kind = TK_KW_SHORT;
            else if (id == "int") t.kind = TK_KW_INT;
            else if (id == "long") t.kind = TK_KW_LONG;
            else if (id == "float") t.kind = TK_KW_FLOAT;
            else t.kind = TK_IDENT;
            return t;
        }
        // numbers: support integer decimal and floats with optional exponent (1.23e-4)
        if (isdigit(c) || (c == '.' && isdigit(src[pos + 1]))) {
            string num;
            bool seenDot = false, seenExp = false;
            while (true) {
                char p = peek();
                if (isdigit(p)) { num.push_back(getc()); continue; }
                if (p == '.' && !seenDot) { seenDot = true; num.push_back(getc()); continue; }
                if ((p == 'e' || p == 'E') && !seenExp) {
                    seenExp = true; num.push_back(getc());
                    if (peek() == '+' || peek() == '-') num.push_back(getc());
                    continue;
                }
                break;
            }
            t.kind = TK_NUMBER;
            t.text = num;
            return t;
        }
        // Operators and punctuation (handle multichar)
        // ==, !=, <=, >=, <<, >> 
        if (starts_with("==")) { getc(); getc(); t.kind = TK_EQ; t.text = "=="; return t; }
        if (starts_with("!=")) { getc(); getc(); t.kind = TK_NE; t.text = "!="; return t; }
        if (starts_with("<=")) { getc(); getc(); t.kind = TK_LE; t.text = "<="; return t; }
        if (starts_with(">=")) { getc(); getc(); t.kind = TK_GE; t.text = ">="; return t; }
        if (starts_with("<<")) { getc(); getc(); t.kind = TK_SHL; t.text = "<<"; return t; }
        if (starts_with(">>")) { getc(); getc(); t.kind = TK_SHR; t.text = ">>"; return t; }

        char ch = getc();
        switch (ch) {
        case ';': t.kind = TK_SEMI; t.text = ";"; return t;
        case '(': t.kind = TK_LPAREN; t.text = "("; return t;
        case ')': t.kind = TK_RPAREN; t.text = ")"; return t;
        case '{': t.kind = TK_LBRACE; t.text = "{"; return t;
        case '}': t.kind = TK_RBRACE; t.text = "}"; return t;
        case ',': t.kind = TK_COMMA; t.text = ","; return t;
        case '.': t.kind = TK_DOT; t.text = "."; return t;
        case '+': t.kind = TK_PLUS; t.text = "+"; return t;
        case '-': t.kind = TK_MINUS; t.text = "-"; return t;
        case '*': t.kind = TK_MUL; t.text = "*"; return t;
        case '/': t.kind = TK_DIV; t.text = "/"; return t;
        case '%': t.kind = TK_MOD; t.text = "%"; return t;
        case '&': t.kind = TK_AMP; t.text = "&"; return t;
        case '|': t.kind = TK_PIPE; t.text = "|"; return t;
        case '^': t.kind = TK_CARET; t.text = "^"; return t;
        case '<': t.kind = TK_LT; t.text = "<"; return t;
        case '>': t.kind = TK_GT; t.text = ">"; return t;
        case '=': t.kind = TK_ASSIGN; t.text = "="; return t;
        default: t.kind = TK_UNKNOWN; t.text = string(1, ch); return t;
        }
    }
};

/*** TYPES & SYMBOLS ***/

enum BaseKind { BK_UNDEF, BK_SHORT, BK_INT, BK_LONG, BK_FLOAT, BK_STRUCT };

struct Type {
    BaseKind base;
    string struct_name; // used if base==BK_STRUCT
    Type() : base(BK_UNDEF) {}
    static Type make_builtin(BaseKind b) { Type t; t.base = b; return t; }
    static Type make_struct(const string& name) { Type t; t.base = BK_STRUCT; t.struct_name = name; return t; }
    string toString() const {
        switch (base) {
        case BK_SHORT: return "short";
        case BK_INT: return "int";
        case BK_LONG: return "long";
        case BK_FLOAT: return "float";
        case BK_STRUCT: return "struct " + struct_name;
        default: return "undef";
        }
    }
    bool isInteger() const {
        return base == BK_SHORT || base == BK_INT || base == BK_LONG;
    }
    bool isFloat() const { return base == BK_FLOAT; }
    bool isScalar() const { return isInteger() || isFloat(); }
    bool same(const Type& o) const {
        if (base != o.base) return false;
        if (base == BK_STRUCT) return struct_name == o.struct_name;
        return true;
    }
};

// Symbol kinds
enum SymKind { SK_VAR, SK_STRUCT };

struct Sym {
    string name;
    SymKind kind;
    Type type; // for var: its type; for struct: type.base==BK_STRUCT and name==struct name
    // for struct: fields map
    map<string, Type> fields;
    Sym(string n = "", SymKind k = SK_VAR, Type t = Type()) : name(n), kind(k), type(t) {}
};

/*** SCOPE & SEMANTIC ANALYZER ***/

struct Scope {
    Scope* parent = nullptr;
    vector<unique_ptr<Scope>> children;
    map<string, unique_ptr<Sym>> syms; // symbols declared in this scope
    string name;
    Scope(Scope* p = nullptr, string n = "<scope>") : parent(p), name(n) {}
};

struct Semantic {
    unique_ptr<Scope> global;
    Scope* cur;
    vector<string> errors;
    Semantic() {
        global = make_unique<Scope>(nullptr, "<global>");
        cur = global.get();
    }
    void enterScope() {
        cur->children.push_back(make_unique<Scope>(cur, "<block>"));
        cur = cur->children.back().get();
    }
    void leaveScope() {
        if (cur->parent) cur = cur->parent;
    }
    Sym* findInCurrent(const string& name) {
        auto it = cur->syms.find(name);
        if (it != cur->syms.end()) return it->second.get();
        return nullptr;
    }
    Sym* find(const string& name) {
        Scope* s = cur;
        while (s) {
            auto it = s->syms.find(name);
            if (it != s->syms.end()) return it->second.get();
            s = s->parent;
        }
        return nullptr;
    }
    bool declareVar(const string& name, const Type& ty, int line) {
        if (findInCurrent(name)) {
            errors.push_back(fmt_line(line) + " Duplicate declaration of '" + name + "' in same scope");
            return false;
        }
        auto sym = make_unique<Sym>(name, SK_VAR, ty);
        cur->syms[name] = move(sym);
        return true;
    }
    bool declareStruct(const string& name, const map<string, Type>& fields, int line) {
        if (findInCurrent(name)) {
            errors.push_back(fmt_line(line) + " Duplicate declaration of type '" + name + "'");
            return false;
        }
        Type t = Type::make_struct(name);
        auto s = make_unique<Sym>(name, SK_STRUCT, t);
        s->fields = fields;
        cur->syms[name] = move(s);
        return true;
    }
    string fmt_line(int line) {
        return "Line " + to_string(line) + ":";
    }

    // check usage of identifier (variable)
    Sym* useIdentifier(const string& name, int line) {
        Sym* s = find(name);
        if (!s) {
            errors.push_back(fmt_line(line) + " Use of undeclared identifier '" + name + "'");
            return nullptr;
        }
        return s;
    }

    // check assignment compatibility leftVar = rightType
    void checkAssignment(const string& leftName, const Type& leftType, const Type& rightType, int line) {
        // leftType must be scalar or field; left must be variable or field (checked earlier)
        // rules: integer->float ok; float->integer NOT allowed (error); struct assignment allowed only if same struct
        if (leftType.base == BK_STRUCT || rightType.base == BK_STRUCT) {
            if (!leftType.same(rightType)) {
                errors.push_back(fmt_line(line) + " Incompatible struct types in assignment");
            }
            return;
        }
        if (leftType.isFloat() && rightType.isInteger()) {
            // ok int->float
            return;
        }
        if (leftType.isInteger() && rightType.isFloat()) {
            errors.push_back(fmt_line(line) + " Possible loss of data: assigning float to integer '" + leftName + "'");
            return;
        }
        // otherwise assume ok
    }

    // binary operation type checking and resulting type
    Type checkBinary(const Type& L, const string& op, const Type& R, int line) {
        // bitwise ops allowed only on integers
        if (op == "&" || op == "|" || op == "^" || op == "<<" || op == ">>") {
            if (!L.isInteger() || !R.isInteger()) {
                errors.push_back(fmt_line(line) + " Bitwise operator '" + op + "' applied to non-integer operand");
                return Type::make_builtin(BK_UNDEF);
            }
            // result type is the wider integer: long>int>short
            if (L.base == BK_LONG || R.base == BK_LONG) return Type::make_builtin(BK_LONG);
            if (L.base == BK_INT || R.base == BK_INT) return Type::make_builtin(BK_INT);
            return Type::make_builtin(BK_SHORT);
        }
        // arithmetic: if any float -> float else wider integer
        if (op == "+" || op == "-" || op == "*" || op == "/" || op == "%") {
            if (L.isFloat() || R.isFloat()) return Type::make_builtin(BK_FLOAT);
            if (L.base == BK_LONG || R.base == BK_LONG) return Type::make_builtin(BK_LONG);
            if (L.base == BK_INT || R.base == BK_INT) return Type::make_builtin(BK_INT);
            return Type::make_builtin(BK_SHORT);
        }
        // comparisons: allowed for scalars; result int
        if (op == "<" || op == ">" || op == "<=" || op == ">=" || op == "==" || op == "!=") {
            if (!(L.isScalar() && R.isScalar())) {
                errors.push_back(fmt_line(line) + " Comparison '" + op + "' on non-scalar types");
            }
            return Type::make_builtin(BK_INT);
        }
        return Type::make_builtin(BK_UNDEF);
    }

    // field access: varName.fieldName
    // returns Type of field or BK_UNDEF on error
    Type checkFieldAccess(const string& varName, const string& fieldName, int line) {
        Sym* s = find(varName);
        if (!s) {
            errors.push_back(fmt_line(line) + " Use of undeclared identifier '" + varName + "'");
            return Type::make_builtin(BK_UNDEF);
        }
        if (s->kind != SK_VAR) {
            errors.push_back(fmt_line(line) + " '" + varName + "' is not a variable");
            return Type::make_builtin(BK_UNDEF);
        }
        if (s->type.base != BK_STRUCT) {
            errors.push_back(fmt_line(line) + " Variable '" + varName + "' is not of struct type");
            return Type::make_builtin(BK_UNDEF);
        }
        // find struct definition
        Sym* def = find(s->type.struct_name);
        if (!def || def->kind != SK_STRUCT) {
            errors.push_back(fmt_line(line) + " Struct definition for '" + s->type.struct_name + "' not found");
            return Type::make_builtin(BK_UNDEF);
        }
        auto it = def->fields.find(fieldName);
        if (it == def->fields.end()) {
            errors.push_back(fmt_line(line) + " Struct '" + def->name + "' has no field '" + fieldName + "'");
            return Type::make_builtin(BK_UNDEF);
        }
        return it->second;
    }

    // printing symbol tree
    void print_tree(ostream& out) {
        function<void(Scope*, int)> dfs = [&](Scope* s, int lvl) {
            string indent(lvl * 2, ' ');
            out << indent << s->name << "\n";
            for (auto& p : s->syms) {
                Sym* sym = p.second.get();
                out << indent << "  " << sym->name;
                if (sym->kind == SK_STRUCT) out << " (struct)";
                else out << " (var:" << sym->type.toString() << ")";
                out << "\n";
                if (sym->kind == SK_STRUCT) {
                    for (auto& f : sym->fields) {
                        out << indent << "    " << f.first << " : " << f.second.toString() << "\n";
                    }
                }
            }
            for (auto& c : s->children) dfs(c.get(), lvl + 1);
        };
        dfs(global.get(), 0);
    }
};

/*** PARSER (recursive descent) ***/

// Predeclare
struct Parser {
    Lexer lex;
    Token cur;
    Semantic sem;
    Parser(const string& s) : lex(s) { cur = lex.next(); }

    void next() { cur = lex.next(); }

    bool accept(TokenKind k) {
        if (cur.kind == k) { next(); return true; }
        return false;
    }
    bool expect(TokenKind k, const string& errMsg) {
        if (cur.kind == k) { next(); return true; }
        sem.errors.push_back("Line " + to_string(cur.line) + ": " + errMsg + " (found '" + cur.text + "')");
        return false;
    }

    // parse entry
    void parseTranslationUnit() {
        while (cur.kind != TK_EOF) {
            if (cur.kind == TK_KW_STRUCT) {
                parseStructDeclaration();
            }
            else if (isTypeName(cur.kind) || cur.kind == TK_IDENT) {
                // type could be builtin type or struct type name (identifier)
                // But if identifier followed by '{' it's not declaration; to simplify: try declaration; otherwise statement
                // We'll check: if it is declaration -> type id ; else parse statement
                if (peekIsDecl()) parseDeclaration();
                else parseStatement();
            }
            else {
                parseStatement();
            }
        }
    }

    bool isTypeName(TokenKind k) {
        return k == TK_KW_SHORT || k == TK_KW_INT || k == TK_KW_LONG || k == TK_KW_FLOAT;
    }

    bool peekIsDecl() {
        // if current token is type or identifier and next token is identifier -> declaration
        Token save = cur;
        // if builtin type
        if (isTypeName(cur.kind)) {
            // next should be identifier
            Token nextt = lex.next();
            lex.pos -= nextt.text.size(); // can't reliably roll back lex internal pos; alternative: perform shallow lookahead using saved lexer state — but simpler: assume builtin type indicates declaration.
            // We'll approximate: builtin type => declaration
            return true;
        }
        // if identifier but is a struct type name declared in sem or will be declared? We'll treat identifier followed by identifier as declaration only if next token is identifier.
        // Simpler approach: lookahead by creating a fresh lexer from current position substring
        // We'll implement a lightweight lookahead by copying remaining source starting at lex.pos - cur.text.size()
        // But lex has internal state; simpler: if cur is IDENT and next token is IDENT -> declaration. We'll create a temporary lexer from remainder.
        string rest = lex.src.substr(lex.pos); // remainder after current token
        // build tokenizer for a fake stream: current text + rest
        Lexer tmp(cur.text + rest);
        tmp.line = cur.line;
        tmp.pos = 0;
        Token t1 = tmp.next(); // current token
        Token t2 = tmp.next();
        if (t1.kind == TK_IDENT && t2.kind == TK_IDENT) return true;
        return false;
    }

    // parse struct: 'struct' IDENT '{' field-decls '}' ';'?
    void parseStructDeclaration() {
        int startLine = cur.line;
        expect(TK_KW_STRUCT, "expected 'struct'");
        if (cur.kind != TK_IDENT) {
            sem.errors.push_back("Line " + to_string(cur.line) + ": expected identifier after 'struct'");
            // try to recover
            while (cur.kind != TK_LBRACE && cur.kind != TK_SEMI && cur.kind != TK_EOF) next();
        }
        string name = cur.text;
        if (cur.kind == TK_IDENT) next(); else name = "<anon>";
        if (!expect(TK_LBRACE, "expected '{' after struct name")) {
            // try to continue
        }
        map<string, Type> fields;
        while (cur.kind != TK_RBRACE && cur.kind != TK_EOF) {
            // expect field: type id ;
            Type ft = parseType();
            if (ft.base == BK_UNDEF) {
                // error: unknown type
                sem.errors.push_back("Line " + to_string(cur.line) + ": Unknown field type in struct '" + name + "'");
                // attempt to skip line
                while (cur.kind != TK_SEMI && cur.kind != TK_RBRACE && cur.kind != TK_EOF) next();
                if (cur.kind == TK_SEMI) next();
                continue;
            }
            if (cur.kind != TK_IDENT) {
                sem.errors.push_back("Line " + to_string(cur.line) + ": expected field name in struct '" + name + "'");
                // skip until ;
                while (cur.kind != TK_SEMI && cur.kind != TK_RBRACE && cur.kind != TK_EOF) next();
                if (cur.kind == TK_SEMI) next();
                continue;
            }
            string fname = cur.text; next();
            expect(TK_SEMI, "expected ';' after field declaration");
            if (fields.find(fname) != fields.end()) {
                sem.errors.push_back("Line " + to_string(cur.line) + ": Duplicate field '" + fname + "' in struct '" + name + "'");
            }
            else {
                fields[fname] = ft;
            }
        }
        expect(TK_RBRACE, "expected '}' after struct body");
        // optional semicolon
        if (cur.kind == TK_SEMI) next();
        // declare struct in current scope
        sem.declareStruct(name, fields, startLine);
    }

    Type parseType() {
        int startLine = cur.line;
        if (cur.kind == TK_KW_SHORT) { next(); return Type::make_builtin(BK_SHORT); }
        if (cur.kind == TK_KW_INT) { next(); return Type::make_builtin(BK_INT); }
        if (cur.kind == TK_KW_LONG) { next(); return Type::make_builtin(BK_LONG); }
        if (cur.kind == TK_KW_FLOAT) { next(); return Type::make_builtin(BK_FLOAT); }
        // struct type as identifier: maybe previously declared struct name or user uses it
        if (cur.kind == TK_IDENT) {
            string nm = cur.text;
            // if a struct symbol exists (in any scope), treat as struct type; otherwise we still allow it (maybe forward declaration?)
            Sym* s = sem.find(nm);
            if (s && s->kind == SK_STRUCT) {
                next();
                return Type::make_struct(nm);
            }
            else {
                // still accept identifier as type name (maybe struct declared later) — but we will validate when used in declaration.
                next();
                // mark as struct type using name; semantic check later: ensure struct actually declared when variable declared
                return Type::make_struct(nm);
            }
        }
        return Type(); // undef
    }

    // parse declaration: type id [= expr] ;
    void parseDeclaration() {
        int startLine = cur.line;
        Type ty = parseType();
        if (ty.base == BK_UNDEF) {
            // unknown type handled in parseType
        }
        if (cur.kind != TK_IDENT) {
            sem.errors.push_back("Line " + to_string(cur.line) + ": expected identifier in declaration");
            // attempt to skip to next semicolon
            while (cur.kind != TK_SEMI && cur.kind != TK_EOF) next();
            if (cur.kind == TK_SEMI) next();
            return;
        }
        string name = cur.text; next();
        // optional initializer: = expr
        if (accept(TK_ASSIGN)) {
            // parse expression to determine type
            Type rtype = parseExpression();
            sem.checkAssignment(name, ty, rtype, startLine);
        }
        expect(TK_SEMI, "expected ';' after declaration");
        // Now actually declare variable; but check: if ty is struct name but no struct declared -> error
        if (ty.base == BK_STRUCT) {
            Sym* def = sem.find(ty.struct_name);
            if (!def || def->kind != SK_STRUCT) {
                sem.errors.push_back("Line " + to_string(startLine) + ": use of unknown struct type '" + ty.struct_name + "'");
                // Still declare variable with that struct name (to allow later checks)
                sem.declareVar(name, ty, startLine);
            }
            else {
                sem.declareVar(name, ty, startLine);
            }
        }
        else {
            sem.declareVar(name, ty, startLine);
        }
    }

    // Statement parsing
    void parseStatement() {
        if (accept(TK_SEMI)) {
            // empty statement
            return;
        }
        else if (accept(TK_LBRACE)) {
            sem.enterScope();
            while (!accept(TK_RBRACE) && cur.kind != TK_EOF) parseStatement();
            sem.leaveScope();
            return;
        }
        else if (cur.kind == TK_KW_FOR) {
            parseFor();
            return;
        }
        else {
            // expression statement or declaration disguised
            // We attempt to parse assignment or expr; if starts with type -> declaration
            if (isTypeName(cur.kind) || (cur.kind == TK_IDENT && maybeTypeName(cur.text))) {
                // Could be declaration or expression. Use lookahead: if pattern type ident ... ;
                // We will check: if next token after type is identifier and next after that is ';' or '=' -> declaration
                Token ttype = cur;
                if (isTypeName(cur.kind)) {
                    // declaration
                    parseDeclaration();
                    return;
                }
                else {
                    // identifier case: if identifier is a type (declared struct), parse declaration
                    Sym* s = sem.find(cur.text);
                    if (s && s->kind == SK_STRUCT) {
                        // Treat as declaration
                        parseDeclaration();
                        return;
                    }
                }
            }
            // Otherwise parse expression and expect semicolon
            Type t = parseExpression();
            expect(TK_SEMI, "expected ';' after statement");
            // If it's an assignment expression like a = ... we would have handled semantic checks in parseExpression
            return;
        }
    }

    bool maybeTypeName(const string& name) {
        Sym* s = sem.find(name);
        return s && s->kind == SK_STRUCT;
    }

    void parseFor() {
        int startLine = cur.line;
        expect(TK_KW_FOR, "expected 'for'");
        expect(TK_LPAREN, "expected '(' after for");
        // for(init; cond; update)
        // init: could be declaration or expression or empty
        if (cur.kind == TK_SEMI) { next(); }
        else {
            // if declaration
            if (isTypeName(cur.kind) || (cur.kind == TK_IDENT && maybeTypeName(cur.text))) {
                parseDeclaration(); // will eat trailing ;
            }
            else {
                // expression statement terminated by ;
                Type t = parseExpression();
                expect(TK_SEMI, "expected ';' in for-init");
            }
        }
        // condition: expression or empty
        if (cur.kind == TK_SEMI) { next(); }
        else {
            Type cond = parseExpression();
            // cond should be scalar
            if (!cond.isScalar()) sem.errors.push_back("Line " + to_string(cur.line) + ": for condition must be scalar type");
            expect(TK_SEMI, "expected ';' after for-condition");
        }
        // update: expression or empty
        if (cur.kind == TK_RPAREN) { next(); }
        else {
            Type upd = parseExpression();
            expect(TK_RPAREN, "expected ')' after for update");
        }
        // statement
        sem.enterScope(); // variables declared in for are in inner scope
        parseStatement();
        sem.leaveScope();
    }

    // Expression parser with precedence climbing
    // We'll implement recursive descent with functions for levels

    Type parseExpression() { return parseAssign(); }

    Type parseAssign() {
        // parse left (could be lvalue) and if '=' then assignment
        // implement right-associative assignment
        Type left = parseOr();
        if (cur.kind == TK_ASSIGN) {
            int line = cur.line;
            // Need to ensure left is l-value: either identifier or field access
            // But parseOr returned a type; we need to know if it was lvalue. To achieve that, we'll track last lvalue via a helper when parsing primary nodes: set lastLValue = pair(name, optional field)
            // For simplicity, we will redo: we will parse a special path: if next token after primary is '=', then we treat it as assignment form
            // To simplify, if current token is '=', we assume previous token was ident or field: we extract last token text from lexer's last; but we can't. Alternative: implement assignment by peeking: if the expression starts with ident (or ident.ident) and next token is '=', parse as assignment specially.
            // So here, to be robust, we will not support complex l-value expressions on left (like a+b = ...). Our parser ensured earlier that assignment will be parsed as statement when appropriate (we parse assignment when seeing identifier then '=') — but to keep working, if we reach here and see '=', we treat it as error. For now, we will not handle nested assignment here.
            // However, to support assignment properly, we implement: if left was parsed by parsePrimary as an lvalue, we stored details in lastLValueName and lastLValueField.
            // So we keep state variables for last lvalue.
        }
        return left;
    }

    // We'll implement assignment handling at the level of parseOr by looking ahead: if current token is IDENT and next token is '=' or '.' then handle accordingly.
    Type parseOr() { return parseBitwise(); }

    Type parseBitwise() {
        Type t = parseShift();
        while (cur.kind == TK_AMP || cur.kind == TK_PIPE || cur.kind == TK_CARET) {
            string op = cur.text; next();
            Type r = parseShift();
            t = sem.checkBinary(t, op, r, cur.line);
        }
        return t;
    }

    Type parseShift() {
        Type t = parseAdd();
        while (cur.kind == TK_SHL || cur.kind == TK_SHR) {
            string op = cur.text; next();
            Type r = parseAdd();
            t = sem.checkBinary(t, op, r, cur.line);
        }
        return t;
    }

    Type parseAdd() {
        Type t = parseMul();
        while (cur.kind == TK_PLUS || cur.kind == TK_MINUS) {
            string op = cur.text; next();
            Type r = parseMul();
            t = sem.checkBinary(t, op, r, cur.line);
        }
        return t;
    }

    Type parseMul() {
        Type t = parseUnary();
        while (cur.kind == TK_MUL || cur.kind == TK_DIV || cur.kind == TK_MOD) {
            string op = cur.text; next();
            Type r = parseUnary();
            t = sem.checkBinary(t, op, r, cur.line);
        }
        return t;
    }

    Type parseUnary() {
        if (cur.kind == TK_PLUS) { next(); return parseUnary(); }
        if (cur.kind == TK_MINUS) { next(); return parseUnary(); }
        return parseRelational();
    }

    Type parseRelational() {
        Type t = parsePrimaryOrAssignment();
        while (cur.kind == TK_LT || cur.kind == TK_GT || cur.kind == TK_LE || cur.kind == TK_GE || cur.kind == TK_EQ || cur.kind == TK_NE) {
            string op = cur.text; next();
            Type r = parsePrimaryOrAssignment();
            t = sem.checkBinary(t, op, r, cur.line);
        }
        return t;
    }

    // Primary and also check for assignment when pattern IDENT '=' ...
    // We implement detection: if current token is IDENT and next token is '=' => assignment.
    // For field access we support chain ident(.ident)*
    Type parsePrimaryOrAssignment() {
        // assignment detection
        if (cur.kind == TK_IDENT) {
            // build identifier chain like a.b.c
            vector<string> chain;
            chain.push_back(cur.text);
            next();
            while (accept(TK_DOT)) {
                if (cur.kind != TK_IDENT) {
                    sem.errors.push_back("Line " + to_string(cur.line) + ": expected field name after '.'");
                    break;
                }
                chain.push_back(cur.text);
                next();
            }
            // if next token is '=' -> assignment to this lvalue
            if (cur.kind == TK_ASSIGN) {
                int line = cur.line;
                next(); // consume =
                Type rtype = parseExpression();
                // resolve left lvalue type: if chain length 1 => variable; if >1 => field access
                if (chain.size() == 1) {
                    string var = chain[0];
                    Sym* s = sem.find(var);
                    if (!s) {
                        sem.errors.push_back("Line " + to_string(line) + ": Left side of assignment: undeclared identifier '" + var + "'");
                    }
                    else if (s->kind != SK_VAR) {
                        sem.errors.push_back("Line " + to_string(line) + ": Left side of assignment is not a variable: '" + var + "'");
                    }
                    else {
                        sem.checkAssignment(var, s->type, rtype, line);
                    }
                    return rtype; // assignment expression value type: right type (not used)
                }
                else {
                    // field chain: first must be variable of struct, and traverse fields
                    string var = chain[0];
                    Sym* s = sem.find(var);
                    if (!s) {
                        sem.errors.push_back("Line " + to_string(line) + ": Left side of assignment: undeclared identifier '" + var + "'");
                        return rtype;
                    }
                    Type curtype = s->type;
                    for (size_t i = 1; i < chain.size(); ++i) {
                        string fld = chain[i];
                        if (curtype.base != BK_STRUCT) {
                            sem.errors.push_back("Line " + to_string(line) + ": '" + chain[i - 1] + "' is not a struct when accessing field '" + fld + "'");
                            curtype = Type::make_builtin(BK_UNDEF); break;
                        }
                        Sym* def = sem.find(curtype.struct_name);
                        if (!def || def->kind != SK_STRUCT) {
                            sem.errors.push_back("Line " + to_string(line) + ": Struct definition '" + curtype.struct_name + "' not found");
                            curtype = Type::make_builtin(BK_UNDEF); break;
                        }
                        auto it = def->fields.find(fld);
                        if (it == def->fields.end()) {
                            sem.errors.push_back("Line " + to_string(line) + ": Struct '" + def->name + "' has no field '" + fld + "'");
                            curtype = Type::make_builtin(BK_UNDEF); break;
                        }
                        curtype = it->second;
                    }
                    // now curtype is type of final field
                    // assignment compatibility between curtype (left) and rtype
                    sem.checkAssignment(chain.back(), curtype, rtype, line);
                    return rtype;
                }
            }
            else {
                // not an assignment: evaluate type of expression chain (field access)
                Type t = Type::make_builtin(BK_UNDEF);
                if (chain.size() == 1) {
                    Sym* s = sem.find(chain[0]);
                    if (!s) {
                        sem.errors.push_back("Line " + to_string(cur.line) + ": Use of undeclared identifier '" + chain[0] + "'");
                        return t;
                    }
                    t = s->type;
                    return t;
                }
                else {
                    // field access chain
                    Sym* s = sem.find(chain[0]);
                    if (!s) {
                        sem.errors.push_back("Line " + to_string(cur.line) + ": Use of undeclared identifier '" + chain[0] + "'");
                        return t;
                    }
                    Type curtype = s->type;
                    for (size_t i = 1; i < chain.size(); ++i) {
                        string fld = chain[i];
                        if (curtype.base != BK_STRUCT) {
                            sem.errors.push_back("Line " + to_string(cur.line) + ": '" + chain[i - 1] + "' is not a struct when accessing field '" + fld + "'");
                            return Type::make_builtin(BK_UNDEF);
                        }
                        Sym* def = sem.find(curtype.struct_name);
                        if (!def || def->kind != SK_STRUCT) {
                            sem.errors.push_back("Line " + to_string(cur.line) + ": Struct definition '" + curtype.struct_name + "' not found");
                            return Type::make_builtin(BK_UNDEF);
                        }
                        auto it = def->fields.find(fld);
                        if (it == def->fields.end()) {
                            sem.errors.push_back("Line " + to_string(cur.line) + ": Struct '" + def->name + "' has no field '" + fld + "'");
                            return Type::make_builtin(BK_UNDEF);
                        }
                        curtype = it->second;
                    }
                    return curtype;
                }
            }
        }

        // parenthesized expression
        if (accept(TK_LPAREN)) {
            Type t = parseExpression();
            expect(TK_RPAREN, "expected ')'");
            return t;
        }

        // number literal
        if (cur.kind == TK_NUMBER) {
            string s = cur.text;
            next();
            // decide float or int: presence of '.' or 'e' or 'E' => float, else int
            if (s.find('.') != string::npos || s.find('e') != string::npos || s.find('E') != string::npos)
                return Type::make_builtin(BK_FLOAT);
            else return Type::make_builtin(BK_INT);
        }

        // unknown primary
        sem.errors.push_back("Line " + to_string(cur.line) + ": Unexpected token '" + cur.text + "' in expression");
        next();
        return Type::make_builtin(BK_UNDEF);
    }
};

/*** MAIN ***/

int main(int argc, char** argv) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <source_file>\n";
        return 1;
    }
    string path = argv[1];
    ifstream in(path);
    if (!in) { cerr << "Cannot open file: " << path << "\n"; return 1; }
    string src((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());

    Parser parser(src);
    parser.parseTranslationUnit();

    cout << "--- Semantic Tree ---\n";
    parser.sem.print_tree(cout);
    cout << "\n--- Errors ---\n";
    if (parser.sem.errors.empty()) cout << "No semantic errors.\n";
    else {
        for (auto& e : parser.sem.errors) cout << e << "\n";
    }
    return 0;
}
