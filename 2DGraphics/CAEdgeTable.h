#pragma once

class CActiveEdgeTable	//��Ч�߱����ݽṹ
{
public:
	double x;			
	int ymax;
	double deltax;			//x�ı仯��
	CActiveEdgeTable *next;	//����	
public:
	CActiveEdgeTable();
	~CActiveEdgeTable();
};

