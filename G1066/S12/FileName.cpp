#include<iostream>
using namespace std;

enum TipCarburant {
	BENZINA95,
	BENZINA99,
	MOTORINA
};

class Rezervor {
	int id;
	TipCarburant tipCarburant;
	float capacitateCurenta;
	float capacitateMaxima;

	//op +=
	//op -=
};

//clasa optionala
class PompaAlimentare {
	const int id;
	bool esteOcupata;
	static int nrPompe;

	//
	//preluareCarburant()
	//ocuparePompa() ->apeleaza op -= din Rezervor
};

class Benzinarie {
	int nrCarburanti;
	float* pretCarburanti;
	string denumire;
	int nrRezervoare;
	Rezervor* listaRezervoare;
	int nrPompe;
	PompaAlimentare* pompeAlimentare;

	//procesul de vanzare
	//void vanzare(int nrPompa, float cantitate, TipCarburant tip)

	//proces alimentare rezervoare
	//void alimentare(float cantitate, TipCarburant tip)
};