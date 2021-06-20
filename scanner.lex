%{

/* Declarations section */
#include "helper.hpp"
#include "hw3_output.hpp"

#include "parser.tab.hpp"


using namespace std;
using namespace output;
%}

%option yylineno 
%option noyywrap
%option nounput
%x comment
%x thisistheend


relop           (>=|<=|<|>)
equalop			(==|!=)
mult 			([*])
div				([/])
plus			([+])
minus			([-])
digit   		([0-9])
letter			([a-zA-Z])
id  			([a-zA-Z][a-zA-Z0-9]*)
whitespace		([\r\t\n ])

%%
{whitespace}+				;
void                        {
							yylval= new cut_type{"VOID"};
							return VOID;}
int                        {
							/*ylval= new cut_type{"INT"}; */
							return INT;}
byte                        {
							/*yylval= new cut_type{"BYTE"}; */
							return BYTE;}
b                        {
							yylval= new cut_type{"BYTE"}; 
							return B;}
bool                        {
							/*yylval= new cut_type{"BOOL"};*/ 
							return BOOL;}
and                        {
							yylval= new cut_type{"AND"};
							return AND;}
or                        {
							yylval= new cut_type{"OR"};
							return OR;}
not                        {
							yylval= new cut_type{"NOT"};			
							return NOT;}
true                        {
							yylval= new cut_type{"True"};
							return TRUE;}
false                     {
							yylval= new cut_type{"FALSE"};
							return FALSE;}
return                        {
								yylval= new cut_type{yytext};
								return RETURN;}
if                        {
							yylval= new cut_type{yytext};
							return IF;}
else                        {
							yylval= new cut_type{yytext};
							return ELSE;}
while                        {
							yylval= new cut_type{yytext};
							return WHILE;}
break                        {
							yylval= new cut_type{yytext};
							return BREAK;}
continue                        {
							yylval= new cut_type{yytext};
							return CONTINUE;}
switch                        {
							yylval= new cut_type{yytext};
							return SWITCH;}
case                        {
							yylval= new cut_type{yytext};
							return CASE;}
default                     {
							yylval= new cut_type{yytext};
							return DEFAULT;}
:                        {yylval= new cut_type{yytext};return COLON;}
;                        {yylval= new cut_type{yytext};return SC;}
,                        {yylval= new cut_type{yytext};return COMMA;}
\(                        {yylval= new cut_type{yytext};return LPAREN;}
\)                        {yylval= new cut_type{yytext};return RPAREN;}
\{                        {yylval= new cut_type{yytext};return LBRACE;}
\}                        {yylval= new cut_type{yytext};return RBRACE;}
=                        {yylval= new cut_type{yytext};return ASSIGN;}
{relop}                        {yylval= new cut_type{yytext};return RELOP;}
{equalop}						{yylval= new cut_type{yytext};return EQUALOP;}
{mult}							{yylval= new cut_type{yytext};return MULT;}
{div}							{yylval= new cut_type{yytext};return DIV;}
{plus}							{yylval= new cut_type{yytext};return PLUS;}
{minus}							{yylval= new cut_type{yytext};return MINUS;}
"//"[^\r|\n]*         BEGIN(comment);
<comment>{
	\r		{BEGIN(INITIAL);}
	\n		{BEGIN(INITIAL);}
	\r\n 	{BEGIN(INITIAL);}
	<<EOF>>	{BEGIN(INITIAL);}
	}
	
{id}+ {
		yylval= new cut_type{yytext};
		return ID;}
0 {	
	yylval= new cut_type{yytext}; 
	return NUM;}
[1-9]+{digit}* {	
					yylval= new cut_type{yytext};
					return NUM;}
\"([^\n\r\"\\]|\\[rnt"\\])+\" 	{	
									yylval= new cut_type{yytext}; 
									return STRING;}
.		{
			errorLex(yylineno);
			exit(1);
		}
<INITIAL><<EOF>>        {BEGIN(thisistheend);return ENDOFFILE;}
<thisistheend><<EOF>>	{return 0;}
%%
/* c code */


