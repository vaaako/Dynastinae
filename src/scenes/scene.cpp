#include "Dynastinae/scenes/scene.hpp"


Scene::Scene(const Window& window) : width(window.get_width()), height(window.get_height()) {}
Scene::Scene(const uint32 width, const uint32 height) : width(width), height(height) {}
