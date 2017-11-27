#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    gyro,           sensorGyro)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_2,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_3,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_4,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_5,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port2,           frontL,        tmotorVex393TurboSpeed_MC29, PIDControl, reversed, encoderPort, I2C_1)
#pragma config(Motor,  port3,           backL,         tmotorVex393TurboSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           backR,         tmotorVex393TurboSpeed_MC29, openLoop)
#pragma config(Motor,  port5,           frontR,        tmotorVex393TurboSpeed_MC29, PIDControl, encoderPort, I2C_2)
#pragma config(Motor,  port6,           leftLift,      tmotorVex393TurboSpeed_MC29, PIDControl, encoderPort, I2C_3)
#pragma config(Motor,  port7,           rightLift,     tmotorVex393TurboSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           armLift,       tmotorVex393TurboSpeed_MC29, openLoop, encoderPort, I2C_4)
#pragma config(Motor,  port9,           claw,          tmotorVex393TurboSpeed_MC29, openLoop, reversed, encoderPort, I2C_5)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

// CHANGE THESE VARIBLES AS NECESSARY
int armLiftPower = 100;
int clawPower = 100;
int clawTarget;
int clawOpen = 27;

void initialize(){
	resetMotorEncoder(armLift);
	resetMotorEncoder(claw);
	SensorType[gyro] = sensorNone;
	wait1Msec(300);
	SensorType[gyro] = sensorGyro;
	wait1Msec(2000);
}

task driveControl(){
	int threshold=30;
	while(1){
		if(abs(vexRT[Ch3])>threshold){
			motor[frontL]=vexRT[Ch3];
			motor[backL]=vexRT[Ch3];
			wait1Msec(100);
			} else {
			motor[frontL]=0;
			motor[backL]=0;
		}

		if(abs(vexRT[Ch2])>threshold){
			motor[frontR]=vexRT[Ch2];
			motor[backR]=vexRT[Ch2];
			wait1Msec(100);
			} else {
			motor[frontR]=0;
			motor[backR]=0;
		}
	}
}

task armControl(){
	while(1){
		if(vexRT[Btn5U]==1){
			motor[armLift] = armLiftPower;
		} else if (vexRT[Btn5D] == 1){
			motor[armLift] = -armLiftPower;
		} else {
			motor[armLift] = 0;
		}
	}
}

task theClawPControl(){
	while (true){
		if(vexRT[Btn8D] == 1){
			clawTarget = clawOpen;
		} else if (vexRT[Btn8L] == 1){
			clawTarget = 0;
		}
		if (nMotorEncoder[claw] < clawTarget-20){
			motor[claw] = 70;
		}	else if (nMotorEncoder[claw] > clawTarget+20){
			motor[claw] = -70;
		}	else {
			motor[claw] = 0;
		}
		wait1Msec(20);
	}
}

task main(){
	initialize();
	startTask(driveControl);
	startTask(armControl);
	while(1){
	}
}
