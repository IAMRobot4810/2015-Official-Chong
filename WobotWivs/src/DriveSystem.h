#ifndef DRIVESYSTEM_H
#define DRIVESYSTEM_H

#include "WPILib.h"

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
	SmartDashboard *dash;

	void DriveArcadeStyle();
	void DriveMecanumStyle();
	void DriveTankStyle();

private:

	int eRead;
	int eReadTwo;
	float sReadX;
	float sReadY;
	float sReadZ;
	float sReadTwoX;
	float sReadTwoY;
	float sReadTwoZ;
	float talValYExp;
	float talValXExp;


protected:

};

#endif