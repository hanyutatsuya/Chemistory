#

echo "š FD101 Make š"
echo ""

echo "š rm *.o *.bnd FD101 š"
make clean
echo ""

echo "š make -f Makefile š"
make -f Makefile
echo ""

echo "š cp -p FD101 ~/bin/ š"
cp -p FD101 ~/bin/
echo "š cp -p FD101.ini ~/bin/ š"
cp -p FD101.ini ~/bin/
echo ""

echo "š Make End š"

