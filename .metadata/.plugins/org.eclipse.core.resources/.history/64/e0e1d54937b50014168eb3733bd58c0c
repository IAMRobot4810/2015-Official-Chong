#include "DriveSystem.h"
#include <math.h>

DriveSystem::DriveSystem(){

	stick  = new Joystick(0);
	stickTwo = new Joystick(1);
	direction = new Gyro(5);
	rlTal = new CANTalon(1);
	rrTal = new CANTalon(4);
	frTal = new CANTalon(3);
	flTal = new CANTalon(2);
	drive = new RobotDrive(flTal, rlTal, frTal, rrTal);
	dash->init();
	direction->InitGyro();
	drive->SetInvertedMotor(RobotDrive::kFrontRightMotor, true);
	drive->SetInvertedMotor(RobotDrive::kRearRightMotor, true);
	rlTal->SetFeedbackDevice(CANTalon::QuadEncoder);
	rrTal->SetFeedbackDevice(CANTalon::QuadEncoder);
	frTal->SetFeedbackDevice(CANTalon::QuadEncoder);
	flTal->SetFeedbackDevice(CANTalon::QuadEncoder);

}

DriveSystem::~DriveSystem(){

	delete stick;
	delete stickTwo;
	delete direction;
	delete rlTal;
	delete rrTal;
	delete frTal;
	delete flTal;
	delete drive;

}

