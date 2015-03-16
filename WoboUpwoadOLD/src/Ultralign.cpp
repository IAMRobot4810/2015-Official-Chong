#include "Ultralign.h"

Ultralign::Ultralign(){

	dri = new DriveSystem();
	lifty = new Lifter();
	uSL = new AnalogInput(0);
	uSLOut = new AnalogOutput(0);
	uSC = new AnalogInput(1);
	uSCOut = new AnalogOutput(1);
	uSR = new AnalogInput(2);
	uSROut = new AnalogOutput(2);
	sDU->init();

}

Ultralign::~Ultralign(){

	delete dri;
	delete lifty;
	delete uSL;
	delete uSLOut;
	delete uSC;
	delete uSCOut;
	delete uSR;
	delete uSROut;

}

float Ultralign::UltraReadSuccessional(){

	uSROut->SetVoltage(0.0);
	uSCOut->SetVoltage(5.0);
	uSCRead = uSC->GetVoltage();
	Wait(0.125);
	uSCOut->SetVoltage(0.0);
	uSLOut->SetVoltage(5.0);
	uSLRead = uSL->GetVoltage();
	Wait(0.125);
	uSLOut->SetVoltage(0.0);
	uSROut->SetVoltage(5.0);
	uSRRead = uSR->GetVoltage();
	Wait(0.125);



}

void Ultralign::AlignandPick(){

	UltraReadSuccessional();

	uSLInch = uSLRead/0.0098;
	uSCInch = uSCRead/0.0098;
	uSRInch = uSRRead/0.0098;
	sDU->PutNumber("Ultrasonic Left Voltage", uSLRead);
	sDU->PutNumber("Ultrasonic Center Voltage", uSCRead);
	sDU->PutNumber("Ultrasonic Right Voltage", uSRRead);
	sDU->PutNumber("Ultrasonic Left Inch", uSLInch);
	sDU->PutNumber("Ultrasonic Center Inch", uSCInch);
	sDU->PutNumber("Ultrasonic Right Inch", uSRInch);

	if(uSCInch > 10.0){

		uValid = false;
		sDU->PutBoolean("Ultralign Validity", uValid);

	}

	else if(uSCInch <= 10.0){

		uValid = true;
		dri->DriveSpeedMecanum(0.0, 0.0, 0.0);
		sDU->PutBoolean("Ultralign Validity", uValid);

		if(uSCRead < uSLRead && uSCRead < uSRRead){

			lifty->SetLevel(Lifter::PLACEGARBAGECAN);
			Wait(1.0);
			lifty->SetArmpos(Lifter::OPEN);
			Wait(1.0);
			lifty->SetLevel(Lifter::GETGARBAGECAN);
			Wait(1.0);
			lifty->SetArmpos(Lifter::GARBAGECAN);
			Wait(1.0);
			lifty->SetLevel(Lifter::PLACEGARBAGECAN);

		}

	}

}