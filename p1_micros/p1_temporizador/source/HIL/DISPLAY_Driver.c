#include "MKL27Z644.h"
#include "GPIO_Driver.h"
#include "DISPLAY_Driver.h"
#include "SegmentDivisor.h"

#define PIN_SEGMENT_A           		0
#define PIN_SEGMENT_B           		1
#define PIN_SEGMENT_C           		2
#define PIN_SEGMENT_D           		3
#define PIN_SEGMENT_E           		0
#define PIN_SEGMENT_F           		6
#define PIN_SEGMENT_G           		7

#define PIN_DISPLAY_ONE         		16
#define PIN_DISPLAY_TWO         		17
#define PIN_DISPLAY_THREE       		1
#define PIN_DISPLAY_FOUR        		2

#define PORT_SEGMENT_A           		WRITE_PORT_B
#define PORT_SEGMENT_B           		WRITE_PORT_B
#define PORT_SEGMENT_C          		WRITE_PORT_B
#define PORT_SEGMENT_D           		WRITE_PORT_B
#define PORT_SEGMENT_E          		WRITE_PORT_C
#define PORT_SEGMENT_F          		WRITE_PORT_D
#define PORT_SEGMENT_G          		WRITE_PORT_D

#define PORT_DISPLAY_ONE       		 	WRITE_PORT_B
#define PORT_DISPLAY_TWO       		 	WRITE_PORT_B
#define PORT_DISPLAY_THREE     		 	WRITE_PORT_C
#define PORT_DISPLAY_FOUR       		WRITE_PORT_C

#define TURN_ON_SEGMENT_A 				GPIO_vfnWritePin(&PORT_SEGMENT_A,  PIN_SEGMENT_A, 1)
#define TURN_ON_SEGMENT_B				GPIO_vfnWritePin(&PORT_SEGMENT_B,  PIN_SEGMENT_B, 1)
#define TURN_ON_SEGMENT_C				GPIO_vfnWritePin(&PORT_SEGMENT_C,  PIN_SEGMENT_C, 1)
#define TURN_ON_SEGMENT_D				GPIO_vfnWritePin(&PORT_SEGMENT_D,  PIN_SEGMENT_D, 1)
#define TURN_ON_SEGMENT_E				GPIO_vfnWritePin(&PORT_SEGMENT_E,  PIN_SEGMENT_E, 1)
#define TURN_ON_SEGMENT_F				GPIO_vfnWritePin(&PORT_SEGMENT_F,  PIN_SEGMENT_F, 1)
#define TURN_ON_SEGMENT_G				GPIO_vfnWritePin(&PORT_SEGMENT_G,  PIN_SEGMENT_G, 1)

#define TURN_OFF_SEGMENT_A				GPIO_vfnWritePin(&PORT_SEGMENT_A,  PIN_SEGMENT_A, 0)
#define TURN_OFF_SEGMENT_B				GPIO_vfnWritePin(&PORT_SEGMENT_B,  PIN_SEGMENT_B, 0)
#define TURN_OFF_SEGMENT_C				GPIO_vfnWritePin(&PORT_SEGMENT_C,  PIN_SEGMENT_C, 0)
#define TURN_OFF_SEGMENT_D				GPIO_vfnWritePin(&PORT_SEGMENT_D,  PIN_SEGMENT_D, 0)
#define TURN_OFF_SEGMENT_E				GPIO_vfnWritePin(&PORT_SEGMENT_E,  PIN_SEGMENT_E, 0)
#define TURN_OFF_SEGMENT_F				GPIO_vfnWritePin(&PORT_SEGMENT_F,  PIN_SEGMENT_F, 0)
#define TURN_OFF_SEGMENT_G				GPIO_vfnWritePin(&PORT_SEGMENT_G,  PIN_SEGMENT_G, 0)

#define TURN_ON_DISPLAY_ONE				GPIO_vfnWritePin(&PORT_DISPLAY_ONE, 	PIN_DISPLAY_ONE,   0)
#define TURN_ON_DISPLAY_TWO				GPIO_vfnWritePin(&PORT_DISPLAY_TWO, 	PIN_DISPLAY_TWO,   0)
#define TURN_ON_DISPLAY_THREE			GPIO_vfnWritePin(&PORT_DISPLAY_THREE, 	PIN_DISPLAY_THREE, 0)
#define TURN_ON_DISPLAY_FOUR			GPIO_vfnWritePin(&PORT_DISPLAY_FOUR, 	PIN_DISPLAY_FOUR,  0)

#define TURN_OFF_DISPLAY_ONE		    GPIO_vfnWritePin(&PORT_DISPLAY_ONE, PIN_DISPLAY_ONE,     1)
#define TURN_OFF_DISPLAY_TWO		    GPIO_vfnWritePin(&PORT_DISPLAY_TWO, PIN_DISPLAY_TWO,     1)
#define TURN_OFF_DISPLAY_THREE			GPIO_vfnWritePin(&PORT_DISPLAY_THREE, PIN_DISPLAY_THREE, 1)
#define TURN_OFF_DISPLAY_FOUR		    GPIO_vfnWritePin(&PORT_DISPLAY_FOUR, PIN_DISPLAY_FOUR,   1)

