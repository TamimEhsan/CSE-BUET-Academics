%code requires{
    #include <bits/stdc++.h>
}

%{
#include <bits/stdc++.h>
#include <typeinfo>

#include "1805022_SymbolInfo.h"
#include "1805022_SymbolTable.h"
#include "1805022_ScopeTable.h"

using namespace std;

// global variables
ofstream logout;
ofstream errout;

SymbolTable* symbolTable = new SymbolTable(31);
SymbolInfo* symbolInfoArguments = new SymbolInfo();

// external variable
extern int global_line_count;
extern int error_count;
extern FILE *yyin;

// function declaration and defination

void grammar_rule_output(string parent,string children){
	logout<<"Line "<<global_line_count<<": "<<parent<<" : "<<children<<"\n"<<endl; 
}

void log_text_output(string log_text){
    logout<<log_text<<"\n"<<endl;
}

extern void error_output(string errorType,string error);

void log_output(string logg){
	logout<<logg<<"\n\n";
}

string concatName(vector<SymbolInfo*> symbolInfos){
	string name = "";
	for(auto symbolInfo: symbolInfos){
		name += symbolInfo->getName();
		if( symbolInfo->getType() == "TYPE_SPECIFIER" or symbolInfo->getType() == "KEYWORD" ) name+=" ";
		else if( symbolInfo->getName() == ";" or symbolInfo->getName() == "{"  ) name+="\n";
		else if(symbolInfo->getName() == "}")  name+="\n\n";
	}
	return name;
}

void insertFunctionToScope(SymbolInfo* functionName,SymbolInfo* typeSpecifier){
	functionName->setTypeSpecifier(typeSpecifier->getTypeSpecifier());
	functionName->setParameterList(symbolInfoArguments->getParameterList());
	functionName->setFunctionDefinition(true);
	//symbolInfoArguments->setParameterList({});
	bool inserted = symbolTable->insertSymbol(functionName);
	if( inserted ) return;
	
	auto prevDeclaration = symbolTable->lookUpSymbol(functionName->getName());

	if( !prevDeclaration->isFunctionDeclaration() ){
		error_output("Multiple declaration of",functionName->getName());
	}else{

		if( prevDeclaration->getTypeSpecifier() != functionName->getTypeSpecifier() ){
			error_output("Return type mismatch with function declaration in function",functionName->getName());
		}
		if( prevDeclaration->getParameterList().size() != functionName->getParameterList().size() ){
			error_output("Total number of arguments mismatch with declaration in function",functionName->getName());
		}else{
			auto argumentListDeclaration = prevDeclaration->getParameterList();
			auto argumentListDefinition = functionName->getParameterList();
			for(int i=0;i<argumentListDeclaration.size();i++){
				if( argumentListDeclaration[i]->getTypeSpecifier() != argumentListDefinition[i]->getTypeSpecifier()){
					error_output(to_string(i+1)+"th argument mismatch in function",functionName->getName());
				}
			}
		}
	}
	
}

bool isVoidTypeSpecifier(SymbolInfo* typeSpecifier){
	if( typeSpecifier->getTypeSpecifier() == "VOID" ){
		error_output("Variable type cannot be void","");
		return true;
	}
	return false;
}

string type_cast(SymbolInfo* leftSymbol,SymbolInfo* rightSymbol){
	string leftType = leftSymbol->getTypeSpecifier();
	string rightType = rightSymbol->getTypeSpecifier();
	if( leftType == "VOID" or rightType == "VOID" ) return "error"; // won't occur :/
	if( leftType == "error" or rightType == "error" ) return "error";
	if( leftType == "FLOAT" or rightType == "FLOAT" ) return "FLOAT";
	return "INT";
}

void yyerror(string s){
	// logout<<"Error at line "<<global_line_count<<": "<<s<<"\n"<<endl;
	// errout<<"Error at line "<<global_line_count<<": "<<s<<"\n"<<endl;
    // error_count++;
}

int yyparse(void);
int yylex(void);

%}

%error-verbose

%union{
    SymbolInfo* symbolInfo; 
	
}

