#

echo "š JD112 Make š"
echo ""

echo "š rm *.o *.bnd JD112 š"
rm *.o *.bnd JD112
echo ""

echo "š make -f Makefile š"
make -f Makefile
echo ""

echo "š cp -p JD112 ~/bin/ š"
cp -p JD112 ~/bin/
echo "š cp -p JD112.ini ~/bin/ š"
cp -p JD112.ini ~/bin/
echo "š cp -p JD112_LOG.ini ~/bin/ š"
cp -p JD112_LOG.ini ~/bin/
echo ""

echo "š Make End š"

