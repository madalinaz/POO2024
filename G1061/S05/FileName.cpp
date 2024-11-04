#include<iostream>
using namespace std;

enum Departament {
	IT, HR, SALES
};


class Angajat {
	const int cod;//codul este unic si generat automat 1001, 1002, etc
	char* nume;
	Departament departament;
	float salariu;
	int nrBonusuri;
	float* listaBonusuri;
	static int nrAngajati;
	//static float salariuMediu; TO DO HOME
	//static float fondSalarii;//asta doar pentru angajatii curenti

public:
	//constr fara param
	Angajat():cod(1000+(++Angajat::nrAngajati)) {
		this->nume = new char[strlen("Anonim") + 1];
		strcpy_s(this->nume, strlen("Anonim") + 1, "Anonim");
		this->departament = Departament::SALES;
		this->salariu = 0;
		this->nrBonusuri = 0;
		this->listaBonusuri = nullptr;
	}
	//constr cu toti param
	Angajat(char* _nume, Departament _departament, 
		float _salariu, int _nrBonusuri, 
		float* _listaBonusuri):cod(1000 + (++Angajat::nrAngajati)) {
		if (_nume != nullptr) {
			this->nume = new char[strlen(_nume) + 1];
			strcpy_s(this->nume, strlen(_nume) + 1, _nume);
		}
		else {
			this->nume = new char[strlen("Anonim") + 1];
			strcpy_s(this->nume, strlen("Anonim") + 1, "Anonim");
		}
		this->departament = _departament;
		this->salariu = _salariu;
		if (_nrBonusuri > 0 && _listaBonusuri != nullptr) {
			this->nrBonusuri = _nrBonusuri;
			this->listaBonusuri = new float[this->nrBonusuri];
			for (int i = 0; i < this->nrBonusuri; i++)
				this->listaBonusuri[i] = _listaBonusuri[i];
		}
		else {
			this->nrBonusuri = 0;
			this->listaBonusuri = nullptr;
		}
	}
	//constr de copiere
	//meth afisare
	void afisare() {
		cout << "\n----------------";
		cout << "\nCod: " << this->cod;
		cout << "\nNume: " << this->nume;
		cout << "\nDepartament: " << this->departament;
		cout << "\nSalariu: " << this->salariu;
		cout << "\nNr bonusuri: " << this->nrBonusuri;
		cout << "\nLista bonusuri: ";
		for (int i = 0; i < this->nrBonusuri; i++)
			cout << this->listaBonusuri[i] << " ";
	}
	// meth pentru gestiune atribute statice
	// get si set pentru nume
	//destructor
};

int Angajat::nrAngajati = 0;

int main() {
	/*int x = 2;
	int y;
	y = 10;
	int z(10);*/

	Angajat a1;
	a1.afisare();
	return 0;
}