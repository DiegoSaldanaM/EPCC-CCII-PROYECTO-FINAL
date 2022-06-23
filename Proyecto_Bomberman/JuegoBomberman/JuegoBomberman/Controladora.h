#ifndef _CONTROLADORA_H_
#define _CONTROLADORA_H_
#include"Escenario.h"
#include"Jugador.h"

class CControladora
{
	public:
		CControladora() {
			oEscenario = new CEscenario();
			oJugador = new CJugador(50,50);
		}
		~CControladora() {}

		void cambiarNivel()
		{
			oEscenario->generarMatriz();
		}

		void dibujar(Graphics^ g, Bitmap^bmpBase, Bitmap^ bmpSolido, Bitmap^ bmpDestruible, Bitmap^bmpJugador) 
		{
			oEscenario->pintarBase(g,bmpBase);
			oEscenario->pintarMatriz(g, bmpSolido, bmpDestruible);
			oJugador->moverJugador(g, bmpJugador, oEscenario->getMatriz()); 

		}
		CJugador* getoJugador() {
			return oJugador;
		}
	private:
		CEscenario* oEscenario;
		CJugador* oJugador;
};

#endif
