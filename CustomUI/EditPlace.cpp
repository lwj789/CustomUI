// EditPlace.cpp : implementation file
//

#include "stdafx.h"
//#include "WormGenIPv6.h"
#include "EditPlace.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditPlace

CEditPlace::CEditPlace()
{
}

CEditPlace::~CEditPlace()
{
}


BEGIN_MESSAGE_MAP(CEditPlace, CEdit)
	//{{AFX_MSG_MAP(CEditPlace)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_MBUTTONDOWN()
	ON_WM_KILLFOCUS()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditPlace message handlers
/////////////////////////////////////////////////////////////////////////////
BOOL CEditPlace::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message == WM_KEYDOWN)
	{
		NMHDR nmHdr;
		::ZeroMemory(&nmHdr, sizeof(NMHDR));

		if((int)pMsg->wParam == VK_ESCAPE)
		{
			ShowWindow(SW_HIDE);

			nmHdr.hwndFrom = m_hWnd;
			nmHdr.idFrom = GetDlgCtrlID();
			nmHdr.code = EHC_EDIT_CLOSE;
			GetParent()->SendMessage(WM_NOTIFY, (LPARAM)NULL, (WPARAM)&nmHdr);

			ReleaseCapture();
			return TRUE;
		}
		else if((int)pMsg->wParam == VK_RETURN)
		{
			nmHdr.hwndFrom = m_hWnd;
			nmHdr.idFrom = GetDlgCtrlID();
			nmHdr.code = EHC_EDIT_CHANGED;
			GetParent()->SendMessage(WM_NOTIFY, (LPARAM)NULL, (WPARAM)&nmHdr);

			ReleaseCapture();
			return TRUE;
		}
		else if((int)pMsg->wParam == VK_TAB)
		{
			nmHdr.hwndFrom = m_hWnd;
			nmHdr.idFrom = GetDlgCtrlID();
			nmHdr.code = EHC_EDIT_TAB;

			if(::GetKeyState(VK_SHIFT) & 0x8000)	GetParent()->SendMessage(WM_NOTIFY, TRUE, (LPARAM)&nmHdr);
			else									GetParent()->SendMessage(WM_NOTIFY, NULL, (LPARAM)&nmHdr);

			ReleaseCapture();
			return TRUE;
		}
		else if((int)pMsg->wParam == 'c' || (int)pMsg->wParam == 'C')
		{
			if(::GetKeyState(VK_CONTROL) & 0x8000)	Copy();
		}
		else if((int)pMsg->wParam == 'v' || (int)pMsg->wParam == 'V')
		{
			if(::GetKeyState(VK_CONTROL) & 0x8000)	Paste();
		}
		else if((int)pMsg->wParam == 'a' || (int)pMsg->wParam == 'A')
		{
			if(::GetKeyState(VK_CONTROL) & 0x8000)	SetSel(0, -1);
		}
	}

	return CEdit::PreTranslateMessage(pMsg);
}

int CEditPlace::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CEdit::OnCreate(lpCreateStruct) == -1)
		return -1;

	CClientDC dc(this);
	m_Font.CreatePointFont(90, _T("Arial"), &dc);
	SetFont(&m_Font);

	return 0;
}

void CEditPlace::OnSetFocus(CWnd* pOldWnd)
{
	CEdit::OnSetFocus(pOldWnd);

//	ReleaseCapture();
	SetCapture();
}

void CEditPlace::OnLButtonDown(UINT nFlags, CPoint point)
{
	CEdit::OnLButtonDown(nFlags, point);

	ClientToScreen(&point);
	if(CWnd::WindowFromPoint(point) != this)
	{
		ReleaseCapture();
		ShowWindow(SW_HIDE);
	}
}

void CEditPlace::OnRButtonDown(UINT nFlags, CPoint point)
{
	CEdit::OnRButtonDown(nFlags, point);

	ClientToScreen(&point);
	if(CWnd::WindowFromPoint(point) != this)
	{
		ReleaseCapture();
		ShowWindow(SW_HIDE);
	}
}

void CEditPlace::OnMButtonDown(UINT nFlags, CPoint point)
{
	CEdit::OnMButtonDown(nFlags, point);

	ClientToScreen(&point);
	if(CWnd::WindowFromPoint(point) != this)
	{
		ReleaseCapture();
		ShowWindow(SW_HIDE);
	}
}

void CEditPlace::OnKillFocus(CWnd* pNewWnd)
{
	CEdit::OnKillFocus(pNewWnd);

//	ReleaseCapture();
}
