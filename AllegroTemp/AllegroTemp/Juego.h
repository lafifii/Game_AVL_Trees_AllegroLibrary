#pragma once
#pragma once

class CJuego {
	Scene myscene;/*
				  AVLTree<Beacon> ArbolBusquedaRecursos;
				  AVLTree<Beacon> ArbolBusquedaPorKM;
				  AVLTree<Beacon> ArbolBusquedaPorEnemigo;
				  AVLTree<Beacon> ArbolBusquedaPorBloques;
				  AVLTree<Beacon> ArbolBusquedaPorDireccion;*/
public:
	CJuego() {
		/*ArbolBusquedaRecursos = AVLTree<Beacon>(2);
		ArbolBusquedaPorKM = AVLTree<Beacon>(4);
		ArbolBusquedaPorEnemigo = AVLTree<Beacon>(1);
		ArbolBusquedaPorDireccion = AVLTree<Beacon>(5);
		ArbolBusquedaPorBloques = AVLTree<Beacon>(3);*/
		myscene = Scene();
	}
	void Disparar()
	{
		myscene.Disparar();
	}
	void BuscarEscenarioPorCriterio()
	{

	}
	void Run(ALLEGRO_FONT *font)
	{
		myscene.update(font);

	}
	~CJuego() {
	}
};
