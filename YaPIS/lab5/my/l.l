%{
#include "tab.h"
#include <stdio.h>
#include <stdlib.h>
%}

%%

AX          { return AX; }
BX          { return BX; }
CX          { return CX; }
DX          { return DX; }
SI          { return SI; }
DI          { return DI; }

"MOV"       { return MOV; }
"ADD"       { return ADD; }
"SUB"       { return SUB; }
"JMP"       { return JMP; }
"CMP"       { return CMP; }
"NOP"       { return NOP; }

[a-zA-Z_][a-zA-Z0-9_]*  { yylval.str = strdup(yytext); return LABEL; }

0x[0-9A-Fa-f]+          { yylval.num = strtol(yytext, NULL, 16); return HEX; }
[ \t]+                  { /* Игнорируем пробелы и табуляцию */ }
\n                      { /* Игнорируем переносы строки */ }
.                       { return yytext[0]; }

%%

int yywrap() {
    return 1;
}
