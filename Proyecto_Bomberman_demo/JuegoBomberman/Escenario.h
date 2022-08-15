#ifndef _ESCENARIO_H_
#define _ESCENARIO_H_
#include<ctime>
#include<stdlib.h>
#define filas 15//definimos el numero de filas
#define columnas 17//definimos el numero de columnas
using namespace System::Drawing;

class CEscenario
{
	public:
		CEscenario(){
			matriz = new int*[filas];//Liberamos espacio
		}
		~CEscenario() {
		}
		void generarMatriz() {
			srand(time(NULL()));
			for (int i{0}; i < filas; i++) {//Liberamos espacio
				matriz[i] = new int[columnas];
			}

			for (int i{ 0 }; i < filas; i++) {				
				for (int j{ 0 }; j < columnas; j++) {
					if (i==0 || j==0 || i==filas-1 || j==columnas-1) //Bloques fijos del limite del mapa
						matriz[i][j] = 1;
					else
					{
						if(i%2==0 && j%2==0)//Bloques fijos dentro del mapa
						{
							matriz[i][j] = 1;
						}
						else
						{
							//Area de inicio
							if ((i == 1 && (j == 1 || j == 2)) || (i == 2 && j == 1) || (i == filas - 2 && (j == columnas - 2 || j == columnas - 3)) || (i == filas - 3 && j == columnas - 2))//Area de spawn
								matriz[i][j] = 0;
							else//Zonas que seran libre o tendran un bloque destruible, 2 es libre, 3 es un bloque destruible
								matriz[i][j] = rand() % 2 + 2;
						}
					}
				}
			}
		}

		void pintarBase(Graphics^ g, Bitmap^ bmpBase) {
			int x{0}, y{ 0 };
			for (int i{ 0 }; i < filas; i++) {				
				x = 0;
				for (int j{ 0 }; j < columnas; j++) {
					if (matriz[i][j] == 0 || matriz[i][j] == 2)
						g->DrawImage(bmpBase, x, y, 50, 50);
					x += 50;
				}
				y += 50;
			}
		}

		void pintarMatriz(Graphics^ g, Bitmap^ bmpSolido, Bitmap^ bmpDestruible) {
			int x{ 0 }, y{ 0 };
			for (int i{ 0 }; i < filas; i++) {
				x = 0;
				for (int j{ 0 }; j < columnas; j++) {
					if (matriz[i][j] == 1) 
						g->DrawImage(bmpSolido, x, y, 50, 50);
					else{
						if (matriz[i][j] == 3)
							g->DrawImage(bmpDestruible, x, y, 50, 50);
					}
					x += 50;
				}
				y += 50;
			}
		}

		int** getMatriz() {
			return matriz;
		}

	private:
		int** matriz;
};

#endif // !1

