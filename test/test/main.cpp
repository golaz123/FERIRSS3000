// TOLE JE POVZETO PO poco-1.7.6/Net/samples/httpget/src/httpget.cpp
// KER NISEM KOPIRAL UVODNEGA KOMENTARJA TA DATOTEKA NI PRIMERNA ZA DISTRIBUCIJO IN UPORABO IZVEN VAJ

// DELUJE NA UBUNTU - testirano s knjiznicami prevedenimi iz izvorne kode
// NA UBUNTU SVOJ PROGRAM PREVEDES Z UKAZOM (uporabi ustrezen -I in -L)
// g++ -o example-poco-net1617.exe example-poco-net1617.cpp -I/usr/local/Poco/include -L/usr/local/Poco/lib -lPocoNet -lPocoFoundation
// ZA IZVAJANJE POT DO KNJIZNICE (CE NI VKLJUCENA V SISTEM) NASTAVIS Z UKAZOM
// export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/Poco/lib

// DELUJE NA MS WINDOWS - testirano s knjiznicami prevedenimi iz izvorne kode
// NA MS WINDOWS SO POTREBNE NEKATERE NASTAVITVE ZA VISUAL STUDIO
// DOBER ZGLED JE NA http://biddy.meolic.com/biddy-vs.html

#include "Meni.h"
#include "Poco/Net/HTTPClientSession.h"
#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/StreamCopier.h"
#include "Poco/URI.h"
#include <iostream>
#include <fstream>
#include <iomanip>

using Poco::Net::HTTPClientSession;
using Poco::Net::HTTPRequest;
using Poco::Net::HTTPResponse;
using Poco::Net::HTTPMessage;
using Poco::StreamCopier;
using Poco::URI;

int wmain(int argc, char** argv)
{
	Meni::GlavniMeni();

	return 0;
}