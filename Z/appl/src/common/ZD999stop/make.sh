#

echo "�� ZD999stop Make ��"
echo ""

echo "�� rm *.o ZD999stop ��"
rm *.o ZD999stop
echo ""

echo "�� make -f Makefile ��"
make -f Makefile
echo ""

echo "�� cp -p ZD999stop ~/bin/ ��"
make install
echo ""

echo "�� Make End ��"

