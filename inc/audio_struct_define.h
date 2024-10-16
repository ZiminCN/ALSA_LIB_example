#ifndef __AUDIO_STRUCT_DEFINE_H
#define __AUDIO_STRUCT_DEFINE_H

typedef struct {
  // DATA sub chunk
  char subchunk2ID[4];
  uint32_t subchunk2Size;
  char *data;
} WAVData;

typedef struct {
  // RIFF chunk descriptor
  char chunkID[4];
  uint32_t chunkSize;
  char format[4];
  // FMT sub chunk
  char subchunk1ID[4];
  uint32_t subchunk1Size;
  uint16_t audioFormat;
  uint16_t numChannels;
  uint32_t sampleRate;
  uint32_t byteRate;
  uint16_t blockAlign;
  uint16_t bitsPerSample;

  /* LIST IART INAM IPRT ISFT */

  // DATA sub chunk
  WAVData wav_data;

} WAVHeader;

#endif  // __AUDIO_STRUCT_DEFINE_H