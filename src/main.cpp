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

  //   std::string wav_file_path = "/home/ziminrsp/huiliu_fangdatong.wav";
  std::string wav_file_path1 =
      "/home/ziminrsp/code_ws/music-source/44100/Chinese/sensors/"
      "audio_error.wav";
  std::string wav_file_path2 =
      "/home/ziminrsp/code_ws/music-source/44100/Chinese/sensors/"
      "camera_error.wav";
  std::string wav_file_path3 =
      "/home/ziminrsp/code_ws/music-source/44100/Chinese/sensors/"
      "camera_normal.wav";
  std::string wav_file_path4 =
      "/home/ziminrsp/code_ws/music-source/44100/Chinese/sensors/"
      "wifi_error.wav";
  std::string wav_file_path5 =
      "/home/ziminrsp/code_ws/music-source/44100/Chinese/sensors/"
      "wifi_succeed.wav";
  std::string wav_file_path6 =
      "/home/ziminrsp/code_ws/music-source/44100/Chinese/sensors/"
      "infrared_tof_error.wav";
  std::string wav_file_path7 =
      "/home/ziminrsp/code_ws/music-source/44100/Chinese/sensors/"
      "infrared_tof_succeed.wav";
  std::string wav_file_path8 =
      "/home/ziminrsp/code_ws/music-source/44100/Chinese/sensors/"
      "interaction_port_error.wav";
  std::string wav_file_path9 =
      "/home/ziminrsp/code_ws/music-source/44100/Chinese/sensors/"
      "interaction_port_succeed.wav";
  std::string wav_file_path10 =
      "/home/ziminrsp/code_ws/music-source/44100/Chinese/sensors/"
      "pose_error.wav";
  std::string wav_file_path11 =
      "/home/ziminrsp/code_ws/music-source/44100/Chinese/sensors/"
      "pose_succeed.wav";
  std::string wav_file_path12 =
      "/home/ziminrsp/code_ws/music-source/44100/Chinese/sensors/"
      "quadruped_mode_error.wav";
  std::string wav_file_path13 =
      "/home/ziminrsp/code_ws/music-source/44100/Chinese/sensors/"
      "quadruped_mode_succeed.wav";
  std::string wav_file_path14 =
      "/home/ziminrsp/code_ws/music-source/44100/Chinese/sensors/"
      "temperature_humidity_error.wav";
  std::string wav_file_path15 =
      "/home/ziminrsp/code_ws/music-source/44100/Chinese/sensors/"
      "temperature_humidity_succeed.wav";

  //   std::string wav_file_path =
  //       "/home/ziminrsp/code_ws/music-source/44100/Chinese/mute.wav";

  audio_play_task_api->add_audio_task(wav_file_path1);
  audio_play_task_api->add_audio_task(wav_file_path2);
  audio_play_task_api->add_audio_task(wav_file_path3);
  audio_play_task_api->add_audio_task(wav_file_path4);
  audio_play_task_api->add_audio_task(wav_file_path5);
  audio_play_task_api->add_audio_task(wav_file_path6);
  audio_play_task_api->add_audio_task(wav_file_path7);
  audio_play_task_api->add_audio_task(wav_file_path8);
  audio_play_task_api->add_audio_task(wav_file_path9);
  audio_play_task_api->add_audio_task(wav_file_path10);
  audio_play_task_api->add_audio_task(wav_file_path11);
  audio_play_task_api->add_audio_task(wav_file_path12);
  audio_play_task_api->add_audio_task(wav_file_path13);
  audio_play_task_api->add_audio_task(wav_file_path14);
  audio_play_task_api->add_audio_task(wav_file_path15);

  audio_play_task_api->start_audio_task();

  while (true) {
    std::cout << "IDLE..." << std::endl;
    sleep(1);
  }

  return 0;
}
