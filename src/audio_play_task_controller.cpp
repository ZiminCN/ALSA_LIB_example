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
    if (this->audio_queue.empty()) {
      // playback mute wav file
      // this->asound_driver_api->try_to_playback_audio(
      //     this->header,
      //     "/home/ziminrsp/code_ws/music-source/44100/Chinese/mute.wav");
      printf("audio queue is empty\r\n");
    } else {
      // playback pueue front wav file
      std::cout << "current audio_queue front is [" << audio_queue.front()
                << "]" << std::endl;
      printf("current audio_queue size is [%d]\r\n", audio_queue.size());

      this->asound_driver_api->try_to_playback_audio(this->header,
                                                     audio_queue.front());

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

void AudioPlayTaskController::play_audio(const std::string& audio_path) {}

}  // namespace audio_play_task
}  // namespace audio