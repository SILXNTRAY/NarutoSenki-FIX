echo "Building tolua++"
cd tools/tolua++
./build.sh

echo ""

cd ../../
make DEBUG=0 -j
