#pragma once

class CAEdgeTable
{
public:
	double x;
	int ymax;
	double deltax;
	CAEdgeTable *next;
public:
	CAEdgeTable();
	~CAEdgeTable();
};

