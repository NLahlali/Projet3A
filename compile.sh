set -e
set -x
bison -d fuzzy.y
flex fuzzy.l
g++ fuzzy.tab.c lex.yy.c -ll -o fuzzy

