#include<iostream>
using namespace std;

enum Departament {
	IT, HR, SALES
};

enum Alergie {
	OU, TELINA, SCOICI
};

class FelMancare
{
	string denumire;
	int nrCalorii;
	int nrIngrediente;
	string* listaIngrediente;
	float* gramajIngrediente;
	int nrAlergeni;
	Alergie* listaAlergii;
	static int nrMediuCalorii;
	static int nrMinimCalorii;//folosit pentru validare la nrCalorii
	bool disponibilitate[12];//daca este sau nu disponibil felul de mancare pentru fiecare luna a anului
public:
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
	Angajat(const char* _nume, Departament _departament, 
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
	Angajat(const Angajat& a): cod(1000 + (++Angajat::nrAngajati)) {//folosesc & pentru ca vreau sa ocolesc copierea
		if (a.nume != nullptr) {
			this->nume = new char[strlen(a.nume) + 1];
			strcpy_s(this->nume, strlen(a.nume) + 1, a.nume);
		}
		else {
			this->nume = new char[strlen("Anonim") + 1];
			strcpy_s(this->nume, strlen("Anonim") + 1, "Anonim");
		}
		this->departament = a.departament;
		this->salariu = a.salariu;
		if (a.nrBonusuri > 0 && a.listaBonusuri != nullptr) {
			this->nrBonusuri = a.nrBonusuri;
			this->listaBonusuri = new float[this->nrBonusuri];
			for (int i = 0; i < this->nrBonusuri; i++)
				this->listaBonusuri[i] = a.listaBonusuri[i];
		}
		else {
			this->nrBonusuri = 0;
			this->listaBonusuri = nullptr;
		}
	}

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
	static int getNrAngajati() {
		return Angajat::nrAngajati;
	}

	// get si set pentru nume
	const char* getNume() {
		return this->nume;
	}

	char* getNume2() {
		char* copie = nullptr;
		if (this->nume != nullptr) {
			copie = new char[strlen(this->nume) + 1];
			strcpy_s(copie, strlen(this->nume) + 1, this->nume);
		}
		return copie;
	}

	//destructor
	~Angajat() {
		if (this->nume != nullptr) {
			delete[] this->nume;
			this->nume = nullptr;
		}

		if (this->listaBonusuri != nullptr) {
			delete[] this->listaBonusuri;
			this->listaBonusuri = nullptr;
		}
	}
};

int Angajat::nrAngajati = 0;

int main() {
	/*int x = 2;
	int y;
	y = 10;
	int z(10);*/

	Angajat a1;
	a1.afisare();

	float bonusuri[] = { 120.5,1000,1200 };
	Angajat a2("Gigel", Departament::IT, 12000, 3, bonusuri);
	a2.afisare();

	cout << endl << a2.getNume();
	cout << endl << a2.getNume2();
	const char* nume = a2.getNume();
	char* nume2 = a2.getNume2();
	cout << endl << nume2;
	//nu uitam dezalocarea din cauza lui getNume2
	if (nume2 != nullptr) {
		delete[] nume2;
		nume2 = nullptr;
	}

	cout << endl << "\nNr angajati: " << Angajat::getNrAngajati();

	Angajat a3(a2);//apel constructor de copiere
	Angajat a4 = a2;
	a4.afisare();
	return 0;
}