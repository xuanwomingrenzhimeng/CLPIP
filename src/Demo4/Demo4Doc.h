// Demo4Doc.h : interface of the CDemo4Doc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DEMO4DOC_H__A98EFF1B_B7AE_4972_BEBC_9E065814F51D__INCLUDED_)
#define AFX_DEMO4DOC_H__A98EFF1B_B7AE_4972_BEBC_9E065814F51D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ImageDib.h"

class CDemo4Doc : public CDocument
{
protected: // create from serialization only
	CDemo4Doc();
	DECLARE_DYNCREATE(CDemo4Doc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDemo4Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	
	virtual ~CDemo4Doc();
	//获取m_dib的指针
	ImageDib *GetPDib()
	{
		return m_dib;
	}
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
public: 
	//ImgDib类的对象，从打开文件中读入的数据放在该对象中
	ImageDib* m_dib;
protected:
	//{{AFX_MSG(CDemo4Doc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEMO4DOC_H__A98EFF1B_B7AE_4972_BEBC_9E065814F51D__INCLUDED_)
