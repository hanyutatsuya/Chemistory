#

echo "�� rm *.o AD107 ��"
rm *.o AD107
echo ""

echo "�� make -f Makefile ��"
make -f Makefile
echo ""

echo "�� cp -p AD107 ~/bin ��"
cp -p AD107 ~/bin
echo "�� cp -p AD107.ini ~/bin ��"
cp -p AD107.ini ~/bin
echo "�� cp -p AD107_LOG.ini ~/bin ��"
cp -p AD107_LOG.ini ~/bin
echo ""

echo "�� Make End ��"
