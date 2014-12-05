#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    AutonSelect,    sensorPotentiometer)
#pragma config(Sensor, in8,    RightArmAngle,  sensorPotentiometer)
#pragma config(Sensor, dgtl1,  waitingButtonBlue, sensorTouch)
#pragma config(Sensor, dgtl11, catapult,       sensorDigitalOut)
#pragma config(Sensor, dgtl12, waitingButtonRed, sensorTouch)
#pragma config(Sensor, I2C_1,  LeftIEM,        sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_2,  RightIEM,       sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Motor,  port1,           LeftArm,       tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port2,           RightFWheel,   tmotorVex393HighSpeed, openLoop, reversed)
#pragma config(Motor,  port3,           RightMWheel,   tmotorVex393HighSpeed, openLoop, reversed, encoder, encoderPort, I2C_2, 1000)
#pragma config(Motor,  port4,           RightBWheel,   tmotorVex393HighSpeed, openLoop, reversed)
#pragma config(Motor,  port5,           LeftIntake,    tmotorVex393HighSpeed, openLoop)
#pragma config(Motor,  port6,           RightIntake,   tmotorVex393HighSpeed, openLoop, reversed)
#pragma config(Motor,  port7,           LeftBWheel,    tmotorVex393HighSpeed, openLoop)
#pragma config(Motor,  port8,           LeftMWheel,    tmotorVex393HighSpeed, openLoop, encoder, encoderPort, I2C_1, 1000)
#pragma config(Motor,  port9,           LeftFWheel,    tmotorVex393HighSpeed, openLoop)
#pragma config(Motor,  port10,          RightArm,      tmotorVex393, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//ABOVE CONFIGURATION COPY AND PASTED FROM 917B-UYakima1-1.c -> Joseph's finished user control code

//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)
//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)


#include "Vex_Competition_Includes.c"

/******************************************
///////// FINAL VARIABLES HERE ///////////
///////// PLACE NECESSARY USER ///////////
//////////CONTROL AND AUTON //////////////
///////// FUNCTIONS HERE /////////////////
******************************************/

////////////////////////////
//***** Drive Values *****//
////////////////////////////
	int FORWARD = 0;
	int BACKWARD = 1;
	int LEFT = 2;
	int RIGHT = 3;
	int TILE = 500; // Theoretically accurate
	int HALF_TILE = 250; // 12"

	int HUNDRED = 127;
	int FIFTY = 64;
	int THIRTY_SEVEN = 48;
	int TWENTY_FIVE = 32;
	int control = 25;
////////////////////
//** Arm Values **//
////////////////////
	int BARRIER = 960;
	int LOW = 130;
	int BUMP = 350;
	int HIGH = 1420;
	int PRE_HIGH = 4000;
	int hold = 20;


//////////////////////////
//**** AUTON SELECT ****//
//////////////////////////
	int AUTON1 = 700;
	int AUTON2 = 2200;
	int AUTON3 = 3800;
