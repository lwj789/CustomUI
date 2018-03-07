// HotList.cpp : implementation file
//

#include "stdafx.h"
#include "HotList.h"
#include "resource.h"

// CHotList

IMPLEMENT_DYNAMIC(CHotList, CWnd)

CHotList::CHotList()
{
	RegisterWindowClass();

	m_bShowCheckBox		= TRUE;

	m_pImageList		= NULL;
	m_bShowIcon			= FALSE;

//	m_nItemHeight		= 42;
	m_nItemHeight		= 25;
	m_nCurSelIndex		= -1;			//선택된 아이템 없음.
	m_nCurOverItemIndex = -1;

	m_nStartIndex		= 0;
	m_nDisplayCount		= 0;

	m_rgbBack			= RGB(232, 228, 219);
//	m_rgbSelBegin		= RGB(221, 236, 255);		//Office 2003 스타일
//	m_rgbSelEnd			= RGB(86, 125, 204);
	m_rgbSelBegin		= RGB(254, 254, 251);		//Visual Studio 2005 스타일
	m_rgbSelEnd			= RGB(193, 192, 168);
	m_rgbOver			= RGB(0, 92, 92);

	m_bMouseTrack		= FALSE;
}

CHotList::~CHotList()
{
}


BEGIN_MESSAGE_MAP(CHotList, CWnd)
	ON_WM_SIZE()
	ON_WM_VSCROLL()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSELEAVE()
	ON_WM_MOUSEWHEEL()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_CREATE()
//	ON_WM_SHOWWINDOW()
ON_WM_CHAR()
ON_WM_KEYDOWN()
END_MESSAGE_MAP()



// CHotList message handlers


/////////////////////////////////////////////////////////////////////////
void CHotList::RegisterWindowClass(void)
{
	WNDCLASS wndcls;
	HINSTANCE hInst = AfxGetInstanceHandle();

	wndcls.style            = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
	wndcls.lpfnWndProc      = ::DefWindowProc;
	wndcls.cbClsExtra       = wndcls.cbWndExtra = 0;
	wndcls.hInstance        = hInst;
	wndcls.hIcon            = NULL;
	wndcls.hCursor          = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
	wndcls.hbrBackground    = (HBRUSH) (COLOR_3DFACE + 1);
	wndcls.lpszMenuName     = NULL;
	wndcls.lpszClassName    = HOTLIST_WINCLASSNAME;

	AfxRegisterClass(&wndcls);
}

/////////////////////////////////////////////////////////////////////////
BOOL CHotList::Create(CWnd* pParentWnd, const RECT & rect, UINT nID, DWORD dwStyle)
{
	BOOL bResult = CWnd::Create(HOTLIST_WINCLASSNAME, _T(""), dwStyle | WS_VSCROLL, rect, pParentWnd, nID);

	SCROLLINFO si; 
	si.cbSize = sizeof(si); 
	si.fMask  = SIF_ALL; 
	si.nMin   = 0; 
	si.nMax   = 110; 
	si.nPage  = 36; 
	si.nPos   = 0; 
	SetScrollInfo(SB_VERT, &si, TRUE); 

	return bResult;
}

/////////////////////////////////////////////////////////////////////////
void CHotList::CalcDisplaySize(void)
{
	CRect Rect;
	GetClientRect(&Rect);
	int nY = Rect.Height();
	m_nDisplayCount = nY / m_nItemHeight;


	if(nY < m_nItemHeight)		m_nDisplayCount = 0;
	else						m_nDisplayCount = nY / m_nItemHeight;

	/////////////////////////////////////////////////////////////////////
	//스크롤바 계산
	int nTotalLine = m_arItemText.GetCount();

	SCROLLINFO si;
	::ZeroMemory(&si, sizeof(SCROLLINFO));
	si.cbSize = sizeof(si);
	GetScrollInfo(SB_VERT, &si);

	si.cbSize = sizeof(si); 
	si.fMask  = SIF_ALL; 
	si.nMin   = 0; 
	si.nMax   = nTotalLine; 
	si.nPage  = m_nDisplayCount; 

	SetScrollInfo(SB_VERT, &si, TRUE);
}

/////////////////////////////////////////////////////////////////////////
void CHotList::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);
	CalcDisplaySize();
	RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
}

