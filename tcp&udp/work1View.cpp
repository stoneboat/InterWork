
// work1View.cpp : Cwork1View 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "work1.h"
#endif

#include "work1Doc.h"
#include "work1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cwork1View

IMPLEMENT_DYNCREATE(Cwork1View, CView)

BEGIN_MESSAGE_MAP(Cwork1View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &Cwork1View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// Cwork1View 构造/析构

Cwork1View::Cwork1View()
{
	// TODO: 在此处添加构造代码

}

Cwork1View::~Cwork1View()
{
}

BOOL Cwork1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// Cwork1View 绘制

void Cwork1View::OnDraw(CDC* /*pDC*/)
{
	Cwork1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// Cwork1View 打印


void Cwork1View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL Cwork1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void Cwork1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void Cwork1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void Cwork1View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void Cwork1View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// Cwork1View 诊断

#ifdef _DEBUG
void Cwork1View::AssertValid() const
{
	CView::AssertValid();
}

void Cwork1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Cwork1Doc* Cwork1View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Cwork1Doc)));
	return (Cwork1Doc*)m_pDocument;
}
#endif //_DEBUG


// Cwork1View 消息处理程序
