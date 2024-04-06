%option noyywrap

%x CHAR_STATE
%x STRING_STATE
%x SINGLE_COMMENT_STATE
%x MULTI_COMMENT_STATE

%{

#include "bits/stdc++.h"
#include "1805022_SymbolInfo.h"
#include "1805022_SymbolTable.h"
#include "1805022_ScopeTable.h"

using namespace std;

int global_line_count = 1;
int error_count = 0;
int line_count = 0;

string string_token;
string string_log;

string char_token;
string char_log;
int char_length;
string comment;

ofstream logout;
ofstream tokenout;


int bucket_size = 7;
SymbolTable symbolTable(bucket_size);

int lineCount = 0;

string toUpper(string s){
    for(auto &c:s) c = toupper(c);
    return s;
}
char processChar(const char* s){
   // '(\\[nt\\afrbv0\"])'
    if( strlen(s) == 3 ) return s[1];
    if( s[2] == 'n' ) return '\n';
    if( s[2] == 't' ) return '\t';
    if( s[2] == '\\' ) return '\\';
    if( s[2] == 'a' ) return '\a';
    if( s[2] == 'f' ) return '\f';
    if( s[2] == 'r' ) return '\r';
    if( s[2] == 'b' ) return '\b';
    if( s[2] == 'v' ) return '\v';
    if( s[2] == '0' ) return '\0';
    if( s[2] == '\"' ) return '\"';
}
%}

KEYWORD if|for|do|int|float|void|switch|default|else|while|break|char|double|return|case|continue
CONST_CHAR '.'|'(\\[nt\\afrbv0\"])'

