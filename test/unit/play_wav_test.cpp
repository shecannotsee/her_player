#include <external/portaudio_wrapper.h>
#include <ffmpeg_wrapper.h>
#include <she_test.h>

#include <thread>

#include "external/spdlog_wrapper.h"

namespace {
const std::string wav_path = "../resource/Something_Just_Like_this.wav";  // 修改为 WAV 文件路径
auto logger                = spdlog_wrapper::get_logger("test");
}  // namespace

TEST2(unit, play_wav_test) {
  demux wav;
  wav.open(wav_path, {});

  av_codec_context_support ctx;

  // 假设解码器支持 WAV 格式（PCM）
  decode decoder(wav.get_codec_id<demux::type::audio>());
  decoder.create_decoder(ctx.add_avcodec_parameters<demux::type::audio>(wav));

  portaudio_wrapper player;
  player.open([&] {
    portaudio_wrapper::open_param param;
    param.numInputChannels  = 0;
    param.numOutputChannels = wav.get_codec_parameters<demux::type::audio>()->channels;
    param.sampleFormat      = paInt16;
    param.sampleRate        = wav.get_codec_parameters<demux::type::audio>()->sample_rate;
    param.framesPerBuffer   = 256;
    param.streamCallback    = nullptr;
    param.userData          = nullptr;
    return param;
  }());
  player.start();

  int count = 0;
  logger->info("start playing");
  for (uint32_t size = 1; size != 0;) {
    const auto data = wav.start_receiving<demux::type::audio>(1);

    size = data.size();

    for (const auto &[type, pkt] : data) {
      auto pcm_list = decoder.decoding(pkt);
      // 解码后的音频数据
      for (auto &frame : pcm_list) {
        // 在这里进行播放
        player.write(frame.get()->data[0], frame.get()->nb_samples);
        count++;
        if (count % 100 == 0) {
          logger->info("{}", count);
        }
      }
    }

  }

  logger->info("Playing done.");
}
