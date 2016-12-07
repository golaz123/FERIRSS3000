#include "Meni.h"


Meni::Meni()
{
	SetConsoleTitle(IME_VERZIJA.c_str());
	setlocale(LC_ALL, "");

	rezim = TESTNO;

	Glavni();
}

Meni::~Meni()
{
}

void Meni::Glavni()
{
	GlavneStoritve tr_storitev = GlavneStoritve::VSE_NOVICE;				// Trenutno oznaèena storitev.
	const std::wstring glavne_storitve[GlavneStoritve::ST_STORITEV] = {	// Storitve izpiane na zaslonu.
		L"1. vse novice",
		L"2. oglasna deska",
		L"3. novice",
		L"4. obvestila za študente",
		L"5. dogodki",
		L"6. zaposlitve",
		L"7. iskanje po datumu",
		L"8. pomoè",
		L"9. testne režim",
		L"10. nastavitve",
		L"11. izhod"
	};
	const izbira_menija p_podmeniji[] = {	// Konstantni kazalci k funckijam, za izpis podmenijev.
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


	system("cls");

	for (int i = 0; i < Meni::GlavneStoritve::ST_STORITEV; i++) { std::wcout << glavne_storitve[i] << std::endl; }
	
	Oznaci(0, tr_storitev - 1, glavne_storitve[tr_storitev - 1]);

	while (true) {
		// Preveri èe je kateri izmed gumbov stisjen (0x8000-najvišji bit drži to vrednost).
		if (GetKeyState(VK_UP) & 0x8000) {				// Pušèica gor.
			IzpisiXY(0, tr_storitev - 1, glavne_storitve[tr_storitev - 1]);	// Odoznaèi prejšnjo vrednost.
			tr_storitev = static_cast<GlavneStoritve>(ZmanjsajDoMeje(tr_storitev, GlavneStoritve::ST_STORITEV - 1, GlavneStoritve::VSE_NOVICE));
			Oznaci(0, tr_storitev - 1, glavne_storitve[tr_storitev - 1]);	// Oznaèi novo vrednost.

			Sleep(GUMB_DEBOUNCE);
		} else if (GetKeyState(VK_DOWN) & 0x8000) {		// Pušèica dol.
			IzpisiXY(0, tr_storitev - 1, glavne_storitve[tr_storitev - 1]);	// Odoznaèi prejšnjo vrednost.
			tr_storitev = static_cast<GlavneStoritve>(PovecajDoMeje(tr_storitev, GlavneStoritve::ST_STORITEV - 1, GlavneStoritve::VSE_NOVICE));
			Oznaci(0, tr_storitev - 1, glavne_storitve[tr_storitev - 1]);	// Oznaèi novo vrednost.

			Sleep(GUMB_DEBOUNCE);
		} else if (GetKeyState(VK_RETURN) & 0x8000) {	// Enter.
			Sleep(GUMB_DEBOUNCE);	// Potrebno je prej debounce, da se ne po pomoti šteje kot stisk tipke v podmeniju.

			(this->*p_podmeniji[tr_storitev - 1])();

			system("cls");

			for (int i = 0; i < Meni::GlavneStoritve::ST_STORITEV; i++) { std::wcout << glavne_storitve[i] << std::endl; }

			Oznaci(0, tr_storitev - 1, glavne_storitve[tr_storitev - 1]);

			Sleep(GUMB_DEBOUNCE);
		} else if (GetKeyState(VK_ESCAPE) & 0x8000) {	// Esc.
			std::exit(0);
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

	std::wcout << besedilo << std::endl;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
}

void Meni::IzpisiXY(int x, int y, std::wstring besedilo)
{
	Meni::PojdiXY(x, y);

	std::wcout << besedilo << std::endl;
}

void Meni::VseNovice()
{
	system("cls");

	while (true) {
		// Preveri èe je kateri izmed gumbov stisjen (0x8000-najvišji bit drži to vrednost).
		if (GetKeyState(VK_UP) & 0x8000) {				// Pušèica gor.
			Sleep(GUMB_DEBOUNCE);
		}
		else if (GetKeyState(VK_DOWN) & 0x8000) {		// Pušèica dol.
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
		// Preveri èe je kateri izmed gumbov stisjen (0x8000-najvišji bit drži to vrednost).
		if (GetKeyState(VK_UP) & 0x8000) {				// Pušèica gor.
			Sleep(GUMB_DEBOUNCE);
		}
		else if (GetKeyState(VK_DOWN) & 0x8000) {		// Pušèica dol.
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
		// Preveri èe je kateri izmed gumbov stisjen (0x8000-najvišji bit drži to vrednost).
		if (GetKeyState(VK_UP) & 0x8000) {				// Pušèica gor.
			Sleep(GUMB_DEBOUNCE);
		}
		else if (GetKeyState(VK_DOWN) & 0x8000) {		// Pušèica dol.
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
		// Preveri èe je kateri izmed gumbov stisjen (0x8000-najvišji bit drži to vrednost).
		if (GetKeyState(VK_UP) & 0x8000) {				// Pušèica gor.
			Sleep(GUMB_DEBOUNCE);
		}
		else if (GetKeyState(VK_DOWN) & 0x8000) {		// Pušèica dol.
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
		// Preveri èe je kateri izmed gumbov stisjen (0x8000-najvišji bit drži to vrednost).
		if (GetKeyState(VK_UP) & 0x8000) {				// Pušèica gor.
			Sleep(GUMB_DEBOUNCE);
		}
		else if (GetKeyState(VK_DOWN) & 0x8000) {		// Pušèica dol.
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
		// Preveri èe je kateri izmed gumbov stisjen (0x8000-najvišji bit drži to vrednost).
		if (GetKeyState(VK_UP) & 0x8000) {				// Pušèica gor.
			Sleep(GUMB_DEBOUNCE);
		}
		else if (GetKeyState(VK_DOWN) & 0x8000) {		// Pušèica dol.
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

void Meni::IskanjePoDatumu()
{
	system("cls");

	std::string vnos = "";

	std::wcout << L"Vpiši datum <dan>.<mesec>.<leto>: ";
	std::cin >> vnos;

	while (true) {	
		// Preveri èe je kateri izmed gumbov stisjen (0x8000-najvišji bit drži to vrednost).
		if (GetKeyState(VK_UP) & 0x8000) {				// Pušèica gor.
			Sleep(GUMB_DEBOUNCE);
		}
		else if (GetKeyState(VK_DOWN) & 0x8000) {		// Pušèica dol.
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
		// Preveri èe je kateri izmed gumbov stisjen (0x8000-najvišji bit drži to vrednost).
		if (GetKeyState(VK_UP) & 0x8000) {				// Pušèica gor.
			Sleep(GUMB_DEBOUNCE);
		}
		else if (GetKeyState(VK_DOWN) & 0x8000) {		// Pušèica dol.
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
		// Preveri èe je kateri izmed gumbov stisjen (0x8000-najvišji bit drži to vrednost).
		if (GetKeyState(VK_UP) & 0x8000) {				// Pušèica gor.
			Sleep(GUMB_DEBOUNCE);
		}
		else if (GetKeyState(VK_DOWN) & 0x8000) {		// Pušèica dol.
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
		// Preveri èe je kateri izmed gumbov stisjen (0x8000-najvišji bit drži to vrednost).
		if (GetKeyState(VK_UP) & 0x8000) {				// Pušèica gor.
			Sleep(GUMB_DEBOUNCE);
		}
		else if (GetKeyState(VK_DOWN) & 0x8000) {		// Pušèica dol.
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
	//od OS pridobimo informacijo o širini okna
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	sirina = csbi.srWindow.Right - csbi.srWindow.Left + 1;

	for (int i = 0; i < sirina; i++) { std::wcout << L"_"; }

	std::wcout << std::endl;
}