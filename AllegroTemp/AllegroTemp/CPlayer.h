#pragma once

class CPlayer :
	public Objeto
{
	int puntos, ncomida, nagua, energia, nmonedas, direccion, nbalas;
	ALLEGRO_BITMAP *image;
	ALLEGRO_BITMAP *ipd; //imagen bala derecha
	ALLEGRO_BITMAP *ipi; //imagen bala izquierda
	vector<CBalas> Pistola;
public:

	void setImage(ALLEGRO_BITMAP *i) {

		if(image != NULL)
			al_destroy_bitmap(image);
		image = i;
	}

	CPlayer() :Objeto::Objeto() {};
	CPlayer(float x1, float y1, float w1, float h1) : Objeto::Objeto(x1, y1, w1, h1) {

		image = NULL;

		for (int i = 0; i < 5; i++)
			Pistola.push_back(CBalas(x, y, 15, 15, 1));

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

	int getPuntos() { return puntos; }
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
	void applyBlockPhysics(vector<T> v) {

		// desaceleracion en x
		if (vx > 0.1) vx -= 0.05;
		else if (vx < -0.1) vx += 0.05;
		else vx = 0.0;


		if (SPACE && -3 < vy) vy -= 1.5;
		else vy += gravity;

		if (LEFT && vx > -5.0) vx -= 0.1;
		if (RIGHT && vx < 5.0) vx += 0.1;

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

		for (auto x : Pistola)
			x.update(ipi, ipd);

		al_draw_scaled_bitmap(image, 0, 0, al_get_bitmap_width(image), al_get_bitmap_height(image),
			x, y, w, h, 1);
	}
	template<typename T>
	int ColisionMalos(vector<T> malos) {

		int id = -1;
		for (int i = 0; i< malos.size(); i++) {

			if (checkCollision(malos[i])) {

				id = i;
				break;
			}
		}

		if (id != -1)
			energia--;

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
			/*else if (vrecursos[id].getTipo() == 4)
			{
			Pistola.push_back(CBalas(0, 0, 10, 10, 1));
			nbalas = Pistola.size();
			}*/
			SumarPuntos(vrecursos[id].getPuntos());
		}

		return id;
	}

	void Disparar() {
		int i = 0;
		for (i = 0; i < Pistola.size(); i++)
			if (!Pistola[i].getSeLanzo())
				break;
		if (Pistola.size()>0)
			Pistola[i].seLanzo();
	}
};
