#pragma once

class CEnemy
{
	float x, y, w, h, vx, vy;
	ALLEGRO_BITMAP  *image;
	int danger;
public:

	CEnemy(float x = width / 2, float y = height / 2, float w = 10, float h = 10,
		ALLEGRO_BITMAP *image = nullptr) :
		x(x), y(y), w(w), h(h), image(image) {
		vx = 2;
		danger = 100;
	}
	void update()
	{
		move();
		al_draw_scaled_bitmap(image, 0, 0, al_get_bitmap_width(image), al_get_bitmap_height(image), x, y, w, h, 1);
	}
	void move() {
		x += vx;
		if (x <= 0 || x > width)
			vx *= -1;
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
