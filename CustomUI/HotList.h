#pragma once
#include "EditPlace.h"

/////////////////////////////////////////////////////////////////////////
#define HOTLIST_WINCLASSNAME			TEXT("CHSWIN_HOT_LIST")

/////////////////////////////////////////////////////////////////////////
#define EHOTLIST_BTN_Y					12						//스크롤 버튼의 Y크기
#define EHOTLIST_CHECKBOX_WIDTH			25						//체크 박스 표시를 위한 폭의 크기

#define COLOR_SCROLL_BTN_NORMAL			RGB(225, 225, 225)		//선택표시 배경색
#define COLOR_SCROLL_BTN_HOT			RGB(235, 235, 235)		//롤오버된 배경색

/////////////////////////////////////////////////////////////////////////
#define EHL_ITEM_SELCHANGED				0x00000001
#define EHL_ITEM_DBLCLICKED				0x00000010
#define EHL_ITEM_CHECK					0x00000020

/////////////////////////////////////////////////////////////////////////
// CHotList
class CHotList : public CWnd
{
	DECLARE_DYNAMIC(CHotList)

public:
	CHotList();
	virtual ~CHotList();

protected:
	CStringArray	m_arItemText;			//각 아이템의 텍스트가 저장될 CString 배열
	CUIntArray		m_arCheck;
	CUIntArray		m_arImageIndex;			//각 아이템의 이미지 인덱스.
	BOOL			m_bShowCheckBox;		//Check box를 표시할 것인지 나타내는 플래그.

	CImageList*		m_pImageList;
	BOOL			m_bShowIcon;

	int				m_nItemHeight;			//아이템의 높이
	int				m_nCurSelIndex;			//선택된 아이템 인덱스
	int				m_nCurOverItemIndex;	//마우스 포인터가 위치한 아이템 인덱스

	int				m_nStartIndex;			//표시될 첫 번째 인덱스
	int				m_nDisplayCount;		//화면에 표시될 수 있는 아이템 수(윈도우 크기에 따라 결정됨.)

	COLORREF		m_rgbBack;
	COLORREF		m_rgbSelBegin, m_rgbSelEnd;
	COLORREF		m_rgbOver;

	CEditPlace		m_wndEdit;
	BOOL			m_bMouseTrack;

protected:
	DECLARE_MESSAGE_MAP()


public:
	void RegisterWindowClass(void);
	BOOL Create(CWnd* pParentWnd, const RECT & rect, UINT nID, DWORD dwStyle);
	void CalcDisplaySize(void);
	void PageUp(int nLinePerPage);
	void PageDown(int nLinePerPage);
	void AddString(CString strItem, BOOL bRedraw, int nImgIndex = 0);
	int HitTest(CPoint point);
	void SelectAll(BOOL bCheck);
	BOOL GetItemPos(int nIndex, CPoint& point);
	BOOL SetItemText(int nIndex, CString strData);
	BOOL GetItemText(int nIndex, CString& strData);
	void SetItemHeight(int nHeight);
	int GetItemHeight(int nHeight);
	void SetSelectedItemColor(COLORREF rgbBegin, COLORREF rgbEnd);
	void SetItemBkColor(COLORREF rgbBack);
	void SetOverColor(COLORREF rgbOver);
	void SetCheck(int nIndex, BOOL bCheck);
	BOOL GetCheck(int nIndex);
	int DeleteSelectedAll(void);
	void ShowCheckBox(BOOL bCheck);
	void SetImageList(CImageList* pImageList, BOOL bShowIcon);
	void ShowIcon(BOOL bShow);
	void InsertString(int nIndex, CString strItem, BOOL bRedraw, int nImgIndex = 0);

	virtual BOOL DrawItem(int nIndex, CDC* pDC);
	virtual int DrawItemData(int nIndex, CDC* pDC, CRect rect);
	virtual void DrawItemBack(int nIndex, CDC* pDC, CRect rect);
	virtual void DrawItemOver(int nIndex, CDC* pDC, CRect rect);
	virtual BOOL DeleteItem(int nIndex, BOOL bRedraw);

	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);

protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
public:
	BOOL IsVisibleItem(int nIndex);
	BOOL GetItemRect(int nIndex, CRect& rect);
};

/////////////////////////////////////////////////////////////////////////
