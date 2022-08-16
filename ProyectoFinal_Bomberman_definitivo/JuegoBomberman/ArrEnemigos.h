#ifndef __ARRENEMIGOS_H__
#define __ARRENEMIGOS_H__
#include "Enemigo.h"
#include<vector>
using namespace std;

class CArrEnemigos
{
public:
	CArrEnemigos() {
		arregloEnemigos = vector<CEnemigo*>();
	}
	~CArrEnemigos(){}
	void crearEnemigos();
	void dibujarEnemigo(Graphics^ g, Bitmap^ bmpEnemigo, int** matriz);

	vector<CEnemigo*> getarregloEnemigos() {
		return arregloEnemigos;
	}
	
private:
	vector<CEnemigo*> arregloEnemigos;
};

void CArrEnemigos::crearEnemigos() {
	CEnemigo* nuevo = new CEnemigo();
	arregloEnemigos.push_back(nuevo);	
}

void CArrEnemigos::dibujarEnemigo(Graphics^ g, Bitmap^ bmpEnemigo, int** matriz)
{
	{
		for (int i{ 0 }; i < arregloEnemigos.size(); ++i)
		{
			arregloEnemigos.at(i)->dibujarEnemigo(g, bmpEnemigo, matriz);
			arregloEnemigos.at(i)->animarEnemigo();
		}
	}
}

#endif // !__ARRENEMIGOS_H__

#pragma once
