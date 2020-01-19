// Relay.h

#ifndef _IRF_h
#define _IRF_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class IRF
{
public:
	IRF(uint8_t pin, bool is_high);
	~IRF();

	void On();
	void Off();

private:
	uint8_t pin;
};


#endif

