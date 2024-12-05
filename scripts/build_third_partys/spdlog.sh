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
git clone https://github.com/gabime/spdlog.git ./third_party/spdlog/ || \
  { echo "Failed to clone spdlog repository."; exit 1; }
cd third_party
mv spdlog spdlog-src
mkdir spdlog-v1.10.0
cd spdlog-v1.10.0
install_path=$(pwd)
cd ..

# build
cd spdlog-src
git checkout v1.10.0 || \
  { echo "Failed to checkout v1.10.0 of spdlog."; exit 1; }

cp -r ./include "$install_path" || \
  { echo "cp failed."; exit 1; }