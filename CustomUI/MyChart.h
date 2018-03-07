#pragma once


// CMyChart

class CMyChart : public CWnd
{
	DECLARE_DYNAMIC(CMyChart)

public:
	CMyChart();
	virtual ~CMyChart();

protected:
	DECLARE_MESSAGE_MAP()
public:
	void RegisterWindowClass();
	BOOL Create(CWnd* pParentWnd, const RECT & rect, UINT nID, DWORD dwStyle);
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};


