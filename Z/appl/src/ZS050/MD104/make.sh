#

echo "š MD104 Make š"
echo ""

echo "š rm *.o *.bnd MD104 š"
rm *.o *.bnd MD104
echo ""

echo "š make -f Makefile š"
make -f Makefile
echo ""

echo "š cp -p MD104 ~/bin/ š"
cp -p MD104 ~/bin/
echo "š cp -p MD104.ini ~/bin/ š"
cp -p MD104.ini ~/bin/
echo ""

echo "š Make End š"

