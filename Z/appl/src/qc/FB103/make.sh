#

echo "�� FB103 Make ��"
echo ""

echo "�� rm *.o *.bnd FB103 ��"
make clean
echo ""

echo "�� make -f Makefile ��"
make -f Makefile
echo ""

echo "�� cp -p FB103 ~/bin/ ��"
cp -p FB103 ~/bin/
echo "�� cp -p FB103.ini ~/bin/ ��"
cp -p FB103.ini ~/bin/
echo ""

echo "�� Make End ��"