/******************************************
///////// VOID FUNCTIONS HERE ////////////
///////// PLACE NECESSARY USER ///////////
//////////CONTROL AND AUTON //////////////
///////// FUNCTIONS HERE /////////////////
******************************************/
	void pre_auton()
	{
		bStopTasksBetweenModes = true; // This is necessary
	}

	void setLeft(int pwr)
	{
		motor[LeftBWheel] = motor[LeftMWheel] = motor[LeftFWheel] = pwr;
	}

	void setRight(int pwr)
	{
		motor[RightBWheel] = motor[RightMWheel] = motor[RightFWheel] = pwr;
	}

	void resetValues(int wait) //reset values to zero for safety - Encoders, Timers and Motors
	{
			wait1Msec(wait);
			motor[LeftBWheel] = motor[LeftMWheel] = motor[LeftFWheel] = 0;
			motor[RightBWheel] = motor[RightMWheel] = motor[RightFWheel] = 0; // drive motors set to zero
			motor[LeftArm] = motor[RightArm] = 0; // arm motors set to zero
			motor[LeftIntake] = motor[RightIntake] = 0; // intake motors set to zero
			nMotorEncoder[LeftMWheel] = 0; //IEMs set to zero
	}

		void preciseDriveStop(int Case) // For now... Select each case to precision stop, idk how to get motor power
	{
		if(Case == FORWARD) // FORWARD if moving forwards -> negative input sharp stop
			motor[LeftBWheel] = motor[LeftMWheel] = motor[LeftFWheel] = motor[RightBWheel] = motor[RightMWheel] = motor[RightFWheel] = -10;
		else if(Case == BACKWARD) // BACKWARD etc...
			motor[LeftBWheel] = motor[LeftMWheel] = motor[LeftFWheel] = motor[RightBWheel] = motor[RightMWheel] = motor[RightFWheel] = 10;
		else if(Case == LEFT) // LEFT
		{
			motor[LeftBWheel] = motor[LeftMWheel] = motor[LeftFWheel] = 5;
			motor[RightBWheel] = motor[RightMWheel] = motor[RightFWheel] = -5;
		}
		else if(Case == RIGHT) // RIGHT
		{
			motor[LeftBWheel] = motor[LeftMWheel] = motor[LeftFWheel] = -5;
			motor[RightBWheel] = motor[RightMWheel] = motor[RightFWheel] = 5;
		}
		else
			motor[LeftBWheel] = motor[LeftMWheel] = motor[LeftFWheel] = motor[RightBWheel] = motor[RightMWheel] = motor[RightFWheel] = 0;
		wait1Msec(1000); // stabilization time
	}

	void noRamp(int direction, int distance)
	{
		nMotorEncoder[LeftMWheel] = 0;
		while(abs(nMotorEncoder[LeftMWheel]) < distance)
		{
			setLeft(direction*FIFTY); setRight(direction*FIFTY);
		}
		if(direction>0)
		{
			preciseDriveStop(FORWARD);
		}
		else
		{
			preciseDriveStop(BACKWARD);
		}
	}

	void noRampFast(int direction, int distance)
	{
		nMotorEncoder[LeftMWheel] = 0;
		while(abs(nMotorEncoder[LeftMWheel]) < distance)
		{
			setLeft(direction*FIFTY+50); setRight(direction*FIFTY+50);
		}
		if(direction>0)
		{
			preciseDriveStop(FORWARD);
		}
		else
		{
			preciseDriveStop(BACKWARD);
		}
	}

	void moveStraight(int direction, int time, int driveTarget)
	{
		nMotorEncoder[LeftMWheel] = 0;
		int distance = 0;
		float pwr = 0;
			while(distance < driveTarget )
			{

					distance = abs(nMotorEncoder[LeftMWheel]);
					if( distance <= driveTarget / 2)
				  pwr = distance / 5 + 25;

					else
						pwr = ( driveTarget - distance ) / 10 + 25;

					pwr *= direction;
					setLeft(pwr);
					setRight(pwr);
			}
			setLeft(0);
			setRight(0);
		}

	void spin(int direction, int time, int degrees) // we need to calculate degrees per tick
	{
		nMotorEncoder[LeftMWheel] = 0;
		// Must test - works

		while(abs(nMotorEncoder[LeftMWheel]) < degrees)
		{
			motor[LeftBWheel] = motor[LeftMWheel] = motor[LeftFWheel] = direction * FIFTY;
			motor[RightBWheel] = motor[RightMWheel] = motor[RightFWheel] = -direction * FIFTY;
		}

		if(direction > 0)
			preciseDriveStop(RIGHT);
		else
			preciseDriveStop(LEFT);
	}

	void intake(int direction){
			motor[LeftIntake] = motor[RightIntake] = direction * 127;
	}

	void launch(){

	}

	void lift(int targetPot)
	{
		int currentPot = SensorValue[RightArmAngle]; // takes current Arm Angle
		while(currentPot != targetPot)
		{
			if(currentPot < targetPot)
			{
				motor[LeftArm] = motor[RightArm] = 127;	 //goes up if lower
			}

			else if(currentPot > targetPot)
			{
				motor[LeftArm] = motor[RightArm] = -127;	//goes down if higher -- must test
			}

			//wait1Msec(50);
			currentPot = SensorValue[RightArmAngle];
		}
	}

	void liftDown()
	{
		while(SensorValue[RightArmAngle] > LOW)
		{
			motor[LeftArm] = motor[RightArm] = -127;

		}
		motor[LeftArm] = motor[RightArm] = 0;
	}

	void holdArm()
	{
		motor[LeftArm] = motor[RightArm] = hold;
	}

	void waitForButton()
	{
		while(SensorValue[waitingButtonRed] == 0 && SensorValue[waitingButtonBlue] == 0){}
	}

	void deploy()
	{
		intake(1);
	}


