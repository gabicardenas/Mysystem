#ifndef HIL_DISPLAY_DRIVER_H_
#define HIL_DISPLAY_DRIVER_H_

void DISPLAY_vfnDriverInit (void);
void DISPLAY_vfnDriverBn (void);

void Display_vfnPrintNormal(uint16_t wPrintNumber);
void DISPLAY_vfnNumberPrinter(uint16_t bRecieveValue);

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

void DISPLAY_vfnActivitySel(uint16_t wPrintNumber, uint8_t bActivityState);

typedef enum
{
	NormalState = 0,
	ConfigState,
	RunState
}Statemodes;

extern uint8_t bActiveDisplaySelect;

#endif /* HIL_DISPLAY_DRIVER_H_ */
