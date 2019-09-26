#ifndef HIL_CONTROLMANAGER_H_
#define HIL_CONTROLMANAGER_H_

typedef enum
{
	enInNormalMode = 0, /*  para que ya se vea el numero y comience a decrementar  */
	enInControlMode
}_ControlManagerState;

void ControlManager_vfnDriverInit(void);
uint8_t ControlManager_bfnActivity(uint8_t *ShiftCnt, uint32_t *NumbertoWork);

#endif
