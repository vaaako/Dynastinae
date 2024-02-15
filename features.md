# Not complete yet, just for I don't forget


# Template
```cpp
void process_keyboard(Window& window, Keyboard keyboard) {
	if(keyboard.down == 27) {
		std::cout << "Closing" << std::endl;
		window.close();
	}
}

int main() {
	// Create main window
	Window window = Window("Hello Knuppel", 800, 600, true);

	// Create 2D shapes to draw
	Triangle rectangle(100.0f, 250.0f, 200.0f, Color { 1.0f, 1.0f, 0.0f });
	Rectangle rectangle(100.0f, 100.0f, 300.0f, 300.0f, Color { 0.5f, 1.0f, 0.5f });

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
		rectangle.draw();
		triangle.draw();

		// Swap buffers
		window.swap();
	}
}
```


![img_here]()


# Shapes and Colors
You can use the `Color` struct to color with a flat color using **RGBA** in the range of **0 - 1**.

The `Color` struct also has an **alpha** optional parameter.

```cpp
//        R     G     B     A
Color { 1.0f, 0.0f, 0.0f, 1.0f }`
```

If you want to use **0 - 255** range, you can use a **Color** built-in method
```
//                                                            R    G   B   A
Rectangle rectangle(100, 100, 50.0f, 50.0f, Color::from_rgba(255, 255, 0, 255));
```

The **alpha** parameter is optional


## Examples
```cpp
// Default color is white
Rectangle rectangle(100.0f, 100.0f, 50.0f, 50.0f);

// Flat color
// WARNING: Need to explicitaly indicate is a color vector
Rectangle rectangle(100.0f, 100.0f, 200.0f, 200.0f, Color { 1.0f, 1.0f, 0.0f }); // RGB / Alpha is optional
```

The following are equivalent to the ones above
```cpp
Rectangle rectangle = Rectangle(100.0f, 100.0f, 50.0f, 50.0f);
Rectangle rectangle = Rectangle(100.0f, 100.0f, 50.0f, 50.0f, Color( 1.0f, 1.0f, 0.0f ));
Rectangle rectangle = Rectangle(100.0f, 100.0f, 50.0f, 50.0f, Color::from_rgba( 255.0f, 255.0f, 255.0f ));
```


![img_here]()


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


You can do the same for **Triangle**
```cpp
// TRIANGLE //

// Default color
Triangle triangle(100.0f, 100.0f, 200.0f);

// Flat color
Triangle triangle(100.0f, 100.0f, 200.0f, Color { 1.0f, 1.0f, 0.0f, 1.0f }); // RGB / Alpha is optional

// Corners color
Triangle triangle(100, 100, 50.0f,
	{
		// R    G     B     A
		1.0f, 0.0f, 0.0f, 1.0f // Bottom Right
		0.0f, 1.0f, 0.0f, 1.0f // Bottom Left
		0.0f, 0.0f, 1.0f, 1.0f // Top
	}
);
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
rectangle.bind_texture(texture);
```
>This is the same for any other shape


![img_here]()


You can also bind to a colorized shape, this will create a filter on the texture
```cpp
Rectangle rectangle(100.0f, 100.0f, 200.0f, 200.0f
	{
		// R     G     B     A
		1.0f, 0.0f, 0.0f, 1.0f // Top Right
		0.0f, 1.0f, 0.0f, 1.0f // Bottom Right
		0.0f, 0.0f, 1.0f, 1.0f // Bottom Left
		1.0f, 1.0f, 1.0f, 1.0f // Top Left
	}
);


// Rainbow texture
rectangle.bind_texture(texture);
```


![img_here]()
