#pragma once

<<<<<<< HEAD
#include "PovezavaHTTP.h"
#include "ObdelavaXML.h"
#include "Datum.h"
#include "Novica.h"
=======
>>>>>>> origin/master
#include <Windows.h>
#include <stdio.h>
#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <string>
<<<<<<< HEAD
#include <thread>
#include <chrono>
#include <ctime>
#include <vector>
=======
#include <queue>
#include "Novica.h"
>>>>>>> origin/master

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
	

<<<<<<< HEAD
	static const std::string IME_VERZIJA;			// Naslov odprtega okna v normalnem režimu.
	static const std::string IME_VERZIJA_TR;		// Naslov odprtega okna v testnem režimu.
	static const std::string IME_VERZIJA_NP;		// Naslov odprtega okna, èe ni zaznane internetne povezave.
	static const int GUMB_DEBOUNCE = 125;			// Kak dolgo poèakat preden znova preverit stanje gumboc (v ms).
	static const int ST_KATEGORIJ_NOVIC = 5;		// Število kategorij novic.
	static std::vector<Novica>* const P_SEZNAMI[];	// Kazalci do seznamov novic.
	static const std::string NOVICE_SPL_NASLOVI[];	// Spletni naslovi kategorij novic.
	static const std::string NOVICE_LOK_IMENA[];	// Imena prenesenih datotek.
	static const std::string PRENOSNA_MAPA;			// Mapa kamor se prenešejo datoteke.
	static const std::string NAPAKA_DUMP;			// Datoteka kamor se izpišejo napake.
	static const int CAS_MED_PRENOSI = 30000;		// Koliko èasa naj preteèe med posamezni prenosi s spleta.
	static const int PREPR_NOVICA_Y = 14;			// Y koordinata konzole za preprosti izpis novice.
	static const int MAX_ST_NOVIC_STRAN = 6;		// Maximalno število podrobno izpisanih novic na eni strani.

	static bool ostani_v_prog;				// Èe naj še ostanem v programu ali ga zaprem.
	static int st_novic_stran;				// Število podrobno izpisanih novic na eno stran.

	// Seznami predelanih novic, za vsako kategorijo posebej.
	static std::vector<Novica> dogodki;
	static std::vector<Novica> odeska;
	static std::vector<Novica> novice;
	static std::vector<Novica> obvestila;
	static std::vector<Novica> zaposlitve;
=======
	typedef void (*izbira_menija)();			// Kazalec do funkcije za izpis novega menija ob izbiri.
>>>>>>> origin/master

	static const std::string IME_VERZIJA;		// Naslov odprtega okna v normalnem režimu.
	static const std::string IME_VERZIJA_TR;	// Naslov odprtega okna v testnem režimu.
	static const int GUMB_DEBOUNCE;				// Kak dolgo poèakat preden znova preverit stanje gumboc (v ms).
	//static Rezim rezim;						// Trenutni režim delovanja programa.
	static std::priority_queue<Novica> vrsta_novic;
	Meni() {}									// Prazen konstruktor

	// Eksplicitino prepovej kopiranje razreda.
	Meni(const Meni&) = delete;
	Meni& operator= (const Meni&) = delete;

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
<<<<<<< HEAD
	static void PrenosInObdelava();
	static void PreprostiIzpisNovic(GlavneStoritve tr_storitev);
	static void PodrobenIzpisNovic(GlavneStoritve tr_storitev, int tr_stran, int st_strani);
	static int DobiSteviloVsehNovic();
=======
	void IskalnaNit(std::wstring kljuc, std::wstring* povratno_sporocilo);
	static bool JeVeljavenVnosDatuma(std::wstring vnos);
>>>>>>> origin/master
public:
	static void GlavniMeni();

};