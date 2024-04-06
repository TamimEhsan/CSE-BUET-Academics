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
ofstream codeout;
ofstream optout;


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
void log_output(string logg,string code){
	logout<<logg<<"\n\n";
	logout<<code<<"\n\n";

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

string currentFunction;

void insertFunctionToScope(SymbolInfo* functionName,SymbolInfo* typeSpecifier){
	functionName->setTypeSpecifier(typeSpecifier->getTypeSpecifier());
	functionName->setParameterList(symbolInfoArguments->getParameterList());
	functionName->setFunctionDefinition(true);
	//symbolInfoArguments->setParameterList({});
	currentFunction = functionName->getName();
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

// intermediate code generation

bool hasMain = false;

vector<string> globalVariables;

int LABEL_COUNTER = 0;

int getLabelCounter(){
	
	return LABEL_COUNTER;
}
string newLabel(){
	LABEL_COUNTER++;
	return "label"+to_string(LABEL_COUNTER);
}
string getOpcode(string op){
	string opcode = "";
	if(op == "<") opcode ="JL";
	else if(op == ">") opcode ="JG";
	else if(op == ">=") opcode ="JGE";
	else if(op == "<=") opcode ="JLE";
	else if(op == "==") opcode ="JE";
	else if(op == "!=") opcode ="JNE";
	return opcode;
}

vector<string> get3address(string code){


	string stripped = code;
	while(stripped[stripped.size()-1] == ' ' or stripped[stripped.size()-1] == '\t' ) stripped.pop_back();
	reverse(stripped.begin(),stripped.end());
	while(stripped[stripped.size()-1] == ' ' or stripped[stripped.size()-1] == '\t' ) stripped.pop_back();
	reverse(stripped.begin(),stripped.end());

	vector<string> codes,codes2;
	vector<string> ret;
	stringstream ss(stripped);
 
    while (ss.good()) {
        string substr;
        getline(ss, substr, ' ');
        codes.push_back(substr);
    }
	if( codes.size()>0 ) ret.push_back(codes[0]);
	else ret.push_back("");
	if( codes.size()>1 ){
		stringstream ss(codes[1]);
		while (ss.good()) {
			string substr;
			getline(ss, substr, ',');
			codes2.push_back(substr);
		}	
	}
	if( codes2.size() == 0 ) {
		ret.push_back("");ret.push_back("");
	}else if( codes2.size() == 1 ){
		ret.push_back(codes2[0]);ret.push_back("");
	}else{
		ret.push_back(codes2[0]);
		ret.push_back(codes2[1]);
	}
	ret.push_back(code);
	// cout<<ret[0]<<" | "<<ret[1]<<" | "<<ret[2]<<endl;
	return ret;

}
void optimizeCode(string code){
	// removing redundant move T - T
	vector<string> codes;
	stringstream ss(code);
	vector<vector<string>> optimized;
 
    while (ss.good()) {
        string substr;
        getline(ss, substr, '\n');
        codes.push_back(substr);
    }
	for(auto code:codes) get3address(code);
	int lines = codes.size();
	// cout<<"debug line count::"<<lines<<endl;

	vector<string> prevthadd = {"","",""};
	for(int i=0;i<lines;i++){
		if( codes[i][0] == ';' ){
			auto thadd = get3address(codes[i]);
			optimized.push_back(thadd);
			continue;
		}

		
		vector<string> thadd = get3address(codes[i]);
		if( optimized.size() == 0 ){
			optimized.push_back(thadd);
			continue;
		}

	//	cout<<thadd[1]<<"="<<prevthadd[1]<<" "<<(thadd[1] == prevthadd[1])<<" || "<<thadd[2]<<"="<<prevthadd[2]<<" "<<(thadd[2] == prevthadd[2])<<endl;
		auto prevthadd = optimized.back();
		if( thadd[0] == "MOV" and prevthadd[0] == "MOV" ){
			if( thadd[1] == prevthadd[1] and thadd[2] == prevthadd[2] ){
				cout<<"optimized :) "<<endl;
			}else if(thadd[1] == prevthadd[2] and thadd[2] == prevthadd[1]){
				cout<<"optimized :) "<<endl;
			}else{
				optimized.push_back(thadd);
			}
		}else if( thadd[0] == "POP" ){
			if( prevthadd[0] == "PUSH" ){
				cout<<"optimized POP :) "<<endl;
				optimized.pop_back();
			}else{
				
				optimized.push_back(thadd);
			}
		}else{
			optimized.push_back(thadd);
		
		}

	}
	for(auto thadd:optimized){
		optout<<thadd[3]<<endl;
	}
}

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

		if(!hasMain){
			error_output("undefined reference to main","");
		}

		if(error_count == 0){
			$$->code = $1->code;
			codeout<<".MODEL SMALL\n.STACK 1000H\n.DATA\n\tFIXED_POINT_MULTIPLIER DW 64H\n\tCR EQU 0Dh\n\tLF EQU 0Ah\n\tNEWLINEM DB CR,LF,'$'\n\tTEN DW 10\n";
			optout<<".MODEL SMALL\n.STACK 1000H\n.DATA\n\tFIXED_POINT_MULTIPLIER DW 64H\n\tCR EQU 0Dh\n\tLF EQU 0Ah\n\tNEWLINEM DB CR,LF,'$'\n\tTEN DW 10\n";
			for(auto variable:globalVariables){
				codeout<<'\t'<<variable<<" DW 0\n";
				optout<<'\t'<<variable<<" DW 0\n";
			}
			codeout<<"\n\n\nNEWLINE PROC \n\t\n\tPUSH AX\n\tPUSH DX\n\t\n\tLEA DX, NEWLINEM\n\tMOV AH,9\n\tINT 21h\n\t\n\tPOP DX\n\tPOP AX \n\tRET\n   \nNEWLINE ENDP\n\nPRINTNUMBER PROC\n\tPUSH CX\n\tMOV CX,0   \n\t\n\tCMP AX,0\t\t\t \n\tJG PRINTNUMBER_START \n\t\n\tCMP AX,0\n\tJNE NOT_ZERO\n\tMOV DX,0\n\tADD DL,'0'\n\tMOV AH, 02H\n\tINT 21H\nCALL NEWLINE \n\tPOP CX  \n\tRET\n\t\n\t\n\tNOT_ZERO:\n\tPUSH AX\n\tMOV DX,'-'\n\tMOV AH, 02H\n\tINT 21H \n\tPOP AX  \n\tNEG AX\n\t\n\tPRINTNUMBER_START:\n\tCMP AX,0\n\tJE PRINTNUMBER_END \n\t\n\tXOR DX, DX\n\tDIV TEN\n\tADD DL, '0'\n\tPUSH DX\n\tINC CX\n\tJMP PRINTNUMBER_START\n\t\n\tPRINTNUMBER_END:\n\t\n\tPRINTNUMBER_LOOP:\n\t\t\n\t\tPOP DX\n\t\tMOV AH, 02H\n\t\tINT 21H\n\t\n\tLOOP PRINTNUMBER_LOOP\nCALL NEWLINE \n\tPOP CX\n\tRET\n\t\nPRINTNUMBER ENDP\n\n";
			optout<<"\n\n\nNEWLINE PROC \n\t\n\tPUSH AX\n\tPUSH DX\n\t\n\tLEA DX, NEWLINEM\n\tMOV AH,9\n\tINT 21h\n\t\n\tPOP DX\n\tPOP AX \n\tRET\n   \nNEWLINE ENDP\n\nPRINTNUMBER PROC\n\tPUSH CX\n\tMOV CX,0   \n\t\n\tCMP AX,0\t\t\t \n\tJG PRINTNUMBER_START \n\t\n\tCMP AX,0\n\tJNE NOT_ZERO\n\tMOV DX,0\n\tADD DL,'0'\n\tMOV AH, 02H\n\tINT 21H\nCALL NEWLINE \n\tPOP CX  \n\tRET\n\t\n\t\n\tNOT_ZERO:\n\tPUSH AX\n\tMOV DX,'-'\n\tMOV AH, 02H\n\tINT 21H \n\tPOP AX  \n\tNEG AX\n\t\n\tPRINTNUMBER_START:\n\tCMP AX,0\n\tJE PRINTNUMBER_END \n\t\n\tXOR DX, DX\n\tDIV TEN\n\tADD DL, '0'\n\tPUSH DX\n\tINC CX\n\tJMP PRINTNUMBER_START\n\t\n\tPRINTNUMBER_END:\n\t\n\tPRINTNUMBER_LOOP:\n\t\t\n\t\tPOP DX\n\t\tMOV AH, 02H\n\t\tINT 21H\n\t\n\tLOOP PRINTNUMBER_LOOP\nCALL NEWLINE \n\tPOP CX\n\tRET\n\t\nPRINTNUMBER ENDP\n\n";
			codeout<<$$->code<<endl;
			optimizeCode($$->code);
			codeout<<"END main\n";
			optout<<"END main\n";
		}
	}
	;

program : program unit {
		grammar_rule_output("program","program unit");
		$$ = new SymbolInfo("","program");
		$$->setName(concatName({$1,$2}));
		log_output($$->getName());

		$$->code = $1->code+$2->code;
	}
	| unit {
		grammar_rule_output("program","unit");
		$$ = new SymbolInfo("","program");
		$$->setName(concatName({$1}));
		log_output($$->getName());

		$$->code = $1->code;
	}
	;
	
unit : var_declaration {
		grammar_rule_output("unit","var_declaration");
		$$ = new SymbolInfo("","unit");
		$$->setName(concatName({$1}));
		log_output($$->getName());

		$$->code = $1->code;
	}
	| func_declaration {
		grammar_rule_output("unit","func_declaration");
		$$ = new SymbolInfo("","unit");
		$$->setName(concatName({$1}));
		log_output($$->getName());

		$$->code = $1->code;	
	}
	| func_definition{
		grammar_rule_output("unit","func_definition");
		$$ = new SymbolInfo("","unit");
		$$->setName(concatName({$1}));
		log_output($$->getName());

		$$->code = $1->code;
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
		$2->setParameterList($5->getParameterList());
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

		$$->code = "\n\n"+$2->getName() + " PROC\n";
		$$->code += "\tPUSH BP\n\tMOV BP,SP\n";

		if($2->getName()=="main"){
			hasMain = true;
			$$->code += "\tMOV AX, @DATA\n\tMOV DS, AX\n\n";
		}
		$$->code += $4->code+"\n";
		$$->code += $7->code+"\n";
		$$->code+=$2->getName()+"_exit:\n";
		$$->code +="\tADD SP,"+to_string(-$7->stackOffset)+"\n";
		$$->code += "\tPOP BP\n";
		
		if($2->getName()=="main"){
			$$->code+="\tMOV AH,4ch\nINT 21h\n\n";
		}else{
			$$->code += "\tRET\n";
		}
		$$->code += "\t"+$2->getName()+" ENDP\n";
	
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

		$$->code = "\n\n"+$2->getName()+" PROC\n";
		$$->code += "\tPUSH BP\n\tMOV BP,SP\n";
		if($2->getName()=="main"){
			hasMain = true;
			$$->code += "\tMOV AX,@DATA\n\tMOV DS,AX\n\n";
		}

		$$->code += $6->code+"\n";
		$$->code+=$2->getName()+"_exit:\n";
		$$->code +="\tADD SP,"+to_string(-$6->stackOffset)+"\n";
		$$->code += "\tPOP BP\n";
		if( $2->getName() == "main" )
			$$->code+="\tMOV AH,4ch\nINT 21h\n\n";
		else 
			$$->code += "RET\n";
		
		$$->code += $2->getName()+" ENDP\n";
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

		$$->code = $2->code;
        $$->code += $3->code;
		$$->stackOffset = symbolTable->getCurrentScopeTable()->stackOffset; 
		
		symbolTable->printAllScopeTable(logout);
		symbolTable->exitScope();

		log_output($$->getName());log_output($$->code);
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
		
		string comment = $$->getName();
		std::replace( comment.begin(), comment.end(), '\n', ' '); // replace all 'x' to 'y'
		$$->code += "; "+comment+"\n";

		if( !isVoidTypeSpecifier($1) ){
			for(auto symbolInfo:$2->getDeclarationList()){
				symbolInfo->setTypeSpecifier($1->getTypeSpecifier());
				
				bool inserted = symbolTable->insertSymbol(symbolInfo);
				if( !inserted ){
					error_output("Multiple declaration of",symbolInfo->getName());
				}else if(symbolTable->getCurrentScopeTable()->getUid() == "1"){
					symbolInfo->stackOffset = 0;
					globalVariables.push_back(symbolInfo->getName());
				}else{
					if( symbolInfo->isArray() )
						$$->code+="\tSUB SP,"+to_string(2*symbolInfo->getSize())+"\n";
					else
						$$->code+="\tSUB SP,2\n";
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
		
		
		string s = $5->getName();
		// create an input stream with your string.
		istringstream is(s);
		int i;
		// use is like an input stream
		is >> i;

		$3->setSize(i);
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

		string s = $3->getName();
		// create an input stream with your string.
		istringstream is(s);
		int i;
		// use is like an input stream
		is >> i;
		$1->setSize(i);
	}
	;
 		  
statements : statement {
		grammar_rule_output("statements","statement");
		$$ = new SymbolInfo("","statements");
		$$->setName(concatName({$1}));
		log_output($$->getName());

		$$->code = $1->code;
	}
	| statements statement {
		grammar_rule_output("statements","statements statement");
		$$ = new SymbolInfo("","statements");
		$$->setName(concatName({$1,$2}));
		log_output($$->getName());

		$$->code = $1->code + '\n' + $2->code;
	}
	;
	   
statement : var_declaration {
		grammar_rule_output("statement","var_declaration");
		$$ = new SymbolInfo("","statement");
		$$->setName(concatName({$1}));
		log_output($$->getName());

		$$->code = $1->code;
	}
	| expression_statement {
		grammar_rule_output("statement","expression_statement");
		$$ = new SymbolInfo("","statement");
		$$->setName(concatName({$1}));
		
		string comment = $$->getName();
		std::replace( comment.begin(), comment.end(), '\n', ' '); // replace all 'x' to 'y'
		$$->code += "; "+comment+"\n";
		$$->code += $1->code;
		log_output($$->getName());
		log_output($$->code);

	}
	| compound_statement {
		grammar_rule_output("statement","compound_statement");
		$$ = new SymbolInfo("","statement");
		$$->setName(concatName({$1}));
		log_output($$->getName());

		$$->code = $1->code;
	}
	| FOR LPAREN expression_statement expression_statement expression RPAREN statement {
		grammar_rule_output("statement","FOR LPAREN expression_statement expression_statement expression RPAREN statement");
		$$ = new SymbolInfo("","statement");
		$$->setName(concatName({$1,$2,$3,$4,$5,$6,$7}));

		string comment = $$->getName();
		std::replace( comment.begin(), comment.end(), '\n', ' '); // replace all 'x' to 'y'
		$$->code += "; "+comment+"\n";

		//string label = to_string( getLabelCounter() );
		string label_loop = newLabel();//"for_loop"+label;
		string label_end = newLabel();//"for_end"+label;

		$$->code+=$3->code;
		$$->code+=label_loop+":\n";
		$$->code+=$4->code;
		$$->code+="\tJCXZ "+label_end+"\n";
		$$->code+=$7->code;
		$$->code+=$5->code;
		$$->code+="\tJMP "+label_loop+"\n";
		$$->code+=label_end+":\n";

		log_output($$->getName());log_output($$->code);
	}
	| IF LPAREN expression RPAREN statement %prec LOWER_THAN_ELSE {
		grammar_rule_output("statement","IF LPAREN expression RPAREN statement");
		$$ = new SymbolInfo("","statement");
		$$->setName(concatName({$1,$2,$3,$4,$5}));
		log_output($$->getName());

		string comment = $$->getName();
		std::replace( comment.begin(), comment.end(), '\n', ' '); // replace all 'x' to 'y'
		$$->code += "; "+comment+"\n";

	//	string label = to_string(getLabelCounter());
		string label_false = newLabel();//"if_false" +label;
		string label_true = newLabel();//"if_true" +label;

		$$->code += $3->code+"\n";
		$$->code += "\tJCXZ "+label_false+"\n"; //l1
		$$->code += $5->code+"\n";
		$$->code += "\tJMP "+label_true+"\n"; //l2
		$$->code += label_false+":\n"; //
		$$->code += label_true+":\n";
	}
	| IF LPAREN expression RPAREN statement ELSE statement {
		grammar_rule_output("statement","IF LPAREN expression RPAREN statement ELSE statement");
		$$ = new SymbolInfo("","statement");
		$$->setName(concatName({$1,$2,$3,$4,$5,$6,$7}));
		log_output($$->getName());

		string comment = $$->getName();
		std::replace( comment.begin(), comment.end(), '\n', ' '); // replace all 'x' to 'y'
		$$->code += "; "+comment+"\n";

		//string label = to_string(getLabelCounter());
		string label_false = newLabel();//"if_false" +label;
		string label_true = newLabel();//"if_true" +label;

		$$->code += $3->code+"\n";
		$$->code += "\tJCXZ "+label_false+"\n"; //l1
		$$->code += $5->code+"\n";
		$$->code += "\tJMP "+label_true+"\n"; //l2
		$$->code += label_false+":\n"; // xxx
		$$->code += $7->code+"\n";
		$$->code += label_true+":\n";
	}
	| WHILE LPAREN expression RPAREN statement {
		grammar_rule_output("statement","WHILE LPAREN expression RPAREN statement");
		$$ = new SymbolInfo("","statement");
		$$->setName(concatName({$1,$2,$3,$4,$5}));
		log_output($$->getName());

		string comment = $$->getName();
		std::replace( comment.begin(), comment.end(), '\n', ' '); // replace all 'x' to 'y'
		$$->code += "; "+comment+"\n";

		
		string label_loop =newLabel();
		string label_end = newLabel();

		$$->code+=label_loop+":\n";
		$$->code+=$3->code;
		$$->code+="\tJCXZ "+label_end+"\n";
		$$->code+=$5->code;
		$$->code+="\tJMP "+label_loop+"\n";
		$$->code+=label_end+":\n";
	}
	| PRINTLN LPAREN ID RPAREN SEMICOLON {
		grammar_rule_output("statement","PRINTLN LPAREN ID RPAREN SEMICOLON");
		$$ = new SymbolInfo("","statement");
		$$->setName(concatName({$1,$2,$3,$4,$5}));

		string comment = $$->getName();
		std::replace( comment.begin(), comment.end(), '\n', ' '); // replace all 'x' to 'y'
		$$->code += "; "+comment+"\n";

		if( !symbolTable->lookUpSymbol($3->getName()) ){
			error_output("Undeclared variable",$3->getName());
		}else{
			////////////
			auto searchedSymbol = symbolTable->lookUpSymbol($3->getName());
		
			if( !searchedSymbol ){
				error_output("Undeclared variable",$3->getName());
				
			}else if(searchedSymbol->isArray()){
				error_output("Type mismatch,",$3->getName()+" is an array");
				$$->setTypeSpecifier("error");
			}else {
				$$->stackOffset =  searchedSymbol->stackOffset;
				if( $$->stackOffset != 0 ) $$->varName = to_string($$->stackOffset)+"[BP]"; // actual variable
				else $$->varName = $3->getName(); // global variable

			//	$$->code += "\tMOV AX,"+$$->varName+"\n";
				$$->code += "\tMOV AX,"+$$->varName+"\n\tCALL PRINTNUMBER\n";

			}
			///////////	
		}
		log_output($$->getName());
	}
	| RETURN expression SEMICOLON {
		grammar_rule_output("statement","RETURN expression SEMICOLON");
		$$ = new SymbolInfo("","statement");
		$$->setName(concatName({$1,$2,$3}));
		log_output($$->getName());

		string comment = $$->getName();
		std::replace( comment.begin(), comment.end(), '\n', ' '); // replace all 'x' to 'y'
		$$->code += "; "+comment+"\n";

		$$->code += $2->code;
		$$->code +="\tMOV DX,CX\n\tJMP "+currentFunction+"_exit\n";
	}
	;
	  
expression_statement : SEMICOLON {
		grammar_rule_output("expression_statement","SEMICOLON");
		$$ = new SymbolInfo("","expression_statement");
		$$->setName(concatName({$1}));
		log_output($$->getName());
		$$->code+=$1->code;
	}			
	| expression SEMICOLON {
		grammar_rule_output("expression_statement","expression SEMICOLON");
		$$ = new SymbolInfo("","expression_statement");
		$$->setName(concatName({$1,$2}));
		$$->setTypeSpecifier($1->getTypeSpecifier());
		log_output($$->getName());

		$$->code = $1->code;
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
			$$->stackOffset =  searchedSymbol->stackOffset;
			// cout<<"debugg3:: "<<$$->stackOffset<<endl;
			if( $$->stackOffset != 0 ) $$->varName = to_string($$->stackOffset)+"[BP]"; // actual variable
            else $$->varName = $1->getName(); // global variable

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
		}else{
			// use bx for index
			$$->code+=$3->code;
			$$->code+="\tMOV BX,CX\n";
			$$->code+="\tSHL BX,1\n";
			$$->code+="\tNEG BX\n";
			$$->code+="\tADD BX,"+to_string(searchedSymbol->stackOffset)+"\n";
			$$->code+="\tADD BX,BP\n";
			$$->varName = "[BX]";
		}
		// aaaaa check if ID is a function :/
		log_output($$->getName());
		log_output($$->code);
	}
	;

expression : logic_expression {
		grammar_rule_output("expression","logic_expression");
		$$ = new SymbolInfo("","expression");
		$$->setName(concatName({$1}));
		$$->setTypeSpecifier($1->getTypeSpecifier());
		
		$$->code = $1->code;
		log_output($$->getName());
		log_output($$->code);
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
		}else{
			$$->code += $1->code;
			$$->code += $3->code;
			$$->code += "\tMOV "+$1->varName+",CX\n";
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

		$$->code = $1->code;
	}	
	| rel_expression LOGICOP rel_expression {
		grammar_rule_output("logic_expression","rel_expression LOGICOP rel_expression");
		$$ = new SymbolInfo("","logic_expression");
		$$->setName(concatName({$1,$2,$3}));
		$$->setTypeSpecifier("INT");
		log_output($$->getName());

		
		string labelEnd = newLabel();
		$$->code += $1->code;
		$$->code += "\tCMP CX,0\n";
		if( $2->getName() == "&&" )
			$$->code += "\tJCXZ "+labelEnd+"\n";
		else
			$$->code += "\tJNZ "+labelEnd+"\n";
		$$->code += $3->code;
		$$->code += labelEnd+":\n";
	}
	;
			
rel_expression : simple_expression {
		grammar_rule_output("rel_expression","simple_expression");
		$$ = new SymbolInfo("","rel_expression");
		$$->setName(concatName({$1}));
		$$->setTypeSpecifier($1->getTypeSpecifier());
		$$->setArray($1->isArray());
		log_output($$->getName());

		$$->code = $1->code;
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

			string opcode = getOpcode($2->getName());

			string labelTrue = newLabel();
			string labelFalse = newLabel();
			$$->code+=$1->code ;
			$$->code+="\tPUSH CX\n"; 
			$$->code+=$3->code;
			$$->code+="\tPOP AX\n";
			$$->code+="\tCMP AX,CX\n";
			$$->code+="\t"+opcode+" "+labelTrue+"\n";
			$$->code+="\tMOV CX,0\n";
			$$->code+="\tJMP "+labelFalse+"\n";
			$$->code+=labelTrue+":\n";
			$$->code+="\tMOV CX,1\n";
			$$->code+=labelFalse+":\n";
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

		$$->code = $1->code;
		log_output($$->getName());
	}
	| simple_expression ADDOP  { $1->code+="\tPUSH CX\n"; } term {
		grammar_rule_output("simple_expression","simple_expression ADDOP term");
		$$ = new SymbolInfo("","simple_expression");
		$$->setName(concatName({$1,$2,$4}));
		$$->setTypeSpecifier( type_cast($1,$4) );
		if( $4->getTypeSpecifier() == "VOID" ){
			error_output("Void function used in expression","");
		}else{
			$$->code = $1->code+$4->code;
			if( $2->getName() == "+" )
				$$->code += "\tPOP AX\n\tADD AX,CX\n\tMOV CX,AX\n";
			else
				$$->code += "\tPOP AX\n\tSUB AX,CX\n\tMOV CX,AX\n";
		}
		log_output($$->getName());
		log_output($$->code);
	}
	;
					
term :	unary_expression {
		grammar_rule_output("term","unary_expression");
		$$ = new SymbolInfo("","term");
		$$->setName(concatName({$1}));
		$$->setTypeSpecifier($1->getTypeSpecifier());
		$$->setArray($1->isArray());
		
		$$->code = $1->code;
		log_output($$->getName());
		log_output($$->code);

	}
	|  term MULOP { $1->code +="\tPUSH CX\n"; } unary_expression {
		grammar_rule_output("term","term MULOP unary_expression");
		$$ = new SymbolInfo("","term");
		$$->setName(concatName({$1,$2,$4}));
		$$->setTypeSpecifier( type_cast($1,$4) );
		if( $4->getTypeSpecifier() == "VOID" ){
			error_output("Void function used in expression","");
		}else if( $2->getName() == "%" and $4->getName() == "0" ){
			error_output("Modulus by Zero","");
			$$->setTypeSpecifier("error");
		}else if($2->getName() == "%" and ( $1->getTypeSpecifier() != "INT" or $4->getTypeSpecifier() != "INT") ){
			error_output("Non-Integer operand on modulus operator","");
			$$->setTypeSpecifier("error");
		}else{
			$$->code += $1->code+$4->code;
			if( $2->getName() == "*" )
				$$->code+="\tPOP AX\nIMUL CX\n\tMOV CX,AX\n";
			else if( $2->getName() == "/" )
				$$->code+="\tPOP AX\nCWD\nIDIV CX\n\tMOV CX,AX\n";
			else if( $2->getName() == "%" )
				$$->code+="\tPOP AX\nCWD\nIDIV CX\n\tMOV CX,DX\n";
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
			$$->code+=$2->code;
			if($1->getName() == "-")
				$$->code+="NEG CX\n";
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
			$$->code+=$2->code;
			//string label = to_string( getLabelCounter() );
			string labelEnd =newLabel();// "not_end"+label;
			string labelOne = newLabel();//"not_one"+label;
			$$->code+=$2->code;
			$$->code+="\tJCXZ "+labelOne+"\n";
			$$->code+="\tMOV CX,0\n";
			$$->code+=labelOne+":\n";
			$$->code+="\tMOV CX,1\n";
			$$->code+=labelEnd+":\n";
		}
		log_output($$->getName());
	}
	| factor {
		grammar_rule_output("unary_expression","factor");
		$$ = new SymbolInfo("","unary_expression");
		$$->setName(concatName({$1}));
		$$->setTypeSpecifier($1->getTypeSpecifier());
		$$->setArray($1->isArray());

		$$->code = $1->code;

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
		
		$$->code+=$1->code;
		$$->code += "\tMOV CX,"+$1->varName+"\n";
		log_output($$->code);
		
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
				$$->code +=$3->code+"\tCALL "+$1->getName()+"\n\tMOV CX,DX\n"+"\tADD SP,"+to_string($3->stackOffset)+"\n";
			}
		}
			
		log_output($$->getName());
	}
	| LPAREN expression RPAREN {
		grammar_rule_output("factor","LPAREN expression RPAREN");
		$$ = new SymbolInfo("","factor");
		$$->setName(concatName({$1,$2,$3}));
		$$->setTypeSpecifier($1->getTypeSpecifier());
		
		$$->code = $2->code;
		log_output($$->getName());
		log_output($$->code);
	}
	| CONST_INT {
		grammar_rule_output("factor","CONST_INT");
		$$ = new SymbolInfo("","factor");
		$$->setName(concatName({$1}));
		$$->setTypeSpecifier("INT");
		log_output($$->getName());

		$$->code = "\tMOV CX,"+$1->getName()+"\n";
	}
	| CONST_FLOAT {
		grammar_rule_output("factor","CONST_FLOAT");
		$$ = new SymbolInfo("","factor");
		$$->setName(concatName({$1}));
		$$->setTypeSpecifier("FLOAT");
		log_output($$->getName());

		$$->code = "\tMOV CX,"+$1->getName()+"\n";
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
			$$->code += $1->code;
			$$->code += "\tMOV CX,"+$1->varName+"\n";
			$$->code += "\tINC "+$1->varName+"\n";
			
		}

		log_output($$->getName()); log_output($$->code);
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
			$$->code += "\tMOV CX,"+$1->varName+"\n";
			$$->code += "\t MOV AX,CX\n\tSUB AX,1\n\tMOV "+$1->varName+",AX\n";
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
		$$->code+=$1->code;
		$$->stackOffset = $1->stackOffset;
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

		$$->code+=$1->code+$3->code;
		$$->code+="\tPUSH CX\n";
		$$->stackOffset = $1->stackOffset + 2;
	}
	| logic_expression {
		grammar_rule_output("arguments","logic_expression");
		$$ = new SymbolInfo("","arguments");
		$$->setName(concatName({$1}));
		$$->pushParameter($1);
		log_output($$->getName());

		$$->code+=$1->code;
		$$->code+="\tPUSH CX\n";
		$$->stackOffset = 2;
	}
	;

LCURL_ : LCURL {
	$$ = $1;
	symbolTable->enterScope();
	int stackOffset = 2;
	//for(auto symbolInfo:symbolInfoArguments->getParameterList()){
	for(int i=symbolInfoArguments->getParameterList().size()-1;i>=0;i--){
		auto symbolInfo = symbolInfoArguments->getParameterList()[i];
		if( symbolInfo->getName() == "" ) continue;
		if( symbolInfo->getTypeSpecifier() == "VOID" )
			symbolInfo->setTypeSpecifier("error");
		stackOffset+=2;
		symbolInfo->stackOffset = stackOffset;
		bool inserted = symbolTable->insertSymbol(symbolInfo);
		if( !inserted ){
			stackOffset-=2;
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
	codeout.open("code.asm");
	optout.open("optimized_code.asm");


	yyin=fp;
	yyparse();
	
	symbolTable->printAllScopeTable(logout);

	logout<<"Total lines: "<<global_line_count<<endl;
    logout<<"Total errors: "<<error_count<<endl;

	fclose(yyin);
 	logout.close();
	errout.close();
	codeout.close();
	optout.close();

	return 0;
}