
// work1View.h : Cwork1View ��Ľӿ�
//

#pragma once


class Cwork1View : public CView
{
protected: // �������л�����
	Cwork1View();
	DECLARE_DYNCREATE(Cwork1View)

// ����
public:
	Cwork1Doc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~Cwork1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // work1View.cpp �еĵ��԰汾
inline Cwork1Doc* Cwork1View::GetDocument() const
   { return reinterpret_cast<Cwork1Doc*>(m_pDocument); }
#endif

