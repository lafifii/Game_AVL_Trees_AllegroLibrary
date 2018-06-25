#pragma once

class Objeto
{
protected:
	float x, y, w, h, vx, vy;

public:

	Objeto(float x = width / 2, float y = height / 2, float w = 10, float h = 10) :
		x(x), y(y), w(w), h(h) {
		vx = vy = 0;
	}

	virtual void update() { }
	virtual void move() { }

	template<typename T>
	bool checkCollisionUp(T b) {


		if (x > b.getX() && x < b.getX() + b.getW() && x + w > b.getX() && x + w < b.getX() + b.getW() &&
			y < b.getY() + b.getH() && y > b.getY()) {
			return true;
		}
		if ((x > b.getX() && x < b.getX() + b.getW() &&
			y < b.getY() + b.getH() && y > b.getY()) ||
			(x + w > b.getX() && x + w < b.getX() + b.getW() &&
				y < b.getY() + b.getH() && y > b.getY())) {
			return true;
		}
		return false;
	}

	template<typename T>
	bool checkCollisionDown(T b) {


		if (x > b.getX() && x < b.getX() + b.getW() && x + w > b.getX() && x + w < b.getX() + b.getW() &&
			y + h > b.getY() && y + h < b.getY() + b.getH()) {
			return true;
		}
		if ((x > b.getX() && x < b.getX() + b.getW() &&
			y + h > b.getY() && y + h < b.getY() + b.getH()) ||
			(x + w > b.getX() && x + w < b.getX() + b.getW() &&
				y + h > b.getY() && y + h < b.getY() + b.getH())) {
			return true;
		}
		return false;
	}
	void setX(float _x) {
		x = _x;
	}
	void setY(float _y) {
		y = _y;
	}
	void setW(float _w) {
		w = _w;
	}
	void setH(float _h) {
		h = _h;
	}
	void setVX(float _v) {
		vx = _v;
	}
	void setVY(float _v) {
		vy = _v;
	}

	float getX() {
		return x;
	}
	float getY() {
		return y;
	}
	float getW() {
		return w;
	}
	float getH() {
		return h;
	}
	float getVX() {
		return vx;
	}
	float getVY() {
		return vy;
	}

	~Objeto() { }

};