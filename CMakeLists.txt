cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

project (RobotFlier)

# Source code
file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE HEADERS ${PROJECT_SOURCE_DIR}/src/*.h)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic -O2)

# Find libs 
if(NOT EMSCRIPTEN)
  find_package(afk REQUIRED) 
  find_package(SDL2 REQUIRED)
  find_package(SDL2_mixer REQUIRED)
  find_package(SDL2_image REQUIRED)
  find_package(SDL2_ttf REQUIRED)
  find_package(SDL2_gfx REQUIRED)
  find_package(EnTT REQUIRED)
endif()

if(EMSCRIPTEN)
  # get_filename_component(EMSDK_DIR ${CMAKE_TOOLCHAIN_FILE} DIRECTORY)
  
  # include_directories(${EMSDK_DIR}/../../../system/include)

  # link_directories(${EMSDK_DIR}/../../../system/lib)

  target_compile_options(${PROJECT_NAME} 
    PUBLIC
      -sUSE_SDL=2
      -sUSE_SDL_IMAGE=2
      -sUSE_SDL_TTF=2
      -sUSE_SDL_MIXER=2
      -sUSE_SDL_GFX=2
  )

  set(SDL_LIBRARIES 
    "--use-preload-plugins \
    --preload-file ${CMAKE_BINARY_DIR}/build/audio@/audio \
    --preload-file ${CMAKE_BINARY_DIR}/build/data@/data \
    --preload-file ${CMAKE_BINARY_DIR}/build/fonts@/fonts \
    --preload-file ${CMAKE_BINARY_DIR}/build/images@/images \
    --preload-file ${CMAKE_BINARY_DIR}/build/screenshots@/screenshots \
    -s DISABLE_EXCEPTION_CATCHING=0 \
    -s DEMANGLE_SUPPORT=1 \
    -s USE_SDL=2 \
    -s USE_SDL_IMAGE=2 \
    -s USE_SDL_TTF=2 \
    -s USE_SDL_MIXER=2 \
    -s USE_SDL_GFX=2 \
    -s SDL2_IMAGE_FORMATS=[\"png\"]"
  ) 

# Run of the mill executable
else(EMSCRIPTEN)
  set(SDL_LIBRARIES SDL2::Image SDL2::Mixer SDL2::TTF SDL2::GFX SDL2::Main)
endif(EMSCRIPTEN)

# Link libraries
if(MINGW)
  target_link_libraries(${PROJECT_NAME} PRIVATE -lmingw32)
endif(MINGW)

target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL_LIBRARIES} EnTT::EnTT afk)

# Export assets
file(COPY ${PROJECT_SOURCE_DIR}/assets/audio DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${PROJECT_SOURCE_DIR}/assets/data DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${PROJECT_SOURCE_DIR}/assets/fonts DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${PROJECT_SOURCE_DIR}/assets/images DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${PROJECT_SOURCE_DIR}/assets/screenshots DESTINATION ${CMAKE_BINARY_DIR})
