#pragma once

class CBlock : public Objeto
{
public:

	CBlock() :Objeto::Objeto() {};
	CBlock(float x1, float y1, float w1, float h1, ALLEGRO_BITMAP *image) :
		Objeto::Objeto(x1, y1, w1, h1, image) { }


	void update() {

		al_draw_scaled_bitmap(image, 0, 0, al_get_bitmap_width(image), al_get_bitmap_height(image),
			x, y, w, h, 1);
	}
};