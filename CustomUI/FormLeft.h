#pragma once
#include "resource.h"
#include "MyChart.h"
#include "HotList.h"

// CFormLeft ��ȭ �����Դϴ�.

class CFormLeft : public CDialog
{
	DECLARE_DYNAMIC(CFormLeft)

public:
	CFormLeft(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CFormLeft();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_FORM_LEFT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	CMyChart m_wndChart;
	CHotList m_List;
	virtual BOOL OnInitDialog();
};
