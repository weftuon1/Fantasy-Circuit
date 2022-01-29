#include "StdAfx.h"
#include "InitComponent.h"
#include "Form1.h"
using namespace System::Windows::Forms;
using namespace Fantasy_Circuit;

void InitComponent::Setupdate(Form^ form1){
	Form1^ f=safe_cast <Form1^>(form1);
	f->updateValue();
}