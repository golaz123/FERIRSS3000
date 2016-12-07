#include "Novica.h"


Novica::Novica() : 
	naslov(L"Prazno"), guid(L"0"), datum_objave(), vsebina(L"Prazno"), prebrana(false)
{
}

Novica::Novica(std::wstring naslov, std::wstring guid, Datum datum_objave, std::wstring vsebina) : 
	naslov(naslov), guid(guid), datum_objave(datum_objave), vsebina(vsebina), prebrana(false)
{
}

Novica::~Novica()
{
}

void Novica::PreprostiIzpis(std::wostream &stream)
{
	stream << naslov << ", " << datum_objave << std::endl;
}

void Novica::PodrobenIzpis(std::wostream &stream)
{
	PreprostiIzpis(stream);

	stream << vsebina << std::endl;
}