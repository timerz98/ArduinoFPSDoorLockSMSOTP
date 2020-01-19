// Button.h

#ifndef _BUTTON_h
#define _BUTTON_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <Bounce2.h>

class Button
{
public:
	Button(uint8_t pin);
	~Button();

	bool Read();
	void Update();

private:
	Bounce *debouncer;
};

#endif

