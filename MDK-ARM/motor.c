#include "motor.h"
#include "main.h"


#define C595_DATA_GPIO_PORT GPIOA
#define C595_DATA_PIN 			GPIO_PIN_7
#define C595_CS_GPIO_PORT GPIOA
#define C595_CS_PIN 			GPIO_PIN_8
#define C595_SCK_GPIO_PORT GPIOA
#define C595_SCK_PIN 			GPIO_PIN_5
#define C595_EN_GPIO_PORT GPIOB
#define C595_EN_PIN 			GPIO_PIN_0




#define DATA(x) HAL_GPIO_WritePin(C595_DATA_GPIO_PORT, C595_DATA_PIN, x? GPIO_PIN_RESET: GPIO_PIN_SET)
#define CS(x) HAL_GPIO_WritePin(C595_CS_GPIO_PORT, C595_CS_PIN, x? GPIO_PIN_RESET: GPIO_PIN_SET)
#define SCK(x) HAL_GPIO_WritePin(C595_SCK_GPIO_PORT, C595_SCK_PIN, x? GPIO_PIN_RESET: GPIO_PIN_SET)
#define EN(x) HAL_GPIO_WritePin(C595_EN_GPIO_PORT, C595_EN_PIN, x? GPIO_PIN_RESET: GPIO_PIN_SET)

uint8_t BYJ[8] = {0x10, 0x30, 0x20, 0x60, 0x40, 0xc0, 0x80, 0x90};


void send__motor_data(uint8_t data)
{
	uint16_t data16 = data << 8;
	
	for (uint8_t i=0; i<16; i++)
	{
		DATA((data16 >> 15) & 1);
		data16 = data16 << 1;
		
		SCK(0);
		SCK(1);
	}
	EN(1);
	EN(0);
}

void motor_drive(uint8_t dir, uint8_t speed)
{
	if (dir)
	{
		for (uint8_t i=0; i<8; i++)
		{
			for (uint8_t j=0; j<20+speed; j++)
				send__motor_data(BYJ[i]);
		}
	}
	else
	{
		for (uint8_t i=0; i<8; i++)
		{
			for (uint8_t j=0; j<20+speed; j++)
				send__motor_data(BYJ[7-i]);
		}
	}
}
