#

echo "�� BD305(�V�t���Ή���) Make ��"
echo ""

echo "�� rm *.o *.bnd BD305 ��"
rm *.o *.bnd BD305
echo ""

echo "�� make -f Makefile ��"
make -f Makefile
echo ""

echo "�� cp -p BD305 ~/bin/ ��"
cp -p BD305 ~/bin/
echo "�� cp -p BD305.ini ~/bin/ ��"
cp -p BD305.ini ~/bin/
echo ""

echo "�� Make End ��"

