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
#include <utility>
#include <vector>

#include "asound_driver.hpp"
#include "audio_file_analyzer.hpp"
#include "audio_mixer_controller.hpp"
#include "yaml-cpp/yaml.h"

#ifdef __cplusplus
extern "C" {
#endif

namespace audio {
namespace audio_play_task {

typedef enum {
  mute = 0,
  battery_check_failed,
  left_battery_offline,
  left_battery_online,
  right_battery_offline,
  right_battery_online,
  left_battery_low_power,
  right_battery_low_power,
  boot_up,
  down_finished,
  downing,
  controller_connected,
  controller_disconnected,
  enter_low_power_mode,
  exit_low_power_mode,
  imu_connected,
  imu_disconnected,
  over_speed,
  pms_check_failed,
  pms_check_succeed,
  pms_selftest_timeout,
  pose_status_error,
  shutdown,
  stand_up,
  turn_off_v48,
  low_power,
  motor_1_error,
  motor_2_error,
  motor_3_error,
  motor_4_error,
  motor_5_error,
  motor_6_error,
  motor_7_error,
  motor_8_error,
  audio_error,
  camera_error,
  camera_normal,
  infrared_tof_error,
  infrared_tof_succeed,
  interaction_port_error,
  interaction_poer_succeed,
  pose_error,
  pose_succeed,
  quadruped_mode_error,
  quadruped_mode_succeed,
  temperature_humidity_error,
  temperature_humidity_succeed,
  ultrasonic_wave_error,
  ultrasonic_wave_succeed,
  wifi_error,
  wifi_succeed,
} audio_play_task_status_t;

class AudioPlayTaskController {
  typedef std::function<bool(const std::string&)> CallbackFunc;

 public:
  AudioPlayTaskController() {
    is_running_.store(true);
    update_yaml_config();
    init_audio_task_status_map();
  }
  ~AudioPlayTaskController() {
    if (audio_task_thread != nullptr) {
      audio_task_thread->join();
    }
    audio_task_thread = nullptr;
    is_task_running_.store(false);
    is_running_.store(false);
  };

  // it should be a callback function
  bool add_audio_task_callback(CallbackFunc callback, const std::string& audio_file_path) {
    return callback(audio_file_path);
  }
  bool add_audio_task(const std::string& audio_file_path);
  bool start_audio_task();
  void exit_audio_task();
  std::string get_audio_play_task_file_path(
      audio_play_task_status_t audio_task);
  void update_yaml_config();

 private:
  std::atomic<bool> is_running_{false};
  std::atomic<bool> is_task_running_{false};
  std::queue<std::string> audio_queue;
  std::mutex audio_task_mutex;
  std::shared_ptr<std::thread> audio_task_thread;

  WAVHeader header;
  YAML::Node chinese_audio_files_config;
  YAML::Node english_audio_files_config;
  YAML::Node language_config;
  std::map<audio_play_task_status_t, std::string> audio_task_status_map;

  std::shared_ptr<audio::alsa_asound::ASoundDriver> asound_driver_api =
      std::make_shared<audio::alsa_asound::ASoundDriver>();

  std::shared_ptr<audio::audio_file_analyzer::AudioFileAnalyzer>
      audio_file_analyzer_api =
          std::make_shared<audio::audio_file_analyzer::AudioFileAnalyzer>();

  std::shared_ptr<audio::mixer::AudioMixerController>
      audio_mixer_controller_api =
          std::make_shared<audio::mixer::AudioMixerController>();

  void process_queue();
  bool if_is_chinese();
  void play_audio(const std::string& audio_file_path);
  void init_audio_task_status_map();
  const std::string* get_audio_task_status_map_string(
      audio_play_task_status_t audio_task) const;
};

}  // namespace audio_play_task
}  // namespace audio

#ifdef __cplusplus
}
#endif

#endif  // __AUDIO_PLAY_TASK_CONTROLLER_HPP__
