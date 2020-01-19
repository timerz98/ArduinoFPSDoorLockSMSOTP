// 
// 
// 

#include "Button.h"


Button::Button(uint8_t pin)
{
	debouncer = new Bounce();

	pinMode(pin, INPUT_PULLUP);

	debouncer->attach(pin);
	debouncer->interval(5); // interval in ms
}

Button::~Button()
{
	if (debouncer)
		delete debouncer;
}

void Button::Update()
{
	debouncer->update();
}

bool Button::Read()
{
	if (debouncer->read() == LOW)
		return true;

	return false;
}