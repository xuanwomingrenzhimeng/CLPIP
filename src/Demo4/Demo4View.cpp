// Demo4View.cpp : implementation of the CDemo4View class
//

#include "stdafx.h"
#include "Demo4.h"
#include "math.h"

#include "Demo4Doc.h"
#include "Demo4View.h"
#include "MainFrm.h"

#include "GrayTrans.h"
#include "ImgSegment.h"
#include "RotateDlg.h"
#include "GeometryTrans.h"
#include "GrayTrans.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDemo4View

IMPLEMENT_DYNCREATE(CDemo4View, CView)

BEGIN_MESSAGE_MAP(CDemo4View, CView)
	//{{AFX_MSG_MAP(CDemo4View)
	ON_COMMAND(id_ColorToGray, OnColorToGray)
	ON_COMMAND(id_Prewitt, OnPrewitt)
	ON_COMMAND(id_FreeRotate, OnFreeRotate)
	ON_COMMAND(id_Binary, OnBinary)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDemo4View construction/destruction

CDemo4View::CDemo4View()
{
	// TODO: add construction code here

}

CDemo4View::~CDemo4View()
{
}

BOOL CDemo4View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDemo4View drawing

void CDemo4View::OnDraw(CDC* pDC)
{
	CDemo4Doc* pDoc = GetDocument();
	ASSERT(pDoc != NULL);
	ImageDib* pDib = pDoc->m_dib;					//����m_dib��ָ��
	
	pDib->Draw(pDC, CPoint(0, 0), pDib->GetDimensions()); 	//��ʾDIB
}


/////////////////////////////////////////////////////////////////////////////
// CDemo4View printing

BOOL CDemo4View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDemo4View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CDemo4View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CDemo4View diagnostics

#ifdef _DEBUG
void CDemo4View::AssertValid() const
{
	CView::AssertValid();
}

