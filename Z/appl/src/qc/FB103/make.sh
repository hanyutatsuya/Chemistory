#

echo "š FB103 Make š"
echo ""

echo "š rm *.o *.bnd FB103 š"
make clean
echo ""

echo "š make -f Makefile š"
make -f Makefile
echo ""

echo "š cp -p FB103 ~/bin/ š"
cp -p FB103 ~/bin/
echo "š cp -p FB103.ini ~/bin/ š"
cp -p FB103.ini ~/bin/
echo ""

echo "š Make End š"

