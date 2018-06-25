#pragma once

class CPlayer :
	public Objeto
{
	int puntos, ncomida, nagua, nmonedas, direccion, nbalas;

	
	vector<CBalas> Pistola;
	float energia;

	ALLEGRO_BITMAP *img, *img2;
	ALLEGRO_BITMAP *l, *r, *balita;
public:

	CPlayer() :Objeto::Objeto() { };
	CPlayer(float x1, float y1, float w1, float h1) :
		Objeto::Objeto(x1, y1, w1, h1) {


		balita = NULL;
		img = NULL;
		img2 = NULL;
		l = NULL;
		r = NULL;
		for (int i = 0; i < 5; i++)
			Pistola.push_back(CBalas(x, y, 15, 15));

		energia = 100;
		nagua = ncomida = nbalas = nmonedas = puntos = 0;
		direccion = 1;
	}

	~CPlayer() {
		if (img2 != NULL)
			al_destroy_bitmap(img2);
		if (img != NULL)
			al_destroy_bitmap(img);
		if (l != NULL)
			al_destroy_bitmap(l);
		if (r != NULL)
			al_destroy_bitmap(r);
		if (balita != NULL)
			al_destroy_bitmap(balita);
	}

	void setImagePlayer(ALLEGRO_BITMAP *a, ALLEGRO_BITMAP *b) {

		if (img != NULL)
			al_destroy_bitmap(img);
		if (img2 != NULL)
			al_destroy_bitmap(img2);

		img = a;
		img2 = b;
	}
	void setImagePistola(ALLEGRO_BITMAP *a, ALLEGRO_BITMAP *b) {

		if (l != NULL)
			al_destroy_bitmap(l);
		if (r != NULL)
			al_destroy_bitmap(r);

		l = a;
		r = b;
	}
	void setImageBalita(ALLEGRO_BITMAP *b) {
		if (balita != NULL)
			al_destroy_bitmap(balita);
		balita = b;
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
	void TomarAgua() {
		if (nagua > 0) {
			nagua--;
			energia++;
		}
	}
	void Comer() {
		if (ncomida > 0) {
			ncomida--;
			energia++;
		}
	}
	void Recargar() {
		if (nmonedas > 10)
		{
			for (int i = 0; i < 5; i++)
			{
				Pistola.push_back(CBalas(x, y, 15, 15));
				nbalas++;
			}
			nmonedas -= 10;
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


	void move() {
		x += vx;
		y += vy;
	}

	template<typename T>
	void applyBlockPhysics(vector<T> v) {

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
		for (int j = 0; j < Pistola.size(); j++)
		{
			if (!Pistola[j].getSeLanzo())
			{
				al_draw_scaled_bitmap(balita, 0, 0, 30, 30,
					10 + (cont++) * 20, 10, 30, 30, 1);
			}
		}
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
		{
			it->update(direccion, l, r);
		}
		if (energia > 10)
			al_draw_scaled_bitmap(img, 0, 0, al_get_bitmap_width(img), al_get_bitmap_height(img),
				x, y + 5, w, h, 1);
		else
			al_draw_scaled_bitmap(img2, 0, 0, al_get_bitmap_width(img2), al_get_bitmap_height(img2),
				x, y + 5, w, h, 1);

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
		int i=-1;
	
		for (int j = 0; j < Pistola.size(); j++)
		{
			if (Pistola[j].getSeLanzo())
			{
				i = -1;
				break;
			}
			if (!Pistola[j].getSeLanzo())
			{
				i = j;
				break;
			}
			
		}
		if (i != -1 && !Pistola.empty())
		{
			Pistola[i].setX(x);
			Pistola[i].setY(y);
			Pistola[i].seLanzo();
			nbalas--;
		}
	}
	
	void DisparoDer() {
		direccion = 1;
		Disparar();
	}
	void CambioEscena() {
		
		int i = -1;

		for (int j = 0; j < Pistola.size(); j++)
		{
			if (Pistola[j].getSeLanzo())
			{
				i = j;
				break;
			}
		}
		if(i!=-1&&Pistola.size()>0)
			Pistola[i].setExiste(false);
	
	}

};