%token<symbolInfo> IF ELSE LOWER_THAN_ELSE FOR WHILE DO BREAK CHAR DOUBLE RETURN SWITCH CASE DEFAULT CONTINUE PRINTLN INCOP DECOP ASSIGNOP NOT LPAREN RPAREN LCURL RCURL LTHIRD RTHIRD COMMA SEMICOLON INT FLOAT VOID CONST_INT CONST_FLOAT ID ADDOP MULOP RELOP LOGICOP CONST_CHAR 
%type<symbolInfo> start program unit func_declaration func_definition parameter_list compound_statement var_declaration type_specifier declaration_list statements statement expression_statement variable expression logic_expression rel_expression simple_expression term unary_expression factor argument_list arguments LCURL_

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%%
start : program{
		grammar_rule_output("start","program");
		$$ = new SymbolInfo("","start");
		$$->setName(concatName({$1}));
		log_output($$->getName());
	}
	;

program : program unit {
		grammar_rule_output("program","program unit");
		$$ = new SymbolInfo("","program");
		$$->setName(concatName({$1,$2}));
		log_output($$->getName());
	}
	| unit {
		grammar_rule_output("program","unit");
		$$ = new SymbolInfo("","program");
		$$->setName(concatName({$1}));
		log_output($$->getName());
	}
	;
	
unit : var_declaration {
		grammar_rule_output("unit","var_declaration");
		$$ = new SymbolInfo("","unit");
		$$->setName(concatName({$1}));
		log_output($$->getName());
	}
	| func_declaration {
		grammar_rule_output("unit","func_declaration");
		$$ = new SymbolInfo("","unit");
		$$->setName(concatName({$1}));
		log_output($$->getName());
	}
	| func_definition{
		grammar_rule_output("unit","func_definition");
		$$ = new SymbolInfo("","unit");
		$$->setName(concatName({$1}));
		log_output($$->getName());
	}
	| error {
		yyclearin;
		yyerrok;
		error_output("Syntax error at unit","");
		$$ = new SymbolInfo("","unit");
		$$->setName("");
	}
	;
     
func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON {
		grammar_rule_output("func_declaration","type_specifier ID LPAREN parameter_list RPAREN SEMICOLON");
		$$ = new SymbolInfo("","func_declaration");
		$$->setName(concatName({$1,$2,$3,$4,$5,$6}));
		$2->setFunctionDeclaration(true);
		$2->setParameterList($4->getParameterList());
		$2->setTypeSpecifier($1->getTypeSpecifier());
		symbolInfoArguments->setParameterList({});

		bool inserted = symbolTable->insertSymbol($2);
		if( !inserted ){
			error_output("multiple defination of",$2->getName());
		}

		log_output($$->getName());
	} 
	| type_specifier ID LPAREN error RPAREN SEMICOLON {
		grammar_rule_output("func_declaration","type_specifier ID LPAREN parameter_list RPAREN SEMICOLON");
		$$ = new SymbolInfo("","func_declaration");
		$$->setName(concatName({$1,$2,$3,$5,$6}));
		$2->setFunctionDeclaration(true);
		// $2->setParameterList($4->getParameterList());
		$2->setTypeSpecifier($1->getTypeSpecifier());
		symbolInfoArguments->setParameterList({});

		bool inserted = symbolTable->insertSymbol($2);
		if( !inserted ){
			error_output("multiple defination of",$2->getName());
		}
		log_output($$->getName());
	}
	| type_specifier ID LPAREN RPAREN SEMICOLON {
		grammar_rule_output("func_declaration","type_specifier ID LPAREN RPAREN SEMICOLON");
		$$ = new SymbolInfo("","func_declaration");
		$$->setName(concatName({$1,$2,$3,$4,$5}));
		$2->setFunctionDeclaration(true);
		$2->setTypeSpecifier($1->getTypeSpecifier());

		bool inserted = symbolTable->insertSymbol($2);
		if( !inserted ){
			error_output("multiple defination of",$2->getName());
		}
		log_output($$->getName());
	}
	;
		 
