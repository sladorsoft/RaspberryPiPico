# Raspberry Pi Pico examples

This repository holds all the source code and other resources used in my tutorial series on **[YouTube](https://www.youtube.com/c/SladorSoft)**.

### The repository contents:

- "**templates**" contains simple "Hello World" examples to start your new projects for Raspberry Pi Pico from. One of them is a [FreeRTOS](https://www.freertos.org/) sample application.
- "**tutorials**" contains all the source code used in my videos on **[YouTube](https://www.youtube.com/c/SladorSoft)**. Each directory inside it is named after the video the source code is used in.

### Prerequisites:

- [Pico SDK](https://github.com/raspberrypi/pico-sdk) - **PICO_SDK_PATH** environment variable must point to the directory containing your local copy
- [Git](https://git-scm.com/)
- [ARM GNU Toolchain](https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads) - its "bin" subdirectory must be added to the **PATH** variable
- your native C/C++ toolset - its "bin" subdirectory must be added to the **PATH** variable. For Windows use [GCC for Windows](https://winlibs.com/)
- [CMake](https://cmake.org/) (GCC for Windows toolset already includes it and you don't need to install it separately).
- [Ninja build system](https://ninja-build.org/) - you need a build system, depending on your OS. All projects in this repo have been tested using Ninja (GCC for Windows toolset already includes it and you don't need to install it separately).
- [Python 3](https://www.python.org/) - required by Pico SDK
- (optionally) [Visual Studio Code](https://code.visualstudio.com/). For full integration, install "C/C++" and "CMake Tools" extensions (both from Microsoft).

### Building:

For my daily development I use a Windows machine with "GCC for Windows", Ninja and VS Code as my IDE, which nicely integrates with CMake. All my projects include some basic configuration for VS Code. I may occasionally test the build on Ubuntu as well.

You can build all the projects without using an IDE. Open the command line in the root of each project and type:
```
cmake -B build -D CMAKE_BUILD_TYPE=Release .
cmake --build build
```
If, for some reason, the default generator (Ninja) is not picked up correctly (or if you wish to use a different one), you may specify it explicitly in the command line:
```
cmake -B build -G Ninja -D CMAKE_BUILD_TYPE=Release .
cmake --build build
```


For more details visit my website **[www.slador.uk](https://www.slador.uk/)**

If you find it interesting, please consider **[subscribing](https://www.youtube.com/c/SladorSoft)**.
