#include "PovezavaHTTP.h"

PovezavaHTTP::PrenosStanje PovezavaHTTP::PrenesiDatoteko(std::string spletni_naslov, std::string pot_datoteke)
{
	PovezavaHTTP::PrenosStanje stanje;
	std::ofstream datoteka;

	datoteka.open(pot_datoteke, std::ios_base::out | std::ios_base::trunc);

	URI uri(spletni_naslov);

	std::string path(uri.getPathAndQuery());

	if (path.empty()) { path = "/"; }

	HTTPClientSession session(uri.getHost(), uri.getPort());
	HTTPRequest request(HTTPRequest::HTTP_GET, path, HTTPMessage::HTTP_1_1);
	HTTPResponse response;

	session.sendRequest(request);
	std::istream &rs = session.receiveResponse(response);

	if (response.getStatus() == Poco::Net::HTTPResponse::HTTP_OK) {
		StreamCopier::copyStream(rs, datoteka);

		stanje.uspesno = true;
	}
	else {
		std::stringstream napaka;
		napaka << response.getStatus() << " " << response.getReason();

		stanje.uspesno = false;
		stanje.napaka = napaka.str();
	}

	return stanje;
}