//
// Created by yakir on 7/14/2024.
//

#ifndef HW3_TYPES_H
#define HW3_TYPES_H

#include <string>
#include <vector>
#include <iostream>

using namespace std;

#define CHECK false

class Node;
#define YYSTYPE Node*
#define TYPE 0
#define DECL 1
#define EXP 2



class Node {
public:
    //vector<string> names;
    string name;

    Node(const string name = "") : name(name) {};
    Node(const Node* node): name(node->name){};

    virtual ~Node() = default;
};

class Type : public Node {
public:
    string type;

    Type(const string type):  type(type){
    };
    virtual ~Type() = default;
};

class ExpNum : public Type {
public:
    ExpNum(): Type("int"){};
};
class ExpNumB : public Type {
public:
    ExpNumB(): Type("byte"){};
};
class ExpBool : public Type {
public:
    ExpBool(): Type("bool"){};
};

class ExpStr : public Type {
public:
    ExpStr(): Type("string"){};
};

class Call : public Type {
public:
    Call(string type,string name, string var_type): Type(type){};

};

class Decl : public Node {
public:
    string type;
    Decl(Node * type, Node * name):Node(name), type(dynamic_cast<Type*>(type)->type){
    };
    virtual ~Decl() = default;

};



Node* makeNode(int node_type,const string type, const string value);

#endif //HW3_TYPES_H
