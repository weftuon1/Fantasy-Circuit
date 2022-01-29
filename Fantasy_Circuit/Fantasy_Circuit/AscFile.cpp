#include "stdafx.h"
#include "AscFile.h"
#include <complex>
#include <math.h>
#include "..\Armadillo\include\armadillo"

void AscFile::fillmap()
{
	NodeType *NodeResult = nodeArray.GetNode();
	Nodedim = NodeResult->size();
	
	for(int i=0;i<NodeResult->size();i++)
	{			
		set<pair<int, int>>::iterator p;
		for(p=(*NodeResult)[i].begin();p!=(*NodeResult)[i].end();p++)					
			NodeMap[(*p).second][(*p).first] = i + 1;
	}

	VoltageNode = new int [Nodedim];
	NodeMatrixG = new complex<double> *[Nodedim];
	NodeMatrixE = new complex<double> [Nodedim];
	NodeMatrixS = new complex<double> *[Nodedim];
	for(int i=0;i<Nodedim;i++)
	{
		VoltageNode[i] = 0;
		NodeMatrixE[i] = 0;

		NodeMatrixG[i] = new complex<double> [Nodedim];
		NodeMatrixS[i] = new complex<double> [1];
		for(int j=0;j<Nodedim;j++)
			NodeMatrixG[i][j] = 0;
		NodeMatrixS[i][0] = 0;	
	}
	
/*
	for(int i=0;i<dim;i++)
	{
		for(int j=0;j<dim;j++)
			cout << NodeMap[i][j];
		cout << endl;
	}*/
	analyze();
}

void AscFile::analyze()
{
	string Ctype[5] = {"Voltage", "Ground", "Resistor", "Capacitor", "Inductor"};
	s = "";
	for(int i=0;i<Elepart.size();i++)
	{
		string tags;
		MarshalString(Convert::ToString(Elepart[i]->Tag), tags);
		if(tags[0] == '1')
		{
			Point fp;
			if(tags[2] == '0')
			{
				fp.X = Elepart[i]->Left + Elepart[i]->Width/2;
				fp.Y = Elepart[i]->Top;				
			}
			else if(tags[2] == '1')
			{
				fp.X = Elepart[i]->Left + Elepart[i]->Width/2;
				fp.Y = Elepart[i]->Top + Elepart[i]->Height;
			}
			fp.X /= diffpix;
			fp.Y /= diffpix;

			if(NodeMap[fp.Y][fp.X] != 0)
			{
				s += gcnew String(Ctype[1].c_str()) + " ";
				s += Convert::ToString(NodeMap[fp.Y][fp.X]);
				s += Environment::NewLine;

				if(tags[0] == '1')
				{
					VoltageNode[NodeMap[fp.Y][fp.X]-1] = 2;
				}
			}
		}
		else
		{
			Point fp;
			Point tp;
			if(((int)tags[2] - 48)%2 == 1)
			{
				fp.X = Elepart[i]->Left;
				fp.Y = Elepart[i]->Top + Elepart[i]->Height/2;
				tp.X = Elepart[i]->Left + Elepart[i]->Width;
				tp.Y = Elepart[i]->Top + Elepart[i]->Height/2;
			}
			else
			{
				fp.X = Elepart[i]->Left + Elepart[i]->Width/2;
				fp.Y = Elepart[i]->Top + Elepart[i]->Height;
				tp.X = Elepart[i]->Left + Elepart[i]->Width/2;
				tp.Y = Elepart[i]->Top;				
			}

			fp.X /= diffpix;
			fp.Y /= diffpix;
			tp.X /= diffpix;
			tp.Y /= diffpix;
			if(NodeMap[fp.Y][fp.X] && NodeMap[tp.Y][tp.X] && NodeMap[fp.Y][fp.X] != NodeMap[tp.Y][tp.X])
			{
				if(tags[0]=='0' &&(tags[2]=='2' || tags[2]=='3'))
					swap(fp, tp);
				s += gcnew String(Ctype[(int)tags[0]-48].c_str()) + " "; 
				s += Convert::ToString(NodeMap[fp.Y][fp.X]) + " ";
				s += Convert::ToString(NodeMap[tp.Y][tp.X]) + " ";
				s += gcnew String(tags.substr(tags.find_first_of(",")+1).c_str());
				s += Environment::NewLine;

				if(tags[0] == '0')
				{
					if(VoltageNode[NodeMap[fp.Y][fp.X]-1]==0)		
						VoltageNode[NodeMap[fp.Y][fp.X]-1] = 1;
					if(VoltageNode[NodeMap[tp.Y][tp.X]-1]==0)
						VoltageNode[NodeMap[tp.Y][tp.X]-1] = 1;		
				}
			}
		}
	}
	string result;	
	MarshalString(s, result);
	cout << result.c_str();

	makematrix();
}

