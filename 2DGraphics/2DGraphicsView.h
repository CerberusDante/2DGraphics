
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
	int ymin, ymax;

	CPoint P, Q;
	CPoint PointList[100];
	CBucket Bucket[601];
	CAEdgeTable *AETHead;

public:
	void BresenhamLine(CDC *pDC, CPoint P, CPoint Q, COLORREF color1, COLORREF color2);
	void BresenhamEllipse(CDC *pDC, CPoint P, CPoint Q, COLORREF color);
	void EllipsePoint(CPoint point, CDC *pDC, COLORREF color);
	void AntiLine(CDC *pDC, CPoint P, CPoint Q);
	void EdgeFillPoly(CDC *pDC, CPoint *P, COLORREF color);
	void CreateBucket(CPoint *P);
	
	void fillcolor(int y);
	void AddEdge(CAEdgeTable edge);
	void SortEdge();
	void UpdateEdge(int y);

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
};

#ifndef _DEBUG  // 2DGraphicsView.cpp 中的调试版本
inline CMy2DGraphicsDoc* CMy2DGraphicsView::GetDocument() const
   { return reinterpret_cast<CMy2DGraphicsDoc*>(m_pDocument); }
#endif

