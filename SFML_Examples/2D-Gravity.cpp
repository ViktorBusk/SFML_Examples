////SFML
//#include "SFML/System.hpp"
//#include "SFML/Graphics.hpp"
//#include "SFML/Window.hpp"
////#include "SFML/Audio.hpp"
////#include "SFML/Network.hpp"
////Others
//#include <iostream>
//#include <math.h>
//#include <cstdlib>
//#include <vector>
//#include <string>
//
//using namespace sf;
//
//float distance(const Vector2f &obj1Pos, const Vector2f &obj2Pos)
//{
//	return sqrt(pow((obj1Pos.x - obj2Pos.x), 2) + pow((obj1Pos.y - obj2Pos.y), 2));
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
//struct simMouse
//{
//	Vector2f pos = Vector2f(0, 0);
//	Vector2f startPoint = Vector2f(0, 0);
//	bool left = false;
//	bool right = false;
//	bool holding = false;
//	bool building = false;
//	float radius = 1;
//	bool push = false;
//
//	//BuildingInformation
//	Vector2f Bpos;
//	Vector2f Bvel;
//	float Bradius;
//	Color Bcolor;
//
//	void update(RenderWindow &window)
//	{
//		this->pos = Vector2f(window.mapPixelToCoords(Mouse::getPosition(window)));
//		this->left = Mouse::isButtonPressed(Mouse::Button::Left);;
//		this->right = Mouse::isButtonPressed(Mouse::Button::Right);
//
//		if (this->right)
//		{
//			this->radius = distance(this->startPoint, this->pos);
//			this->building = true;
//			CircleShape buildCircle(this->radius);
//			buildCircle.setOrigin(this->radius, this->radius);
//			buildCircle.setPosition(this->startPoint);
//			buildCircle.setFillColor(Color::White);
//			window.draw(buildCircle);
//		}
//		else
//		{
//			this->startPoint = this->pos;
//			if (this->building)
//			{
//				Bpos = this->startPoint;
//				Bvel = Vector2f(0.f, 0.f);
//				Bradius = this->radius + 1;
//				Bcolor = Color(rand() % 255, rand() % 255, rand() % 255);
//				this->push = true;
//				this->building = false;
//			}
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
//
//	Text text;
//
//public:
//	Slider(Vector2f pos, float *value, Vector2f interval, Font *font)
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
//		*this->value = this->copyValue * ((this->smallRectPos.x - this->bigRectPos.x + this->interval.x) / (this->rect.x - this->rect.y - this->interval.y));
//		this->text.setString(std::to_string(*this->value));
//
//	}
//};
//
//class Circle
//{
//	struct Statics
//	{
//		static float G;
//		static float friction;
//	};
//
//private:
//	bool chosen;
//
//protected:
//	CircleShape shape;
//	Vector2f vel;
//	Vector2f acc;
//	float mass;
//	float radius;
//
//	const Vector2f &gravity(Circle &other) {
//		if (distance(this->getPos(), other.getPos()) < (this->getRadius() + other.getRadius()) / 2)
//		{
//			return Vector2f(0.f, 0.f);
//		}
//		else
//		{
//			float netGForce = Circle::Statics::G * (this->mass * other.getMass()) / (pow(distance(this->getPos(), other.getPos()), 2));
//			float angle = atan2(other.getPos().y - this->getPos().y, other.getPos().x - this->getPos().x);
//
//			Vector2f GForceAcc(netGForce*cos(angle) / this->mass, netGForce*sin(angle) / this->mass);
//			return GForceAcc;
//		}
//	}
//
//	const bool &colision(Circle &other)
//	{
//		if (distance(this->getPos(), other.getPos()) < this->getRadius() + other.getRadius())
//		{
//			return true;
//		}
//		else
//		{
//			return false;
//		}
//	}
//
//	void bounce(Circle &other) {
//		float xVDiff = this->getVel().x - other.getVel().x;
//		float yVDiff = this->getVel().y - other.getVel().y;
//		float xDist = other.getPos().x - this->getPos().x;
//		float yDist = other.getPos().y - this->getPos().y;
//
//		if (xVDiff * xDist + yVDiff * yDist > 0 && colision(other))
//		{
//			float angle = -atan2(other.getPos().y - this->getPos().y, other.getPos().x - this->getPos().x);
//
//			Vector2f u1 = rotate(this->getVel(), angle);
//			Vector2f u2 = rotate(other.getVel(), angle);
//			float m1 = this->getMass();
//			float m2 = other.getMass();
//
//			Vector2f v1(u1.x * (m1 - m2) / (m1 + m2) + u2.x * 2 * m2 / (m1 + m2), u1.y);
//			Vector2f v2(u2.x * (m2 - m1) / (m1 + m2) + u1.x * 2 * m1 / (m1 + m2), u2.y);
//
//			Vector2f vFinal1 = rotate(v1, -angle);
//			Vector2f vFinal2 = rotate(v2, -angle);
//
//			this->setVel(Vector2f(vFinal1.x / Circle::Statics::friction, vFinal1.y / Circle::Statics::friction));
//			other.setVel(Vector2f(vFinal2.x / Circle::Statics::friction, vFinal2.y / Circle::Statics::friction));
//		}
//	}
//public:
//	Circle(Vector2f pos, Vector2f vel, float radius, Color color)
//	{
//		this->shape = CircleShape(radius, 20);
//		this->vel = vel;
//		this->acc = Vector2f(0.f, 0.f);
//		this->radius = radius;
//		this->mass = pow(radius, 3);
//		this->shape.setOrigin(radius, radius);
//		this->shape.setPosition(pos);
//		this->shape.setFillColor(color);
//		this->chosen = false;
//	}
//	~Circle() {
//
//	}
//
//	//Accessors
//	inline const Vector2f& getPos() const { return this->shape.getPosition(); }
//	inline const Vector2f& getVel() const { return this->vel; }
//	inline const Vector2f& getAcc() const { return this->acc; }
//	inline const float& getMass() const { return this->mass; }
//	inline const float& getRadius() const { return this->radius; }
//	inline const Color& getColor() const { return this->shape.getFillColor(); }
//
//	//Modifiers
//	void move(const Vector2f& vel) { this->shape.move(vel); }
//	void setPos(const Vector2f& pos) { this->shape.setPosition(pos); }
//	void setVel(const Vector2f& vel) { this->vel = vel; }
//	void setAcc(const Vector2f& acc) { this->acc = acc; }
//	void setMass(const float& mass) { this->mass = mass; }
//	void setColor(const Color& color) { this->shape.setFillColor(color); }
//
//	//Static functions
//	inline static float& getG() { return Circle::Statics::G; }
//	inline static float& getFriction() { return Circle::Statics::friction; }
//
//	static Vector2f rotate(const Vector2f &velocity, const float &angle)
//	{
//		Vector2f rotatedVelocities(velocity.x * cos(angle) - velocity.y * sin(angle), velocity.x * sin(angle) + velocity.y * cos(angle));
//		return rotatedVelocities;
//	}
//
//	//Dynamic functions
//	virtual void draw(RenderWindow &window) {
//
//		window.draw(this->shape);
//	}
//	virtual void update(std::vector<Circle> &objects, simMouse &m) {
//		if (distance(this->getPos(), m.pos) < this->getRadius() && m.left && !this->chosen && !m.holding)
//		{
//			this->chosen = true;
//			m.holding = true;
//		}
//
//		if (this->chosen && m.left)
//		{
//			this->setPos(m.pos);
//		}
//		else
//		{
//			this->chosen = false;
//			m.holding = false;
//		}
//
//		for (auto &object : objects)
//		{
//			if (&object == this) continue;
//			this->acc = this->gravity(object);
//			this->vel += this->acc;
//			this->bounce(object);
//		}
//		this->shape.move(this->vel);
//		this->acc = Vector2f(0.f, 0.f);
//	}
//};
//
//class Bullet
//{
//private:
//	Sprite shape;
//	Texture *texture;
//	Vector2f velocity;
//	bool usable;
//	unsigned int dmg;
//	CircleShape hitbox;
//
//public:
//	Bullet(Texture *texture, const Vector2f &startPos, const Vector2f &velocity, const float &rotation)
//	{
//		this->texture = texture;
//		this->shape.setTexture(*texture);
//		this->velocity = velocity;
//		this->shape.setScale(0.25f, 0.25f);
//		this->shape.setOrigin(this->shape.getLocalBounds().width / 2, this->shape.getLocalBounds().height / 2);
//		this->shape.setPosition(startPos);
//		this->usable = true;
//		this->dmg = 1;
//
//		//Rotate with angle;
//		this->hitbox = CircleShape(this->shape.getGlobalBounds().width / 2, 20);
//		this->hitbox.setPosition(this->shape.getPosition());
//		this->shape.setRotation(rotation);
//
//		//Hitbox
//		this->hitbox.setOrigin(this->hitbox.getGlobalBounds().width / 2.f, this->hitbox.getGlobalBounds().width / 2.f);
//
//	}
//
//	//Accessors
//	inline const bool& getUsable() const { return this->usable; }
//	inline const Sprite& getShape() const { return this->shape; }
//	inline const int& getDmg() const { return this->dmg; }
//
//	//Modifiers
//	void setUsable(const bool &usable) { this->usable = usable; }
//
//	//Functions
//	void draw(RenderWindow &window)
//	{
//		//window.draw(this->hitbox);
//		window.draw(this->shape);
//	}
//
//	void update(const RenderWindow& window)
//	{
//		this->shape.move(this->velocity);
//		this->hitbox.setPosition(this->shape.getPosition());
//
//	}
//};
//
//class Player : public Circle
//{
//private:
//	
//protected:
//	Text UIText;
//	Texture *bulletTexture;
//	unsigned int CD;
//	unsigned int incer;
//	float PI;
//	float angle;
//	Sprite sprite;
//	Texture *texture;
//	Vector2f shipAcc;
//	float shipAccD;
//
//public:
//	//Constructors
//	Player(Texture *texture, const Vector2f &startPos, Font *font, Texture *bulletTexture) :
//		Circle(startPos, Vector2f(0.f, 0.f), 25, Color(255, 255, 255))
//	{
//		//Ship
//		this->texture = texture;
//		this->sprite.setTexture(*texture);
//		this->sprite.setScale(0.15f, 0.15f);
//		this->sprite.setPosition(startPos);
//		this->sprite.setOrigin(this->sprite.getLocalBounds().width / 2.f, this->sprite.getLocalBounds().height / 2.f);
//
//		//Movement
//		shipAccD = 0.001f;
//
//		//UI
//		this->UIText.setFont(*font);
//		this->UIText.setCharacterSize(23);
//
//		//Bullets
//		this->bulletTexture = bulletTexture;
//		this->CD = 20;
//		this->incer = 0;
//		this->PI = 3.14159265;
//	}
//	//Destructor
//	virtual ~Player() {}
//	//Accessors
//	inline const Sprite& getShape() const { return this->sprite; }
//	inline const Texture& getTexture() const { return *this->texture; }
//
//	//Modifiers
//
//	//Functions
//	virtual void drawUI(RenderWindow &window)
//	{	
//		this->UIText.setScale(window.getView().getSize().x / window.getDefaultView().getSize().x, window.getView().getSize().y / window.getDefaultView().getSize().y);
//		//Vel
//		this->UIText.setPosition(Vector2f(window.mapPixelToCoords(Vector2i(window.getDefaultView().getSize().x - 250, window.getDefaultView().getSize().y - 150))));
//		this->UIText.setString("Vel: (" + round2D(this->vel.x) + "  " + round2D(this->vel.y) + ")");
//		window.draw(this->UIText);
//		 
//		//Acc
//		this->UIText.setPosition(Vector2f(window.mapPixelToCoords(Vector2i(window.getDefaultView().getSize().x - 250, window.getDefaultView().getSize().y - 200))));
//
//		this->UIText.setString("Acc: (" + round2D(this->shipAcc.x * 100) + ", " + round2D(this->shipAcc.y * 100) + ")");
//		window.draw(this->UIText);
//	}
//
//	virtual void draw(RenderWindow &window) {
//		//window.draw(this->shape);
//		window.draw(this->sprite);
//		this->drawUI(window);
//	}
//
//	virtual void update(std::vector<Circle> &objects, simMouse &m, std::vector<Bullet> &bulletVec)
//	{
//		this->incer++;
//		this->angle = this->sprite.getRotation() * PI / 180 - PI / 2;
//
//		//Input
//		if (Keyboard::isKeyPressed(Keyboard::W))
//			this->move("UP");
//		if (Keyboard::isKeyPressed(Keyboard::S))
//			this->move("DOWN");
//		if (Keyboard::isKeyPressed(Keyboard::A))
//			this->move("LEFT");
//		if (Keyboard::isKeyPressed(Keyboard::D))
//			this->move("RIGHT");
//		if (Keyboard::isKeyPressed(Keyboard::Space))
//			this->shoot(bulletVec);
//
//		for (auto &object : objects)
//		{
//			if (&object == this) continue;
//			this->acc = this->gravity(object);
//			this->vel += this->acc;
//			this->bounce(object);
//		}
//		this->vel += this->shipAcc;
//		this->shape.move(this->vel);
//		
//		this->acc = Vector2f(0.f, 0.f);
//		this->shipAcc = Vector2f(shipAcc.x/1.1, shipAcc.y/1.1);
//		
//		this->sprite.setPosition(this->shape.getPosition());
//
//		//Rotate ship
//		float dx = this->shipAcc.x*INT_MAX - this->sprite.getPosition().x;
//		float dy = this->shipAcc.y*INT_MAX - this->sprite.getPosition().y;
//
//		float rotation = (atan2(dy, dx)) * 180 / PI + 90;
//		if(abs(this->shipAcc.x) > 0.001f || abs(this->shipAcc.y) > 0.001f)
//			this->sprite.setRotation(rotation);
//	}
//
//	void shoot(std::vector<Bullet> &bulletVec)
//	{
//		if (this->incer >= this->CD)
//		{
//			bulletVec.push_back(Bullet(this->bulletTexture, Vector2f(this->getPos().x + 2*this->radius*cos(angle), this->getPos().y + 2*this->radius*sin(angle)), Vector2f(cos(angle) * 5, sin(angle) * 5), this->sprite.getRotation()));
//			this->incer = 0;
//		}
//	}
//
//	void move(std::string direction)
//	{
//		if (direction == "UP")
//			if (this->shipAcc.y < -10* shipAccD) return;
//			else this->shipAcc += Vector2f(0.f, -shipAccD);
//		if (direction == "DOWN")
//			if (this->shipAcc.y > 10 * shipAccD) return;
//			else this->shipAcc += Vector2f(0.f, shipAccD);
//		if (direction == "LEFT")
//			if (this->shipAcc.x < -10 * shipAccD) return;
//			else this->shipAcc += Vector2f(-shipAccD, 0);
//		if (direction == "RIGHT")
//			if (this->shipAcc.x > 10 * shipAccD) return;
//			else this->shipAcc += Vector2f(shipAccD, 0.f);
//	}
//};
//
//class Enemy : public Player
//{
//private:
//
//public:
//	Enemy(Texture *texture, const Vector2f &startPos, Font *font, Texture *bulletTexture) :
//		Player(texture, startPos, font, bulletTexture)
//	{
//		this->CD *= 10;
//		this->shipAccD *= 5;
//		this->incer = rand() % this->CD;
//	}
//
//	void draw(RenderWindow &window) {
//		//window.draw(this->shape);
//		window.draw(this->sprite);
//	}
//
//	void update(std::vector<Circle> &objects, simMouse &m, std::vector<Bullet> &bulletVec, Player &player)
//	{
//		this->incer++;
//		this->angle = this->sprite.getRotation() * PI / 180 - 3*PI / 2;
//		shoot(bulletVec);
//
//		for (auto &object : objects)
//		{
//			if (&object == this) continue;
//			this->acc = this->gravity(object);
//			this->vel += this->acc;
//			this->bounce(object);
//		}
//		this->vel += this->shipAcc;
//		this->shape.move(this->vel);
//
//		this->acc = Vector2f(0.f, 0.f);
//		this->shipAcc = Vector2f(shipAcc.x / 1.1, shipAcc.y / 1.1);
//
//		this->sprite.setPosition(this->shape.getPosition());
//
//		//Move
//		float dx = player.getPos().x - this->sprite.getPosition().x;
//		float dy = player.getPos().y - this->sprite.getPosition().y;
//
//		float rotation = (atan2(dy, dx));
//		
//		this->shipAcc = Vector2f(cos(rotation)*shipAccD, sin(rotation)*shipAccD);
//
//		//Rotate ship
//		dx = this->shipAcc.x*INT_MAX - this->sprite.getPosition().x;
//		dy = this->shipAcc.y*INT_MAX - this->sprite.getPosition().y;
//
//		rotation = (atan2(dy, dx)) * 180 / PI - 90;
//		if (abs(this->shipAcc.x) > 0.001f || abs(this->shipAcc.y) > 0.001f)
//			this->sprite.setRotation(rotation);
//
//	}
//};
//
//float Circle::Statics::G = 0.001f;
//float Circle::Statics::friction = 1.f;
//
////Zoom
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
//int main()
//{
//	//Init random
//	srand(time(NULL));
//
//	//Init window
//	VideoMode desktop = VideoMode().VideoMode::getFullscreenModes()[0];
//	RenderWindow window(desktop, "G-Simulation", Style::Fullscreen);
//	window.setFramerateLimit(144);
//
//	//Init font
//	Font font;
//	font.loadFromFile("Fonts/Prime-Regular.ttf");
//
//	//Vector init
//	std::vector<Circle> objects;
//	std::vector<Bullet> bullets;
//	std::vector<Slider> sliders;
//	std::vector<Enemy> enemies;
//
//	//Init textures
//	Texture playerTex;
//	playerTex.loadFromFile("Textures/ship.png");
//
//	Texture enemyTex;
//	enemyTex.loadFromFile("Textures/enemy.png");
//
//	Texture bulletTex;
//	bulletTex.loadFromFile("Textures/beam.png");
//
//	Texture enemyBulletTex;
//	enemyBulletTex.loadFromFile("Textures/enemyBeam.png");
//
//	//Player init
//	Player player(&playerTex, Vector2f(window.getSize().x / 2.f, window.getSize().y / 2.f), &font, &bulletTex);
//
//	//Sliders init
//	Slider gSlider(Vector2f(100.f, 100.f), &Circle::getG(), Vector2f(-10.f, Circle::getG()), &font);
//	Slider fSlider(Vector2f(100.f, 150.f), &Circle::getFriction(), Vector2f(150.f, Circle::getFriction()*10), &font);
//	sliders.push_back(gSlider);
//	sliders.push_back(fSlider);
//
//	//Init simulation
//	simMouse m;
//	for (size_t i = 0; i < 20; i++)
//	{
//		Vector2f pos(rand() % window.getSize().x, rand() % window.getSize().y);
//		float radius = rand() % 50 + 1;
//		objects.push_back(Circle(pos, Vector2f(0.f, 0.f), radius, Color(rand() % 255, rand() % 255, rand() % 255)));
//	}
//
//	//Enemies inint
//	for (size_t i = 0; i < 5; i++)
//	{
//		Vector2f pos(rand() % window.getSize().x, rand() % window.getSize().y);
//		enemies.push_back(Enemy(&enemyTex, pos, &font, &enemyBulletTex));
//	}
//
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
//		//Draw
//		window.clear();
//		
//		//Updating mouse commands
//		m.update(window);
//		if (m.push)
//		{
//			Circle test = Circle(m.Bpos, m.Bvel, m.Bradius, m.Bcolor);
//			objects.push_back(test);
//			m.push = false;
//		}
//
//		//Updating objects
//		for (size_t i = 0; i < bullets.size(); i++)
//		{
//			bullets[i].draw(window);
//			bullets[i].update(window);
//			if (!bullets[i].getUsable())
//			{
//				bullets.erase(bullets.begin() + i);
//			}
//		}
//
//		for (auto &i : objects)
//		{
//			i.draw(window);
//			i.update(objects, m);
//		}
//		
//		for (auto &i : enemies)
//		{
//			i.draw(window);
//			i.update(objects, m, bullets, player);
//		}
//
//		player.draw(window);
//		player.update(objects, m, bullets);
//
//
//		for (auto &i : sliders)
//		{
//			i.draw(window);
//			i.update(m);
//		}
//
//		window.display();
//	}
//
//	return 0;
//}