#include "Meni.h"

const std::string Meni::IME_VERZIJA = "FERI RSS, v0.1";
const std::string Meni::IME_VERZIJA_TR = "FERI RSS, v0.1 (TR)";
const std::string Meni::IME_VERZIJA_NP = "FERI RSS, v0.1 (NI POVEZAVE)";
const std::string Meni::NOVICE_SPL_NASLOVI[Meni::ST_KATEGORIJ_NOVIC] = { 
	"http://feri.um.si/odeska/rss/",
	"http://feri.um.si/novice/rss/",
	"http://feri.um.si/obvestila/rss/",
	"http://feri.um.si/dogodki/rss/",
	"http://feri.um.si/zaposlitve/rss/"
};
const std::string Meni::NOVICE_LOK_IMENA[Meni::ST_KATEGORIJ_NOVIC] = {
	"odeska.dat",
	"novice.dat",
	"obvestila.dat",
	"dogodki.dat",
	"zaposlitve.dat"
};
std::vector<Novica>* const Meni::P_SEZNAMI[Meni::ST_KATEGORIJ_NOVIC] = {
	&odeska,
	&novice,
	&obvestila,
	&dogodki,
	&zaposlitve
};
const std::string Meni::PRENOSNA_MAPA = ".\\temp\\";
const std::string Meni::NAPAKA_DUMP = ".\\temp\\dump.txt";

bool Meni::ostani_v_prog = true;
int Meni::st_novic_stran = MAX_ST_NOVIC_STRAN;

std::vector<Novica> Meni::dogodki;
std::vector<Novica> Meni::odeska;
std::vector<Novica> Meni::novice;
std::vector<Novica> Meni::obvestila;
std::vector<Novica> Meni::zaposlitve;

void Meni::GlavniMeni()
{
	GlavneStoritve tr_storitev = GlavneStoritve::VSE_NOVICE;	// Trenutno označena storitev.
	const std::wstring glavne_storitve[GlavneStoritve::ST_STORITEV] = {	// Storitve izpiane na zaslonu.
		L"1. vse novice",
		L"2. oglasna deska",
		L"3. novice",
		L"4. obvestila za študente",
		L"5. dogodki",
		L"6. zaposlitve",
		L"7. iskanje po datumu",
		L"8. pomoč",
		L"9. testne režim",
		L"10. nastavitve",
		L"11. izhod"
	};
	const izbira_menija p_podmeniji[GlavneStoritve::ST_STORITEV] = {	// Konstantni kazalci k funckijam, za izpis podmenijev.
		&Meni::VseNovice,
		&Meni::OglasnaDeska,
		&Meni::Novice,
		&Meni::ObvestilaZaStudente,
		&Meni::Dogodki,
		&Meni::Zaposlitve,
		&Meni::IskanjePoDatumu,
		&Meni::Pomoc,
		&Meni::TestniRezim,
		&Meni::Nastavitve,
		&Meni::Izhod
	};

	SetConsoleTitle(IME_VERZIJA.c_str());
	setlocale(LC_ALL, "");

	system("cls");

	// Ustvari nit za prenos datotek in njihovo obdelavo.
	std::thread t_prenos_obdelava(Meni::PrenosInObdelava);

	for (int i = 0; i < Meni::GlavneStoritve::ST_STORITEV; i++) { std::wcout << glavne_storitve[i] << std::endl; }
	
	Meni::Oznaci(0, tr_storitev - 1, glavne_storitve[tr_storitev - 1]);

	while (true) {
		// Preveri če je kateri izmed gumbov stisjen (0x8000-najvišji bit drži to vrednost).
		if (GetKeyState(VK_UP) & 0x8000) {				// Puščica gor.
			Meni::IzpisiXY(0, tr_storitev - 1, glavne_storitve[tr_storitev - 1]);	// Odoznači prejšnjo vrednost.
			tr_storitev = static_cast<GlavneStoritve>(ZmanjsajDoMeje(tr_storitev, GlavneStoritve::ST_STORITEV - 1, GlavneStoritve::VSE_NOVICE));
			Meni::Oznaci(0, tr_storitev - 1, glavne_storitve[tr_storitev - 1]);		// Označi novo vrednost.
			
			Meni::PreprostiIzpisNovic(tr_storitev);	// Izpiši novice trenutne storitve.

			Sleep(GUMB_DEBOUNCE);
		} else if (GetKeyState(VK_DOWN) & 0x8000) {		// Puščica dol.
			Meni::IzpisiXY(0, tr_storitev - 1, glavne_storitve[tr_storitev - 1]);	// Odoznači prejšnjo vrednost.
			tr_storitev = static_cast<GlavneStoritve>(PovecajDoMeje(tr_storitev, GlavneStoritve::ST_STORITEV - 1, GlavneStoritve::VSE_NOVICE));
			Meni::Oznaci(0, tr_storitev - 1, glavne_storitve[tr_storitev - 1]);		// Označi novo vrednost.

			Meni::PreprostiIzpisNovic(tr_storitev);	// Izpiši novice trenutne storitve.

			Sleep(GUMB_DEBOUNCE);
		} else if (GetKeyState(VK_RETURN) & 0x8000) {	// Enter.
			Sleep(GUMB_DEBOUNCE);	// Potrebno je prej debounce, da se ne po pomoti šteje kot stisk tipke v podmeniju.

			(p_podmeniji[tr_storitev - 1])();

			// Izhod iz programa.
			if (!ostani_v_prog) { break; }

			system("cls");

			for (int i = 0; i < Meni::GlavneStoritve::ST_STORITEV; i++) { std::wcout << glavne_storitve[i] << std::endl; }

			Meni::Oznaci(0, tr_storitev - 1, glavne_storitve[tr_storitev - 1]);

			Sleep(GUMB_DEBOUNCE);
		}
	}

	// Varno zaključi z nitjo.
	t_prenos_obdelava.detach();
}

