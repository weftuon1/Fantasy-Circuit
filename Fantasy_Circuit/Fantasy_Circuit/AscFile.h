#pragma once
#include "CalcNode.h"
#include <iostream>
#include <cliext/vector>
#include <vector>
#include <complex>
#include <math.h>
#include "..\Armadillo\include\armadillo"
using namespace std;
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace arma;

typedef cliext::vector<Point> vPoint;	
typedef cliext::vector<PictureBox ^> vPictureBox;

ref class AscFile
{
private:
	CalcNode nodeArray;
	Panel ^CircuitMap;
	vPoint Wire;
	vPictureBox Elepart;
	int **NodeMap;
	int dim;
	int omega;
	int phase;
	int Nodedim;
	String ^s;
	const int diffpix;
	int *VoltageNode;
	complex<double> **NodeMatrixG;
	complex<double> *NodeMatrixE;
	complex<double> **NodeMatrixS;
	void fillmap();	
	void analyze();
	void makematrix();
	void SolveMatrix();
	void MarshalString(String ^, string &);
public:
	AscFile(Panel ^p, vPoint screenWire, vPictureBox screenElepart, int w, int phi);
	int getNodedim();
	int getdim();
	int **getNodeMap();
	complex<double> *getNodeMatrixE();
	~AscFile();	
};