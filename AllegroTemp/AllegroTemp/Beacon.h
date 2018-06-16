#pragma once

class Beacon {
	int nenemigos, nrecursos, nbloques, indice;
	bool portaldebusqueda;
	float kmDistancia;
	string ubicacion;

public:
	Beacon(int numerodeBeacon) {
		portaldebusqueda = true;
		nenemigos = rand() % 5;
		nrecursos = rand() % 9;
		kmDistancia = numerodeBeacon * 5.5;
		indice = numerodeBeacon;
		nbloques = 7 + rand() % 5;
		string nombres[4] = { "Norte","Sur","Este","Oeste" };
		ubicacion = nombres[rand() % 4];
	}
	Beacon() {
		nenemigos = nrecursos = kmDistancia = nbloques = indice = 0;
	}
	int getNEnemigos() { return nenemigos; }
	int getNRecursos() { return nrecursos; }
	int getNBloques() { return nbloques; }
	int getIndex() { return indice; }
	bool PortalBusqueda() { return portaldebusqueda; }
	float getDistancia() { return kmDistancia; }
	string getUbicacion() { return ubicacion; }

	~Beacon() {}

};