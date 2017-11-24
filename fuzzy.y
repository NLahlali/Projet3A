%{
//Utils
#include <iterator>
#include <cstdio>
#include <iostream>
#include <map>
//Operators
#include "FuzzyLogicFrameWork/Core/ValueModel.h"
#include "FuzzyLogicFrameWork/Fuzzy/ThenSugeno.h"
#include "FuzzyLogicFrameWork/Fuzzy/AggMax.h"
#include "FuzzyLogicFrameWork/Fuzzy/SugenoDefuzz.h"
#include "FuzzyLogicFrameWork/Fuzzy/SugenoConclusion.h"
#include "FuzzyLogicFrameWork/Fuzzy/NotMinus1.h"
#include "FuzzyLogicFrameWork/Fuzzy/AndMin.h"
#include "FuzzyLogicFrameWork/Fuzzy/OrMax.h"
#include "FuzzyLogicFrameWork/Fuzzy/ThenMin.h"
#include "FuzzyLogicFrameWork/Fuzzy/AggPlus.h"
#include "FuzzyLogicFrameWork/Core/CogDefuzz.h"
#include "FuzzyLogicFrameWork/Core/FuzzyFactory.h"
//Shapes
#include "FuzzyLogicFrameWork/Fuzzy/IsGauss.h"
#include "FuzzyLogicFrameWork/Fuzzy/IsTrapezeLeft.h"
#include "FuzzyLogicFrameWork/Fuzzy/IsTrapezeRight.h"
#include "FuzzyLogicFrameWork/Fuzzy/IsTrapeze.h"
#include "FuzzyLogicFrameWork/Fuzzy/IsTriangle.h"
#include "FuzzyLogicFrameWork/Fuzzy/IsZshaped.h"
#include "FuzzyLogicFrameWork/Fuzzy/IsBell.h"



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
fuzzy::SugenoDefuzz<float> opSugDefuzz;
std::vector<float> coef;
std::vector<core::Expression<float>*> rules;
fuzzy::SugenoConclusion<float> opConclusion(&coef);
core::FuzzyFactory<float> f(&opNot,&opAnd,&opOr,&opThen,&opAgg,&opDefuzz,&opSugDefuzz,&opConclusion);
core::Expression<float> *r = NULL;
core::Expression<float> * mamdaniSystem=NULL;
core::Expression<float> * sugenoSystem=NULL;


 
void yyerror(char *s);
%}

%union {
    float fval;
    char *sval;
    void* exp;
}

%token VALUES  MEMBERSHIPS OPERATORS MAMDANIRULES SUGENORULES
%token LBRACE RBRACE LPAREN RPAREN

%token TRIANGLE TRAPEZE LTRAPEZE RTRAPEZE BELL ZSHAPED GAUSS

%token ANDMULT ANDMIN ORMAX THENMULT THENMIN AGGPLUS COGDEFUZZ SUGDEFUZZ NOTMINUS1

%token NOT AND OR IS OUTPUT INPUT THEN OFFSET

 
%token <fval> INT
%token <sval> NAME
%type <exp> unaryExp
%type <exp> binaryExp
%type <exp> conclusion
%type <exp> sugenoconclusion
%type <exp> linearCombinaison




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
    | MAMDANIRULES  LBRACE coreMamdaniRules RBRACE { 
                                                     mamdaniSystem  = f.newDefuzz(mOutput.begin()->second, r, 0,30,1);
                                                      cout << mOutput.begin()->first << r <<endl;
                                                      fuzzy::ThenSugeno<float>* pThen = new fuzzy::ThenSugeno<float>;
                                                      f.changeThen(pThen);
                                                    }
    | SUGENORULES LBRACE coreSugenoRules RBRACE     {
                                                      sugenoSystem = f.newSugeno(&rules);
                                                      cout << rules.size() <<endl;
                                                    }
    ;
