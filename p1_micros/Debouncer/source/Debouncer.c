#include "MKL27Z644.h"

#define READ_PORT_A					GPIOA->PDIR
#define READ_PORT_B					GPIOB->PDIR
#define READ_PORT_C					GPIOC->PDIR
#define READ_PORT_D					GPIOD->PDIR
#define READ_PORT_E					GPIOE->PDIR

#define WRITE_PORT_A				GPIOA->PDOR
#define WRITE_PORT_B				GPIOB->PDOR
#define WRITE_PORT_C				GPIOC->PDOR
#define WRITE_PORT_D				GPIOD->PDOR
#define WRITE_PORT_E				GPIOE->PDOR

#define PULL_ENABLE                 1
#define PULL_SELECT                 1
#define PUSH_BUTTON_RUN				0
#define LED                         1
#define HIGH                        1
#define LOW                         0

typedef enum
{
	enPORT_A = 0,
	enPORT_B,
	enPORT_C,
	enPORT_D,
	enPORT_E
}PortEnum;

typedef enum
{
	enINPUT = 0,
	enOUTPUT
}PortMode;


void GPIO_vfnDriverInit(uint8_t enPort, uint8_t bPin, uint8_t bMode)
{
	if(enPort == enPORT_A)
	{
		SIM -> SCGC5 |= SIM_SCGC5_PORTA_MASK;
		PORTA -> PCR[bPin] |= (1 << PORT_PCR_MUX_SHIFT);

		if(bMode == enINPUT)
		{
			GPIOA -> PDDR &= ~(1 << bPin);
		}
		else if(bMode == enOUTPUT)
		{
			GPIOA -> PDDR |=  (1 << bPin);
		}
	}
	else if(enPort == enPORT_B)
	{
		SIM -> SCGC5 |= SIM_SCGC5_PORTB_MASK;
		PORTB -> PCR[bPin] |= (1 << PORT_PCR_MUX_SHIFT);

		if(bMode == enINPUT)
		{
			GPIOB -> PDDR &= ~(1 << bPin);
		}
		else if(bMode == enOUTPUT)
		{
			GPIOB -> PDDR |=  (1 << bPin);
		}
	}
	else if(enPort == enPORT_C)
	{
		SIM -> SCGC5 |= SIM_SCGC5_PORTC_MASK;
		PORTC -> PCR[bPin] |= (1 << PORT_PCR_MUX_SHIFT);

		if(bMode == enINPUT)
		{
			GPIOC -> PDDR &= ~(1 << bPin);
		}
		else if(bMode == enOUTPUT)
		{
			GPIOC -> PDDR |=  (1 << bPin);
		}
	}
	else if(enPort == enPORT_D)
	{
		SIM -> SCGC5 |= SIM_SCGC5_PORTD_MASK;
		PORTD -> PCR[bPin] |= (1 << PORT_PCR_MUX_SHIFT);

		if(bMode == enINPUT)
		{
			GPIOD -> PDDR &= ~(1 << bPin);
		}
		else if(bMode == enOUTPUT)
		{
			GPIOD -> PDDR |=  (1 << bPin);
		}
	}
	else if(enPort == enPORT_E)
	{
		SIM -> SCGC5 |= SIM_SCGC5_PORTE_MASK;
		PORTE -> PCR[bPin] |= (1 << PORT_PCR_MUX_SHIFT);

		if(bMode == enINPUT)
		{
			GPIOE -> PDDR &= ~(1 << bPin);
		}
		else if(bMode == enOUTPUT)
		{
			GPIOE -> PDDR |=  (1 << bPin);
		}
	}
	else
	{
		/* error */
	}
}

void GPIO_vfnWritePin(volatile uint32_t *ptrPort, uint8_t bPin, uint8_t bState)
{
	if(bState)
	{
		*ptrPort |= (1 << bPin);
	}
	else
	{
		*ptrPort &= ~(1 << bPin);
	}
}

uint8_t GPIO_bfnReadPin(const volatile uint32_t *ptrPort, uint8_t bPin, uint8_t bPull_Enable, uint8_t bPull_Select)
{
	uint8_t bPinState = 0;

	if((*ptrPort) & (1 << bPin))
	{
		PORTD ->PCR[bPin] |=  (1 << PORT_PCR_PE_SHIFT);
		PORTD ->PCR[bPin] &= ~(1 << PORT_PCR_PS_SHIFT);
		bPinState = 1;
	}
	else
	{
		bPinState = 0;
	}

	return(bPinState);
}

void GPIO_vfnDriverInit(uint8_t enPort, uint8_t bPin, uint8_t bMode);
void GPIO_vfnWritePin(volatile uint32_t *ptrPort, uint8_t bPin, uint8_t bState);
uint8_t GPIO_bfnReadPin(const volatile uint32_t *ptrPort, uint8_t bPin, uint8_t bPull_Enable, uint8_t bPull_Select);
/*uint8_t abButton_caption[3] = {0,0,0};
static uint8_t bIndex = 0;
uint8_t bCurrent_State = 0;            */  /*   estable   */

int main(void)
{
	uint32_t dwTemp_Val = 0;
	GPIO_vfnDriverInit(enPORT_D, PUSH_BUTTON_RUN, enINPUT);
	GPIO_vfnDriverInit(enPORT_D, LED, enOUTPUT);

    while(1)
    {
    	dwTemp_Val = GPIO_bfnReadPin(&READ_PORT_D, PUSH_BUTTON_RUN, PULL_ENABLE, PULL_SELECT);

    		if(dwTemp_Val == HIGH)
    		{
    			GPIO_vfnWritePin(&WRITE_PORT_D, LED, HIGH);
    		}
    		else
    		{
    			GPIO_vfnWritePin(&WRITE_PORT_D, LED, LOW);
    		}
    }
}

