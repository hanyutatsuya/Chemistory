
rm *.o

#######################################
## PRE COMPILE .sqc -> .c -> .o
#######################################


db2 connect to kea00db USER db2inst1 USING db2inst1
db2 prep AD202_db.sqc bindfile
db2 bind AD202_db.bnd
db2 connect reset
db2 terminate

#######################################
## c
#######################################
##/* object çÏê¨ */
cc -c AD202.c      -I$HOME/sqllib/include -I$HOME/appl/inc 
cc -c edit_zoku.c -I$HOME/sqllib/include -I$HOME/appl/inc
cc -c edit_irai.c -I$HOME/sqllib/include -I$HOME/appl/inc
cc -c com_func.c  -I$HOME/sqllib/include -I$HOME/appl/inc
gcc -fpic -I$HOME/sqllib/include -I$HOME/appl/inc -c AD202_db.c -D_REENTRANT

#######################################
## LoadModule çÏê¨ 
#######################################
cc -fpic  -o AD202 AD202.c edit_zoku.o edit_irai.o com_func.o AD202_db.o -I$HOME/sqllib/include -I$HOME/appl/inc -Wl,-rpath,$HOME/sqllib/lib -L$HOME/appl/lib -lbmlcom -L$HOME/sqllib/lib -ldb2 -lpthread
echo ""

echo "Åö cp -p AD202 ~/bin/ Åö"
cp -p AD202 ~/bin/
echo "Åö cp -p AD202.ini ~/bin/ Åö"
cp -p AD202.ini ~/bin/
echo "Åö cp -p AD202_LOG.ini ~/bin/ Åö"
cp -p AD202_LOG.ini ~/bin/
echo ""

echo "Åö Make End Åö"
