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
	
public:
	//constr fara param
	Angajat() :cod(1000 + (++Angajat::nrAngajati)) {
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
		float* _listaBonusuri) :cod(1000 + (++Angajat::nrAngajati)) {
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
	Angajat(const Angajat& a) : cod(1000 + (++Angajat::nrAngajati)) {//folosesc & pentru ca vreau sa ocolesc copierea
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

	//operator=
	Angajat& operator=(const Angajat& a) {
		if (this != &a) 
		{
			//lucreaza pe obj existente, atunci avem in vedere
			//posibile dezalocari
			if (this->nume != nullptr) {
				delete[] this->nume;
				this->nume = nullptr;
			}
			if (this->listaBonusuri != nullptr) {
				delete[] this->listaBonusuri;
				this->listaBonusuri = nullptr;
			}
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
		return *this;
	}

	//operator comparatie
	bool operator!=(const char* _altNume) {
		if (this->nume != nullptr && _altNume != nullptr) {
			if (strcmp(this->nume, _altNume) != 0)
				return true;
			else
				return false;
		}
		return false;
	}

	//redimensionare vector alocat dinamic
	Angajat& operator+=(float _altBonus) {
		if (_altBonus > 0) {
			Angajat copie = *this;
			if (this->listaBonusuri != nullptr) {
				delete[] this->listaBonusuri;
				this->listaBonusuri = nullptr;
			}
			this->listaBonusuri = new float[this->nrBonusuri + 1];
			for (int i = 0; i < this->nrBonusuri; i++)
				this->listaBonusuri[i] = copie.listaBonusuri[i];
			this->listaBonusuri[this->nrBonusuri] = _altBonus;
			this->nrBonusuri++;
		}
		return *this;
	}

	bool operator!=(const Angajat& a) {
		if (strcmp(this->nume, a.nume) != 0)
			return true;
		if (this->salariu != a.salariu)
			return true;
		//....pentru toate celelalte
		return false;
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

	friend bool operator>(float _altSalariu, const Angajat& a);
};

int Angajat::nrAngajati = 0;

bool operator>(float _altSalariu, const Angajat& a) {
	return _altSalariu > a.salariu;
}

int main() {
	Angajat a1;
	a1.afisare();

	float bonusuri[] = { 120.5,1000,1200 };
	Angajat a2("Gigel", Departament::IT, 12000, 3, bonusuri);
	a2.afisare();

	a1 = a2;
	a1.operator=(a2);
	a1.afisare();
	a1 = a2 = a1;
	a1.afisare();

	//a1 = a1;
	//a1.afisare();

	char nume[] = "Gigel";

	Angajat a3(nume, Departament::IT, 12000, 3, bonusuri);
	Angajat a4(nume, Departament::HR, 11000, 2, bonusuri);
	a3 = a4;
	a3.afisare();

	if (a1 != "Gigel")
		cout << "\nA1 nu este Gigel";
	else
		cout << "\nInvers";

	if (1200 > a1)
		cout << "\nAngajatul a1 are un salariu <1200";
	else
		cout << "\nInvers";

	a1 += 100;//adaugam un nou bonus
	a1.afisare();

	if (a1 != a2)
		cout << "\nObiecte diferite";
	else
		cout << "\nObiecte identice";
	/*
	P1.se identif tipul operatorului (binar/unar, aritmetic, logic...)
	P2.se indetif tipul operanzilor
	P3.daca primul operand este de tipul clasei, atunci
	se poate supraincarca printr-o metoda a clasei (primul 
	operand este "inghitit" de this). daca nu, 
	atunci obligatoriu se implementeaza printr-o functie globala
	(primeste ca parametri toti operanzii)
	P4.!!!ce obiecte se modifica?
	P5. !!!ce returneaza metoda
	*/
	return 0;
}