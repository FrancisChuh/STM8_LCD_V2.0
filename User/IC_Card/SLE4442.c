
#include <reg52.h>
#include "SLE4442.h"
#include <intrins.h>

/* ��ʱ5��us�궨�� */
#define Delay5Us()    _nop_();_nop_();_nop_();_nop_();_nop_()

/* ��ʱ10��us�궨�� */
#define Delay10Us()   _nop_();_nop_();_nop_();_nop_();_nop_();\
					  _nop_();_nop_();_nop_();_nop_();_nop_()

unsigned char bdata ibase;		//����λѰַ��Ԫ,���ڷ��������
								//һ���ֽ�
sbit mybit0 = ibase^0;
sbit mybit1 = ibase^1;
sbit mybit2 = ibase^2;
sbit mybit3 = ibase^3;
sbit mybit4 = ibase^4;
sbit mybit5 = ibase^5;
sbit mybit6 = ibase^6;
sbit mybit7 = ibase^7;

/***************************************************************
�������ƣ�Readchar
��	  �ܣ���һ���ֽ�
��	  ��: ��
��	  �������õ��ֽڵ�ֵ 
****************************************************************/
unsigned char Readchar(void)
{
	CLK = 0; Delay5Us(); mybit0 = IO; CLK = 1; Delay5Us();	//һ���������1 bit
	CLK = 0; Delay5Us(); mybit1 = IO; CLK = 1; Delay5Us();	//һ���������1 bit
	CLK = 0; Delay5Us(); mybit2 = IO; CLK = 1; Delay5Us();	//һ���������1 bit
	CLK = 0; Delay5Us(); mybit3 = IO; CLK = 1; Delay5Us();	//һ���������1 bit
	CLK = 0; Delay5Us(); mybit4 = IO; CLK = 1; Delay5Us();	//һ���������1 bit
	CLK = 0; Delay5Us(); mybit5 = IO; CLK = 1; Delay5Us();	//һ���������1 bit
	CLK = 0; Delay5Us(); mybit6 = IO; CLK = 1; Delay5Us();	//һ���������1 bit
	CLK = 0; Delay5Us(); mybit7 = IO; CLK = 1; Delay5Us();	//һ���������1 bit
	
	return(ibase);		//���ض��õ�һ���ֽ�
}

/************************************************************
�������ƣ�SendByte
��    �ܣ���һ���ֽڵ������ɵ͵���λ���η��ͳ�ȥ
��	  �룺unsigned char sendchar --- Ҫ���͵��ֽ�
��	  ������
*************************************************************/
void SendByte(unsigned char sendchar)
{	
	unsigned char i = 8;
	ibase = sendchar;

	for(; i > 0; i--)			//8�����ط���8��
	{							
		CLK = 0;		
		Delay5Us();
		IO  = mybit0;			//һ�����巢��һ������mybit0
		CLK = 1;
		Delay5Us();
		ibase = ibase>>1;		//���´�Ҫ���͵ı���λ�Ƶ�mybit0
	}
}


/***********************************************************
�������ƣ�RstCard
��    �ܣ�ʹIC��SLE4442��λ
��	  �룺��
��	  ����0 --- ��λ�ɹ�
	      1 --- ��λʧ��,��Ϊ��Ч�������� 
************************************************************/
unsigned char RstCard(void)
{
	unsigned char i;
	unsigned char ReadBuf[4];

	IO  = 1;				//IO  �����øߵ�ƽ			
	RST = 0;				//RST �����õ͵�ƽ
	CLK = 0;				//CLK �����õ͵�ƽ

	Delay10Us();			//������һ��RST�����ڼ����һ��CLK����
	RST = 1;
	Delay5Us();
	CLK = 1;
	Delay5Us();
	CLK = 0;
	Delay5Us();
	RST = 0;
							//���ո�λ��Ӧֵ
	for(i = 0; i < 4; i++)
	{
		ReadBuf[i] = Readchar();
	}

	CLK = 1;
	Delay5Us();		
	CLK = 0;		
	IO  = 1; 				//��CLK��IOΪ��λʱ��ͼ��λ���ʱ��״̬		
	
	if ((ReadBuf[0] == IDENTIFY1) && (ReadBuf[1] == IDENTIFY2) &&
	    (ReadBuf[2] == IDENTIFY3) && (ReadBuf[3] == IDENTIFY4))
	{	
		return 0;			//��λֵ��ȷ,���ظ�λ�ɹ�
	}
	else
	{
		return 1;			//��λֵ����,���ظ�λʧ��
	}  
}


	
/************************************************************
��������SendCommand
��  �ܣ����ݲ�ͬ�Ĳ����������ַ���IC��
��  ����unsigned char command  --- �����֣�
		unsigned char Address  --- ��ַ��
		unsigned char senddata --- ����
����ֵ����
*************************************************************/
void SendCommand(unsigned char command,unsigned char Address,unsigned char senddata)
{
	IO  = 1;			/*������ʼ״̬*/
	CLK = 0;
	Delay5Us();
	CLK = 1;
	Delay10Us();
	IO = 0;
	Delay10Us();
	CLK = 0;
						/*��������*/
	SendByte(command);
	SendByte(Address);
	SendByte(senddata);
						/*����ֹͣ״̬*/
	CLK = 0;
 	IO  = 0;
	Delay5Us();
	CLK = 1;
	Delay5Us();
	IO  = 1;
	Delay5Us();
}

