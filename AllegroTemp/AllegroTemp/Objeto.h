#pragma once

class Objeto
{
protected:
	float x, y, w, h, vx, vy;
	ALLEGRO_BITMAP  *image;

public:

	Objeto(float x = width / 2, float y = height / 2, float w = 10, float h = 10,
		ALLEGRO_BITMAP *image = nullptr) :
		x(x), y(y), w(w), h(h), image(image) {
		vx = vy = 0;
	}

	virtual void update() { }
	virtual void move() { }

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
	ALLEGRO_BITMAP *getImage() {
		return image;
	}

	~Objeto() { }

};