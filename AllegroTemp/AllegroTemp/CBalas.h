#pragma once
class CBalas : public Objeto
{
	bool lanzo;
	bool existe;
	bool left;

public:
	CBalas(float x1, float y1, float w1, float h1) :
		Objeto::Objeto(x1, y1, w1, h1)
	{
		vx = 2;
		if (vx < 0)
			left = true;
		else
			left = false;

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

	template<typename T>
	bool checkCollision(T b) {

		if ((x > b.getX() && x < b.getX() + b.getW() && y > b.getY() && y < b.getY() + b.getH()) ||
			(x + w > b.getX() && x + w < b.getX() + b.getW() && y > b.getY() && y < b.getY() + b.getH()) ||
			(x > b.getX() && x < b.getX() + b.getW() && y + h > b.getY() && y + h < b.getY() + b.getH()) ||
			(x + w > b.getX() && x + w < b.getX() + b.getW() && y + h > b.getY() && y + h < b.getY() + b.getH()))
		{
			return true;
		}
		return false;
	}
	void OtroLado()
	{
		vx = vx * -1;
		if (vx < 0)
			left = true;
		else
			left = false;
	}
	~CBalas()
	{
	}
};