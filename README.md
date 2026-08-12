# FlatOut 2 AI Limit Adjuster

Plugin to increase the maximum amount of AI opponents in FlatOut 2

![128 cars preview](https://i.imgur.com/Vl8u9mL.png)
![fouc ai preview](https://i.imgur.com/QBhbm3R.png)

# Disclaimer

Due to the current programming landscape, I feel that it's necessary to explicitly state that this project had zero assistance or any other kind of involvement from any sort of "AI agent" and it never will.  
This mod was entirely built by hand, by a human being, and I believe that any project that cannot also claim this about itself is not worth people's time. The only acceptable amount of AI use is zero AI use.

## Installation

- Make sure you have v1.2 of the game, as this is the only version this plugin is compatible with. (exe size of 2990080 bytes)
- Plop the files into your game folder, edit `FlatOut2AILimitAdjuster_gcp.toml` to change the options to your liking.
- Enjoy, nya~ :3

## Building

Building is done on an Arch Linux system with CLion and vcpkg being used for the build process. 

Before you begin, clone [nya-common](https://github.com/gaycoderprincess/nya-common) to a folder next to this one, so it can be found.

Required packages: `mingw-w64-gcc vcpkg`

To install all dependencies, use:
```console
vcpkg install tomlplusplus:x86-mingw-static
```

Once installed, copy files from `~/.vcpkg/vcpkg/installed/x86-mingw-static/`:

- `include` dir to `nya-common/3rdparty`
- `lib` dir to `nya-common/lib32`

You should be able to build the project now in CLion.
