//#include "FluidCube.h"
//
//struct simMouse
//{
//	Vector2f pos = Vector2f(0, 0);
//	Vector2f pPos = pos;
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
//		this->left = Mouse::isButtonPressed(Mouse::Button::Left);;
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
//	RectangleShape bigRect;
//	RectangleShape smallRect;
//	bool adjusting = false;
//	bool showVal;
//	float *value;
//	float copyValue;
//	Vector2f interval;
//	std::string name;
//	Text text;
//
//public:
//	static Vector2f rect;
//	Slider(Vector2f pos, float *value, Vector2f interval, Font *font, std::string name, bool showVal)
//	{
//		this->smallRectPos = pos;
//		this->bigRectPos = pos;
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
//		this->text.setCharacterSize(15);
//
//		this->name = name;
//		this->showVal = showVal;
//	}
//	~Slider()
//	{
//
//	}
//
//	std::string round2D(float f)
//	{
//		std::string s(16, '\0');
//		auto written = std::snprintf(&s[0], s.size(), "%.2f", f);
//		s.resize(written);
//		return s;
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
//		this->text.setPosition(this->bigRect.getPosition().x, this->bigRect.getPosition().y - 20 * (window.getView().getSize().x)/window.getDefaultView().getSize().x);
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
//			this->smallRectPos.x = m.pos.x - 5;
//			if (this->smallRectPos.x < this->bigRectPos.x) this->smallRectPos.x = this->bigRectPos.x;
//			if (this->smallRectPos.x + this->rect.y > this->bigRectPos.x + this->rect.x) this->smallRectPos.x = this->bigRectPos.x + this->rect.x - this->rect.y;
//		}
//		if (!m.left)
//		{
//			adjusting = false;
//		}
//
//		//Value
//		*this->value = (this->copyValue * ((this->smallRectPos.x - this->bigRectPos.x) / (this->rect.x - this->rect.y)))/100000;
//		if (this->showVal)
//		{
//			this->text.setString(this->name + ": " + std::to_string(int(*this->value)));
//		}
//		else
//		{
//			this->text.setString(this->name);
//		}
//	}
//};
//
//Vector2f Slider::rect = Vector2f(50, 10);
//
//void zoomViewAt(sf::Vector2i pixel, sf::RenderWindow& window, float zoom);
//
//void draw(RenderWindow &window, FluidCube &fluid, float &angle) {
//	int cx = int(0.5*window.getDefaultView().getSize().x / FluidCube::SCALE);
//	int cy = int(0.5*window.getDefaultView().getSize().y / FluidCube::SCALE);
//	for (int i = -1; i <= 1; i++) {
//		for (int j = -1; j <= 1; j++) {
//			fluid.addDensity(cx + i, cy + j, rand() % 50);
//		}
//	}
//	for (int i = 0; i < 6; i++) {
//		angle += rand()*100;
//		float factor = 10;
//		float vx = factor*cos(angle);
//		float vy = factor*sin(angle);
//		fluid.addVelocity(cx, cy, vx, vy);
//	}
//}
//
//int main()
//{
//	//Init random
//	srand(time(NULL));
//
//	//Init window
//	VideoMode mode = VideoMode(FluidCube::N*FluidCube::SCALE, FluidCube::N*FluidCube::SCALE);
//	RenderWindow window(mode, "Fluid Simulation", Style::Default);
//	window.setFramerateLimit(144);
//
//	//Init font
//	Font font;
//	font.loadFromFile("Fonts/Prime-Regular.ttf");
//
//	//Mouse
//	simMouse m;
//
//	//Init simulation
//	FluidCube fluid(0.1, 1, 10, &font);
//	float angle = 0;
//	std::vector<Slider> sliders;
//	
//	//Sliders init
//	Slider r(Vector2f(1*FluidCube::N*FluidCube::SCALE/5 - 90, FluidCube::N*FluidCube::SCALE - 50), &FluidCube::r, Vector2f(0.f, 0.f), &font, "RED", true);
//	Slider g(Vector2f(2*FluidCube::N*FluidCube::SCALE/5 - 90, FluidCube::N*FluidCube::SCALE - 50), &FluidCube::g, Vector2f(0.f, 0.f), &font, "GREEN", true);
//	Slider b(Vector2f(3*FluidCube::N*FluidCube::SCALE/5 - 90, FluidCube::N*FluidCube::SCALE - 50), &FluidCube::b, Vector2f(0.f, 0.f), &font, "BLUE", true);
//
//	Slider diff(Vector2f(4*FluidCube::N*FluidCube::SCALE/5 - 90, FluidCube::N*FluidCube::SCALE - 50), &fluid.diff, Vector2f(0.f, 0.f), &font, "DIFF", false);
//	Slider visc(Vector2f(5*FluidCube::N*FluidCube::SCALE/5 - 90, FluidCube::N*FluidCube::SCALE - 50), &fluid.visc, Vector2f(0.f, 0.f), &font, "VISC", false);
//
//	sliders.push_back(r);
//	sliders.push_back(g);
//	sliders.push_back(b);
//	sliders.push_back(diff);
//	sliders.push_back(visc);
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
//			/*if (event.type == sf::Event::MouseWheelScrolled)
//			{	
//				if (event.mouseWheelScroll.delta > 0)
//					zoomViewAt({ event.mouseWheelScroll.x, event.mouseWheelScroll.y }, window, (1.f / 1.1));
//				else if (event.mouseWheelScroll.delta < 0)
//					zoomViewAt({ event.mouseWheelScroll.x, event.mouseWheelScroll.y }, window, 1.1);
//			}*/
//		}
//		if (Keyboard::isKeyPressed(Keyboard::Escape))
//			window.close();
//
//		//Clear
//		window.clear();
//
//		//Updating mouse commands
//		m.update(window);
//		if (m.right)
//		{
//			fluid.addDensity(m.pos.x / FluidCube::SCALE, m.pos.y / FluidCube::SCALE, 100);
//			Vector2f amt = m.pos - m.pPos;
//			fluid.addVelocity(m.pos.x / FluidCube::SCALE, m.pos.y / FluidCube::SCALE, amt.x/2, amt.y/2);
//		}
//
//		//Draw
//		//draw(window, fluid, angle);
//
//		fluid.step();
//		fluid.renderD(window);
//
//		for (auto &i : sliders)
//		{
//			i.draw(window);
//			i.update(m);
//		}
//
//		//Display
//		window.display();
//
//		m.pPos = m.pos;
//	}
//}
//
//void zoomViewAt(sf::Vector2i pixel, sf::RenderWindow& window, float zoom)
//{
//	View view{ window.getView() };
//	if (zoom > 1 && view.getSize().x >= window.getDefaultView().getSize().x)
//	{
//		window.setView(window.getDefaultView());
//	}
//	else
//	{
//		view.zoom(zoom);
//	}
//	window.setView(view);
//}