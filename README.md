#Small Language Complier

##About
This is a small language complier via flex & bison.

Small language is a simple C-like language with if, while, function.

##Build
###Build with GCC
        cd c_file
        gcc lex.yy.c small.tab.c
###Build with flex & bison
        cd flex&bison
        flex small.l
        bison -d small.y