void Meni::PreprostiIzpisNovic(Meni::GlavneStoritve tr_storitev)
{
	// Preprosti izpis novic izbrane storitve.
	if (tr_storitev >= Meni::GlavneStoritve::OGLASNA_DESKA && tr_storitev <= Meni::GlavneStoritve::ZAPOSLITVE && 
		!P_SEZNAMI[tr_storitev - 2]->empty()) {

		Meni::PojdiXY(0, PREPR_NOVICA_Y);

		for (std::vector<Novica>::size_type i = 0; i != (P_SEZNAMI[tr_storitev - 2]->size() || st_novic_stran); i++) {
			(*P_SEZNAMI[tr_storitev - 2])[i].PreprostiIzpis(std::wcout);
			std::wcout << std::endl;
		}
	}
}

void Meni::PodrobenIzpisNovic(Meni::GlavneStoritve tr_storitev, int tr_stran, int st_strani)
{
	// Podroben izpis novic izbrane storitve.
	if (tr_storitev >= Meni::GlavneStoritve::OGLASNA_DESKA && tr_storitev <= Meni::GlavneStoritve::ZAPOSLITVE &&
		!P_SEZNAMI[tr_storitev - 2]->empty()) {

		Meni::PojdiXY(0, 0);

		for (std::vector<Novica>::size_type i = 0; i != (P_SEZNAMI[tr_storitev - 2]->size() || st_novic_stran); i++) {
			(*P_SEZNAMI[tr_storitev - 2])[i].PodrobenIzpis(std::wcout);
			std::wcout << std::endl;
		}

		std::wcout << L"◄ Stran " << tr_stran << "/" << st_strani << L" ►";
	}
}

int Meni::DobiSteviloVsehNovic()
{
	int st_novic = 0;

	for (int i = 0; i < Meni::ST_KATEGORIJ_NOVIC; i++) {
		st_novic += P_SEZNAMI[i]->size();
	}

	return st_novic;
}

int Meni::PovecajDoMeje(int tr_vrednost, int max_vrednost, int min_vrednost)
{
	if (tr_vrednost == max_vrednost) { return min_vrednost; } 
	else { return ++tr_vrednost; }
}

int Meni::ZmanjsajDoMeje(int tr_vrednost, int max_vrednost, int min_vrednost)
{
	if (tr_vrednost == min_vrednost) { return max_vrednost; }
	else { return --tr_vrednost; }
}

void Meni::PojdiXY(int x, int y)
{
	COORD koord;
	koord.X = x;
	koord.Y = y;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), koord);
}

void Meni::Oznaci(int x, int y, std::wstring besedilo)
{
	Meni::PojdiXY(x, y);

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN);

	std::wcout << besedilo;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
}

void Meni::IzpisiXY(int x, int y, std::wstring besedilo)
{
	Meni::PojdiXY(x, y);

	std::wcout << besedilo;
}

