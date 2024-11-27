#!/bin/bash
project="her_player"
project_length=${#project}
# Get pwd string
path=$(pwd)
# Get last project_length chars
suffix="${path: -$project_length}"
if [ "$suffix" = "$project" ]; then
    echo "ok"
else
    echo "Path error.Please ensure that the last few strings after using pwd are "$project
    exit 1  # stop
fi

# get source code
git clone https://github.com/shecannotsee/ffmpeg_wrapper.git ./third_party/ffmpeg_wrapper/ || { echo "git clone failed"; exit 1; }
cd third_party
mv ffmpeg_wrapper ffmpeg_wrapper-src
mkdir ffmpeg_wrapper-1.0.0
cd ffmpeg_wrapper-1.0.0
install_path=$(pwd)
cd ..

# build
cd ffmpeg_wrapper-src
git checkout 1.0.0
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX="$install_path" \
  -DFFMPEG_ROOT_DIR=/home/shecannotsee/Desktop/sheer_third_party/libraries/ffmpeg-4.3 \
  -Dbuild_release=ON \
  -Dbuild_tests=OFF \
  -Dbuild_shared_libs=ON \
  .. || { echo "cmake execution failed"; exit 1; }
make -j9 || { echo "make execution failed"; exit 1; }
make install || { echo "make install failed"; exit 1; }
