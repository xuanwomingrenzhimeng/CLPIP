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
	ImageDib* pDib = pDoc->m_dib;					//返回m_dib的指针
	
	pDib->Draw(pDC, CPoint(0, 0), pDib->GetDimensions()); 	//显示DIB
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
	//获取文档类指针
	CDemo4Doc *pDoc=GetDocument();
	//获取ImgCenterDib类对象m_dib的指针，访问当前DIB数据
	ImageDib *pDib=pDoc->GetPDib();
	
	//只处理彩色图像

	//将pDib中的图像数据作为输入数据，调用带参数的构造函数，
	//定义GrayTrans类的对象graytrans
	GrayTrans graytrans(pDib->GetDimensions(),pDib->m_nBitCount,
		pDib->m_lpColorTable, pDib->m_pImgData);
	
	//彩色变灰度格式
	graytrans.ColorToGray();
	
	//建立一个新视图，显示分割结果
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	
	//发送新建文件的消息，创建一个新的文档-视图
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	
	//获取新建视图指针
	CDemo4View* pView=(CDemo4View*)pFrame->MDIGetActive()->GetActiveView();
	
	//获取相关联的新的文档类指针
	CDemo4Doc* pDocNew=pView->GetDocument();

	//获取新文档中的ImgCenterDib类对象指针
	ImageDib *dibNew=pDocNew->GetPDib();

	//将变换后的输出图像作为新建文档的DIB进行显示
	dibNew->ReplaceDib(graytrans.GetDimensions(),graytrans.m_nBitCountOut,graytrans.m_lpColorTableOut, graytrans.m_pImgDataOut);
	
	//设置滚动窗口
	pView->OnInitialUpdate();


	//文档数据置脏，提示存盘信息
	pDocNew->SetModifiedFlag(TRUE);

	//各视图刷新显示
	pDocNew->UpdateAllViews(pView);
	
}

void CDemo4View::OnPrewitt() 
{
	// TODO: Add your command handler code here
	CDemo4Doc *pDoc=GetDocument();
	ImageDib *pDib=pDoc->m_dib;
	
	//只处理灰度和彩色图像
	if(pDib->m_nBitCount!=8&&pDib->m_nBitCount!=24){
		::MessageBox(0,"只处理灰度和彩色图像",MB_OK,0);
		return ;
	}
	
	//定义分割类对象segment，并用当前DIB数据初始化
	ImgSegment segment(pDib->GetDimensions(),pDib->m_nBitCount,
		pDib->m_lpColorTable, pDib->m_pImgData);
	
	//Prewitt算子
	segment.Prewitt();
	
	//新建视图，显示分割结果
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
	
	//只处理灰度和彩色图像
	if(pDib->m_nBitCount!=8&&pDib->m_nBitCount!=24){
		::MessageBox(0,"只处理灰度和彩色图像",MB_OK,0);
		return ;
	}
	//旋转参数设置对话框
	RotateDlg dlgPara;
	if(dlgPara.DoModal()==IDOK){
		//定义GeometryTrans类的对象geoTrans，用当前DIB对其初始化
		GeometryTrans geoTrans(pDib->GetDimensions(),pDib->m_nBitCount,
			pDib->m_lpColorTable, pDib->m_pImgData);
		
		//调用Rotate函数进行图像旋转，将角度和插值方式参数传进函数
		geoTrans.Rotate(dlgPara.m_rotateAngle, dlgPara.m_interpolationSelect);
		
		//新建视图窗口，显示处理结果
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
	//获取文档类中m_dib的指针，访问当前DIB数据
	CDemo4Doc *pDoc=GetDocument();
	ImageDib *pDib=pDoc->m_dib;
	
	//异常判断
	if(pDib->m_nBitCount!=24&&pDib->m_nBitCount!=8){
		::MessageBox(0,"只处理彩色和灰度图像",MB_OK,0);
		return ;
	}
	
	//将pDib中的图像数据作为输入数据，调用带参数的构造函数，
	//定义GrayTrans类的对象graytrans
	GrayTrans graytrans(pDib->GetDimensions(),pDib->m_nBitCount,
		pDib->m_lpColorTable, pDib->m_pImgData);
	
	//调用Binary()对图像进行二值化，缺省状态下阈值为
	graytrans.BinaryImage(120);
	
	//建立一个新视图，显示分割结果
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