/****************************************************************
�������ƣ�SendClock
��    �ܣ����ʹ�������
��    �룺��
��	  ������
*****************************************************************/
void SendClock(void)
{	
	CLK=0;				//����һ������,��Ϊ����Ĺ�ʼ
	Delay10Us();
	CLK=1;
	Delay10Us();

	do
	{
		CLK=0;			
		Delay10Us();
		CLK=1;
		Delay10Us();
	}while(IO == 0);	//���ϲ�����������,����IC���ڲ�����,ֱ��IC����
}						//IO����Ϊ�ߵ�ƽ

/***************************************************************
�������ƣ�ReadCm
��    �ܣ������洢���ж������ݿ鲢����ReadBuf��
��	  �룺unsigned char StarAddr --- ��ʼ��ַ(0 - 255)
		  unsigned char ByteNum  --- Ҫ�������ֽ���(1 - 256)
		  unsigned char *RecBuf  --- �������ݻ�����
��	  ��: 0 --- ���ɹ�
		  1 --- ��ʾ��Ч�����߿���	
****************************************************************/
unsigned char ReadCm(unsigned char StarAddr,unsigned char ByteNum,unsigned char *RecBuf)
{
	unsigned char i = 0;

	if (RstCard() == 1)						/* ʹ����λ*/
		return 1;							/* �����λʧ�ܷ���1 */
		
	SendCommand(0x30,StarAddr,0x00);		/* ���Ͷ��������� */

	for(i = 0; i < ByteNum; i++)
	{
		*RecBuf = Readchar();			    /* �������ж���ByteNum���ֽڲ�����RecBuf�� */
		RecBuf++;
	}
		return 0;
}

/****************************************************************
��������: WriteCm
��    ��: �Ѵ���WriteBuf�е�ByteNum���ֽڵ����ݴ������洢����
��    ��: unsigned char StarAdr   --- ��ʼ��ַ(0 - 255)
          unsigned char ByteNum   --- Ҫд����ֽ���(1 - 256)
	      unsigned char *WriteBuf --- д�����ݻ�����	
��	  ��: 0 --- д�ɹ�
		  1 --- ��ʾ��Ч�����߿���
ע	  �⣺ҪУ����Կ��ȷ�����ܶԿ������洢��д������	
*****************************************************************/
unsigned char WriteCm(unsigned char StarAdr,unsigned char ByteNum,unsigned char *WriteBuf)
{
	unsigned char i = 0;

	if (RstCard() == 1)						    /* ʹ����λ*/
		return 1;							    /* �����λʧ�ܷ���1 */

	for(i = 0; i < ByteNum; i++)
	{
		SendCommand(0x38,StarAdr,*WriteBuf);	//����д���洢������
		SendClock();							//���ʹ�������		
		StarAdr++;								//д���ֽڵ�ַ��1
		WriteBuf++;								//д�뻺����ָ���1
	}
		return 0;
}

/******************************************************************
�������ƣ�ReadPm
��    �ܣ��������洢��,���ѱ����洢����4�ֽڵ����ݴ���RecBuf��
��	  �룺unsigned char *RecBuf  --- �������ݻ�����,����Ϊ4���ֽ�
��    ����0 --- ���ɹ�
		  1 --- ��ʾ��Ч�����߿���	
*******************************************************************/
unsigned char ReadPm(unsigned char *RecBuf)
{
	unsigned char i = 0;

	if (RstCard() == 1)					/* ʹ����λ*/
		return 1;						/* �����λʧ�ܷ���1 */

	SendCommand(0x34,0x00,0x00);		//�������洢������		

	IO = 1;								// ��IO��Ϊ����״̬
	Delay10Us();						// ��ʱһ��

	for(i = 0; i < 4; i++)				//�������洢��4���ֽ�
	{
		*RecBuf=Readchar();
		RecBuf++;						//���ջ�����ָ���1
	}

	SendClock();						//���ʹ�������	

	return 0;
}

/********************************************************************
�������ƣ�WritePm
��    �ܣ�д�������ݴ洢��
��	  �룺unsigned char StartAdr  --- ��ʼ��ַ(0 - 31)
	      unsigned char ByteNum   --- д����ֽ���(1 - 32)
	 	  unsigned char *WriteBuf --- д�����ݻ�����
��	  ����0 --- д�ɹ�
		  1 --- ��ʾ��Ч�����߿���	
ע	  ��: ����У����Կ��ȷ�����ܶԿ��Ļ��洢��д�����ݣ�
          ���д������ݱ����뿨�ж�Ӧ��������Ȳ���д��
*********************************************************************/
unsigned char WritePm(unsigned char StartAdr,unsigned char ByteNum,unsigned char *WriteBuf)
{
	unsigned char i;

	if (RstCard() == 1)							/* ʹ����λ*/
		return 1;								/* �����λʧ�ܷ���1 */

	for (i = 0; i < ByteNum; i++)
	{
		SendCommand(0x3c,StartAdr,*WriteBuf);	//д��һ���ֽ�
		SendClock();							//����д���������
		StartAdr++;								//д���ֽڵ�ַ��1
		WriteBuf++;								//д�뻺����ָ���1
	}	
		return 0;
}

