#pragma config(Sensor, S4, HTTMUX,         sensorHiTechnicTouchMux)

#include "JoystickDriver.c"

#include "C:\Program Files (x86)\Robomatter Inc\ROBOTC Development Environment\Sample Programs\NXT\3rd Party Sensor Drivers\drivers\hitechnic-touchmux.h"
#include "C:\Program Files (x86)\Robomatter Inc\ROBOTC Development Environment\Sample Programs\NXT\3rd Party Sensor Drivers\drivers\lego-touch.h"


void initializeRobot()
{


	// Place code here to sinitialize servos to starting positions.
	// Sensors are automatically configured and setup by ROBOTC. They may need a brief time to stabilize.

	return;
}

task main()
{
SensorType[S4] = sensorHiTechnicTouchMux;

initializeRobot();

	waitForStart();

	while(true)

	{
		int nButtonMap=SensorValue[S4];

		nxtDisplayTextLine(3, "test %d", nButtonMap);

	}
}
