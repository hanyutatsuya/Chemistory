#

echo "�� BD302 Make ��"
echo ""

echo "�� rm *.o *.bnd BD302 ��"
rm *.o *.bnd BD302
echo ""

echo "�� make -f Makefile ��"
make -f Makefile
echo ""

echo "�� cp -p BD302 ~/bin/ ��"
cp -p BD302 ~/bin/
echo "�� cp -p BD302.ini ~/bin/ ��"
cp -p BD302.ini ~/bin/
echo ""

echo "�� Make End ��"

