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
## LSP
This code uses `compile_commands.json` on `build/` and **absolute path**, maybe you will need to configure this on your `LSP` *(probrably `clangd`)*, by adding the flag `--compile-commands-dir=build`

## Dependencies
- SDL: [`SDL2`](https://www.libsdl.org/), [`SDL2_image`](https://wiki.libsdl.org/SDL2_image/FrontPage), [`SDL2_mixer`](https://www.libsdl.org/projects/mixer/) and [`SDL2_ttf`](https://wiki.libsdl.org/SDL2_ttf/FrontPage)
- OpenGL: [`GLEW`](https://glew.sourceforge.net/)
- Math: [`glm`](https://github.com/g-truc/glm)

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
make
sudo make install
```
This will create a `build/` folder, inside it you should have a file called `libDynastinae.so`, if you want to use this file standalone. This will also install the lib to `/usr/include` and `/usr/lib`

## Run
To run a file of yours, including `Dynastinae`, you need to also include the required libraries
```sh
clang++ main.cpp -lDynastinae -lGL -lGLEW -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -o main
./maine
```

>Sooner linking all the required libraries will not be necessary anymore... or not

# Credits
### Libraries
[`SDL2`](https://www.libsdl.org/) ・ [`SDL2_image`](https://wiki.libsdl.org/SDL2_image/FrontPage) ・ [`SDL2_mixer`](https://www.libsdl.org/projects/mixer/) ・ [`SDL2_ttf`](https://wiki.libsdl.org/SDL2_ttf/FrontPage) ・[`GLEW`](https://glew.sourceforge.net/) ・ [`glm`](https://github.com/g-truc/glm)

and me 🦇 
