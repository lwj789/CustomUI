#pragma once
#include "resource.h"
#include "MyChart.h"
#include "HotList.h"

// CFormLeft 대화 상자입니다.

class CFormLeft : public CDialog
{
	DECLARE_DYNAMIC(CFormLeft)

public:
	CFormLeft(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CFormLeft();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_FORM_LEFT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	CMyChart m_wndChart;
	CHotList m_List;
	virtual BOOL OnInitDialog();
};
