// 
// 
// 

#include "SMS.h"

SMS::SMS(String contact_no, String contact_no2)
{
	GSM.begin(4800);

	this->contact_no = contact_no;

	if (contact_no2 != "")
		this->contact_no2 = contact_no2;
}

SMS::~SMS()
{

}

void SMS::send(String text)
{

	GSM.sendSms((char *)contact_no.c_str(), (char *)text.c_str());

	if (contact_no2 != "")
		GSM.sendSms((char *)contact_no2.c_str(), (char *)text.c_str());
}

bool SMS::read(String key)
{
	String text = GSM.readSms(1);
	return text.compareTo("OPEN:" + key);
}