MULTI_CHAR_ERROR '((.)|(\\[nt\\afrbv0\"]))*'
UNFINISHED_CHAR_ERROR '(([^'])|(\\[nt\\afrbv0\"]))*
EMPTY_CHAR_ERROR ''
LETTER [A-Za-z]
DIGIT [0-9]
WHITESPACE [ \t\r\v\f]
%%




{KEYWORD} {
    tokenout<<"<"<<toUpper(yytext)<<"> ";
    logout<<"Line no "<< global_line_count <<": Token " <<"<"<<toUpper(yytext)<< ">"<<" Lexeme "<<yytext<<" found\n"<<endl;
 }
{DIGIT}+ {
    tokenout<<"<CONST_INT, "<<yytext<<"> ";
    logout<<"Line no "<< global_line_count <<": Token " <<"<CONST_INT>"<<" Lexeme "<<yytext<<" found\n"<<endl;
	bool inserted = symbolTable.insertSymbol(SymbolInfo(yytext,"CONST_INT"),logout);
    if( inserted ) symbolTable.printAllScopeTable(logout);
}

[0-9]*\.[0-9]+ {
    tokenout<<"<CONST_FLOAT, "<<yytext<<"> ";
    logout<<"Line no "<< global_line_count <<": Token " <<"<CONST_FLOAT>"<<" Lexeme "<<yytext<<" found\n"<<endl;
    bool inserted = symbolTable.insertSymbol(SymbolInfo(yytext,"CONST_FLOAT"),logout);
    if( inserted ) symbolTable.printAllScopeTable(logout);

}
([0-9]+([Ee][\+\-]?[0-9]+)) {
    tokenout<<"<CONST_FLOAT, "<<yytext<<"> ";
    logout<<"Line no "<< global_line_count <<": Token " <<"<CONST_FLOAT>"<<" Lexeme "<<yytext<<" found\n"<<endl;
    bool inserted = symbolTable.insertSymbol(SymbolInfo(yytext,"CONST_FLOAT"),logout);
    if( inserted ) symbolTable.printAllScopeTable(logout);

}
([0-9]*(\.[0-9]+)([Ee][\+\-]?[0-9]+)?) {
    tokenout<<"<CONST_FLOAT, "<<yytext<<"> ";
    logout<<"Line no "<< global_line_count <<": Token " <<"<CONST_FLOAT>"<<" Lexeme "<<yytext<<" found\n"<<endl;
    bool inserted = symbolTable.insertSymbol(SymbolInfo(yytext,"CONST_FLOAT"),logout);
    if( inserted ) symbolTable.printAllScopeTable(logout);

}
([0-9]*\.[0-9]*\.[0-9\.Ee\+\-]*) {
    error_count++;
    logout<<"Error at line no "<< global_line_count <<": Too many decimal points "<<yytext<<"\n"<<endl;
}
[0-9]*[Ee][\+\-]?([0-9\+\-Ee\.]*) {
    error_count++;
	logout<<"Error at line no "<< global_line_count <<": Ill formed number "<<yytext<<"\n"<<endl;
}

[0-9]*\.[0-9]*[Ee][\+\-]?([0-9\.\+\-eEe\.]*) {
    error_count++;
	logout<<"Error at line no "<< global_line_count <<": Ill formed number "<<yytext<<"\n"<<endl;

}

[_A-Za-z][A-Za-z0-9_]* {
    tokenout<<"<ID, "<<yytext<<"> ";
    logout<<"Line no "<< global_line_count <<": Token " <<"<ID>"<<" Lexeme "<<yytext<<" found\n"<<endl;
	bool inserted = symbolTable.insertSymbol(SymbolInfo(yytext,"ID"),logout);
    if( inserted ) symbolTable.printAllScopeTable(logout);

}

[0-9][A-Za-z0-9_]* {
    error_count++;
    logout<<"Error at line no "<<global_line_count<<": Invalid prefix on ID or invalid suffix on Number "<<yytext<<"\n"<<endl;
}

"+"|"-" {
    tokenout<<"<ADDOP, "<<yytext<<"> ";
    logout<<"Line no "<< global_line_count <<": Token " <<"<ADDOP>"<<" Lexeme "<<yytext<<" found\n"<<endl;
}
"*"|"/"|"%"  {
    tokenout<<"<MULOP, "<<yytext<<"> ";
    logout<<"Line no "<< global_line_count <<": Token " <<"<MULOP>"<<" Lexeme "<<yytext<<" found\n"<<endl;
}
"++"|"--"  {
    tokenout<<"<INCOP, "<<yytext<<"> ";
    logout<<"Line no "<< global_line_count <<": Token " <<"<INCOP>"<<" Lexeme "<<yytext<<" found\n"<<endl;
}
"<"|"<="|">"|">="|"=="|"!="  {
    tokenout<<"<RELOP, "<<yytext<<"> ";
    logout<<"Line no "<< global_line_count <<": Token " <<"<RELOP>"<<" Lexeme "<<yytext<<" found\n"<<endl;
}
"="  {
    tokenout<<"<ASSIGNOP, "<<yytext<<"> ";
    logout<<"Line no "<< global_line_count <<": Token " <<"<ASSIGNOP>"<<" Lexeme "<<yytext<<" found\n"<<endl;
}
"&&"|"||"  {
    tokenout<<"<LOGICOP, "<<yytext<<"> ";
    logout<<"Line no "<< global_line_count <<": Token " <<"<LOGICOP>"<<" Lexeme "<<yytext<<" found\n"<<endl;
}
"!"  {
    tokenout<<"<NOT, "<<yytext<<"> ";
    logout<<"Line no "<< global_line_count <<": Token " <<"<NOT>"<<" Lexeme "<<yytext<<" found\n"<<endl;
}
"("  {
    tokenout<<"<LPAREN, "<<yytext<<"> ";
    logout<<"Line no "<< global_line_count <<": Token " <<"<LPAREN>"<<" Lexeme "<<yytext<<" found\n"<<endl;
}
")"  {
    tokenout<<"<RPAREN, "<<yytext<<"> ";
    logout<<"Line no "<< global_line_count <<": Token " <<"<RPAREN>"<<" Lexeme "<<yytext<<" found\n"<<endl;
}
"{"  {
    tokenout<<"<LCURL, "<<yytext<<"> ";
    logout<<"Line no "<< global_line_count <<": Token " <<"<LCURL>"<<" Lexeme "<<yytext<<" found\n"<<endl;
    symbolTable.enterScope();
}
"}"  {
    tokenout<<"<RCURL, "<<yytext<<"> ";
    logout<<"Line no "<< global_line_count <<": Token " <<"<RCURL>"<<" Lexeme "<<yytext<<" found\n"<<endl;
    symbolTable.exitScope();
}
"["  {
    tokenout<<"<LTHIRD, "<<yytext<<"> ";
    logout<<"Line no "<< global_line_count <<": Token " <<"<LTHIRD>"<<" Lexeme "<<yytext<<" found\n"<<endl;
}
"]"  {
    tokenout<<"<RTHIRD, "<<yytext<<"> ";
    logout<<"Line no "<< global_line_count <<": Token " <<"<RTHIRD>"<<" Lexeme "<<yytext<<" found\n"<<endl;
}
","  {
    tokenout<<"<COMMA, "<<yytext<<"> ";
    logout<<"Line no "<< global_line_count <<": Token " <<"<COMMA>"<<" Lexeme "<<yytext<<" found\n"<<endl;
}
";"  {
    tokenout<<"<SEMICOLON, "<<yytext<<"> ";
    logout<<"Line no "<< global_line_count <<": Token " <<"<SEMICOLON>"<<" Lexeme "<<yytext<<" found\n"<<endl;
}

\/\* {

    comment = "/*";
    line_count = 0;
    // cout<<"STARTED MULTI COMMENT"<<endl;
    BEGIN MULTI_COMMENT_STATE;
}
<MULTI_COMMENT_STATE>\*\/ {
    comment+="*/";
    // cout<<comment<<endl<<"ENDED MULTI COMMENT"<<endl;
    logout<<"Line no "<< global_line_count <<": Token " <<"<COMMENT>"<<" Lexeme "<<comment<<" found\n"<<endl;
    global_line_count+=line_count;
    BEGIN INITIAL;
}

<MULTI_COMMENT_STATE><<EOF>> {
    error_count++;
    logout<<"Error at line no "<< global_line_count <<": Unterminated Comment "<<comment<<"\n"<<endl;
	global_line_count += line_count;	
	BEGIN INITIAL;
}

<MULTI_COMMENT_STATE>\n {
    comment+="\n";
    line_count++;
}
<MULTI_COMMENT_STATE>\r {
    comment+="\r";
}
<MULTI_COMMENT_STATE>. {
    comment+=yytext[0];
}

\/\/ {
    // cout<<"BEGIN SINGLE COMMENT"<<endl;
    line_count = 0;
    comment = "//";
    BEGIN SINGLE_COMMENT_STATE;
}


<SINGLE_COMMENT_STATE>[\r]?\n {
    line_count++;
    // cout<<comment<<endl<<"ENDED SINGLE COMMENT"<<endl;
    logout<<"Line no "<< global_line_count <<": Token " <<"<COMMENT>"<<" Lexeme "<<comment<<" found\n"<<endl;
    global_line_count+=line_count;
    BEGIN INITIAL;
}

<SINGLE_COMMENT_STATE><<EOF>> {
    error_count++;
   	logout<<"Error at line no "<< global_line_count <<": Unterminated Comment "<<comment<<"\n"<<endl;
    global_line_count += line_count;
    BEGIN INITIAL;
}

<SINGLE_COMMENT_STATE>\\\r\n {
    line_count++;
    comment+="\\\r\n";
}

<SINGLE_COMMENT_STATE>\\\n {
    line_count++;
    comment+="\\\n";
}

<SINGLE_COMMENT_STATE>\\ {
    comment+="\\";
}

<SINGLE_COMMENT_STATE>. {
    comment+=yytext[0];
}

' {
    // cout<<"BEGIN CHAR"<<endl;
    char_length = 0;
    char_log = "'";
    char_token = "";
    BEGIN CHAR_STATE;
}

<CHAR_STATE>' {
    char_log+="'";
    // cout<<"ENDED CHAR "<<char_log<<" "<<char_length<<endl;
    if( char_length == 0){
        error_count++;
        logout<<"Error at line no "<<global_line_count<<": Empty character constant error "<<char_log<<"\n"<<endl;
    }else if(char_length == 1){
        tokenout<<"<CONST_CHAR, "<<char_token<<"> ";
        logout<<"Line no "<< global_line_count <<": Token " <<"<CONST_CHAR>"<<" Lexeme "<<char_log<<" found -->"<<"<CONST_CHAR, "<<char_token<<"> ";;
        bool inserted = symbolTable.insertSymbol(SymbolInfo(char_log,"ID"),logout);
        if( inserted ) symbolTable.printAllScopeTable(logout);
    }else{
        error_count++;
        logout<<"Error at line no "<<global_line_count<<": Multi character constant error "<<char_log<<"\n"<<endl;
    }
    BEGIN INITIAL;
}



