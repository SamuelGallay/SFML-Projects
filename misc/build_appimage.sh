#!/bin/bash

wget -cnv https://github.com/linuxdeploy/linuxdeploy/releases/download/continuous/linuxdeploy-x86_64.AppImage

chmod +x linuxdeploy-x86_64.AppImage

mkdir -p appfolder

./linuxdeploy-x86_64.AppImage --appdir appfolder --output appimage -d ../misc/desktop_file.desktop -i ../misc/icon.png -e ../install/Example



