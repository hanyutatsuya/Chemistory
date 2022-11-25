#

echo "š LD101 Make š"
echo ""

echo "š rm *.o *.bnd LD101 š"
rm *.o *.bnd LD101
echo ""

echo "š make -f Makefile š"
make -f Makefile
echo ""

echo "š cp -p LD101 ~/bin/ š"
cp -p LD101 ~/bin/
echo "š cp -p LD101.ini ~/bin/ š"
cp -p LD101.ini ~/bin/
echo ""

echo "š Make End š"

