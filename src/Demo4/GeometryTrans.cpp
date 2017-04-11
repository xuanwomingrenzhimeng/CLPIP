// GeometryTrans.cpp: implementation of the GeometryTrans class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Demo4.h"
#include "GeometryTrans.h"
#include "math.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


GeometryTrans::GeometryTrans()
{

	m_pImgDataOut=NULL;//���ͼ��λͼ����ָ��Ϊ��
	m_lpColorTableOut=NULL;//���ͼ����ɫ��ָ��Ϊ��
	m_nColorTableLengthOut=0;//���ͼ����ɫ����Ϊ0
    m_nBitCountOut=0;//���ͼ��ÿ����λ��Ϊ0	
	m_imgWidthOut=0;//���ͼ��Ŀ�Ϊ0
	m_imgHeightOut=0;//���ͼ��ĸ�Ϊ0	
}

/***********************************************************************
* �������ƣ� GeometryTrans()
* ���������� CSize size -ͼ���С�����ߣ�
*            int nBitCount  -ÿ������ռλ��
*            LPRGBQUAD lpColorTable  -��ɫ��ָ��
*            unsigned char *pImgData  -λͼ����ָ��
* ����ֵ��   ��
* ˵����������Ϊ�������Ĺ��캯��������λͼ�Ĵ�С��ÿ����λ������ɫ��
*      ��λͼ���ݣ�����ImgDib()�Ի����Ա��ʼ��������ʼ���������
*      ���ݳ�Ա
***********************************************************************/
GeometryTrans::GeometryTrans(CSize size, int nBitCount, LPRGBQUAD lpColorTable,
							 unsigned char *pImgData):
ImageDib(size, nBitCount, lpColorTable, pImgData)
{	
	//���ͼ��ÿ����λ��������ͼ����ͬ
    m_nBitCountOut=m_nBitCount;

	//���ͼ����ɫ����
	m_nColorTableLengthOut=ComputeColorTabalLength(m_nBitCountOut);

	//���ͼ����ɫ��������ͼ����ͬ
	if(m_nColorTableLengthOut){
		//������ɫ��������������ɫ����
		m_lpColorTableOut=new RGBQUAD[m_nColorTableLengthOut];
		memcpy(m_lpColorTableOut,m_lpColorTable, sizeof(RGBQUAD)*m_nColorTableLengthOut);
	}
	else// ��ɫͼ��û����ɫ��
		 m_lpColorTableOut=NULL;

	//���ͼ��ָ��Ϊ��
	m_pImgDataOut=NULL;

	//���ͼ���͸���0
	m_imgWidthOut=0;
	m_imgHeightOut=0;
}

/***********************************************************************
* �������ƣ�  ~GeometryTrans()
* ˵���������������ͷ���Դ
***********************************************************************/
GeometryTrans::~GeometryTrans()
{
	//�ͷ����ͼ��λͼ���ݻ�����
	if(m_pImgDataOut!=NULL){
		delete []m_pImgDataOut;
    	m_pImgDataOut=NULL;
	}

	//�ͷ����ͼ����ɫ��
	if(m_lpColorTableOut!=NULL){
		delete []m_lpColorTableOut;
		m_lpColorTableOut=NULL;
	}
}


/***********************************************************************
* �������ƣ� GetDimensions()
* ���������� ��
* ����ֵ��   ͼ��ĳߴ磬��CSize���ͱ��
* ˵�����������ͼ��Ŀ�͸�
***********************************************************************/
CSize GeometryTrans::GetDimensions()
{
	return CSize(m_imgWidthOut, m_imgHeightOut);
}

/***********************************************************************
* �������ƣ�Move()
* ����������int Xmove  -ˮƽ�����ƽ������������Ϊ��λ
*           int Ymove  -��ֱ�����ƽ������������Ϊ��λ
* ˵����������ˮƽ����ֱ�����λ�����󣬿�ʵ�ֶ�ͼ���ƽ�Ʋ�����
        �������ı�ͼ��Ĵ�С������ͼ��Ĳ����ú�ɫ��䡣
***********************************************************************/
void GeometryTrans::Move(int Xmove, int Ymove)
{
	//�ͷžɵ����ͼ�񻺳���
	if(m_pImgDataOut!=NULL){
		delete []m_pImgDataOut;
    	m_pImgDataOut=NULL;
	}

	//���ͼ��Ŀ�͸�
	m_imgWidthOut=m_imgWidth;
	m_imgHeightOut=m_imgHeight;

	//ÿ�������ֽ��������ͼ��������ͼ�����
	int lineByte=(m_imgWidth*m_nBitCount/8+3)/4*4;

	//���뻺���������������
	m_pImgDataOut=new unsigned char[lineByte*m_imgHeight];

	//�ú�ɫ
	memset(m_pImgDataOut,0,lineByte*m_imgHeight);

	//ѭ��������ͼ������
	int i,j;

	//ѭ������,���ص�ÿ��ͨ��
	int k;

	//ÿ�����ֽ��������ͼ��������ͼ�����
	int pixelByte=m_nBitCountOut/8;

	//ƽ������
	for(i=0;i<m_imgHeight;i++){
		for(j=0;j<m_imgWidth;j++){
			//����ĵ�������ͼ��Χ��
			if(i-Ymove>=0&&i-Ymove<m_imgHeight&&j-Xmove>=0&&j-Xmove<m_imgWidth)
			{
				for(k=0;k<pixelByte;k++)
					*(m_pImgDataOut+i*lineByte+j*pixelByte+k)
					=*(m_pImgData+(i-Ymove)*lineByte+(j-Xmove)*pixelByte+k);
			}
		}
	}
}

