#include<iostream>
using namespace std;

enum TipCarburant {
	BENZINA95, BENZINA99, MOTORINA
};

class Rezervor {
	const int id;
	TipCarburant tipCarburant;
	float capacitateMaxima;
	float capacitateCurenta;

	//operator +=
	//operator -=
	//operator !
};

//clasa optionala
class Pompa {
	const int id;
	bool esteOcupata;
};

class Benzinarie {
	//char* denumire;
	string denumire;
	int nrRezervoare;
	//Rezervor* listaRezervoare;
	Rezervor listaRezervoare[3];
	int nrPompe;
	bool* disponibilitatePompe;
	//Pompa* listaPompe;
	float preturiCarburant[3];//vector static
	static float capacitateMaximaAlimentare;
	float vanzari[3];

	//alimentareRezervor(tipCarburant, float capacitate) ->apeleaza op +=
	//alimentareMasina(int nrPompa, tipCarburant, float capacitate) ->apeleaza op -=
};

int main() {
	return 0;
}