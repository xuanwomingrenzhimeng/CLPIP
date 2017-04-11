// Demo3View.cpp : implementation of the CDemo3View class
//

#include "stdafx.h"
#include "Demo3.h"

#include "Demo3Doc.h"
#include "Demo3View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDemo3View

IMPLEMENT_DYNCREATE(CDemo3View, CView)

BEGIN_MESSAGE_MAP(CDemo3View, CView)
	//{{AFX_MSG_MAP(CDemo3View)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDemo3View construction/destruction

CDemo3View::CDemo3View()
{
	// TODO: add construction code here

}

CDemo3View::~CDemo3View()
{
}

BOOL CDemo3View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDemo3View drawing

void CDemo3View::OnDraw(CDC* pDC)
{
	CDemo3Doc* pDoc = GetDocument();			//获取文档类指针
	ASSERT(pDoc != NULL);
	ImageDib* pDib = pDoc->m_dib;					//返回m_dib的指针
	
	pDib->Draw(pDC, CPoint(0, 0), pDib->GetDimensions()); 	//显示DIB

}

/////////////////////////////////////////////////////////////////////////////
// CDemo3View printing

BOOL CDemo3View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDemo3View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CDemo3View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CDemo3View diagnostics

#ifdef _DEBUG
void CDemo3View::AssertValid() const
{
	CView::AssertValid();
}

void CDemo3View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDemo3Doc* CDemo3View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDemo3Doc)));
	return (CDemo3Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDemo3View message handlers
