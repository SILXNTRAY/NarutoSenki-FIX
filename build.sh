echo "Building tolua++"
cd tools/tolua++
./build.sh

echo ""

cd ../../
make DEBUG=1 -j
