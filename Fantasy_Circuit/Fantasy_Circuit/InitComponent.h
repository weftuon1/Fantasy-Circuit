#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

namespace Fantasy_Circuit {
	using namespace std;
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// InitComponent 的摘要
	/// </summary>
	public ref class InitComponent : public System::Windows::Forms::Form
	{
	public:	
		InitComponent(Form^ f, PictureBox ^MyPic)
		{
			InitializeComponent();
			//
			//TODO: 在此加入建構函式程式碼
			//			
			form1 = f;
			pic = MyPic;
			form1->Enabled = false;
			string Title[5] = {"Voltage", "Ground", "Resistor", "Capacitor", "Inductor"};
			string unit[5] = {" (V)", "", " (Ohm)", " (pF)", " (uH)"};
			string s;
			MarshalString(Convert::ToString(pic->Tag), s);

			this->Text = gcnew String(pic->Name);	

			string tmp = Title[(int)(s[0]) - 48];
			tmp += unit[(int)(s[0]) - 48];
			ComponentType->Text = gcnew String(tmp.c_str());			

			InputBox->Text = gcnew String(s.substr(s.find_first_of(",")+1).c_str());
		}	
	protected:
		/// <summary>
		/// 清除任何使用中的資源。
		/// </summary>
		~InitComponent()
		{
			form1->Enabled = true;
			Setupdate(form1);
			if (components)
			{				
				delete components;				
			}
		}

	private:
		/// <summary>
		/// 設計工具所需的變數。
		/// </summary>
		System::ComponentModel::Container ^components;
		Form^ form1;
		PictureBox ^pic;
	private: System::Windows::Forms::Button^  OK_Button;

	private: System::Windows::Forms::Label^  ComponentType;
	private: System::Windows::Forms::TextBox^  InputBox;
	private: System::Windows::Forms::Button^  Cancel_Button;


			 

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器
		/// 修改這個方法的內容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->OK_Button = (gcnew System::Windows::Forms::Button());
			this->ComponentType = (gcnew System::Windows::Forms::Label());
			this->InputBox = (gcnew System::Windows::Forms::TextBox());
			this->Cancel_Button = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// OK_Button
			// 
			this->OK_Button->Font = (gcnew System::Drawing::Font(L"新細明體", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->OK_Button->Location = System::Drawing::Point(12, 87);
			this->OK_Button->Name = L"OK_Button";
			this->OK_Button->Size = System::Drawing::Size(85, 42);
			this->OK_Button->TabIndex = 0;
			this->OK_Button->Text = L"OK";
			this->OK_Button->UseVisualStyleBackColor = true;
			this->OK_Button->Click += gcnew System::EventHandler(this, &InitComponent::OK_Button_Click);
			// 
			// ComponentType
			// 
			this->ComponentType->Font = (gcnew System::Drawing::Font(L"新細明體", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->ComponentType->Location = System::Drawing::Point(12, 9);
			this->ComponentType->Name = L"ComponentType";
			this->ComponentType->Size = System::Drawing::Size(207, 33);
			this->ComponentType->TabIndex = 1;
			this->ComponentType->Text = L"Resistance (Ohm)";
			this->ComponentType->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// InputBox
			// 
			this->InputBox->Font = (gcnew System::Drawing::Font(L"新細明體", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->InputBox->Location = System::Drawing::Point(38, 45);
			this->InputBox->MaxLength = 8;
			this->InputBox->Name = L"InputBox";
			this->InputBox->Size = System::Drawing::Size(143, 36);
			this->InputBox->TabIndex = 2;
			this->InputBox->Text = L"1000";
			this->InputBox->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// Cancel_Button
			// 
			this->Cancel_Button->Font = (gcnew System::Drawing::Font(L"新細明體", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->Cancel_Button->Location = System::Drawing::Point(115, 88);
			this->Cancel_Button->Name = L"Cancel_Button";
			this->Cancel_Button->Size = System::Drawing::Size(85, 42);
			this->Cancel_Button->TabIndex = 3;
			this->Cancel_Button->Text = L"Cancel";
			this->Cancel_Button->UseVisualStyleBackColor = true;
			this->Cancel_Button->Click += gcnew System::EventHandler(this, &InitComponent::Cancel_Button_Click);
			// 
			// InitComponent
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(226, 143);
			this->Controls->Add(this->Cancel_Button);
			this->Controls->Add(this->InputBox);
			this->Controls->Add(this->ComponentType);
			this->Controls->Add(this->OK_Button);
			this->Name = L"InitComponent";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"InitComponent";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: void Setupdate(Form^);
	private: void MarshalString ( String ^ s, string & os ) {
				 using namespace Runtime::InteropServices;
				 const char* chars = 
					 (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
				 os = chars;
				 Marshal::FreeHGlobal(IntPtr((void*)chars));
			 }
	private: System::Void Cancel_Button_Click(System::Object^  sender, System::EventArgs^  e) {
				 delete this;
			 }
private: System::Void OK_Button_Click(System::Object^  sender, System::EventArgs^  e) {
			 int num = 0;
			 try
			 {				 
				 num = Int64::Parse(InputBox->Text);				 
			 }
			 catch (FormatException ^fe)
			 {
			 	MessageBox::Show ("Invalid Input!!!");
				return;
			 }			 

			 if(num <= 0)			 
			 {
				 MessageBox::Show("輸入值不正確");
				 return;
			 }			 		
			 else
			 {
				 string s;				 
				 MarshalString(Convert::ToString(pic->Tag), s);				 
				 s = s.substr(0, s.find_first_of(",")+1);
				 char tmpnum[36];
				 itoa(num, tmpnum,10);
				 s += tmpnum;

				 delete pic->Tag;
				 pic->Tag = gcnew String (s.c_str());
				 cout << "Tag: " << s.c_str() << endl;				 
				 delete this;
			 }
		 }
};
}
