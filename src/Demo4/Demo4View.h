// Demo4View.h : interface of the CDemo4View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DEMO4VIEW_H__AAC390DC_2074_43E7_8507_1BB9DE986069__INCLUDED_)
#define AFX_DEMO4VIEW_H__AAC390DC_2074_43E7_8507_1BB9DE986069__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CDemo4View : public CView
{
protected: // create from serialization only
	CDemo4View();
	DECLARE_DYNCREATE(CDemo4View)

// Attributes
public:
	CDemo4Doc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDemo4View)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDemo4View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDemo4View)
	afx_msg void OnColorToGray();
	afx_msg void OnPrewitt();
	afx_msg void OnFreeRotate();
	afx_msg void OnBinary();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Demo4View.cpp
inline CDemo4Doc* CDemo4View::GetDocument()
   { return (CDemo4Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEMO4VIEW_H__AAC390DC_2074_43E7_8507_1BB9DE986069__INCLUDED_)
