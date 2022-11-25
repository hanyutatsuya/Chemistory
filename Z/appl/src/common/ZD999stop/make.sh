#

echo "š ZD999stop Make š"
echo ""

echo "š rm *.o ZD999stop š"
rm *.o ZD999stop
echo ""

echo "š make -f Makefile š"
make -f Makefile
echo ""

echo "š cp -p ZD999stop ~/bin/ š"
make install
echo ""

echo "š Make End š"