/////////////////////////////////////////////////////////////////////////
void CHotList::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	CString tmp = _T("");
	int nCurrentPos = GetScrollPos(SB_VERT);
	CalcDisplaySize();

	switch(nSBCode)
	{
	case SB_LINEUP:
		PageUp(1);
		break;

	case SB_LINEDOWN:
		PageDown(1);
		break;

	case SB_PAGEUP:
		PageUp(m_nDisplayCount * 2 / 3);
		break;

	case SB_PAGEDOWN:
		PageDown(m_nDisplayCount * 2 / 3);
		break;

	case SB_THUMBTRACK:
	case SB_THUMBPOSITION:
		SetScrollPos(SB_VERT, nPos);
		m_nStartIndex = nPos;
		if(m_nStartIndex < 0)		m_nStartIndex = 0;

		if(m_nStartIndex + m_nDisplayCount > m_arItemText.GetCount())
		{
			m_nStartIndex = m_arItemText.GetCount() - m_nDisplayCount;
			if(m_nStartIndex < 0)		m_nStartIndex = 0;
		}

		CalcDisplaySize();
		break;
	}

	RedrawWindow();

	CWnd::OnVScroll(nSBCode, nPos, pScrollBar);
}

/////////////////////////////////////////////////////////////////////////
void CHotList::PageUp(int nLinePerPage)
{
	m_nStartIndex -= nLinePerPage;
	if(m_nStartIndex < 0)		m_nStartIndex = 0;

	CalcDisplaySize();
	SetScrollPos(SB_VERT, m_nStartIndex);
	RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
}

/////////////////////////////////////////////////////////////////////////
void CHotList::PageDown(int nLinePerPage)
{
	m_nStartIndex += nLinePerPage;
	if(m_nStartIndex + m_nDisplayCount > m_arItemText.GetCount())
	{
		m_nStartIndex = m_arItemText.GetCount() - m_nDisplayCount;
		if(m_nStartIndex < 0)		m_nStartIndex = 0;
	}

	CalcDisplaySize();
	SetScrollPos(SB_VERT, m_nStartIndex);
	RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
}

/////////////////////////////////////////////////////////////////////////
void CHotList::OnLButtonDown(UINT nFlags, CPoint point)
{
//	SetFocus();
	int nIndex = HitTest(point);
	if(nIndex != -1)
	{
		if(m_nCurSelIndex != nIndex)
		{
			m_wndEdit.ShowWindow(SW_HIDE);
			SetFocus();
		}
	}

	CWnd::OnLButtonDown(nFlags, point);
}

/////////////////////////////////////////////////////////////////////////
void CHotList::OnLButtonUp(UINT nFlags, CPoint point)
{
	if(m_wndEdit.IsWindowVisible())		return;

	int nIndex = HitTest(point);
	if(nIndex != -1 && m_bShowCheckBox)
	{
		CRect rect;
		GetClientRect(&rect);
		CPoint ptItem;
		GetItemPos(nIndex, ptItem);

		rect.top	= ptItem.y;
		rect.bottom	= ptItem.y + m_nItemHeight;

		int nCheckBoxSize = 16;
		CRect rectCheckBox(	rect.left + 5, rect.top + 5,
						rect.left + 5 + nCheckBoxSize, rect.top + 5 + nCheckBoxSize);
		if(rectCheckBox.PtInRect(point))	SetCheck(nIndex, !GetCheck(nIndex));
	}

	CClientDC dc(this);
	if(m_nCurSelIndex != nIndex)
	{
		int nPrevIndex = m_nCurSelIndex;
		m_nCurSelIndex = -1;
		DrawItem(nPrevIndex, &dc);
	}

	m_nCurSelIndex = nIndex;
	DrawItem(m_nCurSelIndex, &dc);

	CWnd::OnLButtonUp(nFlags, point);
}

/////////////////////////////////////////////////////////////////////////
void CHotList::OnMouseMove(UINT nFlags, CPoint point)
{
	if(m_wndEdit.IsWindowVisible())
	{
		CWnd::OnMouseMove(nFlags, point);
		return;
	}

	if(!m_bMouseTrack)
	{
		TRACKMOUSEEVENT tme = {0};
		tme.cbSize		= sizeof(tme);
		tme.hwndTrack	= m_hWnd;
		tme.dwFlags		= TME_LEAVE;
		m_bMouseTrack = ::_TrackMouseEvent(&tme);
	}

	int nIndex = HitTest(point);
	if(nIndex != -1)
	{
		if(m_nCurOverItemIndex == nIndex)		return;

		CClientDC dc(this);
		int nPrevIndex = m_nCurOverItemIndex;
		m_nCurOverItemIndex = -1;
		DrawItem(nPrevIndex, &dc);

		m_nCurOverItemIndex = nIndex;
		DrawItem(m_nCurOverItemIndex, &dc);
	}

//	SetFocus();
	CWnd::OnMouseMove(nFlags, point);
}

