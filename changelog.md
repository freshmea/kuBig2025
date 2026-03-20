# Changelog

## 2026-03-20

- Added c_example/bowlingRay as a raylib-based graphical bowling example derived from the bowling scoring logic.
- Added root CMake integration for the bowlingRay target.
- Fixed bowlingRay text rendering by loading a Korean-capable system font instead of relying on raylib's default ASCII font.
- Added detailed documentation for bowlingRay covering library installation, system configuration, file layout, build, and usage.
- Updated VS Code C/C++ include and browse paths so IntelliSense can resolve system-installed raylib headers.
- Split VS Code IntelliSense into separate Arduino-AVR and Linux-raylib configurations.
- Connected the Linux-raylib IntelliSense profile to build/compile_commands.json so VS Code can use actual CMake compile commands.