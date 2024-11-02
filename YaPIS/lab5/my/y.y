%{
#include <stdio.h>
#include <stdlib.h>

void yyerror(const char *s);
int yylex();
%}

%union {
    char* str;
    int num;
}

%token <str> LABEL
%token <num> DEC HEX
%token MOV ADD SUB JMP CMP NOP
%token AX BX CX DX SI DI

%type <str> operand

%%

// Грамматика
program:
    statement_list
    ;

statement_list:
    statement_list statement
    | statement
    ;

statement:
    LABEL ':' command { 
        printf("Label: %s\n", $1); 
    }
    | command
    ;

command:
    MOV operand ',' operand { 
        printf("Command: MOV, "); 
        printf("register: %s, ", $2); 
        printf("hex: %s\n", $4); 
    }
    | ADD operand ',' operand { 
        printf("Command: ADD, "); 
        printf("register: %s, ", $2); 
        printf("hex: %s\n", $4); 
    }
    | SUB operand ',' operand { 
        printf("Command: SUB, "); 
        printf("register: %s, ", $2); 
        printf("register: %s\n", $4); 
    }
    | JMP operand { 
        printf("Command: JMP, "); 
        printf("label: %s\n", $2); 
    }
    | CMP operand ',' operand { 
        printf("Command: CMP, "); 
        printf("register: %s, ", $2); 
        printf("register: %s\n", $4); 
    }
    | NOP { 
        printf("Command: NOP\n"); 
    }
    ;

operand:
    AX { 
        $$ = "AX"; 
    }
    | BX { 
        $$ = "BX"; 
    }
    | CX { 
        $$ = "CX"; 
    }
    | DX { 
        $$ = "DX"; 
    }
    | SI { 
        $$ = "SI"; 
    }
    | DI { 
        $$ = "DI"; 
    }
    | LABEL { 
        $$ = $1; 
    }
    | HEX { 
        $$ = malloc(12); 
        sprintf($$, "0x%X", $1); 
    }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "err: %s\n", s);
}

int main() {
    return yyparse();
}
