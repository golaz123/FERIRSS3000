#pragma once

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "Poco/Net/HTTPClientSession.h"
#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/StreamCopier.h"
#include "Poco/URI.h"

using Poco::Net::HTTPClientSession;
using Poco::Net::HTTPRequest;
using Poco::Net::HTTPResponse;
using Poco::Net::HTTPMessage;
using Poco::StreamCopier;
using Poco::URI;

class PovezavaHTTP
{
private:
	static const std::string prenosna_mapa;

	PovezavaHTTP() {}
public:
	static bool PovezavaHTTP::PrenesiDatoteko(std::string spletni_naslov, std::string ime_datoteke, std::string &napaka);
};

