#include "hitechnic-sensormux.h"
#include "Drivers/hitechnic-eopd.h"

float eopdVal;
const tMUXSensor eopdSensor = msensor_S4_2;

typedef enum{
	GRAY = 0,
	NOTGRAY = 1
} color;
color floorColor;

task /*main()*/ readEOPD()
{
	while(true)
	{
		HTEOPDsetLongRange(eopdSensor);
		eopdVal = HTEOPDreadRaw(eopdSensor);
		if(eopdVal>=78) floorColor = NOTGRAY;
		else floorColor = GRAY;
		eraseDisplay();
		nxtDisplayTextLine(3,"%d",floorColor);
		wait1Msec(300);
	}
}
