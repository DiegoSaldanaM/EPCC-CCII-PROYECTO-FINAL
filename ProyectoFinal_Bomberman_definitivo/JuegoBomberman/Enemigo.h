#ifndef __ENEMIGO__H__
#define __ENEMIGO__H__
#define star_area 1
#define free_block 2
#define destructible_block 3
#include <ctime>
#include <cstdlib>
#include"ArrBombas.h"
using namespace System::Drawing;
enum Estado_Enemigo{Eliminado, Normal};//PARA VERIFICAR SI EL ENEMIGO ESTA AUN EN EL MAPA O FUE ELIMINADO

class CEnemigo
{
public:
	CEnemigo() {
		srand(time(NULL));		
		fila = rand() % f_jugable+1;//13
		columna = rand() % c_jugable + 2;//14
		posX = 715;
		posY = 650;
		dx = 5;
		indiceX = 0;
		indiceY = 0;
		ancho_imag = 96 / 6;//DIVIDIMOS ENTRE 6, PORQUE LA IMAGEN ESTA DIVIDIDA EN 6 SECCIONES
		alto_imag = 16;
		ubicado = false;
		estado = Normal;		
	}
	~CEnemigo() {}

	void animarEnemigo();
	void dibujarEnemigo(Graphics ^g, Bitmap ^bmpEnemigo, int **matriz);
	int borrarEnemigo();
	Rectangle retornarRectangulo() {
		return Rectangle(posX, posY, 50, 50);
	}

protected:	
	int posX;
	int posY;
	//DECLARAMOS i Y j para ayudar a que los enemigos no aparescan en un bloque destruible y asi solo aparescan en un bloque libre
	int fila;
	int columna;
	int f_jugable = 13;//El numero de filas jugables para un enemigo son 13, ya que la primer fila arriba y la ultima de abajo son el limite del mapa
	int c_jugable = 13;
	//DESPLAZAMIENTO EN x E y
	int dx;
	int dy;
	//CON ESTO INDICAMOS QUE SECCION DE LA IMAGEN VA A TOMAR, PARA ASI LOGRAR LA ANIMACION
	int indiceX;
	int indiceY;
	//EL ANCHO Y ALTO DE LA IMAGEN
	int ancho_imag;
	int alto_imag;
	
	bool ubicado;

	Estado_Enemigo estado;
};

void CEnemigo::animarEnemigo() {
	if (indiceX >= 0 && indiceX < 5)
		indiceX++;
	if (indiceX == 5) {
		while (indiceX != 0)
			indiceX--;
	}
}

void CEnemigo::dibujarEnemigo(Graphics^ g, Bitmap^ bmpEnemigo, int** matriz) {
	//Aqui indicamos que seccion de la imagen vamos a usar, de ahi el nombre "porcionUsar"
	Rectangle porcionUsar = Rectangle(indiceX * ancho_imag, indiceY * alto_imag, ancho_imag, alto_imag);
	while ((matriz[fila][columna-1] != free_block || matriz[fila][columna] != free_block || matriz[fila][columna+1] != free_block) && fila<14 && ubicado == false) {
		//Con eso nos aseguramos que verifique todas las columnas para luego hacer lo mismo con la siguiente fila
		columna++;
		if (columna == 15) {
			fila++;
			columna = 0;
		}
		if (fila >= 14)
			break;
		//Una vez termino de examinar el mapa, le asigna la posicion de aparicion al enemigo
		posX = fila * 50;
		posY = columna * 50;
	}
	//Dibujamos un rectangulo donde estara la imagen del enemigo
	//Ya que los bloques son de 50x50, el enemigo sera un poco mas pequeño, 40x40
	Rectangle Aumento = Rectangle(posX, posY, 40, 40);
	g->DrawImage(bmpEnemigo, Aumento, porcionUsar, GraphicsUnit::Pixel);
	ubicado = true;
	posX += dx;
	if ((matriz[posY / 50][(posX + 50) / 50] == destructible_block || matriz[posY / 50][(posX + 50) / 50] == star_area) || 
		matriz[posY/50][(posX-10)/50] == destructible_block || matriz[posY / 50][(posX - 10) / 50] == star_area) {
		dx *= -1;
	}	
}

int CEnemigo::borrarEnemigo()
{	
	return estado = Eliminado;;
	
}


#endif // !__ENEMIGO__H__
#pragma once