void DriveSystem::DriveMecanumStyle(){

	sReadX = stick->GetX();
	sReadY = stick->GetY();
	sReadZ = stick->GetZ();

	talValYExp = pow(sReadY, 5);
	talValXExp = pow(sReadX, 5);
	talValZExp = pow(sReadZ, 5);

	eReadfl = flTal->GetEncVel();
	eReadfr = frTal->GetEncVel();
	eReadrl = rlTal->GetEncVel();
	eReadrr = rrTal->GetEncVel();

	//double xPrint = static_cast<float>(sReadX);
	//double yPrint = static_cast<float>(sReadY);
	//double zPrint = static_cast<float>(sReadZ);
	//double deReadfl = static_cast<int>(eReadfl);
	//double deReadfr = static_cast<int>(eReadfr);
	//double deReadrl = static_cast<int>(eReadrl);
	//double deReadrr = static_cast<int>(eReadrr);

	dash->PutNumber("Joystick X", sReadX);
	dash->PutNumber("Joystick Y", sReadY);
	dash->PutNumber("Joystick Z", sReadZ);
	dash->PutNumber("Front Left Encoder", eReadfl);
	dash->PutNumber("Front Right Encoder", eReadfr);
	dash->PutNumber("Rear Left Encoder", eReadrl);
	dash->PutNumber("Rear Right Encoder", eReadrr);

	if((sReadX < 0.5 && sReadX > -0.5) && (sReadY < 0.5 && sReadY > -0.5) && (sReadZ < 0.5 && sReadZ > -0.5)){ //Dead Bands

		drive->MecanumDrive_Cartesian(0.0, 0.0, 0.0);
		//drive->ArcadeDrive(0.0, 0.0);

	}

	else if((sReadX < 0.5 && sReadX > -0.5) && (sReadY >= 0.5) && (sReadZ < 0.5 && sReadZ > -0.5)){ //Forward Straightening

		drive->MecanumDrive_Cartesian(0.0, talValYExp, 0.0);

		if(eReadfl < eReadfr){

			for(frTalSpeed = -talValYExp; eReadfr > eReadfl; frTalSpeed+0.01){

				frTal->Set(frTalSpeed);

			}

		}

		else if(eReadfl > eReadfr){

			for(flTalSpeed = talValYExp; eReadfl > eReadfr; flTalSpeed-0.01){

				flTal->Set(flTalSpeed);

			}

		}

		else{

			flTal->Set(talValYExp);
			frTal->Set(-talValYExp);
			//drive->MecanumDrive_Cartesian(0.0, talValYExp, 0.0);

		}

		if(eReadrl < eReadrr){

			for(rrTalSpeed = -talValYExp; eReadrr > eReadrl; rrTalSpeed+0.01){

				rrTal->Set(rrTalSpeed);

			}

		}

		else if(eReadrl > eReadrr){

			for(rlTalSpeed = talValYExp; eReadrl > eReadrr; rlTalSpeed-0.01){

				rlTal->Set(rlTalSpeed);

			}

		}

		else{

			rlTal->Set(talValYExp);
			rrTal->Set(-talValYExp);

		}

	}

	else if((sReadX < 0.5 && sReadX > -0.5) && (sReadY <= -0.5) && (sReadZ < 0.5 && sReadZ > -0.5)){ //Backward Straightening

		drive->MecanumDrive_Cartesian(0.0, talValYExp, 0.0);

		if(eReadfl > eReadfr){

			for(flTalSpeed = talValYExp; eReadfr < eReadfl; flTalSpeed+0.01){

				flTal->Set(flTalSpeed);

			}

		}

		else if(eReadfl < eReadfr){

			for(frTalSpeed = -talValYExp; eReadfl < eReadfr; frTalSpeed-0.01){

				frTal->Set(frTalSpeed);

			}

		}

		else{

			flTal->Set(talValYExp);
			frTal->Set(-talValYExp);
			//drive->MecanumDrive_Cartesian(0.0, talValYExp, 0.0);

		}

		if(eReadrl > eReadrr){

			for(rlTalSpeed = talValYExp; eReadrr < eReadrl; rlTalSpeed+0.01){

				rlTal->Set(rlTalSpeed);

			}

		}

		else if(eReadrl < eReadrr){

			for(rlTalSpeed = -talValYExp; eReadrl < eReadrr; rrTalSpeed-0.01){

				rrTal->Set(rrTalSpeed);

			}

		}

		else{

			rlTal->Set(talValYExp);
			rrTal->Set(-talValYExp);

		}

	}

	else if((sReadX >= 0.5) && (sReadY < 0.5 && sReadY > -0.5) && (sReadZ < 0.5 && sReadZ > -0.5)){ //Right Straightening

		drive->MecanumDrive_Cartesian(0.0, talValXExp, 0.0);

		if(eReadfr < eReadrr){

			for(rrTalSpeed = -talValXExp; eReadrr > eReadfr; rrTalSpeed+0.01){

				rrTal->Set(rrTalSpeed);

			}

		}

		else if(eReadfr > eReadrr){

			for(frTalSpeed = talValXExp; eReadfr > eReadrr; frTalSpeed-0.01){

				frTal->Set(frTalSpeed);

			}

		}

		else{

			frTal->Set(talValXExp);
			rrTal->Set(-talValXExp);
			//drive->MecanumDrive_Cartesian(0.0, talValYExp, 0.0);

		}

		if(eReadfl < eReadrl){

			for(rlTalSpeed = -talValXExp; eReadrl > eReadfl; rlTalSpeed+0.01){

				rlTal->Set(rlTalSpeed);

			}

		}

		else if(eReadfl > eReadrl){

			for(flTalSpeed = talValXExp; eReadfl > eReadrl; flTalSpeed-0.01){

				flTal->Set(flTalSpeed);

			}

		}

		else{

			flTal->Set(talValXExp);
			rlTal->Set(-talValXExp);

		}

	}

	else if((sReadX <= -0.5) && (sReadY < 0.5 && sReadY > -0.5) && (sReadZ < 0.5 && sReadZ > -0.5)){ //Left Straightening

		drive->MecanumDrive_Cartesian(talValXExp, 0.0, 0.0);

		if(eReadfr < eReadrr){

			for(rrTalSpeed = -talValXExp; eReadrr > eReadfr; rrTalSpeed-0.01){

				rrTal->Set(rrTalSpeed);

			}

		}

		else if(eReadfr > eReadrr){

			for(frTalSpeed = talValXExp; eReadfr > eReadrr; frTalSpeed+0.01){

				frTal->Set(frTalSpeed);

			}

		}

		else{

			frTal->Set(talValXExp);
			rrTal->Set(-talValXExp);
			//drive->MecanumDrive_Cartesian(0.0, talValYExp, 0.0);

		}

		if(eReadfl < eReadrl){

			for(rlTalSpeed = -talValXExp; eReadrl > eReadfl; rlTalSpeed-0.01){

				rlTal->Set(rlTalSpeed);

			}

		}

		else if(eReadfl > eReadrl){

			for(flTalSpeed = talValXExp; eReadfl > eReadrl; flTalSpeed+0.01){

				flTal->Set(flTalSpeed);

			}

		}

		else{

			flTal->Set(talValXExp);
			rlTal->Set(-talValXExp);

		}

	}

	else if((sReadX < 0.5 && sReadX > -0.5) && (sReadY < 0.5 && sReadY > -0.5) && (sReadZ >= 0.5)){ //Right Turn Straightening

		drive->MecanumDrive_Cartesian(0.0, 0.0, talValZExp);

		if(eReadfl < eReadfr){

			for(frTalSpeed = talValZExp; eReadfr > eReadfl; frTalSpeed-0.01){

				frTal->Set(frTalSpeed);

			}

		}

		else if(eReadfl > eReadfr){

			for(flTalSpeed = talValZExp; eReadfl > eReadfr; flTalSpeed-0.01){

				flTal->Set(flTalSpeed);

			}

		}

		else{

			flTal->Set(talValZExp);
			frTal->Set(talValZExp);
			//drive->MecanumDrive_Cartesian(0.0, talValYExp, 0.0);

		}

		if(eReadrl < eReadrr){

			for(rrTalSpeed = talValZExp; eReadrr > eReadrl; rrTalSpeed-0.01){

				rrTal->Set(rrTalSpeed);

			}

		}

		else if(eReadrl > eReadrr){

			for(rlTalSpeed = talValZExp; eReadrl > eReadrr; rlTalSpeed-0.01){

				rlTal->Set(rlTalSpeed);

			}

		}

		else{

			rlTal->Set(talValZExp);
			rrTal->Set(talValZExp);

		}

	}

	else if((sReadX < 0.5 && sReadX > -0.5) && (sReadY < 0.5 && sReadY > -0.5) && (sReadZ <= -0.5)){ //Left Turn Straightening

		drive->MecanumDrive_Cartesian(0.0, 0.0, talValZExp);

		if(eReadfl < eReadfr){

			for(frTalSpeed = talValZExp; eReadfr > eReadfl; frTalSpeed+0.01){

				frTal->Set(frTalSpeed);

			}

		}

		else if(eReadfl > eReadfr){

			for(flTalSpeed = talValZExp; eReadfl > eReadfr; flTalSpeed+0.01){

				flTal->Set(flTalSpeed);

			}

		}

		else{

			flTal->Set(talValZExp);
			frTal->Set(talValZExp);
			//drive->MecanumDrive_Cartesian(0.0, talValYExp, 0.0);

		}

		if(eReadrl < eReadrr){

			for(rrTalSpeed = talValZExp; eReadrr > eReadrl; rrTalSpeed+0.01){

				rrTal->Set(rrTalSpeed);

			}

		}

		else if(eReadrl > eReadrr){

			for(rlTalSpeed = talValZExp; eReadrl > eReadrr; rlTalSpeed+0.01){

				rlTal->Set(rlTalSpeed);

			}

		}

		else{

			rlTal->Set(talValZExp);
			rrTal->Set(talValZExp);

		}

	}

	else{

		drive->MecanumDrive_Cartesian(talValXExp, talValYExp, talValZExp);
		//drive->ArcadeDrive(talValYExp, talValXExp);

	}

}

