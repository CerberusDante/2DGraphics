
// 2DGraphicsView.h: CMy2DGraphicsView 类的接口
//

#pragma once


class CMy2DGraphicsView : public CView
{
//自定义变量,函数
public:
	int type;
	CPoint P, Q;
	

public:
	void BresenhamLine(CDC *pDC, CPoint P, CPoint Q, COLORREF color1, COLORREF color2);
	void BresenhamEllipse(CDC *pDC, CPoint P, CPoint Q, COLORREF color);
	void EllipsePoint(CPoint point, CDC *pDC, COLORREF color);



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
	
};

#ifndef _DEBUG  // 2DGraphicsView.cpp 中的调试版本
inline CMy2DGraphicsDoc* CMy2DGraphicsView::GetDocument() const
   { return reinterpret_cast<CMy2DGraphicsDoc*>(m_pDocument); }
#endif

