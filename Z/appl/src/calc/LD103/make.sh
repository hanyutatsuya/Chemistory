#

echo "�� LD103 Make ��"
echo ""

echo "�� rm *.o *.bnd LD103 ��"
rm *.o *.bnd LD103
echo ""

echo "�� make -f Makefile ��"
make -f Makefile
echo ""

echo "�� cp -p LD103 ~/bin/ ��"
cp -p LD103 ~/bin/
echo "�� cp -p LD103.ini ~/bin/ ��"
cp -p LD103.ini ~/bin/
echo ""

echo "�� Make End ��"

