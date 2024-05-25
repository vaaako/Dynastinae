#include "../../../include/shapes/renderer/renderer.hpp"


Renderer::Renderer(const Window& window) : width(window.get_width()), height(window.get_height()) {}
Renderer::Renderer(const uint32 width, const uint32 height) : width(width), height(height) {}
