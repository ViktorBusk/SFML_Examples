//#include "Node.h"
//#include "Grid.h"
//
//using namespace sf;
//
//int main()
//{
//	//Init random
//	srand(time(NULL));
//
//	//Init constants
//	const Vector2i windowSize(800, 800);
//	const Vector2i worldSize(800, 800);
//	const Vector2i dimensions(100, 100);
//
//	//Init window
//	VideoMode mode = VideoMode(windowSize.x, windowSize.y);
//	RenderWindow window(mode, "A* Pathfinding", Style::Default);
//	window.setFramerateLimit(144);
//
//	//Init font
//	Font font;
//	font.loadFromFile("Fonts/Prime-Regular.ttf");
//
//	//Mouse
//	Grid::mouse m;
//
//	//Init grid
//	Grid grid(window, worldSize, dimensions);
//
//	//Loop
//	grid.AStarFibb(true, &window);
//
//	while (window.isOpen())
//	{
//		window.clear();
//		Grid::pollEvents(window);
//		//Updating mouse commands
//		m.update(window);
//		//Draw
//		grid.draw(window);
//		
//		window.display();
//		
//		m.pPos = m.pos;
//	}
//}