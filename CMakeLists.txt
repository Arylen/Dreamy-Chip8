# Setup
cmake_minimum_required(VERSION 3.25)

project(
  DreamyChip8
  VERSION 0.1.0
  LANGUAGES CXX
)

include(FetchContent)
include(CTest)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dependencies
set(SPDLOG_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(SPDLOG_BUILD_EXAMPLE OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
  spdlog
  GIT_REPOSITORY https://github.com/gabime/spdlog.git
  GIT_TAG v1.17.0
  GIT_SHALLOW TRUE
)

FetchContent_Declare(
  SDL3
  GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
  GIT_TAG release-3.4.12
  GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(spdlog SDL3)

find_package(OpenGL REQUIRED)

# Project Executable
add_executable(
  dreamy_chip8
  src/main.cpp
  src/core/Log.cpp
  src/window/AppWindow.cpp
)

target_include_directories(
  dreamy_chip8
  PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

target_compile_features(
  dreamy_chip8
  PRIVATE cxx_std_20
)

target_link_libraries(
  dreamy_chip8
  PRIVATE
    SDL3::SDL3
    OpenGL::GL
    spdlog::spdlog
)

if(MSVC)
    target_compile_options(dreamy_chip8 PRIVATE /W4 /permissive-)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "^(AppleClang|Clang|GNU)$")
    target_compile_options(dreamy_chip8 PRIVATE -Wall -Wextra -Wpedantic)
endif()

add_custom_target(
    run
    COMMAND $<TARGET_FILE:dreamy_chip8>
    DEPENDS dreamy_chip8
    USES_TERMINAL
)
