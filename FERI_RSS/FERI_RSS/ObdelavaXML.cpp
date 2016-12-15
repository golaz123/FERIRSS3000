#include "ObdelavaXML.h"


ObdelavaXML::RazclenjenXML ObdelavaXML::RazcleniXML(std::string pot_datoteke)
{
	std::ifstream datoteka;
	datoteka.open(pot_datoteke.c_str(), std::ios_base::in);

	Poco::XML::DOMParser parser;
	Poco::XML::InputSource src(datoteka);
	Poco::XML::AutoPtr<Poco::XML::Document> p_doc = parser.parse(&src);
	
	Poco::XML::NodeIterator it(p_doc, Poco::XML::NodeFilter::SHOW_ALL);
	Poco::XML::Node* p_node = it.nextNode();

	// Preskocimo prvi zapis (vse do drugega "title"), ker to ni novica.
	bool najden_title = false;
	
	while (!najden_title || p_node->nodeName() != "title") {
		if (p_node->nodeName() == "title") { najden_title = true; }

		p_node = it.nextNode();
	}

	ObdelavaXML::RazclenjenXML podatki;

	// Imena nodov in pripadajoèi èlani strukture RazclenjenXML kamor spadajo njihovi podatki.
	const std::string node_imena[] = { 
		"title", 
		"description", 
		"pubDate", 
		"guid" 
	};
	std::wstring* const p_podatek[ObdelavaXML::ST_RAZCLJENJENIH_EL] = {
		&podatki.naslov,
		&podatki.vsebina,
		&podatki.datum_objave,
		&podatki.guid
	};

	Poco::XML::NamedNodeMap* attributes = NULL;
	Poco::XML::Node* attribute = NULL;

	// Pojdi skozi celoten XML.
	while (p_node)
	{
		for (int i = 0; i < ObdelavaXML::ST_RAZCLJENJENIH_EL; i++) {
			if (p_node->nodeName() == node_imena[i]) {
				std::wstring ws_tmp;
				std::string s_tmp;

				p_node = it.nextNode();	// Pijdi na naslednji node, da lahk dobimo vrednost.
				s_tmp = p_node->nodeValue();
				ws_tmp.assign(s_tmp.begin(), s_tmp.end());
				*p_podatek[i] = ws_tmp;	// Shrani vrednost v strukturo.
			}

			p_node = it.nextNode();
		}
	}

	datoteka.close();

	return podatki;
}