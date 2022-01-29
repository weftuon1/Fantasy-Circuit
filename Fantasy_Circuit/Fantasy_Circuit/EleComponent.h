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
			Resistor() : EleComponent()   //���ᦳ�Ѽƥ��bEleComponent�A����
			{

			}
};

ref class Capacitor : public EleComponent
{
		private:
			double C;
		public:
			Capacitor() : EleComponent()   //���ᦳ�Ѽƥ��bEleComponent�A����
			{

			}
};

ref class Inductor : public EleComponent
{
		private:
			double L;
		public:
			Inductor() : EleComponent()   //���ᦳ�Ѽƥ��bEleComponent�A����
			{

			}
};