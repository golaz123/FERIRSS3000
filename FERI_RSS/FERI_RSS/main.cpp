#include "windows.h"
#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <string>

#define IME_VERZIJA "FERI RSS, v0.1"
#define IME_VERZIJA_TR "FERI RSS, v0.1 (TR)"

class Meni
{
private:
	enum izbran {ASD, VSE_NOVICE, OGLASNA_DESKA, NOVICE, OBVESTILA, DOGODKI, ZAPOSLITVE, ISKANJE, POMOC, TESTNI, NASTAVITVE, IZHOD }; //ASD je dodan, da je VSE_NOVICE = 1
	bool testni;
	void Glavni(int izbran); // Oznaèen element v glavnem meniju
	void Novice(int tip); // spremenljivka tip pove katere novice naj vse izpisuje
	void Iskanje();		  // 1 vse novice, 2 oglasna deska,3 novice
	void Pomoc();
	void Nastavitve();
	void Testni();
	void IzrisiCrto(); //po tekstovnem vmesniku izrise crto po celotni dolzini zaslona
	
public:

	Meni();
	
};

void Meni::Glavni(int izbran)
{
	std::wstring izbira[12] =		{L"1. vse novice",
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
									 L"11. izhod"};
	/////////////////*******IZRIS********/////////////////////////////
	system("cls");
	for (int i = 1; i<12; i++) {
		if (i == izbran) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN);
			std::wcout << izbira[i] << std::endl;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
		}
		else {
			std::wcout << izbira[i] << std::endl;
		}
	}
	IzrisiCrto();
	////////////////////////////////////////////////////////////////////
	while (true) {
		if		(GetKeyState(VK_UP) == ) {
			if (izbran > 1)
				Glavni(izbran--);
		}
		else if (GetKeyState(VK_DOWN)) {
			if (izbran < 11)
				Glavni(izbran++);
		}
		else if (GetKeyState(VK_RETURN)) { //tipka enter

		}
		
	} 
}
void Meni::Novice(int tip)
{
}
void Meni::Iskanje()
{
}
void Meni::Pomoc()
{
}
void Meni::Nastavitve()
{
}
void Meni::Testni()
{
}
void Meni::IzrisiCrto()
{
	int sirina;
	//od OS pridobimo informacijo o širini okna
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	sirina = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	for (int i = 0; i < sirina; i++)
		std::wcout << L"_";
	std::wcout << std::endl;

}



Meni::Meni()
{
	SetConsoleTitle(IME_VERZIJA);
	setlocale(LC_ALL,""); // potrebno za izpis v UNICODE
	testni = false;
	Glavni(VSE_NOVICE);
}

int wmain()
{
	Meni();
}