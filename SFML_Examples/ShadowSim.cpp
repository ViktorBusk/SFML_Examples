//#include "utils.hpp"
//#include "LightSource.h"
//
//using namespace sf;
//
//
//void initPolygons(std::vector<Shape*> &polygons)
//{
//	ConvexShape *polygon1 = new ConvexShape;
//	polygon1->setPointCount(3);
//	polygon1->setPoint(0, sf::Vector2f(0, 0));
//	polygon1->setPoint(1, sf::Vector2f(0, 50));
//	polygon1->setPoint(2, sf::Vector2f(100, 50));
//	polygon1->setFillColor(Color::Blue);
//	polygon1->setPosition(100, 200);
//	polygons.push_back(polygon1);
//
//	RectangleShape *polygon2 = new RectangleShape;
//	polygon2->setPosition(200, 300);
//	polygon2->setSize(Vector2f(50.f, 50.f));
//	polygon2->setFillColor(Color::Blue);
//	polygons.push_back(polygon2);
//
//	ConvexShape *polygon3 = new ConvexShape;
//	polygon3->setPointCount(5);
//	polygon3->setPoint(0, sf::Vector2f(0, 0));
//	polygon3->setPoint(1, sf::Vector2f(-25, 25));
//	polygon3->setPoint(2, sf::Vector2f(0, 50));
//	polygon3->setPoint(3, sf::Vector2f(25, 50));
//	polygon3->setPoint(4, sf::Vector2f(50, 25));
//	polygon3->setFillColor(Color::Blue);
//	polygon3->setPosition(400, 600);
//	polygons.push_back(polygon3);
//
//	CircleShape *polygon4 = new CircleShape;
//	polygon4->setPointCount(8);
//	polygon4->setFillColor(Color::Blue);
//	polygon4->setRadius(25.f);
//	polygon4->setPosition(500, 500);
//	polygons.push_back(polygon4);
//
//	for (size_t i = 0; i < 25; i++)
//	{
//		CircleShape *random = new CircleShape;
//		random->setPointCount(rand() % 3 + 3);
//		random->setRadius(rand() % 50);
//		random->setFillColor(Color::Cyan);
//		random->setPosition(rand() % WINDOWSIZE.x, rand() % WINDOWSIZE.y);
//		polygons.push_back(random);
//	}
//}
//void initBorder(RenderWindow* window, std::vector<Shape*> &polygons)
//{
//	RectangleShape *topRect = new RectangleShape(Vector2f(window->getSize().x, 5));
//	topRect->setPosition(Vector2f(0.f, 0.f));
//	polygons.push_back(topRect);
//
//	RectangleShape *leftRect = new RectangleShape(Vector2f(5, window->getSize().y));
//	leftRect->setPosition(Vector2f(0.f, 0.f));
//	polygons.push_back(leftRect);
//
//	RectangleShape *bottomRect = new RectangleShape(Vector2f(window->getSize().x, -5));
//	bottomRect->setPosition(Vector2f(0.f, window->getSize().y));
//	polygons.push_back(bottomRect);
//
//	RectangleShape *rightRect = new RectangleShape(Vector2f(-5, window->getSize().y));
//	rightRect->setPosition(Vector2f(window->getSize().x, 0.f));
//	polygons.push_back(rightRect);
//}
//void initLightSources(std::vector<LightSource*> &lightSources)
//{
//	lightSources.push_back(new LightSource);
//	lightSources.push_back(new LightSource);
//}
//
//void zoomViewAt(sf::Vector2i pixel, sf::RenderWindow& window, float zoom)
//{
//	const sf::Vector2f beforeCoord{ window.mapPixelToCoords(pixel) };
//	sf::View view{ window.getView() };
//	view.zoom(zoom);
//	window.setView(view);
//	const sf::Vector2f afterCoord{ window.mapPixelToCoords(pixel) };
//	const sf::Vector2f offsetCoords{ beforeCoord - afterCoord };
//	view.move(offsetCoords);
//	window.setView(view);
//}
//
//void updateEvents(RenderWindow& window, Event &event)
//{
//	while (window.pollEvent(event))
//	{
//		if (event.type == Event::Closed)
//			window.close();
//		if (event.type == sf::Event::MouseWheelScrolled)
//		{
//			if (event.mouseWheelScroll.delta > 0)
//				zoomViewAt({ event.mouseWheelScroll.x, event.mouseWheelScroll.y }, window, (1.f / 1.05));
//			else if (event.mouseWheelScroll.delta < 0)
//				zoomViewAt({ event.mouseWheelScroll.x, event.mouseWheelScroll.y }, window, 1.05);
//		}
//	}
//	if (Keyboard::isKeyPressed(Keyboard::Escape))
//		window.close();
//}
//
//int main()
//{
//	//Init random
//	srand(time(NULL));
//
//	//Init clock
//	Clock clock;
//	float dt = 0;
//
//	//Init window
//	VideoMode mode = VideoMode(WINDOWSIZE.x, WINDOWSIZE.y);
//	RenderWindow window(mode, "Raycast", Style::Default);
//	window.setFramerateLimit(144);
//
//	//Init font
//	Font font;
//	font.loadFromFile("Fonts/Prime-Regular.ttf");
//
//	//Init polygons and lightsources
//	std::vector<Shape*> polygons;
//	std::vector<LightSource*> lightSources;
//
//	initBorder(&window, polygons);
//	initPolygons(polygons);
//	initLightSources(lightSources);
//
//	while (window.isOpen())
//	{
//		dt = clock.restart().asSeconds();
//		Event event;
//		updateEvents(window, event);
//
//		//Drawing
//		window.clear();
//
//		//Draw
//		for (Shape *shape : polygons)
//		{
//			window.draw(*shape);
//		}
//		for (LightSource *source : lightSources)
//		{
//			source->draw(&window, polygons);
//			source->update(dt);
//		}
//
//		window.display();
//	}
//
//	for (Shape *shape : polygons)
//	{
//		delete shape;
//	}
//	polygons.clear();
//	for (LightSource *source : lightSources)
//	{
//		delete source;
//	}
//	lightSources.clear();
//}