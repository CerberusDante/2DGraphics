#pragma once

class CActiveEdgeTable	//有效边表数据结构
{
public:
	double x;			
	int ymax;
	double deltax;			//x的变化量
	CActiveEdgeTable *next;	//链表	
public:
	CActiveEdgeTable();
	~CActiveEdgeTable();
};