void Meni::PrenosInObdelava()
{
	while (true) {
		PovezavaHTTP::PrenosStanje pr_stanje;

		CreateDirectoryA(PRENOSNA_MAPA.c_str(), NULL);

		// Prenesi vse datoteke.
		for (int i = 0; i < ST_KATEGORIJ_NOVIC; i++) {
			pr_stanje = PovezavaHTTP::PrenesiDatoteko(NOVICE_SPL_NASLOVI[i], PRENOSNA_MAPA + NOVICE_LOK_IMENA[i]);

			if (pr_stanje.uspesno) {
				SetConsoleTitle(IME_VERZIJA.c_str());

				// Shrani razclenjen XML kot objekt tipa Novica.
				ObdelavaXML::RazclenjenXML xml_pod;
				
				xml_pod = ObdelavaXML::RazcleniXML(PRENOSNA_MAPA + NOVICE_LOK_IMENA[i]);
				P_SEZNAMI[i]->push_back(Novica(xml_pod.naslov, xml_pod.guid, Datum(xml_pod.datum_objave), xml_pod.vsebina));
			} else {
				SetConsoleTitle(IME_VERZIJA_NP.c_str());

				// Zapiši napako v dump datoteko s časovno štampilko.
				std::ofstream datoteka;
				std::time_t tr_cas = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());	// Trenutni čas in datum.

				datoteka.open(NAPAKA_DUMP, std::ios_base::out | std::ios_base::trunc);
				datoteka << std::ctime(&tr_cas) << ": " << pr_stanje.napaka << std::endl;
				datoteka.close();
			}
		}

		Sleep(CAS_MED_PRENOSI);
	}
}

void Meni::VseNovice()
{
	static const int min_st_strani = 1;
	int tr_stran = min_st_strani;

	system("cls");

	PodrobenIzpisNovic(Meni::GlavneStoritve::VSE_NOVICE, tr_stran, DobiSteviloVsehNovic());

	while (true) {
		// Preveri če je kateri izmed gumbov stisjen (0x8000-najvišji bit drži to vrednost).
		if (GetKeyState(VK_LEFT) & 0x8000) {			// Puščica levo.
			tr_stran = Meni::ZmanjsajDoMeje(tr_stran, DobiSteviloVsehNovic(), min_st_strani);
			PodrobenIzpisNovic(Meni::GlavneStoritve::VSE_NOVICE, tr_stran, DobiSteviloVsehNovic());

			Sleep(GUMB_DEBOUNCE);
		}
		else if (GetKeyState(VK_RIGHT) & 0x8000) {		// Puščica desno.
			tr_stran = Meni::PovecajDoMeje(tr_stran, DobiSteviloVsehNovic(), min_st_strani);
			PodrobenIzpisNovic(Meni::GlavneStoritve::VSE_NOVICE, tr_stran, DobiSteviloVsehNovic());

			Sleep(GUMB_DEBOUNCE);
		}
		else if (GetKeyState(VK_ESCAPE) & 0x8000) {		// Esc.
			break;
		}
	}
}

void Meni::OglasnaDeska()
{
	static const int min_st_strani = 1;
	int tr_stran = min_st_strani;

	system("cls");

	PodrobenIzpisNovic(Meni::GlavneStoritve::OGLASNA_DESKA, tr_stran, P_SEZNAMI[Meni::GlavneStoritve::OGLASNA_DESKA - 2]->size());

	while (true) {
		// Preveri če je kateri izmed gumbov stisjen (0x8000-najvišji bit drži to vrednost).
		if (GetKeyState(VK_LEFT) & 0x8000) {			// Puščica levo.
			tr_stran = Meni::ZmanjsajDoMeje(tr_stran, DobiSteviloVsehNovic(), min_st_strani);
			PodrobenIzpisNovic(Meni::GlavneStoritve::OGLASNA_DESKA, tr_stran, P_SEZNAMI[Meni::GlavneStoritve::OGLASNA_DESKA - 2]->size());

			Sleep(GUMB_DEBOUNCE);
		}
		else if (GetKeyState(VK_RIGHT) & 0x8000) {		// Puščica desno.
			tr_stran = Meni::PovecajDoMeje(tr_stran, DobiSteviloVsehNovic(), min_st_strani);
			PodrobenIzpisNovic(Meni::GlavneStoritve::OGLASNA_DESKA, tr_stran, P_SEZNAMI[Meni::GlavneStoritve::OGLASNA_DESKA - 2]->size());

			Sleep(GUMB_DEBOUNCE);
		}
		else if (GetKeyState(VK_ESCAPE) & 0x8000) {		// Esc.
			break;
		}
	}
}

