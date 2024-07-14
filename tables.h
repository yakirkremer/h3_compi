//
// Created by yakir on 7/14/2024.
//

#ifndef HW3_TABLES_H
#define HW3_TABLES_H
#include "types.h"



class Symbol {
    string name;
    string type;
    int offset;

public:
    Symbol(const string name, const string type, int offset) : name(name), type(type), offset(offset) {}
    string get_name() const { return name; }

};

class SymbolTable {
    vector<Symbol *> symbols;
    int offset;
    int max_offset;
    bool is_loop;
    string *return_type;

public:
    Symbol* get_symbol(int index) const { return symbols[index]; }
    int get_size() const { return symbols.size(); }
    SymbolTable(int offset, bool is_loop, string return_type = "")
            :max_offset(offset), is_loop(is_loop),offset(offset) {
        this->return_type = new string(return_type);
        this->symbols = vector<Symbol *>();
        if(CHECK)
            cout << "SymbolTable created with offset " << offset << " and is_loop " << is_loop << " and return_type " << return_type << endl;
    }

    void add_symbol(string name, string type, int offset);

    bool symbol_exists(const string &name);

    Symbol *get_symbol(const string &name);

    ~SymbolTable() {
        delete return_type;
        for (auto it = symbols.begin(); it != symbols.end(); it++)
            delete (*it);
    }
};





#endif //HW3_TABLES_H
