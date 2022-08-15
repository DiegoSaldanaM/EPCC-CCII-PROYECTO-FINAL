#ifndef __ARRMEJORAS_H__
#define __ARRMEJORAS_H__
#include"Mejora.h"
#include<vector>

class CArrMejoras
{
public:
	CArrMejoras();
	~CArrMejoras();
	void crearMejoras();
	void dibujarMejoras(Graphics^ g, Bitmap^ bmpMejoras, int** matriz);
	std::vector<CMejora*> getVector_Mejoras() {
		return vector_mejoras;
	}

private:
	std::vector<CMejora*>vector_mejoras;
};

CArrMejoras::CArrMejoras()
{

}

CArrMejoras::~CArrMejoras()
{
}

void CArrMejoras::crearMejoras()
{
	CMejora* nueva_mejora = new CMejora();
	vector_mejoras.push_back(nueva_mejora);
}

void CArrMejoras::dibujarMejoras(Graphics^ g, Bitmap^ bmpMejoras, int** matriz)
{
	for (int i{ 0 }; i < vector_mejoras.size(); i++)
	{
		vector_mejoras.at(i)->dibujar(g, bmpMejoras, matriz);
		vector_mejoras.at(i)->animar();
	}
}

#endif // !__ARRMEJORAS_H__
#pragma once
