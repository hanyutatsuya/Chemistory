#

echo "�� MD104 Make ��"
echo ""

echo "�� rm *.o *.bnd MD104 ��"
rm *.o *.bnd MD104
echo ""

echo "�� make -f Makefile ��"
make -f Makefile
echo ""

echo "�� cp -p MD104 ~/bin/ ��"
cp -p MD104 ~/bin/
echo "�� cp -p MD104.ini ~/bin/ ��"
cp -p MD104.ini ~/bin/
echo ""

echo "�� Make End ��"

