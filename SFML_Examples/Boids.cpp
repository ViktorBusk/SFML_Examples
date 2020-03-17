#include "pch.h"
#include "utils.h"

using namespace sf;

int main()
{
	//Init random
	srand(time(NULL));

	//Init window
	VideoMode desktop = VideoMode().VideoMode::getFullscreenModes()[0];
	RenderWindow window(desktop, "Boids", Style::Fullscreen);
	window.setFramerateLimit(144);

	while (window.isOpen())
	{
		//Events
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (event.type == sf::Event::MouseWheelScrolled)
			{
				if (event.mouseWheelScroll.delta > 0)
					zoomViewAt({ event.mouseWheelScroll.x, event.mouseWheelScroll.y }, window, (1.f / 1.05));
				else if (event.mouseWheelScroll.delta < 0)
					zoomViewAt({ event.mouseWheelScroll.x, event.mouseWheelScroll.y }, window, 1.05);
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape))
			window.close();

		//Clear
		window.clear();
		//Draw
		window.display();
	}
	return 0;
}