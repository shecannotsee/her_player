#include <external/spdlog_wrapper.h>
#include <ffmpeg_wrapper.h>
#include <she_test.h>

namespace {
const std::string wav_path = "../resource/Something_Just_Like_this.wav";  // 修改为 WAV 文件路径
auto logger                = spdlog_wrapper::get_logger("test");
}  // namespace

TEST2(validation, get_wav_duration) {
  demux wav;
  wav.open(wav_path, {});

  av_codec_context_support ctx;

  // 假设解码器支持 WAV 格式（PCM）
  decode decoder(wav.get_codec_id<demux::type::audio>());
  decoder.create_decoder(ctx.add_avcodec_parameters<demux::type::audio>(wav));

  const int sample_rate = wav.get_codec_parameters<demux::type::audio>()->sample_rate;
  logger->info("Sample rate: {}", sample_rate);

  for (uint32_t size = 1; size != 0;) {
    const auto data = wav.start_receiving<demux::type::audio>(1);

    size = data.size();
    for (const auto &[type, pkt] : data) {
      auto pcm_list = decoder.decoding(pkt);
      // 解码后的音频数据
      for (auto &frame : pcm_list) {
        // 解码后的帧
        const int samples_per_frame = frame.get()->nb_samples;
        logger->info("Frames per second: {} fps", sample_rate / samples_per_frame);
        return;;
      }
    }

  }

}
