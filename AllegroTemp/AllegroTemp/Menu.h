#pragma once

class Menu {

	Objeto bnuevo;
	Objeto bcargar;
	Objeto bcredito;
	Objeto bsalir;
	Input in;

	bool juagar;
	bool salir;
	bool cargar;

	short pantalla; // 1: inicial - 2: cargar partida - 3: creditos
public:

	Menu() {

		bnuevo = Objeto(width / 6 * 2, height / 14 * 5, width / 6 * 2, height / 14);
		bcargar = Objeto(width / 6 * 2, height / 14 * 7, width / 6 * 2, height / 14);
		bcredito = Objeto(width / 6 * 2, height / 14 * 9, width / 6 * 2, height / 14);
		bsalir = Objeto(width / 6 * 2, height / 14 * 11, width / 6 * 2, height / 14);

		juagar = false;
		salir = false;
		cargar = false;

		pantalla = 1;
	}

	void update(ALLEGRO_BITMAP *bg, ALLEGRO_FONT *f, CJuego *j) {

		al_draw_scaled_bitmap(bg, 0, 0, al_get_bitmap_width(bg), al_get_bitmap_height(bg),
			0, 0, width, height, 1);

		if (pantalla == 1) buttons(f, j);
		else if (pantalla == 2) cargarPartida(f, j);
		else if (pantalla == 3) drawCredits(f);
	}

	void buttons(ALLEGRO_FONT *f, CJuego *j) {

		string s;

		s = "Un juego bien chillll..";
		al_draw_text(f, al_map_rgb(255, 255, 255), width / 2, height / 14 * 2, ALLEGRO_ALIGN_CENTER, s.c_str());

		//botones
		al_draw_filled_rectangle(bnuevo.getX(), bnuevo.getY(),
			bnuevo.getX() + bnuevo.getW(), bnuevo.getY() + bnuevo.getH(), al_map_rgb(50, 50, 50));
		s = "Nuevo juego";
		al_draw_text(f, al_map_rgb(255, 255, 255), bnuevo.getX() + (bnuevo.getW() / 2),
			bnuevo.getY() + (bnuevo.getH() / 2), ALLEGRO_ALIGN_CENTER, s.c_str());

		al_draw_filled_rectangle(bcargar.getX(), bcargar.getY(),
			bcargar.getX() + bcargar.getW(), bcargar.getY() + bcargar.getH(), al_map_rgb(50, 50, 50));
		s = "Cargar partida";
		al_draw_text(f, al_map_rgb(255, 255, 255), bcargar.getX() + (bcargar.getW() / 2),
			bcargar.getY() + (bcargar.getH() / 2), ALLEGRO_ALIGN_CENTER, s.c_str());

		al_draw_filled_rectangle(bcredito.getX(), bcredito.getY(),
			bcredito.getX() + bcredito.getW(), bcredito.getY() + bcredito.getH(), al_map_rgb(50, 50, 50));
		s = "Creditos";
		al_draw_text(f, al_map_rgb(255, 255, 255), bcredito.getX() + (bcredito.getW() / 2),
			bcredito.getY() + (bcredito.getH() / 2), ALLEGRO_ALIGN_CENTER, s.c_str());

		al_draw_filled_rectangle(bsalir.getX(), bsalir.getY(),
			bsalir.getX() + bsalir.getW(), bsalir.getY() + bsalir.getH(), al_map_rgb(50, 50, 50));
		s = "Salir";
		al_draw_text(f, al_map_rgb(255, 255, 255), bsalir.getX() + (bsalir.getW() / 2),
			bsalir.getY() + (bsalir.getH() / 2), ALLEGRO_ALIGN_CENTER, s.c_str());

		if (checkClicks(bnuevo)) {

			juagar = true;
		}
		else if (checkClicks(bcargar)) {

			cargar = true;
			in = Input(width / 2, height / 2);
			pantalla = 2;
		}
		else if (checkClicks(bcredito)) {

			pantalla = 3;
		}
		else if (checkClicks(bsalir)) {

			salir = true;
		}
	}

	bool checkClicks(Objeto c) {

		if (CLICK) {

			if ((c.getX() < mouseX && mouseX < (c.getX() + c.getW())) &&
				(c.getY() < mouseY && mouseY < (c.getY() + c.getH()))) {

				CLICK = false;
				return true;
			}
			else {

				return false;
			}
		}
		return false;
	}

	bool getSalir() { return salir; }

	void cargarPartida(ALLEGRO_FONT *f, CJuego *j) {

	/*	string s;

		s = "Escriba el nombre de la partida";
		al_draw_text(f, al_map_rgb(255, 255, 255), width / 2, height / 14 * 2, ALLEGRO_ALIGN_CENTER, s.c_str());
		in.update(f);

		al_draw_filled_rectangle(width / 2 - 20, height / 14 * 3, width / 2 + 20, height / 14 * 3 + 10, al_map_rgb(0, 255, 0));
		if (checkClicks(Objeto(width / 2, height / 14 * 3, 40, 10))) {

			//freopen(in.getString().c_str(), "r", stdin);

			//fclose(stdin);
		}*/

	}

	bool getJugar() {

		return juagar;
	}

	bool getCargar() {
		return cargar;
	}
	void drawCredits(ALLEGRO_FONT *f) {

		string s;

		s = "Credits";
		al_draw_text(f, al_map_rgb(255, 255, 255), width / 2, height / 14 * 2, ALLEGRO_ALIGN_CENTER, s.c_str());

		s = "Fiorella Barrientos";
		al_draw_text(f, al_map_rgb(255, 255, 255), width / 2, 200, ALLEGRO_ALIGN_CENTER, s.c_str());

		s = "Franco Moloche";
		al_draw_text(f, al_map_rgb(255, 255, 255), width / 2, 300, ALLEGRO_ALIGN_CENTER, s.c_str());

<<<<<<< HEAD
		s = "Juan";
=======
		s = "Juan Peña";
>>>>>>> 955105f7172619d50cf14098b14242504a676205
		al_draw_text(f, al_map_rgb(255, 255, 255), width / 2, 400, ALLEGRO_ALIGN_CENTER, s.c_str());

		if (CLICK) {
			CLICK = false;
			pantalla = 1;
		}
	}
};