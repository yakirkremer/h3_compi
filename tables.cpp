//
// Created by yakir on 7/14/2024.
//

#include "tables.h"

void print_table(SymbolTable *table) {
    for (int i = 0; i < table->get_size(); i++) {
            std::cout << "Symbol " << table->get_symbol(i)->get_name()  << std::endl;
    }
}

bool SymbolTable::add_symbol(string name, string type, int size, bool is_function = false) {
    if(symbol_exists(name)){
        return false;
    }
    if(CHECK)
        std::cout << "Adding symbol " << name << " of type " << type << " with offset " << offset << std::endl;
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

Symbol * SymbolTable::get_symbol(const string & name){
    for (auto it = symbols.begin(); it != symbols.end(); ++it) {
        if ((*it)->get_name() == name)
            return (*it);
    }
    return nullptr;
}

Call * CreateCall(Node * func, Node * var, SymbolTable *table){
    string name = func->name;
    string var_type = dynamic_cast<Type*>(var)->type;
    if(table->symbol_exists(name) == false){
        return nullptr;
    }
    string type = table->get_symbol(name)->get_type();
    if(name == "print" && var_type == "string"){
        return new Call(type, name, var_type);
    }
    if(name == "printi" && var_type == "int"){
        return new Call(type, name, var_type);
    }
    if(name == "printi" && var_type == "byte"){
        return new Call(type, name, var_type);
    }
    if(name == "readi" && var_type == "int"){
        return new Call(type, name, var_type);
    }
    if(name == "readi" && var_type == "byte"){
        return new Call(type, name, var_type);
    }
    return nullptr;
};

Node * CreateExp(string name, SymbolTable *table){
    if(table->symbol_exists(name) == false){
        return nullptr;
    }
    string type = table->get_symbol(name)->get_type();
    if(type == "int"){
        return new ExpNum();
    }
    if(type == "byte"){
        return new ExpNumB();
    }
    if(type == "bool"){
        return new ExpBool();
    }
    if(type == "string"){
        return new ExpStr();
    }
    return nullptr;
}

bool assign(Node * exp, Node * id, SymbolTable* symbolTable){
    if(symbolTable->symbol_exists(id->name) == false){
        return false;
    }
    string type_dst = symbolTable->get_symbol(id->name)->get_type();
    string type_src = dynamic_cast<Decl*>(exp)->type;

    if(type_src == "int" && type_dst == "byte"){
        return true;
    }
    if(type_src == type_dst ){
        return true;
    }
    return false;
}

