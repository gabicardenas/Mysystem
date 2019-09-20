/********************************************************
*	Author:
*	File Name:
*       Description:
*
********************************************************/

/******************** Include Section ******************/
#include "MKL27Z644.h"
#include "GPIO_Driver.h"

/********************     Defines     ******************/

/******************** Function Prototypes  *************/

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
	GPIO_vfnDriverInit(enPORT_B, 18, enOUTPUT);

	GPIO_vfnWritePin(&WRITE_PORT_B, 18, 1);

	GPIO_vfnDriverInit(enPORT_C, 1, enINPUT);

    while(1)
    {
    	if(GPIO_vfnReadPin(&READ_PORT_C, 1))
    	{
    		asm("NOP");
    	}
    	else
    	{
    		GPIO_vfnToggle(&TOGGLE_PORT_B, 18);
    	}
    }

    return(0);
}
