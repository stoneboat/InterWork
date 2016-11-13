
// work1View.h : Cwork1View 类的接口
//

#pragma once


class Cwork1View : public CView
{
protected: // 仅从序列化创建
	Cwork1View();
	DECLARE_DYNCREATE(Cwork1View)

// 特性
public:
	Cwork1Doc* GetDocument() const;

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
	virtual ~Cwork1View();
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
};

#ifndef _DEBUG  // work1View.cpp 中的调试版本
inline Cwork1Doc* Cwork1View::GetDocument() const
   { return reinterpret_cast<Cwork1Doc*>(m_pDocument); }
#endif

