#include "MKL27Z644.h"
#include "Debouncer.h"

#if(DEBOUNCE_CHANNELS_TO_USE >= 1)

uint8_t bfn_Debouncer(uint8_t bInput_Val, uint8_t bChannel)
{
	uint8_t bReadValue;

	static uint8_t bIndex = 0;
	static uint8_t Samples[((3) + (DEBOUNCE_CHANNELS_TO_USE * 3))];
	static uint8_t StableValue[DEBOUNCE_CHANNELS_TO_USE];

	if(bChannel < DEBOUNCE_CHANNELS_TO_USE)
	{
		bReadValue = bInput_Val;

		if(bReadValue != StableValue[bChannel])
		{
			Samples[bIndex + (bChannel * 3)] = bReadValue;

			bIndex++;
		}
		else
		{
			bIndex = 0;
		}

		if(Samples[0 + (bChannel * 3)] == Samples[2 + (bChannel * 3)])
		{
			StableValue[bChannel] = Samples[0 + (bChannel * 3)];
			bIndex = 0;
		}
		else if(Samples[0 + (bChannel * 3)] != Samples[1 + (bChannel * 3)])
		{
			StableValue[bChannel] = Samples[0 + (bChannel * 3)];
			bIndex = 0;
		}

		if(bReadValue == StableValue[bChannel])
		{
			StableValue[bChannel] = 0;
		}
	}
	else
	{
		while(1);
	}

	return(StableValue[bChannel]);
}
#endif
