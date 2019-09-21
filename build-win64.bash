#! /bin/bash

source ./version.bash

VERSION=$VERSION-win64

x86_64-w64-mingw32-g++ src/pseudo-sc.cpp src/iostream.cpp -Isrc/ -std=c++2a -O3 -static -o bin-win64/pseudo-sc.exe
strip bin-win64/pseudo-sc.exe

mkdir -p release
cd release


R=台服伪简体工具包-$VERSION

mkdir -p $R

cp ../bin-win64/{otfccbuild,otfccdump,pseudo-sc}.exe $R/
cp ../script-windows/run.bat $R/一键生成.bat

7z a -mx -myx -ms=on Pseudo-SC-$VERSION.7z $R/
rar a -ma5 -m5 -s $R.rar $R/
