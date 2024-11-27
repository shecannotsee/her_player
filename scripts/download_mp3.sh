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
wget -O ./resource/Something_Just_Like_this.mp3 "https://api.liumingye.cn/m/api/link?id=b3f634HzOLrfMF9SfoF5rMwGTGRJWlMqEnjJ6ffUFiKV0TWD3PA&quality=320&_t=1732703020890&token=20241016.6d5505af28860854c5aa97ab38ace55d"
ffmpeg -i ./resource/Something_Just_Like_this.mp3 -ar 44100 -ac 2 ./resource/Something_Just_Like_this.wav
