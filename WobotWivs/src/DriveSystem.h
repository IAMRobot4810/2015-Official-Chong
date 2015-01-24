#ifndef DRIVESYSTEM_H
#define DRIVESYSTEM_H

#include "Joystick.h"
#include "Encoder.h"
#include "Talon.h"
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
	Talon *talZero;
	Talon *talOne;
	Talon *talTwo;
	Talon *talThree;
	RobotDrive *drive;
	BuiltInAccelerometer *acc;
	SmartDashboard *dash;

	void DriveArcadeStyle();
	void DriveMecanumStyle();
	void DriveTankStyle();

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
