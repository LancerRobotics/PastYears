#include "JoystickDriver.c"
#include "gyroFunctions.c"

bool smuxOff = false;
bool disableAccel = false;
float lpow, rpow = 0;
int exponentDrive(int input)
{
	if(input < 0)
		return (input*input)*(.0062000123)*-1;
	else
		return (input*input)*(.0062000123);

}



void getJoystickHeader(float x, float y)
{
	float phi;
}

void motorTrigger(tMotor motorCall,int x,int y,int z)
{
	motor[motorCall]= (y+x+z);
}



task FPSDrive()
{
	int x, y, z, trueX, trueY, trueZ;
	while(true)
	{
		getJoystickSettings(joystick);

		x = joystick.joy1_x1; //sideways
		y = joystick.joy1_y1; //forward and backward
		z= joystick.joy1_x2; //rotation
		trueX = (cosDegrees(currHeading+calibrate)*x)-(sinDegrees(currHeading+calibrate)*y); //sets trueX to rotated value
		trueY = (sinDegrees(currHeading+calibrate)*x)+(cosDegrees(currHeading+calibrate)*y);
		x = trueX;
		y = trueY;
		getJoystickHeader(joystick.joy1_y1,joystick.joy1_x1);

		motor[frontLeft]=(-y+x+z)*.78;
		motor[backLeft]= (-y-x+z)*.78; // -y-x||x+y
		motor[frontRight]=(y+x+z)*.78;//-y+x||-x+y
		motor[backRight]=(y-x+z)*.78;

	}
}
