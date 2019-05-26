
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
END_MESSAGE_MAP()

// CMy2DGraphicsView 构造/析构

CMy2DGraphicsView::CMy2DGraphicsView() noexcept
{
	// TODO: 在此处添加构造代码

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
	ClientToScreen(&point);
	OnContextMenu(this, point);
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


void CMy2DGraphicsView::OnLine()
{
	// TODO: 在此添加命令处理程序代码
	type = 1;
}


void CMy2DGraphicsView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CDC *pDC = GetDC();
	if (type != 0)
		P = point;
	CView::OnLButtonDown(nFlags, point);
}


void CMy2DGraphicsView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (type != 0)
	{
		CDC *pDC = GetDC();
		Q = point;
		CRect rect;
		GetClientRect(&rect);
		pDC->SetMapMode(MM_ANISOTROPIC);
		pDC->SetWindowExt(rect.Width(), rect.Height());
		pDC->SetViewportExt(rect.Width(), -rect.Height());
		pDC->SetViewportOrg(rect.Width() / 2, rect.Height() / 2);
		rect.OffsetRect(-rect.Width() / 2, -rect.Height() / 2);

		P.x = P.x - rect.Width() / 2;
		P.y = rect.Height() / 2 - P.y;
		Q.x = Q.x - rect.Width() / 2;
		Q.y = rect.Height() / 2 - Q.y;
		COLORREF color1 = RGB(255, 0, 0);
		COLORREF color2 = RGB(0, 255, 0);
		COLORREF color3 = RGB(0, 0, 0);
		switch (type)
		{
		case 1:
			BresenhamLine(pDC, P, Q, color1, color2);
			break;
		case 2:
			BresenhamEllipse(pDC, P, Q, color3);
			break;
		}
	}

	CView::OnLButtonUp(nFlags, point);
}


void CMy2DGraphicsView::BresenhamLine(CDC *pDC, CPoint P, CPoint Q, COLORREF color1, COLORREF color2)
{
	// TODO: 在此处添加实现代码.
	CPoint p,t;
	COLORREF color;
	color = RGB(0, 0, 0);//使用黑色线绘制直线段
	//color = RGB(rand() % 255, rand() % 255, rand() % 255);//随机颜色绘制直线段，若在每个条件内插入这句，每个点为随机色
	if(fabs(P.x-Q.x)<1e-6)//绘制垂涎
	{
		if(P.y>Q.y)//交换顶点，使得起始点低于中点
		{
			t=P;P=Q;Q=t;
		}
		for(p=P;p.y<P.y;p.y++)
		{
			//color = double(p.y-P.y)/(Q.y-P.y)*color1+ double(Q.y-p.y)/(Q.y-P.y)*color2;//使用渐变颜色线绘制直线段
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
				//color = double(p.y - P.y) / (Q.y - P.y)*color1 + double(Q.y - p.y) / (Q.y - P.y)*color2;
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
				//color = double(p.x - P.x) / (Q.x - P.x)*color1 + double(Q.x - p.x) / (Q.x - P.x)*color2;
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
				//color = double(p.x - P.x) / (Q.x - P.x)*color1 + double(Q.x - p.x) / (Q.x - P.x)*color2;
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
				//color = double(p.y - P.y) / (Q.y - P.y)*color1 + double(Q.y - p.y) / (Q.y - P.y)*color2;
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
	double d1, d2, a, b;
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


