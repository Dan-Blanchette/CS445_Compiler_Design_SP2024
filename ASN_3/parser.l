%{
#include "scanType.h"
#include "treeNodes.h"
#include "treeUtils.h"
#include <string>
#include "parser.tab.h" // This has to be the last include

using namespace std;
// Dan Blanchette
// ASN_3
// CS-445 Compiler Design
// Doctor BC
#define YY_DECL extern "C" int yylex()
#define YYSTYPE int

int line=1;
char *lastToken=(char *)"";
//extern int numErrors;

// used as a means to communicate between .l and .y files
int setValue(int linenum, int tokenClass, char *svalue) {
    yylval.tokenData = new TokenData;


    yylval.tokenData->tokenclass = tokenClass;
    yylval.tokenData->linenum = linenum;
    yylval.tokenData->tokenstr = strdup(svalue);
    yylval.tokenData->cvalue = '@';
    yylval.tokenData->nvalue = 777;
    yylval.tokenData->svalue = NULL;

    yylval.tokenData->tokenstr = lastToken = strdup(svalue);
    // yylval.tokenData->cvalue = 

    switch (tokenClass) {

    case NUMCONST:
       yylval.tokenData->nvalue = stoi(svalue);
         // yylval.tokenData->nvalue = hmmmm ..... I don't need this yet, but
       break;
    case BOOLCONST:
       if(svalue[0] == 't') {
          yylval.tokenData->nvalue = 1;
       }
       else yylval.tokenData->nvalue =0;
       break;
         // yylval.tokenData->nvalue = something to think about.. probably set to 0 or 1? 't' or 'f'?
         break;
    //case OP:
         // yylval.tokenData->cvalue = hmmm..... What should I set it to?
       break;
    // case CHARCONST:
       if(svalue[1] == '\\'){
          if(svalue[2] == 'n')
             yylval.tokenData->cvalue = '\n';
          else if(svalue[2] == '0') {
               yylval.tokenData->cvalue = '\0';
          }
       }
       // test
         // yylval.tokenData->cvalue = not sure what this should be set to yet.
        //  break;
    }

    return tokenClass;
}

%}

%option noyywrap

letter   [a-zA-Z]
digit    [0-9]
quote    [\'] 
underbar [_]
period   [.]
dubquote [\"]
letdig      {digit}|{letter}|{underbar}
string      {letdig}+|{op}+|{whitespace}+|{limitters}+|{period}+
limitters   [\;\,\(\)\{\}\[\]]
whitespace  [\ \t]
op [\(\)\*\+\,\-\/\:\;\<\=\>\?\[\]\%\{\}]
comment \/\/.*   
%%
{op}           { return setValue(line, yytext[0], yytext);} // single char tokens
"!="           { return setValue(line, NEQ, yytext);}
"<="           { return setValue(line, LEQ, yytext);}
">="           { return setValue(line, GEQ, yytext);}
"++"           { return setValue(line, INC, yytext);}
"--"           { return setValue(line, DEC, yytext);}
"=="           { return setValue(line, EQ, yytext);}
"+="           { return setValue(line, ADDASS, yytext);}
"-="           { return setValue(line, SUBASS, yytext);}
"*="           { return setValue(line, MULASS, yytext);}
"/="           { return setValue(line, DIVASS, yytext);}
":<:"          { return setValue(line, MIN, yytext);} // add to parser.y
":>:"          { return setValue(line, MAX, yytext);}
"int"          { return setValue(line, INT, yytext);}
"char"         { return setValue(line, CHAR, yytext);}
"bool"         { return setValue(line, BOOL, yytext);}
"and"          { return setValue(line, AND, yytext);}
"or"           { return setValue(line, OR, yytext);}
"for"          { return setValue(line, FOR, yytext);}
"to"           { return setValue(line, TO, yytext);}
"do"           { return setValue(line, DO, yytext);}
"not"          { return setValue(line, NOT, yytext);}
"by"           { return setValue(line, BY, yytext);}
"while"        { return setValue(line, WHILE, yytext);}
"if"           { return setValue(line, IF, yytext);}
"then"         { return setValue(line, THEN, yytext);}
"else"         { return setValue(line, ELSE, yytext);}
"static"       { return setValue(line, STATIC, yytext);}
"return"       { return setValue(line, RETURN, yytext);}
"break"        { return setValue(line, BREAK, yytext);}
^"#DRBC ".*    { return setValue(line, PRECOMPILER, yytext);}
^"#DRBCRUN ".* { return setValue(line, PRECOMPILER, yytext);}
{digit}+       { return setValue(line, NUMCONST, yytext); }
"true"|"false" {return setValue(line, BOOLCONST, yytext);}
{comment}      ;
{quote}\\?.{quote} {return setValue(line, CHARCONST, yytext);}
{quote}(\\[^\n]|[^\'\\\n]*){quote}  {return setValue(line, CHARCONST, yytext);}
["](\\[^\n]|[^\"\\\n])*["] {return setValue(line, STRINGCONST, yytext);} 
{letter}{letdig}*  {return setValue(line, ID, yytext);}
\n             {  line++; }
{whitespace}+  ;
.              { printf("ERROR(%d): Token error, invalid or misplaced input character: \'%c\'. Character Ignored.\n", line, yytext[0]);}