/***********************************************************************
* �������ƣ� MirrorHorTrans()
* ˵������ͼ��ˮƽ����
***********************************************************************/
void GeometryTrans::MirrorHorTrans()
{
    //�ͷžɵ����ͼ�񻺳���
	if(m_pImgDataOut!=NULL){
		delete []m_pImgDataOut;
    	m_pImgDataOut=NULL;
	}

	//���ͼ��Ŀ�͸�
	m_imgWidthOut=m_imgWidth;
	m_imgHeightOut=m_imgHeight;

	//ÿ�������ֽ��������ͼ��������ͼ�����
	int lineByte=(m_imgWidth*m_nBitCount/8+3)/4*4;

	//���뻺���������������
	m_pImgDataOut=new unsigned char[lineByte*m_imgHeight];

	//ѭ��������ͼ������
	int i,j;

	//ѭ������,���ص�ÿ��ͨ��
	int k;

	//ÿ�����ֽ��������ͼ��������ͼ�����
	int pixelByte=m_nBitCountOut/8;

	//ˮƽ����
	for(i=0;i<m_imgHeight;i++){
		for(j=0;j<m_imgWidth;j++){
			for(k=0;k<pixelByte;k++)
				*(m_pImgDataOut+i*lineByte+j*pixelByte+k)
				=*(m_pImgData+i*lineByte+(m_imgWidth-1-j)*pixelByte+k);
		}
	}
}

/***********************************************************************
* �������ƣ� MirrorVerTrans()
* ˵������ͼ��ֱ����
***********************************************************************/
void GeometryTrans::MirrorVerTrans()
{
	//�ͷžɵ����ͼ�񻺳���
	if(m_pImgDataOut!=NULL){
		delete []m_pImgDataOut;
    	m_pImgDataOut=NULL;
	}

	//���ͼ��Ŀ�͸�
	m_imgWidthOut=m_imgWidth;
	m_imgHeightOut=m_imgHeight;

	//ÿ�������ֽ��������ͼ��������ͼ�����
	int lineByte=(m_imgWidth*m_nBitCount/8+3)/4*4;

	//���뻺���������������
	m_pImgDataOut=new unsigned char[lineByte*m_imgHeight];

	//ѭ��������ͼ������
	int i,j;

	//ѭ������,���ص�ÿ��ͨ��
	int k;

	//ÿ�����ֽ��������ͼ��������ͼ�����
	int pixelByte=m_nBitCountOut/8;

	//��ֱ����
	for(i=0;i<m_imgHeight;i++){
		for(j=0;j<m_imgWidth;j++){
			for(k=0;k<pixelByte;k++)
				*(m_pImgDataOut+i*lineByte+j*pixelByte+k)
				=*(m_pImgData+(m_imgHeight-1-i)*lineByte+j*pixelByte+k);
		}
	}
}

/***********************************************************************
* �������ƣ� Clockwise90()
* ˵������ͼ��˳ʱ����ת90��
***********************************************************************/
void GeometryTrans::Clockwise90()
{
	//�ͷžɵ����ͼ�񻺳���
	if(m_pImgDataOut!=NULL){
		delete []m_pImgDataOut;
    	m_pImgDataOut=NULL;
	}

	//����ͼ��ÿ�������ֽ���
	int lineByte=(m_imgWidth*m_nBitCount/8+3)/4*4;

	//���ͼ��Ŀ�͸�
	m_imgWidthOut=m_imgHeight;
	m_imgHeightOut=m_imgWidth;

	//���ͼ��ÿ�������ֽ���
	int lineByteOut=(m_imgWidthOut*m_nBitCount/8+3)/4*4;

	//���뻺���������������
	m_pImgDataOut=new unsigned char[lineByteOut*m_imgHeightOut];

	//ѭ��������ͼ������
	int i,j;

	//ѭ������,���ص�ÿ��ͨ��
	int k;

	//ÿ�����ֽ��������ͼ��������ͼ�����
	int pixelByte=m_nBitCountOut/8;

	//˳ʱ��90��
	for(i=0;i<m_imgHeightOut;i++){
		for(j=0;j<m_imgWidthOut;j++){
			for(k=0;k<pixelByte;k++)
				*(m_pImgDataOut+i*lineByteOut+j*pixelByte+k)
				=*(m_pImgData+j*lineByte+(m_imgWidth-1-i)*pixelByte+k);
		}
	}
}


