#

echo "š LD105 Make š"
echo ""

echo "š rm *.o *.bnd LD105 š"
rm *.o *.bnd LD105
echo ""

echo "š make -f Makefile š"
make -f Makefile
echo ""

echo "š cp -p LD105 ~/bin/ š"
cp -p LD105 ~/bin/
echo "š cp -p LD105.ini ~/bin/ š"
cp -p LD105.ini ~/bin/
echo ""

echo "š Make End š"

