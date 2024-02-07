# Knuppel 🦇
# About
**Knuppel** is a very simple and basic framework I am developing to code some games

Using `SDL2` and `Glad` I aim to create a very simple to use framework to supply my needs

![demo2](media/demo2.png)
![demo3](media/demo3.png)

# Current Stage
**Knuppel** is in very early stages, check `src/main.cpp`

# Objectives
- [X] Window creation
- [X] Events
    + Not all, but I can add more if I need
- [X] 2D shapes
    + [X] Draw
    + [X] Colors
    + [X] Position
    + [ ] Texture
- [ ] 3D shapes
    + [ ] Draw
    + [ ] Colors
    + [ ] Position
    + [ ] Texture

# Running
## Dependencies
You will need to install[`SDL2`](https://www.libsdl.org/) *(If you are on Linux is probably avaiable on your package manager)*,

## Compiling
- If you want to compile as `lib` and use in any project, you will need `Make`
- If you just want to test and use `main.cpp` *(inside `src/`)*, you will ned `CMake`

## CMake
```sh
cmake -S . -B build # Config
cmake --build build # Compile
./build/knuppel     # Run
```

This way you will run the `main.cpp`

## Make
```sh
mkdir build # Make build directory
make        # Compile
```
This will create a `lib/` folder, inside it you should have a file called `libknuppel.so`, if you want to use this file,
 locally, you can move to your project directory and link to your program

For now, You will also need `glad.o`
```sh
clang -c libs/glad/glad.c
```
>I will change this later

## Linking to your program
### Locally
Move `include` folder to your project

Let's say you have a file called `main.cpp` importing **Knuppel**, you should include with `""`:
```cpp
#include "include/Knuppel/window/window.hpp"
```

To run the program with `Knuppel` linked, you should run the following command:
```sh
clang++ main.cpp glad.o -lSDL2 -L. -lknuppel glad.o -o game
```

### Globally
Alternativally, to not have to use `-L.` flag, you can move `libknuppel.so` to `/usr/lib` and **Knuppel**'s include folder to `/usr/include`,
 this way you don't need to move `libknuppel.so` to every project you want to use it
```
sudo cp -r libknuppel.so /usr/lib/
sudo cp -r include/ /usr/include/Knuppel
```

Then you can include with `<>`
```cpp
#include <Knuppel/window/window.hpp>
```

And run without `-L.` flag
```sh
clang++ main.cpp -lSDL2 -lknuppel -o game
```

# Credits
Made by me 🦇

**Libraries used:** [`SDL2`](https://www.libsdl.org/) for graphics and input handling, and [`Glad`](https://glad.dav1d.de/) for OpenGL