/***********************************************************************
* �������ƣ� Anticlockwise90()
* ˵������ͼ����ʱ����ת90��
***********************************************************************/
void GeometryTrans::Anticlockwise90()
{
	//�ͷžɵ����ͼ�񻺳���
	if(m_pImgDataOut!=NULL){
		delete []m_pImgDataOut;
    	m_pImgDataOut=NULL;
	}

	//����ͼ��ÿ�������ֽ���
	int lineByte=(m_imgWidth*m_nBitCount/8+3)/4*4;

	//���ͼ��Ŀ�͸�
	m_imgWidthOut=m_imgHeight;
	m_imgHeightOut=m_imgWidth;

	//���ͼ��ÿ�������ֽ���
	int lineByteOut=(m_imgWidthOut*m_nBitCount/8+3)/4*4;

	//���뻺���������������
	m_pImgDataOut=new unsigned char[lineByteOut*m_imgHeightOut];

	//ѭ��������ͼ������
	int i,j;

	//ѭ������,���ص�ÿ��ͨ��
	int k;

	//ÿ�����ֽ��������ͼ��������ͼ�����
	int pixelByte=m_nBitCountOut/8;

	//��ʱ��90��
	for(i=0;i<m_imgHeightOut;i++){
		for(j=0;j<m_imgWidthOut;j++){
			for(k=0;k<pixelByte;k++)
				*(m_pImgDataOut+i*lineByteOut+j*pixelByte+k)
				=*(m_pImgData+(m_imgHeight-1-j)*lineByte+i*pixelByte+k);
		}
	}
}

/***********************************************************************
* �������ƣ�Rotate180()
* ˵������ͼ����ת180��
***********************************************************************/
void GeometryTrans::Rotate180()
{
	//�ͷžɵ����ͼ�񻺳���
	if(m_pImgDataOut!=NULL){
		delete []m_pImgDataOut;
    	m_pImgDataOut=NULL;
	}

	//���ͼ��Ŀ�͸�
	m_imgWidthOut=m_imgWidth;
	m_imgHeightOut=m_imgHeight;

	//ÿ�������ֽ��������ͼ��������ͼ�����
	int lineByte=(m_imgWidth*m_nBitCount/8+3)/4*4;

	//���뻺���������������
	m_pImgDataOut=new unsigned char[lineByte*m_imgHeight];

	//ѭ��������ͼ������
	int i,j;

	//ѭ������,���ص�ÿ��ͨ��
	int k;

	//ÿ�����ֽ��������ͼ��������ͼ�����
	int pixelByte=m_nBitCountOut/8;

	//��ת180��
	for(i=0;i<m_imgHeightOut;i++){
		for(j=0;j<m_imgWidthOut;j++){
			for(k=0;k<pixelByte;k++)
				*(m_pImgDataOut+i*lineByte+j*pixelByte+k)
				=*(m_pImgData+(m_imgHeight-1-i)*lineByte+(m_imgWidth-1-j)*pixelByte+k);
		}
	}
}


/*************************************************************************
 * �������ƣ� Zoom()
 * ����:   float ratioX  -���������
 *         float ratioY  -�߶�������
  * ����ֵ: ��
 * ˵��:   ����ָ���Ĵ�С��ָ���Ĳ�ֵ��ʽ����ԭͼ��������ţ����ź�Ľ�����
 *          ��m_pImgDataOut�������У��ú���ͬʱ�ʺ��ڲ�ɫ�ͻҶ�ͼ��
 ************************************************************************/
void GeometryTrans::Zoom(float ratioX, float ratioY)
{
	
	//�ͷžɵ����ͼ�񻺳���
	if(m_pImgDataOut!=NULL){
		delete []m_pImgDataOut;
    	m_pImgDataOut=NULL;
	}
    
	//���ͼ��Ŀ�͸�
	m_imgWidthOut=int(m_imgWidth*ratioX+0.5) ;
	m_imgHeightOut=int(m_imgHeight*ratioY+0.5); 

	//����ͼ��ÿ�������ֽ���
	int lineByteIn=(m_imgWidth*m_nBitCount/8+3)/4*4;
	
	//���ͼ��ÿ�������ֽ���
    int	lineByteOut=(m_imgWidthOut*m_nBitCount/8+3)/4*4;

	//���뻺���������������
	m_pImgDataOut=new unsigned char[lineByteOut*m_imgHeightOut];

	//ÿ�����ֽ���������ͼ�������ͼ����ͬ
	int pixelByte=m_nBitCount/8;
	
	//���ͼ��������ͼ���д���ֵ��λ������
	int coordinateX, coordinateY;
	
	//ѭ�����������ͼ�������
	int i, j;
	
	//ѭ������,���ص�ÿ��ͨ��
	int k;
	
	//���ڲ�ֵ
	for(i=0; i< m_imgHeightOut; i++){
		for(j=0; j<m_imgWidthOut; j++){  
			//���ͼ������Ϊ(j,i)������ӳ�䵽ԭͼ�е�����ֵ������ֵλ��
			coordinateX=j/ratioX+0.5;
			coordinateY=i/ratioY+0.5;
			
			//����ֵλ��������ͼ��Χ�ڣ�����ڲ�ֵ
			if(0<=coordinateX&&coordinateX<m_imgWidth
				&& coordinateY>=0&&coordinateY<m_imgHeight){
				for(k=0;k<pixelByte;k++)
					*(m_pImgDataOut + i * lineByteOut + j*pixelByte + k) 
					=*(m_pImgData+ coordinateY*lineByteIn+ coordinateX*pixelByte + k) ;
			}
			else //����������ͼ��Χ�ڣ�����255  
			{
				for(k=0;k<pixelByte;k++)
					*(m_pImgDataOut + i * lineByteOut + j*pixelByte+k) = 255;
			}
			
		}
	}


}


