#pragma once
#include "EditPlace.h"

/////////////////////////////////////////////////////////////////////////
#define HOTLIST_WINCLASSNAME			TEXT("CHSWIN_HOT_LIST")

/////////////////////////////////////////////////////////////////////////
#define EHOTLIST_BTN_Y					12						//��ũ�� ��ư�� Yũ��
#define EHOTLIST_CHECKBOX_WIDTH			25						//üũ �ڽ� ǥ�ø� ���� ���� ũ��

#define COLOR_SCROLL_BTN_NORMAL			RGB(225, 225, 225)		//����ǥ�� ����
#define COLOR_SCROLL_BTN_HOT			RGB(235, 235, 235)		//�ѿ����� ����

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
	CStringArray	m_arItemText;			//�� �������� �ؽ�Ʈ�� ����� CString �迭
	CUIntArray		m_arCheck;
	CUIntArray		m_arImageIndex;			//�� �������� �̹��� �ε���.
	BOOL			m_bShowCheckBox;		//Check box�� ǥ���� ������ ��Ÿ���� �÷���.

	CImageList*		m_pImageList;
	BOOL			m_bShowIcon;

	int				m_nItemHeight;			//�������� ����
	int				m_nCurSelIndex;			//���õ� ������ �ε���
	int				m_nCurOverItemIndex;	//���콺 �����Ͱ� ��ġ�� ������ �ε���

	int				m_nStartIndex;			//ǥ�õ� ù ��° �ε���
	int				m_nDisplayCount;		//ȭ�鿡 ǥ�õ� �� �ִ� ������ ��(������ ũ�⿡ ���� ������.)

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
