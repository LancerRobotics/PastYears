void setSpeed(int speed, int time)
{
	motor[leftFront]=speed;
	motor[leftMid]=speed;
	motor[leftBack]=speed;
	motor[rightFront]=-speed;
	motor[rightMid]=-speed;
	motor[rightBack]=-speed;
	wait1Msec(time);
}

void turn (int speed, int time)
{
	motor[leftFront]=speed;
	motor[leftMid]=speed;
	motor[leftBack]=speed;
	motor[rightFront]=speed;
	motor[rightMid]=speed;
	motor[rightBack]=speed;
	wait1Msec(time);
}

void stopmotors (int time)
{
	motor[leftFront]=0;
	motor[leftMid]=0;
	motor[leftBack]=0;
	motor[rightFront]=0;
	motor[rightMid]=0;
	motor[rightBack]=0;
	wait1Msec(time);
}
