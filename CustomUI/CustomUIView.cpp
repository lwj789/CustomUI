
// CustomUIView.cpp : CCustomUIView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "CustomUI.h"
#endif

#include "CustomUIDoc.h"
#include "CustomUIView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCustomUIView

IMPLEMENT_DYNCREATE(CCustomUIView, CView)

BEGIN_MESSAGE_MAP(CCustomUIView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CCustomUIView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CCustomUIView 생성/소멸

CCustomUIView::CCustomUIView()
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CCustomUIView::~CCustomUIView()
{
}

BOOL CCustomUIView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CCustomUIView 그리기

void CCustomUIView::OnDraw(CDC* /*pDC*/)
{
	CCustomUIDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CCustomUIView 인쇄


void CCustomUIView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CCustomUIView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CCustomUIView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CCustomUIView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CCustomUIView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CCustomUIView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CCustomUIView 진단

#ifdef _DEBUG
void CCustomUIView::AssertValid() const
{
	CView::AssertValid();
}

void CCustomUIView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCustomUIDoc* CCustomUIView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCustomUIDoc)));
	return (CCustomUIDoc*)m_pDocument;
}
#endif //_DEBUG


// CCustomUIView 메시지 처리기


int CCustomUIView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_wndChart.Create(this, CRect(110, 0, 10, 200), 1234, WS_CHILD | WS_VISIBLE);

	return 0;
}


void CCustomUIView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	m_wndChart.MoveWindow(0, 10, cx, cy - 150);
}
