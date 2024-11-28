#ifndef HER_PLAYER_EXTERNAL_PORTAUDIO_WRAPPER_H
#define HER_PLAYER_EXTERNAL_PORTAUDIO_WRAPPER_H

#include <portaudio.h>

#include <atomic>
#include <fstream>
#include <list>
#include <mutex>
#include <stdexcept>

class portaudio_wrapper {
  static std::atomic<int> instance_count;  // 计数器，追踪活跃的实例数量
  static std::mutex init_mutex;            // 保护初始化和终止操作
  PaStream* stream_;

 public:
  portaudio_wrapper() noexcept {
    // 如果是第一个实例，初始化 PortAudio
    std::lock_guard<std::mutex> lock(init_mutex);
    if (instance_count == 0) {
      if (const auto err = Pa_Initialize(); err != paNoError) {
        throw std::runtime_error("PortAudio Initialize error: " + std::string(Pa_GetErrorText(err)));
      }
    }
    ++instance_count;
  }

  ~portaudio_wrapper() {
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

  struct open_param {
    static constexpr int SAMPLE_RATE = 44100;
    int numInputChannels{0};                /* no input channels */
    int numOutputChannels{2};               /* stereo output */
    PaSampleFormat sampleFormat{paFloat32}; /* 32 bit floating point output */
    double sampleRate{SAMPLE_RATE};         /* */
    unsigned long framesPerBuffer{256};     /* frames per buffer, i.e. the number of sample frames that PortAudio will
                     request from     the callback. Many apps  may want to use  paFramesPerBufferUnspecified, which  tells
                     PortAudio to pick     the best, possibly changing, buffer size.*/
    PaStreamCallback* streamCallback{nullptr}; /* this is your callback function */
    void* userData{nullptr};                   /*This is a pointer that will be passed to your callback*/
  };

  void open(const open_param& param) {
    /* Open an audio I/O stream. */
    const auto err =
        Pa_OpenDefaultStream(&stream_, param.numInputChannels, param.numOutputChannels, param.sampleFormat,
                             param.sampleRate, param.framesPerBuffer, param.streamCallback, param.userData);
    if (err != paNoError) {
      throw std::runtime_error("PortAudio error: " + std::string(Pa_GetErrorText(err)));
    }
  }
  void start() const {
    if (const auto err = Pa_StartStream(stream_); err != paNoError) {
      throw std::runtime_error("PortAudio start stream error: " + std::string(Pa_GetErrorText(err)));
    }
  }
  void sleep(uint64_t msec) {
    Pa_Sleep(msec);
  }
  void stop() const {
    if (const auto err = Pa_StopStream(stream_); err != paNoError) {
      throw std::runtime_error("PortAudio stop stream error: " + std::string(Pa_GetErrorText(err)));
    }
  }
  void write(const void* buffer, const unsigned long frames) const {
    if (const auto err = Pa_WriteStream(stream_, buffer, frames); err != paNoError) {
      throw std::runtime_error("PortAudio write error: " + std::string(Pa_GetErrorText(err)));
    }
  }

};

#endif  // HER_PLAYER_EXTERNAL_PORTAUDIO_WRAPPER_H
