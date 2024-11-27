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
git clone https://github.com/PortAudio/portaudio.git ./third_party/portaudio/ || { echo "git clone failed"; exit 1; }
cd third_party
mv portaudio portaudio-src
mkdir portaudio-v19.7.0
cd portaudio-v19.7.0
install_path=$(pwd)
cd ..

# build
cd portaudio-src
git checkout v19.7.0
./configure --prefix="$install_path" || { echo "configure execution failed"; exit 1; }
make -j9 || { echo "make execution failed"; exit 1; }
make install || { echo "make install failed"; exit 1; }
