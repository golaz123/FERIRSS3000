#include "windows.h"
#include <iostream>
#include <io.h>
#include <fcntl.h>

#define IME_VERZIJA "FERI RSS, v0.1"
#define IME_VERZIJA_TR "FERI RSS, v0.1 (TR)"

class Meni
{
private:
	bool testni;
	void Glavni(); // spremenljivka testni pove èe smo v testnem režimu
	void Novice(int tip); // spremenljivka tip pove katere novice naj vse izpisuje
	void Iskanje();		  // 1 vse novice, 2 oglasna deska,3 novice
	void Pomoc();
	void Nastavitve();
	void Testni();
	void IzrisiCrto(); //po tekstovnem vmesniku izrise crto po celotni dolzini zaslona
	
public:

	Meni();
	
};

void Meni::Glavni()
{
	const std::wstring izbira[12] = {L"1. vse novice",
									 L"1. vse novice",
									 L"2. oglasna deska",
									 L"3. novica", 
									 L"4. obvestila za študente", 
									 L"5. dogodki",
									 L"6. zaposlitve",
									 L"7. iskanje po datumu", 
									 L"8. pomoè", 
									 L"9. testne režim", 
									 L"10. nastavitve", 
									 L"11. izhod"};
	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN);
	std::wcout << L"1. vse novice" << std::endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
	std::wcout << L"2. oglasna deska" << std::endl;
	std::wcout << L"3. novice" << std::endl;
	std::wcout << L"4. obvestila za študente" << std::endl;
	std::wcout << L"5. dogodki" << std::endl;
	std::wcout << L"6. zaposlitve" << std::endl;
	std::wcout << L"7. iskanje po datumu" << std::endl;
	std::wcout << L"8. pomoè" << std::endl;
	std::wcout << L"9. testni režim" << std::endl;
	std::wcout << L"10. nastavitve" << std::endl;
	std::wcout << L"11. izhod" << std::endl;
	IzrisiCrto();

	bool koncan = false;
	do {
		
	} while (!koncan);
}
void Meni::Novice( int tip)
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
	Glavni();
}

int wmain()
{
	Meni();
}