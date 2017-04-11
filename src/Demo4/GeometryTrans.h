// GeometryTrans.h: interface for the GeometryTrans class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GEOMETRYTRANS_H__B72367D3_A738_4723_BB37_DC53B73B0F48__INCLUDED_)
#define AFX_GEOMETRYTRANS_H__B72367D3_A738_4723_BB37_DC53B73B0F48__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ImageDib.h"

class GeometryTrans : public ImageDib  
{

public:
    //���ͼ��ÿ����λ��
	int m_nBitCountOut;
	
	//���ͼ��λͼ����ָ��
	unsigned char * m_pImgDataOut;
	
	//���ͼ����ɫ��
	LPRGBQUAD m_lpColorTableOut;
private:
	//���ͼ��Ŀ�
	int m_imgWidthOut;
	
	//���ͼ��ĸ�
	int m_imgHeightOut;
	
	//���ͼ����ɫ����
	int m_nColorTableLengthOut;
	
public:
	//���캯��
	GeometryTrans();
	
	//�������Ĺ��캯��
	GeometryTrans(CSize size, int nBitCount, LPRGBQUAD lpColorTable, unsigned char *pImgData);
	
	//��������
	~GeometryTrans();
	
	//������Ϊ��λ�������ͼ��Ŀ�͸�
	CSize GetDimensions();
	
	//ƽ��
	void Move(int offsetX, int offsetY);
	
	//����
	void Zoom(float ratioX, float ratioY);//����
	
	//ˮƽ����
	void MirrorHorTrans();
	
	//��ֱ����
	void MirrorVerTrans();
	
	//˳ʱ����ת90��
	void Clockwise90();
	
	//��ʱ����ת90��
	void Anticlockwise90();
	
	//��ת180
	void Rotate180();
	
	//0-360��֮������Ƕ���ת 
	void Rotate(float angle, int interpolationflag);//angle��ת�Ƕ�

private:
	//˫���Բ�ֵ
	unsigned char interpolationDblLinear(unsigned char array[2][2], float xpos, float ypos);

	//���������ֵ
	unsigned char interpolationCube(unsigned char array[4][4], float xpos, float ypos);

	//���ڲ�ֵ��ת
	void RotateNeighbor(int angle);

	//˫���Բ�ֵ��ת
	void RotateDblLinear(float angle);

	//���������ֵ��ת
	void RotateCube(int angle);

};

#endif // !defined(AFX_GEOMETRYTRANS_H__B72367D3_A738_4723_BB37_DC53B73B0F48__INCLUDED_)