/*************************************************************************
 * �������ƣ�  Rotate()
 * ����:   int angle  -��ת�Ƕ�
 * ˵��:   ����ָ����ת�Ƕȣ����ý��ڲ�ֵ��ת������ԭͼ�������ת��
 *         ��ת��������m_pImgDataOut�������У��ú���ͬʱ�ʺ��ڲ�ɫ�ͻҶ�ͼ��
 ************************************************************************/
void GeometryTrans::Rotate(float angle, int interpolationflag)
{
	if(interpolationflag==0)//���ڲ�ֵ����
		RotateNeighbor(angle);

	else if(interpolationflag==1)//˫���Բ�ֵ����
		RotateDblLinear(angle);

	else//���������ֵ����
	    RotateCube(angle);
}

/*************************************************************************
 *
 * �������ƣ�
 *   RotateNeighbor()�����ڲ�ֵ��ת
 *
 * ����:
 *   int angle	- ��ת�ĽǶȣ�0-360�ȣ�
 *
 * ����ֵ:
 *   �ޡ�
 *
 * ˵��:
 *    ��������ڲ�ֵ��ʽ��������ͼ������Ϊԭ�㣬��ͼ����תangle����ת���
 *    �����m_pImgDataOut�У��ú���ͬʱ�ʺ��ڲ�ɫ�ͻҶ�ͼ��
 *
 ************************************************************************/
void GeometryTrans::RotateNeighbor(int angle)
{
	//�ͷžɵ����ͼ�񻺳���
	if(m_pImgDataOut!=NULL){
		delete []m_pImgDataOut;
    	m_pImgDataOut=NULL;
	}

	//ÿ������ռ�ֽ���������ͼ�������ͼ����ͬ
	int pixelByte=m_nBitCount/8;

	// ����ͼ��ÿ��������ռ�ֽ���
	int lineByte=(m_imgWidth*pixelByte+3)/4*4;

	// ��ת�Ƕȣ����ȣ�, ����ת�ǶȴӶ�ת��������
	float	fRotateAngle= 2*3.1415926*angle/360;
	
	// ����ͼ���ĸ��ǵ����꣬��ͼ������Ϊ����ϵԭ��
	float	fSrcX1,fSrcY1,fSrcX2,fSrcY2,fSrcX3,fSrcY3,fSrcX4,fSrcY4;
	
	// ��ת���ĸ��ǵ����꣬��ͼ������Ϊ����ϵԭ��
	float	fDstX1,fDstY1,fDstX2,fDstY2,fDstX3,fDstY3,fDstX4,fDstY4;
	
	// ������ת�Ƕȵ�����
	float fSina = (float) sin((double)fRotateAngle);
	
	// ������ת�Ƕȵ�����
	float fCosa = (float) cos((double)fRotateAngle);
	
	// ����ԭͼ���ĸ��ǵ����꣬��ͼ������Ϊ����ϵԭ��
	fSrcX1 = (float) (- (m_imgWidth  - 1) / 2);
	fSrcY1 = (float) (  (m_imgHeight - 1) / 2);
	fSrcX2 = (float) (  (m_imgWidth  - 1) / 2);
	fSrcY2 = (float) (  (m_imgHeight - 1) / 2);
	fSrcX3 = (float) (- (m_imgWidth  - 1) / 2);
	fSrcY3 = (float) (- (m_imgHeight - 1) / 2);
	fSrcX4 = (float) (  (m_imgWidth  - 1) / 2);
	fSrcY4 = (float) (- (m_imgHeight - 1) / 2);
	
	// ������ͼ�ĸ��ǵ����꣬��ͼ������Ϊ����ϵԭ��
	fDstX1 =  fCosa * fSrcX1 + fSina * fSrcY1;
	fDstY1 = -fSina * fSrcX1 + fCosa * fSrcY1;
	fDstX2 =  fCosa * fSrcX2 + fSina * fSrcY2;
	fDstY2 = -fSina * fSrcX2 + fCosa * fSrcY2;
	fDstX3 =  fCosa * fSrcX3 + fSina * fSrcY3;
	fDstY3 = -fSina * fSrcX3 + fCosa * fSrcY3;
	fDstX4 =  fCosa * fSrcX4 + fSina * fSrcY4;
	fDstY4 = -fSina * fSrcX4 + fCosa * fSrcY4;
	
	// ��ת�����ͼ����
	m_imgWidthOut  = (LONG) ( max( fabs(fDstX4 - fDstX1), fabs(fDstX3 - fDstX2) ) + 0.5);
	
	// ��ת�����ͼ��߶�
	m_imgHeightOut = (LONG) ( max( fabs(fDstY4 - fDstY1), fabs(fDstY3 - fDstY2) ) + 0.5);

	// ��ת�����ͼ��ÿ�е��ֽ���
	int lineByteOut=(m_imgWidthOut*pixelByte+3)/4*4;
	
	//���仺�����������ת���
	m_pImgDataOut = new unsigned char[lineByteOut*m_imgHeightOut];

	// �������������������Ժ�ÿ�ζ�������
	float f1 = (float) (-0.5 * (m_imgWidthOut - 1) * fCosa 
		                + 0.5 * (m_imgHeightOut - 1) * fSina + 0.5 * (m_imgWidth  - 1));
	float f2 = (float) (-0.5 * (m_imgWidthOut - 1) * fSina 
		                - 0.5 * (m_imgHeightOut - 1) * fCosa + 0.5 * (m_imgHeight - 1));

	// ѭ�����������ͼ������
	int	i, j;

	//ѭ�����������ص�ÿ��ͨ��
	int k;
	
	//���ͼ��������ͼ���д���ֵ��λ�����꣬���븡����
	int	coordinateX, coordinateY;

	// ����ڲ�ֵ��ת
	for(i = 0; i < m_imgHeightOut; i++)
	{
		for(j = 0; j < m_imgWidthOut; j++)
		{
			
			// ���ͼ������(j,i)ӳ�䵽����ͼ������꣬���ڲ�ֵȡ����
			coordinateX = (int)(j * fCosa - i * fSina + f1 + 0.5);
			coordinateY = (int)(j * fSina + i * fCosa + f2 + 0.5);
			
			// �ж��Ƿ�������ͼ��Χ��
			if( (coordinateX >= 0) && (coordinateX < m_imgWidth) && (coordinateY >= 0) 
				&& (coordinateY < m_imgHeight))
			{
				//��ͼ��ÿ��ͨ�������ݽ��зֱ��ֵ����ɫͼ��pixelByteΪ3��
				//�Ҷ�ͼ��pixelByteΪ1
				for(k=0; k<pixelByte; k++)
					*(m_pImgDataOut+i*lineByteOut+j*pixelByte+k)
					=*(m_pImgData+coordinateY*lineByte+coordinateX*pixelByte+k);
			}
			else
			{
				// ���ڲ���ԭͼ�е����أ���ֵΪ255
				for(k=0; k<pixelByte; k++)
		    		*(m_pImgDataOut+i*lineByteOut+j*pixelByte+k) = 255;
			}
			
		}
		
	}
	
}

