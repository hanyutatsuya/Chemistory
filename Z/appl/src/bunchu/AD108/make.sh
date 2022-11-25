#

echo "š rm *.o *.bnd AD108 š"
rm *.o *.bnd AD108
echo ""

echo "š make -f Makefile š"
make -f Makefile
echo ""

echo "š cp -p AD108 ~/bin/ š"
cp -p AD108 ~/bin/
echo "š cp -p AD108.ini ~/bin/ š"
cp -p AD108.ini ~/bin/
echo "š cp -p AD108_LOG.ini ~/bin/ š"
cp -p AD108_LOG.ini ~/bin/

echo ""
echo "š Make End š"
