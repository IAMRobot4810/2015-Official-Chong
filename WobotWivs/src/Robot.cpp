#include "WPILib.h"
#include "DriveSystem.h"
//#include "C:\Users\1750800404\wpilib\cpp\current\include\Buttons\JoystickButton.h"
//#include "C:\Users\1750800404\wpilib\cpp\current\include\SmartDashboard\SmartDashboard.h"

class Robot: public IterativeRobot
{

public:

	DriveSystem *driveBro;

	/*Joystick *stick;
	Talon *talZero;
	Talon *talOne;
	Talon *talTwo;
	Talon *talThree;
	RobotDrive *robo;
	JoystickButton *jButton;*/


	Robot(){

		driveBro = new DriveSystem();
		/*stick = new Joystick(0);
		talZero = new Talon(0);
		talOne = new Talon(1);
		talTwo = new Talon(2);
		talThree = new Talon(3);
		robo = new RobotDrive(talTwo, talThree, talOne, talZero);
		jButton = new JoystickButton(stick, 1);*/


	}

	~Robot(){

		delete driveBro;

	}

private:
	LiveWindow *lw;

	void RobotInit()
	{
		lw = LiveWindow::GetInstance();
		/*robo->SetInvertedMotor(RobotDrive::kFrontRightMotor, true);
		robo->SetInvertedMotor(RobotDrive::kRearRightMotor, true);*/
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

		/*robo->MecanumDrive_Cartesian(stick->GetX(), stick->GetY(), stick->GetZ());
		stick->get*/
		driveBro->DriveArcadeStyle();

	}

	void TestPeriodic()
	{
		lw->Run();
	}
};

START_ROBOT_CLASS(Robot);
