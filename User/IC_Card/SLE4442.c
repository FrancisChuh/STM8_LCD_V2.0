
#include <reg52.h>
#include "SLE4442.h"
#include <intrins.h>

/* 延时5个us宏定义 */
#define Delay5Us()    _nop_();_nop_();_nop_();_nop_();_nop_()

/* 延时10个us宏定义 */
#define Delay10Us()   _nop_();_nop_();_nop_();_nop_();_nop_();\
					  _nop_();_nop_();_nop_();_nop_();_nop_()

unsigned char bdata ibase;		//定义位寻址单元,用于发送与接收
								//一个字节
sbit mybit0 = ibase^0;
sbit mybit1 = ibase^1;
sbit mybit2 = ibase^2;
sbit mybit3 = ibase^3;
sbit mybit4 = ibase^4;
sbit mybit5 = ibase^5;
sbit mybit6 = ibase^6;
sbit mybit7 = ibase^7;

/***************************************************************
函数名称：Readchar
功	  能：读一个字节
输	  入: 无
输	  出：所得的字节的值 
****************************************************************/
unsigned char Readchar(void)
{
	CLK = 0; Delay5Us(); mybit0 = IO; CLK = 1; Delay5Us();	//一个脉冲接收1 bit
	CLK = 0; Delay5Us(); mybit1 = IO; CLK = 1; Delay5Us();	//一个脉冲接收1 bit
	CLK = 0; Delay5Us(); mybit2 = IO; CLK = 1; Delay5Us();	//一个脉冲接收1 bit
	CLK = 0; Delay5Us(); mybit3 = IO; CLK = 1; Delay5Us();	//一个脉冲接收1 bit
	CLK = 0; Delay5Us(); mybit4 = IO; CLK = 1; Delay5Us();	//一个脉冲接收1 bit
	CLK = 0; Delay5Us(); mybit5 = IO; CLK = 1; Delay5Us();	//一个脉冲接收1 bit
	CLK = 0; Delay5Us(); mybit6 = IO; CLK = 1; Delay5Us();	//一个脉冲接收1 bit
	CLK = 0; Delay5Us(); mybit7 = IO; CLK = 1; Delay5Us();	//一个脉冲接收1 bit
	
	return(ibase);		//返回读得的一个字节
}

/************************************************************
函数名称：SendByte
功    能：把一个字节的数据由低到高位依次发送出去
输	  入：unsigned char sendchar --- 要发送的字节
输	  出；无
*************************************************************/
void SendByte(unsigned char sendchar)
{	
	unsigned char i = 8;
	ibase = sendchar;

	for(; i > 0; i--)			//8个比特发送8次
	{							
		CLK = 0;		
		Delay5Us();
		IO  = mybit0;			//一个脉冲发送一个比特mybit0
		CLK = 1;
		Delay5Us();
		ibase = ibase>>1;		//将下次要发送的比特位移到mybit0
	}
}


/***********************************************************
函数名称：RstCard
功    能：使IC卡SLE4442复位
输	  入：无
输	  出：0 --- 复位成功
	      1 --- 复位失败,卡为无效卡或卡已损坏 
************************************************************/
unsigned char RstCard(void)
{
	unsigned char i;
	unsigned char ReadBuf[4];

	IO  = 1;				//IO  引脚置高电平			
	RST = 0;				//RST 引脚置低电平
	CLK = 0;				//CLK 引脚置低电平

	Delay10Us();			//下面在一个RST脉冲期间产生一个CLK脉冲
	RST = 1;
	Delay5Us();
	CLK = 1;
	Delay5Us();
	CLK = 0;
	Delay5Us();
	RST = 0;
							//接收复位响应值
	for(i = 0; i < 4; i++)
	{
		ReadBuf[i] = Readchar();
	}

	CLK = 1;
	Delay5Us();		
	CLK = 0;		
	IO  = 1; 				//置CLK和IO为复位时序图复位完成时的状态		
	
	if ((ReadBuf[0] == IDENTIFY1) && (ReadBuf[1] == IDENTIFY2) &&
	    (ReadBuf[2] == IDENTIFY3) && (ReadBuf[3] == IDENTIFY4))
	{	
		return 0;			//复位值正确,返回复位成功
	}
	else
	{
		return 1;			//复位值错误,返回复位失败
	}  
}


	
/************************************************************
函数名：SendCommand
功  能：根据不同的参数把命令字发给IC卡
参  数：unsigned char command  --- 命令字；
		unsigned char Address  --- 地址；
		unsigned char senddata --- 数据
返回值：无
*************************************************************/
void SendCommand(unsigned char command,unsigned char Address,unsigned char senddata)
{
	IO  = 1;			/*产生开始状态*/
	CLK = 0;
	Delay5Us();
	CLK = 1;
	Delay10Us();
	IO = 0;
	Delay10Us();
	CLK = 0;
						/*发送命令*/
	SendByte(command);
	SendByte(Address);
	SendByte(senddata);
						/*产生停止状态*/
	CLK = 0;
 	IO  = 0;
	Delay5Us();
	CLK = 1;
	Delay5Us();
	IO  = 1;
	Delay5Us();
}

