%option noyywrap

%x CHAR_STATE
%x STRING_STATE
%x SINGLE_COMMENT_STATE
%x MULTI_COMMENT_STATE

%{

// amar include
#include "bits/stdc++.h"
#include "1805022_SymbolInfo.h"
#include "1805022_SymbolTable.h"
#include "1805022_ScopeTable.h"
// #include "1805022_NonTerminal.h"

// system er input
#include "y.tab.h"


using namespace std;

// global variable starts
int global_line_count = 1;
int error_count = 0;
int line_count = 0;

string string_token;
string string_log;

string char_token;
string char_log;
int char_length;
string comment;
// global variable ends

// external variables
extern ofstream logout;
extern ofstream errout;
// extern YYSTYPE yylval;
extern SymbolTable* symbolTable;

// external variable ends

void error_output(string errorType,string error){
	logout<<"Error at line "<<global_line_count<<": "<<errorType<<" "<<error<<"\n"<<endl;
	errout<<"Error at line "<<global_line_count<<": "<<errorType<<" "<<error<<"\n"<<endl;
	error_count++;
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


LETTER [A-Za-z]
DIGIT [0-9]
WHITESPACE [ \t\r\v\f]

%%


"if" {
    yylval.symbolInfo =  new SymbolInfo(yytext, "KEYWORD");
    return IF;
}
"else" {
    yylval.symbolInfo =  new SymbolInfo(yytext, "KEYWORD");
    return ELSE;
}
"for" {
    yylval.symbolInfo =  new SymbolInfo(yytext, "KEYWORD");
    return FOR;
}
"while" {
    yylval.symbolInfo =  new SymbolInfo(yytext, "KEYWORD");
    return WHILE;
}
"do" {
    yylval.symbolInfo =  new SymbolInfo(yytext, "KEYWORD");
    return DO;
}
"break" {
    yylval.symbolInfo =  new SymbolInfo(yytext, "KEYWORD");
    return BREAK;
}
"char" {
    yylval.symbolInfo =  new SymbolInfo(yytext, "KEYWORD");
    return CHAR;
}
"double" {
    yylval.symbolInfo =  new SymbolInfo(yytext, "KEYWORD");
    return DOUBLE;
}
"return" {
    yylval.symbolInfo =  new SymbolInfo(yytext, "KEYWORD");
    return RETURN;
}
"switch" {
    yylval.symbolInfo =  new SymbolInfo(yytext, "KEYWORD");
    return SWITCH;
}
"case" {
    yylval.symbolInfo =  new SymbolInfo(yytext, "KEYWORD");
    return CASE;
}
"default" {
    yylval.symbolInfo =  new SymbolInfo(yytext, "KEYWORD");
    return DEFAULT;
}
"continue" {
    yylval.symbolInfo =  new SymbolInfo(yytext, "KEYWORD");
    return CONTINUE;
}
"printf"	{
    yylval.symbolInfo =  new SymbolInfo(yytext, "KEYWORD");
    return PRINTLN;
}

"int" { 
	yylval.symbolInfo = new  SymbolInfo(yytext,"TYPE_SPECIFIER", "INT"); 
	return INT;
}
"float" { 
	yylval.symbolInfo = new  SymbolInfo(yytext,"TYPE_SPECIFIER", "FLOAT"); 
	return FLOAT;
}
"void" { 
	yylval.symbolInfo = new  SymbolInfo(yytext,"TYPE_SPECIFIER", "VOID"); 
	return VOID;
}

[_A-Za-z][A-Za-z0-9_]* {
	yylval.symbolInfo =  new SymbolInfo(yytext, "ID");
	return ID;
}

[0-9][A-Za-z0-9_]+ {
    error_output("Invalid prefix on ID or invalid suffix on Number",yytext);
}

{DIGIT}+ {
	yylval.symbolInfo =  new SymbolInfo(yytext, "CONST_INT", "INT");
	return CONST_INT;
}


[0-9]*\.[0-9]+ {
    yylval.symbolInfo =  new SymbolInfo(yytext, "CONST_FLOAT", "FLOAT");
	return CONST_FLOAT;
}

([0-9]+([Ee][\+\-]?[0-9]+)) {
    yylval.symbolInfo =  new SymbolInfo(yytext, "CONST_FLOAT", "FLOAT");
	return CONST_FLOAT;
}

([0-9]*(\.[0-9]+)([Ee][\+\-]?[0-9]+)?) {
    yylval.symbolInfo =  new SymbolInfo(yytext, "CONST_FLOAT", "FLOAT");
	return CONST_FLOAT;
}

([0-9]*\.[0-9]*\.[0-9\.Ee\+\-]*) {
	error_output("Too many decimal points",yytext);
    yylval.symbolInfo =  new SymbolInfo(yytext, "CONST_FLOAT", "FLOAT");
	return CONST_FLOAT;
}

[0-9]*[Ee][\+\-]?([0-9\+\-Ee\.]*) {
    error_output("Ill formed number",yytext);
}

[0-9]*\.[0-9]*[Ee][\+\-]?([0-9\.\+\-eEe\.]*) {
    error_output("Ill formed number",yytext);
}



"+"|"-" {
    yylval.symbolInfo =  new SymbolInfo(yytext, "ADDOP");
	return ADDOP;
}

"*"|"/"|"%"  {
	yylval.symbolInfo =  new SymbolInfo(yytext, "MULOP");
	return MULOP;
}

"++"  {
	yylval.symbolInfo =  new SymbolInfo(yytext, "INCOP");
	return INCOP;
}
"--"  {
	yylval.symbolInfo =  new SymbolInfo(yytext, "DECOP");
	return DECOP;
}

"<"|"<="|">"|">="|"=="|"!="  {
	yylval.symbolInfo =  new SymbolInfo(yytext, "RELOP");
	return RELOP; 
}

"="  {
	yylval.symbolInfo =  new SymbolInfo(yytext, "ASSIGNOP");
	return ASSIGNOP;
}

"&&"|"||"  {
    yylval.symbolInfo =  new SymbolInfo(yytext, "LOGICOP");
	return LOGICOP;
}

"!"  {
	yylval.symbolInfo =  new SymbolInfo(yytext, "NOT");
	return NOT;
}

"("  {
	yylval.symbolInfo =  new SymbolInfo(yytext, "LPAREN");
	return LPAREN;
}

")"  {
	yylval.symbolInfo =  new SymbolInfo(yytext, "RPAREN");
	return RPAREN;
}

"{"  {
	yylval.symbolInfo =  new SymbolInfo(yytext, "LCURL");
	return LCURL;
   
}

"}"  {
	yylval.symbolInfo =  new SymbolInfo(yytext, "RCURL");
	return RCURL;
   
}

"["  {
	yylval.symbolInfo =  new SymbolInfo(yytext, "LTHIRD");
	return LTHIRD;
}

"]"  {
	yylval.symbolInfo =  new SymbolInfo(yytext, "RTHIRD");
	return RTHIRD;
}

","  {
	yylval.symbolInfo =  new SymbolInfo(yytext, "COMMA");
	return COMMA;
    
}

";"  {
	yylval.symbolInfo =  new SymbolInfo(yytext, "SEMICOLON");
	return SEMICOLON;
}

' {
   
    char_length = 0;
    char_log = "'";
    char_token = "";
    BEGIN CHAR_STATE;
}

<CHAR_STATE>' {
    char_log+="'";
   
    if( char_length == 0){
        error_count++;
		error_output("Empty character constant error",char_log);
    }else if(char_length == 1){
		yylval.symbolInfo = new SymbolInfo(char_token,"CONST_CHAR");
        return CONST_CHAR;
    }else{
		error_output("Multi character constant error",char_log);
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
	error_output("Unterminated character",char_log);
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
   // tokenout<<"<STRING, "<<string_token<<"> ";
   // logout<<"Line no "<< global_line_count <<": Token " <<"<STRING>"<<" Lexeme "<<string_log<<" found -->"<<"<STRING, "<<string_token<<"> \n"<<endl;
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
	error_output("Unterminated String",string_log);
    global_line_count+=line_count+1;
    BEGIN INITIAL;
}
<STRING_STATE><<EOF>> {
    error_output("Unterminated String",string_log);
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
<STRING_STATE>\\f {
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


\/\/ {
    line_count = 0;
    comment = "//";
    BEGIN SINGLE_COMMENT_STATE;
}


<SINGLE_COMMENT_STATE>[\r]?\n {
	// single line comment ends ok here
    line_count++;
   // logout<<"Line no "<< global_line_count <<": Token " <<"<COMMENT>"<<" Lexeme "<<comment<<" found\n"<<endl;
    global_line_count+=line_count;
    BEGIN INITIAL;
}

<SINGLE_COMMENT_STATE><<EOF>> {
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

\/\* {
    comment = "/*";
    line_count = 0;
    BEGIN MULTI_COMMENT_STATE;
}
<MULTI_COMMENT_STATE>\*\/ {

	// multi line comment ends ok here
    comment+="*/";
    // logout<<"Line no "<< global_line_count <<": Token " <<"<COMMENT>"<<" Lexeme "<<comment<<" found\n"<<endl;
    global_line_count+=line_count;
    BEGIN INITIAL;
}

<MULTI_COMMENT_STATE><<EOF>> {
    error_output("Unterminated Comment",comment);
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

\n {
    global_line_count++;
}

{WHITESPACE}+ {}

. {
    error_output("Unrecognized character",yytext);
}

%%


