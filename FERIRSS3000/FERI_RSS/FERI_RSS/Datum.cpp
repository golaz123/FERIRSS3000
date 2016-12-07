#include "Datum.h"


Datum::Datum() : 
	dan(MIN_DAN), mesec(MIN_MESEC), leto(MIN_LETO)
{
}

Datum::Datum(int dan, int mesec, int leto)
{
	if (JeLetoPrestopno(leto)) 
		int dnevi_v_mesecu[] = {31, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; 
	else 
		int dnevi_v_mesecu[] = {31, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	if (JeVeljavenDatum(dan, mesec, leto)) {
		Datum::dan = dan;
		Datum::mesec = mesec;
		Datum::leto = leto;
	}
	else {
		throw 10;
	}
}

Datum::~Datum()
{
}

bool Datum::JeVeljavenDatum(int dan, int mesec, int leto)
{
	if (leto >= MIN_LETO) {
		if (mesec >= MIN_MESEC && mesec <= MAX_MESEC) {
			if (dan >= MIN_DAN && dan <= dnevi_v_mesecu[mesec]) {
				return true;
			}
		}
	}

	return false;
}

bool Datum::JeLetoPrestopno(int leto)
{
	if ((leto % 4 == 0 && leto % 100 != 0) || leto % 400 == 0) {
		return true;
	}

	return false;
}

std::wostream &operator<<(std::wostream &stream, Datum const &datum) {
	stream << datum.dan << "." << datum.mesec << "." << datum.leto;
	return stream;
}