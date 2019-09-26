#include "MKL27Z644.h"
#include "SegmentDivisor.h"

#define  DIVIDER_4_NUMBERS				1000
#define  DIVIDER_3_NUMBERS				100
#define  DIVIDER_2_NUMBERS				10

uint8_t Get_bfnThousands(uint16_t wNumber)
{
	wNumber = wNumber/DIVIDER_4_NUMBERS;

	return(wNumber);
}

uint8_t Get_bfnHundreds(uint16_t wNumber)
{
	wNumber = ((wNumber) - ((wNumber/DIVIDER_4_NUMBERS)*(DIVIDER_4_NUMBERS)));

	wNumber = (wNumber/DIVIDER_3_NUMBERS);

	return(wNumber);
}

uint8_t Get_bfnTens(uint16_t wNumber)
{
	wNumber = ((wNumber) - ((wNumber/DIVIDER_4_NUMBERS)*(DIVIDER_4_NUMBERS)));
	wNumber = ((wNumber) - ((wNumber/DIVIDER_3_NUMBERS)*(DIVIDER_3_NUMBERS)));

	wNumber = wNumber/DIVIDER_2_NUMBERS;

	return(wNumber);
}

uint8_t Get_bfnUnits(uint16_t wNumber)
{
	wNumber = ((wNumber) - ((wNumber/DIVIDER_4_NUMBERS)*(DIVIDER_4_NUMBERS)));
	wNumber = ((wNumber) - ((wNumber/DIVIDER_3_NUMBERS)*(DIVIDER_3_NUMBERS)));
	wNumber = ((wNumber) - ((wNumber/DIVIDER_2_NUMBERS)*(DIVIDER_2_NUMBERS)));

	return(wNumber);
}

