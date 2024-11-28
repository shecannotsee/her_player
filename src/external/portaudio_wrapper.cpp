#include "portaudio_wrapper.h"

std::atomic<int> portaudio_wrapper::instance_count = 0;
std::mutex portaudio_wrapper::init_mutex;