#pragma once
#include"Controladora.h"


namespace JuegoBomberman {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Resumen de Juego
	/// </summary>
	public ref class Juego : public System::Windows::Forms::Form
	{
	
	private:
		CControladora* oControladora = new CControladora(); 
		Bitmap^ bmpSolido = gcnew Bitmap("imagenes\\bmpSolido.png");
		Bitmap^ bmpDestruible = gcnew Bitmap("imagenes\\bmpDestruible.png");
		Bitmap^ bmpSuelo = gcnew Bitmap("imagenes\\bmpSuelo.png");
		Bitmap^ bmpJugador = gcnew Bitmap("imagenes\\Jugador.png");
		Bitmap^ bmpBomba = gcnew Bitmap("imagenes\\bomba.png");
		Bitmap^ bmpExplosion = gcnew Bitmap("imagenes\\explosion.png");

	public:
		Juego(void)
		{
			bmpJugador->MakeTransparent(bmpJugador->GetPixel(0, 0));
			bmpBomba->MakeTransparent(bmpBomba->GetPixel(0, 0));
			bmpExplosion->MakeTransparent(bmpExplosion->GetPixel(0, 0));
			InitializeComponent();
			//
			//TODO: agregar c?digo de constructor aqu?
			//
		}

	protected:
		/// <summary>
		/// Limpiar los recursos que se est?n usando.
		/// </summary>
		~Juego()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Timer^ timer1;
	protected:

	private: System::ComponentModel::IContainer^ components;

	private:
		/// <summary>
		/// Variable del dise?ador necesaria.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// M?todo necesario para admitir el Dise?ador. No se puede modificar
		/// el contenido de este m?todo con el editor de c?digo.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Tick += gcnew System::EventHandler(this, &Juego::timer1_Tick);
			// 
			// Juego
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(417, 426);
			this->Name = L"Juego";
			this->Text = L"Juego";
			this->Load += gcnew System::EventHandler(this, &Juego::Juego_Load);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Juego::mantenerTecla);
			this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &Juego::ultimaTecla);
			this->ResumeLayout(false);

		}

#pragma endregion
	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
		Graphics^ g = this->CreateGraphics();
		BufferedGraphicsContext^ espacio = BufferedGraphicsManager::Current;
		BufferedGraphics^ buffer = espacio->Allocate(g, this->ClientRectangle);

		oControladora->dibujar(buffer->Graphics, bmpSuelo, bmpSolido, bmpBomba, bmpExplosion, bmpDestruible, bmpJugador);
		buffer->Render(g);
		delete buffer, espacio, g;
	}
	private: System::Void Juego_Load(System::Object^ sender, System::EventArgs^ e) {
		oControladora->cambiarNivel();
	}

	private: System::Void mantenerTecla(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		switch (e->KeyCode)
		{
		case Keys::Up:
			oControladora->getoJugador()->setDireccion(Direcciones::Arriba);
			break;
		case Keys::Down:
			oControladora->getoJugador()->setDireccion(Direcciones::Abajo);
			break;
		case Keys::Left:
			oControladora->getoJugador()->setDireccion(Direcciones::Izquierda);
			break;
		case Keys::Right:
			oControladora->getoJugador()->setDireccion(Direcciones::Derecha);
			break;

		default:
			break;
		}
	}
	private: System::Void ultimaTecla(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		switch (e->KeyCode)
		{
			case Keys::Space:
				oControladora->AgregarBomba();
				break;
		default:
			oControladora->getoJugador()->setDireccion(Direcciones::Ninguna);
			break;
		}
	}
};
}
