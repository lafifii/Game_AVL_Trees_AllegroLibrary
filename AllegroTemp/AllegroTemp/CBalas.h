#pragma once
class CBalas : public Objeto
{
	bool lanzo;
	bool existe;

public:
	CBalas(float x1, float y1, float w1, float h1, int direc) :
		Objeto::Objeto(x1, y1, w1, h1, al_load_bitmap("balad.png"))
	{
		if (direc == -1)
			vx *= -1;
		if (vx < 0)
			image = al_load_bitmap("balai.png");
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
	void update() {
		if (lanzo) {
			move();
			if (image != nullptr)
				al_draw_scaled_bitmap(image, 0, 0, al_get_bitmap_width(image), al_get_bitmap_height(image),
					x, y, w, h, 1);
			else
				al_draw_circle(x, y, w, al_map_rgb(12, 43, 43), 10);
		}
	}
	~CBalas()
	{
	}
};