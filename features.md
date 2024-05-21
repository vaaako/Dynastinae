# Not finished yet
This file is not ready yet, and will not be until i release v1.0



# Template


```cpp
#include <Knuppel/window/window.hpp>
#include <Knuppel/shapes/renderer/renderer2d.hpp>
#include <Knuppel/shapes/renderer/renderer3d.hpp>
#include <Knuppel/types/audio.hpp>
#include <Knuppel/types/font.hpp>

#include <iostream>

void process_keyboard(Window& window, Keyboard keyboard) {
	// 27 - ESC
	// You can use keycode or Enum
	if(keyboard.down == 27 || keyboard.down == SDLK_ESCAPE) {
		std::cout << "Closing" << std::endl;
		window.close();
	}
}

int main() {
	Window window = Window("Hello Knuppel", 800, 600, true, true);

	Texture* texture = new Texture("src/texture.jpg", TextureFilter::NEAREST, TextureWrap::MIRRORED);
	Texture* texture2 = new Texture("src/texture2.png", TextureFilter::NEAREST, TextureWrap::MIRRORED);
	Texture* texture3 = new Texture("src/texture3.png", TextureFilter::NEAREST, TextureWrap::MIRRORED);

	// MUSIC - Play only one at the channel
	// SOUND - Can play multple at the same channel
	Audio* mp3 = new Audio("src/sound.mp3", false); // Path, is music
	mp3->set_volume(50);

	Audio* wav = new Audio("src/music.wav", true);
	wav->set_volume(50);

	Font* font = new Font("src/yourfont.ttf", "FPS: 0", 24, { 255 }); // Path, Text, Size, Color

	Renderer2D renderer = Renderer2D();
	Renderer3D renderer3d = Renderer3D(45.0f, 0.1f, 100.0f); // Set camera

	float rotation = 0.0f;
	unsigned int start_time = window.time(); // To count FPS
	while(window.is_open()) {
		window.clear({ 255, 127, 255 });


		// Handle events
		switch (window.process_event()) {
			case Event::QUIT:
				window.close();
				break;

			case Event::KEYDOWN:
			case Event::KEYUP:
				process_keyboard(window, window.keyboard());

				// Here just for demonstration
				if(window.keyboard().down == SDLK_z) {
					mp3->play(2); // How many times play
				}

				if(window.keyboard().down == SDLK_x) {
					wav->play();
				}
				break;

			default:
				break;
		}


		renderer.triangle(texture, 100.0f, 100.0f, 100.0f, 50.0f, Color(0, 255, 0));
		renderer.rectangle(texture, 50.0f, 100.0f, 200.0f, 200.0f);

		renderer.triangle(550.0f, 350.0f, 100.0f, rotation);
		renderer.rectangle(500.0f, 370.0f, 200.0f, 200.0f, Color(0, 0, 255));

		// Don't worry about draw order with 2D, 2D shapes are always above 3D shapes
		renderer3d.pyramid(texture2, -1.0f, -1.0f, -7.0f, rotation, { 0, 255, 0 });
		renderer3d.cube(texture3, 1.0f, 1.0f, -8.0f, rotation, { 255, 255, 0 });


		// Update FPS each seconds
		unsigned int current_time = window.time();
		if(current_time - start_time >= 1000) {
			font->set_text("FPS: " + std::to_string(window.fps()));
			start_time = window.time();
		}
		renderer.draw_font(*font, 10.0f, 10.0f);

		rotation += 1.0f;
		if(rotation > 360.0f) {
			rotation = 0.0f;
		}


		window.swap();
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

If you don't set the color, the default color will be white

If you want to use **0 - 255** range, you can use a **Color** built-in method
```cpp
//                                   R    G   B   A
renderer.triangle(..., Color::from_rgba(255, 255, 0, 255));
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
// This is yellow
renderer.rectangle(100.0f, 300.0f, 50.0f, 50.0f, Color(1.0f, 1.0f, 0.0f));
```

![img_here]()

You can rotate, and draw the outline only
```cpp
//                  X       Y      WIDTH  HEIGHT ROTATE  OUTLINE
renderer.rectangle(100.0f, 100.0f, 50.0f, 50.0f, 180.0f, true);
```

<!--
## Custom colors
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



