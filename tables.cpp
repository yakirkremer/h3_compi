//
// Created by yakir on 7/14/2024.
//

#include "tables.h"


void print_table(SymbolTable *table) {
    for (int i = 0; i < table->get_size(); i++) {
            cout << "Symbol " << table->get_symbol(i)->get_name()  << std::endl;
    }
}

bool SymbolTable::add_symbol(string name, string type,int size, bool is_function = false, string arg_type = "") {
    if(symbol_exists(name)){
        return false;
    }

    symbols.push_back(new Symbol(name, type, max_offset, is_function,arg_type));
    max_offset += size;

    return true;
}

bool SymbolTable::symbol_exists(const std::string &name) {

    for(int i = 0; i < symbols.size(); i++){
       if(symbols[i]->get_name() == name) {
           return true;
       }
    }
    return false;
}

Symbol * SymbolTable::get_symbol(const string & name){
    for(int i = symbols.size()-1; i >= 0; i--) {
        if (symbols[i]->get_name() == name)
            return symbols[i];
    }
    return nullptr;
}

bool Scopes::symbol_exists(const string &name) {
    for(int i = table_scopes.size()-1; i >= 0; i--){
        if(table_scopes[i]->symbol_exists(name)){
            return true;
        }
    }

    return false;
}

bool Scopes::add_symbol(const string &name, const string &type, int size, string arg_type,bool is_function) {
    if(scope->symbol_exists(name)){
        return false;
    }
    scope->add_symbol(name, type, size, is_function, arg_type);
    //scope->max_offset += size;
    return true;
}

Symbol *Scopes::get_symbol(const string &name) {
    for(int i = table_scopes.size()-1; i >= 0; i--){
        Symbol *symbol = table_scopes[i]->get_symbol(name);
        if(symbol != nullptr)
            return symbol;
    }
    return nullptr;
}

Scopes::Scopes(): table_scopes(), offsets(), scope(nullptr) {
    offsets.push_back(0);
    table_scopes.push_back(new SymbolTable(offsets.back()));
    scope = table_scopes.back();
    //this->table_scopes.push_back(new SymbolTable(0));
    //this->scope = table_scopes.back();
    //this->offsets.push_back(0);
}

void print_scopes(vector<SymbolTable *> scopes) {
    for (int i = 0; i < scopes.size(); i++) {
        cout << "Scope " << i << std::endl;
        print_table(scopes[i]);
    }
}

void Scopes::open_scope() {
    offsets.push_back(scope->max_offset);
    table_scopes.push_back(new SymbolTable(offsets.back()));
    scope = table_scopes.back();
}

void Scopes::close_scope() {
    SymbolTable *last = table_scopes.back();
    table_scopes.pop_back();
    delete last;

    scope = table_scopes.back();
    scope->max_offset = offsets.back();
    offsets.pop_back();

}

bool Scopes::in_loop() {
    return scope->is_loop;
}


