//
// Created by yakir on 7/14/2024.
//

#include "tables.h"

void print_table(SymbolTable *table) {
    for (int i = 0; i < table->get_size(); i++) {
            std::cout << "Symbol " << table->get_symbol(i)->get_name()  << std::endl;
    }
}

void SymbolTable::add_symbol(string name, string type, int offset) {
    if(CHECK)
        std::cout << "Adding symbol " << name << " of type " << type << " with offset " << offset << std::endl;
    symbols.push_back(new Symbol(name, type, offset));
    if (offset >= 0)
        max_offset = offset;
    offset+=offset;
    if(CHECK)
        print_table(this);
}

bool SymbolTable::symbol_exists(const std::string &name) {
    if(CHECK)
        cout << "Checking if symbol " << name << " exists" << endl;
    for (int i = 0; i < symbols.size(); i++) {
        if (symbols[i]->get_name() == name){
            if(CHECK)
                cout << "Symbol " << name << " exists" << endl;
            return true;
        }
    }
    if(CHECK)
        cout << "Symbol " << name << " does not exist" << endl;
    return false;
}

