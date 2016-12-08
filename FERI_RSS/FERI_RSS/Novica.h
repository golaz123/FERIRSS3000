#pragma once

#include <string>
#include "Datum.h"

class Novica
{
private:
	std::wstring naslov;
	std::wstring guid;
	std::wstring vsebina;
	Datum datum_objave;
	bool prebrana;
public:
	Novica();
	Novica(std::wstring naslov, std::wstring guid, Datum datum_objave, std::wstring vsebina);
	~Novica();

	void PreprostiIzpis(std::wostream &stream);
	void PodrobenIzpis(std::wostream &stream);
};

