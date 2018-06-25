#pragma once

class CBlock : public Objeto
{
	int tipo;
public:

	CBlock() :Objeto::Objeto() {};
	CBlock(float x1, float y1, float w1, float h1) :
		Objeto::Objeto(x1, y1, w1, h1) {
		

		tipo = (rand() % 122) % 2 == 0 ? 1 : 0;
		vy = 0.9;
	}

	void update(ALLEGRO_BITMAP *image, ALLEGRO_BITMAP *image2) {

		if (tipo == 1)
		{
			y += vy;
			if (y < 100 || y > height - 200)
				vy *= -1;
		}
		if(this->getW() > 170)
			al_draw_scaled_bitmap(image, 0, 0, al_get_bitmap_width(image), al_get_bitmap_height(image),
			x, y, w, h, 1);
		else
			al_draw_scaled_bitmap(image2, 0, 0, al_get_bitmap_width(image2), al_get_bitmap_height(image2),
				x, y, w, h, 1);
	}
	~CBlock() {}
};