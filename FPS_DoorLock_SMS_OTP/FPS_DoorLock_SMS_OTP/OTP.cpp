// 
// 
// 

#include "OTP.h"


OTP::OTP()
{
	totp = new TOTP(hmacKey, 10);
	update_time = new noDelay(1000);
	time = 1579437217;
}

OTP::~OTP()
{

}

String OTP::getOTPCode()
{
	char* newCode = totp->getCode(time);

	return newCode;
}

void OTP::processTimeForOTP()
{
	if (update_time->update())
		time++;
}