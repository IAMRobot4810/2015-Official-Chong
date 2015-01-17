#include "DriveSystem.h"
#include "math.h"

DriveSystem::DriveSystem(){

	stick  = new Joystick(0);
	stickTwo = new Joystick(1);
	talOneEnco = new Encoder(5, 6);
	talTwoEnco = new Encoder(7, 8); //Change inputs for both of these.
	talZero = new Talon(0);
	talOne = new Talon(1);
	talTwo = new Talon(2);
	talThree = new Talon(3);
	drive = new RobotDrive(talTwo, talThree, talOne, talZero);
	//dash = NULL;
	dash->init();
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


}

void DriveSystem::DriveArcadeStyle(){

	sReadX = stick->GetX();
	sReadY = stick->GetY();
	//sReadZ = stick->GetZ();
	eRead = talOneEnco->GetRaw();
	eReadTwo = talTwoEnco->GetRaw();

	/*talValYExp = pow(sReadY, 5);
	talValXExp = pow(sReadX, 3);*/

	double deRead = static_cast<int>(eRead);
	double deReadTwo = static_cast<int>(eReadTwo);

	dash->PutNumber("encoval",deRead);
	dash->PutNumber("encovaltwo",deReadTwo);


	/*if((sReadX <= 0.5 && sReadX >= -0.5) && (sReadY <= 0.5 && sReadY >= -0.5)){

		drive->StopMotor();

	}

	else if((sReadX >= 0.5 || sReadX <= -0.5) && (sReadY <= 0.5 && sReadY >= -0.5)){

		drive->ArcadeDrive(talValYExp, 0.0, false);

		if(eRead < eReadTwo){

			//for(float talTwoSpeed = talTwo ->;)

		}

		else if(eRead > eReadTwo){

		}

		else{

		}

	}

	else if((sReadX >= 0.5 || sReadX <= -0.5) && (sReadY >= 0.5 && sReadY <= -0.5)){

		drive->ArcadeDrive(talValYExp, talValXExp, false);


	}*/

}

void DriveSystem::DriveMecanumStyle(){

	//&& (sReadZ <= 0.25 && sReadZ >= -0.25)

}

void DriveSystem::DriveTankStyle(){

}

