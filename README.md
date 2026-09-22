# Dreamy Chip8

A WIP CHIP-8 emulator written in C++20 using SDL and OpenGL.

Still extremely incomplete.

Mostly a C++ learning project to brush off old skills before moving onto NES or GB.

## Cloning

... If you have to ask how to clone a git repo, why are you looking at my dumb emulator and not just downloading something that isn't a rando's project.

## Requirements

On MacOS, most tools you need are provided by the XCode Command Line Tools.

```
- A C++20 compatible compiler
- CMake 3.25 or newer
- OpenGL 3.2 support on your device
- Just (https://github.com/casey/just)
  - Optional if you want to just copy-paste CMake commands.
```

Project dependencies are downloaded during CMake configuration:

```
- SDL
- spdlog
- Dear ImGui
```

## Building

In a terminal, run `just build`

## Running

In a terminal, run `just run`.

## Tests

// TODO: Figure out how unit tests even work in C++.
