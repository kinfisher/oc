#pragma once
#include <iostream>
#include <vector>

using namespace std;
class pointOctree
{
public:
	double coords[3];

	pointOctree();
	pointOctree(double,double);
	pointOctree(double,double,double);
	~pointOctree();
};

