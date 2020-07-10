#!/bin/bash

rm -rf appimage_packaging

mkdir -p appimage_packaging

cd appimage_packaging

mkdir -p appfolder/usr/bin

cp -r ../media appfolder/usr/bin

echo "Downloading AppImage..."

wget -cnv https://github.com/linuxdeploy/linuxdeploy/releases/download/continuous/linuxdeploy-x86_64.AppImage

echo "Download finished !"

chmod +x linuxdeploy-x86_64.AppImage

mkdir -p appfolder

./linuxdeploy-x86_64.AppImage --appdir appfolder --output appimage -d ../misc/desktop_file.desktop -i ../misc/icon.png -e ../build/src/menu/Menu

mv Samuel-Menu-*.AppImage SamuelMenu.AppImage
