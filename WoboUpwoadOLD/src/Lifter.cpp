#include "Lifter.h"

Lifter::Lifter()
{
	lifthelper = new CANTalon(5);
	clamper = new CANTalon(7);
	heightpot = new AnalogPotentiometer(3, 1.0, 0.0);
	topLimit = new DigitalInput(0);
	botLimit = new DigitalInput(1);
	currarmpos = Open;
	lifttalon = new CANTalon(6);
	armwidth = new AnalogInput(4);
	sDLift->init();
	currlevel = 0;
	breaker = new DoubleSolenoid(1, 0, 1);
	opener = new DoubleSolenoid(1, 2, 3);
	Rolex = new Timer();


}

Lifter::~Lifter()
{
	delete lifthelper;
	delete clamper;
	delete heightpot;
	delete topLimit;
	delete botLimit;
	delete lifttalon;
	delete armwidth;

	delete Rolex;

}

float Lifter::talSpeedLift(){

	Rolex->Reset();
	Rolex->Start();
	sec = Rolex->Get();
	potRead = ConvertToInches(heightpot->Get());

	Rolex->Stop();

	liftRead = abs(potRead/sec);

	//Edit the 5.0

	if(liftRead > 5.0){

		while(liftRead > 5.0){

			setSpeedLift = setSpeedLift - 0.01;

		}

	}

	else if(liftRead <= 5.0){

		while(liftRead <= 5.0){

			setSpeedLift = setSpeedLift + 0.01;

		}

	}

	sDLift->PutNumber("Lifter Height", potRead);
	sDLift->PutNumber("Lifter Speed", setSpeedLift);

	return setSpeedLift;

}

int Lifter::GetLevel()
{
	return currlevel;
}

int Lifter::GetArmpos()
{
	return currarmpos;
}

void Lifter::SetLevel(level l)
{
	switch (l)
	{
	SetArmpos(Lifter::armpos::OPEN);
	case GROUND:
		if(ConvertToInches(heightpot->Get())>groundinches && botLimit->Get())
		{
			breaker->Set(DoubleSolenoid::Value::kReverse);
			lifttalon->Set(downspeed);
			lifthelper->Set(downspeed);
		}
		else if(ConvertToInches(heightpot->Get())<=groundinches || !botLimit->Get()){
			lifttalon->Set(0);
			lifthelper->Set(0);
			breaker->Set(DoubleSolenoid::Value::kForward);
			currlevel = Ground;
		}
		break;
	case UNDERBOXONE:
		if(ConvertToInches(heightpot->Get())>uboxoneinches)
		{
			breaker->Set(DoubleSolenoid::Value::kReverse);
			lifttalon->Set(downspeed);
			lifthelper->Set(downspeed);
		}
		else if(ConvertToInches(heightpot->Get())<uboxoneinches)
		{
			breaker->Set(DoubleSolenoid::Value::kReverse);
			lifttalon->Set(upspeed);
			lifthelper->Set(upspeed);
		}
		else
		{
			breaker->Set(DoubleSolenoid::Value::kForward);
			lifttalon->Set(0);
			lifthelper->Set(0);
			currlevel = Underboxone;
		}
		break;
	case INBETWEEN:
		if(ConvertToInches(heightpot->Get())>inbetweeninches)
		{
			breaker->Set(DoubleSolenoid::Value::kReverse);
			lifttalon->Set(downspeed);
			lifthelper->Set(downspeed);
		}
		else if(ConvertToInches(heightpot->Get())<inbetweeninches)
		{
			breaker->Set(DoubleSolenoid::Value::kReverse);
			lifttalon->Set(upspeed);
			lifthelper->Set(upspeed);
		}
		else
		{
			breaker->Set(DoubleSolenoid::Value::kForward);
			lifttalon->Set(0);
			lifthelper->Set(0);
			currlevel = Inbetween;
		}
		break;
	case OVERBOXTWO:
		if(ConvertToInches(heightpot->Get())>overbtwoinches)
		{
			breaker->Set(DoubleSolenoid::Value::kReverse);
			lifttalon->Set(downspeed);
			lifthelper->Set(downspeed);
		}
		else if(ConvertToInches(heightpot->Get())<overbtwoinches)
		{
		breaker->Set(DoubleSolenoid::Value::kReverse);
		lifttalon->Set(upspeed);
		lifthelper->Set(upspeed);
		}
		else
		{
			breaker->Set(DoubleSolenoid::Value::kForward);
			lifttalon->Set(0);
			lifthelper->Set(0);
			currlevel = Overboxtwo;
		}
		break;
	case GETGARBAGECAN:
		if(ConvertToInches(heightpot->Get())>getgarbageinches)
		{
			breaker->Set(DoubleSolenoid::Value::kReverse);
			lifttalon->Set(downspeed);
			lifthelper->Set(downspeed);
		}
		else if(ConvertToInches(heightpot->Get())<getgarbageinches)
		{
			breaker->Set(DoubleSolenoid::Value::kReverse);
			lifttalon->Set(upspeed);
			lifthelper->Set(upspeed);
		}
		else
		{
			breaker->Set(DoubleSolenoid::Value::kForward);
			lifttalon->Set(0);
			lifthelper->Set(0);
			currlevel = Getgarbage;
		}
		break;
	case PLACEGARBAGECAN:
		if(ConvertToInches(heightpot->Get())>placegarbageinches)
		{
			breaker->Set(DoubleSolenoid::Value::kReverse);
			lifttalon->Set(downspeed);
			lifthelper->Set(downspeed);
		}
		else if(ConvertToInches(heightpot->Get())<placegarbageinches)
		{
			breaker->Set(DoubleSolenoid::Value::kReverse);
			lifttalon->Set(upspeed);
			lifthelper->Set(upspeed);
		}
		else
		{
			breaker->Set(DoubleSolenoid::Value::kForward);
			lifttalon->Set(0);
			lifthelper->Set(0);
			currlevel = PlaceGarbage;
		}
		break;

	case TOP:

		if(ConvertToInches(heightpot->Get())<topinches && topLimit->Get())
		{
			breaker->Set(DoubleSolenoid::Value::kReverse);
			lifttalon->Set(upspeed);
			lifthelper->Set(upspeed);
		}
		else if(ConvertToInches(heightpot->Get())>=topinches && !topLimit->Get())
		{
			breaker->Set(DoubleSolenoid::Value::kForward);
			lifttalon->Set(0);
			lifthelper->Set(0);
			currlevel = Top;
		}
		break;

	};

}

void Lifter::SetArmpos(armpos a)
{
	switch(a)
	{
	case OPEN:
		opener->Set(DoubleSolenoid::kForward);
		break;
	case CLOSE:
		opener->Set(DoubleSolenoid::kReverse);
		break;
	}

}

float Lifter::ConvertToInches(float v){
	return abs(-85.2459*v+23.90984);
}

