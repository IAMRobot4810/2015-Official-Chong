#include "WPILib.h"
#include "Buttons/JoystickButton.h"

#include <math.h>

class Robot: public IterativeRobot
{
public:
	~Robot();

	LiveWindow *lw;

	Joystick* j;

	SmartDashboard* dash;

	JoystickButton* level1;
	JoystickButton* level2;
	JoystickButton* level3;
	JoystickButton* level4;
	JoystickButton* level5;
	JoystickButton* level6;

	JoystickButton* level0;

	RobotDrive* myRobot;
	Talon* talon0;
	Talon* talon1;
	Talon* talon2;
	Talon* talon3;

	BuiltInAccelerometer* accel;

private:

	void RobotInit();
	void AutonomousInit();
	void AutonomousPeriodic();
	void TeleopPeriodic();
	void TeleopInit();
	void TestPeriodic();

	float takePower(float init);


};

Robot::~Robot()
{
	delete j;

	delete level1;
	delete level2;
	delete level3;
	delete level4;
	delete level5;
	delete level6;

	delete level0;

	delete accel;
}

void Robot::RobotInit()
{
	lw = LiveWindow::GetInstance();

	j = new Joystick(0);

	dash = NULL;

	level1 = new JoystickButton(j, 7);
	level2 = new JoystickButton(j, 8);
	level3 = new JoystickButton(j, 9);
	level4 = new JoystickButton(j, 10);
	level5 = new JoystickButton(j, 11);
	level6 = new JoystickButton(j, 12);

	level0 = new JoystickButton(j, 1);

	talon0 = new Talon(0);
	talon1 = new Talon(1);
	talon2 = new Talon(2);
	talon3 = new Talon(3);

	myRobot = new RobotDrive(talon2, talon3, talon1, talon0);
	myRobot->SetInvertedMotor(RobotDrive::kFrontRightMotor, true);
	myRobot->SetInvertedMotor(RobotDrive::kRearRightMotor, true);

	accel = new BuiltInAccelerometer();
}

void Robot::AutonomousInit()
{

}

void Robot::AutonomousPeriodic()
{

}

void Robot::TeleopInit()
{

}

void Robot::TeleopPeriodic()
{
	lw->Run();
	dash->init();

	//myRobot->MecanumDrive_Cartesian(j->GetX(), j->GetY(), j->GetZ());
	//levels
	std::string s = "Go to Level: ";

	dash->PutString(s, "");

	if(level1->Get())
	{
		dash->PutString(s, "1");
	}
	if(level2->Get())
	{
		dash->PutString(s, "2");
	}
	if(level3->Get())
	{
		dash->PutString(s, "3");
	}
	if(level4->Get())
	{
		dash->PutString(s, "4");
	}
	if(level5->Get())
	{
		dash->PutString(s, "5");
	}
	if(level6->Get())
	{
		dash->PutString(s, "6");
	}
	if(level0->Get())
	{
		dash->PutString(s, "Ground");
	}

	//fine tuner
	int direction = j->GetPOV();
	std::string t = "Fine tune direction: ";
	dash->PutString(t, "");
	if(direction == 0)
	{
		dash->PutString(t, "Up");
	}
	if(direction == 180)
	{
		dash->PutString(t, "Down");
	}

	//throttle control
	std::string u = "Throttle Value: ";

	double value = static_cast<float>(j->GetY());

	dash->PutNumber(u, value);

	float jYVal = j->GetY();
	float jXVal = j->GetX();
	float jZVal = j->GetZ();
	//float YMotVal = 2*(jYVal - 0.5);

	if((jYVal <= 0.5 && jYVal >= -0.5) && (jXVal <= 0.5 && jXVal >= -0.5) && (jZVal <= 0.5 && jZVal >= -0.5))
	{
		myRobot->StopMotor();

	}
	else
	{



		myRobot->MecanumDrive_Cartesian(takePower(jXVal), takePower(jYVal), takePower(jZVal));

	}


	double xAccel = accel->GetX();
	double yAccel = accel->GetY();
	double zAccel = accel->GetZ();


	dash->PutNumber("X-accel", xAccel);
	dash->PutNumber("Y-accel", yAccel);
	dash->PutNumber("Z-accel", zAccel);


}

void Robot::TestPeriodic()
{

}

float Robot::takePower(float init)
{
	return pow(init, 3);
}

START_ROBOT_CLASS(Robot);
