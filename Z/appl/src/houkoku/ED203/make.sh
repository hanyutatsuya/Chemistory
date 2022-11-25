#

echo "š ED203 Make š"
echo ""

echo "š rm *.o *.bnd ED203 š"
rm *.o *.bnd ED203
echo ""

echo "š make -f Makefile š"
make -f Makefile
echo ""

echo "š cp -p ED203 ~/bin/ š"
cp -p ED203 ~/bin/
echo "š cp -p ED203.ini ~/bin/ š"
cp -p ED203.ini ~/bin/
echo "š cp -p ED203_LOG.ini ~/bin/ š"
cp -p ED203_LOG.ini ~/bin/
echo ""

echo "š Make End š"

