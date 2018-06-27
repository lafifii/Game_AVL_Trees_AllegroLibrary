#pragma once
#include "Input.h"

class CJuego {

	string file;
	Scene *myscene;
	ALLEGRO_BITMAP *imgpuntero;
	AVLTree <Beacon*> ArboldeBusquedaPorEnemigos;
	AVLTree <Beacon*> ArboldeBusquedaPorRecursos;
	AVLTree <Beacon*> ArboldeBusquedaPorKm;
	AVLTree <Beacon*> ArboldeBusquedaPorUbicacion;
	AVLTree <Beacon*> ArboldeBusquedaPorNBloques;
	Input input;
	ALLEGRO_BITMAP	*bmp;
	bool eligio;

	struct Puntero {
		float x, y;
	}punteroEleccion;
public:
	CJuego() {

		file = "mapa.txt";
		bmp = al_load_bitmap("img/tele.jpg");
		punteroEleccion.x = 290;
		punteroEleccion.y = 70;
		myscene = new Scene();
		eligio = false;
		ArboldeBusquedaPorEnemigos = AVLTree<Beacon*>(1);
		ArboldeBusquedaPorRecursos = AVLTree<Beacon*>(2);
		ArboldeBusquedaPorKm = AVLTree<Beacon*>(3);
		ArboldeBusquedaPorUbicacion = AVLTree<Beacon*>(4);
		ArboldeBusquedaPorNBloques = AVLTree<Beacon*>(5);
		imgpuntero = al_load_bitmap("img/punt.png");


		ALLEGRO_BITMAP *bgaux = al_load_bitmap("img/tele.jpg");
		ALLEGRO_BITMAP *bgaux2 = al_load_bitmap("img/load.jpg");

		al_draw_scaled_bitmap(bgaux, 0, 0, al_get_bitmap_width(bgaux), al_get_bitmap_height(bgaux), 0, 0, width, height, 1);

		al_draw_scaled_bitmap(bgaux2, 0, 0, al_get_bitmap_width(bgaux2), al_get_bitmap_height(bgaux2), width / 2 - 100, 50, 200, 60, 1);

		size_t aux_n = 10000;

		int cont = 0, cont2 = 1;
		for (int i = 0; i < aux_n; i++, cont++)
		{
			if (cont == aux_n/width)
			{
				al_draw_filled_rectangle(cont2, 200, cont2 + 2, 230, al_map_rgb(255, 255, 255));
				cont2 += 3;
				cont = 0;
			}
			al_flip_display();
			Beacon *o = new Beacon(i);
			myscene->AddArbol(o);
			ArboldeBusquedaPorEnemigos.add(o);
			ArboldeBusquedaPorRecursos.add(o);
			ArboldeBusquedaPorKm.add(o);
			ArboldeBusquedaPorUbicacion.add(o);
			ArboldeBusquedaPorNBloques.add(o);

		}
		al_destroy_bitmap(bgaux);
		al_destroy_bitmap(bgaux2);
		myscene->Inicializar_Valores();
	}

