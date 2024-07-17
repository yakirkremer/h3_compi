//
// Created by yakir on 7/14/2024.
//

#include "tables.h"


void print_table(SymbolTable *table) {
    for (int i = 0; i < table->get_size(); i++) {
            cout << "Symbol " << table->get_symbol(i)->get_name()  << std::endl;
    }
}

bool SymbolTable::add_symbol(string name, string type,int size, bool is_function = false, vector<string> types = {}) {
    if(symbol_exists(name)){
        return false;
    }
    if(CHECK)
        cout << "Adding symbol " << name << " of type " << type << " with offset " << offset << std::endl;
    symbols.push_back(new Symbol(name, type, size, is_function));
    if (size >= 0)
        max_offset = size;
    this->offset+=size;
    if(CHECK)
        print_table(this);
    return true;
}

bool SymbolTable::symbol_exists(const std::string &name) {
    if(CHECK)
        //cout << "Checking if symbol " << name << " exists" << endl;
    for(int i = 0; i < symbols.size(); i++){
        //cout << "Checking symbol " << symbols[i]->get_name()<<"out of"<<symbols.size() << endl;
       if(symbols[i]->get_name() == name) {
           return true;
       }
    }
    if(CHECK)
        //cout << "Symbol " << name << " does not exist" << endl;
    return false;
}

Symbol * SymbolTable::get_symbol(const string & name){
    //cout << "Getting symbol " << name << endl;
    for(int i = symbols.size()-1; i >= 0; i--) {
        //cout << "Checking symbol " << symbols[i]->get_name() << endl;
        if (symbols[i]->get_name() == name)
            return symbols[i];
    }
    //cout << "Symbol " << name << " does not exist" << endl;
    return nullptr;
}

bool Scopes::symbol_exists(const string &name) {
    for(int i = table_scopes.size()-1; i >= 0; i--){
        //cout << "Checking scope " << table_scopes[i]->offset << endl;
        if(table_scopes[i]->symbol_exists(name)){
            return true;
        }
    }

    return false;
}

bool Scopes::add_symbol(const string &name, const string &type, int offset, vector <string> arg_types,bool is_function) {
    if(scope->symbol_exists(name)){
        return false;
    }
    scope->add_symbol(name, type, offset, is_function, arg_types);
    return true;
}

Symbol *Scopes::get_symbol(const string &name) {
    //cout << "Getting symbol " << name << endl;
    for(int i = table_scopes.size()-1; i >= 0; i--){
        //cout << "Checking scope " << table_scopes[i]->offset << endl;
        Symbol *symbol = table_scopes[i]->get_symbol(name);
        if(symbol != nullptr)
            return symbol;
    }
    //cout << "Symbol " << name << " does not exist" << endl;
    return nullptr;
}

Scopes::Scopes(): table_scopes(), offsets(), scope(nullptr) {
    //cout << "Creating new scope" << endl;
    this->table_scopes.push_back(new SymbolTable(0));
    this->scope = table_scopes.back();
    this->offsets.push_back(0);
}

void print_scopes(vector<SymbolTable *> scopes) {
    for (int i = 0; i < scopes.size(); i++) {
        cout << "Scope " << i << std::endl;
        print_table(scopes[i]);
    }
}

void Scopes::open_scope() {
    ////cout<<"printing scopes before open new:  "; print_scopes(table_scopes);
    ////cout<<endl;
    table_scopes.push_back(new SymbolTable(offsets.back()));
    scope = table_scopes.back();
    offsets.push_back(offsets.back());
}

void Scopes::close_scope() {
    ////cout<<"printing scopes before close:  "; print_scopes(table_scopes);
    ////cout<<endl;
    SymbolTable *last = table_scopes.back();
    table_scopes.pop_back();
    delete last;
    offsets.pop_back();
    scope = table_scopes.back();
}


