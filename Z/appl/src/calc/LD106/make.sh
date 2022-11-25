#

echo "š LD106 Make š"
echo ""

echo "š rm *.o *.bnd LD106 š"
rm *.o *.bnd LD106
echo ""

echo "š make -f Makefile š"
make -f Makefile
echo ""

echo "š cp -p LD106 ~/bin/ š"
cp -p LD106 ~/bin/
echo "š cp -p LD106.ini ~/bin/ š"
cp -p LD106.ini ~/bin/
echo ""

echo "š Make End š"

