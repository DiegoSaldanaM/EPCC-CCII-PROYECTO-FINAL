#ifndef __CONTROLADORA_H__
#define __CONTROLADORA_H__
#include"Escenario.h"
#include"Jugador.h"
#include "ArrBombas.h"
#include "ArrEnemigos.h"
#include "ArrMejoras.h"

class CControladora
{
	public:
		CControladora() {
			oEscenario = new CEscenario();
			oJugador = new CJugador(50,50);
			oArrBombas = new CArrBombas();
			oArrMejoras = new CArrMejoras();
			oArrEnemigos = new CArrEnemigos();			
			nivel = 1;
		}
		~CControladora() {}

		void cambiarNivel()
		{
			oEscenario->generarMatriz();
		}

		void AgregarBomba() {
			oArrBombas->crear_Bomba(oJugador->getX(), oJugador->getY());
		}

		void disminuir_Vidas_por_Enemigo() {
			for (int i = 0; i < oArrEnemigos->getarregloEnemigos().size(); ++i) {
				if (oJugador->retornarRectangulo().IntersectsWith(oArrEnemigos->getarregloEnemigos().at(i)->retornarRectangulo())) {
					oJugador->disminuirvidas();

				}
			}
		}

		void disminuir_Vidas_por_Bomba() {
			int PuntaIzquierda, PuntaDerecha, CentroInicioY, CentroFinalY, PuntaSuperior, PuntaInferior, CentroInicioX, CentroFinalX;
			for (int i = 0; i < oArrBombas->getarregloBombas().size(); ++i)
			{
				PuntaIzquierda = oArrBombas->getarregloBombas().at(i)->getX() - 100;
				PuntaDerecha = oArrBombas->getarregloBombas().at(i)->getX() + 150;
				PuntaSuperior = oArrBombas->getarregloBombas().at(i)->getY() - 100;
				PuntaInferior = oArrBombas->getarregloBombas().at(i)->getY() + 150;
				CentroInicioY = oArrBombas->getarregloBombas().at(i)->getY();
				CentroInicioX = oArrBombas->getarregloBombas().at(i)->getX();
				CentroFinalX = oArrBombas->getarregloBombas().at(i)->getX() + 50;
				CentroFinalY = oArrBombas->getarregloBombas().at(i)->getY() + 50;

				if (oArrBombas->getarregloBombas().at(i)->getEstado() == Estado::explosion) {
					oJugador->disminuir_Vidas(PuntaIzquierda, PuntaDerecha, CentroInicioY, CentroFinalY, PuntaSuperior, PuntaInferior, CentroInicioX, CentroFinalX);
				}
			}
		}

		void dibujar(Graphics^ g, Bitmap^bmpBase, Bitmap^ bmpSolido, Bitmap^ bmpBomba, Bitmap^ bmpExplosion, Bitmap^ bmpDestruible, Bitmap^bmpJugador,
			Bitmap^ bmpMejoras, Bitmap^bmpEnemigo)
		{
			oEscenario->pintarBase(g,bmpBase);						
			oEscenario->pintarMatriz(g, bmpSolido, bmpDestruible);
			oArrMejoras->dibujarMejoras(g, bmpMejoras, oEscenario->getMatriz()); 
			oJugador->moverJugador(g, bmpJugador, oEscenario->getMatriz()); 
			oArrBombas->dibujar_una_bombas(g, bmpBomba, bmpExplosion, oJugador->getX(), oJugador->getY(), oEscenario->getMatriz());
			oArrEnemigos->dibujarEnemigo(g, bmpEnemigo, oEscenario->getMatriz());
			disminuir_Vidas_por_Bomba();
			disminuir_Vidas_por_Enemigo();
		}

		void crearMejoras() {
			oArrMejoras->crearMejoras();
		}
		void crearEnemigos() {
			oArrEnemigos->crearEnemigos();			
		}

		CJugador* getoJugador() {
			return oJugador;
		}

		CArrMejoras* getoArrMejoras() {
			return oArrMejoras;
		}

		CArrEnemigos* getoArrEnemigos() {
			return oArrEnemigos;
		}

		int getNivel() {
			return nivel;
		}

	private:
		CEscenario* oEscenario;
		CJugador* oJugador;
		CArrBombas* oArrBombas;
		CArrMejoras* oArrMejoras;
		CArrEnemigos* oArrEnemigos;		
		int nivel;

};

#endif //!__CONTROLADORA_H__
