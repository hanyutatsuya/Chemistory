#

echo "�� BD401 Make ��"
echo ""

echo "�� rm *.o *.bnd BD401 ��"
rm *.o *.bnd BD401
echo ""

echo "�� make -f Makefile ��"
make -f Makefile
echo ""

echo "�� cp -p BD401 ~/bin/ ��"
cp -p BD401 ~/bin/
echo "�� cp -p BD401.ini ~/bin/ ��"
cp -p BD401.ini ~/bin/
echo ""

echo "�� Make End ��"

