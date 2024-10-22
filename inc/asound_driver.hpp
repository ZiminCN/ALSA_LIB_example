#ifndef __ASOUND_DRIVER_HPP__
#define __ASOUND_DRIVER_HPP__

#include <alsa/asoundlib.h>
#include <audio_struct_define.h>
#include <unistd.h>

#include <algorithm>
#include <atomic>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <memory>
#include <numeric>
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

namespace alsa_asound {

#define PCM_NAME "hw:2,0"
#define CTL_NAME "hw:2"
#define DEFAULT_PCM_NAME "default"
#define PLAYBACK_FILE "ybxyq.wav"
// ALSA buffer size for playback will be multiplied by this number (max: 16)
#define ALSA_PLAYBACK_BUFFER_MULTIPLY 10
#define ALSA_PLAYBACK_BUFFER 100

class ASoundDriver {
 public:
  ASoundDriver() { is_running_.store(true); };
  ~ASoundDriver() {
    if (this->playback_handle) {
      snd_pcm_close(this->playback_handle);
    }
  };
  bool init_audio_pcm(const char *name, snd_pcm_format_t format);
  bool try_to_playback_audio(WAVHeader wav_header, const std::string &filename);

  char *get_audio_buffer() { return this->audio_buffer; }
  int get_buffer_size() { return this->buffer_size; }
  snd_pcm_t *get_playback_handle() { return this->playback_handle; }
  snd_pcm_uframes_t get_frames() { return this->frames; }

 private:
  std::atomic<bool> is_running_{false};
  unsigned int stream_rate = 44100;
  snd_pcm_hw_params_t *hw_params;
  snd_pcm_t *playback_handle = nullptr;
  int dir;
  snd_pcm_uframes_t frames = 64;
  long loops = 5000000;
  int buffer_size;
  char *audio_buffer;
};

}  // namespace alsa_asound

}  // namespace audio

#ifdef __cplusplus
}
#endif

#endif  // ALSA_ASOUND_DRIVER_HPP_