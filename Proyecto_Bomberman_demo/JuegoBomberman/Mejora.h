#ifndef __MEJORA_H__
#define __MEJORA_H__
#include<ctime>
#include<stdlib.h>
using namespace System::Drawing;

class CMejora
{
public:
	CMejora();
	~CMejora();
	void dibujar(Graphics^ g, Bitmap^ bmpMejoras, int** matriz);
	void animar();

private:
	int i;//Fila donde estara la mejora
	int j;//Columna donde estara la mejora

	int indiceX;
	int indiceY;

	int ancho;
	int alto;

	int tipo_de_mejora;

	bool ubicado;
};

CMejora::CMejora()
{
	srand(time(NULL));
	tipo_de_mejora = rand() % 5 + 1;
	ubicado = false;
	i = rand() % 13 + 1;//i vale desde 1 hasta el 13, 13 es el numero de filas
	j = rand() % 15 + 1;//j vale desde 1 hasta el 15, 15 es el numero de columnas

	ancho = 193 / 12;
	alto = 96 / 6;

	indiceX = 0;
	indiceY = 0;
}

CMejora::~CMejora()
{
}

void CMejora::dibujar(Graphics^ g, Bitmap^ bmpMejoras, int** matriz)
{
	Rectangle porcionUsar = Rectangle(indiceX * ancho, indiceY * alto, ancho, alto);

	while (ubicado == false)
	{
		if (matriz[i][j] == 3)
		{
			ubicado = true;
		}
		else//Para que vaya buscando el item
		{
			if (j < 17)
			{
				i++;
				if (i == 14)
				{
					i = 0;
					j++;
				}
			}
		}

		Rectangle aumento = Rectangle(j * 50, i * 50, ancho * 3.125, alto * 3.125);//Multiplicamos por 3.125 para que no se vea el borde del item
		g->DrawImage(bmpMejoras, aumento, porcionUsar, GraphicsUnit::Pixel);
	}
}

void CMejora::animar()
{
	switch (tipo_de_mejora)
	{
	case 1://Bomba adicional
		indiceX = 0;//PosX de la bomba en la imagen
		if (indiceY >= 0 && indiceY < 1)
			indiceY++;
		else
			indiceY = 0;
		break;

	case 2://Mover bomba
		indiceX = 4;//PosX de moverbomba en la imagen
		if (indiceY >= 0 && indiceY < 1)
			indiceY++;
		else
			indiceY = 0;
		break;

	case 3://Calaver, perder vida
		indiceX = 5;//PosX de la Calavera en la imagen
		if (indiceY >= 0 && indiceY < 1)
			indiceY++;
		else
			indiceY = 0;
		break;

	case 4://Patines
		indiceX = 8;//PosX de los patines en la imagen
		if (indiceY >= 0 && indiceY < 1)
			indiceY++;
		else
			indiceY = 0;
		break;
	case 5://Vidas
		indiceX = 9;//PosX del corazon en la imagen
		if (indiceY >= 0 && indiceY < 1)
			indiceY++;
		else
			indiceY = 0;
		break;
	}
}

#endif // !__MEJORA_H__
#pragma once
