#include "audio_file_analyzer.hpp"

namespace audio {

namespace audio_file_analyzer {

void AudioFileAnalyzer::wav_header_cb(WAVHeaderCallbackFunc callback,
                                      void *data) {
  WAVHeader header = *reinterpret_cast<WAVHeader *>(data);
  printf("do wav_header_cb callback \r\n");
  callback(header);
}

void AudioFileAnalyzer::test_cb(CallbackFunc callback) {
  printf("do test_cb callback \r\n");
  callback();
};

WAVHeader AudioFileAnalyzer::open_wav_file(const std::string &filename) {
  FILE *wavFile = fopen(filename.c_str(), "rb");
  if (!wavFile) {
    printf("Error opening WAV file.\n");
    throw std::runtime_error("Error opening WAV file.");  // 抛出异常
  }

  WAVHeader header;
  fread(&header, (sizeof(WAVHeader) - sizeof(WAVData)), 1, wavFile);
  // check if the file is a vaild WAV file
  if (strncmp(header.chunkID, "RIFF", 4) != 0 ||
      strncmp(header.format, "WAVE", 4) != 0) {
    printf("============================\r\n");
    printf("Error: Not a valid WAV file.\n");
    printf("============================\r\n");
    fclose(wavFile);  // 关闭文件
  }

  // check fmt part info
  if (strncmp(header.subchunk1ID, "fmt ", 4) != 0) {
    printf("============================\r\n");
    printf("Error: WAV file's fmt part info is wrong.\n");
    printf("============================\r\n");
    fclose(wavFile);  // 关闭文件
  }

  int offset_byte_cnt = 0;

  // try to read data part info
  while (1) {
    printf("============== Enter While ==============\r\n");
    size_t bytesRead = fread(&header.wav_data, sizeof(WAVData), 1, wavFile);
    if (bytesRead < 1) {
      printf("Failed to read WAV data. \r\n");
      break;
    }

    if (strncmp(header.wav_data.subchunk2ID, "data", 4) == 0) {
      printf("yes is data\r\n");
      break;
    } else {
      printf("no is not data\r\n");
      printf("header.wav_data.subchunk2ID is [%s]\r\n",
             header.wav_data.subchunk2ID);
      fseek(wavFile, offset_byte_cnt, SEEK_SET);
      offset_byte_cnt += 1;
      printf("offset_byte_cnt: %d\r\n", offset_byte_cnt);
    }

    printf("============== End While ==============\r\n");
  }

  fclose(wavFile);  // 关闭文件

  return header;
}

}  // namespace audio_file_analyzer

}  // namespace audio
