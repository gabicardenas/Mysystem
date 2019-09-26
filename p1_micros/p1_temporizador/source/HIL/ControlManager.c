#include "MKL27Z644.h"
#include "Debouncer.h"
#include "GPIO_Driver.h"
#include "SegmentDivisor.h"
#include "ControlManager.h"

#define PUSH_BUTTON_RUN						(0)
#define PUSH_BUTTON_CONFIG          		(1)
#define PUSH_BUTTON_UP						(2)
#define PUSH_BUTTON_DOWN		    		(3)
#define PUSH_BUTTON_LEFT		    		(4)
#define PUSH_BUTTON_RIGHT           		(5)

#define PORT_RUN_BUTTON						(READ_PORT_D)
#define PORT_CONFIG_BUTTON					(READ_PORT_D)
#define PORT_LEFT_BUTTON					(READ_PORT_D)
#define PORT_RIGHT_BUTTON					(READ_PORT_D)
#define PORT_UP_BUTTON						(READ_PORT_D)
#define PORT_DOWN_BUTTON					(READ_PORT_D)

#define PULL_ENABLE			                (1)
#define PULL_SELECT			                (1)
#define CONTROL_MANAGER_DEBOUNCE_TIME		(5)  /* es el tiempo en el que el debouncer toma una medicion, son el tiempo que tarda el timer del main*/

#define BUTTON_RUN_DEBOUNCE_CHANNEL			(0)
#define BUTTON_CONFIG_DEBOUNCE_CHANNEL		(1)
#define BUTTON_LEFT_DEBOUNCE_CHANNEL		(2)
#define BUTTON_RIGHT_DEBOUNCE_CHANNEL		(3)
#define BUTTON_UP_DEBOUNCE_CHANNEL			(4)
#define BUTTON_DOWN_DEBOUNCE_CHANNEL		(5)

uint8_t bControlManagerbState = 0;  /* variable de estado config o normal*/
const uint16_t AuxArry[4] = {1000, 100, 10, 1};
/* lo que se quiere obtener es si son millares, decenas, etc*/
uint8_t(*Control_ptrSegmentDivisor[])(uint16_t) =
{
		Get_bfnThousands,
		Get_bfnHundreds,
		Get_bfnTens,
		Get_bfnUnits
};

void ControlManager_vfnDriverInit(void)
{
	bControlManagerbState = enInNormalMode;

	GPIO_vfnDriverInit(enPORT_D, PUSH_BUTTON_RUN,     enINPUT);
	GPIO_vfnDriverInit(enPORT_D, PUSH_BUTTON_CONFIG,  enINPUT);
	GPIO_vfnDriverInit(enPORT_D, PUSH_BUTTON_UP,      enINPUT);
	GPIO_vfnDriverInit(enPORT_D, PUSH_BUTTON_DOWN,    enINPUT);
	GPIO_vfnDriverInit(enPORT_D, PUSH_BUTTON_LEFT,    enINPUT);
	GPIO_vfnDriverInit(enPORT_D, PUSH_BUTTON_RIGHT,   enINPUT);
}

/*  el apuntador de shift apunta a los display, y el otro apunta al numero que se imprime en el display */

uint8_t ControlManager_bfnActivity(uint8_t *ShiftCnt, uint32_t *NumbertoWork)
{
	uint8_t bState = 0;
	uint32_t dwState;
	static uint16_t wTimerCounter = 0;

	if(bControlManagerbState == enInControlMode)
	{
		if(wTimerCounter == CONTROL_MANAGER_DEBOUNCE_TIME)
		{
			wTimerCounter = 0;

			if(bfn_Debouncer((GPIO_bfnReadPin(&PORT_RUN_BUTTON, PUSH_BUTTON_RUN, PULL_ENABLE, PULL_SELECT)), BUTTON_RUN_DEBOUNCE_CHANNEL))
			{
				bState = enInNormalMode;

				bControlManagerbState = enInNormalMode;
			}
			else if(bfn_Debouncer((GPIO_bfnReadPin(&PORT_UP_BUTTON, PUSH_BUTTON_UP, PULL_ENABLE, PULL_SELECT)), BUTTON_UP_DEBOUNCE_CHANNEL))
			{
				dwState = *NumbertoWork;
				dwState = Control_ptrSegmentDivisor[*ShiftCnt](dwState);

				if(dwState == 9)
				{
					*NumbertoWork = ((*NumbertoWork) - (dwState * AuxArry[*ShiftCnt]));
				}
				else
				{
					*NumbertoWork = ((*NumbertoWork) + (AuxArry[*ShiftCnt]));
				}

				bState = enInControlMode;
			}
			else if(bfn_Debouncer((GPIO_bfnReadPin(&PORT_DOWN_BUTTON, PUSH_BUTTON_DOWN, PULL_ENABLE, PULL_SELECT)), BUTTON_DOWN_DEBOUNCE_CHANNEL))
			{
				dwState = *NumbertoWork;
				dwState = Control_ptrSegmentDivisor[*ShiftCnt](dwState);

				if(dwState == 0)
				{
					*NumbertoWork = ((*NumbertoWork) + (9 * AuxArry[*ShiftCnt]));
				}
				else
				{
					*NumbertoWork = ((*NumbertoWork) - (AuxArry[*ShiftCnt]));
				}

				bState = enInControlMode;
			}
			else if(bfn_Debouncer((GPIO_bfnReadPin(&PORT_LEFT_BUTTON, PUSH_BUTTON_LEFT, PULL_ENABLE, PULL_SELECT)), BUTTON_LEFT_DEBOUNCE_CHANNEL))
			{
				if(*ShiftCnt != 0)
				{
					*ShiftCnt = (*ShiftCnt - 1);
				}

				bState = enInControlMode;
			}
			else if(bfn_Debouncer((GPIO_bfnReadPin(&PORT_RIGHT_BUTTON, PUSH_BUTTON_RIGHT, PULL_ENABLE, PULL_SELECT)), BUTTON_RIGHT_DEBOUNCE_CHANNEL))
			{
				if(*ShiftCnt <= 2)
				{
					*ShiftCnt = (*ShiftCnt + 1);
				}

				bState = enInControlMode;
			}
			else
			{
				bState = enInControlMode;
			}
		}
		else
		{
			wTimerCounter++;
			bState = enInControlMode;
		}
	}
	else if(bControlManagerbState == enInNormalMode)
	{
		if(wTimerCounter == CONTROL_MANAGER_DEBOUNCE_TIME)
		{
			wTimerCounter = 0;

			if(bfn_Debouncer((GPIO_bfnReadPin(&PORT_CONFIG_BUTTON, PUSH_BUTTON_CONFIG, PULL_ENABLE, PULL_SELECT)), BUTTON_CONFIG_DEBOUNCE_CHANNEL))
			{
				bState = enInControlMode;

				*ShiftCnt = 0;

				wTimerCounter = 0;

				bControlManagerbState = enInControlMode;
			}
		}
		else
		{
			wTimerCounter++;
		}
	}
	else
	{

	}

	return(bState);
}
