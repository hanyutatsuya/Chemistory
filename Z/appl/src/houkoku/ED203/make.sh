#

echo "�� ED203 Make ��"
echo ""

echo "�� rm *.o *.bnd ED203 ��"
rm *.o *.bnd ED203
echo ""

echo "�� make -f Makefile ��"
make -f Makefile
echo ""

echo "�� cp -p ED203 ~/bin/ ��"
cp -p ED203 ~/bin/
echo "�� cp -p ED203.ini ~/bin/ ��"
cp -p ED203.ini ~/bin/
echo "�� cp -p ED203_LOG.ini ~/bin/ ��"
cp -p ED203_LOG.ini ~/bin/
echo ""

echo "�� Make End ��"

