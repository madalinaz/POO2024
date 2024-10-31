#include<iostream>
using namespace std;

enum TipLocuinta {
	AP, CASA
};

class Locuinta {
	const int codUnic;
	char* adresa;
	TipLocuinta tip;
	float suprafata;
	static int nrLocuinte;
	static float suprafataMinima;
	static float suprafataMaxima;
	//static float suprafataMedie;


public:
	//constr fara param
	
	//constr cu toti param
	//constr de copiere
	//op =
	// get si set pentru adresa
	// get pentru membrii statici
	// meth afisare
	//destructor
};

int main() {
	return 0;
}