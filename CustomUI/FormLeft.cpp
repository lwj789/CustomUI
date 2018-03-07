// FormLeft.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "CustomUI.h"
#include "FormLeft.h"
#include "afxdialogex.h"


// CFormLeft 대화 상자입니다.

IMPLEMENT_DYNAMIC(CFormLeft, CDialog)

CFormLeft::CFormLeft(CWnd* pParent /*=NULL*/)
	: CDialog(CFormLeft::IDD, pParent)
{

}

CFormLeft::~CFormLeft()
{
}

void CFormLeft::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CUSTOM, m_wndChart);
}


BEGIN_MESSAGE_MAP(CFormLeft, CDialog)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CFormLeft 메시지 처리기입니다.


// 엔터를 눌렀을때 창이 넘어가는 현상을 막는 함수.
BOOL CFormLeft::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN ||
		pMsg->message == WM_KEYUP)
	{
		if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
			return FALSE; // 엔터나 esc키를 눌러도 적용안되게 막음.
	}

	return CDialog::PreTranslateMessage(pMsg);
}


// 다이얼로그 창 색을 바꾸는 함수.
BOOL CFormLeft::OnEraseBkgnd(CDC* pDC)
{
	CRect rect;
	GetClientRect(&rect);
	pDC->FillSolidRect(&rect, RGB(255, 191, 255));

//	return CDialog::OnEraseBkgnd(pDC);
	return TRUE;
}


BOOL CFormLeft::OnInitDialog()
{
	CDialog::OnInitDialog();

	static CImageList imageList;
	imageList.Create(16, 16, ILC_COLOR32, 3, 0);
	imageList.Add(AfxGetApp()->LoadIcon(IDR_MAINFRAME));

	m_List.Create(this, CRect(0, 100, 200, 500), 1234, WS_CHILD | WS_VISIBLE);
	m_List.SetItemHeight(48);
	m_List.SetImageList(&imageList, TRUE);
	m_List.ShowCheckBox(TRUE);

	CString strTmp = _T("");
	for (int i = 0; i < 50; ++i)
	{
		strTmp.Format(_T("%dth Item"), i);
		m_List.AddString(strTmp, FALSE, 0);
		//		m_wndList.InsertItem(strTmp, FALSE);
	}

	m_List.RedrawWindow();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
