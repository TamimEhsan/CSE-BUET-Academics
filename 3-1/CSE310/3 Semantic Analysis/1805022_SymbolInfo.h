//
// Created by User on 5/23/2022.
//

#ifndef SYMBOL_TABLE_1805022_SYMBOLINFO_H
#define SYMBOL_TABLE_1805022_SYMBOLINFO_H

#include<bits/stdc++.h>
//#include "1805022_Function.h"

using namespace std;

class SymbolInfo  {

    string name;
    string type;
    string typeSpecifier;
    bool functionDefinition = false;
    bool functionDeclaration = false;
    bool array = false;
    int size = 0;
    SymbolInfo* next = nullptr;
    vector<SymbolInfo*> declaration_list;
    vector<SymbolInfo*> parameter_list;



public:
    SymbolInfo();

    SymbolInfo(SymbolInfo* symbolInfo);

    SymbolInfo(SymbolInfo &symbolInfo);

    SymbolInfo(const string &name, const string &type);

    SymbolInfo(const string &name, const string &type, const string &typeSpecifier);

    SymbolInfo(const string &name, const string &type, const string &typeSpecifier, int size);


    ~SymbolInfo();

    const string &getName() const;

    void setName(const string &name);

    const string &getType() const;

    void setType(const string &type);

    const string &getTypeSpecifier() const;

    void setTypeSpecifier(const string &typeSpecifier);

    int getSize() const;

    void setSize(int size);

    SymbolInfo *getNext() const;

    void setNext(SymbolInfo *next);

    void pushDeclaration(SymbolInfo* symbolInfo);

    vector<SymbolInfo*> getDeclarationList();

    void setDeclarationList(vector<SymbolInfo*> symbolInfos);

    bool isFunctionDefinition() const;

    void setFunctionDefinition(bool functionDefinition);

    bool isFunctionDeclaration() const;

    void setFunctionDeclaration(bool functionDeclaration);

    bool isArray() const;

    void setArray(bool array);

    const vector<SymbolInfo *> &getParameterList() const;

    void setParameterList(const vector<SymbolInfo *> &parameterList);

    void pushParameter(SymbolInfo* symbolInfo);
};


#endif //SYMBOL_TABLE_1805022_SYMBOLINFO_H
