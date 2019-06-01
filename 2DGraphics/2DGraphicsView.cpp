
// 2DGraphicsView.cpp: CMy2DGraphicsView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "2DGraphics.h"
#endif

#include "2DGraphicsDoc.h"
#include "2DGraphicsView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define Round(d) int(d+0.5)
#define red RGB(255,0,0)
#define green RGB(0,255,0)
#define blue RGB(0,0,255)
#define white RGB(255,255,255)

// CMy2DGraphicsView

IMPLEMENT_DYNCREATE(CMy2DGraphicsView, CView)

BEGIN_MESSAGE_MAP(CMy2DGraphicsView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMy2DGraphicsView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_LINE, &CMy2DGraphicsView::OnLine)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_ELLIPSE, &CMy2DGraphicsView::OnEllipse)
	ON_COMMAND(ID_ANTILINE, &CMy2DGraphicsView::OnAntiline)
	ON_COMMAND(ID_EDGEFILLPOLY, &CMy2DGraphicsView::OnEdgefillpoly)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_FILE_NEW, &CMy2DGraphicsView::OnFileNew)

	ON_COMMAND(ID_SEEDFILLPOLY, &CMy2DGraphicsView::OnSeedfillpoly)
	ON_COMMAND(ID_CHOOSE_COLOR, &CMy2DGraphicsView::OnChooseColor)
	ON_COMMAND(ID_RESET, &CMy2DGraphicsView::OnReset)
	ON_COMMAND(ID_LOADFIG, &CMy2DGraphicsView::OnLoadfig)
	ON_COMMAND(ID_REFLECTX, &CMy2DGraphicsView::OnReflectx)
	ON_COMMAND(ID_REFLECTY, &CMy2DGraphicsView::OnReflecty)
	ON_COMMAND(ID_REFLICTO, &CMy2DGraphicsView::OnReflicto)
	ON_COMMAND(ID_RIGHT, &CMy2DGraphicsView::OnRight)
	ON_COMMAND(ID_LEFT, &CMy2DGraphicsView::OnLeft)
	ON_COMMAND(ID_UP, &CMy2DGraphicsView::OnUp)
	ON_COMMAND(ID_XNEGATIVE, &CMy2DGraphicsView::OnXnegative)
	ON_COMMAND(ID_XPOSITIVE, &CMy2DGraphicsView::OnXpositive)
	ON_COMMAND(ID_YNEGATIVE, &CMy2DGraphicsView::OnYnegative)
	ON_COMMAND(ID_YPOSITIVE, &CMy2DGraphicsView::OnYpositive)
	ON_COMMAND(ID_ROTATE_ANTI_CLOCK, &CMy2DGraphicsView::OnRotateAntiClock)
	ON_COMMAND(ID_ROTATE_CLOCK, &CMy2DGraphicsView::OnRotateClock)
	ON_COMMAND(ID_DECREASE, &CMy2DGraphicsView::OnDecrease)
	ON_COMMAND(ID_INCREASE, &CMy2DGraphicsView::OnIncrease)
END_MESSAGE_MAP()

// CMy2DGraphicsView 构造/析构

CMy2DGraphicsView::CMy2DGraphicsView() noexcept
{
	// TODO: 在此处添加构造代码
	type = 0;
	PolyCount = 0;
}

CMy2DGraphicsView::~CMy2DGraphicsView()
{
}

BOOL CMy2DGraphicsView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMy2DGraphicsView 绘图

void CMy2DGraphicsView::OnDraw(CDC* /*pDC*/)
{
	CMy2DGraphicsDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	DoubleBuffer();
	// TODO: 在此处为本机数据添加绘制代码
}


// CMy2DGraphicsView 打印


void CMy2DGraphicsView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMy2DGraphicsView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMy2DGraphicsView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMy2DGraphicsView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CMy2DGraphicsView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	
}

void CMy2DGraphicsView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMy2DGraphicsView 诊断

#ifdef _DEBUG
void CMy2DGraphicsView::AssertValid() const
{
	CView::AssertValid();
}

void CMy2DGraphicsView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy2DGraphicsDoc* CMy2DGraphicsView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy2DGraphicsDoc)));
	return (CMy2DGraphicsDoc*)m_pDocument;
}
#endif //_DEBUG


// CMy2DGraphicsView 消息处理程序

