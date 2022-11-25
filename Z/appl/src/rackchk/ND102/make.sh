#

echo "š ND102 Make š"
echo ""

echo "š rm *.o *.bnd ND102 š"
rm *.o *.bnd ND102
echo ""

echo "š make -f Makefile š"
make -f Makefile
echo ""

echo "š cp -p ND102 ~/bin/ š"
cp -p ND102 ~/bin/
echo "š cp -p ND102.ini ~/bin/ š"
cp -p ND102.ini ~/bin/
echo ""

echo "š Make End š"

