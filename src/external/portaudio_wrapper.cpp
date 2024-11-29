#include "portaudio_wrapper.h"

#include <fstream>
#include <mutex>
#include <stdexcept>

int portaudio_wrapper::instance_count = 0;
std::mutex portaudio_wrapper::init_mutex;

portaudio_wrapper::portaudio_wrapper() noexcept : stream_(nullptr) {
  // 如果是第一个实例，初始化 PortAudio
  std::lock_guard<std::mutex> lock(init_mutex);
  if (instance_count == 0) {
    if (const auto err = Pa_Initialize(); err != paNoError) {
      throw std::runtime_error("PortAudio Initialize error: " + std::string(Pa_GetErrorText(err)));
    }
  }
  ++instance_count;
}

portaudio_wrapper::~portaudio_wrapper() {
  // 检查是否停止
  if (const auto err = Pa_IsStreamStopped(stream_); err != paContinue) {
    stop();
  }

  // 关闭流, 释放资源
  if (const auto err = Pa_CloseStream(stream_); err != paNoError) {
    printf("PortAudio cloae stream error: %s\n", Pa_GetErrorText(err));
  }

  // 减少实例计数器，如果是最后一个实例，终止 PortAudio
  std::lock_guard<std::mutex> lock(init_mutex);
  if (--instance_count == 0) {
    if (const auto err = Pa_Terminate(); err != paNoError) {
      printf("PortAudio Terminate error: %s\n", Pa_GetErrorText(err));
    }
  }
}

void portaudio_wrapper::open(const open_param& param) {
  /* Open an audio I/O stream. */
  const auto err = Pa_OpenDefaultStream(&stream_,
                                        param.numInputChannels,   //
                                        param.numOutputChannels,  //
                                        param.sampleFormat,       //
                                        param.sampleRate,         //
                                        param.framesPerBuffer,    //
                                        param.streamCallback,     //
                                        param.userData);
  if (err != paNoError) {
    throw std::runtime_error("PortAudio error: " + std::string(Pa_GetErrorText(err)));
  }
}

void portaudio_wrapper::start() const {
  if (const auto err = Pa_StartStream(stream_); err != paNoError) {
    throw std::runtime_error("PortAudio start stream error: " + std::string(Pa_GetErrorText(err)));
  }
}

void portaudio_wrapper::sleep(const uint64_t millisecond) {
  Pa_Sleep(static_cast<long>(millisecond));
}

void portaudio_wrapper::stop() const {
  if (const auto err = Pa_StopStream(stream_); err != paNoError) {
    throw std::runtime_error("PortAudio stop stream error: " + std::string(Pa_GetErrorText(err)));
  }
}

void portaudio_wrapper::write(const void* buffer, const unsigned long frames) const {
  if (const auto err = Pa_WriteStream(stream_, buffer, frames); err != paNoError) {
    throw std::runtime_error("PortAudio write error: " + std::string(Pa_GetErrorText(err)));
  }
}

