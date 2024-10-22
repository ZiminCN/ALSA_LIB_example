cmake_minimum_required (VERSION 3.20)
project(audio_ALSA_control)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_SOURCE_DIR}/inc)

add_executable(audio_ALSA_control src/main.cpp 
src/asound_driver.cpp 
src/audio_file_analyzer.cpp 
src/audio_mixer_controller.cpp
src/audio_play_task_controller.cpp
)

target_link_libraries(audio_ALSA_control asound)
