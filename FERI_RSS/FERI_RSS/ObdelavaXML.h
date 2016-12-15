#pragma once
#include "Poco/DOM/DOMParser.h"
#include "Poco/DOM/Document.h"
#include "Poco/DOM/NodeIterator.h"
#include "Poco/DOM/NodeFilter.h"
#include "Poco/DOM/NamedNodeMap.h"
#include "Poco/DOM/AutoPtr.h"
#include "Poco/SAX/InputSource.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>


class ObdelavaXML
{
private:
	static const int ST_RAZCLJENJENIH_EL = 4;	// Število razèlenjenih elementov.

	ObdelavaXML() {}
public:
	// Vsebuje pridobljene podatke ob razèlenitvi.
	struct RazclenjenXML {
		std::wstring naslov;
		std::wstring datum_objave;
		std::wstring vsebina;
		std::wstring guid;
	};

	static RazclenjenXML RazcleniXML(std::string pot_datoteke);
};