void AscFile::makematrix()
{
	//string Ctype[5] = {"Voltage", "Ground", "Resistor", "Capacitor", "Inductor"};
	
	//(real, imag);
	//constructor assign
	const double PI = 3.14159265358979;
	double rphase = (double)phase*PI/180;

	for(int i=0;i<Elepart.size();i++)
	{
		complex<double> j(0,1);//----> 0+1i
		string tags;
		MarshalString(Convert::ToString(Elepart[i]->Tag), tags);
		if(tags[0] == '1')
		{
			Point fp;
			if(tags[2] == '0')
			{
				fp.X = Elepart[i]->Left + Elepart[i]->Width/2;
				fp.Y = Elepart[i]->Top;				
			}
			else if(tags[2] == '1')
			{
				fp.X = Elepart[i]->Left + Elepart[i]->Width/2;
				fp.Y = Elepart[i]->Top + Elepart[i]->Height;
			}
			fp.X /= diffpix;
			fp.Y /= diffpix;

			if(NodeMap[fp.Y][fp.X] != 0)
			{
				//s += gcnew String(Ctype[1].c_str()) + " ";
				//s += Convert::ToString(NodeMap[fp.Y][fp.X]);
				//s += Environment::NewLine;

				if(tags[0] == '1')
				{
					//String ^tmp;
					//tmp = gcnew String(tags.substr(tags.find_first_of(",")+1).c_str());
					
					NodeMatrixG[NodeMap[fp.Y][fp.X]-1][NodeMap[fp.Y][fp.X]-1] = 1;
					NodeMatrixS[NodeMap[fp.Y][fp.X]-1][0] = 0;
				}
			}
		}
		else
		{
			Point fp; //front point
			Point tp; // to   point
			if(((int)tags[2] - 48)%2 == 1)
			{
				fp.X = Elepart[i]->Left;
				fp.Y = Elepart[i]->Top + Elepart[i]->Height/2;
				tp.X = Elepart[i]->Left + Elepart[i]->Width;
				tp.Y = Elepart[i]->Top + Elepart[i]->Height/2;
			}
			else
			{
				fp.X = Elepart[i]->Left + Elepart[i]->Width/2;
				fp.Y = Elepart[i]->Top + Elepart[i]->Height;
				tp.X = Elepart[i]->Left + Elepart[i]->Width/2;
				tp.Y = Elepart[i]->Top;				
			}

			fp.X /= diffpix;
			fp.Y /= diffpix;
			tp.X /= diffpix;
			tp.Y /= diffpix;
			if(NodeMap[fp.Y][fp.X] && NodeMap[tp.Y][tp.X] && NodeMap[fp.Y][fp.X] != NodeMap[tp.Y][tp.X])
			{
				if(tags[0]=='0' &&(tags[2]=='2' || tags[2]=='3'))
					swap(fp, tp);
				//s += gcnew String(Ctype[(int)tags[0]-48].c_str()) + " "; 
				//s += Convert::ToString(NodeMap[fp.Y][fp.X]) + " ";
				//s += Convert::ToString(NodeMap[tp.Y][tp.X]) + " ";
				//s += gcnew String(tags.substr(tags.find_first_of(",")+1).c_str());
				//s += Environment::NewLine;


				//v*cos(rad(phase)) + v*sin(rad(phase))*i rad:: convert degree to radian 
				if(tags[0] == '0')
				{
					String ^tmp;
					tmp = gcnew String(tags.substr(tags.find_first_of(",")+1).c_str());
					complex<double> V(Convert::ToDouble(tmp)*cos(rphase), Convert::ToDouble(tmp)*sin(rphase));

					if(VoltageNode[NodeMap[tp.Y][tp.X]-1] == 2)
					{
						NodeMatrixG[NodeMap[fp.Y][fp.X]-1][NodeMap[tp.Y][tp.X]-1] = 1;
						NodeMatrixG[NodeMap[fp.Y][fp.X]-1][NodeMap[fp.Y][fp.X]-1] = -1;			
						NodeMatrixS[NodeMap[fp.Y][fp.X]-1][0] = V;
					}
					else
					{
						NodeMatrixG[NodeMap[tp.Y][tp.X]-1][NodeMap[tp.Y][tp.X]-1] = 1;
						NodeMatrixG[NodeMap[tp.Y][tp.X]-1][NodeMap[fp.Y][fp.X]-1] = -1;			
						NodeMatrixS[NodeMap[tp.Y][tp.X]-1][0] = V;
					}
				}
				else if(tags[0] == '2')
				{
					String ^tmp;
					tmp = gcnew String(tags.substr(tags.find_first_of(",")+1).c_str());
					complex<double> R(Convert::ToDouble(tmp), 0);
					complex<double> tmpp(1, 0);

					if(VoltageNode[NodeMap[fp.Y][fp.X]-1] == 0 && VoltageNode[NodeMap[tp.Y][tp.X]-1] == 0)
					{
						NodeMatrixG[NodeMap[fp.Y][fp.X]-1][NodeMap[fp.Y][fp.X]-1] += tmpp/R;
						NodeMatrixG[NodeMap[tp.Y][tp.X]-1][NodeMap[tp.Y][tp.X]-1] += tmpp/R;
						NodeMatrixG[NodeMap[fp.Y][fp.X]-1][NodeMap[tp.Y][tp.X]-1] += -tmpp/R;
						NodeMatrixG[NodeMap[tp.Y][tp.X]-1][NodeMap[fp.Y][fp.X]-1] += -tmpp/R;
					}
					else if(VoltageNode[NodeMap[fp.Y][fp.X]-1] != 0 && VoltageNode[NodeMap[tp.Y][tp.X]-1] == 0)
					{					
						NodeMatrixG[NodeMap[tp.Y][tp.X]-1][NodeMap[tp.Y][tp.X]-1] += tmpp/R;
						NodeMatrixG[NodeMap[tp.Y][tp.X]-1][NodeMap[fp.Y][fp.X]-1] += -tmpp/R;
					}
					else if(VoltageNode[NodeMap[fp.Y][fp.X]-1] == 0 && VoltageNode[NodeMap[tp.Y][tp.X]-1] != 0)
					{
						NodeMatrixG[NodeMap[fp.Y][fp.X]-1][NodeMap[fp.Y][fp.X]-1] += tmpp/R;
						NodeMatrixG[NodeMap[fp.Y][fp.X]-1][NodeMap[tp.Y][tp.X]-1] += -tmpp/R;
					}
				}
				else if(tags[0] == '3')
				{
					String ^tmp;
					tmp = gcnew String(tags.substr(tags.find_first_of(",")+1).c_str());
					complex<double> C(Convert::ToDouble(tmp)/(pow(10.0, 12.0)), 0);
					complex<double> tmpp(1, 0);
					complex<double> W((double)omega, 0);
					complex<double> Z = tmpp/(j*W*C);
					//cout<<"ZC : " << Z <<endl;
					if(VoltageNode[NodeMap[fp.Y][fp.X]-1] == 0 && VoltageNode[NodeMap[tp.Y][tp.X]-1] == 0)
					{
						NodeMatrixG[NodeMap[fp.Y][fp.X]-1][NodeMap[fp.Y][fp.X]-1] += tmpp/Z;
						NodeMatrixG[NodeMap[tp.Y][tp.X]-1][NodeMap[tp.Y][tp.X]-1] += tmpp/Z;
						NodeMatrixG[NodeMap[fp.Y][fp.X]-1][NodeMap[tp.Y][tp.X]-1] += -tmpp/Z;
						NodeMatrixG[NodeMap[tp.Y][tp.X]-1][NodeMap[fp.Y][fp.X]-1] += -tmpp/Z;
					}
					else if(VoltageNode[NodeMap[fp.Y][fp.X]-1] != 0 && VoltageNode[NodeMap[tp.Y][tp.X]-1] == 0)
					{					
						NodeMatrixG[NodeMap[tp.Y][tp.X]-1][NodeMap[tp.Y][tp.X]-1] += tmpp/Z;
						NodeMatrixG[NodeMap[tp.Y][tp.X]-1][NodeMap[fp.Y][fp.X]-1] += -tmpp/Z;
					}
					else if(VoltageNode[NodeMap[fp.Y][fp.X]-1] == 0 && VoltageNode[NodeMap[tp.Y][tp.X]-1] != 0)
					{
						NodeMatrixG[NodeMap[fp.Y][fp.X]-1][NodeMap[fp.Y][fp.X]-1] += tmpp/Z;
						NodeMatrixG[NodeMap[fp.Y][fp.X]-1][NodeMap[tp.Y][tp.X]-1] += -tmpp/Z;
					}
				}				
				else if(tags[0] == '4')
				{
					String ^tmp;
					tmp = gcnew String(tags.substr(tags.find_first_of(",")+1).c_str());
					complex<double> L(Convert::ToDouble(tmp)*pow(10.0,6.0), 0);					
					complex<double> tmpp(1, 0);
					complex<double> W((double)omega, 0);
					complex<double> Z = (j*W*L);
					//cout<<"ZL : " << Z <<endl;
					if(VoltageNode[NodeMap[fp.Y][fp.X]-1] == 0 && VoltageNode[NodeMap[tp.Y][tp.X]-1] == 0)
					{
						NodeMatrixG[NodeMap[fp.Y][fp.X]-1][NodeMap[fp.Y][fp.X]-1] += tmpp/Z;
						NodeMatrixG[NodeMap[tp.Y][tp.X]-1][NodeMap[tp.Y][tp.X]-1] += tmpp/Z;
						NodeMatrixG[NodeMap[fp.Y][fp.X]-1][NodeMap[tp.Y][tp.X]-1] += -tmpp/Z;
						NodeMatrixG[NodeMap[tp.Y][tp.X]-1][NodeMap[fp.Y][fp.X]-1] += -tmpp/Z;
					}
					else if(VoltageNode[NodeMap[fp.Y][fp.X]-1] != 0 && VoltageNode[NodeMap[tp.Y][tp.X]-1] == 0)
					{					
						NodeMatrixG[NodeMap[tp.Y][tp.X]-1][NodeMap[tp.Y][tp.X]-1] += tmpp/Z;
						NodeMatrixG[NodeMap[tp.Y][tp.X]-1][NodeMap[fp.Y][fp.X]-1] += -tmpp/Z;
					}
					else if(VoltageNode[NodeMap[fp.Y][fp.X]-1] == 0 && VoltageNode[NodeMap[tp.Y][tp.X]-1] != 0)
					{
						NodeMatrixG[NodeMap[fp.Y][fp.X]-1][NodeMap[fp.Y][fp.X]-1] += tmpp/Z;
						NodeMatrixG[NodeMap[fp.Y][fp.X]-1][NodeMap[tp.Y][tp.X]-1] += -tmpp/Z;
					}
				}
			}
		}
	}
	//cout << "flag : " << endl;
	//for(int i=0;i<Nodedim;i++)
	//{	
	//	cout << VoltageNode[i] << " ";
	//}
	
	cout<<endl<<"MatrixG : "<<endl;
	for(int i=0;i<Nodedim;i++)
	{
		for(int j=0;j<Nodedim;j++)
			cout << NodeMatrixG[i][j] << " ";
		cout<<endl;
	}

	cout<<endl<<"MatrixS : "<<endl;
	for(int i=0;i<Nodedim;i++)
	{
		cout << NodeMatrixS[i][0] << " ";
		cout<<endl;
	}
	
	SolveMatrix();
}