/////////////////////////////////////////////////////////////////////////
void CHotList::OnMouseLeave()
{
	m_bMouseTrack = FALSE;
	if(m_wndEdit.IsWindowVisible())		return;

	CClientDC dc(this);
	int nPrevIndex = m_nCurOverItemIndex;
	m_nCurOverItemIndex = -1;
	DrawItem(nPrevIndex, &dc);

	CWnd::OnMouseLeave();
}

/////////////////////////////////////////////////////////////////////////
BOOL CHotList::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	if(m_wndEdit.IsWindowVisible())			m_wndEdit.ShowWindow(SW_HIDE);

	if(zDelta > 0)		PageUp(m_nDisplayCount * 2 / 3);
	else				PageDown(m_nDisplayCount * 2 / 3);

	return CWnd::OnMouseWheel(nFlags, zDelta, pt);
}

/////////////////////////////////////////////////////////////////////////
void CHotList::AddString(CString strItem, BOOL bRedraw, int nImgIndex)
{
	m_arItemText.Add(strItem);
	m_arCheck.Add(FALSE);
	m_arImageIndex.Add(nImgIndex);

	if(GetSafeHwnd() && bRedraw)
		RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
}

/////////////////////////////////////////////////////////////////////////
void CHotList::InsertString(int nIndex, CString strItem, BOOL bRedraw, int nImgIndex)
{
	m_arItemText.InsertAt(nIndex, strItem);
	m_arCheck.InsertAt(nIndex, (UINT)FALSE);
	m_arImageIndex.InsertAt(nIndex, (UINT)nImgIndex);

	if(GetSafeHwnd() && bRedraw)
		RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
}

/////////////////////////////////////////////////////////////////////////
void CHotList::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CRect Rect;
	GetClientRect(&Rect);
	dc.FillSolidRect(&Rect, m_rgbBack);

	for(int i = 0; i < m_nDisplayCount; ++i)
	{
		if(!DrawItem(i + m_nStartIndex, &dc))		break;
	}
}

/////////////////////////////////////////////////////////////////////////
BOOL CHotList::DrawItem(int nIndex, CDC* pDC)
{
	CRect Rect;
	if(!GetItemRect(nIndex, Rect))		return FALSE;

	//1. 배경 출력
	DrawItemBack(nIndex, pDC, Rect);

	//1.1 체크박스를 그려야 한다면 아이템의 크기를 체크박스를 제외한 크기로 조정한다.
	if(m_bShowCheckBox)			Rect.left	+= EHOTLIST_CHECKBOX_WIDTH;
	else						Rect.left	+= 1;

	//2. 아이템 정보 출력.
	DrawItemData(nIndex, pDC, Rect);

	//3. 롤오버 이미지 출력
	DrawItemOver(nIndex, pDC, Rect);

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////
int CHotList::HitTest(CPoint point)
{
	//화면에 출력된 내용을 기준으로 아이템 인덱스를 다시 계산함.
	int nIndex = point.y / m_nItemHeight;
	nIndex += m_nStartIndex;

	//계산 결과가 올바르고 전체 인덱스 내의 값이라면 이를 리턴함.
	if(nIndex < m_nStartIndex + m_nDisplayCount)
	{
		if(nIndex >= 0 && nIndex < m_arItemText.GetCount())		return nIndex;
	}

	return -1;
}

/////////////////////////////////////////////////////////////////////////
int CHotList::DrawItemData(int nIndex, CDC* pDC, CRect rect)
{
	CString strTmp = _T("");
	LOGFONT lf = {0};
	lf.lfHeight = 15;
	if(m_nCurSelIndex == nIndex)		lf.lfWeight = FW_BOLD;
	wsprintf(lf.lfFaceName, _T("%s"), _T("Arial"));
	CFont NewFont;
	NewFont.CreateFontIndirect(&lf);
	CFont* pOldFont = pDC->SelectObject(&NewFont);

	CRect rtText(rect);
	rtText.left += 5;
	if(m_bShowIcon && m_pImageList != NULL)
	{
		IMAGEINFO ImageInfo = {0};
		m_pImageList->GetImageInfo(0, &ImageInfo);

		CPoint ptIcon = rtText.TopLeft();
		ptIcon.y += 4;
		m_pImageList->Draw(pDC, m_arImageIndex[nIndex], ptIcon, ILD_NORMAL | ILD_TRANSPARENT);

		rtText.left += ImageInfo.rcImage.right;
	}

	pDC->SetBkMode(TRANSPARENT);

	rtText.left	+= 5;
	rtText.top	+= 5;
//	strTmp.Format(_T("%04d  %s"), nIndex, m_arItemText[nIndex]);
//	pDC->DrawText(strTmp, -1, &rtText, DT_LEFT);
	pDC->DrawText(m_arItemText[nIndex], -1, &rtText, DT_LEFT);

	pDC->SelectObject(pOldFont);
	return 0;
}

/////////////////////////////////////////////////////////////////////////
BOOL CHotList::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
//	return CWnd::OnEraseBkgnd(pDC);
}

