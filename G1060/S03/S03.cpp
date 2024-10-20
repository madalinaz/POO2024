#include<iostream>
using namespace std;

enum TipMancare {
	CIORBA, PIZZA, PASTE, DESERT, BURGER, NA
};

enum Alergeni {
	LAPTE, ALUNE, SCOICI, MIERE, TELINA
};

class FelMancare {
	//siruri de caractere (static + dinamic)
	char* denumire;//dinamic
	char cod[20];
	//vector numeric (static/dinamic)
	//float* istoricPret;
	//int nrPreturi;
	//float pretMarimePortie[2];//vector numeric alocat static (pret pentru portia mica pe poz 0 si pret portie mare poz 1)
	//enumeratie
	TipMancare tipMancare;
	//vector de enumeratii
	//Alergeni* listaAlergeni;//alocare dinamica
	Alergeni listaAlergeni2[10];//alocare statica
	int nrAlergeni;
	//vector de siruri de caractere
	//string* listaIngrediente;
	//int nrIngrediente;
	//boolean
	bool laPachet;
	//vector de bool
	//.....

public:
	void initializare() {
		//rol de a initializa zona de memorie deja alocata pe stiva
		//denumire = nullptr;
		//sau
		denumire = new char[strlen("-") + 1];
		strcpy_s(denumire, strlen("-") + 1, "-");
		//cod[0] = '\0';
		strcpy_s(cod, strlen("-") + 1, "-");
		tipMancare = TipMancare::NA;
		nrAlergeni = 0;
		laPachet = false;
	}

	void afisare() {
		cout << "\nDenumire: " << denumire;
		cout << "\nCod: " << cod;
		cout << "\nTip mancare: " << tipMancare;
		cout << "\nNr alergeni: " << nrAlergeni;
		cout << "\nLista alergeni: ";
		for (int i = 0; i < nrAlergeni; i++)
			cout << listaAlergeni2[i] << " ";
		cout << "\nLa pachet? " << laPachet;
	}

	//metode accesor ->interfata a unui obiect/ sau a clasei
	//get si set
	//get ->consultare
	//set ->modificare
	bool getLaPachet() {
		return laPachet;
	}

	void setLaPachet(bool _laPachet) {
		laPachet = _laPachet;
	}

	const char* getCod() {
		return cod;
	}

	char* getCod2() {
		char copieCod[20];
		strcpy_s(copieCod, strlen(cod) + 1, cod);
		return copieCod;
	}

	void setCod(const char _cod[20]) {
		strcpy_s(cod, strlen(_cod) + 1, _cod);
	}

	const char* getDenumire() {
		return denumire;
	}

	void setDenumire(const char* _denumire) {
		if (_denumire != nullptr) {
			//denumire este alocat dinamic
			//trebuie dezalocat daca este nevoie pentru a nu avea
			//memory leaks
			if (denumire != nullptr) {
				delete[] denumire;
				denumire = nullptr;//pentru a evita dangling pointers
			}
			denumire = new char[strlen(_denumire) + 1];
			strcpy_s(denumire, strlen(_denumire) + 1, _denumire);
		}
	}
};

int main() {
	FelMancare m;//constructor default ->meth primita automat
	//initializare
	m.initializare();
	//afisare
	m.afisare();
	//metode accesor
	cout << endl << m.getLaPachet();
	m.setLaPachet(true);
	cout << endl << m.getLaPachet();

	cout << endl << m.getCod();
	m.setCod("C02");
	//m.getCod()[0] = 'M';
	cout << endl << m.getCod();
	const char* cod = m.getCod();
	//char* cod2 = m.getCod2();
	//cod2[0] = 'M';//am modificat o alta zona de memorie
	//cout << endl << m.getCod2();
	return 0;
}