/*************************************************************************
 *
 * �������ƣ�
 *   RotateDblLinear()
 *
 * ����:
 *   int angle	- ��ת�ĽǶȣ�0-360�ȣ�
 *
 * ����ֵ:
 *   �ޡ�
 *
 * ˵��:
 *    ����˫���Բ�ֵ��ʽ��������ͼ������Ϊԭ�㣬��ͼ����תangle����ת���
 *    �����m_pImgDataOut�У��ú���ͬʱ�ʺ��ڲ�ɫ�ͻҶ�ͼ��
 *
 ************************************************************************/
void GeometryTrans::RotateDblLinear(float angle)
{
	//�ͷžɵ����ͼ�񻺳���
	if(m_pImgDataOut!=NULL){
		delete []m_pImgDataOut;
    	m_pImgDataOut=NULL;
	}

	//ÿ������ռ�ֽ���������ͼ�������ͼ����ͬ
	int pixelByte=m_nBitCount/8;

	// ����ͼ��ÿ��������ռ�ֽ���
	int lineByte=(m_imgWidth*pixelByte+3)/4*4;

	// ��ת�Ƕȣ����ȣ�, ����ת�ǶȴӶ�ת��������
	float	fRotateAngle= 2*3.1415926*angle/360;
	
/*	// ����ͼ���ĸ��ǵ����꣬��ͼ������Ϊ����ϵԭ��
	float	fSrcX1,fSrcY1,fSrcX2,fSrcY2,fSrcX3,fSrcY3,fSrcX4,fSrcY4;
	
	// ��ת���ĸ��ǵ����꣬��ͼ������Ϊ����ϵԭ��
	float	fDstX1,fDstY1,fDstX2,fDstY2,fDstX3,fDstY3,fDstX4,fDstY4;
	
	// ������ת�Ƕȵ�����
	float fSina = (float) sin((double)fRotateAngle);
	
	// ������ת�Ƕȵ�����
	float fCosa = (float) cos((double)fRotateAngle);
	
	// ����ԭͼ���ĸ��ǵ����꣬��ͼ������Ϊ����ϵԭ��
	fSrcX1 = (float) (- (m_imgWidth  - 1) / 2);
	fSrcY1 = (float) (  (m_imgHeight - 1) / 2);
	fSrcX2 = (float) (  (m_imgWidth  - 1) / 2);
	fSrcY2 = (float) (  (m_imgHeight - 1) / 2);
	fSrcX3 = (float) (- (m_imgWidth  - 1) / 2);
	fSrcY3 = (float) (- (m_imgHeight - 1) / 2);
	fSrcX4 = (float) (  (m_imgWidth  - 1) / 2);
	fSrcY4 = (float) (- (m_imgHeight - 1) / 2);
	
	// ������ͼ�ĸ��ǵ����꣬��ͼ������Ϊ����ϵԭ��
	fDstX1 =  fCosa * fSrcX1 + fSina * fSrcY1;
	fDstY1 = -fSina * fSrcX1 + fCosa * fSrcY1;
	fDstX2 =  fCosa * fSrcX2 + fSina * fSrcY2;
	fDstY2 = -fSina * fSrcX2 + fCosa * fSrcY2;
	fDstX3 =  fCosa * fSrcX3 + fSina * fSrcY3;
	fDstY3 = -fSina * fSrcX3 + fCosa * fSrcY3;
	fDstX4 =  fCosa * fSrcX4 + fSina * fSrcY4;
	fDstY4 = -fSina * fSrcX4 + fCosa * fSrcY4;*/
	
	// ��ת�����ͼ����
	m_imgWidthOut  = m_imgWidth;
	
	// ��ת�����ͼ��߶�
	m_imgHeightOut = m_imgHeight;

	// ��ת�����ͼ��ÿ�е��ֽ���
	int lineByteOut= lineByte;
	
	//���仺�����������ת���
	m_pImgDataOut = new unsigned char[lineByteOut*m_imgHeightOut];

	// �������������������Ժ�ÿ�ζ�������
	float fy = tan(fRotateAngle);
	
	// ѭ�����������ͼ������
	int	i, j;

	//ѭ�����������ص�ÿ��ͨ��
	int k;
	
	//���ͼ��������ͼ���д���ֵ��λ�����꣬���븡����
	int	coordinateX, coordinateY;

	//��Ŵ���ֵ��4�����ص�����
	unsigned char array[2][2];

	//�����м����
	int Iu, Iv;

	//˫���Բ�ֵ��ת
	for(i = 0; i < m_imgHeightOut; i++)
	{
		for(j = 0; j < m_imgWidthOut; j++)
		{		
			// ���ͼ������(j,i)ӳ�䵽����ͼ�������
			coordinateX = j;
			coordinateY = i+fy*j;

			//������ȡ��
			Iu=(int)coordinateX;
			Iv=(int)coordinateY;

			// �ж��Ƿ���ԭͼ��Χ��
			if( (coordinateX >= 0) && (coordinateX < m_imgWidth-1) && (coordinateY >= 0) 
				&& (coordinateY < m_imgHeight-1))
			{
				//��ͼ��ÿ��ͨ�������ݽ��зֱ��ֵ����ɫͼ��pixelByteΪ3��
				//�Ҷ�ͼ��pixelByteΪ1
				for(k=0;k<pixelByte;k++){
					//����ǰ����������Χ2*2�������ؿ���������array
					array[0][0]=*(m_pImgData+ Iv*lineByte+ Iu*pixelByte+k);
					array[0][1]=*(m_pImgData+ Iv*lineByte+ (Iu+1)*pixelByte+k);
					array[1][0]=*(m_pImgData+ (Iv+1)*lineByte+ Iu*pixelByte+k);
					array[1][1]=*(m_pImgData+ (Iv+1)*lineByte+ (Iu+1)*pixelByte+k);
					*(m_pImgDataOut + i * lineByteOut + j*pixelByte+k)
						=interpolationDblLinear(array, coordinateX-Iu, coordinateY-Iv);
				}
			}
			else
			{
				// ���ڲ���ԭͼ��Χ�ڵ������أ���ֵΪ255
				for(k=0;k<pixelByte;k++)
	     			*(m_pImgDataOut+i*lineByteOut+j*pixelByte+k) = 255;
			}
			
		}
		
	}
	
}


