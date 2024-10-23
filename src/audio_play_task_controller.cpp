#include "audio_play_task_controller.hpp"

namespace audio {

namespace audio_play_task {

void AudioPlayTaskController::init_audio_task_status_map() {
  this->audio_task_status_map.clear();
  this->audio_task_status_map.insert(
      std::make_pair(audio_play_task_status_t::mute, "mute"));
  this->audio_task_status_map.insert(std::make_pair(
      audio_play_task_status_t::battery_check_failed, "battery_check_failed"));
  this->audio_task_status_map.insert(std::make_pair(
      audio_play_task_status_t::left_battery_offline, "left_battery_offline"));
  this->audio_task_status_map.insert(std::make_pair(
      audio_play_task_status_t::left_battery_online, "left_battery_online"));
  this->audio_task_status_map.insert(
      std::make_pair(audio_play_task_status_t::right_battery_offline,
                     "right_battery_offline"));
  this->audio_task_status_map.insert(std::make_pair(
      audio_play_task_status_t::right_battery_online, "right_battery_online"));
  this->audio_task_status_map.insert(
      std::make_pair(audio_play_task_status_t::left_battery_low_power,
                     "left_battery_low_power"));
  this->audio_task_status_map.insert(
      std::make_pair(audio_play_task_status_t::right_battery_low_power,
                     "right_battery_low_power"));
  this->audio_task_status_map.insert(
      std::make_pair(audio_play_task_status_t::boot_up, "boot_up"));
  this->audio_task_status_map.insert(
      std::make_pair(audio_play_task_status_t::down_finished, "down_finished"));
  this->audio_task_status_map.insert(
      std::make_pair(audio_play_task_status_t::downing, "downing"));
  this->audio_task_status_map.insert(std::make_pair(
      audio_play_task_status_t::controller_connected, "controller_connected"));
  this->audio_task_status_map.insert(
      std::make_pair(audio_play_task_status_t::controller_disconnected,
                     "controller_disconnected"));
  this->audio_task_status_map.insert(std::make_pair(
      audio_play_task_status_t::enter_low_power_mode, "enter_low_power_mode"));
  this->audio_task_status_map.insert(std::make_pair(
      audio_play_task_status_t::exit_low_power_mode, "exit_low_power_mode"));
  this->audio_task_status_map.insert(
      std::make_pair(audio_play_task_status_t::imu_connected, "imu_connected"));
  this->audio_task_status_map.insert(std::make_pair(
      audio_play_task_status_t::imu_disconnected, "imu_disconnected"));
  this->audio_task_status_map.insert(
      std::make_pair(audio_play_task_status_t::over_speed, "over_speed"));
  this->audio_task_status_map.insert(std::make_pair(
      audio_play_task_status_t::pms_check_failed, "pms_check_failed"));
  this->audio_task_status_map.insert(std::make_pair(
      audio_play_task_status_t::pms_check_succeed, "pms_check_succeed"));
  this->audio_task_status_map.insert(std::make_pair(
      audio_play_task_status_t::pms_selftest_timeout, "pms_selftest_timeout"));
  this->audio_task_status_map.insert(std::make_pair(
      audio_play_task_status_t::pose_status_error, "pose_status_error"));
  this->audio_task_status_map.insert(
      std::make_pair(audio_play_task_status_t::shutdown, "shutdown"));
  this->audio_task_status_map.insert(
      std::make_pair(audio_play_task_status_t::stand_up, "stand_up"));
  this->audio_task_status_map.insert(
      std::make_pair(audio_play_task_status_t::turn_off_v48, "turn_off_v48"));
  this->audio_task_status_map.insert(
      std::make_pair(audio_play_task_status_t::low_power, "low_power"));
  this->audio_task_status_map.insert(
      std::make_pair(audio_play_task_status_t::motor_1_error, "motor_1_error"));
  this->audio_task_status_map.insert(
      std::make_pair(audio_play_task_status_t::motor_2_error, "motor_2_error"));
  this->audio_task_status_map.insert(
      std::make_pair(audio_play_task_status_t::motor_3_error, "motor_3_error"));
  this->audio_task_status_map.insert(
      std::make_pair(audio_play_task_status_t::motor_4_error, "motor_4_error"));
  this->audio_task_status_map.insert(
      std::make_pair(audio_play_task_status_t::motor_5_error, "motor_5_error"));
  this->audio_task_status_map.insert(
      std::make_pair(audio_play_task_status_t::motor_6_error, "motor_6_error"));
  this->audio_task_status_map.insert(
      std::make_pair(audio_play_task_status_t::motor_7_error, "motor_7_error"));
  this->audio_task_status_map.insert(
      std::make_pair(audio_play_task_status_t::motor_8_error, "motor_8_error"));
  this->audio_task_status_map.insert(
      std::make_pair(audio_play_task_status_t::audio_error, "audio_error"));
  this->audio_task_status_map.insert(
      std::make_pair(audio_play_task_status_t::camera_error, "camera_error"));
  this->audio_task_status_map.insert(
      std::make_pair(audio_play_task_status_t::camera_normal, "camera_normal"));
  this->audio_task_status_map.insert(std::make_pair(
      audio_play_task_status_t::infrared_tof_error, "infrared_tof_error"));
  this->audio_task_status_map.insert(std::make_pair(
      audio_play_task_status_t::infrared_tof_succeed, "infrared_tof_succeed"));
  this->audio_task_status_map.insert(
      std::make_pair(audio_play_task_status_t::interaction_port_error,
                     "interaction_port_error"));
  this->audio_task_status_map.insert(
      std::make_pair(audio_play_task_status_t::interaction_poer_succeed,
                     "interaction_poer_succeed"));
  this->audio_task_status_map.insert(
      std::make_pair(audio_play_task_status_t::pose_error, "pose_error"));
  this->audio_task_status_map.insert(
      std::make_pair(audio_play_task_status_t::pose_succeed, "pose_succeed"));
  this->audio_task_status_map.insert(std::make_pair(
      audio_play_task_status_t::quadruped_mode_error, "quadruped_mode_error"));
  this->audio_task_status_map.insert(
      std::make_pair(audio_play_task_status_t::quadruped_mode_succeed,
                     "quadruped_mode_succeed"));
  this->audio_task_status_map.insert(
      std::make_pair(audio_play_task_status_t::temperature_humidity_error,
                     "temperature_humidity_error"));
  this->audio_task_status_map.insert(
      std::make_pair(audio_play_task_status_t::temperature_humidity_succeed,
                     "temperature_humidity_succeed"));
  this->audio_task_status_map.insert(
      std::make_pair(audio_play_task_status_t::ultrasonic_wave_error,
                     "ultrasonic_wave_error"));
  this->audio_task_status_map.insert(
      std::make_pair(audio_play_task_status_t::ultrasonic_wave_succeed,
                     "ultrasonic_wave_succeed"));
  this->audio_task_status_map.insert(
      std::make_pair(audio_play_task_status_t::wifi_error, "wifi_error"));
  this->audio_task_status_map.insert(
      std::make_pair(audio_play_task_status_t::wifi_succeed, "wifi_succeed"));
}

bool AudioPlayTaskController::add_audio_task(
    const std::string& audio_file_path) {
  if (!std::filesystem::exists(audio_file_path)) {
    printf("[Error] [%s] does not exist\n", audio_file_path.c_str());
    return false;
  }

  this->audio_task_mutex.lock();
  this->audio_queue.push(audio_file_path);
  this->audio_task_mutex.unlock();
  return true;
}

void AudioPlayTaskController::play_audio(const std::string& audio_path) {
  this->asound_driver_api->try_to_playback_audio(this->header, audio_path);
}

void AudioPlayTaskController::process_queue() {
  if (!this->is_task_running_.load()) {
    printf("[Debug] is_task_running_ is false, return");
    return;
  }

  printf(
      "[Success] Task Thread AudioPlayTaskController::process_queue() "
      "start\r\n");

  while (this->is_task_running_.load()) {
    if (this->audio_queue.empty()) {
      // playback mute wav file
      // this->asound_driver_api->try_to_playback_audio(
      //     this->header,
      //     "/home/ziminrsp/code_ws/music-source/44100/Chinese/mute.wav");
      printf("audio queue is empty\r\n");
    } else {
      // playback pueue front wav file
      std::cout << "current audio_queue front is [" << this->audio_queue.front()
                << "]" << std::endl;
      printf("current audio_queue size is [%d]\r\n", this->audio_queue.size());

      play_audio(this->audio_queue.front());

      // then pop
      this->audio_task_mutex.lock();
      this->audio_queue.pop();
      this->audio_task_mutex.unlock();
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  }

  this->audio_task_thread->join();
  audio_task_thread = nullptr;
  this->audio_task_mutex.unlock();

  // empty the queue
  while (!audio_queue.empty()) {
    audio_queue.pop();
  }

  this->is_task_running_.store(false);
}

bool AudioPlayTaskController::start_audio_task() {
  if (!this->is_running_.load()) {
    return false;
  }

  printf("\r\n");
  printf("[Debug] Enter start_audio_task\r\n");

  this->asound_driver_api->init_audio_pcm(PCM_NAME, SND_PCM_FORMAT_S16_LE);

  this->audio_mixer_controller_api->init_audio_mixer();

  this->audio_mixer_controller_api->set_audio_volume(127, 127);

  header = this->audio_file_analyzer_api->getWavHeader_T();

  this->is_task_running_.store(true);

  try {
    if (is_task_running_.load()) {
      audio_task_thread = std::make_shared<std::thread>(
          &AudioPlayTaskController::process_queue, this);
    }
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
    printf("[Failed] Task Thread created failed!\r\n");
    return false;
  }

  printf("[Debug] Exit start_audio_task \r\n");

  return true;
}

void AudioPlayTaskController::exit_audio_task() {
  if (this->audio_task_thread != nullptr) {
    this->audio_task_thread->join();
  }
  this->audio_task_thread = nullptr;
  this->audio_task_mutex.unlock();

  // empty the queue
  while (!audio_queue.empty()) {
    audio_queue.pop();
  }

  this->is_task_running_.store(false);
}

void AudioPlayTaskController::update_yaml_config() {
  chinese_audio_files_config =
      YAML::LoadFile("../config/chinese_audio_file.yaml");
  english_audio_files_config =
      YAML::LoadFile("../config/english_audio_file.yaml");
  language_config = YAML::LoadFile("../config/language_config.yaml");
}

bool AudioPlayTaskController::if_is_chinese() {
  std::string name;
  if (this->language_config["is_chinese"]) {
    name = language_config["is_chinese"].as<std::string>();
    printf("[Debug]: is_chinese = %s \r\n", name.c_str());
    if (name == "true") {
      return true;
    } else {
      return false;
    }
  } else {
    printf("[Error]: language_config.yaml Error!\r\n");
  }
  return true;
}

const std::string* AudioPlayTaskController::get_audio_task_status_map_string(
    audio_play_task_status_t audio_task) const {
  auto it = audio_task_status_map.find(audio_task);
  if (it != audio_task_status_map.end()) {
    return &(it->second);
  } else {
    static const std::string return_unknown = "Unknown";
    return &return_unknown;
  }
}

std::string AudioPlayTaskController::get_audio_play_task_file_path(
    audio_play_task_status_t audio_task) {
  update_yaml_config();
  std::string return_unknown = "Unknown";
  std::string audio_name, audio_path, get_task_string_name;

  for (const auto& audio_file : english_audio_files_config["audio_files"]) {
    audio_name = audio_file["name"].as<std::string>();
    // std::cout << "audio_name is " << audio_name << " \r\n" << std::endl;

    get_task_string_name = *get_audio_task_status_map_string(audio_task);
    // std::cout << "get_task_string_name is " << get_task_string_name << " \r\n" << std::endl;
    if ((get_task_string_name != "Unknown")&&(audio_name == get_task_string_name)) {
      audio_path = audio_file["path"].as<std::string>();
      // std::cout << "audio_path is " << audio_path << " \r\n" << std::endl;
      return audio_path;
    }
  }

  std::cout << "[Error]: input audio name : "<< audio_name << " is error! \r\n" << std::endl;
  return return_unknown;
}

}  // namespace audio_play_task
}  // namespace audio