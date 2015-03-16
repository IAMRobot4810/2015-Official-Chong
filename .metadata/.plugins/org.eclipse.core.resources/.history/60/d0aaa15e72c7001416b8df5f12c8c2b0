#include "WPILib.h"
#include "DriveSystem.h"

class Robot: public IterativeRobot
{

public:

	SmartDashboard *sD;
	/*Joystick *stick;
	CANTalon *fl;
	CANTalon *rl;
	CANTalon *fr;
	CANTalon *rr;
	RobotDrive *dr;*/
	DriveSystem *driveBro;
	SerialPort *sp;
	char *buff;
	int buffread;
	AnalogInput *aPot;
	AnalogPotentiometer *sPot;
	//Compressor *comp;

	Robot(){

	}

	~Robot(){

		/*delete stick;
		delete fl;
		delete rl;
		delete fr;
		delete rr;
		delete dr*/;
		delete driveBro;
		delete sp;
		delete buff;
		delete aPot;
		delete sPot;
		//delete comp;
	}

private:

	double sPotGet;

	LiveWindow *lw;

	void RobotInit()
	{

		sD->init();
		/*stick = new Joystick(0);
		fl = new CANTalon(3);
		rl = new CANTalon(1);
		fr = new CANTalon(2);
		rr = new CANTalon(4);
		dr = new RobotDrive(fl, rl, fr, rr);
		dr->SetInvertedMotor(RobotDrive::kFrontRightMotor, true);
		dr->SetInvertedMotor(RobotDrive::kRearRightMotor, true);
		dr->SetSafetyEnabled(false);*/
		driveBro = new DriveSystem();
		sp = new SerialPort(9600, SerialPort::kUSB);
		buff = new char[2];
		aPot = new AnalogInput(0);
		sPot = new AnalogPotentiometer(aPot, 1.0, 0.0);
		//comp = new Compressor(1);
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

		sPotGet = sPot->Get();

		sD->PutNumber("String Potentiometer", sPotGet);

		sp->Read(buff, 1);
		buffread = (int) buff[0];
		std::string heybuff(buff);

		sD->PutString("Buffer: ", heybuff);
		sD->PutNumber("Converted: ", buffread);

		driveBro->DriveMecanumStyleEncoder();
		/*for(float x = 0.0; x <= 1.0; x+=0.0001){
			fl->Set(x);
			rl->Set(x);
			fr->Set(x);
			rr->Set(x);
			sD->PutNumber("talSpeed", x);
		}*/
	}

	void TestPeriodic()
	{
		lw->Run();
	}
};

START_ROBOT_CLASS(Robot);
