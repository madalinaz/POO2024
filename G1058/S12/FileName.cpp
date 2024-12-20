#include<iostream>
using namespace std;
enum Tipcombustibil { diesel, benzina, gpl, altele };

class Rezervor {
	Tipcombustibil tipcomb;
	float capacitateMaxima;
	float nivelcurent;
	//operator +=;
	//operator -=;
	//operator !;

};
class Pompa {//clasa optionala
	int cod;
	bool estelibera;
};

//relatie has a
class benzinarie {
	string denumire;
	int nrrezervoare;
	Rezervor* listarezervoare;//vector de rezervor
	float listaPreturi[4];
	int nrpompe;
	//Pompa* listaPompe;
	//bool* disponibilitatePompe;
	static float alimentareMaxima;
	float vanzari[3];
public:
	void suplimentareRezervor(float cantitate, int pozitie)//apeleaza operatorul += din clasa rezervor
	{ }
	void alimentare(float cantitate, Tipcombustibil tip, int nrPompa) {
		//am alimentate cu 10 litri de benzina la pompa 2
		//apeleaza operatorul-=
		//actualizare vector vanzari
	}
	//generare raport vanzari
	void generareRaportInFisier(string denumireFisier) {
		//scriere in fisier txt
	}
};


int main() {

	return 0;
}