#

echo "�� ZD999rebind Make ��"
echo ""

echo "�� rm *.o ZD999rebind ��"
rm *.o ZD999rebind
echo ""

echo "�� make -f Makefile ��"
make -f Makefile
echo ""

echo "�� cp -p ZD999rebind ~/bin/ ��"
make install
echo ""

echo "�� Make End ��"