void CMy2DGraphicsView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CRect rect;
	GetClientRect(&rect);         //获得客户区矩形大小

	CDC *pDC = GetDC();
	if (type != 0)
	{
		if (type == 4) {
			PointList[PolyCount] = point;	     //左键按下的点存在PointList数组里
			POld[PolyCount].x = PointList[PolyCount].x - rect.Width() / 2;
			POld[PolyCount].y = rect.Height() / 2 - PointList[PolyCount].y;
			//得到新坐标系下点坐标，存储在Pold数组里
			PolyCount++;         //点数目+1
			if (PolyCount > 1) BresenhamLine(pDC, PointList[PolyCount - 2], PointList[PolyCount - 1], COLOR, COLOR);
			//如有2个点及以上，连接上一个点和当前点


		}
		else P = point;   //如果画线画椭圆，取点
		if (type == 5)          //5-种子点填充
		{
			seed = point; 			  //取得种子点
			SeedFillPoly(COLOR);       //种子点填充算法
		}


		else P = point;
	}
	CView::OnLButtonDown(nFlags, point);
}


void CMy2DGraphicsView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (type != 0)
	{
		CDC *pDC = GetDC();

		//CRect rect;
		//GetClientRect(&rect);
		//pDC->SetMapMode(MM_ANISOTROPIC);
		//pDC->SetWindowExt(rect.Width(), rect.Height());
		//pDC->SetViewportExt(rect.Width(), -rect.Height());
		//pDC->SetViewportOrg(rect.Width() / 2, rect.Height() / 2);
		//OffsetRect(-rect.Width() / 2, -rect.Height() / 2);

		if (type != 4)
		{
			Q = point;
			//P.x = P.x - rect.Width() / 2;
			//P.y = rect.Height() / 2 - P.y;
			//Q.x = Q.x - rect.Width() / 2;
			//Q.y = rect.Height() / 2 - Q.y;
			COLORREF color1 = COLOR;
			COLORREF color2 = COLOR;
			COLORREF color3 = COLOR;
			switch (type)
			{
			case 1:
				BresenhamLine(pDC, P, Q, color1, color2);
				break;
			case 2:
				BresenhamEllipse(pDC, P, Q, color3);
				break;
			case 3:
				AntiLine(pDC, P, Q);
				break;
			}
		}
		ReleaseDC(pDC);
	}

	CView::OnLButtonUp(nFlags, point);
}

//双缓冲绘图
void CMy2DGraphicsView::DoubleBuffer()
{
	CDC* pDC = GetDC();
	CRect rect;
	GetClientRect(&rect);//获得客户区的大小

	pDC->SetMapMode(MM_ANISOTROPIC);//pDC自定义坐标系
	pDC->SetWindowExt(rect.Width(), rect.Height());//设置窗口范围
	pDC->SetViewportExt(rect.Width(), -rect.Height());//x轴水平向右，y轴垂直向上
	pDC->SetViewportOrg(rect.Width() / 2, rect.Height() / 2);//屏幕中心为原点

	CDC MemDC;//内存DC
	CBitmap NewBitmap, *pOldBitmap;//内存中承载图像的临时位图
	MemDC.CreateCompatibleDC(pDC);//建立与屏幕pDC兼容的MemDC 
	NewBitmap.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());//创建兼容位图 
	pOldBitmap = MemDC.SelectObject(&NewBitmap); //将兼容位图选入MemDC 
	MemDC.FillSolidRect(&rect, pDC->GetBkColor());//按原来背景填充客户区，否则是黑色

	MemDC.SetMapMode(MM_ANISOTROPIC);//MemDC自定义坐标系
	MemDC.SetWindowExt(rect.Width(), rect.Height());
	MemDC.SetViewportExt(rect.Width(), -rect.Height());
	MemDC.SetViewportOrg(rect.Width() / 2, rect.Height() / 2);

	DrawPoly(&MemDC);
	pDC->BitBlt(-rect.Width() / 2, -rect.Height() / 2, rect.Width(), rect.Height(), &MemDC, -rect.Width() / 2, -rect.Height() / 2, SRCCOPY);//将内存位图拷贝到屏幕
	MemDC.SelectObject(pOldBitmap);//恢复位图
	NewBitmap.DeleteObject();//删除位图
	ReleaseDC(pDC);//释放DC	

}



