#

echo "�� LD105 Make ��"
echo ""

echo "�� rm *.o *.bnd LD105 ��"
rm *.o *.bnd LD105
echo ""

echo "�� make -f Makefile ��"
make -f Makefile
echo ""

echo "�� cp -p LD105 ~/bin/ ��"
cp -p LD105 ~/bin/
echo "�� cp -p LD105.ini ~/bin/ ��"
cp -p LD105.ini ~/bin/
echo ""

echo "�� Make End ��"

