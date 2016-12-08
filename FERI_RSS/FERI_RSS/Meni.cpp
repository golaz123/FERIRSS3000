#include "Meni.h"
#include <thread>

const std::string Meni::IME_VERZIJA = "FERI RSS, v0.1";			// Naslov odprtega okna v normalnem re�imu.
const std::string Meni::IME_VERZIJA_TR = "FERI RSS, v0.1 (TR)";	// Naslov odprtega okna v testnem re�imu.
const int Meni::GUMB_DEBOUNCE = 175;								// Kak dolgo po�akat preden znova preverit stanje gumboc (v ms).

void Meni::GlavniMeni()
{
	GlavneStoritve tr_storitev = GlavneStoritve::VSE_NOVICE;				// Trenutno ozna�ena storitev.
	const std::wstring glavne_storitve[GlavneStoritve::ST_STORITEV] = {	// Storitve izpiane na zaslonu.
		L"1. vse novice",
		L"2. oglasna deska",
		L"3. novice",
		L"4. obvestila za �tudente",
		L"5. dogodki",
		L"6. zaposlitve",
		L"7. iskanje po datumu",
		L"8. pomo�",
		L"9. testne re�im",
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

	for (int i = 0; i < Meni::GlavneStoritve::ST_STORITEV; i++) { std::wcout << glavne_storitve[i] << std::endl; }
	
	Oznaci(0, tr_storitev - 1, glavne_storitve[tr_storitev - 1]);

	while (true) {
		// Preveri �e je kateri izmed gumbov stisjen (0x8000-najvi�ji bit dr�i to vrednost).
		if (GetKeyState(VK_UP) & 0x8000) {				// Pu��ica gor.
			IzpisiXY(0, tr_storitev - 1, glavne_storitve[tr_storitev - 1]);	// Odozna�i prej�njo vrednost.
			tr_storitev = static_cast<GlavneStoritve>(ZmanjsajDoMeje(tr_storitev, GlavneStoritve::ST_STORITEV - 1, GlavneStoritve::VSE_NOVICE));
			Oznaci(0, tr_storitev - 1, glavne_storitve[tr_storitev - 1]);	// Ozna�i novo vrednost.

			Sleep(GUMB_DEBOUNCE);
		} else if (GetKeyState(VK_DOWN) & 0x8000) {		// Pu��ica dol.
			IzpisiXY(0, tr_storitev - 1, glavne_storitve[tr_storitev - 1]);	// Odozna�i prej�njo vrednost.
			tr_storitev = static_cast<GlavneStoritve>(PovecajDoMeje(tr_storitev, GlavneStoritve::ST_STORITEV - 1, GlavneStoritve::VSE_NOVICE));
			Oznaci(0, tr_storitev - 1, glavne_storitve[tr_storitev - 1]);	// Ozna�i novo vrednost.

			Sleep(GUMB_DEBOUNCE);
		} else if (GetKeyState(VK_RETURN) & 0x8000) {	// Enter.
			Sleep(GUMB_DEBOUNCE);	// Potrebno je prej debounce, da se ne po pomoti �teje kot stisk tipke v podmeniju.

			(p_podmeniji[tr_storitev - 1])(); //Klic funkcije podmenija(functor)

			system("cls");

			for (int i = 0; i < Meni::GlavneStoritve::ST_STORITEV; i++) { std::wcout << glavne_storitve[i] << std::endl; }

			Oznaci(0, tr_storitev - 1, glavne_storitve[tr_storitev - 1]);

			Sleep(GUMB_DEBOUNCE);
		}
	}
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

	std::wcout << besedilo;		// Preipi�e morebitno �e obstoje�o besedilo v vrstici.

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
}

void Meni::IzpisiXY(int x, int y, std::wstring besedilo)
{
	Meni::PojdiXY(x, y);

	std::wcout << besedilo;
}

void Meni::VseNovice()
{
	system("cls");

	while (true) {
		// Preveri �e je kateri izmed gumbov stisjen (0x8000-najvi�ji bit dr�i to vrednost).
		if (GetKeyState(VK_UP) & 0x8000) {				// Pu��ica gor.
			Sleep(GUMB_DEBOUNCE);
		}
		else if (GetKeyState(VK_DOWN) & 0x8000) {		// Pu��ica dol.
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

void Meni::OglasnaDeska()
{
	system("cls");

	while (true) {
		// Preveri �e je kateri izmed gumbov stisjen (0x8000-najvi�ji bit dr�i to vrednost).
		if (GetKeyState(VK_UP) & 0x8000) {				// Pu��ica gor.
			Sleep(GUMB_DEBOUNCE);
		}
		else if (GetKeyState(VK_DOWN) & 0x8000) {		// Pu��ica dol.
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

void Meni::Novice()
{
	system("cls");

	while (true) {
		// Preveri �e je kateri izmed gumbov stisjen (0x8000-najvi�ji bit dr�i to vrednost).
		if (GetKeyState(VK_UP) & 0x8000) {				// Pu��ica gor.
			Sleep(GUMB_DEBOUNCE);
		}
		else if (GetKeyState(VK_DOWN) & 0x8000) {		// Pu��ica dol.
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

void Meni::ObvestilaZaStudente()
{
	system("cls");

	while (true) {
		// Preveri �e je kateri izmed gumbov stisjen (0x8000-najvi�ji bit dr�i to vrednost).
		if (GetKeyState(VK_UP) & 0x8000) {				// Pu��ica gor.
			Sleep(GUMB_DEBOUNCE);
		}
		else if (GetKeyState(VK_DOWN) & 0x8000) {		// Pu��ica dol.
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

void Meni::Dogodki()
{
	system("cls");

	while (true) {
		// Preveri �e je kateri izmed gumbov stisjen (0x8000-najvi�ji bit dr�i to vrednost).
		if (GetKeyState(VK_UP) & 0x8000) {				// Pu��ica gor.
			Sleep(GUMB_DEBOUNCE);
		}
		else if (GetKeyState(VK_DOWN) & 0x8000) {		// Pu��ica dol.
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

void Meni::Zaposlitve()
{
	system("cls");

	while (true) {
		// Preveri �e je kateri izmed gumbov stisjen (0x8000-najvi�ji bit dr�i to vrednost).
		if (GetKeyState(VK_UP) & 0x8000) {				// Pu��ica gor.
			Sleep(GUMB_DEBOUNCE);
		}
		else if (GetKeyState(VK_DOWN) & 0x8000) {		// Pu��ica dol.
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

void Meni::IskalnaNit(std::wstring kljuc, std::wstring* povratno_sporocilo)
{
	//	preveri �e je vnos datuma veljaven
	if (!JeVeljavenVnosDatuma(kljuc))
		*povratno_sporocilo = std::wstring(L"Napa�en vnos datuma");
	else
		*povratno_sporocilo = std::wstring(L"ASD");
}
bool Meni::JeVeljavenVnosDatuma(std::wstring vnos)
{

	return true;
}
void Meni::IskanjePoDatumu()
{
	system("cls");

	std::wstring vnos = L"";

	std::wcout << L"Vpi�i datum <dan>.<mesec>.<leto>: ";
	std::wcin >> vnos;
	std::wstring* _povratno_sporocilo = new std::wstring();
	//std::thread t1(IskalnaNit, vnos, _povratno_sporocilo); // ustvarimo novo nit, ki i��e po klju�u vnos
	//t1.join();

	while (true) {	
		// Preveri �e je kateri izmed gumbov stisjen (0x8000-najvi�ji bit dr�i to vrednost).
		if (GetKeyState(VK_UP) & 0x8000) {				// Pu��ica gor.
			Sleep(GUMB_DEBOUNCE);
		}
		else if (GetKeyState(VK_DOWN) & 0x8000) {		// Pu��ica dol.
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
		// Preveri �e je kateri izmed gumbov stisjen (0x8000-najvi�ji bit dr�i to vrednost).
		if (GetKeyState(VK_UP) & 0x8000) {				// Pu��ica gor.
			Sleep(GUMB_DEBOUNCE);
		}
		else if (GetKeyState(VK_DOWN) & 0x8000) {		// Pu��ica dol.
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
		// Preveri �e je kateri izmed gumbov stisjen (0x8000-najvi�ji bit dr�i to vrednost).
		if (GetKeyState(VK_UP) & 0x8000) {				// Pu��ica gor.
			Sleep(GUMB_DEBOUNCE);
		}
		else if (GetKeyState(VK_DOWN) & 0x8000) {		// Pu��ica dol.
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
		// Preveri �e je kateri izmed gumbov stisjen (0x8000-najvi�ji bit dr�i to vrednost).
		if (GetKeyState(VK_UP) & 0x8000) {				// Pu��ica gor.
			Sleep(GUMB_DEBOUNCE);
		}
		else if (GetKeyState(VK_DOWN) & 0x8000) {		// Pu��ica dol.
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
	std::exit(0);
}

void Meni::IzrisiCrto()
{
	int sirina;
	//od OS pridobimo informacijo o �irini okna
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	sirina = csbi.srWindow.Right - csbi.srWindow.Left + 1;

	for (int i = 0; i < sirina; i++) { std::wcout << L"_"; }

	std::wcout << std::endl;
}