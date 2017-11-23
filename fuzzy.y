%{
#include <cstdio>
#include <iostream>
#include <map>
#include "FuzzyLogicFrameWork/Fuzzy/NotMinus1.h"
#include "FuzzyLogicFrameWork/Fuzzy/AndMin.h"
#include "FuzzyLogicFrameWork/Fuzzy/OrMax.h"
#include "FuzzyLogicFrameWork/Fuzzy/ThenMin.h"
#include "FuzzyLogicFrameWork/Fuzzy/AggPlus.h"
#include "FuzzyLogicFrameWork/Core/CogDefuzz.h"
#include "FuzzyLogicFrameWork/Core/FuzzyFactory.h"
#include "FuzzyLogicFrameWork/Fuzzy/IsGauss.h"
#include "FuzzyLogicFrameWork/Fuzzy/IsTrapezeLeft.h"
#include "FuzzyLogicFrameWork/Fuzzy/IsTrapezeRight.h"
#include "FuzzyLogicFrameWork/Fuzzy/IsTrapeze.h"
#include "FuzzyLogicFrameWork/Fuzzy/IsTriangle.h"
#include "FuzzyLogicFrameWork/Core/ValueModel.h"
#include "FuzzyLogicFrameWork/Fuzzy/ThenSugeno.h"
#include "FuzzyLogicFrameWork/Fuzzy/AggMax.h"
#include "FuzzyLogicFrameWork/Fuzzy/SugenoDefuzz.h"
#include "FuzzyLogicFrameWork/Fuzzy/SugenoConclusion.h"
#include <iterator>
using namespace std;

int yylex();
extern "C" int yyparse();
extern "C" FILE *yyin;
extern "C" int yylineno;
extern "C" char* yytext;

std::map< std::string, Is<float>* > mMemberShips;
std::map< std::string, void* > mOperators;
std::map< std::string, core::ValueModel<float>* > mValues;
std::map <std::string,core::ValueModel<float>* > mOutput;
std::vector <float> vOutPutValues;

fuzzy::NotMinus1<float> opNot;
fuzzy::AndMin<float> opAnd;
fuzzy::OrMax<float> opOr;
fuzzy::ThenMin<float> opThen;
fuzzy::AggPlus<float> opAgg;
core::CogDefuzz<float> opDefuzz;
core::FuzzyFactory<float> f(&opNot,&opAnd,&opOr,&opThen,&opAgg,&opDefuzz);
core::Expression<float> *r = NULL;
core::Expression<float> *fuzzySystem=NULL;


 
void yyerror(char *s);
%}

%union {
    float fval;
    char *sval;
    void* exp;
}

%token VALUES  MEMBERSHIPS OPERATORS MAMDANIRULES SUGENORULES
%token LBRACE RBRACE LPAREN RPAREN

%token TRIANGLE TRAPEZE LTRAPEZE RTRAPEZE BELL ZSHAPE GUAUSSE

%token ANDMULT ANDMIN ORMAX THENMULT THENMIN AGGPLUS COGDEFUZZ SUGDEFUZZ NOTMINUS1

%token NOT AND OR IS OUTPUT INPUT THEN

 
%token <fval> INT
%token <sval> NAME
%type <exp> unaryExp
%type <exp> binaryExp
%type <exp> conclusion
%type <exp> sugenoconclusion



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
    | MAMDANIRULES  LBRACE coreMamdaniRules RBRACE { cout<< ">>>>>>>>>>>Fin tout<<<<<<<<<<<<<<" <<endl;
                                                     fuzzySystem = f.newDefuzz(mOutput.begin()->second, r, 0,30,1);
                                                      cout << mOutput.begin()->first << r <<endl;}
    | SUGENORULES LBRACE coreSugenoRules RBRACE
    ;