func_definition : type_specifier ID LPAREN parameter_list RPAREN  { insertFunctionToScope($2,$1); } compound_statement {
		grammar_rule_output("func_definition","type_specifier ID LPAREN parameter_list RPAREN compound_statement");
		$$ = new SymbolInfo("","func_definition");
		$$->setName(concatName({$1,$2,$3,$4,$5,$7}));
		log_output($$->getName());
	}
	| type_specifier ID LPAREN error RPAREN  { insertFunctionToScope($2,$1); } compound_statement {
		grammar_rule_output("func_definition","type_specifier ID LPAREN parameter_list RPAREN compound_statement");
		$$ = new SymbolInfo("","func_definition");
		$$->setName(concatName({$1,$2,$3,$5,$7}));
		error_output("Syntax error at func_definition","");
		log_output($$->getName());
	}
	| type_specifier ID LPAREN RPAREN { insertFunctionToScope($2,$1); } compound_statement {
		grammar_rule_output("func_definition","type_specifier ID LPAREN RPAREN compound_statement");
		$$ = new SymbolInfo("","func_definition");
		$$->setName(concatName({$1,$2,$3,$4,$6}));
		log_output($$->getName());
	}
	;				

parameter_list : parameter_list COMMA type_specifier ID {
		grammar_rule_output("parameter_list","parameter_list COMMA type_specifier ID");
		$$ = new SymbolInfo("","parameter_list");
		$$->setName(concatName({$1,$2,$3,$4}));
		$$->setParameterList($1->getParameterList());
		$4->setTypeSpecifier($3->getTypeSpecifier());
		$$->pushParameter($4);
		isVoidTypeSpecifier($3);
		symbolInfoArguments->setParameterList($$->getParameterList());
		log_output($$->getName());
	} 
	| parameter_list COMMA type_specifier {
		grammar_rule_output("parameter_list","parameter_list COMMA type_specifier");
		$$ = new SymbolInfo("","parameter_list");
		$$->setName(concatName({$1,$2,$3}));
		SymbolInfo* nameLessId = new SymbolInfo("","ID");
		nameLessId->setTypeSpecifier($3->getTypeSpecifier());
		$$->setParameterList($1->getParameterList());
		$$->pushParameter(nameLessId);
		isVoidTypeSpecifier($3);
		symbolInfoArguments->setParameterList($$->getParameterList());
		log_output($$->getName());
	}
	| type_specifier ID {
		grammar_rule_output("parameter_list","type_specifier ID");
		$$ = new SymbolInfo("","parameter_list");
		$$->setName(concatName({$1,$2}));
		$2->setTypeSpecifier($1->getTypeSpecifier());
		$$->pushParameter($2);
		isVoidTypeSpecifier($1);
		symbolInfoArguments->setParameterList($$->getParameterList());
		log_output($$->getName());
	}
	| type_specifier {
		grammar_rule_output("parameter_list","type_specifier");
		$$ = new SymbolInfo("","parameter_list");
		$$->setName(concatName({$1}));
		SymbolInfo* nameLessId = new SymbolInfo("","ID");
		nameLessId->setTypeSpecifier($1->getTypeSpecifier());
		$$->pushParameter(nameLessId);
		isVoidTypeSpecifier($1);
		symbolInfoArguments->setParameterList($$->getParameterList());
		log_output($$->getName());
	}
	;

compound_statement : LCURL_ statements RCURL {
		grammar_rule_output("compound_statement","LCURL statements RCURL");
		$$ = new SymbolInfo("","compound_statement");
		$$->setName(concatName({$1,$2,$3}));
		log_output($$->getName());
		symbolTable->printAllScopeTable(logout);
		symbolTable->exitScope();
	}
	| LCURL_ error RCURL {
		grammar_rule_output("compound_statement","LCURL statements RCURL");
		$$ = new SymbolInfo("","compound_statement");
		$$->setName(concatName({$1,$3}));
		log_output($$->getName());
		symbolTable->printAllScopeTable(logout);
		symbolTable->exitScope();
	}
	| LCURL_ RCURL {
		grammar_rule_output("compound_statement","LCURL RCURL");
		$$ = new SymbolInfo("","compound_statement");
		$$->setName(concatName({$1,$2}));
		log_output($$->getName());
		symbolTable->printAllScopeTable(logout);
		symbolTable->exitScope();
	}
	;
 		    
