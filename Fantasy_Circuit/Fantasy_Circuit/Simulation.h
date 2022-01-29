#pragma once
#include "AscFile.h"
#include "PanelDoublebuffered.h"
#include <iostream>
#include <vector>
#include <cliext/vector>
#include <string>
#include <math.h>

const double PI = 3.14159265358979323846;
namespace Fantasy_Circuit {
	using namespace std;
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Simulation 的摘要
	/// </summary>
	public ref class Simulation : public System::Windows::Forms::Form
	{
	public:
		static Pen^ thePen;
		Bitmap ^theBmp;
	private: System::Windows::Forms::Label^  t0;
	private: System::Windows::Forms::Label^  TT;
	private: System::Windows::Forms::Label^  V0;
	private: System::Windows::Forms::Label^  M1;
	private: System::Windows::Forms::Label^  M2;
	public: 

	public: 

	public: 

	public: 

	public: 

	public: 
		static Graphics ^draw;
		Simulation(Form ^f, cliext::vector <Point> ScreenWire, cliext::vector <PictureBox ^> ScreenElepart, Panel ^p, int w, int phi) : my_circuit(p, ScreenWire, ScreenElepart, w, phi)
		{
			InitializeComponent();
			//
			//TODO: 在此加入建構函式程式碼
			//
			static_cast<MyPanel ^>(Wave_Map)->SetStyle(ControlStyles::AllPaintingInWmPaint, true);
			static_cast<MyPanel^>(Wave_Map)->SetStyle(ControlStyles::DoubleBuffer, true);

			theBmp = gcnew Bitmap(Wave_Map->Width, Wave_Map->Height);
			draw = Graphics::FromImage(theBmp);
			draw->Clear(Color::White);
			
			form1 = f;
			CircuitMap = p;
			Wire = ScreenWire;
			Elepart = ScreenElepart;
			omega = w;
			phase = phi;
			complete = 0;
			solve();
		}

	protected:
		/// <summary>
		/// 清除任何使用中的資源。
		/// </summary>
		~Simulation()
		{			
			if (components)
			{
				delete components;
			}
		}

	private:
		/// <summary>
		/// 設計工具所需的變數。
		/// </summary>
		cliext::vector <Point> Wire;
		cliext::vector <PictureBox ^> Elepart; 		
		cliext::vector <CheckBox ^> WaveCheck;
		Form ^form1;
		Panel ^CircuitMap;
		AscFile my_circuit;
		System::ComponentModel::Container ^components;		
		int omega;
		int phase;
		int Nodedimen;
		int Mapdimen;
		int **NodeMap;
		double maxAmp;
		//bool *
		complex<double> *NodeMatrix;
		double *Amplitude;
		double *sita;
		double **F;
		bool *NodeSelect;
		bool complete;
	private: System::Windows::Forms::Panel^  Wave_Map;

			 
#pragma region Windows Form Designer generated code
		/// <summary>
		/// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器
		/// 修改這個方法的內容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->Wave_Map = (gcnew System::Windows::Forms::Panel());
			this->t0 = (gcnew System::Windows::Forms::Label());
			this->TT = (gcnew System::Windows::Forms::Label());
			this->V0 = (gcnew System::Windows::Forms::Label());
			this->M1 = (gcnew System::Windows::Forms::Label());
			this->M2 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// Wave_Map
			// 
			this->Wave_Map->Location = System::Drawing::Point(62, 39);
			this->Wave_Map->Name = L"Wave_Map";
			this->Wave_Map->Size = System::Drawing::Size(720, 470);
			this->Wave_Map->TabIndex = 0;
			this->Wave_Map->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Simulation::Wave_Map_Paint);
			// 
			// t0
			// 
			this->t0->AutoSize = true;
			this->t0->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->t0->Location = System::Drawing::Point(43, 522);
			this->t0->Name = L"t0";
			this->t0->Size = System::Drawing::Size(46, 20);
			this->t0->TabIndex = 1;
			this->t0->Text = L"0 sec";
			// 
			// TT
			// 
			this->TT->AutoSize = true;
			this->TT->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->TT->Location = System::Drawing::Point(718, 522);
			this->TT->Name = L"TT";
			this->TT->Size = System::Drawing::Size(27, 20);
			this->TT->TabIndex = 2;
			this->TT->Text = L"2T";
			// 
			// V0
			// 
			this->V0->AutoSize = true;
			this->V0->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->V0->Location = System::Drawing::Point(27, 260);
			this->V0->Name = L"V0";
			this->V0->Size = System::Drawing::Size(29, 20);
			this->V0->TabIndex = 3;
			this->V0->Text = L"0V";
			// 
			// M1
			// 
			this->M1->AutoSize = true;
			this->M1->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->M1->Location = System::Drawing::Point(20, 51);
			this->M1->Name = L"M1";
			this->M1->Size = System::Drawing::Size(33, 20);
			this->M1->TabIndex = 4;
			this->M1->Text = L"M1";
			this->M1->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// M2
			// 
			this->M2->AutoSize = true;
			this->M2->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->M2->Location = System::Drawing::Point(13, 470);
			this->M2->Name = L"M2";
			this->M2->Size = System::Drawing::Size(33, 20);
			this->M2->TabIndex = 5;
			this->M2->Text = L"M2";
			this->M2->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// Simulation
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1284, 561);
			this->Controls->Add(this->M2);
			this->Controls->Add(this->M1);
			this->Controls->Add(this->V0);
			this->Controls->Add(this->TT);
			this->Controls->Add(this->t0);
			this->Controls->Add(this->Wave_Map);
			this->Name = L"Simulation";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Simulation";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	public: void solve()
			{							
				//AscFile my_circuit(CircuitMap, Wire, Elepart, omega, phase);
				Nodedimen = my_circuit.getNodedim();
				Mapdimen = my_circuit.getdim();
				NodeMap = my_circuit.getNodeMap();
				NodeMatrix = my_circuit.getNodeMatrixE();
				/*
				for(int i=0; i<Mapdimen; i++)
				{
					for(int j=0; j<Mapdimen; j++)			
						cout << NodeMap[i][j] << " ";
					cout<<endl;
				}
				*/
				Amplitude = new double [Nodedimen];
				sita = new double [Nodedimen];
				NodeSelect = new bool [Nodedimen];
				for(int i=0; i<Nodedimen; i++)
				{
					double rea = NodeMatrix[i].real();
					double img = NodeMatrix[i].imag();
					Amplitude[i] = sqrt(rea*rea+img*img);
					sita[i] = atan2(img,rea);
					//cout << sita[i] << endl;
					NodeSelect[i] = true;
				}						
				CalcY();
			}
	private: void CalcY()
	  	    {
				F = new double *[Nodedimen];
				for(int i=0;i<Nodedimen;i++)
					F[i] = new double[Wave_Map->Width];
				double T = 1.0/(omega/2.0/PI);
				//cout << T << endl;
				double dx = 2*T/(Wave_Map->Width);

				for(int i=0;i<Nodedimen;i++)				
					for(int j=0;j<Wave_Map->Width;j++)					
						F[i][j] = Amplitude[i]*cos(omega*j*dx+sita[i]);															

				TT->Text = Convert::ToString(2*T) + " sec";

				WaveCheck.resize(Nodedimen);

				CheckBox ^Cb;
				for(int i=0;i<Nodedimen;i++)
				{
					Cb = gcnew CheckBox();
					if(i%4 == 0)
						Cb->ForeColor = Color::Red;
					else if(i%4 == 1)
						Cb->ForeColor = Color::Blue;
					else if(i%4 == 2)
						Cb->ForeColor = Color::Green;
					else if(i%4 == 3)
						Cb->ForeColor = Color::Orange;
					Cb->Text = "Node " + Convert::ToString(i+1) + ":  ";

					if(Amplitude[i]!=0)
					{						
						Cb->Text += Convert::ToString((double)((int)(Amplitude[i]*1000))/1000.0);
						Cb->Text += " cos (" +Convert::ToString(omega) + "t ";
						if(sita[i]>=0)
							Cb->Text += "+";
						Cb->Text += Convert::ToString((double)((int)(sita[i]*1000))/1000.0) + " )";
					}
					else
						Cb->Text += "0";
					Cb->Text += " V";

					Cb->Visible = true;
					Cb->Left = 810;
					Cb->Top = (i+2)*40;
					Cb->Font = (gcnew System::Drawing::Font(L"Verdana", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
						static_cast<System::Byte>(0)));
					Cb->AutoSize = true;
					Cb->UseVisualStyleBackColor = true;
					Cb->CheckedChanged += gcnew System::EventHandler(this, &Fantasy_Circuit::Simulation::Cb_CheckedChanged);					
					this->Controls->Add(Cb);
					WaveCheck[i] = Cb;
				}

				for(int i=0;i<Nodedimen;i++)
					WaveCheck[i]->Checked = true;

				complete = true;

				if(complete)
				{
					maxAmp = 0;					 
					for(int i=0;i<Nodedimen;i++)
						if(Amplitude[i] > maxAmp)						 
							maxAmp = Amplitude[i];
				}

				M1->Text = Convert::ToString((double)((int)(maxAmp*100))/100) + " V";;
				M2->Text = Convert::ToString((double)((int)(-maxAmp*100))/100) + " V";;
				
			 }
	private: System::Void Wave_Map_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) 
			 {
				 draw->Clear(Color::White);
				 if(complete)
				 {					 
					 if(maxAmp==0)
					 {
						 e->Graphics->DrawImage(theBmp, 0, 0);
						 return;
					 }
					 double factor = (0.5*Wave_Map->Height/maxAmp)*8.0/9.0;
					 for(int i=0;i<Nodedimen;i++)
					 {						 
						 if(i%4 == 0)
							thePen = gcnew Pen(Color::Red, 2);
						 else if(i%4 == 1)
							 thePen = gcnew Pen(Color::Blue, 2);
						 else if(i%4 == 2)
							 thePen = gcnew Pen(Color::Green, 2);
						 else if(i%4 == 3)
							 thePen = gcnew Pen(Color::Orange, 2);

						 for(int j=0;j<Wave_Map->Width-1;j++)
						 {
							 if(NodeSelect[i]==false)
								break;
							 Point fx(j, 0.5*Wave_Map->Height - factor*F[i][j]);
							 Point tx(j+1, 0.5*Wave_Map->Height - factor*F[i][j+1]);
							 draw->DrawLine(thePen, fx, tx);
						 }
					 }

					 e->Graphics->DrawImage(theBmp, 0, 0);
				 }
				 
			 }
	private: System::Void Cb_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
				 for(int i=0;i<Nodedimen;i++)
				 {
					 if(WaveCheck[i]->Checked)
						 NodeSelect[i] = true;
					 else
						 NodeSelect[i] = false;
				 }	

				 Wave_Map->Invalidate();
			 }
};
}
