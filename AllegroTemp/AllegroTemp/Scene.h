#pragma once

class Scene {

	Beacon Informacion;
	CPlayer player;
	vector<CBlock> vb;
	vector<CEnemy> ve;
	vector<Recurso> vr;
	AVLTree <Beacon> ArboldeBeacons;
	vector<ALLEGRO_BITMAP*> vfondos;
	int indice, nfondo, maxBeacons;
public:

	Scene() {

		player = CPlayer(50, height / 2, 30, 30, al_load_bitmap("TempPlayer.png"));
		nfondo = 0;
		maxBeacons = 10;
		vfondos.push_back(al_load_bitmap("fondo1.png"));
		//CUando subo fondo2 y fondo3 me sale error idk // son imagenes muy pequeñas (creo)
		//vfondos.push_back(al_load_bitmap("fondo2.png"));
		//vfondos.push_back(al_load_bitmap("fondo3.png"));

		indice = 0;
		ArboldeBeacons = AVLTree<Beacon>();



		for (int i = 0; i < maxBeacons; i++)
			ArboldeBeacons.add(Beacon(i));

		Informacion = ArboldeBeacons.search(0);
		GenerarEscena();
	}

	~Scene() {

		while (!vfondos.empty()) {

			al_destroy_bitmap(vfondos[0]);
			vfondos.erase(vfondos.begin());
		}
	}

	Beacon SiguienteBeacon() {

		if (indice < 0)
			ArboldeBeacons.add(Beacon(indice));
		if (indice >= maxBeacons)
		{
			ArboldeBeacons.add(Beacon(indice));
			maxBeacons++;
		}
		return ArboldeBeacons.search(indice);
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

		vb.clear();
		vr.clear();
		ve.clear();

		//Generando enemigos
		for (int i = 0; i < Informacion.getNEnemigos(); i++)
			ve.push_back(CEnemy(80 * i, 100, 50, 50, al_load_bitmap("TempEn.png")));
		//generando bloques
		for (int i = 0; i < Informacion.getNBloques(); i++)
		{
			if (i % 2 == 0)
				vb.push_back(CBlock(0 + i * 100, 400, 200, 50, al_load_bitmap("piso.png")));
			else
				vb.push_back(CBlock(400 + i * 100, 250, 200, 50, al_load_bitmap("piso.png")));
		}
		srand(time(NULL));
		//Generando recurso
		for (int i = 0; i < Informacion.getNRecursos() - 1; i++)
			vr.push_back(Recurso(1 + rand() % 3));
		if (Informacion.PortalBusqueda())
			vr.push_back(Recurso(4));
		else
			vr.push_back(Recurso(1 + rand() % 3));

	}

	void update(ALLEGRO_FONT *font) {

		if (nfondo < 0)
			nfondo = vfondos.size() - 1;
		if (nfondo > vfondos.size() - 1)
			nfondo = 0;

		al_draw_bitmap(vfondos[nfondo], 0, 0, 0);

		string s1 = "Energia: " + to_string(player.getEnergia());
		string s2 = "Agua: " + to_string(player.getAgua());
		string s3 = "Alimentos: " + to_string(player.getComida());
		string s4 = "Monedas: " + to_string(player.getMonedas());

		al_draw_text(font, al_map_rgb(0, 0, 255), width / 2, 50, ALLEGRO_ALIGN_CENTER, s1.c_str());
		al_draw_text(font, al_map_rgb(0, 0, 255), width / 2, 70, ALLEGRO_ALIGN_CENTER, s2.c_str());
		al_draw_text(font, al_map_rgb(0, 0, 255), width / 2, 90, ALLEGRO_ALIGN_CENTER, s3.c_str());
		al_draw_text(font, al_map_rgb(0, 0, 255), width / 2, 110, ALLEGRO_ALIGN_CENTER, s4.c_str());

		if (player.getX() <= 0)
			CambiarEscena(-1);
		else if (player.getX() >= width)
			CambiarEscena(1);

		if (player.getY() > height) player.setY(0);

		player.update();
		player.applyBlockPhysics(vb);

		for (auto x : ve)
			x.update();
		for (auto x : vb)
			x.update();
		for (auto x : vr)
			x.update();

		int indexEn = player.ColisionMalos(ve);
		int indexRec = player.ColisionRecurso(vr);

		if (indexEn != -1) ve.erase(ve.begin() + indexEn);
		if (indexRec != -1) vr.erase(vr.begin() + indexRec);

		al_draw_filled_circle(mouseX, mouseY, 3, al_map_rgb(50, 50, 50));
	}

	void Disparar() {
		player.Disparar();
	}
};