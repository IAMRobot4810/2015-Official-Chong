#include "WPILib.h"

class Robot: public IterativeRobot
{
	Encoder *encoder;
	Talon *talon1;
	Talon *talon2;
	Talon *talon3;
	Talon *talon4;
	Joystick *joystick;
	RobotDrive *robotDrive;
	SmartDashboard *smartDashboard;
	AnalogInput *analoginput;

	Robot(){

		encoder = new Encoder(1, 2, false);
		talon1 = new Talon(1);
		talon2 = new Talon(2);
		talon3 = new Talon(3);
		talon4 = new Talon(4);
		robotDrive = new RobotDrive(talon1, talon2, talon3, talon4);
		joystick = new Joystick();
		smartDashboard->init();
		analoginput = new AnalogInput(1);
	}

	~Robot(){
		delete encoder;
		delete talon1;
		delete talon2;
		delete talon3;
		delete talon4;
		delete robotDrive;
		delete joystick;
		delete analoginput;
	}
private:
	LiveWindow *lw;

	void RobotInit()
	{
		lw = LiveWindow::GetInstance();
	}

	void AutonomousInit()
	{

	}

	void AutonomousPeriodic()
	{

	}

	void TeleopInit()
	{

	}

	void TeleopPeriodic()
	{

		double rate = encoder->GetRate();
		// robotDrive->ArcadeDrive(joystick);
		robotDrive->MecanumDrive_Cartesian(joystick->GetX(), joystick->GetY(), joystick->GetZ());
		smartDashboard->PutNumber("value", rate);
		smartDashboard->PutNumber("voltage", analoginput->GetVoltage());

	}

	void TestPeriodic()
	{
		lw->Run();
	}
};

START_ROBOT_CLASS(Robot);
