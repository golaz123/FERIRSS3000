#include "Datum.h"



Datum::Datum(unsigned dan, unsigned mesec, unsigned leto)
{
	if (PreveriDatum(dan, mesec, leto)) {
		Datum::dan = dan;
		Datum::mesec = mesec;
		Datum::leto = leto;
	} else {
		throw 10;
		Datum::dan = PRIVZET_DAN;
		Datum::mesec = PRIVZET_MESEC;
		Datum::leto = PRIVZETO_LETO;
	}
}


Datum::~Datum()
{
}

bool Datum::PreveriDatum(unsigned dan, unsigned mesec, unsigned leto)
{
	return true;
}