/****************************************************************
函数名称：SendClock
功    能：发送处理脉冲
输    入：无
输	  出：无
*****************************************************************/
void SendClock(void)
{	
	CLK=0;				//产生一个脉冲,做为处理的工始
	Delay10Us();
	CLK=1;
	Delay10Us();

	do
	{
		CLK=0;			
		Delay10Us();
		CLK=1;
		Delay10Us();
	}while(IO == 0);	//不断产生处理脉冲,驱动IC卡内部处理,直到IC卡将
}						//IO口拉为高电平

/***************************************************************
函数名称：ReadCm
功    能：从主存储器中读出数据块并存入ReadBuf中
输	  入：unsigned char StarAddr --- 开始地址(0 - 255)
		  unsigned char ByteNum  --- 要读出的字节数(1 - 256)
		  unsigned char *RecBuf  --- 接收数据缓冲区
输	  出: 0 --- 读成功
		  1 --- 表示无效卡或者卡损坏	
****************************************************************/
unsigned char ReadCm(unsigned char StarAddr,unsigned char ByteNum,unsigned char *RecBuf)
{
	unsigned char i = 0;

	if (RstCard() == 1)						/* 使卡复位*/
		return 1;							/* 如果复位失败返回1 */
		
	SendCommand(0x30,StarAddr,0x00);		/* 发送读主存命令 */

	for(i = 0; i < ByteNum; i++)
	{
		*RecBuf = Readchar();			    /* 从主存中读出ByteNum个字节并存入RecBuf中 */
		RecBuf++;
	}
		return 0;
}

/****************************************************************
函数名称: WriteCm
功    能: 把存在WriteBuf中的ByteNum个字节的数据存入主存储器中
输    入: unsigned char StarAdr   --- 开始地址(0 - 255)
          unsigned char ByteNum   --- 要写入的字节数(1 - 256)
	      unsigned char *WriteBuf --- 写入数据缓冲区	
输	  出: 0 --- 写成功
		  1 --- 表示无效卡或者卡损坏
注	  意：要校验密钥正确，才能对卡的主存储器写入数据	
*****************************************************************/
unsigned char WriteCm(unsigned char StarAdr,unsigned char ByteNum,unsigned char *WriteBuf)
{
	unsigned char i = 0;

	if (RstCard() == 1)						    /* 使卡复位*/
		return 1;							    /* 如果复位失败返回1 */

	for(i = 0; i < ByteNum; i++)
	{
		SendCommand(0x38,StarAdr,*WriteBuf);	//发送写主存储区命令
		SendClock();							//发送处理脉冲		
		StarAdr++;								//写入字节地址加1
		WriteBuf++;								//写入缓冲区指针加1
	}
		return 0;
}

/******************************************************************
函数名称：ReadPm
功    能：读保护存储器,并把保护存储器的4字节的内容存在RecBuf中
输	  入：unsigned char *RecBuf  --- 接收数据缓冲区,长度为4个字节
输    出：0 --- 读成功
		  1 --- 表示无效卡或者卡损坏	
*******************************************************************/
unsigned char ReadPm(unsigned char *RecBuf)
{
	unsigned char i = 0;

	if (RstCard() == 1)					/* 使卡复位*/
		return 1;						/* 如果复位失败返回1 */

	SendCommand(0x34,0x00,0x00);		//读保护存储器命令		

	IO = 1;								// 置IO口为输入状态
	Delay10Us();						// 延时一下

	for(i = 0; i < 4; i++)				//读保护存储器4个字节
	{
		*RecBuf=Readchar();
		RecBuf++;						//接收缓冲区指针加1
	}

	SendClock();						//发送处理脉冲	

	return 0;
}

/********************************************************************
函数名称：WritePm
功    能：写保护数据存储器
输	  入：unsigned char StartAdr  --- 起始地址(0 - 31)
	      unsigned char ByteNum   --- 写入的字节数(1 - 32)
	 	  unsigned char *WriteBuf --- 写入数据缓冲区
输	  出：0 --- 写成功
		  1 --- 表示无效卡或者卡损坏	
注	  意: 首先校验密钥正确，才能对卡的护存储器写入数据，
          其次写入的数据必须与卡中对应的数据相等才能写入
*********************************************************************/
unsigned char WritePm(unsigned char StartAdr,unsigned char ByteNum,unsigned char *WriteBuf)
{
	unsigned char i;

	if (RstCard() == 1)							/* 使卡复位*/
		return 1;								/* 如果复位失败返回1 */

	for (i = 0; i < ByteNum; i++)
	{
		SendCommand(0x3c,StartAdr,*WriteBuf);	//写入一个字节
		SendClock();							//发送写命令处理脉冲
		StartAdr++;								//写入字节地址加1
		WriteBuf++;								//写入缓冲区指针加1
	}	
		return 0;
}

