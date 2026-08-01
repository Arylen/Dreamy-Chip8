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

FetchContent_Declare(
  imgui
  GIT_REPOSITORY https://github.com/ocornut/imgui.git
  GIT_TAG v1.92.8-docking
  GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(spdlog SDL3 imgui)

find_package(OpenGL REQUIRED)

add_library(
  dreamy_imgui STATIC
  "${imgui_SOURCE_DIR}/imgui.cpp"
  "${imgui_SOURCE_DIR}/imgui_demo.cpp"
  "${imgui_SOURCE_DIR}/imgui_draw.cpp"
  "${imgui_SOURCE_DIR}/imgui_tables.cpp"
  "${imgui_SOURCE_DIR}/imgui_widgets.cpp"
  "${imgui_SOURCE_DIR}/backends/imgui_impl_sdl3.cpp"
  "${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp"
)

target_include_directories(
  dreamy_imgui
  PUBLIC
    "${imgui_SOURCE_DIR}"
    "${imgui_SOURCE_DIR}/backends"
)

target_link_libraries(
  dreamy_imgui
  PRIVATE
    SDL3::SDL3
    OpenGL::GL
)

# Project Executable
add_executable(
  dreamy_chip8

  # Core stuff
  src/main.cpp
  src/core/Log.cpp
  src/window/AppWindow.cpp
  src/Application.cpp

  # Emulation
  src/core/emulation/Chip8VM.cpp

  # Ui Elements
  src/core/ui/MainMenuBar.cpp

  # Ui Windows
  src/core/ui/windows/LogWindow.cpp
  src/core/ui/windows/CpuStateWindow.cpp
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
    dreamy_imgui
    SDL3::SDL3
    OpenGL::GL
    spdlog::spdlog
)

# Copy roms and metadata
set(
  DREAMY_ASSET_DIR
  "$<TARGET_FILE_DIR:dreamy_chip8>/assets"
)

add_custom_target(
  copy_runtime_data ALL

  COMMAND
    ${CMAKE_COMMAND} -E remove_directory
    "${DREAMY_ASSET_DIR}/database"
  COMMAND
    ${CMAKE_COMMAND} -E remove_directory
    "${DREAMY_ASSET_DIR}/fonts"
  COMMAND
    ${CMAKE_COMMAND} -E remove_directory
    "${DREAMY_ASSET_DIR}/roms/archive"
  COMMAND
    ${CMAKE_COMMAND} -E remove_directory
    "${DREAMY_ASSET_DIR}/roms/tests"

  COMMAND
    ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/external/chip-8-database/database"
    "${DREAMY_ASSET_DIR}/database"
  COMMAND
    ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/external/chip8-archive/roms"
    "${DREAMY_ASSET_DIR}/roms/archive"
  COMMAND
    ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/external/chip8-test-suite/bin"
    "${DREAMY_ASSET_DIR}/roms/tests"
  COMMAND
    ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/assets/fonts"
    "${DREAMY_ASSET_DIR}/fonts"

  DEPENDS dreamy_chip8
  COMMENT "Building asset directory"
  VERBATIM
)

if(MSVC)
    target_compile_options(dreamy_chip8 PRIVATE /W4 /permissive-)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "^(AppleClang|Clang|GNU)$")
    target_compile_options(dreamy_chip8 PRIVATE -Wall -Wextra -Wpedantic)
endif()

add_custom_target(
    run
    COMMAND $<TARGET_FILE:dreamy_chip8>
    DEPENDS dreamy_chip8 copy_runtime_data
    WORKING_DIRECTORY $<TARGET_FILE_DIR:dreamy_chip8>
    USES_TERMINAL
)
