#

echo "�� ZD101 Make ��"
echo ""

echo "�� rm *.o *.bnd ZD101 ��"
rm *.o *.bnd ZD101
echo ""

echo "�� make -f Makefile ��"
make -f Makefile
echo ""

echo "�� cp -p ZD101 ~/bin/ ��"
cp -p ZD101 ~/bin/
echo "�� cp -p ZD101.ini ~/bin/ ��"
cp -p ZD101.ini ~/bin/
echo ""

echo "�� Make End ��"

