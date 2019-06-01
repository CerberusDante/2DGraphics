#include "CAEdgeTable.h"

class CBucket
{
public:

	CBucket();
	~CBucket();

public:

	CActiveEdgeTable *p;	//指向扫描线对应有效边的指针

};