	CJuego(int index, int inmenor, int nmayor) {


		file = "mapa.txt";
		ifstream fs(file);
		string cadena;

		bmp = al_load_bitmap("img/tele.jpg");
		punteroEleccion.x = 290;
		punteroEleccion.y = 70;
		eligio = false;
		ArboldeBusquedaPorEnemigos = AVLTree<Beacon*>(1);
		ArboldeBusquedaPorRecursos = AVLTree<Beacon*>(2);
		ArboldeBusquedaPorKm = AVLTree<Beacon*>(3);
		ArboldeBusquedaPorUbicacion = AVLTree<Beacon*>(4);
		ArboldeBusquedaPorNBloques = AVLTree<Beacon*>(5);
		imgpuntero = al_load_bitmap("img/punt.png");


		getline(fs, cadena, ' ');
		inmenor = atoi(cadena.c_str());
		getline(fs, cadena, ' ');
		nmayor = atoi(cadena.c_str());
		getline(fs, cadena, ' ');
		index = atoi(cadena.c_str());


		myscene = new Scene();
		myscene->setIndice(index);

		bool fuegenerado2;
		int nenemigos2;
		int nrecursos2;
		bool portaBusq;
		int nbloques2;
		int id2;
		int nuevoindex;
		ALLEGRO_BITMAP *bgaux = al_load_bitmap("img/tele.jpg");
		ALLEGRO_BITMAP *bgaux2 = al_load_bitmap("img/load.jpg");

		al_draw_scaled_bitmap(bgaux, 0, 0, al_get_bitmap_width(bgaux), al_get_bitmap_height(bgaux), 0, 0, width, height, 1);

		al_draw_scaled_bitmap(bgaux2, 0, 0, al_get_bitmap_width(bgaux2), al_get_bitmap_height(bgaux2), width/2 - 100, 50, 200, 60, 1);

		size_t aux_n = (inmenor + nmayor)/width;

		int cont = 0, cont2 = 1;
		for (int i = inmenor; i < nmayor; i++, cont++)
		{
			if (cont == aux_n )
			{
				al_draw_filled_rectangle(cont2, 200, cont2 + 2, 230, al_map_rgb(255, 255, 255));
				cont2 += 3;
				cont = 0;
			}
			al_flip_display();
			 
			getline(fs, cadena, ' ');
			nuevoindex = atoi(cadena.c_str());
			getline(fs, cadena,' ');
			fuegenerado2 = atoi(cadena.c_str());
			 getline(fs, cadena,' ');
			nenemigos2 = atoi(cadena.c_str());
			 getline(fs, cadena,' ');
			nrecursos2 = atoi(cadena.c_str());
			 getline(fs, cadena,' ');
			portaBusq = atoi(cadena.c_str());
			 getline(fs, cadena,' ');
			nbloques2 = atoi(cadena.c_str());
			 getline(fs, cadena,' ');
			id2 = atoi(cadena.c_str());

			Beacon *o = new Beacon(nuevoindex,fuegenerado2,nenemigos2,nrecursos2,portaBusq,nbloques2,id2);
			myscene->AddArbol(o);
			ArboldeBusquedaPorEnemigos.add(o);
			ArboldeBusquedaPorRecursos.add(o);
			ArboldeBusquedaPorKm.add(o);
			ArboldeBusquedaPorUbicacion.add(o);
			ArboldeBusquedaPorNBloques.add(o);

		}
		al_destroy_bitmap(bgaux);
		al_destroy_bitmap(bgaux2);
		fs.close();

		myscene->CargarPartida();
	}
	
