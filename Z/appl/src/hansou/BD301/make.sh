#

echo "�� BD301(�V�t���Ή���) Make ��"
echo ""

echo "�� rm *.o *.bnd BD301 ��"
rm *.o *.bnd BD301
echo ""

echo "�� make -f Makefile ��"
make -f Makefile
echo ""

echo "�� cp -p BD301 ~/bin/ ��"
cp -p BD301 ~/bin/
echo "�� cp -p BD301.ini ~/bin/ ��"
cp -p BD301.ini ~/bin/
echo ""

echo "�� Make End ��"

