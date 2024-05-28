# Target
- Custom vertex colors for 2D?
	+ Add to vertex attrib 2 on shape VBO and check if is to use on shape instance
	+ This could be done by making a custom shape (e.g. `new Cube(custom_color)`), then all variants from this shape with custom color would have this color
- .obj: When creating a OBJ `OBJ obj = Obj()` -> `renderer3d.draw_obj(obj)`. This makes a new VAO and VBO of that obj

- [X] Use Vector2f and Vector3f instead of glm versions
- [ ] Unify shader and `shader_texture` somehow
	+ I don't think this is possible
- [X] Custom keyboard enums
- [ ] Custom event enums
- [ ] More window events
- [ ] Resizing support
- [X] Multiple events support
- [X] Structs to .cpp
- [ ] Avoid circular import for `set_cursor_position` in `window.hpp`
- [X] BUG: If font is not a pointer, the window has a error when trying to close and the program has a segfaut
	+ Maybe it has something to do with the texture pointer in `font.hpp`
	+ SOLVE: I was closing `TTF_Font` when i shoudn't, in `font.cpp`
- [ ] Rotation on 3d object not working
- [ ] Camera best mouse movement
- [ ] Camera draw with custom position support
- [ ] Mouse handle click and motion at the same time
- [ ] Add `template struct vec<>` for vectors?
- [ ] Memory leak somewhere

- [Camera Movement](https://github.com/vaaako/Vakraft/blob/main/src/main/java/com/magenta/main/Game.java#L121)


# Future
- **Level of Detail (LOD):** Implement LOD techniques to dynamically adjust the level of detail based on the distance from the camera. This improves rendering performance by reducing the number of polygons rendered for distant objects.
- **Frustum Culling:** Implement frustum culling to eliminate objects that are outside the camera's view frustum from the rendering process. This reduces unnecessary draw calls and improves overall rendering performance.
