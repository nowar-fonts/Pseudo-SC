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
cp ../script-windows/run-nochat.bat "$R/一键生成字体包(默认).bat"
cp ../script-windows/run-chat.bat "$R/一键生成字体包(简化聊天字体).bat"
cp ../script-windows/project.url "$R/主页·使用说明.url"

7z a -mx -myx -ms=on Pseudo-SC-Toolkit-$VERSION.7z $R/
rar a -ma5 -m5 -s $R.rar $R/
