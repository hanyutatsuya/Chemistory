#

echo "š ZD999rebind Make š"
echo ""

echo "š rm *.o ZD999rebind š"
rm *.o ZD999rebind
echo ""

echo "š make -f Makefile š"
make -f Makefile
echo ""

echo "š cp -p ZD999rebind ~/bin/ š"
make install
echo ""

echo "š Make End š"

