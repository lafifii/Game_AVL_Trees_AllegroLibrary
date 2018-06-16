#pragma once
class CBalas : public Objeto
{
	bool lanzo;
	bool existe;
	bool left;
public:
	CBalas(float x1, float y1, float w1, float h1, int direc) :
		Objeto::Objeto(x1, y1, w1, h1)
	{
		if (direc == -1)
			vx *= -1;
		if (vx < 0)
			left = true;
		else
			left = true;
		existe = true;
		lanzo = false;
	}
	bool getSeLanzo() { return lanzo; }
	void seLanzo() { lanzo = true; }
	void move() {
		x += vx;
		if (x<0 || x>width)
			existe = false;
	}
	bool getExiste() { return existe; }
	void update(ALLEGRO_BITMAP *l, ALLEGRO_BITMAP *r) {
		if (lanzo) {

			move();
			if (left)
				al_draw_scaled_bitmap(l, 0, 0, al_get_bitmap_width(l), al_get_bitmap_height(l), x, y, w, h, 1);
			else
				al_draw_scaled_bitmap(r, 0, 0, al_get_bitmap_width(r), al_get_bitmap_height(r), x, y, w, h, 1);
		}
	}
	~CBalas() { }
};