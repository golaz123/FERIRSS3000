#pragma once

#include <iostream>
#include <map>

class Datum
{
private:
	const int MAX_DAN = 31;
	const int MAX_MESEC = 12;
	const int MIN_DAN = 1;
	const int MIN_MESEC = 1;
	const int MIN_LETO = 2015;

	int dan;
	int mesec;
	int leto;	
	int dnevi_v_mesecu[13];


	bool JeVeljavenDatum(int dan, int mesec, int leto);
	bool JeLetoPrestopno(int leto);
public:
	Datum();
	Datum(int dan, int mesec, int leto);
	~Datum();

	friend std::wostream &operator<<(std::wostream &stream, const Datum &datum);
};

