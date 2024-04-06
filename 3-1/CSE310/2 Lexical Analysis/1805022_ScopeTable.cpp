//
// Created by User on 5/24/2022.
//

#include "1805022_ScopeTable.h"

ScopeTable::ScopeTable(int bucketSize) : bucketSize(bucketSize) {
    hashTable = new SymbolInfo*[bucketSize];
    for(int i=0;i<bucketSize;i++)
        hashTable[i] = nullptr;
}

ScopeTable *ScopeTable::getParentScope() const {
    return parentScope;
}

void ScopeTable::setParentScope(ScopeTable *parentScope) {
    ScopeTable::parentScope = parentScope;
}

string ScopeTable::getUid() const {
    return uid;
}

void ScopeTable::setUid(string uid) {
    ScopeTable::uid = uid;
}

int ScopeTable::getChildCounter() const {
    return childCounter;
}

void ScopeTable::setChildCounter(int childCounter) {
    ScopeTable::childCounter = childCounter;
}

int ScopeTable::getBucketSize() const {
    return bucketSize;
}

void ScopeTable::setBucketSize(int bucketSize) {
    ScopeTable::bucketSize = bucketSize;
}

SymbolInfo **ScopeTable::getHashTable() const {
    return hashTable;
}

void ScopeTable::setHashTable(SymbolInfo **hashTable) {
    ScopeTable::hashTable = hashTable;
}

ScopeTable::~ScopeTable() {
    for(int i=0;i< bucketSize;i++){
        SymbolInfo *cur = hashTable[i];
        while(cur!=nullptr){
            SymbolInfo *si = cur->getNext();
            delete cur;
            cur = si;
        }
    }
    delete[] hashTable;
}

unsigned long ScopeTable::getHash(string str) {
    unsigned long hash = 0;
    for(auto ch:str){
        int c = ch;
        hash = c + (hash << 6) + (hash << 16) - hash;
    }
    return hash%ScopeTable::bucketSize;
}

bool ScopeTable::insertSymbol(SymbolInfo symbolInfo) {
    string name = symbolInfo.getName();
    string type = symbolInfo.getType();
    if( lookUpSymbol(name) != nullptr ) {
        cout<<"<"<<symbolInfo.getName()<<","<<symbolInfo.getType()<<"> already exists in current ScopeTable"<<endl<<endl;
        return false;
    }
    int place = ScopeTable::getHash(name);
    SymbolInfo *newSymbolInfo = new SymbolInfo(name,type);
    int position = 0;
    if( ScopeTable::hashTable[place] == nullptr )
        ScopeTable::hashTable[place] = newSymbolInfo;
    else{
        SymbolInfo* symbolInfoNow = ScopeTable::hashTable[place];
        while(symbolInfoNow->getNext()!= nullptr){
            symbolInfoNow = symbolInfoNow->getNext();
            position++;
        }
        position++;
        symbolInfoNow->setNext(newSymbolInfo);

    }
    cout<<"Inserted in ScopeTable# "<<uid<<" at position "<<place<<", "<<position<<endl<<endl;
    return true;
}

SymbolInfo *ScopeTable::lookUpSymbol(string key) {

    int place = getHash(key);
  
    SymbolInfo* symbolInfoNow = hashTable[place];
    int position = 0;
    while( symbolInfoNow != nullptr){
      
        if( symbolInfoNow->getName() == key ) {
            cout<<"Found in ScopeTable# "<<uid<<" at position "<<place<<" , "<<position<<endl<<endl;
            return symbolInfoNow; }
        symbolInfoNow = symbolInfoNow->getNext();
        position++;
    }

    return nullptr;

}

bool ScopeTable::deleteSymbol(string key) {
    int place = ScopeTable::getHash(key);
    int position = 0;
    SymbolInfo* symbolInfoNow = ScopeTable::hashTable[place];
    if( symbolInfoNow == nullptr ) return false;
    else if( symbolInfoNow->getName() == key ){
        cout<<"Deleted Entry "<<place<<", "<<position<<" from current ScopeTable"<<endl<<endl;
        ScopeTable::hashTable[place] = symbolInfoNow->getNext();
        delete symbolInfoNow;
        return true;
    }
    SymbolInfo *symbolInfoPrev = symbolInfoNow;

    while( symbolInfoNow != nullptr){
        if( symbolInfoNow->getName() == key ) {
            symbolInfoPrev->setNext(symbolInfoNow->getNext());
            cout<<"Deleted Entry "<<place<<", "<<position<<" from current ScopeTable"<<endl<<endl;
            delete symbolInfoNow;
            return true;
        }
        position++;
        symbolInfoPrev = symbolInfoNow;
        symbolInfoNow = symbolInfoNow->getNext();
    }
    return false;
}

void ScopeTable::printScopeTable(ofstream &out) {
    out<<endl<<"ScopeTable # "<<uid<<endl;
    for(int i=0;i<bucketSize;i++){
        SymbolInfo *cur = hashTable[i];
        if( cur == nullptr ) continue;
        out<<i<<" -->  ";
        while (cur!= nullptr){
            out<<"< "<<cur->getName()<<" : "<<cur->getType()<<" > ";
            cur = cur->getNext();
        }
        out<<endl;
    }
    out<<endl;
}

