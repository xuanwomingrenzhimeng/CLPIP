// Demo3View.h : interface of the CDemo3View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DEMO3VIEW_H__9DD0C416_D150_44F4_8BEE_8BFDE9F8244F__INCLUDED_)
#define AFX_DEMO3VIEW_H__9DD0C416_D150_44F4_8BEE_8BFDE9F8244F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ImageDib.h"

class CDemo3View : public CView
{
protected: // create from serialization only
	CDemo3View();
	DECLARE_DYNCREATE(CDemo3View)

// Attributes
public:
	CDemo3Doc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDemo3View)
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
	virtual ~CDemo3View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDemo3View)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Demo3View.cpp
inline CDemo3Doc* CDemo3View::GetDocument()
   { return (CDemo3Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEMO3VIEW_H__9DD0C416_D150_44F4_8BEE_8BFDE9F8244F__INCLUDED_)
