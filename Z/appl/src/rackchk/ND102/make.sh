#

echo "�� ND102 Make ��"
echo ""

echo "�� rm *.o *.bnd ND102 ��"
rm *.o *.bnd ND102
echo ""

echo "�� make -f Makefile ��"
make -f Makefile
echo ""

echo "�� cp -p ND102 ~/bin/ ��"
cp -p ND102 ~/bin/
echo "�� cp -p ND102.ini ~/bin/ ��"
cp -p ND102.ini ~/bin/
echo ""

echo "�� Make End ��"

