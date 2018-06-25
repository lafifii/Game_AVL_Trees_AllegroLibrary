#pragma once
#include "Input.h"

class CJuego {

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

		for (int i = 0; i < 1000; i++)
		{
			Beacon *o = new Beacon(i);
			myscene->AddArbol(o);
			ArboldeBusquedaPorEnemigos.add(o);
			ArboldeBusquedaPorRecursos.add(o);
			ArboldeBusquedaPorKm.add(o);
			ArboldeBusquedaPorUbicacion.add(o);
			ArboldeBusquedaPorNBloques.add(o);

		}
		myscene->Inicializar_Valores();
	}
	//Este usa para cargar partida
	/*
		Para guardar guarda lit todos los beacons el indice menor en el que se quedo el personaje y el maxbeacons del scene
		entonces para cargar tomas estos y llenas todo 
		cada beacon tiene el bool de YaGenerado algo asi,, esto es super importante que se guarde para que no se genere otra vez
	*/
	CJuego(int index, int inmenor, int nmayor) {

		bmp = al_load_bitmap("img/tele.jpg");
		punteroEleccion.x = 290;
		punteroEleccion.y = 70;
		myscene = new Scene(index);
		eligio = false;
		ArboldeBusquedaPorEnemigos = AVLTree<Beacon*>(1);
		ArboldeBusquedaPorRecursos = AVLTree<Beacon*>(2);
		ArboldeBusquedaPorKm = AVLTree<Beacon*>(3);
		ArboldeBusquedaPorUbicacion = AVLTree<Beacon*>(4);
		ArboldeBusquedaPorNBloques = AVLTree<Beacon*>(5);
		imgpuntero = al_load_bitmap("img/punt.png");

		for (int i = inmenor; i < nmayor; i++)
		{
			Beacon *o = new Beacon(i);
			LlenarInfoDeBeacon(o);
			myscene->AddArbol(o);
			ArboldeBusquedaPorEnemigos.add(o);
			ArboldeBusquedaPorRecursos.add(o);
			ArboldeBusquedaPorKm.add(o);
			ArboldeBusquedaPorUbicacion.add(o);
			ArboldeBusquedaPorNBloques.add(o);

		}
		myscene->Inicializar_Valores();
	}
	void LlenarInfoDeBeacon(Beacon *o) {
	//Aui abre el archivo de la info de los beacons y mapas
	//le pones set fue generado y todo eso y luego ya lo agregas al arbol :) que sean dos txt uno con solo info del player y otro con info del mapa que es el que usaremos aqui
	//lees las 5 primeras lineas o algo asi...te dejo un txt de como podrias guardar la info
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
};
