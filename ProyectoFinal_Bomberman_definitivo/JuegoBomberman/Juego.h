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
		CControladora* oControladora;
		Bitmap^ bmpSolido = gcnew Bitmap("imagenes\\bmpSolido.png");
		Bitmap^ bmpDestruible = gcnew Bitmap("imagenes\\bmpDestruible.png");
		Bitmap^ bmpSuelo = gcnew Bitmap("imagenes\\bmpSuelo.png");
		Bitmap^ bmpJugador = gcnew Bitmap("imagenes\\Jugador.png");
		Bitmap^ bmpBomba = gcnew Bitmap("imagenes\\bomba.png");
		Bitmap^ bmpExplosion = gcnew Bitmap("imagenes\\explosion.png");
		Bitmap^ bmpMejoras = gcnew Bitmap("imagenes\\bmpMejoras.png");
		Bitmap^ bmpEnemigo = gcnew Bitmap("imagenes\\bmpEnemigo.png");			

	public:
		Juego(void)
		{
			bmpJugador->MakeTransparent(bmpJugador->GetPixel(0, 0));
			bmpBomba->MakeTransparent(bmpBomba->GetPixel(0, 0));
			bmpExplosion->MakeTransparent(bmpExplosion->GetPixel(0, 0));
			bmpEnemigo->MakeTransparent(bmpEnemigo->GetPixel(0, 0));

			InitializeComponent();
			oControladora = new CControladora();
			//
			//TODO: agregar código de constructor aquí
			//
		}

	protected:
		/// <summary>
		/// Limpiar los recursos que se estén usando.
		/// </summary>
		~Juego()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::Label^ lblNivel;
	private: System::Windows::Forms::ProgressBar^ pbCarga;
	private: System::Windows::Forms::Timer^ trCarga;
	private: System::Windows::Forms::Timer^ timer1;
	protected:

	private: System::ComponentModel::IContainer^ components;

	private:
		/// <summary>
		/// Variable del diseñador necesaria.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Método necesario para admitir el Diseñador. No se puede modificar
		/// el contenido de este método con el editor de código.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->lblNivel = (gcnew System::Windows::Forms::Label());
			this->pbCarga = (gcnew System::Windows::Forms::ProgressBar());
			this->trCarga = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// timer1
			// 
			this->timer1->Tick += gcnew System::EventHandler(this, &Juego::timer1_Tick);
			// 
			// lblNivel
			// 
			this->lblNivel->AutoSize = true;
			this->lblNivel->BackColor = System::Drawing::Color::Transparent;
			this->lblNivel->Font = (gcnew System::Drawing::Font(L"Cooper Black", 26.25F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblNivel->ForeColor = System::Drawing::Color::DarkBlue;
			this->lblNivel->Location = System::Drawing::Point(345, 548);
			this->lblNivel->Name = L"lblNivel";
			this->lblNivel->Size = System::Drawing::Size(153, 40);
			this->lblNivel->TabIndex = 0;
			this->lblNivel->Text = L"NIVEL: ";
			// 
			// pbCarga
			// 
			this->pbCarga->Location = System::Drawing::Point(325, 607);
			this->pbCarga->Name = L"pbCarga";
			this->pbCarga->Size = System::Drawing::Size(173, 23);
			this->pbCarga->TabIndex = 1;
			// 
			// trCarga
			// 
			this->trCarga->Enabled = true;
			this->trCarga->Interval = 2500;
			this->trCarga->Tick += gcnew System::EventHandler(this, &Juego::trCarga_Tick);
			// 
			// Juego
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::Black;
			this->ClientSize = System::Drawing::Size(848, 736);
			this->Controls->Add(this->pbCarga);
			this->Controls->Add(this->lblNivel);
			this->Name = L"Juego";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Juego";
			this->Load += gcnew System::EventHandler(this, &Juego::Juego_Load);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Juego::mantenerTecla);
			this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &Juego::ultimaTecla);
			this->ResumeLayout(false);
			this->PerformLayout();

		}

#pragma endregion
	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
		Graphics^ g = this->CreateGraphics();
		BufferedGraphicsContext^ espacio = BufferedGraphicsManager::Current;
		BufferedGraphics^ buffer = espacio->Allocate(g, this->ClientRectangle);
		oControladora->dibujar(buffer->Graphics, bmpSuelo, bmpSolido, bmpBomba, bmpExplosion, bmpDestruible, bmpJugador, bmpMejoras, bmpEnemigo);
		this->Text = "" + oControladora->getoJugador()->getVidas();
		buffer->Render(g);
		delete buffer, espacio, g;
	}
	private: System::Void Juego_Load(System::Object^ sender, System::EventArgs^ e) {
		lblNivel->Text = "NIVEL: " + oControladora->getNivel();
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
	private: System::Void trCarga_Tick(System::Object^ sender, System::EventArgs^ e) {
		lblNivel->Text = "NIVEL: " + oControladora->getNivel();
		pbCarga->Increment(10);		
		if (trCarga->Interval == 2500 && oControladora->getoArrEnemigos()->getarregloEnemigos().size() < oControladora->getNivel()) {
			oControladora->crearEnemigos();
			oControladora->crearMejoras();
		}
		else {
			trCarga->Enabled = false;
			timer1->Enabled = true;

			lblNivel->Visible = false;
			lblNivel->Enabled = false;
			pbCarga->Visible = false;
			pbCarga->Enabled = false;
		}
	}
};
}
