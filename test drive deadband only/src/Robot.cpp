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
	//Gyro *gy;
	BuiltInAccelerometer *acc;

	Compressor *comp;
	Solenoid *sol;
	Solenoid *arm;
	CANTalon *tal6;
	CANTalon *tal5;
	//DigitalInput *limit;
	AnalogPotentiometer *sPot;
	SmartDashboard *dash;

	Robot(){

		stick = new Joystick(0);

		flTal = new CANTalon(3);
		rlTal = new CANTalon(1);
		frTal = new CANTalon(2);
		rrTal = new CANTalon(4);
		drive = new RobotDrive(flTal, rlTal, frTal, rrTal);
		//gy = new Gyro(0);
		acc = new BuiltInAccelerometer();

		comp = new Compressor(1);
		sol = new Solenoid(1, 4);
		arm = new Solenoid(1, 5);
		tal6 = new CANTalon(6);
		tal5 = new CANTalon(5);
		//limit = new DigitalInput(0);
		sPot = new AnalogPotentiometer(0, 1.0, 0.0);

		drive->SetInvertedMotor(RobotDrive::kFrontRightMotor, true);
		drive->SetInvertedMotor(RobotDrive::kRearRightMotor, true);
		drive->SetSafetyEnabled(false);
		flTal->SetFeedbackDevice(CANTalon::QuadEncoder);
		rlTal->SetFeedbackDevice(CANTalon::QuadEncoder);
		frTal->SetFeedbackDevice(CANTalon::QuadEncoder);
		rrTal->SetFeedbackDevice(CANTalon::QuadEncoder);
		//gy->InitGyro();

		dash->init();


	}

	~Robot(){

		delete stick;

		delete flTal;
		delete rlTal;
		delete frTal;
		delete rrTal;
		delete drive;
		//delete gy;
		delete acc;

		delete comp;
		delete sol;
		delete arm;
		delete tal6;
		delete tal5;
		//delete limit;
		delete sPot;

	}