/////////////////////////////////////////////////////////////////////////
void CHotList::DrawItemBack(int nIndex, CDC* pDC, CRect rect)
{
	if(nIndex == m_nCurSelIndex)
	{
		if(m_rgbSelBegin == m_rgbSelEnd)
		{
			pDC->FillSolidRect(&rect, m_rgbSelBegin);
		}
		else
		{
			TRIVERTEX triVertex[2] = {0};
			GRADIENT_RECT    gRect = {0};

			triVertex[0].x			= rect.left;
			triVertex[0].y			= rect.top;
			triVertex[0].Red		= GetRValue(m_rgbSelBegin) << 8;
			triVertex[0].Green		= GetGValue(m_rgbSelBegin) << 8;
			triVertex[0].Blue		= GetBValue(m_rgbSelBegin) << 8;

			triVertex[1].x			= rect.right;
			triVertex[1].y			= rect.bottom;
			triVertex[1].Red		= GetRValue(m_rgbSelEnd) << 8;
			triVertex[1].Green		= GetGValue(m_rgbSelEnd) << 8;
			triVertex[1].Blue		= GetBValue(m_rgbSelEnd) << 8;

			gRect.UpperLeft = 0;
			gRect.LowerRight = 1;
			pDC->GradientFill(triVertex, 2, &gRect, 1, GRADIENT_FILL_RECT_V);
		}
	}
	else
	{
		pDC->FillSolidRect(&rect, m_rgbBack);
	}

	if(m_bShowCheckBox)
	{
		int nCheckBoxSize = 16;
		CRect rectCheckBox(	rect.left + 5, rect.top + 5,
							rect.left + 5 + nCheckBoxSize, rect.top + 5 + nCheckBoxSize);
		pDC->Draw3dRect(&rectCheckBox, RGB(92, 92, 92), RGB(210, 210, 210));

		if(GetCheck(nIndex))
		{
//			CImage image;
//			image.LoadFromResource(AfxGetInstanceHandle(), IDB_Check);
//			image.TransparentBlt(pDC->m_hDC, rectCheckBox.left + 1, rectCheckBox.top + 1, 16, 16, RGB(255, 255, 255));
			rectCheckBox -= CRect(4, 4, 4, 4);
			CPen NewPen(PS_SOLID, 2, RGB(200, 82, 62));
			CPen* pOldPen = pDC->SelectObject(&NewPen);

			pDC->MoveTo(rectCheckBox.left, rectCheckBox.top);
			pDC->LineTo(rectCheckBox.left, rectCheckBox.bottom);
			pDC->LineTo(rectCheckBox.right, rectCheckBox.top);

			pDC->SelectObject(pOldPen);

		}
	}
}

/////////////////////////////////////////////////////////////////////////
void CHotList::DrawItemOver(int nIndex, CDC* pDC, CRect rect)
{
	//롤오버 출력
	if(nIndex == m_nCurOverItemIndex)//&& nIndex != m_nCurSelIndex)
	{
		CDC MemDC;
		MemDC.CreateCompatibleDC(pDC);
		CBitmap Bmp;
		Bmp.CreateBitmap(rect.Width(), rect.Height(), pDC->GetDeviceCaps(PLANES), pDC->GetDeviceCaps(BITSPIXEL), NULL);
		CBitmap* pOldBmp = MemDC.SelectObject(&Bmp);

		MemDC.FillSolidRect(0, 0, rect.Width(), rect.Height(), m_rgbOver);

		BLENDFUNCTION bf = {0};
		bf.BlendOp				= AC_SRC_OVER;
		bf.SourceConstantAlpha	= 50;
		pDC->AlphaBlend(rect.left, rect.top, rect.Width(), rect.Height(),
						&MemDC,
						0, 0, rect.Width(), rect.Height(), bf);

		MemDC.SelectObject(pOldBmp);
	}
}