void CMy2DGraphicsView::OnChooseColor()
{
	// TODO: 在此添加命令处理程序代码
	CColorDialog ccd(COLOR, CC_SOLIDCOLOR);
	if (IDOK == ccd.DoModal())//调用颜色对话框选取填充色
		COLOR = ccd.GetColor();	//取得的颜色存储在全局变量COLOR
	else
		return;

}


void CMy2DGraphicsView::OnLine()
{
	// TODO: 在此添加命令处理程序代码
	type = 1;
}





void CMy2DGraphicsView::BresenhamLine(CDC *pDC, CPoint P, CPoint Q, COLORREF color1, COLORREF color2)
{
	// TODO: 在此处添加实现代码.
	CPoint p,t;
	COLORREF color;
	//color = RGB(0, 0, 0);//使用黑色线绘制直线段
	//color = RGB(rand() % 255, rand() % 255, rand() % 255);//随机颜色绘制直线段，若在每个条件内插入这句，每个点为随机色
	if(fabs(P.x-Q.x)<1e-6)//绘制垂涎
	{
		if(P.y>Q.y)//交换顶点，使得起始点低于中点
		{
			t=P;P=Q;Q=t;
		}
		for(p=P;p.y<P.y;p.y++)
		{
			color = double(p.y-P.y)/(Q.y-P.y)*color1+ double(Q.y-p.y)/(Q.y-P.y)*color2;//使用渐变颜色线绘制直线段
			pDC->SetPixelV(p,color);
		}
	}
	else
	{
		double k, d;
		k = double(P.y - Q.y) / (P.x - Q.x);
		if (k > 1.0)//绘制k>1
		{
			if (P.y > Q.y)
			{
				t = P; P = Q; Q = t;
			}
			d = 1 - 0.5*k;
			for (p = P; p.y < Q.y; p.y++)
			{
				color = double(p.y - P.y) / (Q.y - P.y)*color1 + double(Q.y - p.y) / (Q.y - P.y)*color2;
				pDC->SetPixelV(p, color);
				if (d >= 0)
				{
					p.x++;
					d += 1 - k;
				}
				else
					d += 1;
			}
		}
		if (0.0 <= k && k <= 1.0)//绘制0<=k<=1
		{
			if (P.x > Q.x)
			{
				t = P; P = Q; Q = t;
			}
			d = 0.5 - k;
			for (p = P; p.x < Q.x; p.x++)
			{
				color = double(p.x - P.x) / (Q.x - P.x)*color1 + double(Q.x - p.x) / (Q.x - P.x)*color2;
				pDC->SetPixelV(p, color);
				if (d < 0)
				{
					p.y++;
					d += 1 - k;
				}
				else
					d -= k;
			}
		}
		if (k >= -1.0 && k < 0.0)//绘制-1<=k<0
		{
			if (P.x > Q.x)
			{
				t = P; P = Q; Q = t;
			}
			d = -0.5 - k;
			for (p = P; p.x < Q.x; p.x++)
			{
				color = double(p.x - P.x) / (Q.x - P.x)*color1 + double(Q.x - p.x) / (Q.x - P.x)*color2;
				pDC->SetPixelV(p, color);
				if (d > 0)
				{
					p.y--;
					d -= 1 + k;
				}
				else
					d -= k;
			}
		}
		if (k < -1.0)//绘制k<-1 
		{
			if (P.y < Q.y)
			{
				t = P; P = Q; Q = t;
			}
			d = -1 - 0.5*k;
			for (p = P; p.y > Q.y; p.y--)
			{
				color = double(p.y - P.y) / (Q.y - P.y)*color1 + double(Q.y - p.y) / (Q.y - P.y)*color2;
				pDC->SetPixelV(p, color);
				if (d < 0)
				{
					p.x++;
					d -= 1 + k;
				}
				else
					d -= 1; ;
			}
		}
	}
}


void CMy2DGraphicsView::OnEllipse()
{
	// TODO: 在此添加命令处理程序代码
	type = 2;
}


