#include "WPILib.h"
#include <cmath>

class Robot: public IterativeRobot
{

public:

	AnalogInput *sPot;
	AnalogPotentiometer *aPot;
	SmartDashboard *sD;
	CANTalon *tal6;
	CANTalon *tal5;
	Joystick *stick;
	JoystickButton *but3;
	JoystickButton *but4;
	JoystickButton *but5;

	Robot(){

	}

	~Robot(){
		delete sPot;
		delete aPot;
		delete tal6;
		delete tal5;
		delete stick;
		delete but3;
		delete but4;
		delete but5;
	}

private:
	LiveWindow *lw;

	void RobotInit()
	{
		sPot = new AnalogInput(3);
		aPot = new AnalogPotentiometer(sPot, 1.0, 0.0);
		sD->init();
		tal6 = new CANTalon(6);
		tal5 = new CANTalon(5);
		stick = new Joystick(0);
		but3 = new JoystickButton(stick, 3);
		but4 = new JoystickButton(stick, 4);
		but5 = new JoystickButton(stick, 5);
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

		double val1 = aPot->Get();
		float val2 = sPot->GetVoltage();

		float scale = abs(-85.2459*val1+23.90984);

		sD->PutNumber("Get", val1);
		sD->PutNumber("GetVoltage", val2);
		sD->PutNumber("GetValue", sPot->GetValue());
		sD->PutNumber("ScaledVal", scale);

		if(but3->Get()){
			tal5->Set(-0.25);
			tal6->Set(-0.25);
		}

		else if(but4->Get()){
			tal5->Set(0.25);
			tal6->Set(0.25);
		}

		else if(but5->Get()){
			tal5->Set(0.0);
			tal6->Set(0.0);
		}
	}

	void TestPeriodic()
	{
		lw->Run();
	}
};

START_ROBOT_CLASS(Robot);
