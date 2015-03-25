#include "WPILib.h"
#include <cmath>

class Robot: public IterativeRobot
{
public:

	Joystick *stick;

	CANTalon *flTal;
	CANTalon *rlTal;
	CANTalon *frTal;
	CANTalon *rrTal;
	RobotDrive *drive;
	SmartDashboard *dash;

	Robot(){

		stick = new Joystick(0);

		flTal = new CANTalon(3);
		rlTal = new CANTalon(1);
		frTal = new CANTalon(2);
		rrTal = new CANTalon(4);
		drive = new RobotDrive(flTal, rlTal, frTal, rrTal);

		drive->SetInvertedMotor(RobotDrive::kFrontRightMotor, true);
		drive->SetInvertedMotor(RobotDrive::kRearRightMotor, true);
		drive->SetSafetyEnabled(false);
		flTal->SetFeedbackDevice(CANTalon::QuadEncoder);
		rlTal->SetFeedbackDevice(CANTalon::QuadEncoder);
		frTal->SetFeedbackDevice(CANTalon::QuadEncoder);
		rrTal->SetFeedbackDevice(CANTalon::QuadEncoder);
		frTal->SetSensorDirection(true);
		rrTal->SetSensorDirection(true);

		dash->init();


	}

	~Robot(){

		delete stick;

		delete flTal;
		delete rlTal;
		delete frTal;
		delete rrTal;
		delete drive;

	}

private:

	LiveWindow *lw;

	bool jb1Hit = false;
	const bool jb3Hit = true;
	const bool jb5Hit = true;

	int flRead = 0;
	int rlRead = 0;
	int frRead = 0;
	int rrRead = 0;

	double liftRate;

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

		flRead = flTal->GetEncVel();
		rlRead = rlTal->GetEncVel();
		frRead = frTal->GetEncVel();
		rrRead = rrTal->GetEncVel();

		float stickX = stick->GetX();
		float stickY = stick->GetY();
		float stickZ = stick->GetZ();

		float sXExp = pow(stickX, 5);
		float sYExp = pow(stickY, 5);
		float sZExp = (pow(stickZ, 3)/3);

		float flCur = flTal->GetOutputCurrent();
		float rlCur = rlTal->GetOutputCurrent();
		float frCur = frTal->GetOutputCurrent();
		float rrCur = rrTal->GetOutputCurrent();

		float flVolt = flTal->GetOutputVoltage();
		float rlVolt = rlTal->GetOutputVoltage();
		float frVolt = frTal->GetOutputVoltage();
		float rrVolt = rrTal->GetOutputVoltage();

		dash->PutNumber("Stick X", stickX);
		dash->PutNumber("Stick Y", stickY);
		dash->PutNumber("Stick Z", stickZ);

		dash->PutNumber("Front Left Encoder", flRead);
		dash->PutNumber("Rear Left Encoder", rlRead);
		dash->PutNumber("Front Right Encoder", frRead);
		dash->PutNumber("Rear Right Encoder", rrRead);

		dash->PutNumber("Front Left Current", flCur);
		dash->PutNumber("Rear Left Current", rlCur);
		dash->PutNumber("Front Right Current", frCur);
		dash->PutNumber("Rear Right Current", rrCur);

		dash->PutNumber("Front Left Voltage", flVolt);
		dash->PutNumber("Rear Left Voltage", rlVolt);
		dash->PutNumber("Front Right Voltage", frVolt);
		dash->PutNumber("Rear Right Voltage", rrVolt);

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

	}

	void TestPeriodic()
	{
		lw->Run();
	}
};

START_ROBOT_CLASS(Robot);