var_declaration : type_specifier declaration_list SEMICOLON {
		grammar_rule_output("var_declaration","type_specifier declaration_list SEMICOLON");
		$$ = new SymbolInfo("","var_declaration");
		$$->setName(concatName({$1,$2,$3}));
		
		if( !isVoidTypeSpecifier($1) ){
			for(auto symbolInfo:$2->getDeclarationList()){
				symbolInfo->setTypeSpecifier($1->getTypeSpecifier());
				
				bool inserted = symbolTable->insertSymbol(symbolInfo);
				if( !inserted ){
					error_output("Multiple declaration of",symbolInfo->getName());
				}
			}
		}
		log_output($$->getName());
	}
	| type_specifier error SEMICOLON {
		grammar_rule_output("var_declaration","type_specifier declaration_list SEMICOLON");
		$$ = new SymbolInfo("","var_declaration");
		$$->setName("");
		error_output("Syntax error at var_declaration","");
		log_output($$->getName());
	}
	;
 		 
type_specifier	: INT {
		grammar_rule_output("type_specifier","INT");
		$$ = new SymbolInfo("","type_specifier");
		$$->setName(concatName({$1}));
		$$->setTypeSpecifier($1->getTypeSpecifier());
		log_output($$->getName());
	}
	| FLOAT {
		$$ = new SymbolInfo("","type_specifier");
		$$->setName(concatName({$1}));
		$$->setTypeSpecifier($1->getTypeSpecifier());
		grammar_rule_output("type_specifier","FLOAT");
		log_output($$->getName());
	}
	| VOID {
		grammar_rule_output("type_specifier","VOID");
		$$ = new SymbolInfo("","type_specifier");
		$$->setName(concatName({$1}));
		$$->setTypeSpecifier($1->getTypeSpecifier());
		log_output($$->getName());
	}
	;
 		
declaration_list : declaration_list COMMA ID {
		grammar_rule_output("declaration_list","declaration_list COMMA ID");
		$$ = new SymbolInfo("","declaration_list");
		$$->setName(concatName({$1,$2,$3}));
		$$->setDeclarationList($1->getDeclarationList());
		$$->pushDeclaration($3);
		log_output($$->getName());
	}
	| declaration_list COMMA ID LTHIRD CONST_INT RTHIRD {
		grammar_rule_output("declaration_list","declaration_list COMMA ID LTHIRD CONST_INT RTHIRD");
		$$ = new SymbolInfo("","declaration_list");
		$$->setName(concatName({$1,$2,$3,$4,$5,$6}));
		$$->setDeclarationList($1->getDeclarationList());
		$3->setArray(true);
		$$->pushDeclaration($3);
		log_output($$->getName());
	}
	| ID {
		grammar_rule_output("declaration_list","ID");
		$$ = new SymbolInfo("","declaration_list");
		$$->setName(concatName({$1}));
		$$->pushDeclaration($1);
		log_output($$->getName());
	}
	| ID LTHIRD CONST_INT RTHIRD {
		grammar_rule_output("declaration_list","ID LTHIRD CONST_INT RTHIRD");
		$$ = new SymbolInfo("","declaration_list");
		$$->setName(concatName({$1,$2,$3,$4}));
		$1->setArray(true);
		$$->pushDeclaration($1);
		log_output($$->getName());
	}
	;
 		  
statements : statement {
		grammar_rule_output("statements","statement");
		$$ = new SymbolInfo("","statements");
		$$->setName(concatName({$1}));
		log_output($$->getName());
	}
	| statements statement {
		grammar_rule_output("statements","statements statement");
		$$ = new SymbolInfo("","statements");
		$$->setName(concatName({$1,$2}));
		log_output($$->getName());
	}
	;
	   
