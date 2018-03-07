// PaneLeft.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "CustomUI.h"
#include "PaneLeft.h"


// CPaneLeft

IMPLEMENT_DYNAMIC(CPaneLeft, CDockablePane)

CPaneLeft::CPaneLeft()
{

}

CPaneLeft::~CPaneLeft()
{
}


BEGIN_MESSAGE_MAP(CPaneLeft, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()



// CPaneLeft 메시지 처리기입니다.




int CPaneLeft::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_wndForm.Create(IDD_FORM_LEFT, this);
	m_wndForm.ShowWindow(SW_SHOW);

	return 0;
}


void CPaneLeft::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	m_wndForm.MoveWindow(0, 0, cx, cy);
}
