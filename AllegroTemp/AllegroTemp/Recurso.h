#pragma once

class Recurso :
	public Objeto
{
	int puntos, tipo;

public:


	Recurso(int t) :
		Objeto::Objeto(20 + rand() % width, 20 + rand() % (height - 60), 50, 50) {

		tipo = t;
		if (tipo == 1) {
			puntos = 100;
			image = al_load_bitmap("coin.png");

		}//Moneda
		else if (tipo == 2) {
			puntos = 150;
			image = al_load_bitmap("food.png");
		}
		// Comida
		else if (tipo == 3) {
			puntos = 120;
			image = al_load_bitmap("agua.png");
		}// Agua
		else {
			puntos = 0;
			image = al_load_bitmap("portal.png");
		}//portal
	}
	void update() {

		if (image != nullptr)
			al_draw_scaled_bitmap(image, 0, 0, al_get_bitmap_width(image), al_get_bitmap_height(image),
				x, y, w, h, 1);
	}

	void move() {
		x += vx;
		if (x <= 0 || x > width)
			vx *= -1;
	}

	int getTipo() { return tipo; }
	int getPuntos() { return puntos; }


	~Recurso() {}
};