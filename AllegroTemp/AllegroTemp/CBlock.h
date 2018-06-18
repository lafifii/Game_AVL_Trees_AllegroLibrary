#pragma once

class CBlock : public Objeto
{
	int tipo;
public:

	CBlock() :Objeto::Objeto() {};
	CBlock(float x1, float y1, float w1, float h1) :
		Objeto::Objeto(x1, y1, w1, h1) {
		srand(time(NULL));
		tipo = (rand() % 122) % 3 == 0 ? 1 : 0;
		vy = 2;
	}

	void update(ALLEGRO_BITMAP *image) {

		if (tipo == 1)
		{
			y += vy;
			if (y < 100 || y > height - 200)
				vy *= -1;
		}
		al_draw_scaled_bitmap(image, 0, 0, al_get_bitmap_width(image), al_get_bitmap_height(image),
			x, y, w, h, 1);
	}
	~CBlock() {}
};