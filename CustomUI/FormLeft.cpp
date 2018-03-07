// FormLeft.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "CustomUI.h"
#include "FormLeft.h"
#include "afxdialogex.h"


// CFormLeft ��ȭ �����Դϴ�.

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


// CFormLeft �޽��� ó�����Դϴ�.


// ���͸� �������� â�� �Ѿ�� ������ ���� �Լ�.
BOOL CFormLeft::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN ||
		pMsg->message == WM_KEYUP)
	{
		if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
			return FALSE; // ���ͳ� escŰ�� ������ ����ȵǰ� ����.
	}

	return CDialog::PreTranslateMessage(pMsg);
}


// ���̾�α� â ���� �ٲٴ� �Լ�.
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
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}
