#include "MKL27Z644.h"


/**
  * @fn vfnInRange
  * @brief Alarm activated if the received value is in the specified range
  * @param No receive a parameters
  * @return No return
*/

void vfnInRange(void);
/**
  * @fn vfnOutRange
  * @brief Alarm activated if the received value is in the specified range
  * @param No receive a parameters
  * @return No return
*/

void vfnOutRange(void);
/**
  * @fn vfnClose
  * @brief Alarm activated if the received value is in the specified range
  * @param No receive a parameters
  * @return No return
*/

void vfnClose(void);
/**
  * @fn vfnLowFrequency
  * @brief Alarm activated if the received value is in the specified range
  * @param No receive a parameters
  * @return No return
*/

void vfnLowFrequency (void);
/**
  * @fn vfnHighFrequency
  * @brief Alarm activated if the received value is in the specified range
  * @param No receive a parameters
  * @return No return
*/

void vfnHighFrequency (void);
/**
  * @fn vfnStableFrequency
  * @brief Alarm activated if the received value is in the specified range
  * @param No receive a parameters
  * @return No return
*/
void vfnStableFrequency(void);

/*
  * @fn Delay
  * @brief Variable used for have a death time, with the purpose to see the change of each alarms
*/
volatile unsigned long Delay = 0;

/**
  * @fn main
  * @brief Main function, where you use all the drivers created in the module
    to meet the objective, in this case, activate alarms so that the mother has a notion of
    what happens with her baby
  * @param No receive a parameters
  * @return No return
*/
void main(void) {
	  uint8_t myNewFuction = 0;
      uint8_t bValFrecuency;
      uint8_t sRangeDetector = 0;
      UART_vfnDriverInit();

    while(1)
    {
        UART1_bfnRead (&bValFrecuency);

            if(bValFrecuency <= 62)
            {
                 vfnLowFrequency();
            }
            if((bValFrecuency > 62) && (bValFrecuency < 66))
            {
                 vfnStableFrequency();
            }
            if(bValFrecuency > 66)
            {
            	 vfnHighFrequency();
            }

       UART_bfnRead(&sRangeDetector);

            if(sRangeDetector <= 50)
            {
                  vfnClose();
            }
            if((sRangeDetector > 50) && (sRangeDetector <= 54))
            {
                  vfnInRange();
            }
            if(sRangeDetector > 54)
            {
                  vfnOutRange();
            }


    }
}