/**********************************************************************
�������ƣ�ReadPsw
��    �ܣ������ܴ洢��
��	  �룺unsigned char *Psw  --- ����װ�����ļ��ܴ洢������,����Ϊ4���ֽ�
		  Psw��һ�ֽ�: 			 ���������ֵ
		  Psw�ڶ��ֽڵ������ֽ�: ��������ֵ
��	  ����0 --- ���ɹ�
		  1 --- ��ʾ��Ч�����߿���
ע	  ��: ����У��������ȷ���ܶ�����ȷ����Կֵ,�������������ֵΪ00 00 00
***********************************************************************/
unsigned char ReadPsw(unsigned char *Psw)
{
	unsigned char i = 0;

	if (RstCard() == 1)					/* ʹ����λ*/
		return 1;						/* �����λʧ�ܷ���1 */

	SendCommand(0x31,0,0);				//�����ܴ洢������

	for(i = 0; i < 4; i++)				//�����ܴ洢�����ĸ��ֽ�
	{
		*Psw = Readchar();			
		Psw++;
	}	
		return 0;
}

/*********************************************************************
�������ƣ�CheckPsw
��    �ܣ�У������,��Psw��1��2��3�ֽڵ����ݷֱ�����ܴ洢����1��2��3�ֽڱȽ�
��	  �룺unsigned char *Psw  --- ��У�������ֵ,����Ϊ3���ֽ�
��    ��: 3: �˶�����ɹ�
	      0: ���ѱ���
	   	  1: ֻʣһ��У�����,У������ʧ��
	      2: ֻʣ����У�����,У������ʧ��
		  4: ��Ϊ��Ч��������
**********************************************************************/
unsigned char CheckPsw(unsigned char *Psw)
{
	unsigned char ReadBuf[4];			
	unsigned char i = 0;

	if (ReadPsw(ReadBuf) == 1)			//�����ܴ洢��
		return 4;

	if(ReadBuf[0]==0x07)			
	{
		SendCommand(0x39,0,0x03);		//��ECдΪ0x03
		SendClock();						//���ʹ�������
	}
	else if(ReadBuf[0]==0x06 || ReadBuf[0]==0x05 || ReadBuf[0]==0x03)
	{
		SendCommand(0x39,0,0x01);		//��ECдΪ0x01
		SendClock();						//���ʹ�������
	}
	else if(ReadBuf[0]==0x01 || ReadBuf[0]==0x02 || ReadBuf[0]==0x04)
	{
		SendCommand(0x39,0,0x00);		//��ECдΪ0x00
		SendClock();						//���ʹ�������
	}
			
	SendCommand(0x33,1,Psw[0]);			//У������ĵ�һ���ֽ�
	SendClock();							
	SendCommand(0x33,2,Psw[1]);			//У������ĵڶ����ֽ�
	SendClock();
	SendCommand(0x33,3,Psw[2]);			//У������ĵ������ֽ�
	SendClock();
	
	SendCommand(0x39,0,0x07);			//�������������
	SendClock();

	SendCommand(0x31,0,0);				//�����ܴ洢������	

	for(i = 0;i < 4;i++)
	{
		ReadBuf[i]=Readchar();			//�����ܴ洢�����ĸ��ֽ�
	}
	
	if(ReadBuf[0] == 0x07) return 3;	//ʣ��3��У�����,У������ɹ�
	else if(ReadBuf[0] == 0x06 || ReadBuf[0] == 0x05 || ReadBuf[0] == 0x03) return 2;
										//ʣ��2��У�����,У������ʧ��
	else if(ReadBuf[0] == 0x04 || ReadBuf[0] == 0x02 || ReadBuf[0] == 0x01) return 1;
										//ʣ��1��У�����,У������ʧ��		
	else return 0;						//ʣ��0��У�����,������
}

/**********************************************************************
�������ƣ�SetPsw
��    �ܣ��޸ļ��ܴ洢���е�����
��	  �룺NewPsw -- �����뻺����,����Ϊ3���ֽ�
��	  ����0 --- ���ɹ�
		  1 --- ��ʾ��Ч�����߿���
ע	  ��: ����У������ɹ�������޸�����, ��������д��������
***********************************************************************/
unsigned char SetPsw(unsigned char *NewPsw)
{
	unsigned char i;

	if (RstCard() == 1)							/* ʹ����λ*/
		return 1;								/* �����λʧ�ܷ���1 */

	for (i = 0; i < 3; i++)
	{
		SendCommand(0x39,i + 1,*NewPsw);		//�����µ�����ֵ
		SendClock();							//���ʹ�������
		NewPsw++;								//����ֵ������ָ���1
	}	
		return 0;
}


