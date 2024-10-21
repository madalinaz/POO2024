#include<iostream>
using namespace std;

enum TipMancare {
	CIORBA, PIZZA, PASTE, DESERT
};

enum Ingredient {
	FAINA, OUA, LAPTE, CARNE, BRANZA
};

class FelMancare {
	//vector static de caractere
	//char cod[10];
	//vector dinamic de caractere
	//char* denumire2;
	string denumire;
	//vector numeric static
	int valoriNutritionale[3];//dimensiune fixa ce reprezinta nr de categorii (glucide, lipide, proteine)
	//vector numeric dinamic
	///float* cantitateIngrediente;
	//int nrIngrediente;
	//enumeratie
	TipMancare tipMancare;
	//vector enumeratii (static + dinamic)
	//Ingredient* listaIngrediente;
	//int nrIngrediente;
	//vector de siruri de caractere 
	string* listaAlergeni;
	int nrAlergeni;
	//bool
	//bool esteVegana;
	//vector de bool
	//bool disponibilitate[12];

public:
	void initializare() {
		denumire = "-";
		for (int i = 0; i < 3; i++)
			valoriNutritionale[i] = 0;
		tipMancare = TipMancare::PASTE;
		nrAlergeni = 0;
		listaAlergeni = nullptr;
	}

	string getDenumire() {
		return denumire;
	}

	void setDenumire(string _denumire) {
		if (_denumire.size() >= 3)
			denumire = _denumire;
	}

	int getNrAlergeni() {
		return nrAlergeni;
	}

	const string* getListaAlergeni() {
		return listaAlergeni;
	}

	void setAlergeni(int _nrAlergeni, string* _listaAlergeni) {
		if (_nrAlergeni > 0 && _listaAlergeni != nullptr) {
			//pentru a nu avea memory leaks
			if (listaAlergeni != nullptr) {
				delete[] listaAlergeni;
				listaAlergeni = nullptr;
			}

			nrAlergeni = _nrAlergeni;
			//shallow copy
			//listaAlergeni = _listaAlergeni;//partajam aceeasi zona de memorie
			//deep copy
			listaAlergeni = new string[nrAlergeni];
			for (int i = 0; i < nrAlergeni; i++)
				listaAlergeni[i] = _listaAlergeni[i];
		}
	}

	void afisare() {
		cout << "\n---------------";
		cout << "\nDenumire: " << denumire;
		cout << "\nValori nutritionale: ";
		for (int i = 0; i < 3; i++)
			cout << valoriNutritionale[i] << " ";
		cout << "\nTip mancare: " << tipMancare;
		cout << "\nNr alergeni: " << nrAlergeni;
		cout << "\nLista alergeni: ";
		for (int i = 0; i < nrAlergeni; i++)
			cout << listaAlergeni[i] << " ";
		cout << "\n---------------";
	}
};

int main() {
	//initializare obj
	FelMancare f1;//apel constructor implicit
	f1.initializare();

	//afisare obj
	f1.afisare();

	//metode accesor (get si set)
	//get rol de consultare
	cout << endl << f1.getDenumire();
	//set rol de modificare/atribuire
	f1.setDenumire("Pizza");
	cout << endl << f1.getDenumire();

	string* listaAlergeni = new string[3]{ "Telina","Scoici","Oua" };
	f1.setAlergeni(3, listaAlergeni);
	cout << endl << f1.getNrAlergeni();
	cout << endl << f1.getListaAlergeni();
	for (int i = 0; i < f1.getNrAlergeni(); i++)
		cout << endl << f1.getListaAlergeni()[i];
	//f1.getListaAlergeni()[0] = "Pacaleala";
	f1.afisare();
	return 0;
}