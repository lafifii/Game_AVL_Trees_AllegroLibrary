#pragma once

class Scene {

	Beacon* Informacion;
	CPlayer player;

	AVLTree <Beacon*> ArboldeBeacons;
	AVLTree <Beacon*> ArboldeBusquedaPorEnemigos;
	AVLTree <Beacon*> ArboldeBusquedaPorRecursos;
	AVLTree <Beacon*> ArboldeBusquedaPorKm;
	AVLTree <Beacon*> ArboldeBusquedaPorUbicacion;
	AVLTree <Beacon*> ArboldeBusquedaPorNBloques;

	int indice, nfondo, maxBeacons, minBeacon;
	bool Buscando, eligio;


	ALLEGRO_BITMAP *ie;
	ALLEGRO_BITMAP *ib, *ib2;

	ALLEGRO_BITMAP *icoin;

	ALLEGRO_BITMAP *ifood;
	ALLEGRO_BITMAP *iagua;
	ALLEGRO_BITMAP *iportal;
	ALLEGRO_BITMAP *ibala, *fondo,*ie2, *fondo2,*fondo3, *fondo4;
	ALLEGRO_BITMAP *iburbuja;

public:

	Scene() {

		ie = al_load_bitmap("img/TempEn.png");
		ie2 = al_load_bitmap("img/TempEn2.png");
		ib = al_load_bitmap("img/piso.png");
		ib2 = al_load_bitmap("img/piso2.png");
		fondo2 = al_load_bitmap("img/fondo2.jpg");
		fondo3 = al_load_bitmap("img/fondo3.jpg");
		fondo4 = al_load_bitmap("img/fondo4.jpg");
		fondo = al_load_bitmap("img/bg.png");

		icoin = al_load_bitmap("img/coin.png");
		ifood = al_load_bitmap("img/food.png");
		iagua = al_load_bitmap("img/agua.png");
		iportal = al_load_bitmap("img/portal.png");
		ibala = al_load_bitmap("img/balita.png");

		iburbuja = al_load_bitmap("img/brujula.png");

		Buscando = eligio = false;

		player = CPlayer(50, height / 2, 40, 40);
		player.setImagePlayer(al_load_bitmap("img/TempPlayer.png"), al_load_bitmap("img/TempPlayer2.png"));
		player.setImagePistola(al_load_bitmap("img/balai.png"), al_load_bitmap("img/balad.png"));
		player.setImageBalita(al_load_bitmap("img/balita.png"));

		nfondo = minBeacon = maxBeacons = 0;


		indice = 0;
		Informacion = new Beacon();
		ArboldeBeacons = AVLTree<Beacon*>();

	}
	//Este usa para cargar partida
	//Aqui se carga con un txt2 donde solo se guarde info del personaje o algo asi
	Scene(int index) {

		ie = al_load_bitmap("img/TempEn.png");
		ie2 = al_load_bitmap("img/TempEn2.png");
		ib = al_load_bitmap("img/piso.png");
		ib2 = al_load_bitmap("img/piso2.png");
		fondo2 = al_load_bitmap("img/fondo2.jpg");
		fondo3 = al_load_bitmap("img/fondo3.jpg");
		fondo4 = al_load_bitmap("img/fondo4.jpg");
		fondo = al_load_bitmap("img/bg.png");

		icoin = al_load_bitmap("img/coin.png");
		ifood = al_load_bitmap("img/food.png");
		iagua = al_load_bitmap("img/agua.png");
		iportal = al_load_bitmap("img/portal.png");
		ibala = al_load_bitmap("img/balita.png");

		Buscando = eligio = false;

		//Llenar info del personaje con los valores del guardado somehow
		player = CPlayer(50, height / 2, 40, 40);
		player.setImagePlayer(al_load_bitmap("img/TempPlayer.png"), al_load_bitmap("img/TempPlayer2.png"));
		player.setImagePistola(al_load_bitmap("img/balai.png"), al_load_bitmap("img/balad.png"));

		nfondo = minBeacon = maxBeacons = 0;
		indice = index;
		Informacion = new Beacon();
		ArboldeBeacons = AVLTree<Beacon*>();

	}
	void AddArbol(Beacon *o) {

		ArboldeBeacons.add(o);
		maxBeacons++;
	}
	void Inicializar_Valores() {

		Beacon *buscar = new Beacon(indice);
		Informacion = ArboldeBeacons.search(buscar);
		GenerarEscena();
	}

	~Scene() {

		al_destroy_bitmap(ie);
		al_destroy_bitmap(ie2);
		al_destroy_bitmap(ib);
		al_destroy_bitmap(ib2);

		al_destroy_bitmap(icoin);
		al_destroy_bitmap(ifood);
		al_destroy_bitmap(iagua);
		al_destroy_bitmap(iportal);
		al_destroy_bitmap(ibala);

		al_destroy_bitmap(fondo);

		al_destroy_bitmap(iburbuja);

		/*while (!vfondos.empty()) {

		al_destroy_bitmap(vfondos[0]);
		vfondos.erase(vfondos.begin());
		}*/
	}

	Beacon* SiguienteBeacon()
	{

		if (indice < minBeacon) {
			Beacon *nuevo = new Beacon(indice);
			ArboldeBeacons.add(nuevo);
			minBeacon--;
		}
		if (indice >= maxBeacons)
		{
			Beacon *nuevo = new Beacon(indice);
			ArboldeBeacons.add(nuevo);
			maxBeacons++;
		}

		Beacon *buscar = new Beacon(indice);
		return ArboldeBeacons.search(buscar);
	}

