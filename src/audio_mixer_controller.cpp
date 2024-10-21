#include "audio_mixer_controller.hpp"

namespace audio {
namespace mixer {

#include "asound_driver.hpp"
bool AudioMixerController::init_audio_mixer() {
  printf("\r\n");
  printf("[Debug] Enter init_audio_mixer\r\n");

  int err = 0;
  snd_mixer_selem_id_alloca(&this->sid);

  err = snd_mixer_open(&this->mixer_handle, 0);
  if (err < 0) {
    printf("snd_mixer_open Err\n");
    return false;
  }

  err = snd_mixer_attach(this->mixer_handle, CTL_NAME);
  if (err < 0) {
    printf("snd_mixer_attach Err\n");
    return false;
  }

  err = snd_mixer_selem_register(this->mixer_handle, NULL, NULL);
  if (err < 0) {
    printf("snd_mixer_selem_register Err\n");
    return false;
  }

  err = snd_mixer_load(this->mixer_handle);
  if (err < 0) {
    printf("snd_mixer_load Err\n");
    return false;
  }

  this->elem = snd_mixer_first_elem(this->mixer_handle);

  while (this->elem) {
    // printf("elem name can be : %s\n", snd_mixer_selem_get_name(this->elem));
    if (strcmp("Speaker", snd_mixer_selem_get_name(this->elem)) == 0) {
      printf("elem name is : %s\r\n", snd_mixer_selem_get_name(this->elem));
      break;
    }
    this->elem = snd_mixer_elem_next(elem);
  }

  if (!this->elem) {
    printf("snd_mixer_find_selem Err\r\n");
    snd_mixer_close(this->mixer_handle);
    this->mixer_handle = NULL;
    return -ENOENT;
  }

  snd_mixer_selem_get_playback_volume_range(this->elem, &this->volMin,
                                            &this->volMax);
  printf("volum range is from [%ld] to [%ld] \r\n", this->volMin, this->volMax);

  snd_mixer_close(this->mixer_handle);

  printf("[Debug] Exit init_audio_mixer\r\n");
  return true;
}

bool AudioMixerController::set_audio_volume(int left_volume, int right_volume) {
  printf("[Debug] Enter set_audio_volume\r\n");

  long volMin = this->volMin, volMax = this->volMax, leftVal = left_volume,
       rightVal = right_volume, current_leftVal = 0, current_rightVal = 0;
  int err = 0, err_left = 0, err_right = 0;

  if ((leftVal < volMin) || (leftVal > volMax) || (rightVal < volMin) ||
      (rightVal > volMax)) {
    printf("Volume value is out of range\r\n");
    return false;
  }

  err = snd_mixer_open(&this->mixer_handle, 0);
  if (err < 0) {
    printf("snd_mixer_open Err\n");
    return false;
  }

  err = snd_mixer_attach(this->mixer_handle, CTL_NAME);
  if (err < 0) {
    printf("snd_mixer_attach Err\n");
    return false;
  }

  err = snd_mixer_selem_register(this->mixer_handle, NULL, NULL);
  if (err < 0) {
    printf("snd_mixer_selem_register Err\n");
    return false;
  }

  err = snd_mixer_load(this->mixer_handle);
  if (err < 0) {
    printf("snd_mixer_load Err\n");
    return false;
  }

  this->elem = snd_mixer_first_elem(this->mixer_handle);

  while (this->elem) {
    // printf("elem name can be : %s\n", snd_mixer_selem_get_name(this->elem));
    if (strcmp("Speaker", snd_mixer_selem_get_name(this->elem)) == 0) {
      printf("elem name is : %s\r\n", snd_mixer_selem_get_name(this->elem));
      break;
    }
    this->elem = snd_mixer_elem_next(elem);
  }

  if (!this->elem) {
    printf("snd_mixer_find_selem Err\r\n");
    snd_mixer_close(this->mixer_handle);
    this->mixer_handle = NULL;
    return -ENOENT;
  }

  snd_mixer_handle_events(this->mixer_handle);
  err_left = snd_mixer_selem_get_playback_volume(
      this->elem, SND_MIXER_SCHN_FRONT_LEFT, &current_leftVal);
  if (err_left < 0) {
    printf("snd_mixer_selem_get_playback_volume get left volume Err\r\n");
  }

  err_right = snd_mixer_selem_get_playback_volume(
      this->elem, SND_MIXER_SCHN_FRONT_RIGHT, &current_rightVal);
  if (err_right < 0) {
    printf("snd_mixer_selem_get_playback_volume get right volume Err\r\n");
  }

  printf("current volum value: leftVal = %ld, rightVal = %ld\r\n",
         current_leftVal, current_rightVal);

  if (snd_mixer_selem_is_playback_mono(this->elem)) {
    // single channel
    printf("device is mono channel\r\n");

    if (err_left < 0) {
      snd_mixer_selem_set_playback_volume(this->elem,
                                          SND_MIXER_SCHN_FRONT_RIGHT, rightVal);
    } else if (err_right < 0) {
      snd_mixer_selem_set_playback_volume(this->elem, SND_MIXER_SCHN_FRONT_LEFT,
                                          leftVal);
    } else {
      printf("both left and right channel are not available\r\n");
    }

  } else {
    // left channel
    err = snd_mixer_selem_set_playback_volume(
        this->elem, SND_MIXER_SCHN_FRONT_LEFT, leftVal);
    if (err < 0) {
      printf("snd_mixer_selem_set_playback_volume set left volume Err\r\n");
    }

    // right channel
    err = snd_mixer_selem_set_playback_volume(
        this->elem, SND_MIXER_SCHN_FRONT_RIGHT, rightVal);
    if (err < 0) {
      printf("snd_mixer_selem_set_playback_volume set right volume Err\r\n");
    }
  }

  snd_mixer_close(this->mixer_handle);

  printf("[Debug] Exit set_audio_volume\r\n");
  return true;
}

}  // namespace mixer
}  // namespace audio
