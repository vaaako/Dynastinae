#include "../../../include/shapes/renderer/renderer.hpp"


Renderer::Renderer(const Window& window) : width(window.get_width()), height(window.get_height()) {}
Renderer::Renderer(const unsigned int width, const unsigned int height) : width(width), height(height) {}
