#include "stdafx.h"

using namespace System;
using namespace System::Reflection;
using namespace System::Runtime::CompilerServices;
using namespace System::Runtime::InteropServices;
using namespace System::Security::Permissions;

//
// �ե󪺤@���T�O�ѤU�C���ݩʶ�����C
// �ܧ�o���ݩʪ��ȧY�i�ק�ե󪺬���
// ��T�C
//
[assembly:AssemblyTitleAttribute("Fantasy_Circuit")];
[assembly:AssemblyDescriptionAttribute("")];
[assembly:AssemblyConfigurationAttribute("")];
[assembly:AssemblyCompanyAttribute("")];
[assembly:AssemblyProductAttribute("Fantasy_Circuit")];
[assembly:AssemblyCopyrightAttribute("Copyright (c)  2016")];
[assembly:AssemblyTrademarkAttribute("")];
[assembly:AssemblyCultureAttribute("")];

//
// �ե󪺪�����T�O�ѤU�C�|���Ⱥc��:
//
//      �D�n����
//      ���n����
//      �իؽs��
//      �׭q�s��
//
// �z�i�H���w�Ҧ����ȡA�]�i�H�̷ӥH�U���覡�A�ϥ� '*' �N�׭q�M�իؽs��
// ���w���w�]��:

[assembly:AssemblyVersionAttribute("1.0.*")];

[assembly:ComVisible(false)];

[assembly:CLSCompliantAttribute(true)];

[assembly:SecurityPermission(SecurityAction::RequestMinimum, UnmanagedCode = true)];