void Meni::Novice()
{
	static const int min_st_strani = 1;
	int tr_stran = min_st_strani;

	system("cls");

	PodrobenIzpisNovic(Meni::GlavneStoritve::NOVICE, tr_stran, P_SEZNAMI[Meni::GlavneStoritve::NOVICE - 2]->size());

	while (true) {
		// Preveri če je kateri izmed gumbov stisjen (0x8000-najvišji bit drži to vrednost).
		if (GetKeyState(VK_LEFT) & 0x8000) {			// Puščica levo.
			tr_stran = Meni::ZmanjsajDoMeje(tr_stran, DobiSteviloVsehNovic(), min_st_strani);
			PodrobenIzpisNovic(Meni::GlavneStoritve::NOVICE, tr_stran, P_SEZNAMI[Meni::GlavneStoritve::NOVICE - 2]->size());

			Sleep(GUMB_DEBOUNCE);
		}
		else if (GetKeyState(VK_RIGHT) & 0x8000) {		// Puščica desno.
			tr_stran = Meni::PovecajDoMeje(tr_stran, DobiSteviloVsehNovic(), min_st_strani);
			PodrobenIzpisNovic(Meni::GlavneStoritve::NOVICE, tr_stran, P_SEZNAMI[Meni::GlavneStoritve::NOVICE - 2]->size());

			Sleep(GUMB_DEBOUNCE);
		}
		else if (GetKeyState(VK_ESCAPE) & 0x8000) {		// Esc.
			break;
		}
	}
}

void Meni::ObvestilaZaStudente()
{
	static const int min_st_strani = 1;
	int tr_stran = min_st_strani;

	system("cls");

	PodrobenIzpisNovic(Meni::GlavneStoritve::OBVESTILA, tr_stran, P_SEZNAMI[Meni::GlavneStoritve::OBVESTILA - 2]->size());

	while (true) {
		// Preveri če je kateri izmed gumbov stisjen (0x8000-najvišji bit drži to vrednost).
		if (GetKeyState(VK_LEFT) & 0x8000) {			// Puščica levo.
			tr_stran = Meni::ZmanjsajDoMeje(tr_stran, DobiSteviloVsehNovic(), min_st_strani);
			PodrobenIzpisNovic(Meni::GlavneStoritve::OBVESTILA, tr_stran, P_SEZNAMI[Meni::GlavneStoritve::OBVESTILA - 2]->size());

			Sleep(GUMB_DEBOUNCE);
		}
		else if (GetKeyState(VK_RIGHT) & 0x8000) {		// Puščica desno.
			tr_stran = Meni::PovecajDoMeje(tr_stran, DobiSteviloVsehNovic(), min_st_strani);
			PodrobenIzpisNovic(Meni::GlavneStoritve::OBVESTILA, tr_stran, P_SEZNAMI[Meni::GlavneStoritve::OBVESTILA - 2]->size());

			Sleep(GUMB_DEBOUNCE);
		}
		else if (GetKeyState(VK_ESCAPE) & 0x8000) {		// Esc.
			break;
		}
	}
}

void Meni::Dogodki()
{
	static const int min_st_strani = 1;
	int tr_stran = min_st_strani;

	system("cls");

	PodrobenIzpisNovic(Meni::GlavneStoritve::DOGODKI, tr_stran, P_SEZNAMI[Meni::GlavneStoritve::DOGODKI - 2]->size());

	while (true) {
		// Preveri če je kateri izmed gumbov stisjen (0x8000-najvišji bit drži to vrednost).
		if (GetKeyState(VK_LEFT) & 0x8000) {			// Puščica levo.
			tr_stran = Meni::ZmanjsajDoMeje(tr_stran, DobiSteviloVsehNovic(), min_st_strani);
			PodrobenIzpisNovic(Meni::GlavneStoritve::DOGODKI, tr_stran, P_SEZNAMI[Meni::GlavneStoritve::DOGODKI - 2]->size());

			Sleep(GUMB_DEBOUNCE);
		}
		else if (GetKeyState(VK_RIGHT) & 0x8000) {		// Puščica desno.
			tr_stran = Meni::PovecajDoMeje(tr_stran, DobiSteviloVsehNovic(), min_st_strani);
			PodrobenIzpisNovic(Meni::GlavneStoritve::DOGODKI, tr_stran, P_SEZNAMI[Meni::GlavneStoritve::DOGODKI - 2]->size());

			Sleep(GUMB_DEBOUNCE);
		}
		else if (GetKeyState(VK_ESCAPE) & 0x8000) {		// Esc.
			break;
		}
	}
}

