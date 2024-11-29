#ifndef HER_PLAYER_EXTERNAL_PORTAUDIO_WRAPPER_H
#define HER_PLAYER_EXTERNAL_PORTAUDIO_WRAPPER_H

#include <portaudio.h>

#include <mutex>

class portaudio_wrapper {
  static int instance_count;     // 计数器，追踪活跃的实例数量
  static std::mutex init_mutex;  // 保护初始化和终止操作
  PaStream* stream_;

 public:
  portaudio_wrapper() noexcept;

  ~portaudio_wrapper();

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

  void open(const open_param& param);

  void start() const;

  void sleep(uint64_t millisecond);

  void stop() const;

  void write(const void* buffer, unsigned long frames) const;
};

#endif  // HER_PLAYER_EXTERNAL_PORTAUDIO_WRAPPER_H