void DriveSystem::DriveMecanumStyleGyro(){

	sReadX = stick->GetX();
	sReadY = stick->GetY();
	sReadZ = stick->GetZ();

	talValYExp = pow(sReadY, 5);
	talValXExp = pow(sReadX, 5);
	talValZExp = pow(sReadZ, 5);

	gyrRead = direction->GetAngle();

	dash->PutNumber("Joystick X", sReadX);
	dash->PutNumber("Joystick Y", sReadY);
	dash->PutNumber("Joystick Z", sReadZ);
	dash->PutNumber("Gyroscope Angle Reading", gyrRead);

	if((sReadX < 0.5 && sReadX > -0.5) && (sReadY < 0.5 && sReadY > -0.5) && (sReadZ < 0.5 && sReadZ > -0.5)){ //Dead Bands

		drive->MecanumDrive_Cartesian(0.0, 0.0, 0.0, gyrRead);
		//drive->ArcadeDrive(0.0, 0.0);

	}

	else if((sReadX < 0.5 && sReadX > -0.5) && (sReadY >= 0.5 || sReadY <= -0.5) && (sReadZ < 0.5 && sReadZ > -0.5)){

		drive->MecanumDrive_Cartesian(0.0, talValYExp, 0.0, gyrRead);

	}

	else if((sReadX >= 0.5 || sReadX <= -0.5) && (sReadY < 0.5 && sReadY > -0.5) && (sReadZ < 0.5 && sReadZ > -0.5)){

		drive->MecanumDrive_Cartesian(0.0, talValYExp, 0.0, gyrRead);

	}

	else if((sReadX < 0.5 && sReadX > -0.5) && (sReadY < 0.5 && sReadY > -0.5) && (sReadZ >= 0.5 || sReadZ <= -0.5)){

		drive->MecanumDrive_Cartesian(0.0, talValYExp, 0.0, gyrRead);

	}

	else{

		drive->MecanumDrive_Cartesian(talValXExp, talValYExp, talValZExp, gyrRead);
		//drive->ArcadeDrive(talValYExp, talValXExp);

	}

}

void DriveSystem::DriveTankStyle(){

	drive->TankDrive(stickTwo, stick);

}

void DriveSystem::DriveArcadeStyle(){

	drive->ArcadeDrive(stick);

}

void DriveSystem::DriveSpeedMecanum(float x, float y, float z){

	drive->MecanumDrive_Cartesian(x, y, z /*stick->GetX(), stick->GetY(), stick->GetZ()*/);

}

void DriveSystem::DriveSpeedArcade(float movSpeed, float rotSpeed){

	drive->ArcadeDrive(movSpeed,rotSpeed);

}

void DriveSystem::DriveSpeedTank(float lSpeed, float rSpeed){

	drive->TankDrive(lSpeed, rSpeed);

}

void DriveSystem::StopRobot(){

	drive->StopMotor();

}
