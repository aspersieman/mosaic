#!/bin/bash

sudo apt install -y g++ cmake make git libgtk2.0-dev pkg-config

git clone git@github.com:opencv/opencv.git ~/src/opencv

cd ~/src/opencv

mkdir -p build && cd build

# Next, generate the build scripts using cmake
cmake ../

# build the source using make
make -j4

# Install the OpenCV package
sudo make install
