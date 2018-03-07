#pragma once
#include "FormLeft.h"


// CPaneLeft

class CPaneLeft : public CDockablePane
{
	DECLARE_DYNAMIC(CPaneLeft)

public:
	CPaneLeft();
	virtual ~CPaneLeft();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	CFormLeft m_wndForm;
	afx_msg void OnSize(UINT nType, int cx, int cy);
};


