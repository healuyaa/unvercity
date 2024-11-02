bison -d my/y.y -o my/tab.c
flex -o my/lex.c my/l.l 
gcc my/lex.c my/tab.c -o my/app ./my/libfl.a