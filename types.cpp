//
// Created by yakir on 7/14/2024.
//

#include "types.h"

Node *makeNode(int node_type,const string value,  const string type) {
    switch (node_type) {
        case DECL:
            return new Decl(new Type(type),new Node(value));
        case TYPE:
            return new Type(type);
        case EXP:
            return new Exp(type, value);
        default:
            return nullptr;
    }
}

Statement::Statement(Type *type, Node *id) : Node() {

        std::cout << "Statement Type ID: " << type->type << " " << id->value << std::endl;
    value = type->value;

}

/*
Program: Statements                         {printProductionRule(1);}
Statements: Statement                       {printProductionRule(2);}
Statements: Statements Statement            {printProductionRule(3);}
Statement: LBRACE Statements RBRACE         {printProductionRule(4);}
Statement: Type ID SC                       {printProductionRule(5);}
Statement: Type ID ASSIGN Exp SC            {printProductionRule(6);}
Statement: ID ASSIGN Exp SC                 {printProductionRule(7);}
Statement: Call SC                          {printProductionRule(8);}
Statement: RETURN SC                        {printProductionRule(9);}
Statement: IF LPAREN Exp RPAREN Statement   {printProductionRule(10);}
Statement: IF LPAREN Exp RPAREN Statement ELSE Statement    {printProductionRule(11);}
Statement: WHILE LPAREN Exp RPAREN Statement    {printProductionRule(12);}
Statement: BREAK SC                         {printProductionRule(13);}
Statement: CONTINUE SC                      {printProductionRule(14);}
Call: ID LPAREN Exp RPAREN                  {printProductionRule(15);}
Type: INT                                   {printProductionRule(16);}
Type: BYTE                                  {printProductionRule(17);}
Type: BOOL                                  {printProductionRule(18);}
Exp: LPAREN Exp RPAREN                      {cout<<"the expression value is"<<$1->value<<endl; printProductionRule(19);}
Exp: Exp MULTIPLICATIVE Exp                 {printProductionRule(20);}
Exp: Exp ADDITIVE Exp                       {printProductionRule(20);}
Exp: ID                                     {printProductionRule(21);}
Exp: Call                                   {printProductionRule(22);}
Exp: NUM                                    {$$ = new Exp($1, "num");}
Exp: NUM B                                  {printProductionRule(24);}
Exp: STRING                                 {printProductionRule(25);}
Exp: TRUE                                   {printProductionRule(26);}
Exp: FALSE                                  {printProductionRule(27);}
Exp: NOT Exp                                {printProductionRule(28);}
Exp: Exp AND Exp                            {printProductionRule(29);}
Exp: Exp OR Exp                             {printProductionRule(30);}
Exp: Exp RELOP Exp                          {printProductionRule(31);}
Exp: Exp EQUALITY Exp                       {printProductionRule(31);}
Exp: LPAREN Type RPAREN Exp                 {printProductionRule(32);}
 */