	void Disparar()
	{
		myscene->Disparar();
	}
	void Buscar(ALLEGRO_FONT *font)
	{
		if (!eligio)
		{
		
			
			if (UP)
			{
				if (punteroEleccion.y - 20 >= 70)
				{
					punteroEleccion.y = punteroEleccion.y - 20;
					UP = false;
				}
			}
			if (DOWN)
			{
				if (punteroEleccion.y + 20 <= 150)
				{
					punteroEleccion.y = punteroEleccion.y + 20;
					DOWN = false;
				}
			}

			al_draw_scaled_bitmap(imgpuntero, 0, 0, al_get_bitmap_width(imgpuntero), al_get_bitmap_height(imgpuntero),
				punteroEleccion.x, punteroEleccion.y, 15, 15, 1);
			al_draw_text(font, al_map_rgb(0, 0, 0), width / 2, 30, ALLEGRO_ALIGN_CENTER, "Teletransportate a otro escenario...Elige criterio:");
			al_draw_text(font, al_map_rgb(0, 0, 255), width / 2, 70, ALLEGRO_ALIGN_CENTER, "Numero de Recursos");
			al_draw_text(font, al_map_rgb(0, 0, 255), width / 2, 90, ALLEGRO_ALIGN_CENTER, "Numero de Bloques");
			al_draw_text(font, al_map_rgb(0, 0, 255), width / 2, 110, ALLEGRO_ALIGN_CENTER, "Ubicacion");
			al_draw_text(font, al_map_rgb(0, 0, 255), width / 2, 130, ALLEGRO_ALIGN_CENTER, "KM de Distancia al punto de partida");
			al_draw_text(font, al_map_rgb(0, 0, 255), width / 2, 150, ALLEGRO_ALIGN_CENTER, "Numero de Enemigos");
			if (ELEX)
			{
				eligio = true;
				ELEX = false;
				input = Input(width / 2,50);
			}
		}
		else
		{

			al_draw_text(font, al_map_rgb(0, 0, 0), width / 2, 30, ALLEGRO_ALIGN_CENTER, "Escribe el atributo que deseas");
			input.update(font);
			if (ELEX) {

				Beacon *nuevaInfo = new Beacon(0);
				ELEX = false;
				int numeroBuscar;
				float flotanteBuscar;
				if(punteroEleccion.y == 70)
				{
					numeroBuscar = stoi(input.getString().c_str());
					nuevaInfo->setNRecursos(numeroBuscar); 
					nuevaInfo = ArboldeBusquedaPorRecursos.search(nuevaInfo);
					
				}
				else if (punteroEleccion.y == 90)
				{
					numeroBuscar = stoi(input.getString().c_str());
					nuevaInfo->setNBloques(numeroBuscar); 
					nuevaInfo = ArboldeBusquedaPorNBloques.search(nuevaInfo);
				}
				else if (punteroEleccion.y == 110)
				{
					string str = input.getString();
					nuevaInfo->setUbicacion(input.getString()); 
					nuevaInfo = ArboldeBusquedaPorUbicacion.search(nuevaInfo);
				}
				else if (punteroEleccion.y == 130)
				{
					flotanteBuscar = strtof(input.getString().c_str(),0);
					nuevaInfo->setDistancia(flotanteBuscar); 
					nuevaInfo = ArboldeBusquedaPorKm.search(nuevaInfo);
				}
				
				else
				{
					numeroBuscar = stoi(input.getString().c_str());
					nuevaInfo->setNEnemigos(numeroBuscar); 
					nuevaInfo = ArboldeBusquedaPorEnemigos.search(nuevaInfo);
			
				}
				if (nuevaInfo != nullptr)
					myscene->setInformacion(nuevaInfo);
				else
					myscene->setBuscando(false);
				eligio = false;
			}
		}

	}
	void Run(ALLEGRO_FONT *font)
	{ 
		bool d = myscene->update(font);
		
		if (d)
		{
			al_draw_scaled_bitmap(bmp, 0, 0, al_get_bitmap_width(bmp), al_get_bitmap_height(bmp),
				0, 0, width, height, 1);
			Buscar(font);
		}
	}
	
	void PersonajeCome() { myscene->PersonajeCome(); }
	void PersonajeTomarAgua() {
		myscene->PersonajeTomarAgua();
	}
	void PersonajeCompraBalas() {
		myscene->PersonajeCompraBalas();
	}
	~CJuego() {

		al_destroy_bitmap(imgpuntero);
		al_destroy_bitmap(bmp);

		delete myscene;
	}
	void CargarInfo() {
		myscene->CargarPlayer();
	}
	void GuardarInfo() {
		myscene->GuardarPlayer();
	}
	void GuardarMapa() {

		ofstream fs(file);
		fs.clear();
		fs << myscene->getMinBeacon();
		fs << " " << myscene->getMaxBeacon();
		fs << " " << myscene->getIndiceActual();
		Beacon *beaconguardar;

		for (int i = myscene->getMinBeacon(); i < myscene->getMaxBeacon(); i++) {

			if (i == myscene->getIndiceActual())
				beaconguardar = myscene->getInfoActual();
			else 
				beaconguardar = myscene->getBeacon(i);
			
			fs << " " << i;
			fs << " " << beaconguardar->getFueGenerado();
			fs << " " << beaconguardar->getNEnemigos();
			fs << " " << beaconguardar->getNRecursos();
			fs << " " << beaconguardar->getEsPortal();
			fs << " " << beaconguardar->getNBloques();
			fs << " " << beaconguardar->getIdUbicacion();
			
		}
		fs.flush();
		fs.close();
	
	
	}
};
