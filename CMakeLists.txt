cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)

project (RobotFlier)

file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "src/*.h")

# SOURCE
set (INCLUDE_DIRS "")
foreach (_headerFile ${HEADERS})
  get_filename_component(_dir ${_headerFile} PATH)
  list (APPEND INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES INCLUDE_DIRS)

find_library(ALLEGRO_LIBRARY NAMES liballegro.dll.a liballegro.so)
find_library(ALLEGRO_ACODEC_LIBRARY NAMES liballegro_acodec.dll.a liballegro_acodec.so)
find_library(ALLEGRO_AUDIO_LIBRARY NAMES liballegro_audio.dll.a liballegro_audio.so)
find_library(ALLEGRO_COLOR_LIBRARY NAMES liballegro_color.dll.a liballegro_color.so)
find_library(ALLEGRO_DIALOG_LIBRARY NAMES liballegro_dialog.dll.a liballegro_dialog.so)
find_library(ALLEGRO_FONT_LIBRARY NAMES liballegro_font.dll.a liballegro_font.so)
find_library(ALLEGRO_IMAGE_LIBRARY NAMES liballegro_image.dll.a liballegro_image.so)
find_library(ALLEGRO_MAIN_LIBRARY NAMES liballegro_main.dll.a liballegro_main.so)
find_library(ALLEGRO_PRIMITIVES_LIBRARY NAMES liballegro_primitives.dll.a liballegro_primitives.so)
find_library(ALLEGRO_TTF_LIBRARY NAMES liballegro_ttf.dll.a liballegro_ttf.so)

add_executable (RobotFlier ${SOURCES})

target_compile_options(RobotFlier PRIVATE -Wall -Wextra -pedantic)

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

target_include_directories(RobotFlier PRIVATE ${INCLUDE_DIRS})

# TESTING
file(GLOB_RECURSE TEST_SOURCES "tests/*.cpp")
file(GLOB_RECURSE TEST_HEADERS "tests/*.h")

set (INCLUDE_DIRS "")
foreach (_headerFile ${TEST_HEADERS})
  get_filename_component(_dir ${_headerFile} PATH)
  list (APPEND INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES INCLUDE_DIRS)

set(CATCH_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tests/catch2)
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR})

add_executable(tests ${TEST_SOURCES})
target_link_libraries(tests Catch)