/////////////////////////////////////////////////////////////////////////
void CHotList::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	int nIndex = HitTest(point);
	CPoint ptItem;
	if(nIndex != -1 && GetItemPos(nIndex, ptItem))
	{
		CRect Rect;
		GetClientRect(&Rect);

		if(m_bShowCheckBox)			Rect.left	+= EHOTLIST_CHECKBOX_WIDTH;
		else						Rect.left	+= 1;

		if(m_bShowIcon && m_pImageList != NULL)
		{
			IMAGEINFO ImageInfo = {0};
			m_pImageList->GetImageInfo(0, &ImageInfo);
			Rect.left += ImageInfo.rcImage.right;
		}

		Rect.left += 9;

		CString strTmp = _T("");
		GetItemText(nIndex, strTmp);
		m_wndEdit.SetWindowPos(NULL, Rect.left, ptItem.y + (m_nItemHeight - 20) / 2 + 1, Rect.Width(), 20, SWP_SHOWWINDOW | SWP_NOZORDER);
		m_wndEdit.SetWindowText(strTmp);
		m_wndEdit.SetFocus();

		DWORD dwSel = 0;
		dwSel = HIWORD(-1);
		m_wndEdit.SetSel(dwSel);
	}

	CWnd::OnLButtonDblClk(nFlags, point);
}

/////////////////////////////////////////////////////////////////////////
int CHotList::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_wndEdit.Create( WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, CRect(0, 0, 0, 0), this, 1234);

	return 0;
}

/////////////////////////////////////////////////////////////////////////
BOOL CHotList::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	CString strTmp = _T("");
	NMHDR* pNmHdr = (NMHDR*)lParam;

	if(pNmHdr->idFrom == 1234)
	{
		switch(pNmHdr->code)
		{
		/////////////////////////////////////////////////////////////////
		case EHC_EDIT_CHANGED:
			{
				if(m_wndEdit.IsWindowVisible())
				{
					m_wndEdit.ShowWindow(SW_HIDE);
					m_wndEdit.GetWindowText(strTmp);
				}

				SetItemText(m_nCurSelIndex, strTmp);
				break;
			}

		/////////////////////////////////////////////////////////////////
		case EHC_EDIT_CLOSE:
			{
//				RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
				CClientDC dc(this);
				DrawItem(m_nCurSelIndex, &dc);
				break;
			}
		}
	}

	return CWnd::OnNotify(wParam, lParam, pResult);
}

