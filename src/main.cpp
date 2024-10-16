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

  std::shared_ptr<audio::alsa_asound::ASoundDriver> asound_driver_api =
      std::make_shared<audio::alsa_asound::ASoundDriver>();

  std::shared_ptr<audio::audio_file_analyzer::AudioFileAnalyzer>
      audio_file_analyzer_api =
          std::make_shared<audio::audio_file_analyzer::AudioFileAnalyzer>();

  //   asound_driver_api->init_snd_mixer();
  //   asound_driver_api->set_snd_volume(50);
  asound_driver_api->init_audio_pcm(PCM_NAME, SND_PCM_FORMAT_S16_LE);
  std::string wav_file_path = "/home/ziminrsp/dukou_caiqin.wav";
  auto wav_header = audio_file_analyzer_api->getWavHeader_T();
  wav_header = audio_file_analyzer_api->open_wav_file(wav_file_path);

  printf("\r\n");
  printf("[Debug]: RIFF chunk descriptor\r\n");
  printf("[Debug]: wav_header.chunkID is [%s] \r\n", wav_header.chunkID);
  printf("[Debug]: wav_header.chunkSize is [0x%08X] \r\n",
         wav_header.chunkSize);
  printf("[Debug]: wav_header.format is [%s] \r\n", wav_header.format);

  printf("\r\n");
  printf("[Debug]: FMT chunk descriptor\r\n");
  printf("[Debug]: wav_header.subchunk1ID is [%s] \r\n",
         wav_header.subchunk1ID);
  printf("[Debug]: wav_header.subchunk1Size is [%d] \r\n",
         wav_header.subchunk1Size);
  printf("[Debug]: wav_header.audioFormat is [%d] \r\n",
         wav_header.audioFormat);
  printf("[Debug]: wav_header.numChannels is [%d] \r\n",
         wav_header.numChannels);
  printf("[Debug]: wav_header.sampleRate is [%d] \r\n", wav_header.sampleRate);
  printf("[Debug]: wav_header.byteRate is [%d] \r\n", wav_header.byteRate);
  printf("[Debug]: wav_header.blockAlign is[%d] \r\n ", wav_header.blockAlign);
  printf("[Debug]: wav_header.bitsPerSample is[%d] \r\n ",
         wav_header.bitsPerSample);

  printf("\r\n");
  printf("[Debug]: WAVE chunk descriptor\r\n");
  printf("[Debug]: wav_header.wav_data.subchunk2ID is [%s] \r\n",
         wav_header.wav_data.subchunk2ID);
  printf("[Debug]: wav_header.wav_data.subchunk2Size is [0x%08X] \r\n",
         wav_header.wav_data.subchunk2Size);
  printf("[Debug]: wav_header.wav_data.data is [0x%08X] \r\n",
         wav_header.wav_data.data);

  asound_driver_api->try_playback_audio(wav_header);

  while (true) {
    std::cout << "IDLE..." << std::endl;
    sleep(1);
  }

  return 0;
}
