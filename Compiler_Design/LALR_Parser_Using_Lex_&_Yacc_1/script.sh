bison -d assg3.y
flex  -o assg3.l.c assg3.l
gcc  -o assg3 assg3.l.c assg3.tab.c -lfl -lm 
./assg3
