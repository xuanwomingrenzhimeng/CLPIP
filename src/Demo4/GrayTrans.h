// GrayTrans.h: interface for the GrayTrans class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRAYTRANS_H__B6C0CDAF_310D_4B49_90AD_71A2B6207E97__INCLUDED_)
#define AFX_GRAYTRANS_H__B6C0CDAF_310D_4B49_90AD_71A2B6207E97__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ImageDib.h"

class GrayTrans : public ImageDib  
{
public:
	//���ͼ��ÿ����λ��
	int m_nBitCountOut;
	
	//���ͼ��λͼ����ָ��
	unsigned char * m_pImgDataOut;
	
	//���ͼ����ɫ��
	LPRGBQUAD m_lpColorTableOut;

	//���ͼ��Ŀ�����Ϊ��λ
	int m_imgWidthOut;
	
	//���ͼ��ĸߣ�����Ϊ��λ
	int m_imgHeightOut;
	
	//���ͼ����ɫ����
	int m_nColorTableLengthOut;
	
public:
	//���������Ĺ��캯��
	GrayTrans();
	
	//�������Ĺ��캯��
	GrayTrans(CSize size, int nBitCount, LPRGBQUAD lpColorTable, 
		unsigned char *pImgData);
	
	//��������
	~GrayTrans();
	
	//������Ϊ��λ�������ͼ��Ŀ�͸�
	CSize GetDimensions();

	//��ɫ��Ҷȸ�ʽ
	void ColorToGray();
	
	//��ֵ��
	void BinaryImage(int threshold=128);

	//��ת
	void RevImage();

    //���ڱ任
	void ThresholdWindow(int bTop, int bBottom);
	
	//��������
	void LinearStrech(CPoint point1,CPoint point2);
	
private:
	//��ͨ��������������
	void LinearStrechForSnglChannel(unsigned char *pImgDataIn,
		unsigned char *pImgDataOut,int imgWidth,int imgHeight,
		CPoint point1,CPoint point2);

};

#endif // !defined(AFX_GRAYTRANS_H__B6C0CDAF_310D_4B49_90AD_71A2B6207E97__INCLUDED_)
