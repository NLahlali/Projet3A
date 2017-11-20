%{
using namespace std;
#include "fuzzy.tab.h"
%}
%%
[ \t\n]       			    ;
values		   				{ return VALUES; }
input 						{ return INPUT; }
output						{ return OUTPUT; }
memberships		   			{ return MEMBERSHIPS; }
operators		   			{ return OPERATORS; }
MamdaniRules			    { return MAMDANIRULES; }
SugenoRules		   			{ return SUGENORULES; }
triangle		  		    { return TRIANGLE; }
trapez		  			    { return TRAPEZ; }
ltrapez					    { return LTRAPEZ; }
rtrapez		 			    { return RTRAPEZ; }
bell					    { return BELL; }
zshape					    { return ZSHAPE; }
guausse					    { return GUAUSSE; }
AndMult		  			    { return ANDMULT; }
OrMax		  			    { return ORMAX; }
ThenMult			   	    { return THENMULT; }
AggPlus		 			    { return AGGPLUS; }
CogDefuzz				    { return COGDEFUZZ; }
SugenoConclusion		    { return SUGENOCONCLUSION; }
NotMinus1				    { return NOTMINUS1; }
not		 				    { return NOT; }
is							{ return IS; }
and 						{ return AND; }
or 							{ return OR; }
then 						{ return THEN; }
\(            			    { return LPAREN; }
\)           			    { return RPAREN; }
\{			 			    { return LBRACE; }
\}						    { return RBRACE; }
[0-9]+     			        { yylval.ival = atoi(yytext); return INT; }
[a-zA-Z0-9]+   				{
    							yylval.sval = strdup(yytext);
   								 return NAME;
							}
;							{ return yytext[0]; }
.							;
%%
