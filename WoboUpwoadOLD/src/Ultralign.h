#ifndef ULTRALIGN_H
#define ULTRALIGN_H

#include "AnalogInput.h"
#include "AnalogOutput.h"
#include "DriveSystem.h"
#include "Lifter.h"

class Ultralign{

public:

	Ultralign();
	~Ultralign();

	DriveSystem *dri;
	Lifter *lifty;
	AnalogInput *uSL;
	AnalogOutput *uSLOut;
	AnalogInput *uSC;
	AnalogOutput *uSCOut;
	AnalogInput *uSR;
	AnalogOutput *uSROut;
	SmartDashboard *sDU;


	float UltraReadSuccessional();
	void AlignandPick();

private:

	float uSLRead;
	float uSCRead;
	float uSRRead;
	float uSLInch;
	float uSCInch;
	float uSRInch;
	bool uValid;

};

#endif
