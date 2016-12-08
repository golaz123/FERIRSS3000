#pragma once

#include "PovezavaHTTP.h"
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
	
	typedef void (*izbira_menija)();	// Kazalec do funkcije za izpis novega menija ob izbiri.

	static const std::string IME_VERZIJA;			// Naslov odprtega okna v normalnem režimu.
	static const std::string IME_VERZIJA_TR;		// Naslov odprtega okna v testnem režimu.
	static const int GUMB_DEBOUNCE;					// Kak dolgo poèakat preden znova preverit stanje gumboc (v ms).
	static const int ST_KATEGORIJ_NOVIC;			// Število kategorij novic.
	static const std::string novice_spl_naslovi[];	// Spletni naslovi kategorij novic.
	static const std::string novice_lok_imena[];
	static const std::string prenosna_mapa;

	Meni() {}

	static void VseNovice();
	static void OglasnaDeska();
	static void Novice();
	static void ObvestilaZaStudente();
	static void Dogodki();
	static void Zaposlitve();
	static void IskanjePoDatumu();
	static void Pomoc();
	static void Nastavitve();
	static void TestniRezim();
	static void Izhod();
	static void IzrisiCrto();

	static void PojdiXY(int x, int y);	// Pojdi na doloèeno x, y koordinato v konzoli.
	static void Oznaci(int x, int y, std::wstring besedilo);
	static void IzpisiXY(int x, int y, std::wstring besedilo);
	static int PovecajDoMeje(int tr_vrednost, int max_vrednost, int min_vrednost);
	static int ZmanjsajDoMeje(int tr_vrednost, int max_vrednost, int min_vrednost);
	static void PrenesiNovice();
public:
	static void GlavniMeni();
};