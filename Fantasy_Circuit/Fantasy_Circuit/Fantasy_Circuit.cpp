// Fantasy_Circuit.cpp: �D�n�M���ɡC

#include "stdafx.h"
#include "Form1.h"
#include "Spice.h"


using namespace Fantasy_Circuit;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// �إߥ��󱱨���e�A���ҥ� Windows XP ��ı�ƮĪG
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// �إߥD�����ð���
	Application::Run(gcnew Form1());
	Spice myspice;	
	return 0;
}
