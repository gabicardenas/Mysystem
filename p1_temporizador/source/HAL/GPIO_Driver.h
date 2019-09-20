#ifndef HAL_GPIO_DRIVER_H_
#define HAL_GPIO_DRIVER_H_

#define WRITE_PORT_A				GPIOA->PDOR
#define WRITE_PORT_B				GPIOB->PDOR
#define WRITE_PORT_C				GPIOC->PDOR
#define WRITE_PORT_D				GPIOD->PDOR
#define WRITE_PORT_E				GPIOE->PDOR

#define READ_PORT_A					GPIOA->PDIR
#define READ_PORT_B					GPIOB->PDIR
#define READ_PORT_C					GPIOC->PDIR
#define READ_PORT_D					GPIOD->PDIR
#define READ_PORT_E					GPIOE->PDIR

#define TOGGLE_PORT_A				GPIOA->PTOR
#define TOGGLE_PORT_B				GPIOB->PTOR
#define TOGGLE_PORT_C				GPIOC->PTOR
#define TOGGLE_PORT_D				GPIOD->PTOR
#define TOGGLE_PORT_E				GPIOE->PTOR

#define LEFT_BUTTON         0
#define RIGHT_BUTTON        1
#define TOP_BUTTON          2
#define DOWN_BUTTON         3
#define RUN_BUTTON          4
#define CONFIG_BUTTON       5
#define SEGMENT_A           0
#define SEGMENT_B           1
#define SEGMENT_C           2
#define SEGMENT_D           3
#define SEGMENT_E           0
#define SEGMENT_F           6
#define SEGMENT_G           7
#define Display_ONE         16
#define Display_TWO         17
#define Display_THREE       18
#define Display_FOUR        19

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

void GPIO_vfnToggle(volatile uint32_t *ptrPort, uint8_t bPin);
void GPIO_vfnDriverInit(uint8_t enPort, uint8_t bPin, uint8_t bMode);
uint8_t GPIO_vfnReadPin(const volatile uint32_t *ptrPort, uint8_t bPin);
void GPIO_vfnWritePin(volatile uint32_t *ptrPort, uint8_t bPin, uint8_t bState);

#endif
