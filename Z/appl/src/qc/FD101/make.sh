#

echo "�� FD101 Make ��"
echo ""

echo "�� rm *.o *.bnd FD101 ��"
make clean
echo ""

echo "�� make -f Makefile ��"
make -f Makefile
echo ""

echo "�� cp -p FD101 ~/bin/ ��"
cp -p FD101 ~/bin/
echo "�� cp -p FD101.ini ~/bin/ ��"
cp -p FD101.ini ~/bin/
echo ""

echo "�� Make End ��"

