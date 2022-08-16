#ifndef __ARRBOMBAS_H__
#define __ARRBOMBAS_H__
#include <vector>
#include"Bomba.h"

class CArrBombas
{
	public:
		CArrBombas() {
			totalBombas = 1;
		}
		~CArrBombas() {}
		void crear_Bomba(int x, int y) {
			if (arregloBombas.size() < totalBombas) {
				CBomba* nueva_bomba = new CBomba(x, y);
				arregloBombas.push_back(nueva_bomba);
			}			
		}
		void dibujar_una_bombas(Graphics^g, Bitmap^bmpBomba, Bitmap^bmpExplosion, int xJugador, int yJugador, int **matriz	) {
			for (int i{ 0 }; i < arregloBombas.size(); i++) 
			{
				switch (arregloBombas.at(i)->getEstado())
				{
					case Estado::normal:
						arregloBombas.at(i)->DibujarBomba(g, bmpBomba, xJugador, yJugador, matriz);
						arregloBombas.at(i)->animar();
						break;
					case Estado::explosion:
						arregloBombas.at(i)->DibujarExplosion(g, bmpExplosion, matriz);
						arregloBombas.at(i)->animarExplosion();
						break;
					case Estado::desaparecer:
						arregloBombas.erase(arregloBombas.begin() + i);
						break;
				}
			}
		}

		vector<CBomba*> getarregloBombas() {
			return arregloBombas;
		}		

	private:
		vector<CBomba*> arregloBombas;
		int totalBombas;
};


#endif // !__ARRBOMBAS_H__