#define DISPLAY_TIME_TO_SHIFT			(4)
#define DISPLAY_CONFIG_DISABLE			(0)
#define DISPLAY_CONFIG_AVAILABLE		(1)

void PrintNumberZero(void);
void PrintNumberOne(void);
void PrintNumberTwo(void);
void PrintNumberThree(void);
void PrintNumberFour(void);
void PrintNumberFive(void);
void PrintNumberSix(void);
void PrintNumberSeven(void);
void PrintNumberEight(void);
void PrintNumberNine(void);

void Display_vfnPrintNormal(uint16_t wPrintNumber);
void DISPLAY_vfnNumberPrinter(uint16_t wRecieveValue);

void (*Display_ptraPrintState[])(void) =
{
	PrintNumberZero,
	PrintNumberOne,
	PrintNumberTwo,
	PrintNumberThree,
	PrintNumberFour,
	PrintNumberFive,
	PrintNumberSix,
	PrintNumberSeven,
	PrintNumberEight,
	PrintNumberNine
};

uint8_t bSaveActivityState;
uint8_t bActiveDisplaySelect = 0;

uint32_t dwShiftCounter = 0;

void DISPLAY_vfnDriverInit (void)
{
	bSaveActivityState = NormalState;

	GPIO_vfnDriverInit(enPORT_B, PIN_SEGMENT_A, enOUTPUT);
	GPIO_vfnDriverInit(enPORT_B, PIN_SEGMENT_B, enOUTPUT);
	GPIO_vfnDriverInit(enPORT_B, PIN_SEGMENT_C, enOUTPUT);
	GPIO_vfnDriverInit(enPORT_B, PIN_SEGMENT_D, enOUTPUT);
	GPIO_vfnDriverInit(enPORT_C, PIN_SEGMENT_E, enOUTPUT);
	GPIO_vfnDriverInit(enPORT_D, PIN_SEGMENT_F, enOUTPUT);
	GPIO_vfnDriverInit(enPORT_D, PIN_SEGMENT_G, enOUTPUT);

	GPIO_vfnDriverInit(enPORT_B, PIN_DISPLAY_ONE,   enOUTPUT);
	GPIO_vfnDriverInit(enPORT_B, PIN_DISPLAY_TWO,   enOUTPUT);
	GPIO_vfnDriverInit(enPORT_C, PIN_DISPLAY_THREE, enOUTPUT);
	GPIO_vfnDriverInit(enPORT_C, PIN_DISPLAY_FOUR,  enOUTPUT);
}

void DISPLAY_vfnNumberPrinter(uint16_t wRecieveValue)
{
	Display_ptraPrintState[wRecieveValue]();
}

void PrintNumberZero(void)
{
	 TURN_ON_SEGMENT_A;
	 TURN_ON_SEGMENT_B;
	 TURN_ON_SEGMENT_C;
	 TURN_ON_SEGMENT_D;
	 TURN_ON_SEGMENT_E;
	 TURN_ON_SEGMENT_F;

	 TURN_OFF_SEGMENT_G;
}

void PrintNumberOne(void)
{
	 TURN_ON_SEGMENT_B;
	 TURN_ON_SEGMENT_C;

	 TURN_OFF_SEGMENT_A;
	 TURN_OFF_SEGMENT_D;
	 TURN_OFF_SEGMENT_E;
	 TURN_OFF_SEGMENT_F;
	 TURN_OFF_SEGMENT_G;
}

void PrintNumberTwo(void)
{
	 TURN_ON_SEGMENT_A;
	 TURN_ON_SEGMENT_B;
	 TURN_ON_SEGMENT_D;
	 TURN_ON_SEGMENT_E;
	 TURN_ON_SEGMENT_G;

	 TURN_OFF_SEGMENT_C;
	 TURN_OFF_SEGMENT_F;
}

void PrintNumberThree(void)
{
	 TURN_ON_SEGMENT_A;
	 TURN_ON_SEGMENT_B;
	 TURN_ON_SEGMENT_C;
	 TURN_ON_SEGMENT_D;
	 TURN_ON_SEGMENT_G;

	 TURN_OFF_SEGMENT_E;
	 TURN_OFF_SEGMENT_F;
}

void PrintNumberFour(void)
{
	 TURN_ON_SEGMENT_B;
	 TURN_ON_SEGMENT_C;
	 TURN_ON_SEGMENT_F;
	 TURN_ON_SEGMENT_G;

	 TURN_OFF_SEGMENT_A;
	 TURN_OFF_SEGMENT_D;
	 TURN_OFF_SEGMENT_E;
}