statement : var_declaration {
		grammar_rule_output("statement","var_declaration");
		$$ = new SymbolInfo("","statement");
		$$->setName(concatName({$1}));
		log_output($$->getName());
	}
	| expression_statement {
		grammar_rule_output("statement","expression_statement");
		$$ = new SymbolInfo("","statement");
		$$->setName(concatName({$1}));
		log_output($$->getName());
	}
	| compound_statement {
		grammar_rule_output("statement","compound_statement");
		$$ = new SymbolInfo("","statement");
		$$->setName(concatName({$1}));
		log_output($$->getName());
	}
	| FOR LPAREN expression_statement expression_statement expression RPAREN statement {
		grammar_rule_output("statement","FOR LPAREN expression_statement expression_statement expression RPAREN statement");
		$$ = new SymbolInfo("","statement");
		$$->setName(concatName({$1,$2,$3,$4,$5,$6,$7}));
		log_output($$->getName());
	}
	| IF LPAREN expression RPAREN statement %prec LOWER_THAN_ELSE {
		grammar_rule_output("statement","IF LPAREN expression RPAREN statement");
		$$ = new SymbolInfo("","statement");
		$$->setName(concatName({$1,$2,$3,$4,$5}));
		log_output($$->getName());
	}
	| IF LPAREN expression RPAREN statement ELSE statement {
		grammar_rule_output("statement","IF LPAREN expression RPAREN statement ELSE statement");
		$$ = new SymbolInfo("","statement");
		$$->setName(concatName({$1,$2,$3,$4,$5,$6,$7}));
		log_output($$->getName());
	}
	| WHILE LPAREN expression RPAREN statement {
		grammar_rule_output("statement","WHILE LPAREN expression RPAREN statement");
		$$ = new SymbolInfo("","statement");
		$$->setName(concatName({$1,$2,$3,$4,$5}));
		log_output($$->getName());
	}
	| PRINTLN LPAREN ID RPAREN SEMICOLON {
		grammar_rule_output("statement","PRINTLN LPAREN ID RPAREN SEMICOLON");
		$$ = new SymbolInfo("","statement");
		$$->setName(concatName({$1,$2,$3,$4,$5}));
		if( !symbolTable->lookUpSymbol($3->getName()) ){
			error_output("Undeclared variable",$3->getName());
		}
		log_output($$->getName());
	}
	| RETURN expression SEMICOLON {
		grammar_rule_output("statement","RETURN expression SEMICOLON");
		$$ = new SymbolInfo("","statement");
		$$->setName(concatName({$1,$2,$3}));
		log_output($$->getName());
	}
	;
	  
expression_statement : SEMICOLON {
		grammar_rule_output("expression_statement","SEMICOLON");
		$$ = new SymbolInfo("","expression_statement");
		$$->setName(concatName({$1}));
		log_output($$->getName());
	}			
	| expression SEMICOLON {
		grammar_rule_output("expression_statement","expression SEMICOLON");
		$$ = new SymbolInfo("","expression_statement");
		$$->setName(concatName({$1,$2}));
		$$->setTypeSpecifier($1->getTypeSpecifier());
		log_output($$->getName());
	} 
	| error SEMICOLON {
		yyclearin;
		yyerrok;
		error_output("Syntax error at expression statement","");
		$$ = new SymbolInfo("","expression_statement");
	} 
	;
	  
variable : ID {
		grammar_rule_output("variable","ID");
		$$ = new SymbolInfo("","variable");
		$$->setName(concatName({$1}));
		
		auto searchedSymbol = symbolTable->lookUpSymbol($1->getName());
		if( !searchedSymbol ){
			error_output("Undeclared variable",$1->getName());
			$$->setTypeSpecifier("error");
		}else if(searchedSymbol->isArray()){
			error_output("Type mismatch,",$1->getName()+" is an array");
			$$->setTypeSpecifier("error");
		}else {
			$$->setTypeSpecifier(searchedSymbol->getTypeSpecifier());
			$$->setArray(searchedSymbol->isArray());
		}
		// aaaaa check if ID is a function :/
		log_output($$->getName());
	}
	| ID LTHIRD expression RTHIRD {
		grammar_rule_output("variable","ID LTHIRD expression RTHIRD");
		$$ = new SymbolInfo("","variable");
		$$->setName(concatName({$1,$2,$3,$4}));
		auto searchedSymbol = symbolTable->lookUpSymbol($1->getName());
		if( !searchedSymbol ){
			error_output("Undeclared variable",$1->getName());
		}else if( !searchedSymbol->isArray() ){
			error_output($1->getName(),"not an array");
			$$->setTypeSpecifier(searchedSymbol->getTypeSpecifier());
		}else{
			$$->setTypeSpecifier(searchedSymbol->getTypeSpecifier());
		}
		if( $3->getTypeSpecifier()!= "CONST_INT" and $3->getTypeSpecifier()!= "INT" ){
			error_output("Expression inside third brackets not an integer","");	
		}
		// aaaaa check if ID is a function :/
		log_output($$->getName());
	}
	;

