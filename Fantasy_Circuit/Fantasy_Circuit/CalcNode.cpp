#include "stdafx.h"
#include "CalcNode.h"

CalcNode::CalcNode(cliext::vector<Point> ScreenWire)
{
	Node = new NodeType;
	Wire = ScreenWire;		
	analyze();
}

CalcNode::~CalcNode()
{
	delete Node;
}

void CalcNode::analyze()
{
	const int diffpix = 20;
	for(int i=0;i<Wire.size();i+=2)
	{
		vector<int> Found_set;
		int x1 = Wire[i].X/diffpix;
		int y1 = Wire[i].Y/diffpix;
		int x2 = Wire[i+1].X/diffpix;
		int y2 = Wire[i+1].Y/diffpix;	
		for(int j=0;j<Node->size();j++)
		{
			if(Find_in_set(j, x1, y1, x2, y2) == true)
				Found_set.push_back(j);
		}
		int be_insert = Node->size();
		if(Found_set.empty()==false)
		{
			be_insert = Found_set[0];
			for(int j=1;j<Found_set.size();j++)				
				(*Node)[be_insert].insert((*Node)[Found_set[j]].begin(), (*Node)[Found_set[j]].end());		
		}
		else
			Node->resize(Node->size()+1);
		merge(be_insert, x1, y1, x2, y2);
		for(int j=Found_set.size()-1;j>=1;j--)			
			Node->erase(Node->begin() + Found_set[j]);			
	}
		display();
}

bool CalcNode::Find_in_set(int n, int x1, int y1, int x2, int y2)
{				
	if(x1 > x2)
		swap(x1, x2);
	if(y1 > y2)
		swap(y1, y2);
	for(int i=x1;i<=x2;i++)		
		for(int j=y1;j<=y2;j++)			
			if((*Node)[n].find(make_pair(i, j)) != (*Node)[n].end())
				return true;					
	return false;
}

void CalcNode::merge(int n, int x1, int y1, int x2, int y2)
{
	if(x1 > x2)
		swap(x1, x2);
	if(y1 > y2)
		swap(y1, y2);
	for(int i=x1;i<=x2;i++)		
		for(int j=y1;j<=y2;j++)			
			(*Node)[n].insert(make_pair(i, j));					
}

void CalcNode::display()
{
	set<pair<int, int>>::iterator p;
	cout << "Node Number: " << Node->size() << endl;
	for(int i=0;i<Node->size();i++)
	{
		cout << "========= Node " << i << " ===========" <<endl;
		for(p=(*Node)[i].begin();p!=(*Node)[i].end();p++)			
			cout << "(" << (*p).first << " , " << (*p).second << ")" << "  ";
		cout << endl;
	}
	cout << endl;
}

NodeType *CalcNode::GetNode()
{
	return Node;
}