#include "PovezavaHTTP.h"

const std::string PovezavaHTTP::prenosna_mapa = "\temp";

bool PovezavaHTTP::PrenesiDatoteko(std::string spletni_naslov, std::string ime_datoteke, std::string &napaka)
{
	std::ofstream datoteka;
	datoteka.open(prenosna_mapa + ime_datoteke, std::ios_base::out | std::ios_base::trunc);

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

		return true;
	}
	else {
		napaka = response.getStatus() + response.getReason();

		return false;
	}
}