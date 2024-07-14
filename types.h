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
    string value;

    Node(const string value = "") : value(value) {
    };
    Node(const Node &node): value(node.value){
    };
    virtual ~Node() = default;
};

class Type : public Node {
public:
    string type;

    Type(const string type):  type(type){
    };
    virtual ~Type() = default;
};

class Decl : public Node {
public:
    string type;

    Decl(const Type * type,const Node * node){
    if(CHECK)
        std::cout << "Decl " << type->type << " " << node->value << std::endl;
    };
    virtual ~Decl() = default;
};

class Exp: public Node {
public:
    string type;

    Exp(const string type,  Node * node): node(node),type(type){};
    virtual ~Exp() = default;
};

class Statement: public Node {
    Statement(Type *type, Node *id);
};

Node* makeNode(int node_type,const string type, const string value);

#endif //HW3_TYPES_H
