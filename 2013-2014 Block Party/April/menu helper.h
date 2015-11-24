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

bool Red=true;
bool Near=true;
int Delay=0;

task runMenu()
{
void* currVar;
char currType;

currVar = &Red;
currType = 'b';

while(true){
if(Delay<0){
Delay=0;
} else if(Delay>25){
Delay = 25;
}

nxtDisplayString(0,"Color:    %s",Red?"red":"blue ");
nxtDisplayString(1,"Side: %s",Near?"near":"far");
nxtDisplayString(2,"Delay:   %2i",Delay);

nxtDisplayTextLine(7,"%s,%s,%i",Red?"R":"B",Near?"Near":"Far",Delay);

if(currVar == &Red)
{
nxtDisplayStringAt(94,63,"*");
nxtDisplayStringAt(94,55," ");
nxtDisplayStringAt(94,47," ");
} else if(currVar == &Near){
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
if(currVar == &Red){
currVar = &Near;
currType = 'b';
} else if(currVar == &Near) {
currVar = &Delay;
currType = 'i';
} else {
currVar = &Red;
currType = 'b';
}
ClearTimer(T1);
while(nNxtButtonPressed!=kNoButton&&time1[T1]<=400);
}


}
}

void displayAutoType()
{
nxtDisplayTextLine(7,"%s,%s,%i",Red?"R":"B",Near?"Near":"Far",Delay);
}
