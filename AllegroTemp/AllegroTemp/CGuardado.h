#pragma once
#include <fstream>
#include <string.h>
#include <string>

using namespace std;
class CGuardado
{
	int puntos, ncomida, nagua, nmonedas, energia, nivel, x, y, nbalas;
	string file;
public:
	CGuardado() { file = "archivoplayer.txt"; }

	void setPuntos(int nuevo) { puntos=nuevo;}
	void setNcomida(int nuevo) { ncomida=nuevo;	}
	void setNagua(int nuevo){ nagua=nuevo; }
	void setNmonedas(int nuevo) { nmonedas=nuevo; }
	void setEnergia(int nuevo) { energia=nuevo; }
	void setX(int nuevo) { x = nuevo; }
	void setY(int nuevo) { y = nuevo; }
	void setBalas(int nuevo) {nbalas  = nuevo; }
	int getPuntos() { return puntos; }
	int getNcomida() { return ncomida; }
	int getNagua() { return nagua; }
	int getNmonedas() { return nmonedas; }
	int getEnergia() { return energia; }
	int getX() { return x; }
	int getY() { return y; }
	int getBalas() { return nbalas; }
	void Grabar();
	void LeerArchivo();

	~CGuardado();
};

void CGuardado::Grabar()
{
	ofstream fs(file);
	fs.clear();
	fs << endl << getPuntos() << endl;
	fs << getNcomida() << endl;
	fs << getNagua() << endl;
	fs << getNmonedas() << endl;
	fs << getEnergia() << endl;
	fs << getX() << endl;
	fs << getY() << endl;
	fs << getBalas() << endl;
	fs.flush();
	fs.close();
}

void CGuardado::LeerArchivo()
{
	ifstream fs(file);
	string cadena;
	while (!fs.eof())
	{
		getline(fs, cadena);
		if (cadena.length() > 0) {
			puntos = atoi(cadena.c_str());
			getline(fs, cadena);
			ncomida = atoi(cadena.c_str());
			getline(fs, cadena);
			nagua = atoi(cadena.c_str());
			getline(fs, cadena);
			nmonedas = atoi(cadena.c_str());
			getline(fs, cadena);
			energia = atoi(cadena.c_str());
			getline(fs, cadena);
			x = atoi(cadena.c_str());
			getline(fs, cadena);
			y = atoi(cadena.c_str());
			getline(fs, cadena);
			nbalas = atoi(cadena.c_str());
			getline(fs, cadena);
		}
	}
	fs.close();
}

CGuardado::~CGuardado()
{
}
