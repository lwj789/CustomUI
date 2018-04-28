// MyChart.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "CustomUI.h"
#include "MyChart.h"


// CMyChart

IMPLEMENT_DYNAMIC(CMyChart, CWnd)

CMyChart::CMyChart()
{
	RegisterWindowClass();
}

CMyChart::~CMyChart()
{
}


BEGIN_MESSAGE_MAP(CMyChart, CWnd)
	ON_WM_PAINT()     /// kkkkk
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()



// CMyChart 메시지 처리기입니다.




void CMyChart::RegisterWindowClass()
{
	WNDCLASS wndcls;
	HINSTANCE hInst = AfxGetInstanceHandle();

	wndcls.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
	wndcls.lpfnWndProc = ::DefWindowProc;
	wndcls.cbClsExtra = wndcls.cbWndExtra = 0;
	wndcls.hInstance = hInst;
	wndcls.hIcon = NULL;
	wndcls.hCursor = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
	wndcls.hbrBackground = (HBRUSH)(COLOR_3DFACE + 1);
	wndcls.lpszMenuName = NULL;
	wndcls.lpszClassName = TEXT("CHSWIN_CHART");

	AfxRegisterClass(&wndcls);
}


BOOL CMyChart::Create(CWnd* pParentWnd, const RECT & rect, UINT nID, DWORD dwStyle)
{
	return CWnd::Create(_T("CHSWIN_CHART"), _T(""), dwStyle, rect, pParentWnd, nID);
}


void CMyChart::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	Graphics g(dc);
	g.SetSmoothingMode(SmoothingModeHighQuality);
//	dc.SetViewportOrg(10, -10);
	Matrix transformMatrix;
	transformMatrix.Translate(10.0f, -10.0f);
	g.SetTransform(&transformMatrix);

	CRect rect;
	GetClientRect(&rect); // 윈도우의 크기 알아냄.

	Pen BluePen(Color(255, 92, 92, 130), 5.0f); // 선색과 선 굵기 설정. 
	BluePen.SetStartCap(LineCapRound);
	BluePen.SetEndCap(LineCapRound);


	//X
//	dc.MoveTo(0, rect.Height() - 1);
//	dc.LineTo(rect.Width(), rect.Height() - 1);
	g.DrawLine(&BluePen, Point(0, rect.Height() - 1), Point(rect.Width(), rect.Height() - 1));
	
	//Y
//	dc.MoveTo(0, rect.Height() - 1);
//	dc.LineTo(0, 0);
	g.DrawLine(&BluePen, Point(0, rect.Height() - 1), Point(0, 0));

	dc.TextOut(10, 10, _T("WJ Chart"));
}


BOOL CMyChart::OnEraseBkgnd(CDC* pDC)
{
	//return CWnd::OnEraseBkgnd(pDC);
	CRect rect;
	GetClientRect(&rect); // 윈도우의 크기 알아냄.
	//pDC->FillSolidRect(&rect, RGB(255, 255, 0));

	Graphics graphics(*pDC);
	graphics.SetSmoothingMode(SmoothingModeHighQuality);  // 안티엘러어싱 적용 (선이 좀더 부드럽게 표현됨)

	// 선형 그라데이션 효과 넣음.
	LinearGradientBrush lgBrush(
		Rect(0, 0, rect.Width(), rect.Height()),
			Color(128, 221, 236, 255),
			Color(255, 86, 125, 204),
			45.0f,
			FALSE);

	graphics.FillRectangle(&lgBrush, 0, 0, rect.Width(), rect.Height());
	return TRUE;
}
