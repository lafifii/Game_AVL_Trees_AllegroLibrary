#pragma once

class Beacon {
	int nenemigos, nrecursos, nbloques, indice, idUbicacion;
	bool portaldebusqueda;
	float kmDistancia;
	string ubicacion;
	bool fueGenerado;
	vector<CBlock> vb;
	vector<CEnemy> ve;
	vector<string> nombres;
	vector<Recurso> vr;
	
public:
	Beacon(int numerodeBeacon) {
		fueGenerado = false;
		portaldebusqueda = (rand() % 67) % 2 == 0 ? true : false;
		nenemigos = rand() % 7;
		nrecursos = rand() % 9;
		kmDistancia = numerodeBeacon * 5.5;
		indice = numerodeBeacon;
		nbloques = 7 + rand() % 5;
		nombres.push_back("NORTE NORESTE"); nombres.push_back("NOROESTE"); nombres.push_back("ESTE NORESTE");
		nombres.push_back("ESTE"); nombres.push_back("ESTE SUDESTE");
		nombres.push_back("SUDESTE"); nombres.push_back("SUR SUDESTE"); nombres.push_back("SUR"); nombres.push_back("SUR SUDOESTE");
		nombres.push_back("SUDOESTE");
		nombres.push_back("OESTE SUDOESTE");
		nombres.push_back("OESTE"); nombres.push_back("OESTE NOROESTE"); nombres.push_back("NOROESTE"); nombres.push_back("NORTE NOROESTE");
		nombres.push_back("NORTE");
	
		idUbicacion = rand() % 16;
		ubicacion = nombres[rand() % 16];

	}
	
	void GenerarEscenario() {
		if(!fueGenerado){
			fueGenerado = true;
			//Generando enemigos
			for (int i = 0; i < nenemigos; i++)
				ve.push_back(CEnemy(80 * i, 100, 50, 50));
			//generando bloques
			for (int i = 0; i <nbloques; i++)
			{
				if (i % 2 == 0)
					vb.push_back(CBlock(0 + i * 100, 400, 70 + rand() % 140, 50));
				else
					vb.push_back(CBlock(400 + i * 100, 250, 70 + rand() % 120, 50));
			}
			srand(time(NULL));
			//Generando recurso
			for (int i = 0; i < nrecursos - 1; i++)
				vr.push_back(Recurso(1 + rand() % 4));
			if (portaldebusqueda)
				vr.push_back(Recurso(5));
			else
				vr.push_back(Recurso(1 + rand() % 4));

		}
	}
	Beacon() {
		nenemigos = nrecursos = kmDistancia = nbloques = indice = 0;
	}
	void setFueGenerado(bool b) { fueGenerado = b; }
	void setNEnemigos(int e) { nenemigos=e; }
	void setNRecursos(int n) { nrecursos=n; }
	void setNBloques(int n) { nbloques=n; }
	void setDistancia(float n) { kmDistancia=n; }
	void setUbicacion(string u) {
		ubicacion=u; 


		for (int i = 0; i < 16; i++)
			if (nombres[i] == u)
				idUbicacion = i;

	}

	int getNEnemigos() { return nenemigos; }
	int getNRecursos() { return nrecursos; }
	int getNBloques() { return nbloques; }
	int getIndex() { return indice; }
	bool PortalBusqueda() { return portaldebusqueda; }
	float getDistancia() { return kmDistancia; }
	int getIdUbicacion() { return idUbicacion; }
	string getUbicacion() { return ubicacion; }

	void update(ALLEGRO_BITMAP *fondo, ALLEGRO_BITMAP *ie, ALLEGRO_BITMAP *ie2, ALLEGRO_BITMAP *ib, ALLEGRO_BITMAP *ib2,
		ALLEGRO_BITMAP *icoin, ALLEGRO_BITMAP *ifood, ALLEGRO_BITMAP *iagua, ALLEGRO_BITMAP *ibala, ALLEGRO_BITMAP *iportal) {
		
	al_draw_scaled_bitmap(fondo, 0, 0, al_get_bitmap_width(fondo), al_get_bitmap_height(fondo),
			0, 0, width, height, 1);

		for (vector<CEnemy>::iterator it = ve.begin(); it != ve.end(); it++)
			it->update(ie, ie2, vb);

		for (vector<CBlock>::iterator it = vb.begin(); it != vb.end(); it++)
			it->update(ib, ib2);

		for (int i = 0; i < vr.size(); i++) {

			switch (vr[i].getTipo())
			{
			case 1:
				vr[i].update(icoin);
				break;
			case 2:
				vr[i].update(ifood);
				break;
			case 3:
				vr[i].update(iagua);
				break;
			case 4:
				vr[i].update(ibala);
				break;
			case 5:
				vr[i].update(iportal);
				break;
			}
		}


	}
	vector<CBlock> getBloques() { return vb; }
	vector <Recurso> getRecursos() { return vr; }
	vector <CEnemy> getEnemigos() { return ve; }
	~Beacon() {}
	void EliminarRecurso(int indexRec) { vr.erase(vr.begin() + indexRec); nrecursos--; }
	void EliminarEnemigo(int indexEn) { ve.erase(ve.begin() + indexEn); nenemigos--; }


};