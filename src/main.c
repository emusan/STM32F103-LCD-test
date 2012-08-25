/*
 * A quick test program to test the LCD on the dev board mentioned in 
 * the readme. Also blinks an LED and does some floating point calcs for 
 * fun and testing :D.
 * 
 * If this helps you do something cool let me know!
 */

#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "lcd_control.h"

int main(int argc, char *argv[])
{
	LCD_Configuration();
	LCD_Initialization();
	GPIO_InitTypeDef GPIO_InitStructure;
	u32 delay;

	/* GPIOA Periph clock enable */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

	/* Configure PC12 to mode: slow rise-time, pushpull output */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;//GPIO No. 0
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;;//slow rise time
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;// push-pull output
	GPIO_Init(GPIOA,&GPIO_InitStructure);//GPIOA init

	//LCD_Test();

	while(1)
	{
		LCD_Clear(LCD_Blue);
		/* make some float calculations */
		float x = 42,y = 23,z = 7;
		int i = 0;
		for (i = 0;i<6;i++)
		{
			z = (x*y)/z;
		};

		/* GPIO PA0 set, pin=high,LED2 off */
		GPIOA->BSRR = GPIO_BSRR_BS2;
		//GPIO_WriteBit(GPIOA,GPIO_Pin_1,Bit_SET);

		/*delay ->> compiler optimizer settings must be "-O0" */
		delay = 500000;
		while(delay)
		{
			delay--;
		}

		/* GPIO PA0 reset pin=low, LED2 on */
		GPIOA->BSRR = GPIO_BSRR_BR2;
		//GPIO_WriteBit(GPIOA,GPIO_Pin_1,Bit_RESET);

		/* delay --> blah */
		delay = 500000;
		while(delay)
		{
			delay--;
		}
	}
}