void AscFile::SolveMatrix()
{
	Mat<complex<double> > A(Nodedim, Nodedim);
	Mat<complex<double> > B(Nodedim, 1);
	Mat<complex<double> > X(Nodedim, 1);

	for(int i=0;i<Nodedim;i++)
	{
		B(i,0) = NodeMatrixS[i][0];
		for(int j=0;j<Nodedim;j++)		
			A(i, j) = NodeMatrixG[i][j];		
	}	
	
	cout << endl << "Solution:" << endl;
	try
	{
		X = solve(A, B);
		
		for(int i=0;i<Nodedim;i++)
		{
			cout << X(i, 0) << endl;
			NodeMatrixE[i] = X(i, 0);
		}
		
	}
	catch (...)
	{
		cout << "Exception occur";
	}
}

AscFile::AscFile(Panel ^p, vPoint screenWire, vPictureBox screenElepart, int w, int phi): nodeArray(screenWire), diffpix(20)
{
	omega = w;
	phase = phi;
	cout << "Omega: " << omega << endl;
	cout << "Phase:  " << phase << endl;
	CircuitMap = p;
	Wire = screenWire;
	Elepart = screenElepart;
	dim = max(CircuitMap->Height, CircuitMap->Width)/diffpix + 1;				

	NodeMap = new int *[dim];
	for(int i=0;i<dim;i++)
	{
		NodeMap[i] = new int [dim];
		for(int j=0;j<dim;j++)
			NodeMap[i][j] = 0;
	}

	fillmap();
}

AscFile::~AscFile()
{
	/*
	for(int i=0;i<dim;i++)
		delete []NodeMap[i];
	delete []NodeMap;
	*/
}

int AscFile::getNodedim()
{
	return Nodedim;
}

int AscFile::getdim()
{
	return dim;
}

int** AscFile::getNodeMap()
{
	return NodeMap;
}

complex<double>* AscFile::getNodeMatrixE()
{
	return NodeMatrixE;
}

void AscFile::MarshalString ( String ^ s, string& os ) 
{
	using namespace Runtime::InteropServices;
	const char* chars = 
	(const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
	os = chars;
	Marshal::FreeHGlobal(IntPtr((void*)chars));
}