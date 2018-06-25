#pragma once

class CEnemy
{
	float x, y, w, h, vx, vy;
	int danger,val;
public:

	CEnemy(float x = width / 2, float y = height / 2, float w = 10, float h = 10) :
		x(x), y(y), w(w), h(h) {
		vx = 0;
		vy = 2;
		danger = 100;
		val= rand() % 43;
	}

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
	template <class T>
	void update(ALLEGRO_BITMAP *a, ALLEGRO_BITMAP *b, vector<T> vec)
	{
		move(vec);
		if(val%2==0)
			al_draw_scaled_bitmap(a, 0, 0, al_get_bitmap_width(a), al_get_bitmap_height(a),
				x, y, w, h, 1);
		else
			al_draw_scaled_bitmap(b, 0, 0, al_get_bitmap_width(b), al_get_bitmap_height(b),
				x, y, w, h, 1);

	}
	template <class T>
	void move(vector<T> v) {
		x += vx;
		y += gravity + vy;
		if (x > width)
			x = 0;
		if (y >= height)
			y = 0;
		for (auto r : v) {

			if (checkCollisionUp(r)) {
				y = r.getY() + r.getH();
				vx = 0.4;
			}

			if (checkCollisionDown(r)) {
				y = r.getY() - h;
				vx = 0.4;
			}
		}
	}
	int getDanger() { return danger; }
	~CEnemy() { }

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
};
