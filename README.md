# Chip8Emulator
## About
My attempt at writing a Chip8 Emulator. This is mainly a learning exercise / experimental ground
for architecting a modern C++ codebases- But this is still a working emulator first and foremost. The former
only acts as an excuse for any esoteric choices.
## Design
- Modern C++23, Built with CMake.
- Development enviroment and dynamic dependencies declaratively defined via the [Nix Flake](https://wiki.nixos.org/wiki/Flakes) system. Creates the exact dev enviroment needed by
cmake for compiliation. Requires a system running NixOS or the Nix Package manager installed. Similar to Docker but without the overhead of a whole filesystem.
- Seperate Renderer made with OpenGL (GLEW & GLFW). Every "frame" rendered by the emulator is displayed as a texture.

<img width="640" height="342" alt="image" src="https://github.com/user-attachments/assets/ef8edf75-f3c8-4076-bfb2-91e30e81b4d9" />