void CMy2DGraphicsView::BresenhamEllipse(CDC *pDC, CPoint P, CPoint Q, COLORREF color)
{
	// TODO: 在此处添加实现代码.
	CPoint p;
	double d1, d2;
	long a, b;
	a = fabs(P.x - Q.x) / 2;
	b = fabs(P.y - Q.y) / 2;
	p.x = 0;
	p.y = b;
	d1 = b * b + a * a*(-b + 0.25);
	EllipsePoint(p, pDC, color);
	while (b*b*(p.x + 1) < a*a*(p.y - 0.5))
	{
		if (d1 < 0)
			d1 += b * b*(2 * p.x + 3);
		else
		{
			d1 += b * b*(2 * p.x + 3) + a * a*(-2 * p.y + 2);
			p.y--;
		}
		p.x++;
		EllipsePoint(p, pDC, color);
	}
	d2 = b * b*(p.x + 0.5)*(p.x + 0.5) + a * a*(p.y - 1)*(p.y - 1) - a * a*b*b;
	while (p.y > 0)
	{
		if (d2 < 0)
		{
			d2 += b * b*(2 * p.x + 2) + a * a*(-2 * p.y + 3);
			p.x++;
		}
		else
			d2 += a * a*(-2 * p.y + 3);
		p.y--;
		EllipsePoint(p, pDC, color);
	}
}


void CMy2DGraphicsView::EllipsePoint(CPoint point, CDC *pDC, COLORREF color)
{
	// TODO: 在此处添加实现代码.
	CPoint pc = CPoint((P.x + Q.x) / 2.0, (P.y + Q.y) / 2.0);
	pDC->SetPixelV(point.x + pc.x, point.y + pc.y, color);
	pDC->SetPixelV(-point.x + pc.x, point.y + pc.y, color);
	pDC->SetPixelV(point.x + pc.x, -point.y + pc.y, color);
	pDC->SetPixelV(-point.x + pc.x, -point.y + pc.y, color);
}


void CMy2DGraphicsView::OnAntiline()
{
	// TODO: 在此添加命令处理程序代码
	type = 3;
}


void CMy2DGraphicsView::AntiLine(CDC *pDC, CPoint P, CPoint Q)
{
	// TODO: 在此处添加实现代码.
	CPoint p, t;
	COLORREF color;
	color = COLOR;
	if (fabs(P.x - Q.x) < 1e-6)//绘制垂线
	{
		if (P.y > Q.y)//交换顶点，是的起始点低于终点
		{
			t = P; P = Q; Q = t;
		}
		for (p = P; p.y < P.y; p.y++)
			pDC->SetPixelV(p, color);
	}
	else
	{
		double k, e;
		k = double(Q.y - P.y) / (Q.x - P.x);
		if (k > 1.0)                      //绘制k>1
		{
			if (P.y > Q.y)
			{
				t = P; P = Q; Q = t;
			}
			for (p = P, e = 1 / k; p.y < Q.y; p.y++)
			{
				pDC->SetPixelV(p, RGB(e * 255, e * 255, e * 255));
				pDC->SetPixelV(p.x + 1, p.y, RGB((1.0 - e) * 255, (1.0 - e) * 255, (1.0 - e) * 255));
				e = e + 1 / k;
				if (e >= 1.0)
				{
					p.x++;
					e--;
				}
			}
		}
		if (0.0 <= k && k <= 1.0)//绘制0<k<1
		{
			if (P.x > Q.x)
			{
				t = P; P = Q; Q = t;
			}
			for (p = P, e = k; p.x < Q.x; p.x++)
			{
				pDC->SetPixelV(p, RGB(e * 255, e * 255, e * 255));
				pDC->SetPixelV(p.x, p.y + 1, RGB((1.0 - e) * 255, (1.0 - e) * 255, (1.0 - e) * 255));
				e = e + k;
				if (e >= 1.0)
				{
					p.y++;
					e--;
				}
			}
		}
		if (k >= -1.0 && k < 0.0)//绘制-1=<k<=0
		{
			if (P.x > Q.x)
			{
				t = P; P = Q; Q = t;
			}
			for (p = P, e = -k; p.x < Q.x; p.x++)
			{
				pDC->SetPixelV(p, RGB(e * 255, e * 255, e * 255));
				pDC->SetPixelV(p.x, p.y - 1, RGB((1.0 - e) * 255, (1.0 - e) * 255, (1.0 - e) * 255));
				e = e - k;
				if (e >= 1.0)
				{
					p.y--;
					e--;
				}
			}
		}
		if (k < -1.0)//绘制k<-1 
		{
			if (P.y < Q.y)
			{
				t = P; P = Q; Q = t;
			}
			for (p = P, e = -1 / k; p.y > Q.y; p.y--)
			{
				pDC->SetPixelV(p, RGB(e * 255, e * 255, e * 255));
				pDC->SetPixelV(p.x + 1, p.y, RGB((1.0 - e) * 255, (1.0 - e) * 255, (1.0 - e) * 255));
				e = e - 1 / k;
				if (e >= 1.0)
				{
					p.x++;
					e--;
				}
			}
		}
	}
}


