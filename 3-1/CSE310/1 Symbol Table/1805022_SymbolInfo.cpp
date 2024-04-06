//
// Created by User on 5/23/2022.
//

#include "1805022_SymbolInfo.h"

const string &SymbolInfo::getName() const {
    return name;
}

void SymbolInfo::setName(const string &name) {
    SymbolInfo::name = name;
}

const string &SymbolInfo::getType() const {
    return type;
}

void SymbolInfo::setType(const string &type) {
    SymbolInfo::type = type;
}

SymbolInfo *SymbolInfo::getNext() const {
    return next;
}

void SymbolInfo::setNext(SymbolInfo *next) {
    SymbolInfo::next = next;
}

SymbolInfo::SymbolInfo() {}

SymbolInfo::~SymbolInfo() {

}

SymbolInfo::SymbolInfo(const string &name, const string &type) : name(name), type(type) {}