	void CambiarEscena(int a) {

		if (a == -1)
		{
			nfondo--;
			indice--;
			Informacion = SiguienteBeacon();
			player.setX(width);
		}
		else
		{
			nfondo++;
			indice++;
			Informacion = SiguienteBeacon();
			player.setX(0);
		}

		GenerarEscena();
	}

	void GenerarEscena() {

		
		player.CambioEscena();
		Informacion->GenerarEscenario();
		if (indice % 2 == 0)
			Informacion->update(fondo, ie, ie2, ib, ib2, icoin, ifood, iagua, ibala, iportal);
		if (indice % 3 == 0)
			Informacion->update(fondo2, ie, ie2, ib, ib2, icoin, ifood, iagua, ibala, iportal);
		if (indice % 5 == 0)
			Informacion->update(fondo3, ie, ie2, ib, ib2, icoin, ifood, iagua, ibala, iportal);
		if (indice % 2 != 0 && indice % 3 != 0 && indice % 5 != 0)
			Informacion->update(fondo4, ie, ie2, ib, ib2, icoin, ifood, iagua, ibala, iportal);
	}

	bool update(ALLEGRO_FONT *font) {


		if (!Buscando) {

			if (indice % 2 == 0)
				Informacion->update(fondo, ie, ie2, ib, ib2, icoin, ifood, iagua, ibala, iportal);
			if (indice % 3 == 0)
				Informacion->update(fondo2, ie, ie2, ib, ib2, icoin, ifood, iagua, ibala, iportal);
			if (indice % 5 == 0)
				Informacion->update(fondo3, ie, ie2, ib, ib2, icoin, ifood, iagua, ibala, iportal);
			if(indice%2!=0 && indice%3!=0 && indice%5!=0)
				Informacion->update(fondo4, ie, ie2, ib, ib2, icoin, ifood, iagua, ibala, iportal);

			pintarTablero(font);

			player.applyBlockPhysics(Informacion->getBloques());

			if (player.getX() <= 0)
				CambiarEscena(-1);
			else if (player.getX() >= width)
				CambiarEscena(1);

			if (player.getY() > height) player.setY(0);
			else if (player.getY() < 0) player.setY(height);

			player.update();


			int indexRec = player.ColisionRecurso(Informacion->getRecursos());
			int indexEn = player.ColisionMalos(Informacion->getEnemigos());


			if (indexRec != -1)
			{
				if (Informacion->getRecursos()[indexRec].getTipo() == 5)
					Buscando = true;
				Informacion->EliminarRecurso(indexRec);
			
			}
			if (indexEn != -1)
				Informacion->EliminarEnemigo(indexEn);

		}
		return Buscando;
	}
	void setBuscando(bool bs) { Buscando = bs; }
	void setInformacion(Beacon *o) {
		indice = o->getIndex();
		Informacion = o;
		Buscando = false;
		GenerarEscena();
	}
	void pintarTablero(ALLEGRO_FONT *font) {

		string s1 = "Energia: " + to_string(player.getEnergia());
		string s2 = "Agua: " + to_string(player.getAgua());
		string s3 = "Alimentos: " + to_string(player.getComida());
		string s4 = "Monedas: " + to_string(player.getMonedas());

		string is1 = "Distancia: " + to_string(Informacion->getDistancia());
		string is2 = "Numero Enemigos: " + to_string(Informacion->getNEnemigos());
		string is3 = "Numero Recursos: " + to_string(Informacion->getNRecursos());
		string is4 = "Numero Bloques: " + to_string(Informacion->getNBloques());
		

		al_draw_text(font, al_map_rgb(0, 0, 255), width / 2, 50, ALLEGRO_ALIGN_CENTER, s1.c_str());
		al_draw_text(font, al_map_rgb(0, 0, 255), width / 2, 70, ALLEGRO_ALIGN_CENTER, s2.c_str());
		al_draw_text(font, al_map_rgb(0, 0, 255), width / 2, 90, ALLEGRO_ALIGN_CENTER, s3.c_str());
		al_draw_text(font, al_map_rgb(0, 0, 255), width / 2, 110, ALLEGRO_ALIGN_CENTER, s4.c_str());

		al_draw_text(font, al_map_rgb(0, 0, 255), width-80, 30, ALLEGRO_ALIGN_CENTER, Informacion->getUbicacion().c_str());
		al_draw_text(font, al_map_rgb(0, 0, 255), width - 80, 50, ALLEGRO_ALIGN_CENTER, is1.c_str());
		al_draw_text(font, al_map_rgb(0, 0, 255), width - 80, 70, ALLEGRO_ALIGN_CENTER, is2.c_str());
		al_draw_text(font, al_map_rgb(0, 0, 255), width - 80, 90, ALLEGRO_ALIGN_CENTER, is3.c_str());
		al_draw_text(font, al_map_rgb(0, 0, 255), width - 80, 110, ALLEGRO_ALIGN_CENTER, is4.c_str());


		al_draw_scaled_bitmap(iburbuja, 0, 0, 30, 30, width - 170, 10, 30, 30, 1);

	}

	void Disparar() {
		player.DisparoDer();
	}

	void PersonajeTomarAgua() { player.TomarAgua(); }
	void PersonajeCome() { player.Comer(); }
	void PersonajeCompraBalas() { player.Recargar(); }
};