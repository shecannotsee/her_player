#include <ffmpeg_wrapper.h>
#include <portaudio.h>
#include <she_test.h>

#include <thread>

namespace {
const std::string wav_path = "../resource/Something_Just_Like_this.wav";  // 修改为 WAV 文件路径
}  // namespace

TEST2(validation, play_mp3_test) {  // 修改为 play_wav_test（更贴切）
  demux wav;
  wav.open(wav_path, {});

  av_codec_context_support ctx;

  // 假设解码器支持 WAV 格式（PCM）
  decode decoder(wav.get_codec_id<demux::type::audio>());
  decoder.create_decoder(ctx.add_avcodec_parameters<demux::type::audio>(wav));

  /********************************************************************************************************************/
  PaError err = Pa_Initialize();
  if (err != paNoError) {
    std::cerr << "PortAudio error: " << Pa_GetErrorText(err) << std::endl;
    exit(1);
  }
  PaStream *stream;
  // 设置正确的通道数和采样率
  err = Pa_OpenDefaultStream(&stream,
                             0,  // no input channels
                             wav.get_codec_parameters<demux::type::audio>()->channels,
                             paInt16,  // sample format
                             wav.get_codec_parameters<demux::type::audio>()->sample_rate,
                             256,   // frames per buffer
                             NULL,  // no callback, use blocking API
                             NULL   // no callback user data
  );
  if (err != paNoError) {
    std::cerr << "PortAudio error: " << Pa_GetErrorText(err) << std::endl;
    return;
  }

  // 启动音频流
  err = Pa_StartStream(stream);
  if (err != paNoError) {
    std::cerr << "PortAudio error: " << Pa_GetErrorText(err) << std::endl;
    return;
  }
  /********************************************************************************************************************/

  int count = 0;
  std::cout << "Playing " << wav_path << std::endl;
  for (uint32_t size = 1; size != 0;) {
    const auto data = wav.start_receiving<demux::type::audio>(1);

    size = data.size();

    for (const auto &[type, pkt] : data) {
      auto pcm_list = decoder.decoding(pkt);
      // 解码后的音频数据
      for (auto &frame : pcm_list) {
        // 在这里进行播放
        Pa_WriteStream(stream, frame.get()->data[0], frame.get()->nb_samples);
        count++;
        if (count % 100 == 0) {
          std::cout << count << std::endl;
        }
      }
    }
  }
  std::cout << "Playing done." << std::endl;

  /********************************************************************************************************************/
  // 停止音频流
  err = Pa_StopStream(stream);
  if (err != paNoError) {
    std::cerr << "PortAudio error: " << Pa_GetErrorText(err) << std::endl;
    return;
  }

  // 关闭音频流
  Pa_CloseStream(stream);
  /********************************************************************************************************************/
}
