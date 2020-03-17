#pragma once
#include "utils.hpp"

//https://mikeash.com/pyblog/fluid-simulation-for-dummies.html

using namespace sf;

class FluidCube
{
private:
	int size;
	float dt;

	float *s;
	float *density;

	float *Vx;
	float *Vy;

	float *Vx0;
	float *Vy0;

	Text text;

public:
	static int const N = 200;
	static int const iter = 1;
	static int const SCALE = 5;
	static float r;
	static float g;
	float diff;
	float visc;

	static float b;

	FluidCube(float dt, int diffusion, int viscosity, Font *font);
	~FluidCube();

	//Accessors
	inline const float& getDens(int x, int y) const { return this->density[IX(x, y)]; }
	//Modifiers

	//Functions
	void initData(Font *font);
	void step();
	void showData(RenderWindow &window);
	void renderD(RenderWindow &window);

	static int IX(int x, int y);
	void addDensity(int x, int y, float amount);
	void addVelocity(int x, int y, float amountX, float amountY);
	
	static void diffuse(int b,  float *x, float *x0, float diff, float dt);
	static void lin_solve(int b, float *x, float *x0, float a, float c);
	static void project(float *velocX, float *velocY, float *p, float *div);
	static void advect(int b, float *d, float *d0, float *velocX, float *velocY, float dt);
	static void set_bnd(int b, float *x);
	
};