private:

	LiveWindow *lw;

	bool jb1Hit = false;
	const bool jb3Hit = true;
	const bool jb5Hit = true;

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


		arm->Set(DoubleSolenoid::kReverse);
		//bool jb1Hit = false;
		//tal5->SetVoltageRampRate(2);
		//dash->PutBoolean("Gyroscope On", true);

	}

	void TeleopPeriodic()
	{

		int flRead = flTal->GetEncVel();
		int rlRead = rlTal->GetEncVel();
		int frRead = frTal->GetEncVel();
		int rrRead = rrTal->GetEncVel();

		//float gyrAngle;

		/*if(dash->GetBoolean("Gyroscope On") == true){
			gyrAngle = gy->GetAngle();
		}

		else if(dash->GetBoolean("Gyroscope On") == false){
			gyrAngle = 0;
		}

		else{
			dash->PutBoolean("Gyroscope On", true);
			gyrAngle = gy->GetAngle();
		}*/

		double roll = acc->GetX();
		double pitch = acc->GetY();
		double yaw = acc->GetZ();

		float stickX = stick->GetX();
		float stickY = stick->GetY();
		float stickZ = stick->GetZ();

		float sXExp = pow(stickX, 5);
		float sYExp = pow(stickY, 5);
		float sZExp = (pow(stickZ, 3)/2);

		float flCur = flTal->GetOutputCurrent();
		float rlCur = rlTal->GetOutputCurrent();
		float frCur = frTal->GetOutputCurrent();
		float rrCur = rrTal->GetOutputCurrent();

		float flVolt = flTal->GetOutputVoltage();
		float rlVolt = rlTal->GetOutputVoltage();
		float frVolt = frTal->GetOutputVoltage();
		float rrVolt = rrTal->GetOutputVoltage();

		float sPotRead = sPot->Get();
		float sInch = abs(92.65734 * sPotRead - 26.17133);
		//float sInch = abs(-85.2459*sPotRead+23.90984);

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

		dash->PutNumber("String Read", sPotRead);
		dash->PutNumber("Height (Inches)", sInch);

		//dash->PutNumber("GyroAngle", gyrAngle);
		dash->PutNumber("Roll", roll);
		dash->PutNumber("Pitch", pitch);
		dash->PutNumber("Yaw", yaw);

		if((stickX > -0.5 && stickX < 0.5) && (stickY > -0.5 && stickY < 0.5) && (stickZ > -0.25 && stickZ < 0.25)){
			drive->MecanumDrive_Cartesian(0.0, 0.0, 0.0/*, gyrAngle*/);
		}

		else if((stickX > -0.5 && stickX < 0.5) && (stickY <= -0.5 || stickY >= 0.5) && (stickZ > -0.25 && stickZ < 0.25)){
			drive->MecanumDrive_Cartesian(0.0, sYExp, 0.0/*, gyrAngle*/);
		}

		else if((stickX <= -0.5 || stickX >= 0.5) && (stickY > -0.5 && stickY < 0.5) && (stickZ > -0.25 && stickZ < 0.25)){
			drive->MecanumDrive_Cartesian(sXExp, 0.0, 0.0/*, gyrAngle*/);
		}

		else if((stickX > -0.5 && stickX < 0.5) && (stickY > -0.5 && stickY < 0.5) && (stickZ <= -0.25 && stickZ >= 0.25)){
			drive->MecanumDrive_Cartesian(0.0, 0.0, sZExp/*, gyrAngle*/);
		}

		else{
			drive->MecanumDrive_Cartesian(sXExp, sYExp, sZExp/*, gyrAngle*/);
		}

		/*for(float x = 0.0; x<=1.0; x+=0.0001){
			flTal->Set(x);
			rlTal->Set(x);
			frTal->Set(x);
			rrTal->Set(x);
			dash->PutNumber("x", x);
		}*/


		/*if(flCur>0.0){
			dash->PutNumber("startTimeFl", time->Get());
			time->Stop();
		}

		if(rlCur>0.0){
			dash->PutNumber("startTimeRl", time2->Get());
			time2->Stop();
		}

		if(frCur>0.0){
			dash->PutNumber("startTimeFr", time3->Get());
			time3->Stop();
		}

		if(rrCur>0.0){
			dash->PutNumber("startTimeRr", time4->Get());
			time4->Stop();
		}*/

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

		if(stick->GetRawButton(2) /*&& jb1Hit == false*/){ // opening
			arm->Set(false);
			jb1Hit = true;
		}
		if(stick->GetRawButton(1) /*&& jb1Hit == true*/){ // closing
			arm->Set(true);
			jb1Hit = false;
		}

		dash->PutBoolean("Claw is Open", jb1Hit);

		float armSpeed = ((-stick->GetThrottle())/2) + 0.54;
		dash->PutNumber("Throttle Value", armSpeed);

		if(stick->GetRawButton(5) == jb5Hit && stick->GetRawButton(3) != jb3Hit /*&& limit->Get()*/) {
			sol->Set(true);
			tal5->Set(-armSpeed);
			tal6->Set(-armSpeed);
		}
		else if(stick->GetRawButton(3) != jb3Hit /*&& !limit->Get()*/ && stick->GetRawButton(5) == jb5Hit){
			tal5->Set(0.0);
			tal6->Set(0.0);
			sol->Set(false);
		}
		else if(stick->GetRawButton(3) == jb3Hit && stick->GetRawButton(5) != jb5Hit){
			sol->Set(true);
			tal5->Set(0.0);
			tal6->Set(0.0);
		}
		else if(stick->GetRawButton(5) != jb5Hit && stick->GetRawButton(3) != jb3Hit){
			tal5->Set(0.0);
			tal6->Set(0.0);
			sol->Set(false);
		}
		else if(stick->GetRawButton(5) == jb5Hit && stick->GetRawButton(3) == jb3Hit){
			tal5->Set(0.0);
			tal6->Set(0.0);
			sol->Set(false);
		}

		/*if(stick->GetRawButton(7) == jb7Hit) {
			sol->Set(true);
			tal5->Set(-0.5);
			tal6->Set(-0.5);
		}
		else if(stick->GetRawButton(7) != jb7Hit && stick->GetRawButton(3) != jb3Hit && stick->GetRawButton(4) != jb4Hit){
			sol->Set(false);
			tal5->Set(0.0);
			tal6->Set(0.0);
		}*/

	}

	void TestPeriodic()
	{
		lw->Run();
	}
};

START_ROBOT_CLASS(Robot);