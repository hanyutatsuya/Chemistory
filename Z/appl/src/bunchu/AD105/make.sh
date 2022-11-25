#

echo "š AD105 Make š"
echo ""

echo "š rm *.o *.bnd AD105 š"
rm *.o *.bnd AD105
echo ""

echo "š make -f Makefile š"
make -f Makefile
echo ""

echo "š cp -p AD105 ~/bin/ š"
cp -p AD105 ~/bin/
echo "š cp -p AD105.ini ~/bin/ š"
cp -p AD105.ini ~/bin/
echo "š cp -p AD105_SORT.ini ~/bin/ š"
cp -p AD105_SORT.ini ~/bin/
echo "š cp -p AD105_LOG.ini ~/bin/ š"
cp -p AD105_LOG.ini ~/bin/
echo ""

echo "š Make End š"

