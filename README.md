# Dynastinae 🪲
# About
**Dynastinae** is a very basic game framework I am developing to code some simple games

![demo](media/demo.gif)
<!-- ![demo2](media/demo2.png) -->
<!-- ![demo3](media/demo3.png) -->

# Current Stage
**Dynastinae** is in very early stages, check `src/main.cpp`

## Objectives
- [X] Window creation
- [X] Events
    + Not all, but I can add more if I need
- [X] 2D shapes
    + [X] Draw
    + [X] Colors
    + [X] Texture
    + [X] Position
    + [ ] Line
    + [ ] Better triangle
    + [ ] Circle
- [X] 3D shapes
    + [X] Draw
    + [X] Colors
    + [X] Texture
    + [ ] Position
    + [ ] 3D shapes size?
    + [ ] Skybox
    + [ ] Import `.obj`
- [X] Movement
- [X] Audio
- [X] Fonts
- [ ] Gif texture?
- [ ] Stuff I didn't think of

# Running
## Dependencies
- SDL: [`SDL2`](https://www.libsdl.org/), [`SDL2 Image`](https://wiki.libsdl.org/SDL2_image/FrontPage), [`SDL2 Mixer`](https://www.libsdl.org/projects/mixer/) and [`SDL2 TTF`](https://wiki.libsdl.org/SDL2_ttf/FrontPage)
- OpenGL: [`GLEW`](https://glew.sourceforge.net/)

*(If you are on Linux is probably all avaiable on your package manager)*,

## Compiling
- If you want to compile as a `lib` file and use in any project, you will need `Make`
- If you just want to test and use `main.cpp` *(inside `src/`)*, you will need `CMake`

## CMake
```sh
cmake -S . -B build # Config
cmake --build build # Compile
./build/dynastinae  # Run
```

## Make
```sh
sudo make install
```
This will create a `lib/` folder, inside it you should have a file called `libdynastinae.so`, if you want to use this file. This will also install the lib to `/usr/include` and `/usr/lib`

## Linking to your program
<!--
### Locally
Move `include` folder to your project

Let's say you have a file called `main.cpp` importing **dynastinae**, you should include with `""`:
```cpp
#include "include/dynastinae/window/window.hpp"
```

To run the program with `dynastinae` linked, you should run the following command:
```sh
clang++ main.cpp -lSDL2 -lSDL2_image -lGL -lGLEW -L. -ldynastinae -o game
```

### Globally
Alternativally, to not have to use `-L.` flag, you can move `libdynastinae.so` to `/usr/lib` and **Dynastinae**'s include folder to `/usr/include`,
 this way you don't need to move `libdynastinae.so` to every project you want to use it
-->

If you just executed `make` without `install`, you have to move some files
```
sudo cp lib/libdynastinae.so /usr/lib/
sudo cp -r include/ /usr/include/dynastinae
```

Then you can include properly
```cpp
#include <Dynastinae/window/window.hpp>
```

And now you can run
```sh
clang++ main.cpp -lGL -lGLEW -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -ldynastinae -o game
```

>Sooner linking all the required libraries will not be necessary anymore

# Credits
### Libraries
[`SDL2`](https://www.libsdl.org/) ・ [`SDL2 Image`](https://wiki.libsdl.org/SDL2_image/FrontPage) ・ [`SDL2 Mixer`](https://www.libsdl.org/projects/mixer/) ・ [`SDL2 TTF`](https://wiki.libsdl.org/SDL2_ttf/FrontPage) ・[`GLEW`](https://glew.sourceforge.net/)

and me 🦇 
