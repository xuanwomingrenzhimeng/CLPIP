// Demo4Doc.cpp : implementation of the CDemo4Doc class
//

#include "stdafx.h"
#include "Demo4.h"

#include "Demo4Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDemo4Doc

IMPLEMENT_DYNCREATE(CDemo4Doc, CDocument)

BEGIN_MESSAGE_MAP(CDemo4Doc, CDocument)
	//{{AFX_MSG_MAP(CDemo4Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDemo4Doc construction/destruction

CDemo4Doc::CDemo4Doc()
{
	// TODO: add one-time construction code here
	m_dib = new ImageDib;
}

CDemo4Doc::~CDemo4Doc()
{
	if (m_dib != NULL)
	{
		delete m_dib;
		m_dib = 0;
	}
}

BOOL CDemo4Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CDemo4Doc serialization

void CDemo4Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CDemo4Doc diagnostics

#ifdef _DEBUG
void CDemo4Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDemo4Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDemo4Doc commands

BOOL CDemo4Doc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (m_dib->Read(lpszPathName) == TRUE)
	{	
		SetModifiedFlag(FALSE);     // start off with unmodified
		return TRUE;
	}
	else 
		return 0;
}

BOOL CDemo4Doc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(m_dib->Write(lpszPathName) == TRUE)	{
		SetModifiedFlag(FALSE);     // have saved
		return TRUE;
	}
	else 
		return 0;	
//	return CDocument::OnSaveDocument(lpszPathName);
}
