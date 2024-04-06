//
// Created by User on 5/23/2022.
//

#ifndef SYMBOL_TABLE_1805022_SYMBOLINFO_H
#define SYMBOL_TABLE_1805022_SYMBOLINFO_H

#include<bits/stdc++.h>
using namespace std;

class SymbolInfo {

    string name;
    string type;
    SymbolInfo* next = nullptr;

public:
    SymbolInfo();

    SymbolInfo(const string &name, const string &type);

    ~SymbolInfo();

    const string &getName() const;

    void setName(const string &name);

    const string &getType() const;

    void setType(const string &type);

    SymbolInfo *getNext() const;

    void setNext(SymbolInfo *next);


};


#endif //SYMBOL_TABLE_1805022_SYMBOLINFO_H
