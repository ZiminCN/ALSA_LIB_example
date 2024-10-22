#ifndef __AUDIO_PLAY_TASK_CONTROLLER_HPP__
#define __AUDIO_PLAY_TASK_CONTROLLER_HPP__

#include <unistd.h>

#include <algorithm>
#include <atomic>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <memory>
#include <mutex>
#include <numeric>
#include <queue>
#include <sstream>
#include <stack>
#include <string>
#include <thread>
#include <vector>

#include "asound_driver.hpp"
#include "audio_file_analyzer.hpp"
#include "audio_mixer_controller.hpp"

#ifdef __cplusplus
extern "C" {
#endif

namespace audio {
namespace audio_play_task {

class AudioPlayTaskController {
 public:
  AudioPlayTaskController() { is_running_.store(true); }
  ~AudioPlayTaskController() {
    if (audio_task_thread != nullptr) {
      audio_task_thread->join();
    }
    audio_task_thread = nullptr;
    is_task_running_.store(false);
    is_running_.store(false);
  };
  bool add_audio_task(const std::string& audio_file_path);
  bool start_audio_task();
  void exit_audio_task();

 private:
  std::atomic<bool> is_running_{false};
  std::atomic<bool> is_task_running_{false};
  std::queue<std::string> audio_queue;
  std::mutex audio_task_mutex;
  std::shared_ptr<std::thread> audio_task_thread;
  WAVHeader header;

  std::shared_ptr<audio::alsa_asound::ASoundDriver> asound_driver_api =
      std::make_shared<audio::alsa_asound::ASoundDriver>();

  std::shared_ptr<audio::audio_file_analyzer::AudioFileAnalyzer>
      audio_file_analyzer_api =
          std::make_shared<audio::audio_file_analyzer::AudioFileAnalyzer>();

  std::shared_ptr<audio::mixer::AudioMixerController>
      audio_mixer_controller_api =
          std::make_shared<audio::mixer::AudioMixerController>();

  void process_queue();
  void play_audio(const std::string& audio_file_path);
};

}  // namespace audio_play_task
}  // namespace audio

#ifdef __cplusplus
}
#endif

#endif  // __AUDIO_PLAY_TASK_CONTROLLER_HPP__
