#ifndef DRIVESYSTEM_H
#define DRIVESYSTEM_H

#include "Joystick.h"
#include "Encoder.h"
#include "CANTalon.h"
#include "RobotDrive.h"
#include "SmartDashboard/SmartDashboard.h"
#include "BuiltInAccelerometer.h"

class DriveSystem{

public:

	DriveSystem();
	~DriveSystem();

	Joystick *stick;
	Joystick *stickTwo;
	Encoder *talOneEnco;
	Encoder *talTwoEnco;
	CANTalon *talZero;
	CANTalon *talOne;
	CANTalon *talTwo;
	CANTalon *talThree;
	RobotDrive *drive;
	BuiltInAccelerometer *acc;
	SmartDashboard *dash;

	void DriveArcadeStyle();
	void DriveMecanumStyle();
	void DriveTankStyle();
	void DriveSpeedMecanum(float x, float y, float z);
	void StopRobot();

private:

	int eReadOne;
	int eReadTwo;
	float sReadX;
	float sReadY;
	float sReadZ;
	float sReadTwoX;
	float sReadTwoY;
	float sReadTwoZ;
	float talValYExp;
	float talValXExp;
	float talValZExp;
	float talZeroSpeed;
	float talOneSpeed;
	float talTwoSpeed;
	float talThreeSpeed;
	double accValX;
	double accValY;
	double accValZ;

protected:

};

#endif
