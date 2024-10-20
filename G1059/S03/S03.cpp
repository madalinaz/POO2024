#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
#include <cstring>

enum Culoare {
	ALB, NEGRU, GRI, ROSU, NA //NA=not avalabile
};

class Masina {
	//vector static
	//vector dinamic
	//sir de caractere
	char* model; //sir de caractere alocat dinamic
	char nrInmatriculare[9]; //alocare statica
	int cc; //capacitate cilindrica
	float* costReparatii;
	int nrReparatii;
	bool esteAccidentata;
	Culoare culoare;

public:
	void initializare() {
		//rol de initializare obiect nou construit
		//model = nullptr;
		//in loc de nullptr putem scrie:
		model = new char[strlen("-") + 1]; //(2 octeti)
		strcpy(model, "-");

		nrInmatriculare[0] = '\0';
		//sau strcpy(nrInmatriculare, "-");

		cc = 0; //int-urile sunt initializate cu 0

		costReparatii = nullptr; //la nivel de vector numeric, alocat static sau dinaic, plecam de la "nullptr"
		nrReparatii = 0;

		esteAccidentata = false;

		culoare = Culoare::NA;
	}

	void afisare() {
		cout << "\nModel: " << model; //daca era nullptr trebuia o verificare suplimentara
		cout << "\nNr inmatriculare: " << nrInmatriculare;
		cout << "\nCapacitate cilindrica: " << cc;
		//cout<<"\nCost reparatii: "<< costReparatii; daca scriem asa, va afisa adresa primului element din vector
		cout << "\nCost reparatii: ";
		for (int i = 0; i < nrReparatii; i++)
			cout << costReparatii[i] << " ";
		cout << "\nNr reparatii: " << nrReparatii;
		cout << "\nEste accidentata: " << esteAccidentata;
		cout << "\nCuloare: " << culoare;
	}

	//meth accesor (get si set)
	//get->consultare
	//set->modificare

	int getCc() {   //get are rolul de a extrage din obiectul curent doar acel atribut pe care ni-l dorim
		return cc;
	}
	void setCc(int ccNoua) {  //set are rolul de a modifica 
		if (ccNoua >= 500)
			cc = ccNoua;
	}



	Culoare getCuloare() {
		return culoare;
	}

	void setCuloare(Culoare culoareNoua) {
		culoare = culoareNoua;
	}



	char* getModel() {
		return model;
	}

	void setModel(const char* modelNou) { //pentru ca model este alocat dinamic, trebuie sa dezalocam
		if (modelNou != nullptr && strlen(modelNou) >= 3) {
			if (model != nullptr) { //verificam daca avem ce dezaloca
				delete[] model;
				model = nullptr;
			}
			model = new char[strlen(modelNou) + 1];
			strcpy(model, "-");
		}
	}
};

int main() {
	Masina m; //constructor fara parametrii sau constructor default; insumeaza octetii tuturor atributelor; nu initializeaza zona de memorie asa cum ne dorim noi
	//initializare
	m.initializare(); //!!SA NU UITAM DE ()
	//afisare
	m.afisare();
	//metode accesor
	m.setCc(1200);
	cout << endl << m.getCc();

	m.setCuloare(Culoare::GRI); //cand utilizam set pentru un enum, NEAPARAT IN PARANTEZA SCRIEM NUMELE ENUM::(CULOAREA NOUA)
	cout << endl << m.getCuloare();

	m.setModel("Audi"); //daca vrem sa apelam un setter folosind un sir constant cum e Audi trebuie sa initializam ca fiind constant in setterul nostru
	cout << endl << m.getModel();


	//TEMA: o clasa care sa contina: vector static,vector dinamic,sir de caractere(si cu * si fara), vector de bool, enumeratie, metoda de initializare, metoda de afisare,setter+getter pentru atribut
	return 0;
}