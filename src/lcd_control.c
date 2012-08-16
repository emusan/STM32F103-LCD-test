/*
 * This is a series of functions to communicate between an ILI9320 LCD 
 * controller and an STM32F1xx series ARM microcontroller. The required 
 * pinout can be found in the pinout.txt file at the root of the project.
 *
 * This code borrows a lot from other similar libraries, I hope it helps 
 * you as much as they have helped me.
 */

#include "stm32f1x.h"

u16 DeviceCode;

void LCD_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	// Open the clock we want
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC,ENABLE);

	// Configure the LCD pins for push-pull output
	// This is just the lower 8 bits of data
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB,&GPIO_InitStructure);

	// Now for the high 8 bits
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_Init(GPIOC,&GPIO_InitStructure);

	// Control pins
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12;
	GPIO_Init(GPIOC,&GPIO_InitStructure);

	// Backlight control
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	LCD_Light_On;
}

/*
 * Name: void LCD_Initialization()
 * Function: initialize ILI9320 controller(may work with 9325 and 9328, untested)
 * Input: none
 * Output: none
 * Note:
 * Call the method: LCD_Initialization();
 */
void LCD_Initialization()
{
	u16 i;

	// Set all bits
	LCD_WriteData(0xffff);
	// Set various pins
	Set_Rst;
	Set_nWr;
	Set_Cs;
	Set_Rs;
	Set_nRd;
	Set_Rst;
	LCD_Reset();	// reset LCD

	// Wait a bit
	for (i = 50000;i > 0;i--);
	for (i = 50000;i > 0;i--);
	for (i = 50000;i > 0;i--);
	LCD_WriteRegister(0x0000,0x0001);
	LCD_Delay(10000);
	for (i = 50000;i > 0;i--);
	for (i = 50000;i > 0;i--);
	LCD_DeviceCode = LCD_ReadRegister(0x0000);
	if (LCD_DeviceCode==0x9325 || LCD_Device_code == 0x9328)
	{
		LCD_WriteRegister(0x00e7,0x0010);
		LCD_WriteRegister(0x0000,0x0001);			// Starts internal oscillator
		LCD_WriteRegister(0x0001,0x0100);
		LCD_WriteRegister(0x0002,0x0700);			// Power on
		LCD_WriteRegister(0x0003,(1 << 12) | (1 << 5) | (1 << 4));		// 65K
		LCD_WriteRegister(0x0004,0x0000);
		LCD_WriteRegister(0x0008,0x0207);
		LCD_WriteRegister(0x0009,0x0000);
		LCD_WriteRegister(0x000a,0x0000);			// Display setting
		LCD_WriteRegister(0x000c,0x0001);
		LCD_WriteRegister(0x000d,0x0000);
		LCD_WriteRegister(0x000f,0x0000);

		// Power on sequence
		LCD_WriteRegister(0x0010,0x0000);
		LCD_WriteRegister(0x0011,0x0007);
		LCD_WriteRegister(0x0012,0x0000);
		LCD_WriteRegister(0x0013,0x0000); 
		for (i = 50000;i > 0;i--);
		for (i = 50000;i > 0;i--);
		LCD_WriteRegister(0x0010,0x1590);
		LCD_WriteRegister(0x0011,0x0227);
		for (i = 50000;i > 0;i--);
		for (i = 50000;i > 0;i--);
		LCD_WriteRegister(0x0012,0x009c);
		for (i = 50000;i > 0;i--);
		for (i = 50000;i > 0;i--);
		LCD_WriteRegister(0x0013,0x1900);
		LCD_WriteRegister(0x0029,0x0023);
		LCD_WriteRegister(0x002b,0x000e);
		for (i = 50000;i > 0;i--);
		for (i = 50000;i > 0;i--);
		LCD_WriteRegister(0x0020,0x0000);
		LCD_WriteRegister(0x0021,0x0000);
		for (i = 50000;i > 0;i--);
		for (i = 50000;i > 0;i--);
		LCD_WriteRegister(0x0030,0x0007);
		LCD_WriteRegister(0x0031,0x0707);
		LCD_WriteRegister(0x0032,0x0006);
		LCD_WriteRegister(0x0035,0x0704);
		LCD_WriteRegister(0x0036,0x1f04);
		LCD_WriteRegister(0x0037,0x0004);
		LCD_WriteRegister(0x0038,0x0000);
		LCD_WriteRegister(0x0039,0x0706);
		LCD_WriteRegister(0x003c,0x0701);
		LCD_WriteRegister(0x003d,0x000f);
		for (i = 50000;i > 0;i--);
		for (i = 50000;i > 0;i--);
		LCD_WriteRegister(0x0050,0x0000);
		LCD_WriteRegister(0x0051,0x00ef);
		LCD_WriteRegister(0x0052,0x0000);
		LCD_WriteRegister(0x0053,0x013f);
		LCD_WriteRegister(0x0060,0xa700);
		LCD_WriteRegister(0x0061,0x0001);
		LCD_WriteRegister(0x006a,0x0000);
		LCD_WriteRegister(0x0080,0x0000);
		LCD_WriteRegister(0x0081,0x0000);
		LCD_WriteRegister(0x0082,0x0000);
		LCD_WriteRegister(0x0083,0x0000);
		LCD_WriteRegister(0x0084,0x0000);
		LCD_WriteRegister(0x0085,0x0000);
		LCD_WriteRegister(0x0090,0x0010);
		LCD_WriteRegister(0x0092,0x0000);
		LCD_WriteRegister(0x0093,0x0003);
		LCD_WriteRegister(0x0095,0x0110);
		LCD_WriteRegister(0x0097,0x0000);
		LCD_WriteRegister(0x0098,0x0000);

		// Display on sequence
		LCD_WriteRegister(0x0007,0x0133);
		LCD_WriteRegister(0x0020,0x0000);
		LCD_WriteRegister(0x0021,0x0000);
	}
	else if (LCD_DeviceCode == 0x9320)
	{
		LCD_WriteRegister(0x00,0x0000);		// Start Oscillation
		LCD_WriteRegister(0x01,0x0100);		// Driver output control (makes it scan top left to bottom right, odd for top half, even for bottom)
		LCD_WriteRegister(0x02,0x0700);		// Line inversion on the LCD Driving Wave Control
		LCD_WriteRegister(0x03,0x1018);		// Entry mode set(may need changing
		LCD_WriteRegister(0x04,0x0000);		// Resizing stuff(not needed by me)
		LCD_WriteRegister(0x08,0x0202);		// (Display control 2) Set 2 lines for for both front and back porch(minimum number, helps VSYNC)
		LCD_WriteRegister(0x09,0x0000);		// (Display control 3) Sets 0 frame scan cycle(not needed for this communication) and normal scan
		LCD_WriteRegister(0x0a,0x0000);		// Not necessary(FMARK signal stuff)
		LCD_WriteRegister(0x0c,0x0001);		// 16-bit RGB interface(1 transfer/pixel), using internal system clock and system interface
		LCD_WriteRegister(0x0d,0x0000);		// Frame Marker at position 0(starts outputting frame right away
		LCD_WriteRegister(0x0f,0x0000);		// Data input on rising edge of DOTCLK, data written when ENABLE=0,HSPL/VSPL(H/VSYNC pins) Low polarit = active

		for (i = 50000;i > 0;i--);
		for (i = 50000;i > 0;i--);
		LCD_WriteRegister(0x07,0x0101);		// (Display control 1) Set display to operate, VCOM output to GND
		for (i = 50000;i > 0;i--);
		for (i = 50000;i > 0;i--);

		LCD_WriteRegister(0x10,0x10c0);		// (Power control 1) Enable power supply
		LCD_WriteRegister(0x11,0x0007);		// (Power control 2) Ref. voltage(VciOUT) = Vci1, operating frequency = Fosc in circuit 1 and Fosc/16 in circuit 2
		LCD_WriteRegister(0x12,0x0110);		// (Power control 3) Enable VGL output, use internal electric volume(VCM) to set VcomH(Vcom center voltage level
		LCD_WriteRegister(0x13,0x0a00);		// (Power control 4) VCOM Amplitude = VREG1OUT x 0.90
		LCD_WriteRegister(0x29,0x0000);		// (Power control 7) VcomH voltage = VREG1OUT x .69

		LCD_WriteRegister(0x2b,0x0008);		// 90Hz frame rate, internal resistor. (maybe should be 0x0408)

		// Horiz. and Vert. RAM Address Position. Set up for 320x240
		LCD_WriteRegister(0x50,0);			// X starts at 0
		LCD_WriteRegister(0x51,239);		// X ends at 239
		LCD_WriteRegister(0x52,0);			// Y starts at 0
		LCD_WriteRegister(0x53,319);		// Y ends at 319

		LCD_WriteRegister(0x60,0x2700);		// (Driver output control) Gate scans at 0, ends after 320 lines
		LCD_WriteRegister(0x61,0x0001);		// (Driver output control) grayscale inversion
		LCD_WriteRegister(0x62,0x0000);		// (Vertical scroll control) not used

		LCD_WriteRegister(0x80,0x0000);		// Display position for partial image 1
		LCD_WriteRegister(0x81,0x0000);		// RAM address for start of partial image 1
		LCD_WriteRegister(0x82,0x0000);		// RAM address for end of partial image 1
		LCD_WriteRegister(0x83,0x0000);		// Display position for partial image 2
		LCD_WriteRegister(0x84,0x0000);		// RAM address for start of partial image 2
		LCD_WriteRegister(0x85,0x0000);		// RAM address for end of partial image 2

		LCD_WriteRegister(0x90,0x0010);		// (Panel interface control 1) Sets clock number for internal clock
		LCD_WriteRegister(0x92,0x0000);		// (Panel interface control 2) 0 Clocks of overlap when synced
		LCD_WriteRegister(0x93,0x0001);		// (Panel interface control 3) 1 Clock output position when synced
		LCD_WriteRegister(0x95,0x0110);		// (Panel interface control 4) Division ration of 1/4, 16 clocks per horizontal line
		LCD_WriteRegister(0x97,0x0000);		// (Panel interface control 5) 0 Clock non-overlap
		LCD_WriteRegister(0x98,0x0000);		// (Panel interface control 6) Source output position 0 clocks

		LCD_WriteRegister(0x07,0x0133);		// (Display control 1) Set display to operate, base image display, normal display (maybe should be 0x0173)
	}
	for (i = 50000;i > 0;i--);
	LCD_Clear(LCD_Red);
}
