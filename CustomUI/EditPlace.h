#if !defined(AFX_EDITPLACE_H__B5A96B97_18A2_47DE_A137_305AC2889D4E__INCLUDED_)
#define AFX_EDITPLACE_H__B5A96B97_18A2_47DE_A137_305AC2889D4E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditPlace.h : header file
//

/////////////////////////////////////////////////////////////////////////////
#define EHC_EDIT_CHANGED				0x00000001		//텍스트 변경
#define EHC_EDIT_CLOSE					0x00000002		//단순히 닫음
#define EHC_EDIT_TAB					0x00000010		//텝키를 누름

/////////////////////////////////////////////////////////////////////////////
// CEditPlace window

class CEditPlace : public CEdit
{
// Construction
public:
	CEditPlace();

// Attributes
public:
	CFont	m_Font;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditPlace)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEditPlace();

	// Generated message map functions
protected:
	//{{AFX_MSG(CEditPlace)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITPLACE_H__B5A96B97_18A2_47DE_A137_305AC2889D4E__INCLUDED_)
