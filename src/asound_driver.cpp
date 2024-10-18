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

  // unsigned int buffer_time, period_time;
  // err = snd_pcm_hw_params_get_buffer_time_max(this->hw_params, &buffer_time,
  // 0); printf("[Debug] snd_pcm_hw_params_get_buffer_time_max.err: %d\n", err);
  // if (err < 0) {
  //   printf("cannot snd_pcm_hw_params_get_buffer_time_max (%s)\r\n",
  //          snd_strerror(err));
  //   return err;
  // }

  // if (buffer_time > 500000) {
  //   buffer_time = 500000;
  //   printf("[%s %d] buffer_time=%d, irq=%d\r\n", __FILE__, __LINE__,
  //          buffer_time, buffer_time / 4);
  // }

  // err = snd_pcm_hw_params_set_buffer_time_near(
  //     this->playback_handle, this->hw_params, &buffer_time, 0);
  // printf("[Debug] snd_pcm_hw_params_set_buffer_time_near.err: %d\n", err);
  // if (err < 0) {
  //   printf("cannot snd_pcm_hw_params_set_buffer_time_near (%s)\r\n",
  //          snd_strerror(err));
  //   return err;
  // }

  // period_time = buffer_time / 4;
  // err = snd_pcm_hw_params_set_period_time_near(
  //     this->playback_handle, this->hw_params, &period_time, 0);
  // printf("[Debug] snd_pcm_hw_params_set_period_time_near.err: %d\n", err);
  // if (err < 0) {
  //   printf("cannot snd_pcm_hw_params_set_period_time_near (%s)\r\n",
  //          snd_strerror(err));
  //   return err;
  // }

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

bool ASoundDriver::init_snd_mixer() {
  printf("[Debug]: init snd mixer \r\n");
  snd_mixer_open(&this->mixer_handle, 0);
  snd_mixer_attach(this->mixer_handle, "default");
  snd_mixer_selem_register(this->mixer_handle, NULL, NULL);
  snd_mixer_load(this->mixer_handle);

  snd_mixer_selem_id_alloca(&this->sid);
  snd_mixer_selem_id_set_name(this->sid, "Master");

  snd_mixer_close(this->mixer_handle);

  return true;
}

bool ASoundDriver::set_snd_volume(int volume_percent) {
  if (volume_percent < 0 || volume_percent > 100) {
    return false;
  }
  printf("[Debug]: set snd volume \r\n");

  snd_mixer_open(&this->mixer_handle, 0);

  printf("[Debug]: 1 \r\n");
  long min_volume, max_volume, volume;
  this->elem = snd_mixer_find_selem(this->mixer_handle, this->sid);
  printf("[Debug]: 2 \r\n");
  snd_mixer_selem_get_playback_volume_range(this->elem, &min_volume,
                                            &max_volume);
  printf("[Debug]: 3 \r\n");
  volume = (max_volume - min_volume) * volume_percent / 100 + min_volume;
  snd_mixer_selem_set_playback_volume(this->elem, SND_MIXER_SCHN_FRONT_LEFT,
                                      volume);
  printf("[Debug]: 4 \r\n");
  snd_mixer_selem_set_playback_volume(this->elem, SND_MIXER_SCHN_FRONT_RIGHT,
                                      volume);
  printf("[Debug]: 5 \r\n");
  snd_mixer_close(this->mixer_handle);
  printf("[Debug]: 6 \r\n");
  return true;
}

bool ASoundDriver::try_playback_audio(WAVHeader wav_header) {
  printf("\r\n");
  printf("[Debug] enter try_playback_audio \r\n");

  printf("step 1\r\n");
  // 假设左声道和右声道的音频数据分别为 left_buffer 和 right_buffer
  int err = 0;
  wav_header.wav_data.data = (char *)malloc(wav_header.wav_data.subchunk2Size);

  memset(wav_header.wav_data.data, 0xFF, wav_header.wav_data.subchunk2Size);

  if (!wav_header.wav_data.data) {
    printf("malloc failed!\r\n");
    snd_pcm_close(this->playback_handle);
    return false;
  }

  printf("step 2\r\n");
  snd_pcm_uframes_t audio_frames = wav_header.wav_data.subchunk2Size /
                                   (wav_header.numChannels * sizeof(uint16_t));
  if (audio_frames < 0) {
    printf("audio_frames < 0!\r\n");
    snd_pcm_close(this->playback_handle);
    return false;
  }

  printf("ready for prepare\r\n");
  while ((err = snd_pcm_prepare(this->playback_handle)) != 0) {
    sleep(0.2);
    printf("idle for snd_pcm_prepare! \r\n");
  }

  printf("playback start\r\n");
  err = snd_pcm_writei(this->playback_handle, wav_header.wav_data.data,
                       wav_header.wav_data.subchunk2Size);
  printf("err: %d\r\n", err);

  printf("playback end\r\n");

  snd_pcm_drain(this->playback_handle);
  snd_pcm_close(this->playback_handle);
  printf("playback done\r\n");

  return true;
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

    // if (err == 0) {
    //   printf("end of file on input\r\n");
    //   break;
    // } else if (err != this->buffer_size) {
    //   printf("read file error!\r\n");
    // }
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
