//
// Created by User on 5/24/2022.
//

#include "1805022_SymbolTable.h"

SymbolTable::SymbolTable(int bucketSize) : bucketSize(bucketSize) {
    currentScopeTable = new ScopeTable(bucketSize);
   // cout<<"bbb"<<endl<<endl;
}

ScopeTable *SymbolTable::getCurrentScopeTable() const {
    return currentScopeTable;
}

void SymbolTable::setCurrentScopeTable(ScopeTable *currentScopeTable) {
    SymbolTable::currentScopeTable = currentScopeTable;
}

int SymbolTable::getBucketSize() const {
    return bucketSize;
}

void SymbolTable::setBucketSize(int bucketSize) {
    SymbolTable::bucketSize = bucketSize;
}

SymbolTable::~SymbolTable() {
    while(currentScopeTable != nullptr)
    {
        ScopeTable* parent = currentScopeTable->getParentScope();
        delete currentScopeTable;
        currentScopeTable = parent;
    }
}

void SymbolTable::enterScope() {
    ScopeTable *scopeTable = new ScopeTable(bucketSize);
    scopeTable->setParentScope(currentScopeTable);
    currentScopeTable = scopeTable;
    if( currentScopeTable->getParentScope()!= nullptr ){
       // cout<<"has parent "<<endl<<endl;
        int siblings = currentScopeTable->getParentScope()->getChildCounter();
        currentScopeTable->getParentScope()->setChildCounter(siblings+1);
        siblings++;
        currentScopeTable->setUid(currentScopeTable->getParentScope()->getUid()+"."+to_string(siblings));
    }
    cout<<"New ScopeTable with id "<<currentScopeTable->getUid()<<" created"<<endl<<endl;

}

void SymbolTable::exitScope() {
    if( currentScopeTable == nullptr ) return;
    ScopeTable *toDelete = currentScopeTable;
    currentScopeTable = currentScopeTable->getParentScope();
    cout<<"ScopeTable with id "<<toDelete->getUid()<<" removed"<<endl<<endl;
    delete toDelete;


}

bool SymbolTable::insertSymbol(SymbolInfo symbolInfo) {
  //  cout<<"aaa"<<endl<<endl;
    if( currentScopeTable == nullptr ) return false;
    bool inserted = currentScopeTable->insertSymbol(symbolInfo);
    return inserted;
}

bool SymbolTable::removeSymbol(string key) {
    if( currentScopeTable == nullptr ) return false;
    bool deleted = currentScopeTable->deleteSymbol(key);
    if(!deleted)
        cout<<key<<" not found"<<endl<<endl;
    return deleted;
}

SymbolInfo *SymbolTable::lookUpSymbol(string key) {

    ScopeTable *scopeTableNow = currentScopeTable;

    while (scopeTableNow!= nullptr){
        SymbolInfo *si =  scopeTableNow->lookUpSymbol(key);
        if( si!= nullptr ){
            return si;
        }
        scopeTableNow = scopeTableNow->getParentScope();
    }

    cout<<"Not found"<<endl<<endl;
    return nullptr;

}

void SymbolTable::printCurrentScopeTable() {
    currentScopeTable->printScopeTable();
}

void SymbolTable::printAllScopeTable() {
    ScopeTable *cur = currentScopeTable;
    while (cur!= nullptr){
        cur->printScopeTable();
        cur = cur->getParentScope();
    }
}
