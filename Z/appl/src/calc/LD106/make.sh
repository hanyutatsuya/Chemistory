#

echo "�� LD106 Make ��"
echo ""

echo "�� rm *.o *.bnd LD106 ��"
rm *.o *.bnd LD106
echo ""

echo "�� make -f Makefile ��"
make -f Makefile
echo ""

echo "�� cp -p LD106 ~/bin/ ��"
cp -p LD106 ~/bin/
echo "�� cp -p LD106.ini ~/bin/ ��"
cp -p LD106.ini ~/bin/
echo ""

echo "�� Make End ��"

