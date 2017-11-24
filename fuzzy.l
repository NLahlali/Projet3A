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
trapeze		  			    { return TRAPEZE; }
ltrapeze					{ return LTRAPEZE; }
rtrapeze	 			    { return RTRAPEZE; }
bell					    { return BELL; }
zshaped					    { return ZSHAPED; }
gauss					    { return GAUSS; }
AndMult		  			    { return ANDMULT; }
AndMin		  			    { return ANDMIN; }
OrMax		  			    { return ORMAX; }
OrPlus		  			    { return ORPLUS; }
ThenMult			   	    { return THENMULT; }
ThenMin			   	    	{ return THENMIN; }
AggPlus		 			    { return AGGPLUS; }
AggMax		 			    { return AGGMAX; }
CogDefuzz				    { return COGDEFUZZ; }
SugDefuzz		            { return SUGDEFUZZ; }
NotMinus1				    { return NOTMINUS1; }
not		 				    { return NOT; }
is							{ return IS; }
offset						{ return OFFSET; }
and 						{ return AND; }
or 							{ return OR; }
then 						{ return THEN; }
\(            			    { return LPAREN; }
\)           			    { return RPAREN; }
\{			 			    { return LBRACE; }
\}						    { return RBRACE; }
[+-]?([0-9]*[.])?[0-9]+     { yylval.fval = strtod(yytext,NULL);
							  return INT; }
[a-zA-Z0-9]+   				{
    							yylval.sval = strdup(yytext);
   								 return NAME;
							}
;							{ return yytext[0]; }
.							;
%%
