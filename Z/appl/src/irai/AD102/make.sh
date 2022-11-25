
rm *.o

#######################################
## PRE COMPILE .sqc -> .c -> .o
#######################################

db2 connect to kea00db USER db2inst1 USING db2inst1
db2 prep AD102_db.sqc bindfile
db2 bind AD102_db.bnd
db2 connect reset
db2 terminate

#######################################
## c
#######################################
##/* object �쐬 */
##cc -c *.c
cc  -c AD102.c      -I$HOME/sqllib/include -I$HOME/appl/inc
cc  -c edit_irai.c -I$HOME/sqllib/include -I$HOME/appl/inc
cc  -c com_func.c  -I$HOME/sqllib/include -I$HOME/appl/inc
gcc -fpic -I$HOME/sqllib/include -I$HOME/appl/inc -c AD102_db.c -D_REENTRANT

#######################################
## LoadModule �쐬 
#######################################

##cc -fpic  -o AD102 AD102.c edit_irai.o com_func.o AD102_db.o -I$HOME/sqllib/include -I$HOME/appl/inc -Wl,-rpath,$HOME/sqllib/lib -L$HOME/appl/lib -lbml -L$HOME/sqllib/lib -ldb2 -lpthread

cc -fpic  -o AD102 AD102.c edit_irai.o com_func.o AD102_db.o -I$HOME/sqllib/include -I$HOME/appl/inc -Wl,-rpath,$HOME/sqllib/lib -L$HOME/appl/lib -lbmlcom -L$HOME/sqllib/lib -ldb2 -lpthread

echo "�� cp -p AD102 ~/bin/ ��"
cp -p AD102 ~/bin/
echo "�� cp -p AD102.ini ~/bin/ ��"
cp -p AD102.ini ~/bin/
echo "�� cp -p AD102_LOG.ini ~/bin/ ��"
cp -p AD102_LOG.ini ~/bin/
