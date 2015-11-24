#pragma config(Sensor, S1,     HTSPB,          sensorI2CCustom9V) //config protoboard
#pragma DebuggerWindows("joystickSimple") //joystick can control


/*





THIS USES XANDER SOLDAAT'S AND ROBOTC'S DRIVER UTILITIES, INCLUDING THE JOYSTICK DRIVER AND THE HITECHNIC SUPERPRO PROTOBOARD DRIVER

COPYRIGHT (C) 2015 PRIANSH SHAH FOR LANCER ROBOTICS/LIVINGSTON HIGH SCHOOL
FOR OBTAINING A LICENSE TO MODIFY THIS CODE PLEASE CONTACT US AT ftc3415@gmail.com
FOR USING THIS WITHOUT MODIFICATION PLEASE CITE THIS DRIVER IN THE BEGINNING OF YOUR FILE AS SO:
//uses Lancer Robotics NXT ArduinoJoystick script


--





*/
#include "JoystickDriver.c" //can use joystick methods
#include "Drivers/hitechnic-superpro.h" //can use protoboard methods
#include "Drivers/hitechnic-protoboard.h"

#define scale 0.78125 //a scaling factor to reduce joystick input
#define deadzone 15 //joystick deadzone

float x1,y1,x2,y2; //joystick axes values
float buttons[] = {0,0,0,0}; //button values, can be retrieved using returnButtons()
bool ranging = false; //does it range values (for analog, no it doesnt!)
int testVal = 0; //debugging var

bool please(bool x){ return true; }

int convert(float x)
{
	if(x>deadzone) return 1;
	else if(x<-deadzone) return -1;
	else return 0;
}

bool setRanging()
{
	ranging = true;
	return true;
}

bool setDirect()
{
	ranging = false;
	return true;
}

bool getProcessedValues()
{
	if(ranging)
	{
		x1 = joystick.joy1_x1*scale;
		y1 = joystick.joy1_y1*scale;
		x2 = joystick.joy1_x2*scale;
		y2 = joystick.joy1_y2*scale;
	}
	else
	{
		x1 = convert(joystick.joy1_x1*scale);
		y1 = convert(joystick.joy1_y1*scale);
		x2 = convert(joystick.joy1_x2*scale);
		y2 = convert(joystick.joy1_y2*scale);
	}
	return true;
}

task buttonHandler()
{
	while(true)
	{
		for(int j = 0; j<4; j++)
		{
			if(joy1Btn(j)==1) buttons[j] = 1;
			else buttons[j] = 0;
		}
	}
}

ubyte convertToUbyte()
{
	int temp[] = {0,0,0,0,0,0,0,0};
	if(x1>0) temp[0]=1;
	if(x1<0) temp[1]=1;
	if(y1>0) temp[2]=1;
	if(y1<0) temp[3]=1;
	if(x2>0) temp[4]=1;
	if(x2<0) temp[5]=1;
	if(y2>0) temp[6]=1;
	if(y2<0) temp[7]=1;
	int raw=0;
	for(int j = 0; j<8; j++) raw+=temp[j]*(pow(10,j);
	return raw;
}

void init()
{
	HTSPBsetupIO(HTSPB,0xFF);
	HTSPBwriteIO(HTSPB,00000001);
	wait1Msec(500);
	HTSPBwriteIO(HTSPB,00000011);
	wait1Msec(200);
	HTSPBwriteIO(HTSPB,00000111);
	wait1Msec(200);
	HTSPBwriteIO(HTSPB,00001111);
	wait1Msec(500);
	HTSPBwriteIO(HTSPB,11111111);
	wait1Msec(500);
	HTSPBwriteIO(HTSPB,00001111);
	wait1Msec(500);
	HTSPBwriteIO(HTSPB,11111111);
	wait1Msec(200);
	HTSPBwriteIO(HTSPB,00000000);
	HTSPBwriteAnalog(HTSPB,HTSPB_DACO0, DAC_MODE_SINEWAVE, 300, 1023);
}

int returnButtons()
{
	int raw;
	for(int k = 0; k < 4; k++)
	{
		raw+=buttons[k]*pow(10,k);
	}
	return raw;
}


task main()
{
	init();
	while(true)
	{
		getJoystickSettings(joystick); //updates joystick values
		please(getProcessedValues()); //processes them to get triple boolean values
		if(x1!=0 || x2!= 0 || y1!=0 || y2!=0) HTSPBwriteAnalog(HTSPB,HTSPB_DACO1, DAC_MODE_SQUAREWAVE, 300, 1023); //indicates joystick input received
		else HTSPBwriteAnalog(HTSPB, HTSPB_DACO1, DAC_MODE_SQUAREWAVE,300,0);
		HTSPBwriteIO(HTSPB, convertToUbyte()); //writes joystick input
		/*
		[x1 pos, x1 neg, y1 pos, y1 neg, x2 pos, x2 neg, y2 pos, y2 neg] --> 12345678
		   1       2        3       4       5       6       7       8
		*/
		writeDebugStreamLine("Writing %d", convertToUbyte()); //debugger on
	}
	while(true)wait1Msec(1000);
}