void PrintNumberFive(void)
{
	 TURN_ON_SEGMENT_A;
	 TURN_ON_SEGMENT_C;
	 TURN_ON_SEGMENT_D;
	 TURN_ON_SEGMENT_F;
	 TURN_ON_SEGMENT_G;

	 TURN_OFF_SEGMENT_B;
	 TURN_OFF_SEGMENT_E;
}

void PrintNumberSix(void)
{
	 TURN_ON_SEGMENT_A;
	 TURN_ON_SEGMENT_C;
	 TURN_ON_SEGMENT_D;
	 TURN_ON_SEGMENT_E;
	 TURN_ON_SEGMENT_F;
	 TURN_ON_SEGMENT_G;

	 TURN_OFF_SEGMENT_B;
}

void PrintNumberSeven(void)
{
	 TURN_ON_SEGMENT_A;
	 TURN_ON_SEGMENT_B;
	 TURN_ON_SEGMENT_C;

	 TURN_OFF_SEGMENT_D;
	 TURN_OFF_SEGMENT_E;
	 TURN_OFF_SEGMENT_G;
	 TURN_OFF_SEGMENT_F;
}

void PrintNumberEight(void)
{
	 TURN_ON_SEGMENT_A;
	 TURN_ON_SEGMENT_B;
	 TURN_ON_SEGMENT_C;
	 TURN_ON_SEGMENT_D;
	 TURN_ON_SEGMENT_E;
	 TURN_ON_SEGMENT_F;
	 TURN_ON_SEGMENT_G;
}

void PrintNumberNine(void)
{
	 TURN_ON_SEGMENT_A;
	 TURN_ON_SEGMENT_B;
	 TURN_ON_SEGMENT_C;
	 TURN_ON_SEGMENT_F;
	 TURN_ON_SEGMENT_G;

	 TURN_OFF_SEGMENT_D;
	 TURN_OFF_SEGMENT_E;
}

void DISPLAY_vfnActivitySel(uint16_t wPrintNumber, uint8_t bActivityState)
{
	bSaveActivityState = bActivityState;

	if(bSaveActivityState == NormalState)
	{
		if(dwShiftCounter == DISPLAY_TIME_TO_SHIFT)
		{
			dwShiftCounter = 0;
			Display_vfnPrintNormal(wPrintNumber);
		}
		else
		{
			dwShiftCounter++;
		}
	}
	else if((bSaveActivityState == ConfigState))
	{
		Display_vfnPrintNormal(wPrintNumber);
	}
	else if(bSaveActivityState == RunState)
	{
		bSaveActivityState = NormalState;
	}
	else
	{

	}
}

void Display_vfnPrintNormal(uint16_t wPrintNumber)   /*ESTO ES PARA PRENDER Y APAGAR LOS DISPLAYS*/
{
	uint8_t bPrintAux;

	if(bActiveDisplaySelect == 0)
	{
		if(bSaveActivityState == NormalState)
		{
			bActiveDisplaySelect = 1;
		}

		bPrintAux = Get_bfnThousands(wPrintNumber);
		DISPLAY_vfnNumberPrinter(bPrintAux);

		TURN_ON_DISPLAY_ONE;
		TURN_OFF_DISPLAY_TWO;
		TURN_OFF_DISPLAY_THREE;
		TURN_OFF_DISPLAY_FOUR;
	}
	else if(bActiveDisplaySelect == 1)
	{
		if(bSaveActivityState == NormalState)
		{
			bActiveDisplaySelect = 2;
		}

		bPrintAux = Get_bfnHundreds(wPrintNumber);
		DISPLAY_vfnNumberPrinter(bPrintAux);

		TURN_ON_DISPLAY_TWO;
		TURN_OFF_DISPLAY_ONE;
		TURN_OFF_DISPLAY_THREE;
		TURN_OFF_DISPLAY_FOUR;
	}
	else if(bActiveDisplaySelect == 2)
	{
		if(bSaveActivityState == NormalState)
		{
			bActiveDisplaySelect = 3;
		}

		bPrintAux = Get_bfnTens(wPrintNumber);
		DISPLAY_vfnNumberPrinter(bPrintAux);

		TURN_ON_DISPLAY_THREE;
		TURN_OFF_DISPLAY_ONE;
		TURN_OFF_DISPLAY_TWO;
		TURN_OFF_DISPLAY_FOUR;
	}
	else
	{
		if(bSaveActivityState == NormalState)
		{
			bActiveDisplaySelect = 0;
		}

		bPrintAux = Get_bfnUnits(wPrintNumber);
		DISPLAY_vfnNumberPrinter(bPrintAux);

		TURN_ON_DISPLAY_FOUR;
		TURN_OFF_DISPLAY_ONE;
		TURN_OFF_DISPLAY_TWO;
		TURN_OFF_DISPLAY_THREE;
	}
}
