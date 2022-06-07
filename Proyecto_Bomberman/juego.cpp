#include "juego.h"
using namespace JuegoBomberman;

void main(){
	Application::EnableVisualStyles();
	Application::Run(gcnew juego());  //Inicializador
}
