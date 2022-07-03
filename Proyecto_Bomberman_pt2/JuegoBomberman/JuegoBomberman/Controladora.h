#ifndef _CONTROLADORA_H_
#define _CONTROLADORA_H_
#include"Escenario.h"
#include"Jugador.h"
#include "ArrBombas.h"

class CControladora
{
	public:
		CControladora() {
			oEscenario = new CEscenario();
			oJugador = new CJugador(50,50);
			oArrBombas = new CArrBombas();
		}
		~CControladora() {}

		void cambiarNivel()
		{
			oEscenario->generarMatriz();
		}

		void AgregarBomba() {
			oArrBombas->crear_Bomba(oJugador->getX(), oJugador->getY());
		}

		void dibujar(Graphics^ g, Bitmap^bmpBase, Bitmap^ bmpSolido, Bitmap^ bmpBomba, Bitmap^ bmpExplosion, Bitmap^ bmpDestruible, Bitmap^bmpJugador)
		{
			oEscenario->pintarBase(g,bmpBase);
			oEscenario->pintarMatriz(g, bmpSolido, bmpDestruible);
			oJugador->moverJugador(g, bmpJugador, oEscenario->getMatriz()); 
			oArrBombas->dibujar_una_bombas(g, bmpBomba, bmpExplosion, oJugador->getX(), oJugador->getY(), oEscenario->getMatriz());
		}
		CJugador* getoJugador() {
			return oJugador;
		}
	private:
		CEscenario* oEscenario;
		CJugador* oJugador;
		CArrBombas* oArrBombas;
};

#endif
