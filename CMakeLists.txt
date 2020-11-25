cmake_minimum_required(VERSION 3.11)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)

project (RobotFlier)

# Source code
file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h)

add_executable (RobotFlier ${SOURCES} ${HEADERS})

target_compile_options(RobotFlier PRIVATE -Wall -Wextra -pedantic)

# Find libs
find_library(ALLEGRO_LIBRARY NAMES liballegro.dll.a liballegro.so liballegro.5.2.dylib)
find_library(ALLEGRO_ACODEC_LIBRARY NAMES liballegro_acodec.dll.a liballegro_acodec.so liballegro_acodec.5.2.dylib)
find_library(ALLEGRO_AUDIO_LIBRARY NAMES liballegro_audio.dll.a liballegro_audio.so liballegro_audio.5.2.dylib)
find_library(ALLEGRO_COLOR_LIBRARY NAMES liballegro_color.dll.a liballegro_color.so liballegro_color.5.2.dylib)
find_library(ALLEGRO_DIALOG_LIBRARY NAMES liballegro_dialog.dll.a liballegro_dialog.so liballegro_dialog.5.2.dylib)
find_library(ALLEGRO_FONT_LIBRARY NAMES liballegro_font.dll.a liballegro_font.so liballegro_font.5.2.dylib)
find_library(ALLEGRO_IMAGE_LIBRARY NAMES liballegro_image.dll.a liballegro_image.so liballegro_image.5.2.dylib)
find_library(ALLEGRO_MAIN_LIBRARY NAMES liballegro_main.dll.a liballegro_main.so liballegro_main.5.2.dylib)
find_library(ALLEGRO_PRIMITIVES_LIBRARY NAMES liballegro_primitives.dll.a liballegro_primitives.so liballegro_primitives.5.2.dylib)
find_library(ALLEGRO_TTF_LIBRARY NAMES liballegro_ttf.dll.a liballegro_ttf.so liballegro_ttf.5.2.dylib)

# Link Libs
target_link_libraries(RobotFlier ${ALLEGRO_LIBRARY})
target_link_libraries(RobotFlier ${ALLEGRO_ACODEC_LIBRARY})
target_link_libraries(RobotFlier ${ALLEGRO_AUDIO_LIBRARY})
target_link_libraries(RobotFlier ${ALLEGRO_COLOR_LIBRARY})
target_link_libraries(RobotFlier ${ALLEGRO_DIALOG_LIBRARY})
target_link_libraries(RobotFlier ${ALLEGRO_FONT_LIBRARY})
target_link_libraries(RobotFlier ${ALLEGRO_IMAGE_LIBRARY})
target_link_libraries(RobotFlier ${ALLEGRO_MAIN_LIBRARY})
target_link_libraries(RobotFlier ${ALLEGRO_PRIMITIVES_LIBRARY})
target_link_libraries(RobotFlier ${ALLEGRO_TTF_LIBRARY})

