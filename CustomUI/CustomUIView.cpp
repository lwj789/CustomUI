
// CustomUIView.cpp : CCustomUIView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
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
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CCustomUIView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CCustomUIView ����/�Ҹ�

CCustomUIView::CCustomUIView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CCustomUIView::~CCustomUIView()
{
}

BOOL CCustomUIView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CCustomUIView �׸���

void CCustomUIView::OnDraw(CDC* /*pDC*/)
{
	CCustomUIDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
}


// CCustomUIView �μ�


void CCustomUIView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CCustomUIView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CCustomUIView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CCustomUIView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
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


// CCustomUIView ����

#ifdef _DEBUG
void CCustomUIView::AssertValid() const
{
	CView::AssertValid();
}

void CCustomUIView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCustomUIDoc* CCustomUIView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCustomUIDoc)));
	return (CCustomUIDoc*)m_pDocument;
}
#endif //_DEBUG


// CCustomUIView �޽��� ó����


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
