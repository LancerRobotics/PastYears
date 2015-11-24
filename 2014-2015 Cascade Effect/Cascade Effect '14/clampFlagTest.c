#include "hitechnic-sensormux.h"
#include "RollingGoal.c"
#include "Robotics (PROGRAMENG)/lego-touch.h"

const tMUXSensor touchClamp = msensor_S4_1;

//float servoVAL = 0;
//bool breakOut = false;

task autoRollingGoal()
{
//	servo[dump] = 75;
//	servo[flag]=8;

	servo[flag] = 0;
	servo[rollingGoalPair] = OPEN;
		wait1Msec(1000);



	while(true)
	{
		//servoVal = servo[flag];
		pressed = TSreadState(touchClamp);
		//if(pressed)breakOut = true;
		if(pressed)
		{
			breakOut = true;
		}
		else if(!pressed) breakOut = false;
		if(breakOut)
		{
			servo[flag] = 110;
			servo[rollingGoalPair] = CLAMPED;
		}

		else
		{
			servo[flag] = 0;
		}

			/*
		if(breakOut)
		{
			servo[flag] = 110;
			wait1Msec(1000);
		}
		//else servo[flag] = 0;
		*/
		/*
		if(pressed && !breakOut) {servo[flag] = 110; breakOut = true;}
		if(!pressed){breakOut = false; servo[flag] = 0;}
		*/
	}
}
