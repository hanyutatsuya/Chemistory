
rm *.o

#######################################
## PRE COMPILE .sqc -> .c -> .o
#######################################
db2 connect to  kea00db user db2inst1  using db2inst1
db2 prep AD301_db.sqc bindfile
db2 bind AD301_db.bnd
db2 connect reset
db2 terminate

#######################################
## c
#######################################
##/* object çÏê¨ */
##cc -c *.c
cc -c AD301.c     -I$HOME/sqllib/include -I$HOME/appl/inc 
cc -c com_func.c  -I$HOME/sqllib/include -I$HOME/appl/inc
gcc -fpic -I$HOME/sqllib/include -I$HOME/appl/inc -c AD301_db.c -D_REENTRANT

#######################################
## LoadModule çÏê¨ 
#######################################
cc -fpic  -o AD301 AD301.c com_func.o AD301_db.o -I$HOME/sqllib/include -I$HOME/appl/inc -Wl,-rpath,$HOME/sqllib/lib -L$HOME/appl/lib -lbmlcom -L$HOME/sqllib/lib -ldb2 -lpthread

echo "Åö cp -p AD301 ~/bin/ Åö"
cp -p AD301 ~/bin/
echo "Åö cp -p AD301.ini ~/bin/ Åö"
cp -p AD301.ini ~/bin/