void CDemo4View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDemo4Doc* CDemo4View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDemo4Doc)));
	return (CDemo4Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDemo4View message handlers

//DEL void CDemo4View::OnMove() 
//DEL {
//DEL 	// TODO: Add your command handler code here
//DEL 	
//DEL }

void CDemo4View::OnColorToGray() 
{
	// TODO: Add your command handler code here
	//��ȡ�ĵ���ָ��
	CDemo4Doc *pDoc=GetDocument();
	//��ȡImgCenterDib�����m_dib��ָ�룬���ʵ�ǰDIB����
	ImageDib *pDib=pDoc->GetPDib();
	
	//ֻ�����ɫͼ��

	//��pDib�е�ͼ��������Ϊ�������ݣ����ô������Ĺ��캯����
	//����GrayTrans��Ķ���graytrans
	GrayTrans graytrans(pDib->GetDimensions(),pDib->m_nBitCount,
		pDib->m_lpColorTable, pDib->m_pImgData);
	
	//��ɫ��Ҷȸ�ʽ
	graytrans.ColorToGray();
	
	//����һ������ͼ����ʾ�ָ���
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	
	//�����½��ļ�����Ϣ������һ���µ��ĵ�-��ͼ
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	
	//��ȡ�½���ͼָ��
	CDemo4View* pView=(CDemo4View*)pFrame->MDIGetActive()->GetActiveView();
	
	//��ȡ��������µ��ĵ���ָ��
	CDemo4Doc* pDocNew=pView->GetDocument();

	//��ȡ���ĵ��е�ImgCenterDib�����ָ��
	ImageDib *dibNew=pDocNew->GetPDib();

	//���任������ͼ����Ϊ�½��ĵ���DIB������ʾ
	dibNew->ReplaceDib(graytrans.GetDimensions(),graytrans.m_nBitCountOut,graytrans.m_lpColorTableOut, graytrans.m_pImgDataOut);
	
	//���ù�������
	pView->OnInitialUpdate();


	//�ĵ��������࣬��ʾ������Ϣ
	pDocNew->SetModifiedFlag(TRUE);

	//����ͼˢ����ʾ
	pDocNew->UpdateAllViews(pView);
	
}

void CDemo4View::OnPrewitt() 
{
	// TODO: Add your command handler code here
	CDemo4Doc *pDoc=GetDocument();
	ImageDib *pDib=pDoc->m_dib;
	
	//ֻ����ҶȺͲ�ɫͼ��
	if(pDib->m_nBitCount!=8&&pDib->m_nBitCount!=24){
		::MessageBox(0,"ֻ����ҶȺͲ�ɫͼ��",MB_OK,0);
		return ;
	}
	
	//����ָ������segment�����õ�ǰDIB���ݳ�ʼ��
	ImgSegment segment(pDib->GetDimensions(),pDib->m_nBitCount,
		pDib->m_lpColorTable, pDib->m_pImgData);
	
	//Prewitt����
	segment.Prewitt();
	
	//�½���ͼ����ʾ�ָ���
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	CDemo4View* pView=(CDemo4View*)pFrame->MDIGetActive()->GetActiveView();
	CDemo4Doc* pDocNew=pView->GetDocument();
	ImageDib *dibNew=pDocNew->m_dib;
	dibNew->ReplaceDib(segment.GetDimensions(),segment.m_nBitCountOut,segment.m_lpColorTableOut, segment.m_pImgDataOut);
	pView->OnInitialUpdate();
	pDocNew->SetModifiedFlag(TRUE);
	pDocNew->UpdateAllViews(pView);	
	Invalidate();
}

void CDemo4View::OnFreeRotate() 
{
	// TODO: Add your command handler code here
	CDemo4Doc *pDoc=GetDocument();
	ImageDib *pDib=pDoc->m_dib;
	
	//ֻ����ҶȺͲ�ɫͼ��
	if(pDib->m_nBitCount!=8&&pDib->m_nBitCount!=24){
		::MessageBox(0,"ֻ����ҶȺͲ�ɫͼ��",MB_OK,0);
		return ;
	}
	//��ת�������öԻ���
	RotateDlg dlgPara;
	if(dlgPara.DoModal()==IDOK){
		//����GeometryTrans��Ķ���geoTrans���õ�ǰDIB�����ʼ��
		GeometryTrans geoTrans(pDib->GetDimensions(),pDib->m_nBitCount,
			pDib->m_lpColorTable, pDib->m_pImgData);
		
		//����Rotate��������ͼ����ת�����ǶȺͲ�ֵ��ʽ������������
		geoTrans.Rotate(dlgPara.m_rotateAngle, dlgPara.m_interpolationSelect);
		
		//�½���ͼ���ڣ���ʾ������
		CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
		pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
		CDemo4View* pView=(CDemo4View*)pFrame->MDIGetActive()->GetActiveView();
		CDemo4Doc* pDocNew=pView->GetDocument();
		ImageDib *dibNew=pDocNew->GetPDib();
		dibNew->ReplaceDib(geoTrans.GetDimensions(),geoTrans.m_nBitCountOut,
			geoTrans.m_lpColorTable, geoTrans.m_pImgDataOut);
		pView->OnInitialUpdate();
		pDocNew->SetModifiedFlag(TRUE);
		pDocNew->UpdateAllViews(pView);
	}
}

void CDemo4View::OnBinary() 
{
	// TODO: Add your command handler code here
	//��ȡ�ĵ�����m_dib��ָ�룬���ʵ�ǰDIB����
	CDemo4Doc *pDoc=GetDocument();
	ImageDib *pDib=pDoc->m_dib;
	
	//�쳣�ж�
	if(pDib->m_nBitCount!=24&&pDib->m_nBitCount!=8){
		::MessageBox(0,"ֻ�����ɫ�ͻҶ�ͼ��",MB_OK,0);
		return ;
	}
	
	//��pDib�е�ͼ��������Ϊ�������ݣ����ô������Ĺ��캯����
	//����GrayTrans��Ķ���graytrans
	GrayTrans graytrans(pDib->GetDimensions(),pDib->m_nBitCount,
		pDib->m_lpColorTable, pDib->m_pImgData);
	
	//����Binary()��ͼ����ж�ֵ����ȱʡ״̬����ֵΪ
	graytrans.BinaryImage(120);
	
	//����һ������ͼ����ʾ�ָ���
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	CDemo4View* pView=(CDemo4View*)pFrame->MDIGetActive()->GetActiveView();
	CDemo4Doc* pDocNew=pView->GetDocument();
	ImageDib *dibNew=pDocNew->m_dib;
	dibNew->ReplaceDib(graytrans.GetDimensions(),graytrans.m_nBitCountOut,graytrans.m_lpColorTableOut, graytrans.m_pImgDataOut);
	pView->OnInitialUpdate();	
	pDocNew->SetModifiedFlag(TRUE);
	pDocNew->UpdateAllViews(pView);
}
