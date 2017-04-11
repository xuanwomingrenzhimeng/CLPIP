// Demo3Doc.h : interface of the CDemo3Doc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DEMO3DOC_H__E939EBD7_50E4_40E5_9F44_1544A625E9DF__INCLUDED_)
#define AFX_DEMO3DOC_H__E939EBD7_50E4_40E5_9F44_1544A625E9DF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ImageDib.h"

class CDemo3Doc : public CDocument
{
protected: // create from serialization only
	CDemo3Doc();
	DECLARE_DYNCREATE(CDemo3Doc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDemo3Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	ImageDib* m_dib;
	virtual ~CDemo3Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDemo3Doc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEMO3DOC_H__E939EBD7_50E4_40E5_9F44_1544A625E9DF__INCLUDED_)
