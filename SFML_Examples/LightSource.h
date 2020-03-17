#include "utils.hpp"
#define WINDOWSIZE Vector2i(800, 800)

using namespace sf;

class LightSource
{
private:
	CircleShape shape;
	static Texture texture;
	Sprite sprite;
	bool follow = false;
	float radius;
	float lightAngle;
	float moveAngle;
	Vector2f spawnPos;
	
	//Mouse
	static Vector2f mousePos;
	static bool holding;

	struct Ray {
		Vector2f sourcePoint;
		Vector2f interSectPoint;
		float radius = INT_MAX;
		float angle;
		Ray(Vector2f SP, float A)
		{
			this->sourcePoint = SP;
			this->angle = A;
		};
		bool getLineIntersection(float p0_x, float p0_y, float p1_x, float p1_y,
			float p2_x, float p2_y, float p3_x, float p3_y, float *i_x, float *i_y);
		void findClosestIntersectPoint(std::vector<Shape*>& polygons);
	};
	std::vector<LightSource::Ray> rays;

public:
	LightSource();
	~LightSource();
	
	void draw(RenderWindow * window, std::vector<Shape*> &polygons);
	void update(const float &dt);
};

