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
namespace mixer {

class AudioMixerController {
 public:
  AudioMixerController() { is_running_.store(true); };
  ~AudioMixerController() { snd_mixer_close(this->mixer_handle); };
  bool init_audio_mixer();
  bool set_audio_volume(int left_volume, int right_volume);

 private:
  std::atomic<bool> is_running_{false};
  long int volMin = 0, volMax = 0;
  snd_mixer_t *mixer_handle = nullptr;
  snd_mixer_elem_t *elem = nullptr;
  snd_mixer_selem_id_t *sid = nullptr;
};

}  // namespace mixer
}  // namespace audio

#ifdef __cplusplus
}
#endif