void CMy2DGraphicsView::OnEdgefillpoly()
{
	// TODO: 在此添加命令处理程序代码
	type = 4;
}


void CMy2DGraphicsView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CRect rect;
	CDC *pDC = GetDC();
	GetClientRect(&rect);

	if (type == 4)     //4--多边形扫描线填充时
	{
		BresenhamLine(pDC, PointList[PolyCount - 1], PointList[0], COLOR, COLOR);
		//画出多边形最后一条首尾相连线
		PointList[PolyCount] = PointList[0];  //实现多边形点列首尾相连，封闭多边形
		POld[PolyCount].x = PointList[PolyCount].x - rect.Width() / 2;
		POld[PolyCount].y = rect.Height() / 2 - PointList[PolyCount].y;
		//type = 41;                     //41--开始准备填充，不在允许左键按下取点。
	}
	ReleaseDC(pDC);
	CView::OnRButtonDown(nFlags, point);

	if (type ==5 )
	{
		BresenhamLine(pDC, PointList[PolyCount - 1], PointList[0], RGB(0, 0, 0), RGB(0, 0, 0));
	}

	ReleaseDC(pDC);

	CView::OnRButtonDown(nFlags, point);
}


void CMy2DGraphicsView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDC *pDC = GetDC();
	if (type == 4) {
		EdgeFillPoly(pDC, PointList, red);
		PolyCount = 0;
		type = 0;
	}
	if (type == 5) {
		//EdgeFillPoly2(pDC, PointList, red);
		PolyCount = 0;
		type = 0;
	}
	ReleaseDC(pDC);

	CView::OnLButtonDblClk(nFlags, point);
}


void CMy2DGraphicsView::EdgeFillPoly(CDC *pDC, CPoint *P, COLORREF color)
{
	// TODO: 在此处添加实现代码.
	PolyCount--;
	PointList[PolyCount] = PointList[0];	//多边形首尾相接
	CreateBucket(P);					//生成桶表，并求出ymin，ymax

	CActiveEdgeTable *edge;
	AETHead = new CActiveEdgeTable;		////有效边表的头指针， 并把next置空

	AETHead->next = NULL;				//下一个地址为NULL

	int y = ymin;
	//扫描线从ymin至ymax依次填充
	while (y < ymax)
	{
		edge = new CActiveEdgeTable;	//创建指向有效边表数据结构的指针edge
		edge = Bucket[y].p;				//从桶表中取得扫描线对应有效边
		while (edge != NULL)
		{
			AddEdge(*edge);				//边插入
			edge = edge->next;			//遍历所有边进行插入
		}
		SortEdge();						
		fillcolor(y);					//两两配对着色
		y++;							//下一条扫描线
		UpdateEdge(y);					//有效边表更新
		edge = NULL;
	}
}


//桶表的创建
void CMy2DGraphicsView::CreateBucket(CPoint *P)
{
	int y;
	ymin = ymax = P[0].y;

	CActiveEdgeTable *edge;

	//将桶表所有值设为NULL
	for (int i = 1; i < 601; i++)
	{
		Bucket[i].p = NULL;				
	}

	for (int i = 0; i < PolyCount; i++)
	{
		edge = new CActiveEdgeTable;	//创建有效边表指针edge
		if (P[i].y < P[i + 1].y)
		{
			y = P[i].y;
			edge->x = P[i].x;			//有效边的x值为起点的x值
			edge->ymax = P[i + 1].y;	//有效边的ymax值下一条有效边的起点的y值
			edge->deltax = double(P[i + 1].x - P[i].x) / (P[i + 1].y - P[i].y);
										//x的变化量为斜率的倒数
			edge->next = Bucket[y].p;	//定义有效边表的下一项
			Bucket[y].p = edge;			//扫描线对应桶表指向有效边

			//随着边的遍历不断确认ymax及ymin
			if (P[i].y < ymin) 
				ymin = P[i].y;
			if (P[i + 1].y > ymax)
				ymax = P[i + 1].y;
		}
		if (P[i].y > P[i + 1].y)
		{
			y = P[i + 1].y;
			edge->x = P[i + 1].x;
			edge->ymax = P[i].y;
			edge->deltax = double(P[i + 1].x - P[i].x) / (P[i + 1].y - P[i].y);
			edge->next = Bucket[y].p;
			Bucket[y].p = edge;
			if (P[i + 1].y < ymin)
				ymin = P[i + 1].y;
			if (P[i].y > ymax)
				ymax = P[i].y;
		}
		edge = NULL;			//地址设置为NULL
	}
}


