%{
#include "scanType.h"
#include "parser.tab.h" // This has to be the last include

using namespace std;

#define YY_DECL extern "C" int yylex()
#define YYSTYPE int

int line=1;
char *lastToken=(char *)"";
//extern int numErrors;

// used as a means to communicate between .l and .y files
int setValue(int linenum, int tokenClass, char *svalue) {
    yylval.tinfo.tokenclass = tokenClass;
    yylval.tinfo.linenum = linenum;
    yylval.tinfo.tokenstr = strdup(svalue);
    yylval.tinfo.cvalue = '@';
    yylval.tinfo.nvalue = 777;
    yylval.tinfo.svalue = NULL;

    yylval.tinfo.tokenstr = lastToken = strdup(svalue);

    switch (tokenClass) {

    case NUMCONST:
         // yylval.tinfo.nvalue = hmmmm ..... I don't need this yet, but
         break;
    case BOOLCONST:
         // yyval.tinfo.nvalue = something to think about.. probably set to 0 or 1?
         break;
    case OP:
         // yylval.tinfo.cvalue = hmmm..... What should I set it to?
         break;
    // case CHARCONST:
         // yyval.tinfo.cvalue = not sure what this should be set to yet.
    //    break;
    }


    return tokenClass;
}

%}

%option noyywrap

letter   [a-zA-Z]
digit    [0-9]
quote    [\']
underbar [_]
letdig      {digit}|{letter}|{underbar}
limitters   [\;\,\(\)\{\}\[\]]
op    [\-\+\*\/\%]
whitespace  [\ \t]
comment \/\/.*
%%
[\(\)\*\+\,\-\/\:\;\<\=\>\?\[\]\%\{\}]         { return setValue(line, OP, yytext); } // single char tokens
"!="           { return setValue(line, NEQ, yytext);}
"++"           { return setValue(line, INC, yytext);}
"--"           { return setValue(line, DEC, yytext);}
"=="           { return setValue(line, EQ, yytext);}
"+="           { return setValue(line, ADDASS, yytext);}
"-="           { return setValue(line, SUBASS, yytext);}
"*="           { return setValue(line, MULASS, yytext);}
"/="           { return setValue(line, DIVASS, yytext);}
":<:"          { return setValue(line, MIN, yytext);} // add to parser.y
":>:"          { return setValue(line, MAX, yytext);}
"and"          { return setValue(line, AND, yytext);}
"or"           { return setValue(line, OR, yytext);}
"for"          { return setValue(line, FOR, yytext);}
"to"           { return setValue(line, TO, yytext);}
"by"           { return setValue(line, BY, yytext);}
"while"        { return setValue(line, WHILE, yytext);}
"if"           { return setValue(line, IF, yytext);}
"then"         { return setValue(line, THEN, yytext);}
"else"         { return setValue(line, ELSE, yytext);}
^"#DRBC ".*    { return setValue(line, PRECOMPILER, yytext); }
"true"|"false" {return setValue(line, BOOLCONST, yytext);}
[0-9]+         { return setValue(line, NUMCONST, yytext); }
\n             {  line++; }
{whitespace}+  ;
.              { printf("ERROR(%d): Token error, invalid or misplaced input character: \'%c\'. Character Ignored.\n", line, yytext[0]);}


