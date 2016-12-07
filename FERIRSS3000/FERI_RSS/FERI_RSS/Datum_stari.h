#pragma once
class Datum
{
private:
	unsigned dan;
	unsigned mesec;
	unsigned leto; //Pazi kje so meje (konstruktor)!
	
	bool PreveriDatum(unsigned dan, unsigned mesec, unsigned leto);

	static const unsigned PRIVZET_DAN = 1;
	static const unsigned PRIVZET_MESEC = 1; 
	static const unsigned PRIVZETO_LETO = 2015;
public:
	Datum(unsigned dan, unsigned mesec, unsigned leto);
	~Datum();
};

