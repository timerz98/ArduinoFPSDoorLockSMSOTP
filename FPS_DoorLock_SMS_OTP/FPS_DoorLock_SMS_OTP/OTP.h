// OTP.h

#ifndef _OTP_h
#define _OTP_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <sha1.h>
#include <TOTP.h>
#include <NoDelay.h>

class OTP
{
public:
	OTP();
	~OTP();

	String getOTPCode();
	void processTimeForOTP();
private:
	noDelay *update_time;
	TOTP *totp;
	uint8_t hmacKey[10] = { 0x4d, 0x79, 0x4c, 0x65, 0x67, 0x6f, 0x44, 0x6f, 0x6f, 0x72 };
	unsigned long time;
};

#endif

