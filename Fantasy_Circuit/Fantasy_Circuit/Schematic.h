#pragma once
//#include "AscFile.h"
#include "EleComponent.h"
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

ref class Schematic
{
		private:
			Bitmap ^CircuitMap;
			Graphics ^CircuitG;
			Pen ^CircuitWire;
			
		public:
			Schematic()	  //default constructor
			{

			}
			EleComponent c1;   //Composition Component
			void Showbitmap(){}
			void DrawWire(Point S, Point E){}
			void DrawComponent(Point S, int type){}
			void DeleteLine(){}
			void DeleteComponent(){}
			bool AscFile_to_Grapharray(){return false;}
			bool Grapharray_to_Matrix(){return true;}			
};

struct Ctype
{
		int type;
		int value;
};

ref class Grapharray : public Schematic
{
		private:
			int NodeNum;
			Ctype **twodimarray;
		public:
			Grapharray() : Schematic()   //ぇΤ把计ゴSchematic珹腹柑
			{

			}
};

ref class Matrix : public Schematic
{	
		private:
			
		public:
			Matrix() : Schematic()   //ぇΤ把计ゴSchematic珹腹柑
			{

			}
};

