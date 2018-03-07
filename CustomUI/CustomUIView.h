
// CustomUIView.h : CCustomUIView Ŭ������ �������̽�
//

#pragma once
#include "MyChart.h"

							
class CCustomUIView : public CView
{
protected: // serialization������ ��������ϴ�.
	CCustomUIView();
	DECLARE_DYNCREATE(CCustomUIView)

// Ư���Դϴ�.
public:
	CCustomUIDoc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CCustomUIView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:


// ������ �޽��� �� �Լ�
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	CMyChart m_wndChart;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

#ifndef _DEBUG  // CustomUIView.cpp�� ����� ����
inline CCustomUIDoc* CCustomUIView::GetDocument() const
   { return reinterpret_cast<CCustomUIDoc*>(m_pDocument); }
#endif

