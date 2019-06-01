
// 2DGraphicsView.h: CMy2DGraphicsView 类的接口
//

#include "CBucket.h"
#include "CAEdgeTable.h"

#pragma once



class CMy2DGraphicsView : public CView
{
//自定义变量,函数
public:
	int type;
	int PolyCount;
	long xmin, xmax;
	long ymin, ymax;
	int top;    //栈指标
	CPoint P, Q;
	CPoint seed;
	                 
	CPoint PointList[100];
	CBucket Bucket[601];		
	CActiveEdgeTable *AETHead;	//定义有效边表头节点
	CPoint POld[100];            //存储原始多边形点列
	COLORREF COLOR;              //当前颜色
	CPoint stack[100];           //堆栈
	double T[3][3];

public:
	void BresenhamLine(CDC *pDC, CPoint P, CPoint Q, COLORREF color1, COLORREF color2);
	void BresenhamEllipse(CDC *pDC, CPoint P, CPoint Q, COLORREF color);
	void EllipsePoint(CPoint point, CDC *pDC, COLORREF color);
	void AntiLine(CDC *pDC, CPoint P, CPoint Q);
	void EdgeFillPoly(CDC *pDC, CPoint *P, COLORREF color);
	void CreateBucket(CPoint *P);
	
	void fillcolor(int y);
	void AddEdge(CActiveEdgeTable edge);
	void SortEdge();
	void UpdateEdge(int y);

	void DoubleBuffer();
	void DrawPoly(CDC *pDC);

	void Multi();
	void Translate(int dx, int dy);
	void Shear(double b, double c);
	void Rotate(double beta);
	void Zoom(double sx, double sy);
	void Identity();


protected: // 仅从序列化创建
	CMy2DGraphicsView() noexcept;
	DECLARE_DYNCREATE(CMy2DGraphicsView)

// 特性
public:
	CMy2DGraphicsDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CMy2DGraphicsView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLine();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	
	afx_msg void OnEllipse();
	
	afx_msg void OnAntiline();

	afx_msg void OnEdgefillpoly();
	
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	
	afx_msg void OnFileNew();
//	afx_msg void OnEdgefillpoly2();

	afx_msg void OnSeedfillpoly();
	
	void SeedFillPoly(COLORREF color);
	afx_msg void OnChooseColor();
	afx_msg void OnReset();
	afx_msg void OnLoadfig();
	afx_msg void OnReflectx();
	afx_msg void OnReflecty();
	afx_msg void OnReflicto();
	afx_msg void OnRight();
	afx_msg void OnLeft();
	afx_msg void OnUp();
	afx_msg void OnXnegative();
	afx_msg void OnXpositive();
	afx_msg void OnYnegative();
	afx_msg void OnYpositive();
	afx_msg void OnRotateAntiClock();
	afx_msg void OnRotateClock();
	afx_msg void OnDecrease();
	afx_msg void OnIncrease();
	
};

#ifndef _DEBUG  // 2DGraphicsView.cpp 中的调试版本
inline CMy2DGraphicsDoc* CMy2DGraphicsView::GetDocument() const
   { return reinterpret_cast<CMy2DGraphicsDoc*>(m_pDocument); }
#endif