expression : logic_expression {
		grammar_rule_output("expression","logic_expression");
		$$ = new SymbolInfo("","expression");
		$$->setName(concatName({$1}));
		$$->setTypeSpecifier($1->getTypeSpecifier());
		log_output($$->getName());
	}
	| variable ASSIGNOP logic_expression {
		grammar_rule_output("expression","variable ASSIGNOP logic_expression");
		$$ = new SymbolInfo("","expression");
		$$->setName(concatName({$1,$2,$3}));
	
		if( $3->getTypeSpecifier() == "VOID" ){
			error_output("Void function used in expression","");
		}else if( $1->getTypeSpecifier()== "FLOAT" and $3->getTypeSpecifier() == "INT" ){
			// itscool
		}else if( $1->getTypeSpecifier()!=$3->getTypeSpecifier() and $3->getTypeSpecifier()!="error" and $1->getTypeSpecifier()!="error"){
			error_output("Type mismatch","");
		}
		log_output($$->getName());
	}
	;
		
logic_expression : rel_expression {
		grammar_rule_output("logic_expression","rel_expression");
		$$ = new SymbolInfo("","logic_expression");
		$$->setName(concatName({$1}));
		$$->setTypeSpecifier($1->getTypeSpecifier());
		$$->setArray($1->isArray());
		log_output($$->getName());
	}	
	| rel_expression LOGICOP rel_expression {
		grammar_rule_output("logic_expression","rel_expression LOGICOP rel_expression");
		$$ = new SymbolInfo("","logic_expression");
		$$->setName(concatName({$1,$2,$3}));
		$$->setTypeSpecifier("INT");
		log_output($$->getName());
	}
	;
			
rel_expression : simple_expression {
		grammar_rule_output("rel_expression","simple_expression");
		$$ = new SymbolInfo("","rel_expression");
		$$->setName(concatName({$1}));
		$$->setTypeSpecifier($1->getTypeSpecifier());
		$$->setArray($1->isArray());
		log_output($$->getName());
	}
	| simple_expression RELOP simple_expression	{
		grammar_rule_output("rel_expression","simple_expression RELOP simple_expression");
		$$ = new SymbolInfo("","rel_expression");
		$$->setName(concatName({$1,$2,$3}));
		if( $1->getTypeSpecifier() == "VOID" or $3->getTypeSpecifier() == "VOID" ){
			error_output("Void function used in expression","");
			$$->setTypeSpecifier("error");
		}else{
			$$->setTypeSpecifier("INT");
		}
		log_output($$->getName());
	}
	;
				
simple_expression : term {
		grammar_rule_output("simple_expression","term");
		$$ = new SymbolInfo("","simple_expression");
		$$->setName(concatName({$1}));
		$$->setTypeSpecifier($1->getTypeSpecifier());
		$$->setArray($1->isArray());
		log_output($$->getName());
	}
	| simple_expression ADDOP term {
		grammar_rule_output("simple_expression","simple_expression ADDOP term");
		$$ = new SymbolInfo("","simple_expression");
		$$->setName(concatName({$1,$2,$3}));
		$$->setTypeSpecifier( type_cast($1,$3) );
		if( $3->getTypeSpecifier() == "VOID" ){
			error_output("Void function used in expression","");
		}
		log_output($$->getName());
	}
	;
					
