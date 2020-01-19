/*
 Name:		FPS_DoorLock_SMS_OTP.ino
 Created:	1/19/2020 5:56:29 PM
 Author:	CrisantoIII
*/

// the setup function runs once when you press reset or power the board
#include "Button.h"
#include "FPS.h"
#include "IICLCD.h"
#include "IRF.h"
#include "LED.h"
#include "OTP.h"
#include "SMS.h"

#include <NoDelay.h>
noDelay *otp_timeout;

Button		*open;
FPS			*fps;
IICLCD		*lcd;
IRF			*irf;
LED			*led_red;
LED			*led_green;
OTP			*otp;
SMS			*sms;

#define OPEN_PIN			3

#define LCD_ADDRESS			0x27
#define	LCD_ROWS			2
#define LCD_COLS			16

#define LOCK_DRIVER			4
#define GREEN_PIN			5
#define RED_PIN				6

#define CONTACT_NO			"+63000000000"
#define CONTACT_NO2			""

#define FPS_BAUDRATE		57600

#define OTP_TIME_LIMIT		30000

String otp_code = "";
bool otp_enabled = false;


void setup() {

	open = new Button(OPEN_PIN);
	fps = new FPS(&Serial, FPS_BAUDRATE);
	lcd = new IICLCD(LCD_ADDRESS, LCD_ROWS, LCD_COLS);
	irf = new IRF(LOCK_DRIVER, false);
	led_red = new LED(GREEN_PIN, false);
	led_green = new LED(RED_PIN, false);
	otp = new OTP();
	sms = new SMS(CONTACT_NO, CONTACT_NO2);
	otp_timeout = new noDelay(OTP_TIME_LIMIT);

	if (fps->isFPSConnected())
	{
		lcd->showisFPSConnected();
		delay(3000);
	}
	else
	{
		lcd->showFPSnotFound();
		delay(3000);
		lcd->showFPSCheckConnection();
		while (1) {}
	}

}

// the loop function runs over and over again until power down or reset
void loop() {
	otp->processTimeForOTP();
	open->Update();

	if (open->Read())
	{
		otp_code = otp->getOTPCode();
		sms->send(otp_code);

		if (otp_timeout)
			delete otp_timeout;

		otp_timeout = new noDelay(OTP_TIME_LIMIT);
	}

	if (otp_enabled)
	{
		if (sms->read(otp_code))
		{
			irf->On();
			led_green->On();
			led_red->Off();
			delay(3000);
			irf->Off();
			led_green->Off();
			led_red->Off();
			otp_enabled = false;
		}
		else
		{
			if (otp_timeout->update())
				otp_enabled = false;

		}
	}

	processFPS();
	delay(50);

}


int processFPS()
{
	if (fps->readValidImge() == false)
	{
		lcd->showreadNotValidImge();
		return -1;
	}

	if (fps->checkImage2Tz() == false)
	{
		lcd->showcheckFailedImage2Tz();
		delay(3000);
		return -1;
	}

	if (fps->findMatch() == false)
	{
		lcd->showfindNotMatch();
		sms->send("FPS Failed");
		delay(3000);
		return -1;
	}

	//If everything was ok, then we successfully match
	lcd->showSuccess();
	irf->On();
	led_green->On();
	led_red->Off();
	sms->send("FPS Accepted");
	delay(3000);
	irf->Off();
	led_green->Off();
	led_red->Off();
	return fps->Success();
}