#ifndef __BLUETOOTH_H__
#define __BLUETOOTH_H__

#define Startup         1
#define Stop            2
#define ManualMode      3
#define GoForward       4
#define GoBackward      5
#define TurnLeft        6
#define TurnRight       7
#define AutoAvoid       8
#define AutoWayfinding  9
#define ManualMode_Exit 10
#define AutoAvoid_Exit  11
#define AutoWayfinding_Exit  12

uint8_t BT_GetInstructionValue(char* command);

#endif
