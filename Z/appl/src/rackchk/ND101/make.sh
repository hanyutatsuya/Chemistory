#

echo "�� ND101 Make ��"
echo ""

echo "�� rm *.o *.bnd ND101 ��"
rm *.o *.bnd ND101
echo ""

echo "�� make -f Makefile ��"
make -f Makefile
echo ""

echo "�� cp -p ND101 ~/bin/ ��"
cp -p ND101 ~/bin/
echo "�� cp -p ND101.ini ~/bin/ ��"
cp -p ND101.ini ~/bin/
echo ""

echo "�� Make End ��"

