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

		}//Moneda
		else if (tipo == 2) {
			puntos = 150;
		}
		// Comida
		else if (tipo == 3) {
			puntos = 120;
		}// Agua
		else if (tipo == 4) {
			puntos = 50;
		}// Balas

		else {
			puntos = 0;
		}//portal
	}
	void update(ALLEGRO_BITMAP *image) {
		
		al_draw_scaled_bitmap(image, 0, 0, al_get_bitmap_width(image), al_get_bitmap_height(image), x, y, w, h, 1);
	}

	int getTipo() { return tipo; }
	int getPuntos() { return puntos; }


	~Recurso() { }
};