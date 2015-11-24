#include "Drivers/hitechnic-sensormux.h"
#include "JoystickDriver.c"

int BUTTON_DUMP = 8;
int BUTTON_STOREDUMP = 1;
int score = 0;

//added this, thisll make the dump more readable :P
typedef enum {
	down = 185,
	regular = 90,
	store = 75
} servoPosition;

servoPosition dumpPosition;

task runDump(){
	servo[dump] = 80;
	wait1Msec(1000);
	while(true){
		if(joy2Btn(8)||joy1Btn(8))
		{
			servo[dump] = 180;
		}
		if(joy2Btn(6)||joy1Btn(6))
		{
		servo[dump] = 80;
		}
		if(joy2Btn(1)||joy1Btn(1))
		{
		servo[dump]= 70;
		}
	}
}
