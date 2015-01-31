#include "DriveSystem.h"
#include "math.h"

DriveSystem::DriveSystem(){

	stick  = new Joystick(0);
	stickTwo = new Joystick(1);
	talOneEnco = new Encoder(2, 3, false);
	talTwoEnco = new Encoder(0, 1, true);
	talZero = new CANTalon(1);
	talOne = new CANTalon(2);
	talTwo = new CANTalon(4);
	talThree = new CANTalon(3);
	drive = new RobotDrive(talTwo, talThree, talOne, talZero);
	acc = new BuiltInAccelerometer();
	dash->init();
	drive->SetInvertedMotor(RobotDrive::kFrontRightMotor, true);
	drive->SetInvertedMotor(RobotDrive::kRearRightMotor, true);

}

DriveSystem::~DriveSystem(){

	delete stick;
	delete stickTwo;
	delete talOneEnco;
	delete talTwoEnco;
	delete talZero;
	delete talOne;
	delete talTwo;
	delete talThree;
	delete drive;
	delete acc;

}

void DriveSystem::DriveMecanumStyle(){

	sReadX = stick->GetX();
	sReadY = stick->GetY();
	sReadZ = stick->GetZ();

	eReadOne = talTwoEnco->GetRate();
	eReadTwo = talOneEnco->GetRate();

	accValX = acc->GetX();
	accValY = acc->GetY();
	accValZ = acc->GetZ();

	talValYExp = pow(sReadY, 5);
	talValXExp = pow(sReadX, 5);
	talValZExp = pow(sReadZ, 5);

	double xPrint = static_cast<float>(sReadX);
	double yPrint = static_cast<float>(sReadY);
	double zPrint = static_cast<float>(sReadZ);
	double deRead = static_cast<int>(eReadOne);
	double deReadTwo = static_cast<int>(eReadTwo);

	dash->PutNumber("Joystick X", xPrint);
	dash->PutNumber("Joystick Y", yPrint);
	dash->PutNumber("Joystick Z", zPrint);
	dash->PutNumber("Front Left Encoder",deRead);
	dash->PutNumber("Front Right Encoder",deReadTwo);
	dash->PutNumber("Roll", accValX);
	dash->PutNumber("Pitch", accValY);
	dash->PutNumber("Yaw", accValZ);

	if((sReadX <= 0.5 && sReadX >= -0.5) && (sReadY <= 0.5 && sReadY >= -0.5)&& (sReadZ <= 0.5 && sReadZ >= -0.5)){

		drive->StopMotor();

	}

	else if((sReadX <= 0.5 || sReadX >= -0.5) && (sReadY >= 0.5 && sReadY <= -0.5) && (sReadZ <= 0.5 || sReadZ >= -0.5)){

		drive->MecanumDrive_Cartesian(0.0, talValYExp, 0.0);

		if(eReadOne < eReadTwo){

			for(talTwoSpeed = sReadY; eReadTwo > eReadOne; talTwoSpeed-0.01){

				talTwo->Set(talTwoSpeed);

			}

		}

		else if(eReadOne > eReadTwo){

			for(talOneSpeed = sReadY; eReadOne > eReadTwo; talOneSpeed-0.01){

				talOne->Set(talOneSpeed);

			}

		}

		else{

			drive->MecanumDrive_Cartesian(0.0, talValYExp, 0.0);

		}

	}

	else{

		drive->MecanumDrive_Cartesian(talValXExp, talValYExp, talValZExp);

	}

}

void DriveSystem::DriveTankStyle(){

}

void DriveSystem::DriveArcadeStyle(){

}

void DriveSystem::DriveSpeedMecanum(float x, float y, float z){

	drive->MecanumDrive_Cartesian(stick->GetX(), stick->GetY(), stick->GetZ());

}

void DriveSystem::StopRobot(){

	drive->StopMotor();

}

void Mech(){



}
