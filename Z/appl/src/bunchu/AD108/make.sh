#

echo "�� rm *.o *.bnd AD108 ��"
rm *.o *.bnd AD108
echo ""

echo "�� make -f Makefile ��"
make -f Makefile
echo ""

echo "�� cp -p AD108 ~/bin/ ��"
cp -p AD108 ~/bin/
echo "�� cp -p AD108.ini ~/bin/ ��"
cp -p AD108.ini ~/bin/
echo "�� cp -p AD108_LOG.ini ~/bin/ ��"
cp -p AD108_LOG.ini ~/bin/

echo ""
echo "�� Make End ��"
