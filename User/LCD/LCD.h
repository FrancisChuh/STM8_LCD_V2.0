#include "include.h"

#define   PRICE   		10
#define   SY         		11
#define   USED   		12
#define   BUY       	        13
#define   Valve_OFF             14
#define   Valve_ON              15
#define   BATTERY               16
#define   READ_IC               17
#define   M3                    18
#define   YUAN                  19
#define   CHARGE                20
#define   BAD                   21


#define   X1   (LCD->RAM[LCD_RAMRegister_10] )		//价格
#define   X2	(LCD->RAM[LCD_RAMRegister_7] )		//剩余
#define   X3   (LCD->RAM[LCD_RAMRegister_3] )		//用量
#define   X4   (LCD->RAM[LCD_RAMRegister_0] )		//购入


#define A1      (LCD->RAM[LCD_RAMRegister_10])
#define	B1      (LCD->RAM[LCD_RAMRegister_7])
#define	C1      (LCD->RAM[LCD_RAMRegister_3])
#define	D1      (LCD->RAM[LCD_RAMRegister_0])
#define	E1      (LCD->RAM[LCD_RAMRegister_0])      
#define	F1      (LCD->RAM[LCD_RAMRegister_7])        
#define	G1      (LCD->RAM[LCD_RAMRegister_3])       
#define   X5   (LCD->RAM[LCD_RAMRegister_10] )		//阀关

#define	A2      (LCD->RAM[LCD_RAMRegister_10] )        
#define	B2      (LCD->RAM[LCD_RAMRegister_7] )        
#define	C2      (LCD->RAM[LCD_RAMRegister_3] )       
#define	D2      (LCD->RAM[LCD_RAMRegister_0])        
#define	E2      (LCD->RAM[LCD_RAMRegister_0] )        
#define	F2	   (LCD->RAM[LCD_RAMRegister_7] )
#define	G2	   (LCD->RAM[LCD_RAMRegister_4] )
#define   X6   (LCD->RAM[LCD_RAMRegister_11] )		//阀开


#define	A3	(LCD->RAM[LCD_RAMRegister_11] )
#define	B3	(LCD->RAM[LCD_RAMRegister_7] )
#define	C3	(LCD->RAM[LCD_RAMRegister_4])       
#define	D3	(LCD->RAM[LCD_RAMRegister_0] )
#define	E3	(LCD->RAM[LCD_RAMRegister_0] )
#define	F3	(LCD->RAM[LCD_RAMRegister_7])
#define	G3	(LCD->RAM[LCD_RAMRegister_4] )
#define   X7   (LCD->RAM[LCD_RAMRegister_11] )		//换电池


#define	A4	(LCD->RAM[LCD_RAMRegister_11] )
#define	B4	(LCD->RAM[LCD_RAMRegister_7] )
#define	C4	(LCD->RAM[LCD_RAMRegister_4] )
#define	D4	(LCD->RAM[LCD_RAMRegister_0] )       
#define	E4	(LCD->RAM[LCD_RAMRegister_1] )
#define	F4	(LCD->RAM[LCD_RAMRegister_8] )
#define	G4	(LCD->RAM[LCD_RAMRegister_4] )
#define   X8   (LCD->RAM[LCD_RAMRegister_11] )		//读卡


#define	A5	(LCD->RAM[LCD_RAMRegister_11] )
#define	B5	(LCD->RAM[LCD_RAMRegister_8] )
#define	C5	(LCD->RAM[LCD_RAMRegister_4] )
#define	D5	(LCD->RAM[LCD_RAMRegister_1] )
#define	E5	(LCD->RAM[LCD_RAMRegister_1] )      
#define	F5	(LCD->RAM[LCD_RAMRegister_8] )
#define	G5	(LCD->RAM[LCD_RAMRegister_4] )

#define	A6	(LCD->RAM[LCD_RAMRegister_11] )
#define	B6	(LCD->RAM[LCD_RAMRegister_8] )
#define	C6	(LCD->RAM[LCD_RAMRegister_4] )
#define	D6	(LCD->RAM[LCD_RAMRegister_1] )
#define	E6	(LCD->RAM[LCD_RAMRegister_1] )
#define	F6	(LCD->RAM[LCD_RAMRegister_8] )       
#define	G6	(LCD->RAM[LCD_RAMRegister_5] )

#define	A7	(LCD->RAM[LCD_RAMRegister_12] )
#define	B7	(LCD->RAM[LCD_RAMRegister_8] )
#define	C7	(LCD->RAM[LCD_RAMRegister_5] )
#define	D7	(LCD->RAM[LCD_RAMRegister_1] )
#define	E7	(LCD->RAM[LCD_RAMRegister_1] )
#define	F7	(LCD->RAM[LCD_RAMRegister_8] )       
#define	G7	(LCD->RAM[LCD_RAMRegister_5] )
#define	Point4	(LCD->RAM[LCD_RAMRegister_12] )		//P2


#define	A8	(LCD->RAM[LCD_RAMRegister_12] )
#define	B8	(LCD->RAM[LCD_RAMRegister_8] )
#define	C8	(LCD->RAM[LCD_RAMRegister_5] )
#define	D8	(LCD->RAM[LCD_RAMRegister_1] )
#define	E8	(LCD->RAM[LCD_RAMRegister_2] )
#define	F8	(LCD->RAM[LCD_RAMRegister_9] )       
#define	G8	(LCD->RAM[LCD_RAMRegister_5] )
#define	Point5	(LCD->RAM[LCD_RAMRegister_12] )       //P1


#define	X9	(LCD->RAM[LCD_RAMRegister_12])			//M3
#define	X11	(LCD->RAM[LCD_RAMRegister_9])			//元
#define	X10	(LCD->RAM[LCD_RAMRegister_5])			//请缴费
#define	X12	(LCD->RAM[LCD_RAMRegister_2])			//异常


void LCD_GLASS_Init(void);
void LCD_Display_All(void);
void displayNumber(unsigned char Position, unsigned char Number);
void LCD_GLASS_Clear(void);
void display_TEST(void);
void display_Good(void);
void display_Error(void);
