//#include "Predator.h"
//
//using namespace sf;
//
//std::string round2D(float f);
//void zoomViewAt(sf::Vector2i pixel, sf::RenderWindow& window, float zoom);
//
//float distance(const Vector2f &obj1Pos, const Vector2f &obj2Pos)
//{
//	return sqrt(pow((obj1Pos.x - obj2Pos.x), 2) + pow((obj1Pos.y - obj2Pos.y), 2));
//}
//
//struct simMouse
//{
//	Vector2f pos = Vector2f(0, 0);
//	Vector2f startPoint = Vector2f(0, 0);
//	bool left = false;
//	bool right = false;
//	bool holding = false;
//	float radius = 1;
//	bool push = false;
//
//	void update(RenderWindow &window)
//	{
//		this->pos = Vector2f(window.mapPixelToCoords(Mouse::getPosition(window)));
//		this->left = Mouse::isButtonPressed(Mouse::Button::Left);
//		this->right = Mouse::isButtonPressed(Mouse::Button::Right);
//
//		if (this->right)
//		{
//			this->push = true;
//		}
//	}
//	template <typename T>
//	static bool rectColision(T obj, simMouse m)
//	{
//		if (obj.getPosition().x < m.pos.x + 1 &&
//			obj.getPosition().x + obj.getGlobalBounds().width > m.pos.x &&
//			obj.getPosition().y < m.pos.y + 1 &&
//			obj.getPosition().y + obj.getGlobalBounds().height > m.pos.y) {
//			return true;
//		}
//		else
//		{
//			return false;
//		}
//	}
//};
//
//class Slider
//{
//private:
//	Vector2f smallRectPos;
//	Vector2f bigRectPos;
//	Vector2f rect;
//	RectangleShape bigRect;
//	RectangleShape smallRect;
//	bool adjusting = false;
//	float *value;
//	float copyValue;
//	Vector2f interval;
//	std::string name;
//
//	Text text;
//
//public:
//	Slider(Vector2f pos, float *value, Vector2f interval, Font *font, std::string name)
//	{
//		this->smallRectPos = pos;
//		this->bigRectPos = pos;
//		this->rect = Vector2f(200, 20);
//		//Sliders
//		this->bigRect.setFillColor(Color(100, 100, 100));
//		this->smallRect.setFillColor(Color(200, 200, 200));
//
//		this->interval = interval;
//		this->value = value;
//		this->copyValue = *value;
//		//Text
//		this->text.setFont(*font);
//		this->text.setString(std::to_string(*this->value));
//		this->text.setCharacterSize(17);
//
//		this->name = name;
//	}
//	~Slider()
//	{
//
//	}
//
//	void draw(RenderWindow &window)
//	{
//		//Slider
//		this->bigRect.setPosition(Vector2f(window.mapPixelToCoords(Vector2i(this->bigRectPos))));
//		this->smallRect.setPosition(Vector2f(window.mapPixelToCoords(Vector2i(this->smallRectPos))));
//
//		Vector2f scaledRect = Vector2f(this->rect.x/window.getDefaultView().getSize().x * window.getView().getSize().x, 
//			this->rect.y / window.getDefaultView().getSize().y * window.getView().getSize().y);
//
//		this->bigRect.setSize(scaledRect);
//		this->smallRect.setSize(Vector2f(scaledRect.y, scaledRect.y));
//
//		window.draw(this->bigRect);
//		window.draw(this->smallRect);
//
//		//Text
//		this->text.setPosition(this->bigRect.getPosition());
//		this->text.setScale(window.getView().getSize().x / window.getDefaultView().getSize().x, window.getView().getSize().y / window.getDefaultView().getSize().y);
//		window.draw(this->text);
//	}
//
//	void update(simMouse m)
//	{
//		if (simMouse::rectColision(smallRect, m) && m.left && !adjusting)
//		{
//			adjusting = true;
//		}
//		if (adjusting)
//		{
//			this->smallRectPos.x = Mouse::getPosition().x - 15;
//			if (this->smallRectPos.x < this->bigRectPos.x) this->smallRectPos.x = this->bigRectPos.x;
//			if (this->smallRectPos.x + this->rect.y > this->bigRectPos.x + this->rect.x) this->smallRectPos.x = this->bigRectPos.x + this->rect.x - this->rect.y;
//		}
//		if (!m.left)
//		{
//			adjusting = false;
//		}
//
//		//Value
//		*this->value = (this->copyValue * ((this->smallRectPos.x - this->bigRectPos.x) / (this->rect.x - this->rect.y)));
//		this->text.setString(this->name /*+  + round2D(*this->value*200)*/);
//
//	}
//};
//
//int main()
//{
//	//Init random
//	srand(time(NULL));
//
//	//Init window
//	VideoMode desktop = VideoMode().VideoMode::getFullscreenModes()[0];
//	RenderWindow window(desktop, "Boids", Style::Fullscreen);
//	/*VideoMode mode = VideoMode(1000, 1000);
//	RenderWindow window(mode, "A* Pathfinding", Style::Default);*/
//	window.setFramerateLimit(144);
//
//	//Init font
//	Font font;
//	font.loadFromFile("Fonts/Prime-Regular.ttf");
//
//	//Mouse
//	simMouse m;
//
//	//Init Vectors
//	std::vector<Boid> boids;
//	std::vector<Predator> predators;
//	std::vector<Slider> sliders;
//	
//	//Spawn boids
//	for (size_t i = 0; i < 500; i++)
//	{
//		boids.push_back(Boid(Vector2f(rand() % window.getSize().x, rand() % window.getSize().y), Vector2f((-rand() % 10 + 5)/6, (-rand() % 10 + 5)/6)));
//	}
//
//	//Spawn predators
//	for (size_t i = 0; i < 5; i++)
//	{
//		predators.push_back(Predator(Vector2f(rand() % window.getSize().x, rand() % window.getSize().y), Vector2f((-rand() % 10 + 5) / 6, (-rand() % 10 + 5) / 6)));
//	}
//
//	//Sliders init
//	Slider f1(Vector2f(100.f, 100.f), &Boid::factor1, Vector2f(0.f, 0.f), &font, "Separation");
//	Slider f2(Vector2f(100.f, 150), &Boid::factor2, Vector2f(0.f, 0.f), &font, "Alignment");
//	Slider f3(Vector2f(100.f, 200.f), &Boid::factor3, Vector2f(0.f, 0.f), &font, "Cohesion");
//	Slider fr(Vector2f(100.f, 300.f), &Boid::perception, Vector2f(0.f, 0.f), &font, "Perception");
//	Slider fs(Vector2f(100.f, 350.f), &Boid::scared, Vector2f(0.f, 0.f), &font, "Danger");
//
//	sliders.push_back(f1);
//	sliders.push_back(f2);
//	sliders.push_back(f3);
//	sliders.push_back(fr);
//	sliders.push_back(fs);
//
//	for (auto &i : sliders)
//	{
//		i.update(m);
//	}
//
//	//Loop
//	while (window.isOpen())
//	{
//		//Events
//		Event event;
//		while (window.pollEvent(event))
//		{
//			if (event.type == Event::Closed)
//				window.close();
//			if (event.type == sf::Event::MouseWheelScrolled)
//			{	
//				if (event.mouseWheelScroll.delta > 0)
//					zoomViewAt({ event.mouseWheelScroll.x, event.mouseWheelScroll.y }, window, (1.f / 1.05));
//				else if (event.mouseWheelScroll.delta < 0)
//					zoomViewAt({ event.mouseWheelScroll.x, event.mouseWheelScroll.y }, window, 1.05);
//			}
//		}
//		if (Keyboard::isKeyPressed(Keyboard::Escape))
//			window.close();
//
//		//Clear
//		window.clear();
//
//		//Updating mouse commands
//		m.update(window);
//		if (m.push && !m.right)
//		{
//			boids.push_back(Boid(m.pos, Vector2f((-rand() % 10 + 5) / 3, (-rand() % 10 + 5) / 3)));
//			m.push = false;
//		}
//
//		for (auto &boid : boids)
//		{
//			boid.draw(window);
//			//Avoid predators
//			Vector2f c;
//			for (auto &predator : predators)
//			{
//				const float dist = distance(boid.getPos(), predator.getPos());
//				if (dist < Boid::perception) {
//					c = c - (predator.getPos() - boid.getPos());
//					c = Vector2f(c.x / dist, c.y / dist);
//				}
//			}
//			c = Vector2f(c.x*Boid::scared, c.y*Boid::scared);
//			
//			boid.addVel(c);
//			boid.update(boids);
//		}
//
//		for (auto &predator : predators)
//		{
//			predator.draw(window);
//			predator.update(boids);
//		}
//
//		for (auto &i : sliders)
//		{
//			i.draw(window);
//			i.update(m);
//		}
//
//		//Display
//		window.display();
//	}
//	return 0;
//}
//
//std::string round2D(float f)
//{
//	std::string s(16, '\0');
//	auto written = std::snprintf(&s[0], s.size(), "%.2f", f);
//	s.resize(written);
//	return s;
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