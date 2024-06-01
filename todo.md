# Target
- [X] Use Vector2f and Vector3f instead of glm versions
- [ ] Unify shader and `shader_texture` somehow
	+ I don't think this is possible
- [ ] **[?]** Texture overlay
	+ Texture atlas support
	+ Opacity
- [X] Custom keyboard enums
- [ ] Window Events
	+ [X] Custom event enums
	+ [X] Multiple events support
	+ [ ] Resizing support
	+ [ ] Mouse handle click and motion at the same time
	+ [ ] More window events
- [X] Structs to `.cpp`
- [ ] Avoid circular import for `set_cursor_position` in `window.hpp`
- [X] BUG: If font is not a pointer, the window has a error when trying to close and the program has a segfaut
	+ Maybe it has something to do with the texture pointer in `font.hpp`
	+ **SOLUTION:** I was closing `TTF_Font` when i shoudn't, in `font.cpp`
- [ ] Rotation of 3D shape not working
- [ ] Camera
	+ [Camera Movement](https://github.com/vaaako/Vakraft/blob/main/src/main/java/com/magenta/main/Game.java#L121)
	+ [ ] Best mouse movement
	+ [ ] Custom position for shapes
- [X] **[DISCARTED]** Add `template struct vec<>` for vectors
- [ ] Memory leak somewhere (i don't know if is on my `font.hpp` or SDL2 one)
- [X] Split `shapes/` and `renderers/`
	+ I don't know if `renderes/` is the correct name
- [X] View `Raylib` source code

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
