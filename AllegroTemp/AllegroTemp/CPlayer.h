#pragma once

class CPlayer :
	public Objeto
{
	int puntos, ncomida, nagua, nmonedas, direccion, nbalas;

	ALLEGRO_BITMAP *ipd; //imagen bala derecha
	ALLEGRO_BITMAP *ipi; //imagen bala izquierda
	vector<CBalas> Pistola;
	float energia;

	ALLEGRO_BITMAP *image;

	//ALGIF_ANIMATION *gif = algif_load_animation("chica.gif");
public:

	CPlayer() :Objeto::Objeto() {};
	CPlayer(float x1, float y1, float w1, float h1) :
		Objeto::Objeto(x1, y1, w1, h1) {

		image = NULL;

		for (int i = 0; i < 5; i++)
			Pistola.push_back(CBalas(x, y, 15, 15));

		energia = 100;
		nagua = ncomida = nbalas = nmonedas = puntos = 0;
		direccion = 1;

		ipi = al_load_bitmap("balai.png");
		ipd = al_load_bitmap("balad.png");
	}

	~CPlayer() {

		if (ipi != NULL)
			al_destroy_bitmap(ipi);
		if (ipd != NULL)
			al_destroy_bitmap(ipd);
		if (image != NULL)
			al_destroy_bitmap(image);
	}

	void setImage(ALLEGRO_BITMAP *i) {
		if (image != NULL) {
			al_destroy_bitmap(image);
		}
		image = i;
	}

	int getPuntos() { return puntos; }
	void RestarPuntos(int p) { puntos -= p; }
	void SumarPuntos(int p) { puntos += p; }
	void RestarAgua() { nagua--; }
	int getEnergia() { return energia; }
	int getAgua() { return nagua; }
	int getMonedas() { return nmonedas; }
	void RestarComida() { ncomida--; }
	int getComida() { return ncomida; }
	int getDireccion() { return direccion; }

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

	template<typename T>
	bool checkCollisionUp(T b) {


		if (x > b.getX() && x < b.getX() + b.getW() && x + w > b.getX() && x + w < b.getX() + b.getW() &&
			y < b.getY() + b.getH() && y > b.getY()) {
			return true;
		}
		if ((x > b.getX() && x < b.getX() + b.getW() &&
			y < b.getY() + b.getH() && y > b.getY()) ||
			(x + w > b.getX() && x + w < b.getX() + b.getW() &&
				y < b.getY() + b.getH() && y > b.getY())) {
			return true;
		}
		return false;
	}

	template<typename T>
	bool checkCollisionDown(T b) {


		if (x > b.getX() && x < b.getX() + b.getW() && x + w > b.getX() && x + w < b.getX() + b.getW() &&
			y + h > b.getY() && y + h < b.getY() + b.getH()) {
			return true;
		}
		if ((x > b.getX() && x < b.getX() + b.getW() &&
			y + h > b.getY() && y + h < b.getY() + b.getH()) ||
			(x + w > b.getX() && x + w < b.getX() + b.getW() &&
				y + h > b.getY() && y + h < b.getY() + b.getH())) {
			return true;
		}
		return false;
	}

	void move() {
		x += vx;
		y += vy;
	}

	template<typename T>
	void applyBlockPhysics(vector<T> &v) {

		// desaceleracion en x
		if (energia > 10) {
			if (vx > 0.1) vx -= 0.05;
			else if (vx < -0.1) vx += 0.05;
			else vx = 0.0;


			if (SPACE && -3 < vy) vy -= 1.5;
			else vy += gravity;

			if (LEFT && vx > -5.0) vx -= 0.1;
			if (RIGHT && vx < 5.0) vx += 0.1;
		}
		else
		{
			energia += 0.1;
			vx = 0;
			vy += gravity;
		}
		move();

		for (auto x : v) {

			if (checkCollisionUp(x)) {
				y = x.getY() + x.getH();
				vy = 0.0;
			}

			if (checkCollisionDown(x)) {
				y = x.getY() - h - 0.1;
				vy = 0.0;
			}
		}



	}
	void update() {


		int cont = 0;
		for (int j = 0; j<Pistola.size(); j++)
			if (!Pistola[j].getSeLanzo())
				al_draw_scaled_bitmap(al_load_bitmap("balita.png"), 0, 0, 30, 30,
					10 + (cont++) * 20, 10, w, h, 1);

		int i;
		bool si = false;
		for (i = 0; i < Pistola.size(); i++)
		{
			if (!Pistola[i].getExiste())
			{
				si = true;
				break;
			}
		}
		if (si && Pistola.size() > 0)
			Pistola.erase(Pistola.begin() + i);

		vector<CBalas>::iterator it;
		for (it = Pistola.begin(); it != Pistola.end(); it++)
			it->update(ipi, ipd);
		
		al_draw_scaled_bitmap(image, 0, 0, al_get_bitmap_width(image), al_get_bitmap_height(image),
			x, y, w, h, 1);

		//al_draw_bitmap(algif_get_bitmap(gif, al_get_time()), x, y, 0);

	}
	template<typename T>
	int ColisionMalos(vector<T> malos) {

		for (int i = 0; i< malos.size(); i++) {

			if (checkCollision(malos[i])) {

				RestarPuntos(malos[i].getDanger());
				energia--;
				break;
			}
		}


		int id = -1;
		for (auto x : Pistola)
			if (x.getSeLanzo() && x.getExiste())
				for (int i = 0; i < malos.size(); i++)
					if (x.checkCollision(malos[i]))
						id = i;

		return id;

	}

	template<typename T>
	int ColisionRecurso(vector<T> vrecursos)
	{
		int id = -1;
		for (int i = 0; i< vrecursos.size(); i++)
		{
			if (checkCollision(vrecursos[i]))
			{
				id = i;
				break;
			}

		}

		if (id != -1)
		{
			if (vrecursos[id].getTipo() == 1)
				nmonedas++;
			else if (vrecursos[id].getTipo() == 2)
				ncomida++;
			else if (vrecursos[id].getTipo() == 3)
				nagua++;
			else if (vrecursos[id].getTipo() == 4)
				Pistola.push_back(CBalas(x, y, 15, 15));

			SumarPuntos(vrecursos[id].getPuntos());
			energia++;
		}

		return id;
	}

	void Disparar() {
		int i;
		for (i = 0; i < Pistola.size(); i++)
			if (!Pistola[i].getSeLanzo())
				break;
		if (Pistola.size() > 0)
		{
			Pistola[i].setX(x);
			Pistola[i].setY(y);
			Pistola[i].seLanzo();
			if (direccion == -1)
				Pistola[i].OtroLado();
			direccion = 1;
		}
	}
	void CambiarDireccion() {
		direccion = direccion * -1;
		Disparar();
	}

};