//将扫描线对应的所有新边插入到数据结构中，插入操作到保证CActiveEdgeTable还是有序表，统一表示为一AETHead为头结点的链表
void CMy2DGraphicsView::AddEdge(CActiveEdgeTable edge)
{
	CActiveEdgeTable *p, *q, *s;
	s = new CActiveEdgeTable;
	*s = edge;
	q = AETHead;
	p = q->next;
	while (p)
	{
		if ((s->x < p->x) || (s->x == p->x&&s->deltax < p->deltax))    p = NULL;	//如满足条件，则p选定
		else { q = p;  p = p->next; }
	}
	s->next = q->next; //把边插入到p结构前
	q->next = s;
}


//为扫描线两两填充
void CMy2DGraphicsView::fillcolor(int y)
{
	CDC *pDC = GetDC();
	CActiveEdgeTable *temp = AETHead->next;
	while (temp != NULL && temp->next != NULL)
	{
		BresenhamLine(pDC, CPoint(temp->x, y), CPoint(temp->next->x, y), red, red);	//使用BresenhamLine函数绘制扫描线，指定颜色为红色
		temp = temp->next->next;	//转至下一组以两个交点为端点的扫描线
	}
	temp = NULL;
}


//有效边表中结点排序
void CMy2DGraphicsView::SortEdge()
{

}


//更新边表中的x值，至结点时更新有效边表,两两配对填充
void CMy2DGraphicsView::UpdateEdge(int y)
{
	CActiveEdgeTable *temp = AETHead;
	while (temp->next != NULL)
	{
		if (temp->next->ymax == y)
			temp->next = temp->next->next;
		else {
			temp->next->x += temp->next->deltax;
			temp = temp->next;
		}
	}
	temp = NULL;
}


void CMy2DGraphicsView::OnFileNew()
{
	// TODO: 在此添加命令处理程序代码
	if (type == 4)
		PolyCount = 0;
	else if (type == 5)
		PolyCount = 0;
	Invalidate();
}


void CMy2DGraphicsView::OnSeedfillpoly()
{
	// TODO: 在此添加命令处理程序代码
	type = 5;
}



void CMy2DGraphicsView::DrawPoly(CDC *pDC)
{
	CRect rect;
	GetClientRect(&rect);//获得客户区的大小
	pDC->MoveTo(0, -rect.Height() / 2);
	pDC->LineTo(0, rect.Height() / 2);
	pDC->MoveTo(-rect.Width() / 2, 0);
	pDC->LineTo(rect.Width() / 2, 0);
	pDC->MoveTo(POld[0]);
	pDC->Ellipse(-3, -3, 3, 3);
	for (int i = 0; i < PolyCount; i++)
		pDC->LineTo(POld[i + 1]);

}


void CMy2DGraphicsView::SeedFillPoly(COLORREF color)
{
	// TODO: 在此处添加实现代码.
}




//重置多边形
void CMy2DGraphicsView::OnReset()
{
	// TODO: 在此添加命令处理程序代码
	CRect rect;
	GetClientRect(&rect);//获得客户区的大小
	for (int i = 0; i <= PolyCount; i++)
	{
		POld[i].x = PointList[i].x - rect.Width() / 2;
		POld[i].y = rect.Height() / 2 - PointList[i].y;
	}
	Invalidate(FALSE);

}


