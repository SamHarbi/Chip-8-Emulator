# Chip8Emulator
## About
My attempt at writing a Chip8 Emulator. This is mainly a learning exercise / experimental ground
for designing a modern C++ codebase- But this is still a working emulator first and foremost. The former
only acts as an excuse for any excess choices. At a glance those are as follows:

- Targeting Modern C++23, Built with CMake.
- Dynamic dependencies declaratively defined via the [Nix Flake](https://wiki.nixos.org/wiki/Flakes) system. Creates the exact dev environment needed by
cmake for compilation. Requires a system running NixOS or the Nix Package manager installed. Similar to Docker but without the overhead of a whole filesystem.
- Separate Renderer made with OpenGL (GLEW & GLFW). Every "frame" rendered by the emulator is displayed as a texture.
- Input manager, which is handled by GLFW

## Emulator Compliance
### Corax+ Extended Opcode Test | [Chip-8 test suite](https://github.com/Timendus/chip8-test-suite)
![Corax+ Opcode Test Result](/assets/corax+.png "Corax+ Opcode Test")

### Flags Test | [Chip-8 test suite](https://github.com/Timendus/chip8-test-suite)
![Flags Test Result](/assets/flags.png "Flags Test")

