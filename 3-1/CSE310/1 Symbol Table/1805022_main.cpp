#include <bits/stdc++.h>
#include "1805022_SymbolTable.h"

using namespace std;

int main() {
    freopen("input.txt", "r", stdin);
    freopen("1805022_output.txt", "w", stdout);
    int bucketSize = 10;
    cin>>bucketSize;

    SymbolTable symbolTable(bucketSize);
    string command;
    while(cin>>command){
        if( command == "I" ){
            string name,type;
            cin>>name>>type;
            cout<<command<<" "<<name<<" "<<type<<endl<<endl;
            SymbolInfo symbolInfo(name,type);
            symbolTable.insertSymbol(symbolInfo);
        }else if( command == "L" ){
            string name;
            cin>>name;
            cout<<command<<" "<<name<<endl<<endl;
            symbolTable.lookUpSymbol(name);
        }else if( command == "D" ){
            string name;
            cin>>name;
            cout<<command<<" "<<name<<endl<<endl;
            symbolTable.removeSymbol(name);
        }else if( command == "P" ){
            string code;
            cin>>code;
            cout<<command<<" "<<code<<endl<<endl;
            if( code == "A" )
                symbolTable.printAllScopeTable();
            else
                symbolTable.printCurrentScopeTable();
        }else if( command == "S" ){
            cout<<command<<endl<<endl;
            symbolTable.enterScope();
        }else if( command == "E" ){
            cout<<command<<endl<<endl;
            symbolTable.exitScope();
        }else if( command == "END" ){
            return 0;
        }
    }
    return 0;
}
