#include <alsa/asoundlib.h>
#include <audio_struct_define.h>
#include <unistd.h>

#include <algorithm>
#include <atomic>
#include <functional>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <memory>
#include <numeric>
#include <optional>
#include <queue>
#include <sstream>
#include <stack>
#include <string>
#include <thread>
#include <vector>

#ifdef __cplusplus
extern "C" {
#endif

namespace audio {

namespace audio_file_analyzer {

class AudioFileAnalyzer {
  typedef std::function<void()> CallbackFunc;
  typedef std::function<void(WAVHeader)> WAVHeaderCallbackFunc;

 public:
  AudioFileAnalyzer() { is_running_.store(true); };
  ~AudioFileAnalyzer() = default;
  void wav_header_cb(WAVHeaderCallbackFunc callback, void *data);
  void test_cb(CallbackFunc callback);
  void test_callback() { printf("test success!\r\n"); }
  WAVHeader open_wav_file(const std::string &filename);
  WAVHeader getWavHeader_T() {
    WAVHeader header;
    return header;
  }

 private:
  std::atomic<bool> is_running_{false};
};  // namespace audio_file_analyzer

}  // namespace audio_file_analyzer

}  // namespace audio

#ifdef __cplusplus
}
#endif