/*************************************************************************
 *
 * �������ƣ�
 *   RotateCube()
 *
 * ����:
 *   int angle	- ��ת�ĽǶȣ�0-360�ȣ�
 *
 * ����ֵ:
 *   ��
 *
 * ˵��:
 *    �������������ֵ��ʽ��������ͼ������Ϊԭ�㣬��ͼ����תangle����ת���
 *    �����m_pImgDataOut�У��ú���ͬʱ�ʺ��ڲ�ɫ�ͻҶ�ͼ��
 *
 ************************************************************************/
void GeometryTrans::RotateCube(int angle)
{
	//�ͷžɵ����ͼ�񻺳���
	if(m_pImgDataOut!=NULL){
		delete []m_pImgDataOut;
    	m_pImgDataOut=NULL;
	}

	//ÿ������ռ�ֽ���������ͼ�������ͼ����ͬ
	int pixelByte=m_nBitCount/8;

	// ����ͼ��ÿ��������ռ�ֽ���
	int lineByte=(m_imgWidth*pixelByte+3)/4*4;

	// ��ת�Ƕȣ����ȣ�, ����ת�ǶȴӶ�ת��������
	float	fRotateAngle= 2*3.1415926*angle/360;
	
	// ����ͼ���ĸ��ǵ����꣬��ͼ������Ϊ����ϵԭ��
	float	fSrcX1,fSrcY1,fSrcX2,fSrcY2,fSrcX3,fSrcY3,fSrcX4,fSrcY4;
	
	// ��ת���ĸ��ǵ����꣬��ͼ������Ϊ����ϵԭ��
	float	fDstX1,fDstY1,fDstX2,fDstY2,fDstX3,fDstY3,fDstX4,fDstY4;
	
	// ������ת�Ƕȵ�����
	float fSina = (float) sin((double)fRotateAngle);
	
	// ������ת�Ƕȵ�����
	float fCosa = (float) cos((double)fRotateAngle);
	
	// ����ԭͼ���ĸ��ǵ����꣬��ͼ������Ϊ����ϵԭ��
	fSrcX1 = (float) (- (m_imgWidth  - 1) / 2);
	fSrcY1 = (float) (  (m_imgHeight - 1) / 2);
	fSrcX2 = (float) (  (m_imgWidth  - 1) / 2);
	fSrcY2 = (float) (  (m_imgHeight - 1) / 2);
	fSrcX3 = (float) (- (m_imgWidth  - 1) / 2);
	fSrcY3 = (float) (- (m_imgHeight - 1) / 2);
	fSrcX4 = (float) (  (m_imgWidth  - 1) / 2);
	fSrcY4 = (float) (- (m_imgHeight - 1) / 2);
	
	// ������ͼ�ĸ��ǵ����꣬��ͼ������Ϊ����ϵԭ��
	fDstX1 =  fCosa * fSrcX1 + fSina * fSrcY1;
	fDstY1 = -fSina * fSrcX1 + fCosa * fSrcY1;
	fDstX2 =  fCosa * fSrcX2 + fSina * fSrcY2;
	fDstY2 = -fSina * fSrcX2 + fCosa * fSrcY2;
	fDstX3 =  fCosa * fSrcX3 + fSina * fSrcY3;
	fDstY3 = -fSina * fSrcX3 + fCosa * fSrcY3;
	fDstX4 =  fCosa * fSrcX4 + fSina * fSrcY4;
	fDstY4 = -fSina * fSrcX4 + fCosa * fSrcY4;
	
	// ��ת�����ͼ����
	m_imgWidthOut  = (LONG) ( max( fabs(fDstX4 - fDstX1), fabs(fDstX3 - fDstX2) ) + 0.5);
	
	// ��ת�����ͼ��߶�
	m_imgHeightOut = (LONG) ( max( fabs(fDstY4 - fDstY1), fabs(fDstY3 - fDstY2) ) + 0.5);

	// ��ת�����ͼ��ÿ�е��ֽ���
	int lineByteOut=(m_imgWidthOut*pixelByte+3)/4*4;
	
	//���仺�����������ת���
	m_pImgDataOut = new unsigned char[lineByteOut*m_imgHeightOut];

	// �������������������Ժ�ÿ�ζ�������
	float f1 = (float) (-0.5 * (m_imgWidthOut - 1) * fCosa 
		                + 0.5 * (m_imgHeightOut - 1) * fSina + 0.5 * (m_imgWidth  - 1));
	float f2 = (float) (-0.5 * (m_imgWidthOut - 1) * fSina 
		                - 0.5 * (m_imgHeightOut - 1) * fCosa + 0.5 * (m_imgHeight - 1));

	// ѭ�����������ͼ������
	int	i, j;

	//ѭ�����������ص�ÿ��ͨ��
	int k;
	
	//���ͼ��������ͼ���д���ֵ��λ�����꣬���븡����
	int	coordinateX, coordinateY;

	//��Ŵ���ֵ��16�����ص�����
	unsigned char array[4][4];

	//�����м����
	int Iu, Iv;

	//ѭ����������ȷ��Ҫ��ֵ��λ��ȡ4x4������
	int x, y;

	// ���������ֵ
	for(i = 0; i < m_imgHeightOut; i++)
	{
		for(j = 0; j < m_imgWidthOut; j++)
		{		
			// ���ͼ������(j,i)ӳ�䵽����ͼ�������
			coordinateX = j * fCosa - i * fSina + f1;
			coordinateY = j * fSina + i * fCosa + f2;

			//������ȡ��
			Iu=(int)coordinateX;
			Iv=(int)coordinateY;

			// �ж��Ƿ���ԭͼ��Χ��
			if( (coordinateX >= 1) && (coordinateX < m_imgWidth-3) && (coordinateY >= 1) 
				&& (coordinateY < m_imgHeight-3))
			{
				//��ͼ��ÿ��ͨ�������ݽ��зֱ��ֵ����ɫͼ��pixelByteΪ3��
				//�Ҷ�ͼ��pixelByteΪ1
				for(k=0;k<pixelByte;k++){
					//����ǰ����������Χ4*4�������ؿ���������array
					for(y=Iv-1;y<Iv+3;y++){
						for (x=Iu-1;x<Iu+3;x++){
							array[y-Iv+1][x-Iu+1]=*(m_pImgData+y*lineByte+x*pixelByte+k);
						}
					}
					*(m_pImgDataOut + i * lineByteOut + j*pixelByte+k)
						=interpolationCube(array, coordinateX-Iu, coordinateY-Iv);
				}
			}
			else
			{
				// ���ڲ���ԭͼ�ڵ����أ���ֵΪ255
				for(k=0;k<pixelByte;k++)
    	 			*(m_pImgDataOut+i*lineByteOut+j*pixelByte+k) = 255;
			}
			
		}
		
	}
	
}


