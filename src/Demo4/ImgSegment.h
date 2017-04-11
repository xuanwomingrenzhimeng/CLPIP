// ImgSegment.h: interface for the ImgSegment class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMGSEGMENT_H__FCB7CF39_B6FD_406A_B7B4_D237EAE7FDFD__INCLUDED_)
#define AFX_IMGSEGMENT_H__FCB7CF39_B6FD_406A_B7B4_D237EAE7FDFD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ImageDib.h"

class ImgSegment : public ImageDib  
{
public:
	//���ͼ��ÿ����λ��
	int m_nBitCountOut;
	//���ͼ��λͼ����ָ��
	unsigned char * m_pImgDataOut;	
	//���ͼ����ɫ��
	LPRGBQUAD m_lpColorTableOut;	
    //���ͼ��Ŀ�
	int m_imgWidthOut;	
	//���ͼ��ĸ�
	int m_imgHeightOut;
	//���ͼ����ɫ����
	int m_nColorTableLengthOut;	
public:
	//���������Ĺ��캯��
	ImgSegment();	
	//�������Ĺ��캯��
	ImgSegment(CSize size, int nBitCount, LPRGBQUAD lpColorTable, 
		unsigned char *pImgData);
	//��������
	virtual ~ImgSegment();
public:
	//������Ϊ��λ�������ͼ��ĳߴ�
	CSize GetDimensions();
    //����Ӧ��ֵ�ָ�
	void AdaptThreshSeg(unsigned char *pImgData);
	//Roberts����
	void Roberts();	
    //Sobel����
	void Sobel();	
	//Prewitt����
	void Prewitt();	
	//Laplacian����
	void Laplacian();	
public:
	//��������
	void RegionGrow(CPoint SeedPos, int thresh);
	//���߸���
	void EdgeTrace();

};

#endif // !defined(AFX_IMGSEGMENT_H__FCB7CF39_B6FD_406A_B7B4_D237EAE7FDFD__INCLUDED_)
