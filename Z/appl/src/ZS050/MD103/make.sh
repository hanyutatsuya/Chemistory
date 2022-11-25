#

echo "š MD103 Make š"
echo ""

echo "š rm *.o *.bnd MD103 š"
rm *.o *.bnd MD103
echo ""

echo "š make -f Makefile š"
make -f Makefile
echo ""

echo "š cp -p MD103 ~/bin/ š"
cp -p MD103 ~/bin/
echo "š cp -p MD103.ini ~/bin/ š"
cp -p MD103.ini ~/bin/
echo ""

echo "š Make End š"

