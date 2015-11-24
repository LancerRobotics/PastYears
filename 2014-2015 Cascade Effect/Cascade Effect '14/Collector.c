#include "JoystickDriver.c"
#include "hitechnic-sensormux.h"


int BUTTON_COLLECT = 5;
int BUTTON_REVERSECOLLECT = 7;

task runCollector(){
	while(true){
		if(joy2Btn(BUTTON_COLLECT)){
			motor[collector] = -65;
			motor[collector2] = 65;
		}
		else if(joy2Btn(BUTTON_REVERSECOLLECT)){
			motor[collector] = 65;
			motor[collector2] = -65;
		}
		else if(joy1Btn(5)){
			motor[collector] = -65;
			motor[collector2] = 65;
		}
		else if(joy1Btn(7)){
			motor[collector] = 65;
			motor[collector2] = -65;
		}
		else{
			motor[collector] = 0;
			motor[collector2] = 0;
		}

	}
}
