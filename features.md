# Not complete yet, just for I don't forget


# Template


```cpp
#include "../include/window/window.hpp"
#include "../include/shapes/2d/renderer2d.hpp"
#include "../include/shapes/3d/renderer3d.hpp"
#include <iostream>

void process_keyboard(Window& window, Keyboard keyboard) {
	if(keyboard.down == 27) {
		std::cout << "Closing" << std::endl;
		window.close();
	}
}

int main() {
	// Create main Window
	const std::string title = "Helllo Knuppel";
	Window window = Window(title, 800, 600, true); // Title, Width, Height, VSync

	Renderer2D renderer = Renderer2D();
	Renderer3D renderer = Renderer3D(45.0f, 0.1f, 100.0f); // Set camera


	// Main loop
	while(window.is_open()) {
		// Clear window
		window.clear(1.0f, 0.5f, 1.0f);

		// Events handler
		switch (window.process_event()) {
			case Event::QUIT:
				window.close();
				break;

			case Event::KEYDOWN:
			case Event::KEYUP:
				// Add more events if you need
				process_keyboard(window, window.keyboard());
				break;

			default:
				break;
		}

		// Draw shapes
		// The draw order matters
		renderer.set_color(Color(1.0f, 1.0f, 0.0f ));
		renderer.triangle(texture, 100.0f, 100.0f, 100.0f, Color(0.0f, 1.0f, 0.0f), 50.0f, false);
		renderer.triangle(200.0f, 150.0f, 100.0f, -50.0f);
		renderer.triangle(300.0f, 250.0f, 100.0f);

		renderer.rectangle(texture, 200.0f, 150.0f, 200.0f, 200.0f, rotation);
		renderer.rectangle(350.0f, 300.0f, 200.0f, 200.0f, Color(0.0f, 0.0f, 1.0f));
		rotation += 1.0f;

		renderer3d.pyramid(texture, 10.0f, 100.0f, 100.0f, 100.0f, rotation);


		// Swap buffers
		window.swap();

		// Each one second show FPS
		window.set_title(title + " | FPS: " + std::to_string(window.fps()));
	}
}
```



![img_here]()


# 2D Shapes and Colors
## Colors
In order to draw a shape, you need to create a renderer, this is simple as that
```cpp
Renderer2D renderer = Renderer2D();
```

You can use the `Color` struct to color with a flat color using **RGBA** in the range of **0 - 1**.

The `Color` struct also has an **alpha** optional parameter.

```cpp
//        R     G     B     A
Color(1.0f, 0.0f, 0.0f, 1.0f );`
```

You can set a color to use on all 2D shapes
```cpp
renderer.set_color(Color(1.0f, 1.0f, 0.0f));
```

```cpp
renderer.set_color(1.0f, 1.0f, 0.0f);
```

This will set the color for **ALL** shapes, even the ones above this *set*

If you don't set the color, the default color will be white

If you want to use **0 - 255** range, you can use a **Color** built-in method
```cpp
//                                   R    G   B   A
renderer.set_color(Color::from_rgba(255, 255, 0, 255));
```

>The **alpha** parameter is optional


## Shapes
```cpp
//                  X       Y      WIDTH  HEIGHT
renderer.rectangle(100.0f, 100.0f, 50.0f, 50.0f);
```

You can also define a color for a individual shape
```cpp
//                  X       Y      WIDTH  HEIGHT                COLOR
renderer.rectangle(100.0f, 100.0f, 50.0f, 50.0f, Color(0.0f, 1.0f, 1.0f, 1.0f));
```

```cpp
// This is dark blue, because was the last color set to the renderer
renderer.rectangle(100.0f, 100.0f, 50.0f, 50.0f);

// Both below are dark blue
renderer.set_color(0.0f, 0.0f, 1.0f);
renderer.rectangle(150.0f, 100.0f, 50.0f, 50.0f);
renderer.rectangle(200.0f, 100.0f, 50.0f, 50.0f);

// This is yellow
renderer.rectangle(100.0f, 300.0f, 50.0f, 50.0f, Color(1.0f, 1.0f, 0.0f));
```

![img_here]()

You can rotate, and draw the outline only
```cpp
//                  X       Y      WIDTH  HEIGHT ROTATE  OUTLINE
renderer.rectangle(100.0f, 100.0f, 50.0f, 50.0f, 180.0f, true);
```

## Custom colors
...
<!--
Alternatively, use a vector to color each corner with a separate color, creating a gradient effect.
```cpp
// Corners color
Rectangle rectangle(100.0f, 100.0f, 200.0f, 200.0f
	{
		// R    G     B     A
		1.0f, 0.0f, 0.0f, 1.0f // Top Right
		0.0f, 1.0f, 0.0f, 1.0f // Bottom Right
		0.0f, 0.0f, 1.0f, 1.0f // Bottom Left
		1.0f, 1.0f, 1.0f, 1.0f // Top Left
	}
);
```

![img_here]()
-->


All above are the same for drawing a triangle, but instead of a `width` and `height`, triangle only have a `side`
```cpp
//                 X       Y      SIZE
Triangle triangle(100.0f, 100.0f, 200.0f);
```

![img_here]()


# Textures
Texture path is relative to the path you run

e.g. if the executable file is inside `example/build/` but you run from `example/`
 the texture path is relative from `example/`, so, if the texture is inside
 `example/assets/texture.jpg` the path to the texture is `assets/texture.jpg`

Load the texture
```cpp
Texture texture = Texture("assets/texture.jpg");
```

Then bind it to a shape
```cpp
//                 TEXTURE   X       Y      WIDTH  HEIGHT
renderer.rectangle(texture, 100.0f, 100.0f, 50.0f, 50.0f);
```
>This is the same for any other shape

![img_here]()

The **renderer color** doesn't colorize the texture, to do so you need to set individually
```cpp
//                 TEXTURE   X       Y      WIDTH  HEIGHT
renderer.rectangle(texture, 100.0f, 100.0f, 50.0f, 50.0f, Color(1.0f, 1.0f, 0.0f));
```
This will apply a yellow filter to the texture


![img_here]()

## Filters
...