/////////////////////////////////////////////////////////////////////////
BOOL CHotList::GetItemPos(int nIndex, CPoint& point)
{
//	CalcDisplaySize();
	if(nIndex < 0 || nIndex >= m_arItemText.GetSize())							return FALSE;
	if(nIndex < m_nStartIndex || nIndex > m_nStartIndex + m_nDisplayCount)		return FALSE;

	point.x = 0;
	point.y = (nIndex - m_nStartIndex) * m_nItemHeight;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////
BOOL CHotList::SetItemText(int nIndex, CString strData)
{
	if(nIndex < 0 || nIndex >= m_arItemText.GetSize())							return FALSE;

	m_arItemText[nIndex] = strData;

	CClientDC dc(this);
	return DrawItem(nIndex, &dc);
}

/////////////////////////////////////////////////////////////////////////
BOOL CHotList::GetItemText(int nIndex, CString& strData)
{
	if(nIndex < 0 || nIndex >= m_arItemText.GetSize())							return FALSE;

	strData = m_arItemText[nIndex];
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////
void CHotList::SetItemHeight(int nHeight)
{
	m_nItemHeight = nHeight;
}

/////////////////////////////////////////////////////////////////////////
int CHotList::GetItemHeight(int nHeight)
{
	return m_nItemHeight;
}

/////////////////////////////////////////////////////////////////////////
void CHotList::SetSelectedItemColor(COLORREF rgbBegin, COLORREF rgbEnd)
{
	m_rgbSelBegin	= rgbBegin;
	m_rgbSelEnd		= rgbEnd;

	if(GetSafeHwnd())	RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
}

/////////////////////////////////////////////////////////////////////////
void CHotList::SetItemBkColor(COLORREF rgbBack)
{
	m_rgbBack = rgbBack;
	if(GetSafeHwnd())	RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
}

/////////////////////////////////////////////////////////////////////////
void CHotList::SetOverColor(COLORREF rgbOver)
{
	m_rgbOver = rgbOver;
	if(GetSafeHwnd())	RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
}

/////////////////////////////////////////////////////////////////////////
void CHotList::SetCheck(int nIndex, BOOL bCheck)
{
	if(nIndex < 0 || nIndex >= m_arItemText.GetSize())							return;
//	if(nIndex < m_nStartIndex || nIndex > m_nStartIndex + m_nDisplayCount)		return;

	m_arCheck.SetAt(nIndex, bCheck);
	CClientDC dc(this);
	DrawItem(nIndex, &dc);
}

/////////////////////////////////////////////////////////////////////////
BOOL CHotList::GetCheck(int nIndex)
{
	if(nIndex < 0 || nIndex >= m_arItemText.GetSize())							return FALSE;
//	if(nIndex < m_nStartIndex || nIndex > m_nStartIndex + m_nDisplayCount)		return FALSE;

	return (BOOL)m_arCheck.GetAt(nIndex);
}

/////////////////////////////////////////////////////////////////////////
void CHotList::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CWnd::OnChar(nChar, nRepCnt, nFlags);
}

/////////////////////////////////////////////////////////////////////////
void CHotList::SelectAll(BOOL bCheck)
{
	int nCount = m_arItemText.GetCount();
	for(int i = 0; i < nCount; ++i)
	{
		m_arCheck.SetAt(i, bCheck);
	}

	RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
}

/////////////////////////////////////////////////////////////////////////
void CHotList::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	static BOOL bSelectAll = TRUE;
	CString strTmp = _T("");
	if(nChar == _T('A') || nChar == _T('a'))
	{
		if( HIBYTE(::GetKeyState(VK_CONTROL)) )
		{
			SelectAll(bSelectAll);
			bSelectAll = !bSelectAll;
		}
	}
	else if(nChar == VK_DELETE)
	{
		if(AfxMessageBox(_T("선택한 항목을 삭제하시겠습니까?"), MB_YESNO) == IDYES)
		{
			int nDeleted = DeleteSelectedAll();
			if(nDeleted > 0)
			{
				strTmp.Format(_T("%d개 항목을 삭제하였습니다."), nDeleted);
				AfxMessageBox(strTmp);
			}
		}
	}

	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}

/////////////////////////////////////////////////////////////////////////
int CHotList::DeleteSelectedAll(void)
{
	int nCount = m_arItemText.GetCount();
	int nDeleteCount = 0;
	for(int i = nCount - 1; i >= 0; --i)
	{
		if(GetCheck(i))
		{
			DeleteItem(i, FALSE);
			nDeleteCount++;
		}
	}

	if(nDeleteCount > 0)
		RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
	return nDeleteCount;
}

/////////////////////////////////////////////////////////////////////////
BOOL CHotList::DeleteItem(int nIndex, BOOL bRedraw)
{
	if(nIndex < 0 || nIndex >= m_arItemText.GetSize())			return FALSE;

	m_arItemText.RemoveAt(nIndex);
	m_arCheck.RemoveAt(nIndex);
	m_arImageIndex.RemoveAt(nIndex);

	if(GetSafeHwnd() && bRedraw)
		RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////
void CHotList::ShowCheckBox(BOOL bCheck)
{
	m_bShowCheckBox = bCheck;
	if(GetSafeHwnd())		RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
}

/////////////////////////////////////////////////////////////////////////
void CHotList::SetImageList(CImageList* pImageList, BOOL bShowIcon)
{
	m_pImageList = pImageList;
	m_bShowIcon = bShowIcon;
}

/////////////////////////////////////////////////////////////////////////
void CHotList::ShowIcon(BOOL bShow)
{
	m_bShowIcon = bShow;
	if(GetSafeHwnd())		RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
}

/////////////////////////////////////////////////////////////////////////
BOOL CHotList::IsVisibleItem(int nIndex)
{
	if(nIndex < 0 || nIndex >= m_arItemText.GetSize())							return FALSE;
	if(nIndex < m_nStartIndex || nIndex > m_nStartIndex + m_nDisplayCount)		return FALSE;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////
BOOL CHotList::GetItemRect(int nIndex, CRect& rect)
{
	if(!IsVisibleItem(nIndex))	return FALSE;

	int nY = (nIndex - m_nStartIndex) * m_nItemHeight;
	GetClientRect(&rect);

	rect.top	= nY;
	rect.bottom	= nY + m_nItemHeight;

	return TRUE;
}