term :	unary_expression {
		grammar_rule_output("term","unary_expression");
		$$ = new SymbolInfo("","term");
		$$->setName(concatName({$1}));
		$$->setTypeSpecifier($1->getTypeSpecifier());
		$$->setArray($1->isArray());
		log_output($$->getName());
	}
	|  term MULOP unary_expression {
		grammar_rule_output("term","term MULOP unary_expression");
		$$ = new SymbolInfo("","term");
		$$->setName(concatName({$1,$2,$3}));
		$$->setTypeSpecifier( type_cast($1,$3) );
		if( $3->getTypeSpecifier() == "VOID" ){
			error_output("Void function used in expression","");
		}else if( $2->getName() == "%" and $3->getName() == "0" ){
			error_output("Modulus by Zero","");
			$$->setTypeSpecifier("error");
		}else if($2->getName() == "%" and ( $1->getTypeSpecifier() != "INT" or $3->getTypeSpecifier() != "INT") ){
			error_output("Non-Integer operand on modulus operator","");
			$$->setTypeSpecifier("error");
		}
		log_output($$->getName());
	}
	;

unary_expression : ADDOP unary_expression {
		grammar_rule_output("unary_expression","ADDOP unary_expression");
		$$ = new SymbolInfo("","unary_expression");
		$$->setName(concatName({$1,$2}));
		if( $2->getTypeSpecifier() == "VOID" ){
			error_output("Void function used in expression","");
			$$->setTypeSpecifier("error");
		}else{
			$$->setTypeSpecifier($2->getTypeSpecifier());
		}
		log_output($$->getName());
	} 
	| NOT unary_expression {
		grammar_rule_output("unary_expression","NOT unary_expression");
		$$ = new SymbolInfo("","unary_expression");
		$$->setName(concatName({$1,$2}));
		
		if( $2->getTypeSpecifier() == "VOID" ){
			error_output("Void function used in expression","");
			$$->setTypeSpecifier("error");
		}else{
			$$->setTypeSpecifier("INT");
		}
		log_output($$->getName());
	}
	| factor {
		grammar_rule_output("unary_expression","factor");
		$$ = new SymbolInfo("","unary_expression");
		$$->setName(concatName({$1}));
		$$->setTypeSpecifier($1->getTypeSpecifier());
		$$->setArray($1->isArray());
		log_output($$->getName());
	}
	;
	
factor : variable {
		grammar_rule_output("factor","variable");
		$$ = new SymbolInfo("","factor");
		$$->setName(concatName({$1}));
		$$->setTypeSpecifier($1->getTypeSpecifier());
		$$->setArray($1->isArray());
		log_output($$->getName());
	}
	| ID LPAREN argument_list RPAREN {
		grammar_rule_output("factor","ID LPAREN argument_list RPAREN");
		$$ = new SymbolInfo("","factor");
		$$->setName(concatName({$1,$2,$3,$4}));
		auto searchedSymbol = symbolTable->lookUpSymbol($1->getName());
		if( !searchedSymbol ){
			error_output("Undeclared function",$1->getName());
		}else{
			$$->setTypeSpecifier(searchedSymbol->getTypeSpecifier());
			if( !searchedSymbol->isFunctionDeclaration() and !searchedSymbol->isFunctionDefinition()){
				error_output($1->getName(),"is not a function");
			}else if( $3->getParameterList().size()!= searchedSymbol->getParameterList().size()){
				error_output("Total number of arguments mismatch in function",$1->getName());
			}else{
				auto callerParameterList = $3->getParameterList();
				auto calledParameterList = searchedSymbol->getParameterList();
				for(int i=0;i<callerParameterList.size();i++){
					if( callerParameterList[i]->getTypeSpecifier()!= calledParameterList[i]->getTypeSpecifier()){
						error_output(to_string(i+1)+"th argument mismatch in function",$1->getName());
					}
					if( callerParameterList[i]->isArray() and !calledParameterList[i]->isArray() ){
						error_output("Type mismatch,",callerParameterList[i]->getName()+" is an array");
					}else if( !callerParameterList[i]->isArray() and calledParameterList[i]->isArray() ){
						error_output("Type mismatch,",callerParameterList[i]->getName()+" is not an array");
					}
				}
			}
		}
			
		log_output($$->getName());
	}
	| LPAREN expression RPAREN {
		grammar_rule_output("factor","LPAREN expression RPAREN");
		$$ = new SymbolInfo("","factor");
		$$->setName(concatName({$1,$2,$3}));
		$$->setTypeSpecifier($1->getTypeSpecifier());
		log_output($$->getName());
	}
	| CONST_INT {
		grammar_rule_output("factor","CONST_INT");
		$$ = new SymbolInfo("","factor");
		$$->setName(concatName({$1}));
		$$->setTypeSpecifier("INT");
		log_output($$->getName());
	}
	| CONST_FLOAT {
		grammar_rule_output("factor","CONST_FLOAT");
		$$ = new SymbolInfo("","factor");
		$$->setName(concatName({$1}));
		$$->setTypeSpecifier("FLOAT");
		log_output($$->getName());
	}
	| variable INCOP {
		grammar_rule_output("factor","variable INCOP");
		$$ = new SymbolInfo("","factor");
		$$->setName(concatName({$1,$2}));
		if( $1->getTypeSpecifier() == "VOID" ){
			error_output("Void function used in expression","");
			$$->setTypeSpecifier("error");
		}else{
			$$->setTypeSpecifier($1->getTypeSpecifier());
		}
		
		log_output($$->getName());
	}
	| variable DECOP {
		grammar_rule_output("factor","variable DECOP");
		$$ = new SymbolInfo("","factor");
		$$->setName(concatName({$1,$2}));
		if( $1->getTypeSpecifier() == "VOID" ){
			error_output("Void function used in expression","");
			$$->setTypeSpecifier("error");
		}else{
			$$->setTypeSpecifier($1->getTypeSpecifier());
		}
		log_output($$->getName());
	}
	;