coreValues:
    INPUT NAME INT ';' { cout<<$2<<endl;
                     core::ValueModel<float>* pInput = new core::ValueModel<float>($3);
                     mValues[$2] = pInput ;
                      }

    | coreValues INPUT NAME INT ';' { cout<<$3<<endl;
                     core::ValueModel<float>* pInput = new core::ValueModel<float>($4);
                     mValues[$3] = pInput ;}

    | coreValues OUTPUT NAME INT INT INT INT ';' { cout<<$3<<endl;
                                                   core::ValueModel<float>* pOutput = new core::ValueModel<float>($4);
                                                   mOutput[$3] = pOutput ;
                                                   vOutPutValues.push_back($5);
                                                   vOutPutValues.push_back($6);
                                                   vOutPutValues.push_back($7);
                                                 }
    ;

coreMemberships:
    shape ';'
    | coreMemberships shape ';'
    ;
shape:
    NAME TRIANGLE INT INT INT {cout<< $3<<" " << $4<<" " << $5 <<endl;
                          cout<< "triangle declared"<<$1 <<endl;
                          fuzzy::IsTriangle<float>* pTriangle = new fuzzy::IsTriangle<float>($3,$4,$5);
                          mMemberShips[$1] = pTriangle;
                          cout<< "added"<<endl; }
    | NAME TRAPEZE INT INT INT INT {cout<< $3<<" " << $4<<" " << $5 <<endl;
                          fuzzy::IsTrapeze<float> trapeze($3,$4,$5,$6);
                          cout<< "trapez declared"<<endl;
                          mMemberShips[$1] = &trapeze;
                          cout<< "added"<<endl; }
    | NAME LTRAPEZE 
    | NAME RTRAPEZE
    | NAME BELL
    | NAME ZSHAPE
    | NAME GUAUSSE INT INT
    ;
coreOperators:
    oper ';'   
    | coreOperators oper ';'      
    ;
oper:
    NAME ANDMULT  { fuzzy::AndMin<float> opAnd;
                    fuzzy::AndMin<float>* pOpAnd = new fuzzy::AndMin<float>;
                    mOperators[$1] = pOpAnd;
                    f.changeAnd(pOpAnd);
                    cout << $1 <<" declared " <<&opAnd<<endl;}


    | NAME ANDMIN { fuzzy::AndMin<float> opAnd;
                    fuzzy::AndMin<float>* pOpAnd = new fuzzy::AndMin<float>;
                    //fuzzy::AndMin<float>* pOpAnd = &opAnd;
                    mOperators[$1] = pOpAnd;
                    f.changeAnd(pOpAnd);
                    cout << $1 <<" declared " <<&opAnd<<endl;}


    | NAME ORMAX     { fuzzy::OrMax<float> opOr;
                       fuzzy::OrMax<float>* pOpOr = new fuzzy::OrMax<float>;
                       //fuzzy::OrMax<float>* pOpOr = &opOr;
                       mOperators[$1] = pOpOr;
                       f.changeOr(pOpOr);
                       cout << $1 <<"declared" <<endl;}


    | NAME THENMULT      { fuzzy::ThenMin<float> opThen;
                           fuzzy::ThenMin<float>* pThen = new fuzzy::ThenMin<float>;
                           //fuzzy::ThenMin<float>* pThen = &opThen;
                           mOperators[$1] = pThen;
                           f.changeThen(pThen);
                           cout << $1 <<"declared"<<&opThen<<endl;}


    | NAME THENMIN      { fuzzy::ThenMin<float> opThen;
                          fuzzy::ThenMin<float>* pThen = new fuzzy::ThenMin<float>;
                          //fuzzy::ThenMin<float>* pThen = &opThen;
                          mOperators[$1] = pThen;
                          f.changeThen(pThen);
                          cout << $1 <<"declared" <<endl;}


    | NAME AGGPLUS   { fuzzy::AggPlus<float> opAgg;
                       fuzzy::AggPlus<float>* pOpAgg = new fuzzy::AggPlus<float>;
                       //fuzzy::AggPlus<float>* pOpAgg = &opAgg;
                       mOperators[$1] = pOpAgg;
                       f.changeAgg(pOpAgg);
                       cout << $1 <<"declared" <<endl;}


    | NAME COGDEFUZZ     { CogDefuzz<float> opDefuzz;
                           CogDefuzz<float>* pOpDefuzz = new CogDefuzz<float>;
                           //CogDefuzz<float>* pOpDefuzz = &opDefuzz;
                           mOperators[$1] = pOpDefuzz;
                           f.changeDefuzz(pOpDefuzz);
                           cout << $1 <<"declared" <<endl;}


    | NAME SUGDEFUZZ      { fuzzy::SugenoDefuzz<float> opSugDefuzz;
                            mOperators[$1] = &opSugDefuzz;
                            cout << $1 <<"declared" <<endl;}


    | NAME NOTMINUS1     { fuzzy::NotMinus1<float> opNot;
                           fuzzy::NotMinus1<float>* pOpNot = &opNot;
                           mOperators[$1] = pOpNot;
                           cout << $1 <<"declared" <<endl;}
    ;
