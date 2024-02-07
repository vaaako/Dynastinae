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
	Triangle rectangle(100.0f, 200.0f, 50.0f, Color { 1.0f, 1.0f, 0.0f }); // RGB
	Rectangle rectangle(100.0f, 200.0f, 50.0f, 50.0f, Color { 0.5f, 1.0f, 0.5f }); // RGB

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

		// Draw triangles
		triangle.draw();

		// Swap buffers
		window.swap();
	}
}

```

# Shapes and Colors
Você pode usar a struct `Color` para colorir com uma flat color usando RGB no range de
 **0 - 1**, ou então usar um vector para colorir cada canto com uma cor separada, criando
 um efeito gradiente


```cpp
// Default color is white
Rectangle triangle(100, 100, 50.0f, 50.0f);

// Flat color
// WARNING: Need to explicitaly indicate is a color vector
Rectangle triangle(100, 100, 50.0f, 50.0f, Color { 1.0f, 1.0f, 0.0f }); // RGB / Alpha is optional

// Corners color
Rectangle triangle(100, 100, 50.0f, 50.0f
	//  R     G     B     A
	{
		1.0f, 0.0f, 0.0f, 1.0f // Top Right
		0.0f, 1.0f, 0.0f, 1.0f // Bottom Right
		0.0f, 0.0f, 1.0f, 1.0f // Bottom Left
		1.0f, 1.0f, 1.0f, 1.0f // Top Left
	}
);


// Triangle

// Default color
Triangle triangle(100, 100, 50.0f);

// Flat color
Triangle triangle(100, 100, 50.0f, Color { 1.0f, 1.0f, 0.0f }); // RGB / Alpha is optional

// Corners color
Triangle triangle(100, 100, 50.0f,
	//  R     G     B     A
	{
		1.0f, 0.0f, 0.0f, 1.0f // Bottom Right
		0.0f, 1.0f, 0.0f, 1.0f // Bottom Left
		0.0f, 0.0f, 1.0f, 1.0f // Top
	}
);
```

A struct `Color` também aceita **opacity** como parâmetro

**e.g.:** `Color { 1.0f, 0.0f, 0.0f, 1.0f }`A
