#ifndef DRIVESYSTEM_H
#define DRIVESYSTEM_H
//#pragma once

//#include "WPILib.h"


#include "Joystick.h"
#include "CANTalon.h"
#include "RobotDrive.h"
#include "SmartDashboard/SmartDashboard.h"

class DriveSystem{

public:

	DriveSystem();
	~DriveSystem();

	Joystick *stick;
	CANTalon *rlTal;
	CANTalon *rrTal;
	CANTalon *frTal;
	CANTalon *flTal;
	RobotDrive *drive;
	SmartDashboard *dash;

	void DriveMecanumStyle();
	void DriveSpeedMecanum(float x, float y, float z);

private:

	int eReadfl;
	int eReadfr;
	int eReadrl;
	int eReadrr;
	float sReadX;
	float sReadY;
	float sReadZ;
	float sReadTwoX;
	float sReadTwoY;
	float sReadTwoZ;
	float gyrRead;
	float talValYExp;
	float talValXExp;
	float talValZExp;
	float rlTalSpeed;
	float rrTalSpeed;
	float frTalSpeed;
	float flTalSpeed;

};

#endif