coreMamdaniRules: 
    unaryExp conclusion { cout<< "executer en 6 l1" <<endl;
                            r = f.newThen((core::Expression<float> *)$1,(core::Expression<float> *)$2); }

    | binaryExp conclusion { cout<< "executer en 6 l2" <<endl;
                              r = f.newThen((core::Expression<float> *)$1,(core::Expression<float> *)$2); }

    | coreMamdaniRules unaryExp conclusion { cout<< "executer en 6 l3" <<endl;
                              r = f.newAgg(r,f.newThen((core::Expression<float> *)$2,(core::Expression<float> *)$3)); }
    | coreMamdaniRules binaryExp conclusion { cout<< "executer en 6 l4" <<endl;
                                                r = f.newAgg(r,f.newThen((core::Expression<float> *)$2,(core::Expression<float> *)$3)); }
    ;

unaryExp:
    NOT LPAREN  binaryExp RPAREN { cout<< "executer en 5" <<endl;}
    | NAME IS NAME 
    ;

binaryExp:
    NAME IS NAME OR NAME IS NAME { cout<< "executer en 3" <<endl;
                                   $$ = f.newOr(f.newIs(mMemberShips[$3],mValues[$1]),f.newIs(mMemberShips[$7],mValues[$5]));
                                  }
    | NAME IS NAME AND NAME IS NAME {cout<<"executer en 3p"<<endl;
                                  $$ = f.newAnd(f.newIs(mMemberShips[$3],mValues[$1]),f.newIs(mMemberShips[$7],mValues[$5]));
                                 }
    ;
conclusion:
    THEN NAME IS NAME ';' { cout<< "executer en 1" <<endl;
                            $$ = f.newIs(mMemberShips[$4],mOutput[$2]);}
    ;

coreSugenoRules:
    unaryExp sugenoconclusion
    | binaryExp sugenoconclusion
    | coreSugenoRules unaryExp sugenoconclusion
    | coreSugenoRules binaryExp sugenoconclusion

sugenoconclusion:
    THEN INT NAME INT NAME ';'

%%

void Mamdani()
{
    

    float s, foo;

    while (true)
    {
        std::cout << "service : ";
        std::cin >> s;
        mValues["service"]->setValue(s);
        std::cout<< "food : ";
        std::cin >> foo;
        mValues["food"]->setValue(foo);
        std::cout<< "tips -> " << fuzzySystem->evaluate() << std::endl;
    }

}

void Sugeno()
{

}
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
    cout <<"Map Operators size:"<< mOperators.size() <<endl;
    cout <<"Map mMemberShips size:"<< mMemberShips.size() <<endl;
    // Iterate through all elements in std::map
    std::map< std::string, Is<float>* >::iterator it = mMemberShips.begin();
    while(it != mMemberShips.end())
    {
        std::cout<<it->first<<" :: "<<it->second<<std::endl;
        it++;
    }
   std::map< std::string, void* >::iterator it1 = mOperators.begin();
    while(it1 != mOperators.end())
    {
        std::cout<<it1->first<<" :: "<<it1->second<<endl;
        it1++;
    }
    unsigned select;
    std::cout << "1: Mamdani" << std::endl;
    std::cout << "2: Sugeno" << std::endl;
    std::cout << "> ";
    std::cin >> select;
    if (select == 1)
        Mamdani();
    else
        Sugeno();
}

void yyerror(char *s) {
    cout << "Parse error: " << s <<endl;
    cout << "token error: " << yytext <<endl;
    cout << "line" << yylineno <<endl;
    exit(-1);
}