/*************************************************************************
 *
 * �������ƣ�
 *   interpolationDblLinear()
 *
 * ����:
 *   array��2*2���飬���ͼ�����ֵλ����Χ�ĸ����ػҶ�ֵ
 *   xpos��yposΪ����������ĸ����صĲ�ֵλ�����꣬ȡС��
 *
 * ����ֵ:
 *   ��ֵ�����
 *
 * ˵��:
 *   �ú�����ԭͼ�����ֵλ�õ��ĸ��������ݿ���������array�У����ݲ�ֵλ�������
 *   Ӧ��array��λ�ã�������array���ĸ�Ԫ�ؽ���˫���Բ�ֵ������ֵΪ��ֵ�Ľ����
 ************************************************************************/
unsigned char GeometryTrans::interpolationDblLinear(unsigned char array[2][2], 
													float xpos, float ypos)
{
	//�����м����
	int t1, t2;

	//�ȴ�ֱ�������Բ�ֵ
	t1 = (1-ypos)*array[0][0] + ypos*array[1][0];
	t2 = (1-ypos)*array[0][1] + ypos*array[1][1];

	//��ˮƽ�������Բ�ֵ
	float t=(int)((1-xpos)*t1 + xpos*t2);

	//����ֵ���С��0�������0
	if(t<0)
		t=0;

	//����ֵ�������255�������255
	if(t>255) 
		t=255;

	//��ֵ�������
	return (unsigned char)t;
}


