
// work1View.cpp : Cwork1View ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &Cwork1View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// Cwork1View ����/����

Cwork1View::Cwork1View()
{
	// TODO: �ڴ˴���ӹ������

}

Cwork1View::~Cwork1View()
{
}

BOOL Cwork1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// Cwork1View ����

void Cwork1View::OnDraw(CDC* /*pDC*/)
{
	Cwork1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// Cwork1View ��ӡ


void Cwork1View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL Cwork1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void Cwork1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void Cwork1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
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


// Cwork1View ���

#ifdef _DEBUG
void Cwork1View::AssertValid() const
{
	CView::AssertValid();
}

void Cwork1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Cwork1Doc* Cwork1View::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Cwork1Doc)));
	return (Cwork1Doc*)m_pDocument;
}
#endif //_DEBUG


// Cwork1View ��Ϣ�������
