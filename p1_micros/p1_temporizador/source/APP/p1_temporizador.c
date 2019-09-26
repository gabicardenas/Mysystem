/********************************************************
*	Author: Gabriela Ceja, Frida Garcia
*	File Name: Timer
*   Description:
*
********************************************************/

/******************** Include Section ******************/
#include "MKL27Z644.h"
#include "GPIO_Driver.h"
#include "DISPLAY_Driver.h"
#include "ControlManager.h"

/********************     Defines     ******************/
#define APP_LED_TIME				(1000)

/******************** Function Prototypes  *************/
void App_vfnLedInit(void);

/******************** Local Functions ******************/
/** @brief
 *  @param
 *  @param
 *  @return
 */


/******************* Global Functions ******************/
/** @brief
 *  @param
 *  @param
 *  @return
 */

/******************* Static Variables ******************/

/******************* Global Variables ******************/

/******************* Static constants ******************/

/******************* Global Variables ******************/

/*******************      Function    ******************/
int main(void)
{
	uint8_t bAppState = 0;
	uint32_t dwTimerCounter;
	uint16_t wLedCounter = 0;
	uint32_t dwApp_PrinterNumber = 0;

	App_vfnLedInit();

	DISPLAY_vfnDriverInit();

	ControlManager_vfnDriverInit();

    while(1)
    {
    	if(wLedCounter == APP_LED_TIME)
    	{
    		wLedCounter = 0;
    		GPIO_vfnToggle(&TOGGLE_PORT_B, 18);

    		if((bAppState == enInNormalMode) && (dwApp_PrinterNumber > 0))
    		{
    			dwApp_PrinterNumber--;
    		}
    	}

    	wLedCounter++;
    	dwTimerCounter = 1000;
    	while(dwTimerCounter--);

    	bAppState = ControlManager_bfnActivity(&bActiveDisplaySelect, &dwApp_PrinterNumber);

    	DISPLAY_vfnActivitySel(dwApp_PrinterNumber, bAppState);
    	as
    }

    return(0);
}

void App_vfnLedInit(void)
{
	GPIO_vfnDriverInit(enPORT_B, 18, enOUTPUT);
}
