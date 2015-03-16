#include "WPILib.h"
#include "Lifter.h"

class Robot: public IterativeRobot
{

public:

	Joystick *stick;
	/*JoystickButton *jb7;
	JoystickButton *jb8;
	JoystickButton *jb9;
	JoystickButton *jb10;
	JoystickButton *jb11;
	JoystickButton *jb12;*/

	//Lifter *lift;
	Compressor *comp;
	Solenoid *sol;
	DoubleSolenoid *arm;
	CANTalon *tal6;
	CANTalon *tal5;
	DigitalInput *limit;
	SmartDashboard *dash;

	Robot(){

		stick = new Joystick(0);

		//lift = new Lifter();
		comp = new Compressor(1);
		sol = new Solenoid(1, 0);
		arm = new DoubleSolenoid(1, 1, 2);
		tal6 = new CANTalon(6);
		tal5 = new CANTalon(5);
		limit = new DigitalInput(0);
		dash->init();

	}

	~Robot(){

		delete stick;

		//delete lift;
		delete comp;
		delete sol;
		delete arm;
		delete tal6;
		delete tal5;
		delete limit;

	}

private:

	LiveWindow *lw;
	const bool jb7Hit = true;
	const bool jb8Hit = true;
	bool jb9Hit = false;
	bool jb10Hit = false;
	bool jb11Hit = false;
	bool jb12Hit = false;

	void RobotInit(){

		lw = LiveWindow::GetInstance();

	}

	void AutonomousInit(){

	}

	void AutonomousPeriodic(){

	}

	void TeleopInit(){

	}

	void TeleopPeriodic(){

		/*if(stick->GetRawButton(3)){
			sol->Set(true);
					tal5->Set(-0.25);
					tal6->Set(-0.25);
				}

				else if(stick->GetRawButton(4)){
					sol->Set(true);
					tal5->Set(-0.03);
					tal6->Set(-0.03);
				}

				else if(stick->GetRawButton(5)){
					tal5->Set(0.0);
					tal6->Set(0.0);
					sol->Set(false);
				}

		if(stick->GetRawButton(9)){
			jb9Hit = true;
		}

		if(stick->GetRawButton(10)){
			jb10Hit = true;
		}*/

		if(stick->GetRawButton(11)){
			arm->Set(DoubleSolenoid::kForward);
			//jb11Hit = true;
		}
		if(stick->GetRawButton(12)){
			arm->Set(DoubleSolenoid::kReverse);
			//jb12Hit = true;
		}

		/*if(jb9Hit == true){
			lift->SetLevel(Lifter::TOP);
			jb9Hit = false;
		}

		if(jb10Hit == true){
			lift->SetLevel(Lifter::GROUND);
			jb10Hit = false;
		}

		if(jb11Hit == true){
			lift->SetArmpos(Lifter::OPEN);
			//arm->Set(DoubleSolenoid::kForward);
			jb11Hit = false;
		}

		if(jb12Hit == true){
			lift->SetArmpos(Lifter::CLOSE);
			//arm->Set(DoubleSolenoid::kReverse);
			jb12Hit = false;
		}*/

		float armSpeed = (stick->GetThrottle()/2) + 0.5;

		if(stick->GetRawButton(7) == jb7Hit && stick->GetRawButton(8) != jb8Hit && limit->Get()) {
			sol->Set(true);
			tal5->Set(-armSpeed);
			tal6->Set(-armSpeed);
		}
		else if(stick->GetRawButton(8) != jb8Hit && !limit->Get() && stick->GetRawButton(7) == jb7Hit){
			tal5->Set(0.0);
			tal6->Set(0.0);
			sol->Set(false);
		}
		else if(stick->GetRawButton(8) == jb8Hit && stick->GetRawButton(7) != jb7Hit){
			sol->Set(true);
			tal5->Set(0.0);
			tal6->Set(0.0);
		}
		else if(stick->GetRawButton(7) != jb7Hit && stick->GetRawButton(8) != jb8Hit){
			tal5->Set(0.0);
			tal6->Set(0.0);
			sol->Set(false);
		}
		else if(stick->GetRawButton(7) == jb7Hit && stick->GetRawButton(8) == jb8Hit){
			tal5->Set(0.0);
			tal6->Set(0.0);
			sol->Set(false);
		}

	}

	void TestPeriodic(){

		lw->Run();

	}


};

START_ROBOT_CLASS(Robot);