// 
// 
// 

#include "IRF.h"


IRF::IRF(uint8_t pin, bool is_high)
{
	this->pin = pin;

	pinMode(pin, OUTPUT);

	if (is_high)
		digitalWrite(pin, HIGH);
	else
		digitalWrite(pin, LOW);
}

IRF::~IRF()
{

}

void IRF::On()
{
	digitalWrite(pin, HIGH);
}

void IRF::Off()
{
	digitalWrite(pin, LOW);
}