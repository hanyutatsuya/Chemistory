#

echo "�� MD103 Make ��"
echo ""

echo "�� rm *.o *.bnd MD103 ��"
rm *.o *.bnd MD103
echo ""

echo "�� make -f Makefile ��"
make -f Makefile
echo ""

echo "�� cp -p MD103 ~/bin/ ��"
cp -p MD103 ~/bin/
echo "�� cp -p MD103.ini ~/bin/ ��"
cp -p MD103.ini ~/bin/
echo ""

echo "�� Make End ��"

