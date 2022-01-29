	#pragma once
	#pragma comment(linker, "/subsystem:console /entry:WinMainCRTStartup")
	#include "InitComponent.h"
	#include "Simulation.h"
	#include "Spice.h"
	#include "PanelDoublebuffered.h"
	#include <iostream>
	#include <deque>
	#include <stdlib.h>
	#include <complex>
	#include <math.h>
	#include "..\Armadillo\include\armadillo"
	//使用 vector <PictureBox ^>
	#include <cliext/vector>
	
	//===================
	namespace Fantasy_Circuit {
		
		using namespace System;
		using namespace System::ComponentModel;
		using namespace System::Collections;
		using namespace System::Windows::Forms;
		using namespace System::Data;
		using namespace System::Drawing;
		using namespace std;

		/// <summary>
		/// Form1 的摘要
		/// </summary>
		public ref class Form1 : public System::Windows::Forms::Form
		{
		public:
			Bitmap ^theBmp;
			static Graphics ^draw;
			int voltagecount;
			int groundcount;
			int resistorcount;
			int capacitorcount;
			int inductorcount;

		private: System::Windows::Forms::Button^  R_Button;
		private: System::Windows::Forms::Button^  L_Button;
		private: System::Windows::Forms::Button^  C_Button;
		private: System::Windows::Forms::Button^  V_button;
		private: System::Windows::Forms::Button^  G_Button;
		private: System::Windows::Forms::GroupBox^  groupBox1;
		private: System::Windows::Forms::ImageList^  ComponentList;
		private: System::Windows::Forms::ImageList^  ComponentList1;
		private: System::Windows::Forms::ImageList^  ComponentList2;
		private: System::Windows::Forms::ImageList^  ComponentList3;
		private: System::Windows::Forms::ImageList^  ComponentList4;
		private: System::Windows::Forms::Button^  Pen_Button;
		private: System::Windows::Forms::ImageList^  PenList;
		private: System::Windows::Forms::Button^  button1;
		private: System::Windows::Forms::TextBox^  OmegaText;
		private: System::Windows::Forms::Label^  OmegaLabel;
		private: System::Windows::Forms::Label^  label2;
		private: System::Windows::Forms::TextBox^  PhaseText;
		private: System::Windows::Forms::Button^  Clear;
		private: System::Windows::Forms::Button^  button2;





		public: 
			static Pen^ thePen;
			
			Form1(void)
			{
				InitializeComponent();
				//
				//TODO: 在此加入建構函式程式碼
				//doublebuffered
				static_cast<MyPanel ^>(Circuit_Map)->SetStyle(ControlStyles::AllPaintingInWmPaint, true);
				static_cast<MyPanel^>(Circuit_Map)->SetStyle(ControlStyles::DoubleBuffer, true);

				theBmp = gcnew Bitmap(Circuit_Map->Width, Circuit_Map->Height);
				draw = Graphics::FromImage(theBmp);
				draw->Clear(Color::Black);
				voltagecount = 0;
				groundcount;
				resistorcount = 0;
				capacitorcount = 0;
				inductorcount = 0;
				//CursorInitialX = 0; CursorInitialY = 0; //滑鼠拖曳初始位置
				isMoveState = false;
				WireMode = false;
				//imageList
				Piclist.push_back(ComponentList);//Voltage
				Piclist.push_back(ComponentList1);//Ground
				Piclist.push_back(ComponentList2);//Resistor
				Piclist.push_back(ComponentList3);//Capacitor
				Piclist.push_back(ComponentList4);//Inductor
			}

		protected:
			/// <summary>
			/// 清除任何使用中的資源。
			/// </summary>
			~Form1()
			{
				if (components)
				{
					delete components;
				}
			}
		private: System::Windows::Forms::Panel^  Circuit_Map;
		private: System::ComponentModel::IContainer^  components;
		protected: 

		private:			

				 /// <summary>
			/// 設計工具所需的變數。
			/// </summary>		
			int ControlPositionX,  ControlPositionY; //元件初始位置
			//int CursorInitialX,  CursorInitialY; //滑鼠拖曳初始位置
			bool isMoveState;
			cliext::vector <PictureBox ^> Elepart; // 存電子元件的位址
			cliext::vector <ImageList ^> Piclist; // 存ImageList
			cliext::vector <Point> WirePoint;		
			cliext::vector <Point> Wire;
			cliext::vector <Label ^> LabelPtr;
			bool WireMode;			
			Simulation ^NewForm;

	#pragma region Windows Form Designer generated code
			/// <summary>
			/// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器
			/// 修改這個方法的內容。
			/// </summary>
			void InitializeComponent(void)
			{
				this->components = (gcnew System::ComponentModel::Container());
				System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
				this->Circuit_Map = (gcnew System::Windows::Forms::Panel());
				this->R_Button = (gcnew System::Windows::Forms::Button());
				this->L_Button = (gcnew System::Windows::Forms::Button());
				this->C_Button = (gcnew System::Windows::Forms::Button());
				this->V_button = (gcnew System::Windows::Forms::Button());
				this->G_Button = (gcnew System::Windows::Forms::Button());
				this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
				this->Clear = (gcnew System::Windows::Forms::Button());
				this->button2 = (gcnew System::Windows::Forms::Button());
				this->button1 = (gcnew System::Windows::Forms::Button());
				this->Pen_Button = (gcnew System::Windows::Forms::Button());
				this->ComponentList = (gcnew System::Windows::Forms::ImageList(this->components));
				this->ComponentList1 = (gcnew System::Windows::Forms::ImageList(this->components));
				this->ComponentList2 = (gcnew System::Windows::Forms::ImageList(this->components));
				this->ComponentList3 = (gcnew System::Windows::Forms::ImageList(this->components));
				this->ComponentList4 = (gcnew System::Windows::Forms::ImageList(this->components));
				this->PenList = (gcnew System::Windows::Forms::ImageList(this->components));
				this->OmegaText = (gcnew System::Windows::Forms::TextBox());
				this->OmegaLabel = (gcnew System::Windows::Forms::Label());
				this->label2 = (gcnew System::Windows::Forms::Label());
				this->PhaseText = (gcnew System::Windows::Forms::TextBox());
				this->groupBox1->SuspendLayout();
				this->SuspendLayout();
				// 
				// Circuit_Map
				// 
				this->Circuit_Map->BackColor = System::Drawing::Color::Black;
				this->Circuit_Map->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
				this->Circuit_Map->Cursor = System::Windows::Forms::Cursors::Default;
				this->Circuit_Map->ForeColor = System::Drawing::SystemColors::Control;
				this->Circuit_Map->Location = System::Drawing::Point(130, 114);
				this->Circuit_Map->Name = L"Circuit_Map";
				this->Circuit_Map->Size = System::Drawing::Size(680, 520);
				this->Circuit_Map->TabIndex = 0;
				this->Circuit_Map->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::Circuit_Map_Paint);
				this->Circuit_Map->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::Circuit_Map_MouseDown);
				// 
				// R_Button
				// 
				this->R_Button->BackColor = System::Drawing::Color::DimGray;
				this->R_Button->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"R_Button.Image")));
				this->R_Button->Location = System::Drawing::Point(181, 10);
				this->R_Button->Name = L"R_Button";
				this->R_Button->Size = System::Drawing::Size(80, 80);
				this->R_Button->TabIndex = 1;
				this->R_Button->UseVisualStyleBackColor = false;
				this->R_Button->Click += gcnew System::EventHandler(this, &Form1::R_Button_Click);
				// 
				// L_Button
				// 
				this->L_Button->BackColor = System::Drawing::Color::DimGray;
				this->L_Button->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"L_Button.Image")));
				this->L_Button->Location = System::Drawing::Point(347, 10);
				this->L_Button->Name = L"L_Button";
				this->L_Button->Size = System::Drawing::Size(80, 80);
				this->L_Button->TabIndex = 2;
				this->L_Button->UseVisualStyleBackColor = false;
				this->L_Button->Click += gcnew System::EventHandler(this, &Form1::L_Button_Click);
				// 
				// C_Button
				// 
				this->C_Button->BackColor = System::Drawing::Color::DimGray;
				this->C_Button->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"C_Button.Image")));
				this->C_Button->Location = System::Drawing::Point(264, 10);
				this->C_Button->Name = L"C_Button";
				this->C_Button->Size = System::Drawing::Size(80, 80);
				this->C_Button->TabIndex = 3;
				this->C_Button->UseVisualStyleBackColor = false;
				this->C_Button->Click += gcnew System::EventHandler(this, &Form1::C_Button_Click);
				// 
				// V_button
				// 
				this->V_button->BackColor = System::Drawing::Color::DimGray;
				this->V_button->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"V_button.Image")));
				this->V_button->Location = System::Drawing::Point(15, 10);
				this->V_button->Name = L"V_button";
				this->V_button->Size = System::Drawing::Size(80, 80);
				this->V_button->TabIndex = 4;
				this->V_button->UseVisualStyleBackColor = false;
				this->V_button->Click += gcnew System::EventHandler(this, &Form1::V_button_Click);
				// 
				// G_Button
				// 
				this->G_Button->BackColor = System::Drawing::Color::DimGray;
				this->G_Button->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"G_Button.Image")));
				this->G_Button->Location = System::Drawing::Point(98, 10);
				this->G_Button->Name = L"G_Button";
				this->G_Button->Size = System::Drawing::Size(80, 80);
				this->G_Button->TabIndex = 5;
				this->G_Button->UseVisualStyleBackColor = false;
				this->G_Button->Click += gcnew System::EventHandler(this, &Form1::G_Button_Click);
				// 
				// groupBox1
				// 
				this->groupBox1->Controls->Add(this->Clear);
				this->groupBox1->Controls->Add(this->button2);
				this->groupBox1->Controls->Add(this->button1);
				this->groupBox1->Controls->Add(this->Pen_Button);
				this->groupBox1->Controls->Add(this->G_Button);
				this->groupBox1->Controls->Add(this->V_button);
				this->groupBox1->Controls->Add(this->C_Button);
				this->groupBox1->Controls->Add(this->L_Button);
				this->groupBox1->Controls->Add(this->R_Button);
				this->groupBox1->Cursor = System::Windows::Forms::Cursors::Default;
				this->groupBox1->Location = System::Drawing::Point(118, 25);
				this->groupBox1->Name = L"groupBox1";
				this->groupBox1->Size = System::Drawing::Size(747, 621);
				this->groupBox1->TabIndex = 6;
				this->groupBox1->TabStop = false;
				// 
				// Clear
				// 
				this->Clear->BackColor = System::Drawing::Color::DimGray;
				this->Clear->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"Clear.Image")));
				this->Clear->Location = System::Drawing::Point(602, 10);
				this->Clear->Name = L"Clear";
				this->Clear->Size = System::Drawing::Size(80, 80);
				this->Clear->TabIndex = 9;
				this->Clear->UseVisualStyleBackColor = false;
				this->Clear->Click += gcnew System::EventHandler(this, &Form1::Clear_Click);
				// 
				// button2
				// 
				this->button2->BackColor = System::Drawing::Color::DimGray;
				this->button2->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"button2.Image")));
				this->button2->Location = System::Drawing::Point(333, 270);
				this->button2->Name = L"button2";
				this->button2->Size = System::Drawing::Size(80, 80);
				this->button2->TabIndex = 8;
				this->button2->UseVisualStyleBackColor = false;
				// 
				// button1
				// 
				this->button1->BackColor = System::Drawing::Color::DimGray;
				this->button1->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"button1.Image")));
				this->button1->Location = System::Drawing::Point(516, 10);
				this->button1->Name = L"button1";
				this->button1->Size = System::Drawing::Size(80, 80);
				this->button1->TabIndex = 7;
				this->button1->UseVisualStyleBackColor = false;
				this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
				// 
				// Pen_Button
				// 
				this->Pen_Button->BackColor = System::Drawing::Color::DimGray;
				this->Pen_Button->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"Pen_Button.Image")));
				this->Pen_Button->Location = System::Drawing::Point(430, 10);
				this->Pen_Button->Name = L"Pen_Button";
				this->Pen_Button->Size = System::Drawing::Size(80, 80);
				this->Pen_Button->TabIndex = 6;
				this->Pen_Button->UseVisualStyleBackColor = false;
				this->Pen_Button->Click += gcnew System::EventHandler(this, &Form1::Pen_Button_Click);
				// 
				// ComponentList
				// 
				this->ComponentList->ImageStream = (cli::safe_cast<System::Windows::Forms::ImageListStreamer^  >(resources->GetObject(L"ComponentList.ImageStream")));
				this->ComponentList->TransparentColor = System::Drawing::Color::Transparent;
				this->ComponentList->Images->SetKeyName(0, L"V_0_N.png");
				this->ComponentList->Images->SetKeyName(1, L"V_1_N.png");
				this->ComponentList->Images->SetKeyName(2, L"V_2_N.png");
				this->ComponentList->Images->SetKeyName(3, L"V_3_N.png");
				this->ComponentList->Images->SetKeyName(4, L"V_0_Y.png");
				this->ComponentList->Images->SetKeyName(5, L"V_1_Y.png");
				this->ComponentList->Images->SetKeyName(6, L"V_2_Y.png");
				this->ComponentList->Images->SetKeyName(7, L"V_3_Y.png");
				// 
				// ComponentList1
				// 
				this->ComponentList1->ImageStream = (cli::safe_cast<System::Windows::Forms::ImageListStreamer^  >(resources->GetObject(L"ComponentList1.ImageStream")));
				this->ComponentList1->TransparentColor = System::Drawing::Color::Transparent;
				this->ComponentList1->Images->SetKeyName(0, L"G_0_N.png");
				this->ComponentList1->Images->SetKeyName(1, L"G_1_N.png");
				this->ComponentList1->Images->SetKeyName(2, L"G_0_Y.png");
				this->ComponentList1->Images->SetKeyName(3, L"G_1_Y.png");
				// 
				// ComponentList2
				// 
				this->ComponentList2->ImageStream = (cli::safe_cast<System::Windows::Forms::ImageListStreamer^  >(resources->GetObject(L"ComponentList2.ImageStream")));
				this->ComponentList2->TransparentColor = System::Drawing::Color::Transparent;
				this->ComponentList2->Images->SetKeyName(0, L"R_0_N.png");
				this->ComponentList2->Images->SetKeyName(1, L"R_1_N.png");
				this->ComponentList2->Images->SetKeyName(2, L"R_0_Y.png");
				this->ComponentList2->Images->SetKeyName(3, L"R_1_Y.png");
				// 
				// ComponentList3
				// 
				this->ComponentList3->ImageStream = (cli::safe_cast<System::Windows::Forms::ImageListStreamer^  >(resources->GetObject(L"ComponentList3.ImageStream")));
				this->ComponentList3->TransparentColor = System::Drawing::Color::Transparent;
				this->ComponentList3->Images->SetKeyName(0, L"C_0_N.png");
				this->ComponentList3->Images->SetKeyName(1, L"C_1_N.png");
				this->ComponentList3->Images->SetKeyName(2, L"C_0_Y.png");
				this->ComponentList3->Images->SetKeyName(3, L"C_1_Y.png");
				// 
				// ComponentList4
				// 
				this->ComponentList4->ImageStream = (cli::safe_cast<System::Windows::Forms::ImageListStreamer^  >(resources->GetObject(L"ComponentList4.ImageStream")));
				this->ComponentList4->TransparentColor = System::Drawing::Color::Transparent;
				this->ComponentList4->Images->SetKeyName(0, L"I_0_N.png");
				this->ComponentList4->Images->SetKeyName(1, L"I_1_N.png");
				this->ComponentList4->Images->SetKeyName(2, L"I_0_Y.png");
				this->ComponentList4->Images->SetKeyName(3, L"I_1_Y.png");
				// 
				// PenList
				// 
				this->PenList->ImageStream = (cli::safe_cast<System::Windows::Forms::ImageListStreamer^  >(resources->GetObject(L"PenList.ImageStream")));
				this->PenList->TransparentColor = System::Drawing::Color::Transparent;
				this->PenList->Images->SetKeyName(0, L"Mouse.png");
				this->PenList->Images->SetKeyName(1, L"Pencil.png");
				// 
				// OmegaText
				// 
				this->OmegaText->Font = (gcnew System::Drawing::Font(L"新細明體", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
					static_cast<System::Byte>(136)));
				this->OmegaText->Location = System::Drawing::Point(12, 182);
				this->OmegaText->MaxLength = 8;
				this->OmegaText->Multiline = true;
				this->OmegaText->Name = L"OmegaText";
				this->OmegaText->Size = System::Drawing::Size(97, 32);
				this->OmegaText->TabIndex = 7;
				this->OmegaText->Text = L"10";
				this->OmegaText->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
				// 
				// OmegaLabel
				// 
				this->OmegaLabel->Font = (gcnew System::Drawing::Font(L"新細明體", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
					static_cast<System::Byte>(136)));
				this->OmegaLabel->Location = System::Drawing::Point(22, 147);
				this->OmegaLabel->Name = L"OmegaLabel";
				this->OmegaLabel->Size = System::Drawing::Size(77, 32);
				this->OmegaLabel->TabIndex = 8;
				this->OmegaLabel->Text = L"Omega";
				// 
				// label2
				// 
				this->label2->Font = (gcnew System::Drawing::Font(L"新細明體", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
					static_cast<System::Byte>(136)));
				this->label2->Location = System::Drawing::Point(22, 261);
				this->label2->Name = L"label2";
				this->label2->Size = System::Drawing::Size(77, 32);
				this->label2->TabIndex = 10;
				this->label2->Text = L"Phase";
				this->label2->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				// 
				// PhaseText
				// 
				this->PhaseText->Font = (gcnew System::Drawing::Font(L"新細明體", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
					static_cast<System::Byte>(136)));
				this->PhaseText->Location = System::Drawing::Point(12, 296);
				this->PhaseText->MaxLength = 8;
				this->PhaseText->Multiline = true;
				this->PhaseText->Name = L"PhaseText";
				this->PhaseText->Size = System::Drawing::Size(97, 32);
				this->PhaseText->TabIndex = 9;
				this->PhaseText->Text = L"10";
				this->PhaseText->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
				// 
				// Form1
				// 
				this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
				this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				this->ClientSize = System::Drawing::Size(877, 649);
				this->Controls->Add(this->label2);
				this->Controls->Add(this->PhaseText);
				this->Controls->Add(this->OmegaLabel);
				this->Controls->Add(this->OmegaText);
				this->Controls->Add(this->Circuit_Map);
				this->Controls->Add(this->groupBox1);
				this->DoubleBuffered = true;
				this->Name = L"Form1";
				this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
				this->Text = L"Fantancy_Circuit";
				this->groupBox1->ResumeLayout(false);
				this->ResumeLayout(false);
				this->PerformLayout();

			}
	#pragma endregion		
		private: System::Void Circuit_Map_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
					 draw->Clear(Circuit_Map->BackColor);
					 thePen = gcnew Pen(Color::DarkSlateGray, 1);//設定畫筆
					 const int diffpix = 20;//洞洞板相離距離(pixel)

					 //=========== 畫橫線 =================
					 Point FromPoint(0, diffpix);
					 Point ToPoint(Circuit_Map->Width, diffpix);					 
					 do 
					 {
						 draw->DrawLine(thePen, FromPoint, ToPoint);//畫線
						 FromPoint.Y += diffpix;
						 ToPoint.Y += diffpix;
					 } 
					 while (FromPoint.Y < Circuit_Map->Height);
					 //=========== End ===================
					 //=========== 畫直線 =================
					 FromPoint.X = diffpix;
					 FromPoint.Y = 0;
					 ToPoint.X = diffpix;
					 ToPoint.Y = Circuit_Map->Height;
					 do 
					 {
						 draw->DrawLine(thePen, FromPoint, ToPoint);//畫線
						 FromPoint.X += diffpix;
						 ToPoint.X += diffpix;
					 } 
					 while (FromPoint.X < Circuit_Map->Width);					 					 					 					 
					 //============ End =================					
					 //============ 畫方格點 ==============
					 const int reclen = 6;//設定方格點的邊長
					 SolidBrush ^mybrush = gcnew SolidBrush(Color::DarkSlateGray);//設定筆刷
					 for(int i=0;;i+=4)
					 {
						 int x = (i+1)*diffpix;
						 if(x>=Circuit_Map->Width)
							 break;
						 for(int j=0;;j+=4)
						 {
							 int y = (j+1)*diffpix;
							 if(y>=Circuit_Map->Height)
								break;							 
							 draw->FillRectangle(mybrush, x-reclen/2, y-reclen/2, reclen, reclen);//畫方格點
						 }						 
					 }					 					 					 
					 //================ End ==============					 					
					 delete thePen;//清除thePen
					 delete mybrush;//清除mybrush								 
					 thePen = gcnew Pen(Color::LightGray, 3);
					 mybrush = gcnew SolidBrush(Color::LightGray);
					 int CSize = 8;
					 for(int i=0;i<Wire.size();i+=2)
					 {						 
						 draw->DrawLine(thePen, Wire[i], Wire[i+1]);
						 draw->FillEllipse(mybrush, Wire[i].X-CSize/2, Wire[i].Y-CSize/2, CSize, CSize);
						 draw->FillEllipse(mybrush, Wire[i+1].X-CSize/2, Wire[i+1].Y-CSize/2, CSize, CSize);
					 }
					 delete mybrush;
					 CSize = 10;
					 mybrush = gcnew SolidBrush(Color::Yellow);
					 for(int i=0;i<WirePoint.size();i++)
						 draw->FillEllipse(mybrush, WirePoint[i].X-CSize/2, WirePoint[i].Y-CSize/2, CSize, CSize);
					 delete thePen;
					 delete mybrush;
					  e->Graphics->DrawImage(theBmp, 0, 0);//畫圖到Circuit_Map(Panel)上面
				 }
		private: System::Void V_button_Click(System::Object^  sender, System::EventArgs^  e) {					 
					 voltagecount++;
					 String ^str = "0 0 4 1,10";
					 CreatePictureBox(this->Parent, "volatge", 0, 0, 80, 80, 0, str); //CreatePictureBox(Control^ parent, String^ boxname, int x, int y, int w, int h, int componentindex)
				 }
		
		private: System::Void G_Button_Click(System::Object^  sender, System::EventArgs^  e) {
					 groundcount++;			
					 String ^str = "1 0 2 1,0";
					 CreatePictureBox(this->Parent, "ground", 0, 0, 80, 80, 1, str); //CreatePictureBox(Control^ parent, String^ boxname, int x, int y, int w, int h, int componentindex)
				 }
		private: System::Void R_Button_Click(System::Object^  sender, System::EventArgs^  e) {
					 resistorcount++;
					 String ^str = "2 0 2 1,10";
					 CreatePictureBox(this->Parent, "resistor", 0, 0, 80, 80, 2, str); //CreatePictureBox(Control^ parent, String^ boxname, int x, int y, int w, int h, int componentindex)
				 }
		private: System::Void C_Button_Click(System::Object^  sender, System::EventArgs^  e) {
					 capacitorcount++;
					 String ^str = "3 0 2 1,10";
					 CreatePictureBox(this->Parent, "capacitor", 0, 0, 80, 80, 3, str); //CreatePictureBox(Control^ parent, String^ boxname, int x, int y, int w, int h, int componentindex)
				 }
		private: System::Void L_Button_Click(System::Object^  sender, System::EventArgs^  e) {
					 inductorcount++;
					 String ^str = "4 0 2 1,10";
					 CreatePictureBox(this->Parent, "inductor", 0, 0, 80, 80, 4, str); //CreatePictureBox(Control^ parent, String^ boxname, int x, int y, int w, int h, int componentindex)
				 }

		private: System::Void CreatePictureBox(Control^ parent, String^ boxname, int x, int y, int w, int h, int componentindex, String ^Tagstr)
				 {					 
					 PictureBox ^pic = gcnew PictureBox();
					 Elepart.push_back(pic);//將電子元件存入 vector
					 cout << "Component Count: " << Elepart.size() << endl;// 顯示電子元件數量
					 pic->Location = System::Drawing::Point(x, y);     // 設定位置
					 pic->Size = System::Drawing::Size(w, h);         // 設定寬高
					 
					 switch(componentindex)
					 {
						case 0:
							pic->Name = boxname + Convert::ToString(voltagecount);         // 用圖檔名稱加流水號當作控制項的名稱
							break;
						case 1:
							pic->Name = boxname + Convert::ToString(groundcount);
							break;
						case 2:
							pic->Name = boxname + Convert::ToString(resistorcount);
							break;
						case 3:
							pic->Name = boxname + Convert::ToString(capacitorcount);
							break;
						case 4:
							pic->Name = boxname + Convert::ToString(inductorcount);
							break;
						default:
							break;
					 }
					 pic->BackColor = Color::Transparent;
					 pic->Tag = Tagstr;
					 //cout << GetPicIndex(Convert::ToString(pic->Tag)) << endl;							 
					 pic->Image = Piclist[(int)(Tagstr[0])-48]->Images[GetPicIndex(Convert::ToString(pic->Tag))];	 
					 //pic->Image = ComponentList->Images[componentindex];	 
					 pic->SizeMode = PictureBoxSizeMode::StretchImage;
					 
					 pic->Click += gcnew System::EventHandler(this, &Form1::pic_Click); // 設定所有的PictureBox的Click事件都呼叫相同的事件函式
					 pic->KeyUp += gcnew KeyEventHandler(this, &Form1::pic_KeyUp); // 設定所有的PictureBox的Click事件都呼叫相同的事件函式					 
					 pic->KeyDown += gcnew KeyEventHandler(this, &Form1::pic_KeyDown);
					 pic->MouseDown += gcnew MouseEventHandler(this, &Form1::pic_MouseDown);
					 pic->MouseMove += gcnew MouseEventHandler(this, &Form1::pic_MouseMove);
					 pic->MouseUp += gcnew MouseEventHandler(this, &Form1::pic_MouseUp);					 
					 pic->GotFocus += gcnew System::EventHandler(this, &Form1::pic_GotFocus);
					 pic->LostFocus += gcnew System::EventHandler(this, &Form1::pic_LostFocus);
					 pic->DoubleClick += gcnew System::EventHandler(this, &Form1::pic_DoubleClick);					 
					 Circuit_Map->Controls->Add(pic);
					 pic->Focus();//取得Focus，才能接收KeyUp									 
					 if(componentindex!=1)					 
					 {
						 Label ^lb = gcnew Label;
						 lb->Text = "10";
						 lb->ForeColor = Color::Orange;
						 lb->Left = 0;
						 lb->Top = 20;
						 lb->AutoSize = true;
						 //cout << lb->Height << endl;
						 //cout << lb->Width << endl;
						 lb->Parent = pic;					 
						 pic->Controls->Add(lb);
						 LabelPtr.push_back(lb);
					 }					 
				 }
		private: int GetPicIndex(String ^str)
				 {
					 string s;
					 MarshalString(str, s);
					 int num[4];
					 for(int pre = s.find_first_not_of(" "),pos,i=0;pre!=string::npos;pre = s.find_first_not_of(" ", pos),i++)
					 {
						 pos = s.find_first_of(" ",pre);
						 num[i] = atoi(s.substr(pre, pos-pre).c_str());
					 }
					 int result = 0;
					 result = num[3]*num[2] + num[1];
					 return result;
				 }
		public: void updateValue()
				{
					for(int i=0;i<LabelPtr.size();i++)
						if(LabelPtr[i])
						{
							string tmp;								 
							MarshalString(Convert::ToString(LabelPtr[i]->Parent->Tag), tmp);
							LabelPtr[i]->Text = gcnew String(tmp.substr(tmp.find_first_of(",") +1).c_str());
						}
				}
		private: void MarshalString ( String ^ s, string& os ) {
					 using namespace Runtime::InteropServices;
					 const char* chars = 
						 (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
					 os = chars;
					 Marshal::FreeHGlobal(IntPtr((void*)chars));
				 }
		private: System::Void pic_Click(System::Object^  sender, System::EventArgs^  e)
				 {					 					 					 					 
					 PictureBox ^pic = safe_cast<PictureBox ^>(sender); // 將sender轉型成PictureBox
					 //pic->Focus();//取得Focus，才能接收KeyUp
					 //pic->BackColor = Color::Red;
					 //if (pic == NULL) 
						// return;

					 //String ^name = pic->Name; // 取出pictureBox的名稱
					 //MessageBox::Show (pic->Name);					 
					 // 以下就你讀取到的名稱去處理你要做的事情
					 
					 //cout << "Click!!!" << endl;
					 
				 }
		private: System::Void pic_KeyUp(System::Object^  sender,System::Windows::Forms::KeyEventArgs^  e)
				 {					 
					 if(e->KeyCode == Keys::Delete)// 按下delete鍵
					 {
						 //cout << "Delete a Component" << endl;

						 PictureBox ^pic = safe_cast<PictureBox ^>(sender); 
						 
						 for(int i=0;i<LabelPtr.size();i++)
						 {
							 if(LabelPtr[i]->Parent == pic)
							 {
								 LabelPtr.erase(LabelPtr.begin()+i, LabelPtr.begin()+i+1);
								 break;
							 }
						 }
						 for(int i=0;i<Elepart.size();i++)//搜尋要被刪掉的物件
						 {
							 if(Elepart[i] == pic)							
							 {
								 Elepart.erase(Elepart.begin()+i, Elepart.begin()+i+1);							
								 break;
							 }
						 }
						 Circuit_Map->Controls->Remove(pic);
						 delete pic->Click;
						 delete pic->DoubleClick;
						 delete pic->KeyUp;
						 delete pic->KeyDown;
						 delete pic->MouseDown;
						 delete pic->MouseMove;
						 delete pic->MouseUp;
						 delete pic->GotFocus;
						 delete pic->LostFocus;
						 delete pic->Image;
						 delete pic;//刪除物件	
					 }
				 }		
		private: System::Void pic_KeyDown(System::Object^  sender,System::Windows::Forms::KeyEventArgs^  e)
				 {
					 if(e->Control == true && e->KeyCode == Keys::R)
					 {
						 PictureBox ^pic = safe_cast<PictureBox ^>(sender);
						 string s;
						 MarshalString(Convert::ToString(pic->Tag), s);
						 s[2] = ((int)(s[2])-48 + 1)%((int)(s[4])-48) + '0';					 					 
						 String ^Tagstr = gcnew String(s.c_str());
						 pic->Tag = Tagstr;
						 delete pic->Image;
						 pic->Image = Piclist[(int)s[0]-48]->Images[GetPicIndex(Convert::ToString(pic->Tag))];
						 delete Tagstr;
					 }
				 }
		private: System::Void pic_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
				 {
					 PictureBox ^pic = safe_cast<PictureBox ^>(sender);
					 pic->Focus();
					 if(WireMode == false)
					 {
						 if (isMoveState == false) //非移動狀態
						 {
							 ControlPositionX = pic->Left; //元件初始位置
							 ControlPositionY = pic->Top;
							 //POINT p;
							 //GetCursorPos(&p);			 
							 //CursorInitialX = e->X; //滑鼠拖曳初始位置
							 //CursorInitialY = e->Y;

							 isMoveState = true; //設為移動狀態
						 }
					 }
					 else
					 {
						 Point Curp, Cmp1, Cmp2;						 
						 Curp.X = ((e->X%20 < 10)? (e->X/20)*20:(e->X/20+1)*20) + pic->Left;
						 Curp.Y = ((e->Y%20 < 10)? (e->Y/20)*20:(e->Y/20+1)*20) + pic->Top;						 
						 string s;
						 MarshalString(Convert::ToString(pic->Tag), s);
						 if(((int)s[0]-48)!=1)
						 {
							 switch(((int)s[2]-48)%2)
							 {
								 case 0:
									 Cmp1 = Point(pic->Left+pic->Width/2, pic->Top);
									 Cmp2 = Point(pic->Left+pic->Width/2, pic->Top+pic->Height);
									 break;
								 case 1:
									 Cmp1 = Point(pic->Left, pic->Top+pic->Height/2);
									 Cmp2 = Point(pic->Left+pic->Width, pic->Top+pic->Height/2);						
							 }
						 }
						 else
						 {
							 switch(((int) s[2] - 48))
							 {
								case 0:
									Cmp1 = Point(pic->Left + pic->Width/2, pic->Top);
								case 1:
									Cmp2 = Point(pic->Left+pic->Width/2, pic->Top + pic->Height);
							 }							 
							 Cmp2 = Point(-1,-1);
						 }
						 Point Topoint;
						 if(Curp==Cmp1 || Curp == Cmp2)
						 {
							 if(WirePoint.size()==0)				 
								 WirePoint.push_back(Curp);
							 else
							 {
								 if(Curp!=WirePoint[0])
								 {
									 if(abs(Curp.X-WirePoint[0].X)>=abs(Curp.Y-WirePoint[0].Y))
									 {
										 Topoint = Point(Curp.X, WirePoint[0].Y);
										 WirePoint.push_back(Topoint);
									 }
									 else
									 {
										 Topoint = Point(WirePoint[0].X, Curp.Y);
										 WirePoint.push_back(Topoint);
									 }						
									 Wire.push_back(WirePoint[0]);
									 Wire.push_back(WirePoint[1]);						
									 WirePoint.clear();						
									 //this->Invalidate();
								 }
							 }
							 Circuit_Map->Invalidate();
						 }						 						 
					 }
					 
					 //cout << CursorInitialX << endl;
					 //cout << CursorInitialY << endl;
					 //cout << pic->Parent->Size.Width << endl;
					 //cout << pic->Parent->Size.Height << endl;
				 }
				 
		private: System::Void pic_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
				 {
					 PictureBox ^pic = safe_cast<PictureBox ^>(sender);

					 if (isMoveState == true && WireMode==false) //移動狀態
					 {
						int dx = e->X - pic->Size.Width/2; //暫存目前滑鼠位置(相對picturebox中心點)
						int dy = e->Y - pic->Size.Height/2;
						// 新視窗位置 = 舊視窗位置 + 滑鼠移動距離
						int adjustx = (ControlPositionX + dx) % 20;
						int adjusty = (ControlPositionY + dy) % 20;

						if(0 <= adjustx && adjustx <= 9)
							pic->Left = ControlPositionX + dx - adjustx;
						else if(9 < adjustx && adjustx <= 19)
							pic->Left = ControlPositionX + dx + (20-adjustx);
						
						if(0 <= adjusty && adjusty <= 9)
							pic->Top = ControlPositionY + dy - adjusty;
						else if(9 < adjustx && adjustx <= 19)
							pic->Top = ControlPositionY + dy + (20-adjusty);
						
						if(pic->Left < 0)
							pic->Left = 0;
						else if(pic->Left+pic->Size.Width > pic->Parent->Size.Width)
							pic->Left = pic->Parent->Size.Width - pic->Size.Width;

						if(pic->Top < 0)
							pic->Top = 0;
						else if(pic->Top+pic->Size.Height > pic->Parent->Size.Height)
							pic->Top = pic->Parent->Size.Height - pic->Size.Height;
						//CursorInitialX = dx;
						//CursorInitialY = dy;
						ControlPositionX = pic->Left; //元件初始位置更新
						ControlPositionY = pic->Top;

						//cout << e->X << endl;
						//cout << e->Y << endl;

						//Circuit_Map->Invalidate();
					 }
					 
				 }

		private: System::Void pic_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
				 {
					 //PictureBox ^pic = safe_cast<PictureBox ^>(sender);
					 if(WireMode==false)
						isMoveState = false; //設為非移動狀態
				 }			
		private: System::Void pic_GotFocus(System::Object^  sender, System::EventArgs^  e)
				 {
					 PictureBox ^pic = safe_cast<PictureBox ^>(sender);
					 string s;
					 MarshalString(Convert::ToString(pic->Tag), s);
					 s[6] = '1';					 					 
					 String ^Tagstr = gcnew String(s.c_str());
					 pic->Tag = Tagstr;
					 delete pic->Image;
					 pic->Image = Piclist[(int)s[0]-48]->Images[GetPicIndex(Convert::ToString(pic->Tag))];
					 delete Tagstr;
				 }
		private: System::Void pic_LostFocus(System::Object^  sender, System::EventArgs^  e)
				 {
					 PictureBox ^pic = safe_cast<PictureBox ^>(sender);
					 if(pic)
					 {
						 string s;
						 MarshalString(Convert::ToString(pic->Tag), s);
						 s[6] = '0';					 					 
						 String ^Tagstr = gcnew String(s.c_str());						 						 
						 pic->Tag = Tagstr;
						 delete pic->Image;						 						 
						 pic->Image = Piclist[(int)s[0]-48]->Images[GetPicIndex(Convert::ToString(pic->Tag))	];
						 delete Tagstr;						 
					 }					 
				 }
		private: System::Void pic_DoubleClick(System::Object^  sender, System::EventArgs^  e) 
				 {
					 PictureBox ^pic = safe_cast<PictureBox ^>(sender);
					 string s;
					 MarshalString(Convert::ToString(pic->Tag), s);					 
					 if(((int)s[0]-48) != 1)
					 {
						 InitComponent^ NewForm = gcnew InitComponent(this, pic) ;
						 NewForm->Visible = true;						 
					 }					 
				 }
private: System::Void Pen_Button_Click(System::Object^  sender, System::EventArgs^  e) {
			 WireMode = !WireMode;
			 WirePoint.clear();
			 if(WireMode)
			 {
				 groupBox1->Cursor = Cursors::Cross;
				 Circuit_Map->Cursor = Cursors::Cross;
				 delete Pen_Button->Image;
				 Pen_Button->Image = PenList->Images[0];
			 }
			 else
			 {
				 groupBox1->Cursor = Cursors::Default;
				 Circuit_Map->Cursor = Cursors::Default;
				 delete Pen_Button->Image;
				 Pen_Button->Image = PenList->Images[1];
			 }
			 Circuit_Map->Invalidate();
		 }
private: System::Void Circuit_Map_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 if(WireMode)
			 {
				 if(e->Button == ::MouseButtons::Right)
				 {
					 WirePoint.clear();
					 Circuit_Map->Invalidate();					 
					 return;
				 }
				 Point Curp;
				 Curp.X = (e->X%20 < 10)? (e->X/20)*20:(e->X/20+1)*20;
				 Curp.Y = (e->Y%20 < 10)? (e->Y/20)*20:(e->Y/20+1)*20;
				 Point Topoint;
				 if(WirePoint.size()==0)				 
					WirePoint.push_back(Curp);
				 else
				 {
					if(Curp!=WirePoint[0])
					{
						if(abs(Curp.X-WirePoint[0].X)>=abs(Curp.Y-WirePoint[0].Y))
						{
							Topoint = Point(Curp.X, WirePoint[0].Y);
							WirePoint.push_back(Topoint);
						}
						else
						{
							Topoint = Point(WirePoint[0].X, Curp.Y);
							WirePoint.push_back(Topoint);
						}						
						Wire.push_back(WirePoint[0]);
						Wire.push_back(WirePoint[1]);						
						WirePoint.clear();						
						//this->Invalidate();
					}
				 }
				 Circuit_Map->Invalidate();
			 }
		 }
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(NewForm)
			 {
				 NewForm->Enabled=false;
				 NewForm->Visible=false;
			 }
				
			 int Omega;
			 int Phase;
			 try
			 {
				 Omega = Int64::Parse(OmegaText->Text);
				 Phase = Int64::Parse(PhaseText->Text);
				 if(Omega<=0 || Phase<0)
				 {
					 MessageBox::Show("			Omega AND Phase\nneed to be Positive Integer");
					 return;
				 }
			 }
			 catch(FormatException ^fe)
			 {
				 MessageBox::Show("輸入格式不正確");
				 return;
			 }
			NewForm = gcnew Simulation(this, Wire, Elepart, this->Circuit_Map, Omega, Phase);
			NewForm->Visible = true;							
		 }		 
private: System::Void Clear_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 WirePoint.clear();
			 Wire.clear();
			 for(int i=0;i<Elepart.size();i++)
				 delete Elepart[i];
			 Elepart.clear();
			 LabelPtr.clear();
			 Circuit_Map->Invalidate();
		 }
};
}

