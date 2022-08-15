#ifndef _Bomba_H_
#define _Bomba_H_
using namespace System::Drawing;
//Forma moderna, enum class
enum class Estado{ normal, explosion, desaparecer };
//enum Estado {normal, explosion, desaparecer};//Los 3 estados de la bomba

class CBomba
{
	public:
		CBomba(int x, int y) {
			this->x = x;
			this->y = y;
			estado = Estado::normal;

			ancho = 66 / 3;//Se divide segun el numero de imagenes, en el caso de la bomba son 3
			alto = 24;//Aqui no se divide porque la imagen es solo una fila
			
			indiceX = 0;//Inicializamos en 0, porque se hara el conteo de la imagen desde la izquierda
			tiempo_bf_explotar = 0;

			//	Datos iniciales para la explosion
			indiceEX = 0;
			indiceEY = 0;
			altoExplosion = 160 / 8;
			anchoExplosion = 80 / 8;

		};

		~CBomba() {};
		

		bool validarLugar(int xJugador, int yJugador, int **matriz)
		{
			if(matriz[yJugador/50][xJugador/50]==0 || matriz[yJugador/50][xJugador/50]==2)
				return true;
			else
				return false;
		}
		void DibujarBomba(Graphics^ g, Bitmap^ bmpBomba, int xJugador, int yJugador, int** matriz)
		{
			if (validarLugar(xJugador, yJugador, matriz) == true)
			{ 
				Rectangle porcionUsar = Rectangle(indiceX * ancho, 0, ancho, alto);
				Rectangle aumento = Rectangle(x, y, 40, 40);//Cada bloque de la matriz tiene tamaño
				g->DrawImage(bmpBomba, aumento, porcionUsar, GraphicsUnit::Pixel);
			}			
			if (tiempo_bf_explotar == 6) {
				estado = Estado::explosion;
			}
		}
		void animar()
		{
			if (indiceX >= 0 && indiceX < 2)
				indiceX++;
			else
			{
				tiempo_bf_explotar++;
				indiceX = 0;
			}
		}

