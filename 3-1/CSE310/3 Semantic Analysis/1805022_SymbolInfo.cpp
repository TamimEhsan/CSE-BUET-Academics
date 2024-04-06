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

SymbolInfo::SymbolInfo(SymbolInfo *symbolInfo) {
    name = symbolInfo->name;
    type = symbolInfo->type;
    typeSpecifier = symbolInfo->typeSpecifier;
    size = symbolInfo->size;
    functionDeclaration = symbolInfo->functionDeclaration;
    functionDefinition = symbolInfo->functionDefinition;
    array = symbolInfo->array;
    parameter_list = symbolInfo->parameter_list;
    declaration_list = symbolInfo->declaration_list;
}


SymbolInfo::SymbolInfo(const string &name, const string &type) : name(name), type(type) {}

SymbolInfo::SymbolInfo(const string &name, const string &type, const string &typeSpecifier) : name(name), type(type),
                                                                                              typeSpecifier(
                                                                                                      typeSpecifier) {}

SymbolInfo::SymbolInfo(const string &name, const string &type, const string &typeSpecifier, int size) : name(name),
                                                                                                        type(type),
                                                                                                        typeSpecifier(
                                                                                                                typeSpecifier),
                                                                                                        size(size) {}

const string &SymbolInfo::getTypeSpecifier() const {
    return typeSpecifier;
}

void SymbolInfo::setTypeSpecifier(const string &typeSpecifier) {
    SymbolInfo::typeSpecifier = typeSpecifier;
}

int SymbolInfo::getSize() const {
    return size;
}

void SymbolInfo::setSize(int size) {
    SymbolInfo::size = size;
}

void SymbolInfo::pushDeclaration(SymbolInfo* symbolInfo){
    declaration_list.push_back(symbolInfo);
}

vector<SymbolInfo*> SymbolInfo::getDeclarationList(){
    return declaration_list;
}

void SymbolInfo::setDeclarationList(vector<SymbolInfo*> symbolInfos){
    declaration_list = symbolInfos;
}

bool SymbolInfo::isFunctionDefinition() const {
    return functionDefinition;
}

void SymbolInfo::setFunctionDefinition(bool functionDefinition) {
    SymbolInfo::functionDefinition = functionDefinition;
}

bool SymbolInfo::isFunctionDeclaration() const {
    return functionDeclaration;
}

void SymbolInfo::setFunctionDeclaration(bool functionDeclaration) {
    SymbolInfo::functionDeclaration = functionDeclaration;
}

const vector<SymbolInfo *> &SymbolInfo::getParameterList() const {
    return parameter_list;
}

void SymbolInfo::setParameterList(const vector<SymbolInfo *> &parameterList) {
    parameter_list = parameterList;
}

void SymbolInfo::pushParameter(SymbolInfo *symbolInfo) {
    parameter_list.push_back(symbolInfo);
}

SymbolInfo::SymbolInfo(SymbolInfo &symbolInfo) {
    name = symbolInfo.name;
    type = symbolInfo.type;
    typeSpecifier = symbolInfo.typeSpecifier;
    size = symbolInfo.size;
    functionDeclaration = symbolInfo.functionDeclaration;
    functionDefinition = symbolInfo.functionDefinition;
    array = symbolInfo.array;
    parameter_list = symbolInfo.parameter_list;
    declaration_list = symbolInfo.declaration_list;
}

bool SymbolInfo::isArray() const {
    return array;
}

void SymbolInfo::setArray(bool array) {
    SymbolInfo::array = array;
}


