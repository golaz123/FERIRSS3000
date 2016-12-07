#pragma once

#include <Windows.h>
#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <string>

class Meni
{
private:
	// Možni režimi delovanja programa.
	enum Rezim { 
		NORMALNO, 
		TESTNO 
	};

	// Možne izbire v glavnem meniju.
	enum GlavneStoritve { 
		VSE_NOVICE = 1, 
		OGLASNA_DESKA, 
		NOVICE, 
		OBVESTILA, 
		DOGODKI, 
		ZAPOSLITVE, 
		ISKANJE, 
		POMOC, 
		TESTNI, 
		NASTAVITVE, 
		IZHOD,
		ST_STORITEV
	};
	
	typedef void (Meni::*izbira_menija)();	// Kazalec do funkcije za izpis novega menija ob izbiri.

	const std::string IME_VERZIJA = "FERI RSS, v0.1";			// Naslov odprtega okna v normalnem režimu.
	const std::string IME_VERZIJA_TR = "FERI RSS, v0.1 (TR)";	// Naslov odprtega okna v testnem režimu.
	const int GUMB_DEBOUNCE = 125;								// Kak dolgo poèakat preden znova preverit stanje gumboc (v ms).
	Rezim rezim;												// Trenutni režim delovanja programa.
	
	void Glavni();
	void VseNovice();
	void OglasnaDeska();
	void Novice();
	void ObvestilaZaStudente();
	void Dogodki();
	void Zaposlitve();
	void IskanjePoDatumu();
	void Pomoc();
	void Nastavitve();
	void TestniRezim();
	void Izhod();
	void IzrisiCrto();

	void PojdiXY(int x, int y);	// Pojdi na doloèeno x, y koordinato v konzoli.
	void Oznaci(int x, int y, std::wstring besedilo);
	void IzpisiXY(int x, int y, std::wstring besedilo);
	static int PovecajDoMeje(int tr_vrednost, int max_vrednost, int min_vrednost);
	static int ZmanjsajDoMeje(int tr_vrednost, int max_vrednost, int min_vrednost);
public:
	Meni();
	~Meni();
};