#include "WPILib.h"
#include "DriveSystem.h"
#include "Lifter.h"

class Robot: public IterativeRobot
{

public:

	Joystick *stick;
	Joystick *stickTwo;
	JoystickButton *jb3;
	JoystickButton *jb4;
	JoystickButton *jb5;
	JoystickButton *jb6;
	JoystickButton *jb7;
	JoystickButton *jb8;
	JoystickButton *jb9;
	JoystickButton *jb10;
	JoystickButton *jb11;
	JoystickButton *jb12;

	DriveSystem *driveBro;
	Lifter *liftBro;
	SmartDashboard *dashT;

	Robot(){

	}

	~Robot(){

		liftBro->SetLevel(Lifter::GROUND);
		delete stick;
		delete stickTwo;
		delete jb3;
		delete jb4;
		delete jb5;
		delete jb6;
		delete jb7;
		delete jb8;
		delete jb9;
		delete jb10;
		delete jb11;
		delete jb12;

		delete driveBro;
		delete liftBro;

	}

private:

	LiveWindow *lw;

	void RobotInit(){

		stick = new Joystick(0);
		stickTwo = new Joystick(1);
		jb3 = new JoystickButton(stick, 3);
		jb4 = new JoystickButton(stick, 4);
		jb5 = new JoystickButton(stick, 5);
		jb6 = new JoystickButton(stick, 6);
		jb7 = new JoystickButton(stick, 7);
		jb8 = new JoystickButton(stick, 8);
		jb9 = new JoystickButton(stick, 9);
		jb10 = new JoystickButton(stick, 10);
		jb11 = new JoystickButton(stick, 11);
		jb12 = new JoystickButton(stick, 12);

		driveBro = new DriveSystem();
		liftBro = new Lifter();
		dashT->init();

		lw = LiveWindow::GetInstance();

	}

	void AutonomousInit(){

	}

	void AutonomousPeriodic(){

	}

	void TeleopInit(){

	}

	void TeleopPeriodic(){

		driveBro->DriveMecanumStyle();
		//driveBro->DriveSpeedMecanum(stick->GetX(), stick->GetY(), stick->GetZ());
		//driveBro->DriveMecanumStyleGyro();

		if(jb3->Get()){

			liftBro->SetArmpos(Lifter::OPEN);

		}

		else if(jb4->Get()){

			liftBro->SetArmpos(Lifter::BOXWIDE);

		}

		else if(jb5->Get()){

			liftBro->SetArmpos(Lifter::BOXSHORT);

		}

		else if(jb6->Get()){

			liftBro->SetArmpos(Lifter::GARBAGECAN);

		}

		else if(jb7->Get()){

			liftBro->SetLevel(Lifter::GROUND);

		}

		else if(jb8->Get()){

			liftBro->SetLevel(Lifter::UNDERBOXONE);

		}

		else if(jb9->Get()){

			liftBro->SetLevel(Lifter::INBETWEEN);

		}

		else if(jb10->Get()){

			liftBro->SetLevel(Lifter::OVERBOXTWO);

		}

		else if(jb11->Get()){

			liftBro->SetLevel(Lifter::GETGARBAGECAN);

		}

		else if(jb12->Get()){

			liftBro->SetLevel(Lifter::TOP);

		}

	}

	void TestPeriodic(){

		lw->Run();

	}


};

START_ROBOT_CLASS(Robot);