/**********************************************************************
函数名称：ReadPsw
功    能：读加密存储器
输	  入：unsigned char *Psw  --- 用于装读到的加密存储器内容,长度为4个字节
		  Psw第一字节: 			 错误计数器值
		  Psw第二字节到第四字节: 卡的密码值
输	  出：0 --- 读成功
		  1 --- 表示无效卡或者卡损坏
注	  意: 必须校验密码正确才能读到正确的密钥值,否则读到的密码值为00 00 00
***********************************************************************/
unsigned char ReadPsw(unsigned char *Psw)
{
	unsigned char i = 0;

	if (RstCard() == 1)					/* 使卡复位*/
		return 1;						/* 如果复位失败返回1 */

	SendCommand(0x31,0,0);				//读加密存储器命令

	for(i = 0; i < 4; i++)				//读加密存储器的四个字节
	{
		*Psw = Readchar();			
		Psw++;
	}	
		return 0;
}

/*********************************************************************
函数名称：CheckPsw
功    能：校验密码,把Psw中1，2，3字节的内容分别与加密存储器的1，2，3字节比较
输	  入：unsigned char *Psw  --- 待校验的密码值,长度为3个字节
输    出: 3: 核对密码成功
	      0: 卡已报废
	   	  1: 只剩一次校验机会,校验密码失败
	      2: 只剩二次校验机会,校验密码失败
		  4: 卡为无效卡或已损坏
**********************************************************************/
unsigned char CheckPsw(unsigned char *Psw)
{
	unsigned char ReadBuf[4];			
	unsigned char i = 0;

	if (ReadPsw(ReadBuf) == 1)			//读加密存储器
		return 4;

	if(ReadBuf[0]==0x07)			
	{
		SendCommand(0x39,0,0x03);		//将EC写为0x03
		SendClock();						//发送处理脉冲
	}
	else if(ReadBuf[0]==0x06 || ReadBuf[0]==0x05 || ReadBuf[0]==0x03)
	{
		SendCommand(0x39,0,0x01);		//将EC写为0x01
		SendClock();						//发送处理脉冲
	}
	else if(ReadBuf[0]==0x01 || ReadBuf[0]==0x02 || ReadBuf[0]==0x04)
	{
		SendCommand(0x39,0,0x00);		//将EC写为0x00
		SendClock();						//发送处理脉冲
	}
			
	SendCommand(0x33,1,Psw[0]);			//校验密码的第一个字节
	SendClock();							
	SendCommand(0x33,2,Psw[1]);			//校验密码的第二个字节
	SendClock();
	SendCommand(0x33,3,Psw[2]);			//校验密码的第三个字节
	SendClock();
	
	SendCommand(0x39,0,0x07);			//擦除错误计数器
	SendClock();

	SendCommand(0x31,0,0);				//读加密存储器命令	

	for(i = 0;i < 4;i++)
	{
		ReadBuf[i]=Readchar();			//读加密存储器的四个字节
	}
	
	if(ReadBuf[0] == 0x07) return 3;	//剩下3次校验机会,校验密码成功
	else if(ReadBuf[0] == 0x06 || ReadBuf[0] == 0x05 || ReadBuf[0] == 0x03) return 2;
										//剩下2次校验机会,校验密码失败
	else if(ReadBuf[0] == 0x04 || ReadBuf[0] == 0x02 || ReadBuf[0] == 0x01) return 1;
										//剩下1次校验机会,校验密码失败		
	else return 0;						//剩下0次校验机会,卡报废
}

/**********************************************************************
函数名称：SetPsw
功    能：修改加密存储器中的密码
输	  入：NewPsw -- 新密码缓冲区,长度为3个字节
输	  出：0 --- 读成功
		  1 --- 表示无效卡或者卡损坏
注	  意: 必须校验密码成功后才能修改密码, 否则密码写不进卡中
***********************************************************************/
unsigned char SetPsw(unsigned char *NewPsw)
{
	unsigned char i;

	if (RstCard() == 1)							/* 使卡复位*/
		return 1;								/* 如果复位失败返回1 */

	for (i = 0; i < 3; i++)
	{
		SendCommand(0x39,i + 1,*NewPsw);		//发送新的密码值
		SendClock();							//发送处理脉冲
		NewPsw++;								//密码值缓冲区指针加1
	}	
		return 0;
}


