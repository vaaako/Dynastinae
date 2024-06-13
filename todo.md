# Target
- [X] Use Vector2f and Vector3f instead of glm versions
- [X] Custom keyboard enums
- [X] Structs to `.cpp`
- [X] BUG: If font is not a pointer, the window has a error when trying to close and the program has a segfaut
	+ Maybe it has something to do with the texture pointer in `font.hpp`
	+ **SOLUTION:** I was closing `TTF_Font` when i shoudn't, in `font.cpp`
- [X] **[DISCARTED]** Add `template struct vec<>` for vectors
- [X] Split `shapes/` and `renderers/`
	+ I don't know if `renderes/` is the correct name
- [X] View `Raylib` source code
- [X] Fix log `fmt`
	+ [X] Log for `audio.cpp` and `font.cpp` -> instead of logging full path, make a method on `StringHelper` to get only the file name
- [X] Avoid circular import for `set_cursor_position` in `window.hpp`
- [ ] Unify shader and `shader_texture` somehow
	+ I don't think this is possible
	+ Maybe set the texture alpha to zero when using just solid color?
- [ ] **[?]** More texture options
	+ [ ] Different texture for each face
	+ [ ] Texture overlay
	+ [ ] Texture atlas support
	+ [ ] Opacity
- [ ] Window Events
	+ [X] Custom event enums
	+ [X] Multiple events support
	+ [ ] Resizing support
	+ [ ] Mouse handle click and motion at the same time
	+ [ ] More window events
- [ ] Camera
	+ [X] **[DISCARTED]** [Camera Movement](https://github.com/vaaako/Vakraft/blob/main/src/main/java/com/magenta/main/Game.java#L121)
	+ [X] Best mouse movement
	+ [X] Custom position for shapes
	+ [X] Rotation of 3D shape not working
	+ [ ] Shapes custom scale
- [ ] Memory leak somewhere (i don't know if is on my `font.hpp` or SDL2 one)
- [ ] **[!]** Move draw to the shape struct. e.g. Cube -> import cube shape -> `cube.draw(args)`;
	+ Renderer3D -> `renderer.draw_cube(texture)` -> `cube.draw(texture)`
	+ [Tutorial](https://www.youtube.com/watch?v=NUZF_5RKfS4)
	+ Rename `shape.hpp` to `mesh.hpp`
- [ ] Put required libraries `shared libraries` files on `libs/` folder


# Notes
- **[?]** Custom vertex colors for 2D
	+ Add to vertex attrib 2 on shape VBO and check if is to use on shape instance
	+ This could be done by making a custom shape (e.g. `new Cube(custom_color)`), then all variants from this shape with custom color would have this color
- When creating a `Object` -> `Model obj = Model("assets/models/character.obj")`
	+ `Model` will be a struct with `VAO` and `VBO` *(possibly a child of `Shape`)*
	+ `camera.draw_obj(obj)`
<!--
# Future
- **Level of Detail (LOD):** Implement LOD techniques to dynamically adjust the level of detail based on the distance from the camera. This improves rendering performance by reducing the number of polygons rendered for distant objects.
- **Frustum Culling:** Implement frustum culling to eliminate objects that are outside the camera's view frustum from the rendering process. This reduces unnecessary draw calls and improves overall rendering performance.
-->
