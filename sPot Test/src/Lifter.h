#ifndef LIFTER_H
#define LIFTER_H

#include <WPILib.h>
#include <cmath>

class Lifter
{

private:
	CANTalon* clamper;
	AnalogPotentiometer* heightpot;
	DigitalInput *topLimit;
	AnalogInput* armwidth;
	CANTalon* lifttalon;
	CANTalon*lifthelper;
	SmartDashboard *sDLift;
	Solenoid* breaker;
	DoubleSolenoid* opener;
	int currlevel;
	int currarmpos;
	int factormeters = 2;
public:
	Lifter();
	~Lifter();
	enum level{GROUND, UNDERBOXONE, INBETWEEN, OVERBOXTWO, GETGARBAGECAN, PLACEGARBAGECAN, TOP};
	enum armpos{OPEN, CLOSE};

	static const int Ground = 0;
	static const int Underboxone = 1;
	static const int Inbetween = 2;
	static const int Overboxtwo = 3;
	static const int Getgarbage = 4;
	static const int PlaceGarbage = 5;
	static const int Top = 6;
	float ConvertToInches(float v);
	static const int Open = 7;
	static const int Boxshort = 8;
	static const int Garbage = 9;
	static const int Boxwide = 10;
	int GetLevel();
	int GetArmpos();
	void SetLevel(level l);
	void SetArmpos(armpos a);
	constexpr static const double openwidthm = 1.0;
	constexpr static const double closedwidthm = 0.1;
	constexpr static const double boxwidem = 1.5;
	constexpr static const double boxsmallm = 0.5;
	constexpr static const double gcanm = 0.75;
	constexpr static const double ropmeter=100;
	constexpr static const double groundinches = 5;
	constexpr static const double uboxoneinches = 10;
	constexpr static const double inbetweeninches = 15;
	constexpr static const double overbtwoinches = 20;
	constexpr static const double getgarbageinches = 25;
	constexpr static const double placegarbageinches = 30;
	constexpr static const double topinches = 54;
	constexpr static const double upspeed = -0.25;
	constexpr static const double downspeed = -0.03;


	Timer *Rolex;
	float sec;
	float potRead;
	float liftRead;
	float setSpeedLift;
	float talSpeedLift();

};



#endif
