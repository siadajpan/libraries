/*
 * GPS.cpp
 *
 *  Created on: 2014/05/10
 *      Author: sin
 */

#include <GPS.h>

void GPS::begin(unsigned long baud) {
	if ( _onoff != 0xff ) {
		pinMode(_onoff, OUTPUT);
		digitalWrite(_onoff, HIGH);
	}
	SoftwareSerial::begin(baud);
}

bool GPS::start(void) {
	if ( _onoff == 0xff )
		return true;
	delay(1200);
	if ( available() > 6 )
		return true;
	digitalWrite(_onoff, LOW);
	delay(1200);
	digitalWrite(_onoff, HIGH);
	delay(1200);
	return available() > 6;
}

bool GPS::readGGA() {
//	GGA (474741): 065048.000,3335.5119,N,13021.3472,E,1,05,7.2,48.1,M,27.3,M,,0000
	int n;
	char tmp[12];
	if ( !readStrUntil(',',tmp,12) ) // UTC
		return false;
	_utc = atof(tmp);
	find(","); 	// Valid/Non Valid
	if ( !readStrUntil(',',tmp,12) ) // Lat.
		return false;
	_latitude = atof(tmp);
	if ( !readStrUntil(',',tmp,12) ) // N/S
		return false;
	if (tmp[0] == 'S') _latitude = -_latitude;
	if ( (n = readBytesUntil(',',tmp,12)) ) // Long.
		return false;
	_longitude = atof(tmp);
	if ( readStrUntil(',',tmp,12) )	// E/W
		return false;
	if (tmp[0] == 'W') _longitude = -_longitude;
	find(",");
	find(",");
	find(",");
	if ( !readStrUntil(',',tmp,12) ) // alt.
		return false;
	_altitude = atof(tmp);
	if ( readStrUntil(',',tmp,12) )	// M
		return false;
	if (tmp[0] != 'M') _altitude = 0;
	find("\n");
	return true;
}

bool GPS::readRMC() {
	int n;
	char tmp[12];
	if ( !readStrUntil(',',tmp,12) ) // UTC
		return false;
	_utc = atof(tmp);
	find(","); 	// Valid/Non Valid
	if ( !readStrUntil(',',tmp,12) ) // Lat.
		return false;
		_latitude = atof(tmp);
	if ( !readBytesUntil(',',tmp,12) ) // N/S
		return false;
	else
		if (tmp[0] == 'S') _latitude = -_latitude;
	if ( !readBytesUntil(',',tmp,12) ) // Long.
		return false;
	_longitude = atof(tmp);
	if ( !readBytesUntil(',',tmp,12) ) // E/W
		return false;
	else
		if (tmp[0] == 'W') _longitude = -_longitude;

	if ( !readStrUntil(',',tmp,12) )	// knots
		return false;
	_knots = atof(tmp);
	if ( !readStrUntil(',',tmp,12) )	// knots
		return false;
	_degree = atof(tmp);
	if ( !readStrUntil(',',tmp,12) )	// date
		return false;
	_date = atof(tmp);
	find("\n");
	return true;
}

unsigned long GPS::catchMessage(unsigned long timeout) {
	size_t n;
	char tmp[8];
	setTimeout(timeout);
	if ( !find("$") ) return false;
	n = readBytesUntil(',', tmp, 7);
	return ((unsigned long)tmp[2])<<16 | ((unsigned long)tmp[3]) << 8 | tmp[4];
}
/*
bool GPS::getSentence(const char msg[6], char * result, unsigned long timeout) {
    size_t n;
    char tmp[8] = "$";
    setTimeout(timeout);
    strcat(tmp, msg);
	if (!find(tmp)) return false;

    n = readBytesUntil('*', result, 128);
    result[n] = 0;
    n = readBytesUntil('\n',tmp, 8);
    tmp[n] = 0;
    strcat(result,"#");
    strcat(result,tmp);
    return true;
}
*/
float GPS::latitude(void) {
	double ipart;
	float fpart = modf(_latitude/100.0f, &ipart);
	return ipart + fpart*1.666667;
}

float GPS::latitude(float & secs) {
	double ipart;
	secs = modf(_latitude, &ipart) * 60.0f;
	return ipart/100.0;
}

float GPS::longitude(void) {
	double ipart;
	float fpart = modf(_longitude/100.0f, &ipart);
	return ipart + fpart*1.666667;
}

float GPS::longitude(float & secs) {
	double ipart;
	secs = modf(_longitude, &ipart) * 60.0f;
	return ipart/100.0;
}

float GPS::JST() {
	if ( _utc + 90000.0 >= 240000.0 )
		return _utc + 150000.0;
	else
		return _utc + 90000.0;
}

