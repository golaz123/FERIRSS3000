#pragma once

#include "Poco/Net/HTTPClientSession.h"
#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/StreamCopier.h"
#include "Poco/URI.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>


class PovezavaHTTP
{
private:
	PovezavaHTTP() {}
public:
	// Stanje prenosa datoteke.
	struct PrenosStanje {
		bool uspesno;		// �e se je datoteka uspe�no prenesla.
		std::string napaka;	// Vsebuje podatke o napaki.
	};

	static PrenosStanje PrenesiDatoteko(std::string spletni_naslov, std::string pot_datoteke);
};

