#include "asound_driver.hpp"

namespace audio {

namespace alsa_asound {

bool ASoundDriver::init_audio_pcm(const char *name, snd_pcm_format_t format) {
  int err = -1;

  err = snd_pcm_open(&this->playback_handle, name, SND_PCM_STREAM_PLAYBACK, 0);
  printf("[Debug] snd_pcm_open.err is %d \r\n", err);
  if (err < 0) {
    printf("cannot snd_pcm_open (%s)\r\n", snd_strerror(err));
    return -1;
  }

  err = snd_pcm_hw_params_malloc(&this->hw_params);
  printf("[Debug] snd_pcm_hw_params_malloc.err is %d \r\n", err);
  if (err < 0) {
    printf("cannot snd_pcm_hw_params_malloc (%s)\r\n", snd_strerror(err));
    return err;
  }

  err = snd_pcm_hw_params_any(this->playback_handle, this->hw_params);
  printf("[Debug] snd_pcm_hw_params_any.err: %d\n", err);
  if (err < 0) {
    printf("cannot snd_pcm_hw_params_any (%s)\r\n", snd_strerror(err));
    return err;
  }

  err = snd_pcm_hw_params_set_rate_resample(this->playback_handle,
                                            this->hw_params, 1);
  printf("[Debug] snd_pcm_hw_params_set_rate_resample.err: %d\n", err);
  if (err < 0) {
    printf("cannot snd_pcm_hw_params_set_rate_resample (%s)\r\n",
           snd_strerror(err));
    return err;
  }

  err = snd_pcm_hw_params_set_access(this->playback_handle, this->hw_params,
                                     SND_PCM_ACCESS_RW_INTERLEAVED);
  printf("[Debug] snd_pcm_hw_params_set_access.err: %d\n", err);
  if (err < 0) {
    printf("cannot snd_pcm_hw_params_set_access (%s)\r\n", snd_strerror(err));
    return err;
  }

  err = snd_pcm_hw_params_set_format(this->playback_handle, this->hw_params,
                                     format);
  printf("[Debug] snd_pcm_hw_params_set_format.err: %d\n", err);
  if (err < 0) {
    printf("cannot snd_pcm_hw_params_set_format (%s)\r\n", snd_strerror(err));
    return err;
  }

  err =
      snd_pcm_hw_params_set_channels(this->playback_handle, this->hw_params, 2);
  printf("[Debug] snd_pcm_hw_params_set_channels.err: %d\n", err);
  if (err < 0) {
    printf("cannot snd_pcm_hw_params_set_channels (%s)\r\n", snd_strerror(err));
    return err;
  }

  unsigned int rrate;
  rrate = this->stream_rate;
  printf("[Debug] rrate is %d\r\n", rrate);
  err = snd_pcm_hw_params_set_rate_near(this->playback_handle, this->hw_params,
                                        &rrate, &this->dir);
  printf("[Debug] snd_pcm_hw_params_set_rate_near.err: %d\n", err);
  if (err < 0) {
    printf("cannot snd_pcm_hw_params_set_rate_near (%s)\r\n",
           snd_strerror(err));
    return err;
  }

  err = snd_pcm_hw_params_set_period_size_near(
      this->playback_handle, this->hw_params, &this->frames, &this->dir);

  err = snd_pcm_hw_params(this->playback_handle, this->hw_params);
  printf("[Debug] snd_pcm_hw_params.err: %d\n", err);
  // snd_pcm_hw_params_free(this->hw_params);
  if (err < 0) {
    printf("cannot snd_pcm_hw_params (%s)\r\n", snd_strerror(err));
    return err;
  }

  err = snd_pcm_hw_params_get_period_size(this->hw_params, &this->frames,
                                          &this->dir);
  if (err < 0) {
    printf("cannot snd_pcm_hw_params_get_period_size (%s)\r\n",
           snd_strerror(err));
    return err;
  }

  this->buffer_size = this->frames * 4;

  this->audio_buffer = (char *)malloc(this->buffer_size);

  err = snd_pcm_hw_params_get_period_time(this->hw_params, &rrate, &this->dir);
  if (err < 0) {
    printf("cannot snd_pcm_hw_params_get_period_time (%s)\r\n",
           snd_strerror(err));
    return err;
  }

  return 0;
}

bool ASoundDriver::try_to_playback_audio(WAVHeader wav_header,
                                         const std::string &filename) {
  printf("[Debug] enter try to playback audio\r\n");
  long temp_loops = this->loops;
  int err = 0;

  std::ifstream ifs_file;

  printf("try to open file:[%s]. ", filename.c_str());

  ifs_file.open(filename, std::ios::binary);
  if (!ifs_file) {
    printf("open file failed!\r\n");
    return false;
  }

  const size_t temp_buffer_size = this->buffer_size;
  char temp_buffer[temp_buffer_size];

  printf("temp_buffer_size is [%d] \r\n", temp_buffer_size);
  printf("enter loop\r\n");

  while (temp_loops) {
    temp_loops--;
    // err = read(, this->audio_buffer, this->buffer_size);
    ifs_file.read(temp_buffer, temp_buffer_size);
    if (ifs_file) {
      // printf("success read file byte! \r\n");
    } else if (ifs_file.eof()) {
      printf("read file end! \r\n");
    } else if (ifs_file.fail()) {
      printf("read file error! \r\n");
      return false;
    }

    err = snd_pcm_writei(this->playback_handle, temp_buffer, this->frames);
    if (err == -EPIPE) {
      printf("underrun occurred \r\n");
      snd_pcm_prepare(this->playback_handle);
    } else if (err < 0) {
      printf("error from writei: %s \r\n", snd_strerror(err));
    } else if (err != (int)this->frames) {
      printf("short write, write %d frames\r\n", err);
    }
  }

  printf("exit loop\r\n");

  ifs_file.close();

  snd_pcm_drain(this->playback_handle);
  snd_pcm_close(this->playback_handle);
  free(this->audio_buffer);

  return true;
}

}  // namespace alsa_asound

}  // namespace audio
