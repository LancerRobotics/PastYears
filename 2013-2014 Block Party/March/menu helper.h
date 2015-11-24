TButtons NEXT_BTN = kRightButton;
TButtons PREV_BTN = kLeftButton;
TButtons CAT_BTN = kEnterButton;

void switchBool(bool *ptr, TButtons btn)
{
	if(btn == NEXT_BTN || btn == PREV_BTN)
	{
		*ptr=!*ptr;
	}
}

void switchInt(int *ptr, TButtons btn)
{
	if(btn == NEXT_BTN){
		*ptr=*ptr+1;
	} else if(btn == PREV_BTN) {
		*ptr=*ptr-1;
	}
}

bool red=true;
bool near=true;
int delay=0;

task runMenu()
{
	void* currVar;
	char currType;

	currVar = &red;
	currType = 'b';

	while(true){
		if(delay<0){
			delay=0;
		} else if(delay>10){
			delay = 10;
		}

		nxtDisplayString(0,"Color:    %s",red?"red":"blue ");
		nxtDisplayString(1,"Side: %s",near?"near":"far");
		nxtDisplayString(2,"Delay:   %2i",delay);

		nxtDisplayTextLine(7,"%s,%s,%i",red?"R":"B",near?"Near":"Far",delay);

		if(currVar == &red)
		{
			nxtDisplayStringAt(94,63,"*");
			nxtDisplayStringAt(94,55," ");
			nxtDisplayStringAt(94,47," ");
		} else if(currVar == &near){
			nxtDisplayStringAt(94,63," ");
			nxtDisplayStringAt(94,55,"*");
			nxtDisplayStringAt(94,47," ");
		} else {
			nxtDisplayStringAt(94,63," ");
			nxtDisplayStringAt(94,55," ");
			nxtDisplayStringAt(94,47,"*");
		}

		//this section is copied from JoystickDriver.c with changed line numbers
		if ( externalBatteryAvg < 0){
			nxtDisplayTextLine(5, "Ext Batt: OFF");       //External battery is off or not connected
		} else {
			nxtDisplayTextLine(5, "Ext Batt:%4.1f V", externalBatteryAvg / (float) 1000);
		}
		nxtDisplayTextLine(6, "NXT Batt:%4.1f V", nAvgBatteryLevel / (float) 1000);   // Display NXT Battery Voltage

		if(nNxtButtonPressed==NEXT_BTN||nNxtButtonPressed==PREV_BTN){
			if(currType=='b'){
				switchBool(currVar,nNxtButtonPressed);
			} else if (currType=='i') {
				switchInt(currVar,nNxtButtonPressed);
			}
			ClearTimer(T1);
			while(nNxtButtonPressed!=kNoButton&&time1[T1]<=400);
		}

		if(nNxtButtonPressed==CAT_BTN){
			if(currVar == &red){
				currVar = &near;
				currType = 'b';
			} else if(currVar == &near) {
				currVar = &delay;
				currType = 'i';
			} else {
				currVar = &red;
				currType = 'b';
			}
			ClearTimer(T1);
			while(nNxtButtonPressed!=kNoButton&&time1[T1]<=400);
		}


	}
}

void displayAutoType()
{
	nxtDisplayTextLine(7,"%s,%s,%i",red?"R":"B",near?"Near":"Far",delay);
}
