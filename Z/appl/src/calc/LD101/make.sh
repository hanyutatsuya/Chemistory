#

echo "�� LD101 Make ��"
echo ""

echo "�� rm *.o *.bnd LD101 ��"
rm *.o *.bnd LD101
echo ""

echo "�� make -f Makefile ��"
make -f Makefile
echo ""

echo "�� cp -p LD101 ~/bin/ ��"
cp -p LD101 ~/bin/
echo "�� cp -p LD101.ini ~/bin/ ��"
cp -p LD101.ini ~/bin/
echo ""

echo "�� Make End ��"

