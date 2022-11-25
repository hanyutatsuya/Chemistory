#

echo "š LD103 Make š"
echo ""

echo "š rm *.o *.bnd LD103 š"
rm *.o *.bnd LD103
echo ""

echo "š make -f Makefile š"
make -f Makefile
echo ""

echo "š cp -p LD103 ~/bin/ š"
cp -p LD103 ~/bin/
echo "š cp -p LD103.ini ~/bin/ š"
cp -p LD103.ini ~/bin/
echo ""

echo "š Make End š"

