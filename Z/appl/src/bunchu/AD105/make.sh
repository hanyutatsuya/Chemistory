#

echo "�� AD105 Make ��"
echo ""

echo "�� rm *.o *.bnd AD105 ��"
rm *.o *.bnd AD105
echo ""

echo "�� make -f Makefile ��"
make -f Makefile
echo ""

echo "�� cp -p AD105 ~/bin/ ��"
cp -p AD105 ~/bin/
echo "�� cp -p AD105.ini ~/bin/ ��"
cp -p AD105.ini ~/bin/
echo "�� cp -p AD105_SORT.ini ~/bin/ ��"
cp -p AD105_SORT.ini ~/bin/
echo "�� cp -p AD105_LOG.ini ~/bin/ ��"
cp -p AD105_LOG.ini ~/bin/
echo ""

echo "�� Make End ��"