		void DibujarExplosion(Graphics^ g, Bitmap^ bmpExplosionCentro, int** matriz) {

			Rectangle porcionUsarCentro = Rectangle(indiceEX * anchoExplosion, indiceEY * altoExplosion, anchoExplosion, altoExplosion); // indiceY=0
			Rectangle centro = Rectangle(x, y, 50, 50);
			g->DrawImage(bmpExplosionCentro, centro, porcionUsarCentro, GraphicsUnit::Pixel);
			if (matriz[y / 50][(x - 50) / 50] != 1) {
				Rectangle porcionUsarIzquierda = Rectangle(indiceEX * anchoExplosion, indiceEY + 2 * altoExplosion, anchoExplosion, altoExplosion); //indiceY = 2
				Rectangle izquierda = Rectangle(x - 50, y, 50, 50);
				g->DrawImage(bmpExplosionCentro, izquierda, porcionUsarIzquierda, GraphicsUnit::Pixel);

				if (matriz[y / 50][(x - 50) / 50] == 3) { matriz[y / 50][(x - 50) / 50] = 2; }
			}


			if (matriz[y / 50][(x + 50) / 50] != 1) {
				Rectangle porcionUsarDerecha = Rectangle(indiceEX * anchoExplosion, indiceEY + 4 * altoExplosion, anchoExplosion, altoExplosion); //indiceY = 4
				Rectangle derecha = Rectangle(x + 50, y, 50, 50);
				g->DrawImage(bmpExplosionCentro, derecha, porcionUsarDerecha, GraphicsUnit::Pixel);

				if (matriz[y / 50][(x + 50) / 50] == 3) { matriz[y / 50][(x + 50) / 50] = 2; }

			}
			if (matriz[y / 50][(x + 50) / 50] != 1) {
				Rectangle porcionUsarPuntaDerecha = Rectangle(indiceEX * anchoExplosion, indiceEY + 3 * altoExplosion, anchoExplosion, altoExplosion); //indiceY = 3
				Rectangle Puntaderecha = Rectangle(x + 100, y, 50, 50);
				g->DrawImage(bmpExplosionCentro, Puntaderecha, porcionUsarPuntaDerecha, GraphicsUnit::Pixel);

				if (matriz[y / 50][(x + 100) / 50] == 3 && matriz[y / 50][(x + 50) / 50] != 1)
				{

					matriz[y / 50][(x + 100) / 50] = 2;
				}
			}

			if (matriz[y / 50][(x - 50) / 50] != 1) {
				Rectangle porcionUsarPuntaIzquierda = Rectangle(indiceEX * anchoExplosion, indiceEY + 1 * altoExplosion, anchoExplosion, altoExplosion); //indiceY = 1
				Rectangle Puntaizquierda = Rectangle(x - 100, y, 50, 50);
				g->DrawImage(bmpExplosionCentro, Puntaizquierda, porcionUsarPuntaIzquierda, GraphicsUnit::Pixel);

				if (matriz[y / 50][(x - 100) / 50] == 3 && matriz[y / 50][(x - 50) / 50] != 1)
				{
					matriz[y / 50][(x - 100) / 50] = 2;
				}
			}

			Rectangle porcionUsarVerticales = Rectangle(indiceEX * anchoExplosion, indiceEY + 6 * altoExplosion, anchoExplosion, altoExplosion); //indiceY = 1
			Rectangle VerticalSuperior = Rectangle(x, y - 50, 50, 50);
			Rectangle VerticalInferior = Rectangle(x, y + 50, 50, 50);

			if (matriz[(y - 50) / 50][x / 50] != 1) { g->DrawImage(bmpExplosionCentro, VerticalSuperior, porcionUsarVerticales, GraphicsUnit::Pixel); }
			if (matriz[(y - 50) / 50][x / 50] == 3) { matriz[(y - 50) / 50][x / 50] = 2; }
			if (matriz[(y + 50) / 50][x / 50] != 1) { g->DrawImage(bmpExplosionCentro, VerticalInferior, porcionUsarVerticales, GraphicsUnit::Pixel); }
			if (matriz[(y + 50) / 50][x / 50] == 3) { matriz[(y + 50) / 50][x / 50] = 2; }


			if (matriz[(y - 50) / 50][x / 50] != 1) {
				Rectangle porcionUsarPuntaSuperior = Rectangle(indiceEX * anchoExplosion, indiceEY + 5 * altoExplosion, anchoExplosion, altoExplosion); //indiceY = 5
				Rectangle PuntaSuperior = Rectangle(x, y - 100, 50, 50);
				g->DrawImage(bmpExplosionCentro, PuntaSuperior, porcionUsarPuntaSuperior, GraphicsUnit::Pixel);

				if (matriz[(y - 100) / 50][x / 50] == 3 && matriz[(y - 50) / 50][x / 50] != 1) { matriz[(y - 100) / 50][x / 50] = 2; }
			}


			if (matriz[(y + 50) / 50][x / 50] != 1) {
				Rectangle porcionUsarPuntaInferior = Rectangle(indiceEX * anchoExplosion, indiceEY + 7 * altoExplosion, anchoExplosion, altoExplosion); //indiceY = 7
				Rectangle PuntaInferior = Rectangle(x, y + 100, 50, 50);
				g->DrawImage(bmpExplosionCentro, PuntaInferior, porcionUsarPuntaInferior, GraphicsUnit::Pixel);
				if (matriz[(y + 100) / 50][x / 50] == 3 && matriz[(y + 50) / 50][x / 50] != 1) {
					matriz[(y + 100) / 50][x / 50] = 2;
				}
			}
		}

		void animarExplosion() {
			if (indiceEX >= 0 && indiceEX < 3) {
				indiceEX++;
			}
			else
			{
				estado = Estado::desaparecer;
			}
		}
		Estado getEstado() {
			return estado;
		}

		int getX() {
			return x;
		}
		int getY() {
			return y;
		}

	private://Datos de la explocion
		int anchoExplosion;
		int altoExplosion;
		int indiceEX;
		int indiceEY;

	private://Datos de la bomba
		int x;
		int y;

		int ancho;
		int alto;
		int indiceX;//indice en Y no es necesario, porque la imagen de la bomba solo avanza segun el indiceX, muy diferente a la imagen del personaje

		int tiempo_bf_explotar;

		Estado estado;
};

#endif // !_Bomba_H_

