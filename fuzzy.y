%{
#include <cstdio>
#include <iostream>
//#include "Fuzzy/IsTriangle.h"
using namespace std;

int yylex();
extern "C" int yyparse();
extern "C" FILE *yyin;
extern "C" int yylineno;
extern "C" char* yytext;
 
void yyerror(char *s);
%}

%union {
    int ival;
    float fval;
    char *sval;
}

%token VALUES  MEMBERSHIPS OPERATORS MAMDANIRULES SUGENORULES
%token LBRACE RBRACE LPAREN RPAREN

%token TRIANGLE TRAPEZ LTRAPEZ RTRAPEZ BELL ZSHAPE GUAUSSE

%token ANDMULT ORMAX THENMULT AGGPLUS COGDEFUZZ SUGENOCONCLUSION NOTMINUS1

%token NOT AND OR IS OUTPUT INPUT THEN

%token <ival> INT
%token <sval> NAME
%type <fval> number

%type <ival> expression


%%
start:
        expressions;
expressions:
    expressions expression 
    | expression 
    ;
expression:
    VALUES LBRACE coreValues RBRACE
    | MEMBERSHIPS   LBRACE coreMemberships RBRACE
    | OPERATORS LBRACE coreOperators RBRACE
    | MAMDANIRULES  LBRACE coreMamdaniRules RBRACE
    | SUGENORULES LBRACE coreSugenoRules RBRACE
    ;
coreValues:
    INPUT NAME domain { cout<<$2<<endl; }
    | coreValues INPUT NAME domain { cout<<$3<<endl; }
    | coreValues OUTPUT NAME domain  { cout<<$3<<endl; }
    ;
domain:
    number number number number ';'
    ;
number: 
    INT {cout<<$1<<endl;}
    | INT '.' INT
    ;

coreMemberships:
    NAME shape ';'
    | coreMemberships NAME shape ';'
    ;
shape:
    TRIANGLE INT INT INT {cout<< $2<<" " << $3<<" " << $4 <<endl;
                          /*fuzzy::IsTriangle<float> cheap($2,$3,$4);*/}
    | TRAPEZ INT INT INT INT
    | LTRAPEZ 
    | RTRAPEZ
    | BELL
    | ZSHAPE
    | GUAUSSE INT INT
    ;
coreOperators:
    NAME oper ';'   {cout<< $1 <<endl;}
    | coreOperators NAME oper ';'      {cout<< $2 <<endl;}
    ;
oper:
    ANDMULT
    | ORMAX
    | THENMULT
    | AGGPLUS
    | COGDEFUZZ
    | SUGENOCONCLUSION
    | NOTMINUS1
    ;
coreMamdaniRules:
    unaryExp conclusion
    | binaryExp conclusion
    | coreMamdaniRules unaryExp conclusion
    | coreMamdaniRules binaryExp conclusion
    ;
unaryExp:
    unaryOp LPAREN  binaryExp RPAREN
    | unaryOp LPAREN binaryExp RPAREN
    ;
unaryOp:
    NOT
    ;
binaryExp:
    NAME IS NAME oprt NAME IS NAME
    ;
oprt:
    AND
    | OR
    ;
conclusion:
    THEN NAME IS NAME ';'
    ;
coreSugenoRules:
    unaryExp sugenoconclusion
    | binaryExp sugenoconclusion
    | coreMamdaniRules unaryExp sugenoconclusion
    | coreMamdaniRules binaryExp sugenoconclusion

sugenoconclusion:
    THEN INT NAME INT NAME ';'

%%

int main(int argc, char *argv[]) {
    if (argc!= 2) {
        cout <<"Usage: <command> filename"<<endl;
        return 1;
    }
    FILE *myfile = fopen(argv[1], "r");
    if (!myfile) {
        cout << "I can't open "<<argv[1]<< endl;
        return -1;
    }
    yyin = myfile;

    do {
        yyparse();
    } while (!feof(yyin));
    cout <<"parsing completed"<<endl;
    unsigned select;
    std::cout << "1: Mamdani" << std::endl;
    std::cout << "2: Sugeno" << std::endl;
    std::cout << "> ";
    std::cin >> select;
}

void yyerror(char *s) {
    cout << "Parse error: " << s <<endl;
    cout << "token error: " << yytext <<endl;
    exit(-1);
}



