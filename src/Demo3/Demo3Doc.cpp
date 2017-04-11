// Demo3Doc.cpp : implementation of the CDemo3Doc class
//

#include "stdafx.h"
#include "Demo3.h"

#include "Demo3Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDemo3Doc

IMPLEMENT_DYNCREATE(CDemo3Doc, CDocument)

BEGIN_MESSAGE_MAP(CDemo3Doc, CDocument)
	//{{AFX_MSG_MAP(CDemo3Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDemo3Doc construction/destruction

CDemo3Doc::CDemo3Doc()
{
	// TODO: add one-time construction code here
	m_dib = new ImageDib;

}

CDemo3Doc::~CDemo3Doc()
{
	if (m_dib != NULL)
	{
		delete m_dib;
		m_dib = 0;
	}
}

BOOL CDemo3Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CDemo3Doc serialization

void CDemo3Doc::Serialize(CArchive& ar)
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
// CDemo3Doc diagnostics

#ifdef _DEBUG
void CDemo3Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDemo3Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDemo3Doc commands

BOOL CDemo3Doc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	
	// TODO: Add your specialized creation code here
	

	if (m_dib->Read(lpszPathName) == TRUE)
	{	
		SetModifiedFlag(FALSE);     // start off with unmodified
		return TRUE;
	}
	else 
		return 0;
}

BOOL CDemo3Doc::OnSaveDocument(LPCTSTR lpszPathName) 
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