<CHAR_STATE>\\n {
    char_length++;
    char_log+="\\n";
    char_token+="\n";
}
<CHAR_STATE>\\t {
    char_length++;
    char_log+="\\t";
    char_token+="\t";
}
<CHAR_STATE>\\\\ {
    char_length++;
    char_log+="\\\\";
    char_token+="\\";
}
<CHAR_STATE>\\' {
    char_length++;
    char_log+="\\'";
    char_token+="\'";
}
<CHAR_STATE>\\a {
    char_length++;
    char_log+="\\a";
    char_token+="\a";
}
<CHAR_STATE>\\f {
    char_length++;
    char_log+="\\f";
    char_token+="\f";
}
<CHAR_STATE>\\r {
    char_length++;
    char_log+="\\r";
    char_token+="\r";
}
<CHAR_STATE>\\b {
    char_length++;
    char_log+="\\b";
    char_token+="\b";
}
<CHAR_STATE>\\v {
    char_length++;
    char_log+="\\v";
    char_token+="\v";
}
<CHAR_STATE>\\0 {
    char_length++;
    char_log+="\\0";
    char_token+="\0";
}

<CHAR_STATE>[\r]?\n {
    error_count++;
    logout<<"Error at line no "<<global_line_count<<": Unterminated character "<<char_log<<"\n"<<endl;
    global_line_count++;
    BEGIN INITIAL;
}
<CHAR_STATE>. {
    char_length++;
    char_log+=yytext[0];
    char_token+=yytext[0];
}



