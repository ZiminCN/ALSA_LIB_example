#include <unistd.h>

#include <algorithm>
#include <atomic>
#include <functional>
#include <iostream>
#include <iterator>
#include <list>
#include <main.hpp>
#include <map>
#include <memory>
#include <numeric>
#include <queue>
#include <sstream>
#include <stack>
#include <string>
#include <thread>
#include <vector>

int main() {
  std::cout << "Hello World!" << std::endl;
  std::shared_ptr<audio::audio_play_task::AudioPlayTaskController>
      audio_play_task_api =
          std::make_shared<audio::audio_play_task::AudioPlayTaskController>();

    std::string wav_file_path = "/home/ziminrsp/huiliu_fangdatong.wav";

  audio_play_task_api->add_audio_task_callback(std::bind(&audio::audio_play_task::AudioPlayTaskController::add_audio_task, audio_play_task_api, std::placeholders::_1), audio_play_task_api->get_audio_play_task_file_path(audio::audio_play_task::audio_play_task_status_t::mute));
  audio_play_task_api->add_audio_task_callback(std::bind(&audio::audio_play_task::AudioPlayTaskController::add_audio_task, audio_play_task_api, std::placeholders::_1), audio_play_task_api->get_audio_play_task_file_path(audio::audio_play_task::audio_play_task_status_t::battery_check_failed));
//   audio_play_task_api->add_audio_task_callback(std::bind(&audio::audio_play_task::AudioPlayTaskController::add_audio_task, audio_play_task_api, std::placeholders::_1), audio_play_task_api->get_audio_play_task_file_path(audio::audio_play_task::audio_play_task_status_t::left_battery_offline));
//   audio_play_task_api->add_audio_task_callback(std::bind(&audio::audio_play_task::AudioPlayTaskController::add_audio_task, audio_play_task_api, std::placeholders::_1), audio_play_task_api->get_audio_play_task_file_path(audio::audio_play_task::audio_play_task_status_t::left_battery_online));
//   audio_play_task_api->add_audio_task_callback(std::bind(&audio::audio_play_task::AudioPlayTaskController::add_audio_task, audio_play_task_api, std::placeholders::_1), audio_play_task_api->get_audio_play_task_file_path(audio::audio_play_task::audio_play_task_status_t::right_battery_offline));
//   audio_play_task_api->add_audio_task_callback(std::bind(&audio::audio_play_task::AudioPlayTaskController::add_audio_task, audio_play_task_api, std::placeholders::_1), audio_play_task_api->get_audio_play_task_file_path(audio::audio_play_task::audio_play_task_status_t::right_battery_online));
//   audio_play_task_api->add_audio_task_callback(std::bind(&audio::audio_play_task::AudioPlayTaskController::add_audio_task, audio_play_task_api, std::placeholders::_1), audio_play_task_api->get_audio_play_task_file_path(audio::audio_play_task::audio_play_task_status_t::left_battery_low_power));
//   audio_play_task_api->add_audio_task_callback(std::bind(&audio::audio_play_task::AudioPlayTaskController::add_audio_task, audio_play_task_api, std::placeholders::_1), audio_play_task_api->get_audio_play_task_file_path(audio::audio_play_task::audio_play_task_status_t::right_battery_low_power));
//   audio_play_task_api->add_audio_task_callback(std::bind(&audio::audio_play_task::AudioPlayTaskController::add_audio_task, audio_play_task_api, std::placeholders::_1), audio_play_task_api->get_audio_play_task_file_path(audio::audio_play_task::audio_play_task_status_t::boot_up));
//   audio_play_task_api->add_audio_task_callback(std::bind(&audio::audio_play_task::AudioPlayTaskController::add_audio_task, audio_play_task_api, std::placeholders::_1), audio_play_task_api->get_audio_play_task_file_path(audio::audio_play_task::audio_play_task_status_t::down_finished));
//   audio_play_task_api->add_audio_task_callback(std::bind(&audio::audio_play_task::AudioPlayTaskController::add_audio_task, audio_play_task_api, std::placeholders::_1), audio_play_task_api->get_audio_play_task_file_path(audio::audio_play_task::audio_play_task_status_t::downing));
//   audio_play_task_api->add_audio_task_callback(std::bind(&audio::audio_play_task::AudioPlayTaskController::add_audio_task, audio_play_task_api, std::placeholders::_1), audio_play_task_api->get_audio_play_task_file_path(audio::audio_play_task::audio_play_task_status_t::controller_connected));
//   audio_play_task_api->add_audio_task_callback(std::bind(&audio::audio_play_task::AudioPlayTaskController::add_audio_task, audio_play_task_api, std::placeholders::_1), audio_play_task_api->get_audio_play_task_file_path(audio::audio_play_task::audio_play_task_status_t::controller_disconnected));
//   audio_play_task_api->add_audio_task_callback(std::bind(&audio::audio_play_task::AudioPlayTaskController::add_audio_task, audio_play_task_api, std::placeholders::_1), audio_play_task_api->get_audio_play_task_file_path(audio::audio_play_task::audio_play_task_status_t::enter_low_power_mode));
//   audio_play_task_api->add_audio_task_callback(std::bind(&audio::audio_play_task::AudioPlayTaskController::add_audio_task, audio_play_task_api, std::placeholders::_1), audio_play_task_api->get_audio_play_task_file_path(audio::audio_play_task::audio_play_task_status_t::exit_low_power_mode));
//   audio_play_task_api->add_audio_task_callback(std::bind(&audio::audio_play_task::AudioPlayTaskController::add_audio_task, audio_play_task_api, std::placeholders::_1), audio_play_task_api->get_audio_play_task_file_path(audio::audio_play_task::audio_play_task_status_t::imu_connected));
//   audio_play_task_api->add_audio_task_callback(std::bind(&audio::audio_play_task::AudioPlayTaskController::add_audio_task, audio_play_task_api, std::placeholders::_1), audio_play_task_api->get_audio_play_task_file_path(audio::audio_play_task::audio_play_task_status_t::imu_disconnected));
//   audio_play_task_api->add_audio_task_callback(std::bind(&audio::audio_play_task::AudioPlayTaskController::add_audio_task, audio_play_task_api, std::placeholders::_1), audio_play_task_api->get_audio_play_task_file_path(audio::audio_play_task::audio_play_task_status_t::over_speed));
//   audio_play_task_api->add_audio_task_callback(std::bind(&audio::audio_play_task::AudioPlayTaskController::add_audio_task, audio_play_task_api, std::placeholders::_1), audio_play_task_api->get_audio_play_task_file_path(audio::audio_play_task::audio_play_task_status_t::pms_check_failed));
//   audio_play_task_api->add_audio_task_callback(std::bind(&audio::audio_play_task::AudioPlayTaskController::add_audio_task, audio_play_task_api, std::placeholders::_1), audio_play_task_api->get_audio_play_task_file_path(audio::audio_play_task::audio_play_task_status_t::pms_check_succeed));
//   audio_play_task_api->add_audio_task_callback(std::bind(&audio::audio_play_task::AudioPlayTaskController::add_audio_task, audio_play_task_api, std::placeholders::_1), audio_play_task_api->get_audio_play_task_file_path(audio::audio_play_task::audio_play_task_status_t::pms_selftest_timeout));
//   audio_play_task_api->add_audio_task_callback(std::bind(&audio::audio_play_task::AudioPlayTaskController::add_audio_task, audio_play_task_api, std::placeholders::_1), audio_play_task_api->get_audio_play_task_file_path(audio::audio_play_task::audio_play_task_status_t::pose_status_error));
//   audio_play_task_api->add_audio_task_callback(std::bind(&audio::audio_play_task::AudioPlayTaskController::add_audio_task, audio_play_task_api, std::placeholders::_1), audio_play_task_api->get_audio_play_task_file_path(audio::audio_play_task::audio_play_task_status_t::shutdown));
//   audio_play_task_api->add_audio_task_callback(std::bind(&audio::audio_play_task::AudioPlayTaskController::add_audio_task, audio_play_task_api, std::placeholders::_1), audio_play_task_api->get_audio_play_task_file_path(audio::audio_play_task::audio_play_task_status_t::stand_up));
//   audio_play_task_api->add_audio_task_callback(std::bind(&audio::audio_play_task::AudioPlayTaskController::add_audio_task, audio_play_task_api, std::placeholders::_1), audio_play_task_api->get_audio_play_task_file_path(audio::audio_play_task::audio_play_task_status_t::turn_off_v48));
//   audio_play_task_api->add_audio_task_callback(std::bind(&audio::audio_play_task::AudioPlayTaskController::add_audio_task, audio_play_task_api, std::placeholders::_1), audio_play_task_api->get_audio_play_task_file_path(audio::audio_play_task::audio_play_task_status_t::low_power));
//   audio_play_task_api->add_audio_task_callback(std::bind(&audio::audio_play_task::AudioPlayTaskController::add_audio_task, audio_play_task_api, std::placeholders::_1), audio_play_task_api->get_audio_play_task_file_path(audio::audio_play_task::audio_play_task_status_t::motor_1_error));
//   audio_play_task_api->add_audio_task_callback(std::bind(&audio::audio_play_task::AudioPlayTaskController::add_audio_task, audio_play_task_api, std::placeholders::_1), audio_play_task_api->get_audio_play_task_file_path(audio::audio_play_task::audio_play_task_status_t::motor_2_error));
//   audio_play_task_api->add_audio_task_callback(std::bind(&audio::audio_play_task::AudioPlayTaskController::add_audio_task, audio_play_task_api, std::placeholders::_1), audio_play_task_api->get_audio_play_task_file_path(audio::audio_play_task::audio_play_task_status_t::motor_3_error));
//   audio_play_task_api->add_audio_task_callback(std::bind(&audio::audio_play_task::AudioPlayTaskController::add_audio_task, audio_play_task_api, std::placeholders::_1), audio_play_task_api->get_audio_play_task_file_path(audio::audio_play_task::audio_play_task_status_t::motor_4_error));
//   audio_play_task_api->add_audio_task_callback(std::bind(&audio::audio_play_task::AudioPlayTaskController::add_audio_task, audio_play_task_api, std::placeholders::_1), audio_play_task_api->get_audio_play_task_file_path(audio::audio_play_task::audio_play_task_status_t::motor_5_error));
//   audio_play_task_api->add_audio_task_callback(std::bind(&audio::audio_play_task::AudioPlayTaskController::add_audio_task, audio_play_task_api, std::placeholders::_1), audio_play_task_api->get_audio_play_task_file_path(audio::audio_play_task::audio_play_task_status_t::motor_6_error));
//   audio_play_task_api->add_audio_task_callback(std::bind(&audio::audio_play_task::AudioPlayTaskController::add_audio_task, audio_play_task_api, std::placeholders::_1), audio_play_task_api->get_audio_play_task_file_path(audio::audio_play_task::audio_play_task_status_t::motor_7_error));
//   audio_play_task_api->add_audio_task_callback(std::bind(&audio::audio_play_task::AudioPlayTaskController::add_audio_task, audio_play_task_api, std::placeholders::_1), audio_play_task_api->get_audio_play_task_file_path(audio::audio_play_task::audio_play_task_status_t::motor_8_error));
//   audio_play_task_api->add_audio_task_callback(std::bind(&audio::audio_play_task::AudioPlayTaskController::add_audio_task, audio_play_task_api, std::placeholders::_1), audio_play_task_api->get_audio_play_task_file_path(audio::audio_play_task::audio_play_task_status_t::audio_error));
//   audio_play_task_api->add_audio_task_callback(std::bind(&audio::audio_play_task::AudioPlayTaskController::add_audio_task, audio_play_task_api, std::placeholders::_1), audio_play_task_api->get_audio_play_task_file_path(audio::audio_play_task::audio_play_task_status_t::camera_error));
//   audio_play_task_api->add_audio_task_callback(std::bind(&audio::audio_play_task::AudioPlayTaskController::add_audio_task, audio_play_task_api, std::placeholders::_1), audio_play_task_api->get_audio_play_task_file_path(audio::audio_play_task::audio_play_task_status_t::camera_normal));
//   audio_play_task_api->add_audio_task_callback(std::bind(&audio::audio_play_task::AudioPlayTaskController::add_audio_task, audio_play_task_api, std::placeholders::_1), audio_play_task_api->get_audio_play_task_file_path(audio::audio_play_task::audio_play_task_status_t::infrared_tof_error));
//   audio_play_task_api->add_audio_task_callback(std::bind(&audio::audio_play_task::AudioPlayTaskController::add_audio_task, audio_play_task_api, std::placeholders::_1), audio_play_task_api->get_audio_play_task_file_path(audio::audio_play_task::audio_play_task_status_t::infrared_tof_succeed));
//   audio_play_task_api->add_audio_task_callback(std::bind(&audio::audio_play_task::AudioPlayTaskController::add_audio_task, audio_play_task_api, std::placeholders::_1), audio_play_task_api->get_audio_play_task_file_path(audio::audio_play_task::audio_play_task_status_t::interaction_port_error));
//   audio_play_task_api->add_audio_task_callback(std::bind(&audio::audio_play_task::AudioPlayTaskController::add_audio_task, audio_play_task_api, std::placeholders::_1), audio_play_task_api->get_audio_play_task_file_path(audio::audio_play_task::audio_play_task_status_t::interaction_poer_succeed));
//   audio_play_task_api->add_audio_task_callback(std::bind(&audio::audio_play_task::AudioPlayTaskController::add_audio_task, audio_play_task_api, std::placeholders::_1), audio_play_task_api->get_audio_play_task_file_path(audio::audio_play_task::audio_play_task_status_t::pose_error));
//   audio_play_task_api->add_audio_task_callback(std::bind(&audio::audio_play_task::AudioPlayTaskController::add_audio_task, audio_play_task_api, std::placeholders::_1), audio_play_task_api->get_audio_play_task_file_path(audio::audio_play_task::audio_play_task_status_t::pose_succeed));
//   audio_play_task_api->add_audio_task_callback(std::bind(&audio::audio_play_task::AudioPlayTaskController::add_audio_task, audio_play_task_api, std::placeholders::_1), audio_play_task_api->get_audio_play_task_file_path(audio::audio_play_task::audio_play_task_status_t::quadruped_mode_error));
//   audio_play_task_api->add_audio_task_callback(std::bind(&audio::audio_play_task::AudioPlayTaskController::add_audio_task, audio_play_task_api, std::placeholders::_1), audio_play_task_api->get_audio_play_task_file_path(audio::audio_play_task::audio_play_task_status_t::quadruped_mode_succeed));
//   audio_play_task_api->add_audio_task_callback(std::bind(&audio::audio_play_task::AudioPlayTaskController::add_audio_task, audio_play_task_api, std::placeholders::_1), audio_play_task_api->get_audio_play_task_file_path(audio::audio_play_task::audio_play_task_status_t::temperature_humidity_error));
//   audio_play_task_api->add_audio_task_callback(std::bind(&audio::audio_play_task::AudioPlayTaskController::add_audio_task, audio_play_task_api, std::placeholders::_1), audio_play_task_api->get_audio_play_task_file_path(audio::audio_play_task::audio_play_task_status_t::temperature_humidity_succeed));
//   audio_play_task_api->add_audio_task_callback(std::bind(&audio::audio_play_task::AudioPlayTaskController::add_audio_task, audio_play_task_api, std::placeholders::_1), audio_play_task_api->get_audio_play_task_file_path(audio::audio_play_task::audio_play_task_status_t::ultrasonic_wave_error));
//   audio_play_task_api->add_audio_task_callback(std::bind(&audio::audio_play_task::AudioPlayTaskController::add_audio_task, audio_play_task_api, std::placeholders::_1), audio_play_task_api->get_audio_play_task_file_path(audio::audio_play_task::audio_play_task_status_t::ultrasonic_wave_succeed));
//   audio_play_task_api->add_audio_task_callback(std::bind(&audio::audio_play_task::AudioPlayTaskController::add_audio_task, audio_play_task_api, std::placeholders::_1), audio_play_task_api->get_audio_play_task_file_path(audio::audio_play_task::audio_play_task_status_t::wifi_error));
//   audio_play_task_api->add_audio_task_callback(std::bind(&audio::audio_play_task::AudioPlayTaskController::add_audio_task, audio_play_task_api, std::placeholders::_1), audio_play_task_api->get_audio_play_task_file_path(audio::audio_play_task::audio_play_task_status_t::wifi_succeed));

    audio_play_task_api->add_audio_task_callback(std::bind(&audio::audio_play_task::AudioPlayTaskController::add_audio_task, audio_play_task_api, std::placeholders::_1), wav_file_path);



  audio_play_task_api->start_audio_task();

  while (true) {
    std::cout << "IDLE..." << std::endl;
    sleep(1);
  }

  return 0;
}