///////////////////////////
//*** AUTON Functions ***//
///////////////////////////

	void Alex() // Caches preload (5) + Knocks 2 big balls (10)
	{
		waitForButton();
	  moveStraight(1, 0, 1470); // maintenence and recalibrating needed...1400 worked
		wait10Msec(30);
		lift(HIGH);
		holdArm();
		moveStraight(1, 0, 430);
		//wait1Msec(1000);
		intake(-1);
		wait10Msec(150); // outtakes 3
		moveStraight(-1, 0, 400); //move back away from goal
		liftDown();


		moveStraight(-1, 0, 1400);
		waitForButton();

		/*
		bool repeatBall = false;
		ClearTimer(T1);
		while(time1[T1] < 800) {
			if(!(SensorValue[waitingButtonRed] == 0 && SensorValue[waitingButtonBlue] == 0)){
				repeatBall = true;
				break;
			}
		}
		if(repeatBall){
			lift(BARRIER);
			holdArm();
			intake(-1);
			moveStraight(1, 0, 580); //estimated guess based on 10Q's values
			wait1Msec(300);
			moveStraight(-1, 0, 580);
		}
		*/

		wait10Msec(50);
		lift(BARRIER);
		holdArm();

		moveStraight(1, 0, 950);
		wait1Msec(300);
		moveStraight(-1, 0, 950);

		waitForButton();

		noRampFast(1,2000);
		resetValues(100);
	}

	void RedSai()
	{
		deploy();

		moveStraight(1, 0, 950);
		wait1Msec(300);
		moveStraight(-1, 0, 950);
		resetValues(100);

		waitForButton();
		moveStraight(1,0,1500); //move forward
		spin(-1,0,180); // turn towards the cache
		lift(HIGH); // nearest 100
		holdArm();
		moveStraight(1, 0, 650); // reaches goal
		intake(-1);
		wait1Msec(1000); // outtake
	}

		void blueDevansh() // Places preload (1-2) + 2 buckies (2-4) + TURN RIGHT Knocks buckies (1-6)
	{
		deploy();
		intake(1);
		wait10Msec(10);
		moveStraight(1, 0, 455); //picks up
		wait10Msec(50);
		moveStraight(-1, 0, 475);//comes back
		intake(0);
				// end part 1: prepare dump
		waitForButton();
		lift(BUMP);
		holdArm();
		intake(-1);
		resetValues(1200);
			// end part 2: dump
		waitForButton();
		liftDown();
		wait10Msec(100);
		moveStraight(1, 0, 700);
			// end part 3: prepare hit
		spin(1, 0, 200);
		intake(-1);
		lift(BUMP);
		holdArm();
		noRamp(1, 250);
		resetValues(0);
			// end part 4: hit
	}

	void redDevansh() // Places preload (1-2) + 2 buckies (2-4) + TURN LEFT Knocks buckies (1-6)
	{
		deploy();
		intake(1);
		wait10Msec(10);
		moveStraight(1, 0, 455); //picks up
		wait10Msec(50);
		moveStraight(-1, 0, 475);//comes back
		intake(0);
				// end part 1: prepare dump
		waitForButton();
		lift(BUMP);
		holdArm();
		intake(-1);
		resetValues(1200);
			// end part 2: dump
		waitForButton();
		liftDown();
		wait10Msec(100);
		moveStraight(1, 0, 700);
			// end part 3: prepare hit
		spin(-1, 0, 200);
		intake(-1);
		lift(BUMP);
		holdArm();
		noRamp(1, 250);
		resetValues(0);
			// end part 4: hit
	}