coreValues:
    INPUT NAME INT ';' { 
                        cout<<$2<<endl;
                        core::ValueModel<float>* pInput = new core::ValueModel<float>($3);
                        mValues[$2] = pInput ;
                       }

    | coreValues INPUT NAME INT ';' { 
                                      cout<<$3<<endl;
                                      core::ValueModel<float>* pInput = new core::ValueModel<float>($4);
                                      mValues[$3] = pInput ;
                                    }

    | coreValues OUTPUT NAME INT INT INT INT ';' { 
                                                   cout<<$3<<endl;
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
    NAME TRIANGLE INT INT INT {
                                cout<< $3<<" " << $4<<" " << $5 <<endl;
                                cout<< "triangle declared"<<$1 <<endl;
                                fuzzy::IsTriangle<float>* pTriangle = new fuzzy::IsTriangle<float>($3,$4,$5);
                                mMemberShips[$1] = pTriangle;
                                cout<< "added"<<endl; 
                              }
    | NAME TRAPEZE INT INT INT INT {
                                      cout<< $3<<" " << $4<<" " << $5 <<endl;
                                      fuzzy::IsTrapeze<float>* pTrapeze = new fuzzy::IsTrapeze<float>($3,$4,$5,$6);
                                      mMemberShips[$1] = pTrapeze;
                                      cout<< "added"<<endl;
                                    }
    | NAME LTRAPEZE INT INT INT {
                                    fuzzy::IsTrapezeLeft<float>* pLTrapeze = new fuzzy::IsTrapezeLeft<float>($3,$4,$5);
                                    mMemberShips[$1] = pLTrapeze;
                                }

    | NAME RTRAPEZE INT INT INT {
                                    fuzzy::IsTrapezeRight<float>* pRTrapeze = new fuzzy::IsTrapezeRight<float>($3,$4,$5);
                                    mMemberShips[$1] = pRTrapeze;
                                }

    | NAME BELL INT INT INT {
                                fuzzy::IsBell<float>* pTrapeze = new fuzzy::IsBell<float>($3,$4,$5);
                                mMemberShips[$1] = pTrapeze;
                            }

    | NAME ZSHAPED INT INT {
                                fuzzy::IsZshaped<float>* pZ = new fuzzy::IsZshaped<float>($3,$4);
                                mMemberShips[$1] = pZ;
                            }

    | NAME GAUSS INT INT{
                                fuzzy::IsGauss<float>* pTrapeze = new fuzzy::IsGauss<float>($3,$4);
                                mMemberShips[$1] = pTrapeze;
                            }
    ;
coreOperators:
    oper ';'   
    | coreOperators oper ';'      
    ;
oper:
    NAME ANDMULT  { 
                    fuzzy::AndMin<float> opAnd;
                    fuzzy::AndMin<float>* pOpAnd = new fuzzy::AndMin<float>;
                    mOperators[$1] = pOpAnd;
                    f.changeAnd(pOpAnd);
                    cout << $1 <<" declared " <<&opAnd<<endl;
                  }


    | NAME ANDMIN { 
                    fuzzy::AndMin<float> opAnd;
                    fuzzy::AndMin<float>* pOpAnd = new fuzzy::AndMin<float>;
                    mOperators[$1] = pOpAnd;
                    f.changeAnd(pOpAnd);
                    cout << $1 <<" declared " <<&opAnd<<endl;
                  }


    | NAME ORMAX     { 
                       fuzzy::OrMax<float> opOr;
                       fuzzy::OrMax<float>* pOpOr = new fuzzy::OrMax<float>;
                       mOperators[$1] = pOpOr;
                       f.changeOr(pOpOr);
                       cout << $1 <<"declared" <<endl;
                     }


    | NAME THENMULT      { 
                           fuzzy::ThenMin<float> opThen;
                           fuzzy::ThenMin<float>* pThen = new fuzzy::ThenMin<float>;
                           mOperators[$1] = pThen;
                           f.changeThen(pThen);
                           cout << $1 <<"declared"<<&opThen<<endl;}


    | NAME THENMIN      { 
                          fuzzy::ThenMin<float> opThen;
                          fuzzy::ThenMin<float>* pThen = new fuzzy::ThenMin<float>;
                          mOperators[$1] = pThen;
                          f.changeThen(pThen);
                          cout << $1 <<"declared" <<endl;}


    | NAME AGGPLUS   { 
                       fuzzy::AggPlus<float> opAgg;
                       fuzzy::AggPlus<float>* pOpAgg = new fuzzy::AggPlus<float>;
                       mOperators[$1] = pOpAgg;
                       f.changeAgg(pOpAgg);
                       cout << $1 <<"declared" <<endl;}


    | NAME COGDEFUZZ     { 
                           CogDefuzz<float> opDefuzz;
                           CogDefuzz<float>* pOpDefuzz = new CogDefuzz<float>;
                           mOperators[$1] = pOpDefuzz;
                           f.changeDefuzz(pOpDefuzz);
                           cout << $1 <<"declared" <<endl;}


    | NAME SUGDEFUZZ      { 
                            fuzzy::SugenoDefuzz<float> opSugDefuzz;
                            fuzzy::SugenoDefuzz<float>* pOpSugDefuzz = new fuzzy::SugenoDefuzz<float> ;
                            mOperators[$1] = &opSugDefuzz;
                            f.changeSugeno(pOpSugDefuzz);
                            cout << $1 <<"declared" <<endl;}


    | NAME NOTMINUS1     { 
                           fuzzy::NotMinus1<float> opNot;
                           fuzzy::NotMinus1<float>* pOpNot = new fuzzy::NotMinus1<float>;
                           mOperators[$1] = pOpNot;
                           f.changeNot(pOpNot);
                           cout << $1 <<"declared" <<endl;}
    ;
coreMamdaniRules: 
    unaryExp conclusion { 
                            r = f.newThen((core::Expression<float> *)$1,(core::Expression<float> *)$2);
                         }

    | binaryExp conclusion { 
                              r = f.newThen((core::Expression<float> *)$1,(core::Expression<float> *)$2);
                           }

    | coreMamdaniRules unaryExp conclusion { 
                                              r = f.newAgg(r,f.newThen((core::Expression<float> *)$2,(core::Expression<float> *)$3));
                                           }

    | coreMamdaniRules binaryExp conclusion { 
                                                r = f.newAgg(r,f.newThen((core::Expression<float> *)$2,(core::Expression<float> *)$3));
                                            }
    ;

unaryExp:
    NOT LPAREN  binaryExp RPAREN { 
                                    $$ = f.newNot((core::Expression<float>*)$3);
                                  }

    | NAME IS NAME { 
                      if(mValues.find($1) != mValues.end() && mMemberShips.find($3) != mMemberShips.end())
                        $$ = f.newIs(mMemberShips[$3],mValues[$1]);
                      else{
                        cout<<"undifined input or membership : "<<endl<<$1<<endl<<$3<<endl;
                        exit(-1);
                      }
                   }
    ;

binaryExp:
    NAME IS NAME OR NAME IS NAME { 
                                   if(mValues.find($1) != mValues.end() && mValues.find($5) != mValues.end() &&
                                      mMemberShips.find($3) != mMemberShips.end() && mMemberShips.find($7) != mMemberShips.end())
                                        $$ = f.newOr(f.newIs(mMemberShips[$3],mValues[$1]),f.newIs(mMemberShips[$7],mValues[$5]));
                                    else{
                                      cout<<"undifined input or membership"<<endl<<$1<<endl<<$3<<endl<<$5<<endl<<$7<<endl;
                                      exit(-1);
                                    }
                                  }
    | NAME IS NAME AND NAME IS NAME {
                                      if(mValues.find($1) != mValues.end() && mValues.find($5) != mValues.end() &&
                                        mMemberShips.find($3) != mMemberShips.end() && mMemberShips.find($7) != mMemberShips.end())
                                        $$ = f.newAnd(f.newIs(mMemberShips[$3],mValues[$1]),f.newIs(mMemberShips[$7],mValues[$5]));
                                    else{
                                      cout<<"undifined input or membership"<<endl<<$1<<endl<<$3<<endl<<$5<<endl<<$7<<endl;
                                      exit(-1);
                                    }
                                    }
    ;
conclusion:
    THEN NAME IS NAME ';' { 
                            if(mOutput.find($2) != mOutput.end() && mMemberShips.find($4) != mMemberShips.end())
                              $$ = f.newIs(mMemberShips[$4],mOutput[$2]);
                            else{
                              cout<<"undifined output or membership : "<<endl<<$2<<endl<<$4<<endl;
                              exit(-1);
                            }
                          }
    ;

coreSugenoRules:
    unaryExp sugenoconclusion  {
                                    rules.push_back( f.newThen((core::Expression<float> *)$1,(core::Expression<float> *)$2));
                                }

    | binaryExp sugenoconclusion {
                                    rules.push_back( f.newThen((core::Expression<float> *)$1,(core::Expression<float> *)$2));
                                }

    | coreSugenoRules unaryExp sugenoconclusion {
                                                   rules.push_back( f.newThen((core::Expression<float> *)$2,(core::Expression<float> *)$3));
                                                }

    | coreSugenoRules binaryExp sugenoconclusion {
                                                    rules.push_back( f.newThen((core::Expression<float> *)$2,(core::Expression<float> *)$3));
                                                  }

sugenoconclusion:
    THEN linearCombinaison ';'  {
                                  fuzzy::SugenoConclusion<float>* pConclusion = new fuzzy::SugenoConclusion<float>(&coef);
                                  f.changeConclusion(pConclusion);
                                  $$ = f.newNConclusion((std::vector<core::Expression<float>*>*) $2);
                                  cout << sConclusion.size()<< endl;
                                  cout << coef[0] << coef[1] <<coef [2]<<endl;

                                 }
linearCombinaison:
    INT NAME                    {
                                    coef.push_back($1);
                                    if(mValues.find($2) != mValues.end()){
                                      std::vector<core::Expression<float>*>* sConclusion = new std::vector<core::Expression<float>*>;
                                      sConclusion->push_back(mValues[$2]);
                                      $$ = sConclusion;
                                    }
                                    else{
                                      cout<<"undifined input : "<<endl<<$2<<endl;
                                      exit(-1);
                                    }

                                }
    | linearCombinaison INT NAME { 
                                    if(mValues.find($3) != mValues.end())
                                      ((std::vector<core::Expression<float>*>*)$1)->push_back(mValues[$3]);
                                    else{
                                      cout<<"undifined input : "<<endl<<$3<<endl;
                                      exit(-1);
                                    }
                                    cout << "here2"<<endl;
                                    coef.push_back($2);
                                  }
    | linearCombinaison INT NAME OFFSET INT {  
                                    coef.push_back($2);
                                    coef.push_back($5);
                                    if(mValues.find($3) != mValues.end())
                                      ((std::vector<core::Expression<float>*>*)$1)->push_back(mValues[$3]);
                                    else{
                                      cout<<"undifined input : "<<endl<<$3<<endl;
                                      exit(-1);
                                 }
                               }
    ;

%%

void mamdani()
{
  float s;
  std::map< std::string, core::ValueModel<float>* >::iterator it = mValues.begin();
  while(it != mValues.end())
    {
        std::cout<<it->first<<" :";
        std::cin >> s;
        it->second->setValue(s);
        it++;
    }

    std::cout<< mOutput.begin()->first<<" ->" << mamdaniSystem->evaluate() << std::endl;
     
    
    
}

void sugeno()
{ 
  fuzzy::ThenSugeno<float>* pThen = new fuzzy::ThenSugeno<float>;
  f.changeThen(pThen);
    float s;
  std::map< std::string, core::ValueModel<float>* >::iterator it = mValues.begin();
  while(it != mValues.end())
    {
        std::cout<<it->first<<" :";
        std::cin >> s;
        it->second->setValue(s);
        it++;
    }

    std::cout<< mOutput.begin()->first<<" ->" << sugenoSystem->evaluate() << std::endl;
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
    /*cout <<"parsing completed"<<endl;
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
    }*/
    while(true){
    int select;
    std::cout << "1: Mamdani" << std::endl;
    std::cout << "2: Sugeno" << std::endl;
    std::cout << "-1: exit" <<endl;
    std::cout << "> ";
    std::cin >> select;
    switch(select){
      case 1 : mamdani();
              break;
      case 2 : sugeno();
               break;
      case -1: exit(0);

      default: break;
    }
      

    }
}

void yyerror(char *s) {
    cout << "Parse error: " << s <<endl;
    cout << "token error: " << yytext <<endl;
    cout << "line" << yylineno <<endl;
    exit(-1);
}