\" {
   //cout<<"BEGIN CHAR"<<endl;
   line_count = 0;
   string_log = "\"";
   string_token = "\"";
   BEGIN STRING_STATE;
}
<STRING_STATE>\"  {
    string_log+="\"";
    string_token+="\"";
    tokenout<<"<STRING, "<<string_token<<"> ";
    logout<<"Line no "<< global_line_count <<": Token " <<"<STRING>"<<" Lexeme "<<string_log<<" found -->"<<"<STRING, "<<string_token<<"> \n"<<endl;
    global_line_count+=line_count;
    BEGIN INITIAL;
}

<STRING_STATE>\\\r\n  {
    string_log+="\\\r\n";
    line_count++;
}
<STRING_STATE>\\\n  {
    string_log+="\\\n";
    line_count++;
}

<STRING_STATE>[\r]?\n {
    error_count++;
    logout<<"Error at line no "<<global_line_count<<": Unterminated String "<<string_log<<"\n"<<endl;
    global_line_count+=line_count+1;
    BEGIN INITIAL;
}
<STRING_STATE><<EOF>> {
    error_count++;
    logout<<"Error at line no "<<global_line_count<<": Unterminated String "<<string_log<<"\n"<<endl;
    global_line_count++;
    BEGIN INITIAL;
}

<STRING_STATE>\\n {
    string_log+="\\n";
    string_token+="\n";
}
<STRING_STATE>\\t {
    string_log+="\\t";
    string_token+="\t";
}
<STRING_STATE>\\\\ {
    char_log+="\\\\";
    string_token+="\\";
}
<STRING_STATE>\\\" {
    string_log+="\\\"";
    string_token+="\"";
}
<STRING_STATE>\\a {
    string_log+="\\a";
    string_token+="\a";
}
<CHAR_STATE>\\f {
    string_log+="\\f";
    string_token+="\f";
}
<STRING_STATE>\\r {
    string_log+="\\r";
    string_token+="\r";
}
<STRING_STATE>\\b {
    string_log+="\\b";
    string_token+="\b";
}
<STRING_STATE>\\v {
    string_log+="\\v";
    string_token+="\v";
}
<STRING_STATE>\\0 {
    string_log+="\\0";
    string_token+="\0";
}
<STRING_STATE>. {
    string_log+=yytext[0];
    string_token+=yytext[0];
}

\n {
    global_line_count++;
}
{WHITESPACE}+ {}
. {
    error_count++;
    logout<<"Error at line no "<<global_line_count<<": Unrecognized character "<<yytext<<"\n"<<endl;
}

%%

int main(int argc,char *argv[]){
	
	if(argc!=2){
		printf("Please provide input file name and try again\n");
		return 0;
	}
	
	FILE *fin=fopen(argv[1],"r");
	if(fin==NULL){
		printf("Cannot open specified file\n");
		return 0;
	}

	tokenout.open("1805022_token.txt");
	logout.open("1805022_log.txt");

	yyin= fin;
	yylex();
	fclose(yyin);

	symbolTable.printAllScopeTable(logout);

	logout<<"Total lines: "<<global_line_count<<endl;
	logout<<"Total errors: "<<error_count<<endl;

	tokenout.close();
	logout.close();


	return 0;
}