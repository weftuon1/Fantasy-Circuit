#pragma once

ref class EleComponent
{
		private:
			
		public:
			EleComponent()	  //default constructor
			{

			}
};

ref class Resistor : public EleComponent
{
		private:
			double R;
		public:
			Resistor() : EleComponent()   //ぇΤ把计ゴEleComponent珹腹柑
			{

			}
};

ref class Capacitor : public EleComponent
{
		private:
			double C;
		public:
			Capacitor() : EleComponent()   //ぇΤ把计ゴEleComponent珹腹柑
			{

			}
};

ref class Inductor : public EleComponent
{
		private:
			double L;
		public:
			Inductor() : EleComponent()   //ぇΤ把计ゴEleComponent珹腹柑
			{

			}
};