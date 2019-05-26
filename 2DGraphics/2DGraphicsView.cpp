
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
