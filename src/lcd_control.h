#ifndef __LCD_CONTROLLER_H__
#define __LCD_CONTROLLER_H__

#define Set_Cs GPIOC->BSRR = GPIO_Pin_8;
#define Clr_Cs GPIOC->BRR = GPIO_Pin_8;

#define Set_Rs GPIOC->BSRR = GPIO_Pin_9;
#define Clr_Rs GPIOC->BRR = GPIO_Pin_9;

#define Set_nWr GPIOC->BSRR = GPIO_Pin_10;
#define Clr_nWr GPIOC->BRR = GPIO_Pin_10;

#define Set_nRd GPIOC->BSRR = GPIO_Pin_11;
#define Clr_nRd GPIOC->BRR = GPIO_Pin_11;

#define Set_Rst GPIOC->BSRR = GPIO_Pin_12;
#define Clr_Rst GPIOC->BRR = GPIO_Pin_12;

#define LCD_Light_On GPIOC->BSRR = GPIO_Pin_13;
#define LCD_Light_Off GPIOC->BRR = GPIO_Pin_13;

/* LCD colors */
#define LCD_White				0xFFFF
#define LCD_Black				0x0000
#define LCD_Blue				0x001F
#define LCD_Red					0xF800
#define LCD_Green				0x07E0
#define LCD_Cyan				0x07FF

#define LCD_NCS_GPIO_PORT GPIOC
#define LCD_NCS_PIN GPIO_Pin_8

typedef enum {
	LCD_PORTRAIT_TOP_DOWN,
	LCD_PORTRAIT_BOTTOM_UP,
	LCD_LANDSCAPE_TOP_DOWN;
	LCD_LANDSCAPE_BOTTOM_UP;
} LCD_OrientationMode_t;

#define LCD_WIDTH_HW		240
#define LCD_HEIGHT_HW		320

#define LCD_PORTRAIT		0
#define LCD_LANDSCAPE		1
#define LCD_ORIENTATION	LCD_LANDSCAPE

#if LCD_ORIENTATION == LCD_PORTRAIT
	#define LCD_WIDTH			240
	#define LCD_HEIGHT		320
	#define LCD_CHARS_PER_LINE	10
	#define LCD_CHAR_LINES	13
	#define LCD_ENTRY_MODE_DEFAULT 0x1030
	#define LCD_ORIENTATION_DEFAULT LCD_PORTRAIT_TOP_DOWN
#else
	#define LCD_WIDTH			320
	#define LCD_HEIGHT		240
	#define LCD_CHARS_PER_LINE	15
	#define LCD_CHAR_LINES		10
	#define LCD_ENTRY_MODE_DEFAULT 0x1018
	#define LCD_ORIENTATION_DEFAULT LCD_LANDSCAPE_TOP_DOWN
#endif

#define LCD_LINE_HORIZONTAL	0x00
#define LCD_LINE_VERTICAL		0x01

/* exported functions */
void LCD_Configuration(void);
void LCD_Initialization(void);
void LCD_Reset(void);
void LCD_WriteRegister(u16 index,u16 data);
void LCD_SetCursor(u16 x,u16 y);
void LCD_SetWindow(u16 Startx,u16 Starty,u16 Endx,u16 Endy);
void LCD_DrawPicture(u16 Startx,u16 Starty,u16 Endx,u16 Endy,u16 *pic);
void LCD_SetPoint(u16 x,u16 y,u16 Color);
void LCD_Clear(u16 Color);
void LCD_Delay(u32 nCount);
void LCD_Test(void);
void LCD_WriteData(u16 data);
void LCD_WriteIndex(u16 idx);
void LCD_Backlight(bool status);

u16 LCD_BGR2RGB(u16 color);
u16 LCD_ReadData(void);
u16 LCD_ReadRegister(u16 index);

static __INLINE uint16_t LCD_RGB2Pixel565(uint8_t r,uint8_t g,uint8_t b)
{
	/* RGB2PIXEL565 from a macro in Greg Haerr's Nano-X, MPL license */
	return ((((r) & 0xf8) << 8) | (((g) & 0xfc) << 3) | (((b) & 0xf8) >> 3 ));
}

void LCD_SetOrientation(LCD_OrientationMode_t m);
LCD_OrientationMode_t LCD_GetOrientation(void);
uint16_t LCD_GetWidth(void);
uint16_t LCD_GetHeight(void);

#endif // __LCD_CONTROLLER_H__
