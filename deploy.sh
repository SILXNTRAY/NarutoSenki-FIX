#!/bin/bash
echo "Building NarutoSenki Project ..."

./build-release.sh

mkdir Build/NarutoSenki

rm -rf Build/NarutoSenki/Data
rm -rf Build/NarutoSenki/lua
cp projects/NarutoSenki/Resources Build/NarutoSenki/Data -r
cp projects/NarutoSenki/lua       Build/NarutoSenki/lua  -r

cp projects/NarutoSenki/proj.linux/bin/release/NarutoSenki Build/NarutoSenki/NarutoSenki

cp lib/linux/release/libcocos2d.so       Build/NarutoSenki/libcocos2d.so
cp lib/linux/release/libcocosdenshion.so Build/NarutoSenki/libcocosdenshion.so
cp lib/linux/release/liblua.so           Build/NarutoSenki/liblua.so

cp Build/Templates/run.sh Build/NarutoSenki/run.sh

cd Build
tar -zcvf NarutoSenki.tar.gz ./NarutoSenki

echo "done"
