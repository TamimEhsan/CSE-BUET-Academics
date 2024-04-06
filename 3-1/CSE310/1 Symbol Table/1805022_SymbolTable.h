//
// Created by User on 5/24/2022.
//

#ifndef SYMBOL_TABLE_1805022_SYMBOLTABLE_H
#define SYMBOL_TABLE_1805022_SYMBOLTABLE_H

#include "1805022_ScopeTable.h"

class SymbolTable {
    ScopeTable* currentScopeTable;
    int bucketSize = 2;

public:
    SymbolTable(int bucketSize);

    ~SymbolTable();

    ScopeTable *getCurrentScopeTable() const;

    void setCurrentScopeTable(ScopeTable *currentScopeTable);

    int getBucketSize() const;

    void setBucketSize(int bucketSize);

    void enterScope();

    void exitScope();

    bool insertSymbol(SymbolInfo symbolInfo);

    bool removeSymbol(string key);

    SymbolInfo* lookUpSymbol(string key);

    void printCurrentScopeTable();

    void printAllScopeTable();
};


#endif //SYMBOL_TABLE_1805022_SYMBOLTABLE_H