void Meni::Zaposlitve()
{
	static const int min_st_strani = 1;
	int tr_stran = min_st_strani;

	system("cls");

	PodrobenIzpisNovic(Meni::GlavneStoritve::ZAPOSLITVE, tr_stran, P_SEZNAMI[Meni::GlavneStoritve::ZAPOSLITVE - 2]->size());

	while (true) {
		// Preveri če je kateri izmed gumbov stisjen (0x8000-najvišji bit drži to vrednost).
		if (GetKeyState(VK_LEFT) & 0x8000) {			// Puščica levo.
			tr_stran = Meni::ZmanjsajDoMeje(tr_stran, DobiSteviloVsehNovic(), min_st_strani);
			PodrobenIzpisNovic(Meni::GlavneStoritve::ZAPOSLITVE, tr_stran, P_SEZNAMI[Meni::GlavneStoritve::ZAPOSLITVE - 2]->size());

			Sleep(GUMB_DEBOUNCE);
		}
		else if (GetKeyState(VK_RIGHT) & 0x8000) {		// Puščica desno.
			tr_stran = Meni::PovecajDoMeje(tr_stran, DobiSteviloVsehNovic(), min_st_strani);
			PodrobenIzpisNovic(Meni::GlavneStoritve::ZAPOSLITVE, tr_stran, P_SEZNAMI[Meni::GlavneStoritve::ZAPOSLITVE - 2]->size());

			Sleep(GUMB_DEBOUNCE);
		}
		else if (GetKeyState(VK_ESCAPE) & 0x8000) {		// Esc.
			break;
		}
	}
}

void Meni::IskanjePoDatumu()
{
	system("cls");

	std::wstring vnos = L"";

	std::wcout << L"Vpiši datum <dan>.<mesec>.<leto>: ";
	std::wcin >> vnos;

	while (true) {	
		// Preveri če je kateri izmed gumbov stisjen (0x8000-najvišji bit drži to vrednost).
		if (GetKeyState(VK_UP) & 0x8000) {				// Puščica gor.
			Sleep(GUMB_DEBOUNCE);
		}
		else if (GetKeyState(VK_DOWN) & 0x8000) {		// Puščica dol.
			Sleep(GUMB_DEBOUNCE);
		}
		else if (GetKeyState(VK_RETURN) & 0x8000) {		// Enter.
			Sleep(GUMB_DEBOUNCE);
		}
		else if (GetKeyState(VK_ESCAPE) & 0x8000) {		// Esc.
			break;
		}
	}
}

void Meni::Pomoc()
{
	system("cls");

	while (true) {
		// Preveri če je kateri izmed gumbov stisjen (0x8000-najvišji bit drži to vrednost).
		if (GetKeyState(VK_UP) & 0x8000) {				// Puščica gor.
			Sleep(GUMB_DEBOUNCE);
		}
		else if (GetKeyState(VK_DOWN) & 0x8000) {		// Puščica dol.
			Sleep(GUMB_DEBOUNCE);
		}
		else if (GetKeyState(VK_RETURN) & 0x8000) {		// Enter.
			Sleep(GUMB_DEBOUNCE);
		}
		else if (GetKeyState(VK_ESCAPE) & 0x8000) {		// Esc.
			break;
		}
	}
}

void Meni::Nastavitve()
{
	system("cls");

	while (true) {
		// Preveri če je kateri izmed gumbov stisjen (0x8000-najvišji bit drži to vrednost).
		if (GetKeyState(VK_UP) & 0x8000) {				// Puščica gor.
			Sleep(GUMB_DEBOUNCE);
		}
		else if (GetKeyState(VK_DOWN) & 0x8000) {		// Puščica dol.
			Sleep(GUMB_DEBOUNCE);
		}
		else if (GetKeyState(VK_RETURN) & 0x8000) {		// Enter.
			Sleep(GUMB_DEBOUNCE);
		}
		else if (GetKeyState(VK_ESCAPE) & 0x8000) {		// Esc.
			break;
		}
	}
}

void Meni::TestniRezim()
{
	system("cls");

	while (true) {
		// Preveri če je kateri izmed gumbov stisjen (0x8000-najvišji bit drži to vrednost).
		if (GetKeyState(VK_UP) & 0x8000) {				// Puščica gor.
			Sleep(GUMB_DEBOUNCE);
		}
		else if (GetKeyState(VK_DOWN) & 0x8000) {		// Puščica dol.
			Sleep(GUMB_DEBOUNCE);
		}
		else if (GetKeyState(VK_RETURN) & 0x8000) {		// Enter.
			Sleep(GUMB_DEBOUNCE);
		}
		else if (GetKeyState(VK_ESCAPE) & 0x8000) {		// Esc.
			break;
		}
	}
}

void Meni::Izhod()
{
	ostani_v_prog = false;
}

void Meni::IzrisiCrto()
{
	int sirina;
	//od OS pridobimo informacijo o širini okna
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	sirina = csbi.srWindow.Right - csbi.srWindow.Left + 1;

	for (int i = 0; i < sirina; i++) { std::wcout << L"_"; }

	std::wcout << std::endl;
}