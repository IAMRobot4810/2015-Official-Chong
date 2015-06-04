#include "WPILib.h"

class Robot: public IterativeRobot
{

public:

	SmartDashboard *sD;
	Joystick *stick;
	CANTalon *fl;
	CANTalon *rl;
	CANTalon *fr;
	CANTalon *rr;
	RobotDrive *drive;
	/*DriveSystem *driveBro;
	SerialPort *sp;
	char *buff;
	int buffread;
	AnalogInput *aPot;
	AnalogPotentiometer *sPot;*/
	//Compressor *comp;

	Robot(){

	}

	~Robot(){

		delete stick;
		delete fl;
		delete rl;
		delete fr;
		delete rr;
		delete drive;
		/*delete driveBro;
		delete sp;
		delete buff;
		delete aPot;
		delete sPot;*/
		//delete comp;
	}

private:

	double sPotGet;
	double sPotConvert;

	LiveWindow *lw;

	void RobotInit()
	{

		sD->init();
		stick = new Joystick(0);
		fl = new CANTalon(3);
		rl = new CANTalon(1);
		fr = new CANTalon(2);
		rr = new CANTalon(4);
		drive = new RobotDrive(fl, rl, fr, rr);
		drive->SetInvertedMotor(RobotDrive::kFrontRightMotor, true);
		drive->SetInvertedMotor(RobotDrive::kRearRightMotor, true);
		drive->SetSafetyEnabled(false);
		/*driveBro = new DriveSystem();
		sp = new SerialPort(9600, SerialPort::kUSB);
		buff = new char[2];
		aPot = new AnalogInput(0);
		sPot = new AnalogPotentiometer(aPot, 1.0, 0.0);*/
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

		float stickX = stick->GetX();
		float stickY = stick->GetY();
		float stickZ = stick->GetZ();

		float sXExp = pow(stickX, 5);
		float sYExp = pow(stickY, 5);
		float sZExp = (pow(stickZ, 3)/3);

		/*sPotGet = sPot->Get();
		sPotConvert = 92.65734 * sPotGet - 26.17133;

		sD->PutNumber("String Potentiometer Raw", sPotGet);
		sD->PutNumber("Lifter Height (Inches)", sPotConvert);

		sp->Read(buff, 1);
		buffread = (int) buff[0];
		std::string heybuff(buff);

		sD->PutString("Buffer: ", heybuff);
		sD->PutNumber("Converted: ", buffread);*/

		if((stickX > -0.5 && stickX < 0.5) && (stickY > -0.5 && stickY < 0.5) && (stickZ > -0.25 && stickZ < 0.25)){
			drive->MecanumDrive_Cartesian(0.0, 0.0, 0.0);
		}

		else if((stickX > -0.5 && stickX < 0.5) && (stickY <= -0.5 || stickY >= 0.5) && (stickZ > -0.25 && stickZ < 0.25)){
			drive->MecanumDrive_Cartesian(0.0, sYExp, 0.0);
		}

		else if((stickX <= -0.5 || stickX >= 0.5) && (stickY > -0.5 && stickY < 0.5) && (stickZ > -0.25 && stickZ < 0.25)){
			drive->MecanumDrive_Cartesian(sXExp, 0.0, 0.0);
		}

		else if((stickX > -0.5 && stickX < 0.5) && (stickY > -0.5 && stickY < 0.5) && (stickZ <= -0.25 && stickZ >= 0.25)){
			drive->MecanumDrive_Cartesian(0.0, 0.0, sZExp);
		}

		else{
			drive->MecanumDrive_Cartesian(sXExp, sYExp, sZExp);
		}

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