/*************************************************************************
 *
 * �������ƣ�
 *   interpolationCube()
 *
 * ����:
 *   array��4x4���飬���ͼ�����ֵλ����Χ16�����ػҶ�ֵ
 *   xpos��ypos��Ӧ��4x4����16��Ԫ�صĲ�ֵ����
 *
 * ����ֵ:
 *   ��ֵ�����
 *
 * ˵��:
 *   �ú�����ԭͼ�����ֵλ����Χ16���������ݿ���������array�У����ݲ�ֵλ�������
 *   Ӧ��array��λ�ã�������array��16��Ԫ�ؽ������������ֵ������ֵΪ��ֵ�Ľ����
 *
 ************************************************************************/
unsigned char GeometryTrans::interpolationCube(unsigned char array[4][4], float xpos, float ypos)
{

	//�������飬�����ֵ����Ҫ��ϵ��
	float col[4], row[4];

	//׼����ֵ��x��������Դ
	col[0]=xpos+1;
	col[1]=xpos;
	col[2]=1-xpos;
	col[3]=2-xpos;

	//׼����ֵ��y��������Դ
	row[0]=ypos+1;
	row[1]=ypos;
	row[2]=1-ypos;
	row[3]=2-ypos;
	
	//ѭ������
	int i;

	//��ʱ����
	float t;

	//��ˮƽ����ϵ��������м���
	for(i=0;i<4;i++){
		t=fabs(col[i]);
		if (t>=0&&t<1)
			col[i]=pow(t,3)-2*pow(t,2)+1;
		else if (t>=1&&t<2)
			col[i]=-pow(t,3)+5*pow(t,2)-8*t+4;
		else
			col[i]=0;
	}

	//�Դ�ֱ����ϵ��������м���
	for(i=0;i<4;i++){
		t=fabs(row[i]);
		if (t>=0&&t<1)
			row[i]=pow(t,3)-2*pow(t,2)+1;
		else if (t>=1&&t<2)
			row[i]=-pow(t,3)+5*pow(t,2)-8*t+4;
		else
			row[i]=0;
	}
	
	//������õ�ϵ�����Ӧͼ���������������
	float tempArray[4], temp;
	//��x������
	for(i=0;i<4;i++)
		tempArray[i]=row[0]*array[0][i]+row[1]*array[1][i]+row[2]*array[2][i]+row[3]*array[3][i];
	
	//��y������
	temp=0;
	for (i=0;i<4;i++)
		temp+=tempArray[i]*col[i];
		
	//����ֵ�����ͼ��Ҷȼ���Χ�����
	if (temp>255)
		temp=255;
	if (temp<0)
		temp=0;

	//��������ֵ����ֵ���
	return (unsigned char)temp;

}