void CMy2DGraphicsView::OnLoadfig()
{
	// TODO: 在此添加命令处理程序代码
	CDC *pDC = GetDC();//定义设备上下文指针 
	CRect rect;
	GetClientRect(&rect);              //获得客户区的大小
	CDC MemDC;                         //内存DC
	CBitmap NewBitmap, *pOldBitmap;     //内存中承载图像的位图
	MemDC.CreateCompatibleDC(pDC);     //建立与屏幕pDC兼容的MemDC 
	NewBitmap.LoadBitmap(IDB_BITMAP1);  //导入空心汉字位图
	pOldBitmap = MemDC.SelectObject(&NewBitmap);       //将兼容位图选入MemDC 
	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &MemDC, 0, 0, SRCCOPY);
	//将内存位图拷贝到屏幕
	MemDC.SelectObject(pOldBitmap);    //恢复位图
	NewBitmap.DeleteObject();          //删除位图
	MemDC.DeleteDC();                  //删除MemDC
	ReleaseDC(pDC);                   //释放DC

}


void CMy2DGraphicsView::OnReflectx()
{
	// TODO: 在此添加命令处理程序代码
}


void CMy2DGraphicsView::OnReflecty()
{
	// TODO: 在此添加命令处理程序代码
}


void CMy2DGraphicsView::OnReflicto()
{
	// TODO: 在此添加命令处理程序代码
}


void CMy2DGraphicsView::OnRight()
{
	// TODO: 在此添加命令处理程序代码
}


void CMy2DGraphicsView::OnLeft()
{
	// TODO: 在此添加命令处理程序代码
	Translate(-10, 0);   //x,y平移的单位
	Invalidate();       //重绘图形

}


void CMy2DGraphicsView::OnUp()
{
	// TODO: 在此添加命令处理程序代码
}


void CMy2DGraphicsView::OnXnegative()
{
	// TODO: 在此添加命令处理程序代码
	Shear(0, -1);  //调用错切函数
	Invalidate(FALSE);    //重绘

}


void CMy2DGraphicsView::OnXpositive()
{
	// TODO: 在此添加命令处理程序代码
}


void CMy2DGraphicsView::OnYnegative()
{
	// TODO: 在此添加命令处理程序代码
}


void CMy2DGraphicsView::OnYpositive()
{
	// TODO: 在此添加命令处理程序代码
}


void CMy2DGraphicsView::OnRotateAntiClock()
{
	// TODO: 在此添加命令处理程序代码
}


void CMy2DGraphicsView::OnRotateClock()
{
	// TODO: 在此添加命令处理程序代码
}


void CMy2DGraphicsView::OnDecrease()
{
	// TODO: 在此添加命令处理程序代码
}


void CMy2DGraphicsView::OnIncrease()
{
	// TODO: 在此添加命令处理程序代码
	Zoom(2, 2);     //调用Zoom函数，放大系数2,2
	Invalidate();  //重绘

}


// 矩阵相乘
void CMy2DGraphicsView::Multi()
{
	// TODO: 在此处添加实现代码.
	CPoint Temp[100];
	for (int i = 0; i <= PolyCount; i++)
		Temp[i] = POld[i];
	for (int i = 0; i <= PolyCount; i++)
	{
		POld[i].x = Temp[i].x*T[0][0] + Temp[i].y*T[1][0] + T[2][0];
		POld[i].y = Temp[i].x*T[0][1] + Temp[i].y*T[1][1] + T[2][1];
	}

}


// 平移变换矩阵
void CMy2DGraphicsView::Translate(int dx, int dy)
{
	// TODO: 在此处添加实现代码.
	Identity();     //单位矩阵T
	T[2][0] = dx; T[2][1] = dy;       //平移矩阵，T改变
	Multi();              //矩阵相乘

}


// 错切变换矩阵
void CMy2DGraphicsView::Shear(double b, double c)
{
	// TODO: 在此处添加实现代码.
}


// 旋转变换矩阵
void CMy2DGraphicsView::Rotate(double beta)
{
	// TODO: 在此处添加实现代码.
}


// 比例变换矩阵
void CMy2DGraphicsView::Zoom(double sx, double sy)
{
	// TODO: 在此处添加实现代码.
}


// 生成单位矩阵
void CMy2DGraphicsView::Identity()
{
	// TODO: 在此处添加实现代码.
	T[0][0] = 1.0; T[0][1] = 0.0; T[0][2] = 0.0;
	T[1][0] = 0.0; T[1][1] = 1.0; T[1][2] = 0.0;
	T[2][0] = 0.0; T[2][1] = 0.0; T[2][2] = 1.0;

}
