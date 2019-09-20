#include "MKL27Z644.h"
#include "GPIO_Driver.h"

#define SET_BIT(var,bit)    var |=  (1<<bit)
#define RESET_BIT(var,bit)  var &= ~(1<<bit)
#define CHECK_BIT(var,bit)  var &   (1<<bit)

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

uint8_t GPIO_vfnReadPin(const volatile uint32_t *ptrPort, uint8_t bPin)
{
	uint8_t bPinState = 0;

	if((*ptrPort) & (1 << bPin))
	{
		/** si esta entrando voltaje entra aqui **/

		bPinState = 1;
	}
	else
	{
		bPinState = 0;
	}

	return(bPinState);
}

void GPIO_vfnToggle(volatile uint32_t *ptrPort, uint8_t bPin)
{
	*ptrPort |= (1 << bPin);
}