/*****************************************************
//////// AUTONOMOUS PROGRAM HERE /////////////////////
*****************************************************/

task autonomous()
{
	deploy();
	while(true)
	{
		if(SensorValue[waitingButtonRed] == 1)
		{
			if(SensorValue[AutonSelect] < AUTON1)
			{

			}
			else if(SensorValue[AutonSelect] < AUTON2)
			{

			}
			else if(SensorValue[AutonSelect] < AUTON3)
			{

		 	}
			break;
		}
		else if(SensorValue[waitingButtonBlue] == 1)
		{
			if(SensorValue[AutonSelect] < AUTON1)
			{

			}
			else if(SensorValue[AutonSelect] < AUTON2)
			{

			}
			else if(SensorValue[AutonSelect] < AUTON3)
			{

			}
			break;
		}
	}
}

bool tomato = false;

task drive()
{
	while(true)
	{
		while(!tomato){
			int RightDrivePower, LeftDrivePower = 0;
			int Channel3 = abs(vexRT(Ch3)) < control ? 0 : vexRT(Ch3);
			int Channel1 = abs(vexRT(Ch1)) < control ? 0 : vexRT(Ch1);

			RightDrivePower = Channel3 - Channel1;
			LeftDrivePower = Channel3 + Channel1;

			setRight(RightDrivePower);

			setLeft(LeftDrivePower);
		}
	}
}




task arm()
{
	while(true)
	{
		if(!tomato){
			int LiftPower = 0;

			if((vexRT[Btn5U] == 0 && vexRT[Btn5D] == 0) && (SensorValue[RightArmAngle] >= (BUMP)))
				LiftPower = hold;
			else if(SensorValue[RightArmAngle] <= LOW) //LOW Safety Limit
				LiftPower = vexRT[Btn5U]*127 - vexRT[Btn5D]*0; // can only go up now
			else // Full Manual
				LiftPower = vexRT[Btn5U]*127 - vexRT[Btn5D]*127;

			if(vexRT[Btn8D] == 1) // left bottom button to set to barrier height, may need testing
			{
				while(SensorValue[RightArmAngle] != BARRIER)
				{
					if(SensorValue[RightArmAngle] < BARRIER)
						LiftPower = 127;
					break;
					if(SensorValue[RightArmAngle] > BARRIER)
						LiftPower = -127;
					break;
				}
			}

			motor[RightArm] = motor[LeftArm] = LiftPower;
		}

	}
}

task intake()
{
	while(true)
	{
		if(!tomato){
			int IntakePower = 0;
			IntakePower = vexRT[Btn6U]*127 - vexRT[Btn6D]*127;
			motor[RightIntake] = motor[LeftIntake] = IntakePower;
		}
	}
}

bool hang = false;
task solenoids()
{
	while(true)
	{
		if(!tomato){
			if(!hang){
				if(vexRT[Btn7R] == 1){
					hang = true;
				}
			}
			else if(hang){
				if(vexRT[Btn7L] == 1){
					hang = false;
				}
			}
			if(hang){
				SensorValue[catapult] = 1;
			}
			else if(vexRT[Btn7U] == 1){
					SensorValue[catapult] = 1;
			}
			else{
				SensorValue[catapult] = 0;
			}
		}
	}
}

task autonTest(){
	Alex();
}

task usercontrol(){
	//StartTask(autonTest);


	StartTask(drive);
	StartTask(arm);
	StartTask(solenoids);
	StartTask(intake);

}
