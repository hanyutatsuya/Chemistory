#

echo "�� JD112 Make ��"
echo ""

echo "�� rm *.o *.bnd JD112 ��"
rm *.o *.bnd JD112
echo ""

echo "�� make -f Makefile ��"
make -f Makefile
echo ""

echo "�� cp -p JD112 ~/bin/ ��"
cp -p JD112 ~/bin/
echo "�� cp -p JD112.ini ~/bin/ ��"
cp -p JD112.ini ~/bin/
echo "�� cp -p JD112_LOG.ini ~/bin/ ��"
cp -p JD112_LOG.ini ~/bin/
echo ""

echo "�� Make End ��"

