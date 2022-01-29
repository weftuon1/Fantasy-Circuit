#pragma once
#include <iostream>
#include <cliext/vector>
#include <vector>
#include <iterator>
#include <set>
using namespace std;
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

typedef vector<set<pair<int, int>>> NodeType;

ref class CalcNode
{
private:
	cliext::vector<Point> Wire;	
	NodeType *Node;	
	void analyze();	
	bool Find_in_set(int n, int x1, int y1, int x2, int y2);	
	void merge(int n, int x1, int y1, int x2, int y2);	
	void display();	
public:
	CalcNode(cliext::vector<Point> ScreenWire);	
	~CalcNode();		
	NodeType *GetNode();
};