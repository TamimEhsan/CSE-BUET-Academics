//
// Created by User on 5/24/2022.
//

#ifndef SYMBOL_TABLE_1805022_SCOPETABLE_H
#define SYMBOL_TABLE_1805022_SCOPETABLE_H

#include "1805022_SymbolInfo.h"

class ScopeTable {
    ScopeTable* parentScope = nullptr;
    string uid = "1";
    int childCounter = 0;
    int bucketSize = 2;
    SymbolInfo** hashTable;
public:
    ScopeTable(int bucketSize);

    ~ScopeTable();

    ScopeTable *getParentScope() const;

    void setParentScope(ScopeTable *parentScope);

    string getUid() const;

    void setUid(string uid);

    int getChildCounter() const;

    void setChildCounter(int childCounter);

    int getBucketSize() const;

    void setBucketSize(int bucketSize);

    SymbolInfo **getHashTable() const;

    void setHashTable(SymbolInfo **hashTable);

    unsigned long getHash(string str);

    bool insertSymbol(SymbolInfo symbolInfo);

    SymbolInfo* lookUpSymbol(string key);

    bool deleteSymbol(string key);

    void printScopeTable(ofstream &out);


};


#endif //SYMBOL_TABLE_1805022_SCOPETABLE_H
