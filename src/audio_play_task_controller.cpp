#include "audio_play_task_controller.hpp"

namespace audio {

namespace audio_play_task {

bool AudioPlayTaskController::add_audio_task(
    const std::string& audio_file_path) {
  if (!std::filesystem::exists(audio_file_path)) {
    printf("[Error] %s does not exist\n", audio_file_path.c_str());
    return false;
  }

  this->audio_task_mutex.lock();
  this->audio_queue.push(audio_file_path);
  this->audio_task_mutex.unlock();
  return true;
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
    // if (this->audio_queue.empty()) {
    //   // playback mute wav file
    // } else {
    //   // playback pueue front wav file

    //   // then pop
    //   this->audio_task_mutex.lock();
    //   this->audio_queue.pop();
    //   this->audio_task_mutex.unlock();
    // }
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    printf("[Debug] thread idle...");
  }
}

bool AudioPlayTaskController::start_audio_task() {
  if (!this->is_running_.load()) {
    return false;
  }

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

  return true;
}

void AudioPlayTaskController::play_audio(const std::string& audio_path) {}

}  // namespace audio_play_task
}  // namespace audio