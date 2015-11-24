#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.
#include "C:\Users\james.mcgovern\Desktop\menu helper.h"

void initializeRobot()
{
	return;
}

task main()
{
	initializeRobot();

	bDisplayDiagnostics = false;
	StartTask(runMenu);

	waitForStart(); // Wait for the beginning of autonomous phase.

	StopTask(runMenu);
	eraseDisplay();
	bDisplayDiagnostics = true;

	wait1Msec((Delay)*1000);

	//Use the variables to run your auto here
}