argument_list : arguments {
		grammar_rule_output("argument_list","arguments");
		$$ = new SymbolInfo("","argument_list");
		$$->setName(concatName({$1}));
		$$->setParameterList($1->getParameterList());
		log_output($$->getName());
	}
	| arguments error {
		grammar_rule_output("argument_list","arguments");
		yyclearin;
		yyerrok;
		error_output("Syntax error at arguments","");
		$$ = new SymbolInfo("","argument_list");
		$$->setName(concatName({$1}));
		$$->setParameterList($1->getParameterList());
		log_output($$->getName());
	}
	| {
		grammar_rule_output("argument_list","");
		$$ = new SymbolInfo("","argument_list");
		log_output($$->getName());
	}
	;
	
arguments : arguments COMMA logic_expression {
		grammar_rule_output("arguments","arguments COMMA logic_expression");
		$$ = new SymbolInfo("","arguments");
		$$->setName(concatName({$1,$2,$3}));
		$$->setParameterList($1->getParameterList());
		$$->pushParameter($3);
		log_output($$->getName());
	}
	| logic_expression {
		grammar_rule_output("arguments","logic_expression");
		$$ = new SymbolInfo("","arguments");
		$$->setName(concatName({$1}));
		$$->pushParameter($1);
		log_output($$->getName());
	}
	;

LCURL_ : LCURL {
	$$ = $1;
	symbolTable->enterScope();
	for(auto symbolInfo:symbolInfoArguments->getParameterList()){
		if( symbolInfo->getName() == "" ) continue;
		if( symbolInfo->getTypeSpecifier() == "VOID" )
			symbolInfo->setTypeSpecifier("error");
		bool inserted = symbolTable->insertSymbol(symbolInfo);
		if( !inserted ){
			error_output("Multiple declaration of",symbolInfo->getName()+" in parameter");
		}
	}
	symbolInfoArguments->setParameterList({});
}


%%
int main(int argc,char *argv[]){
	FILE *fp;

	if((fp=fopen(argv[1],"r"))==NULL){
		printf("Cannot Open Input File.\n");
		exit(1);
	}

	logout.open("log.txt");
	errout.open("error.txt");

	yyin=fp;
	yyparse();
	
	symbolTable->printAllScopeTable(logout);

	logout<<"Total lines: "<<global_line_count<<endl;
    logout<<"Total errors: "<<error_count<<endl;

	fclose(yyin);
 	logout.close();
	errout.close();
	return 0;
}