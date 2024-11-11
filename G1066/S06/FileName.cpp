#include<iostream>
using namespace std;

enum Departament {
	IT, HR, VZ
};

class Angajat {
	const int id;//cod unic care se genereaza automat
	char* nume;
	float salariu;
	Departament departament;
	static int nrAngajati;
	int nrBonusuri;
	float* listaBonusuri;

public:
	//constr fara param
	Angajat() :id(1000 + (++Angajat::nrAngajati)) {
		this->nume = new char[strlen("Anonim") + 1];
		strcpy_s(this->nume, strlen("Anonim") + 1, "Anonim");
		this->salariu = 0;
		this->departament = IT;
		this->nrBonusuri = 0;
		this->listaBonusuri = nullptr;
	}

	//constr cu aproape toti param
	Angajat(const char* _nume, float salariu = 0, Departament = IT) :id(1000 + (++Angajat::nrAngajati)) {
		if (_nume != nullptr) {
			this->nume = new char[strlen(_nume) + 1];
			strcpy_s(this->nume, strlen(_nume) + 1, _nume);
		}
		else {
			this->nume = nullptr;
		}
		this->salariu = salariu;
		this->departament = departament;
		this->nrBonusuri = 0;
		this->listaBonusuri = nullptr;
	}

	//constr de copiere
	Angajat(const Angajat& a) :id(1000 + (++Angajat::nrAngajati)) {
		if (a.nume != nullptr) {
			this->nume = new char[strlen(a.nume) + 1];
			strcpy_s(this->nume, strlen(a.nume) + 1, a.nume);
		}
		else {
			this->nume = nullptr;
		}
		this->salariu = a.salariu;
		this->departament = a.departament;
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
	//op =
	Angajat& operator=(const Angajat& a)
	{
		if (this != &a)
		{
			//combinatie intre destructor si constructor de copiere
			if (this->nume != nullptr)
			{
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
				this->nume = nullptr;
			}
			this->salariu = a.salariu;
			this->departament = a.departament;
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

	//op comparatie
	bool operator<(float x) {
		return this->salariu < x;
	}

	Angajat& operator-=(float x) {
		if (x > 0 && this->salariu > x) {
			this->salariu -= x;
		}
		return *this;
	}

	Angajat& operator+=(float x) {
		if (x > 0) {
			Angajat copie = *this;
			if (this->listaBonusuri != nullptr) {
				delete[] this->listaBonusuri;
				this->listaBonusuri = nullptr;
			}
			this->nrBonusuri++;
			this->listaBonusuri = new float[this->nrBonusuri];
			for (int i = 0; i < copie.nrBonusuri; i++)
				this->listaBonusuri[i] = copie.listaBonusuri[i];
			this->listaBonusuri[this->nrBonusuri - 1] = x;
		}
		return *this;
	}

	bool operator==(Angajat a) {
		if (strcmp(this->nume, a.nume) != 0)
			return false;
		if (this->salariu != a.salariu)
			return false;
		//....
		return true;
	}

	//get si set pentru nume
	const char* getNume() {
		return this->nume;
	}

	void setNume(const char* _nume)
	{
		if (this->nume != nullptr)
		{
			delete[] this->nume;
			this->nume = nullptr;
		}

		if (_nume != nullptr) {
			this->nume = new char[strlen(_nume) + 1];
			strcpy_s(this->nume, strlen(_nume) + 1, _nume);
		}
		else {
			this->nume = nullptr;
		}
	}

	//meth statice pentru atributul static
	static int  getNrAngajati()
	{
		return Angajat::nrAngajati;
	}

	float getSalariu(){
		this->salariu = 10;
		return this->salariu;
	}

	//meth afisare
	void afisare()
	{
		cout << "\n--------------------------\n";
		cout << "ID: " << this->id << endl;
		cout << "Nume: " << this->nume << endl;
		cout << "Salariul: " << this->salariu << endl;
		cout << "Departament: " << this->departament << endl;
		cout << "Nr bonusuri: " << this->nrBonusuri << endl;
		cout << "Lista bonusuri: ";
		for (int i = 0; i < this->nrBonusuri; i++)
			cout << this->listaBonusuri[i] << " ";
		cout << "\n--------------------------\n";
	}

	//destructor
	~Angajat() {
		if (this->nume != nullptr)
		{
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

bool operator<=(float x, Angajat a) {
	return x <= a.getSalariu();
	//return !(a < x);
}

int main() {

	Angajat a1;
	Angajat a2("Nume", 10000, IT);
	/*
	=
	+= -= *= /= (actualizam this)
	!= == <= (comparatie) (obj to obj)(alte versiune)
	! ++ (pre si post)
	+ (obj + obj; obj + int; int + obj)
	cast
	[] (index ce primeste o pozitie dar si index ce returneaza o pozitie)
	<< si >>
	functie ()
	*/

	a2.operator<(8000);
	if (a2 < 8000)
		cout << "\nAngajatul a2 are un salariu < 8000";
	else
		cout << "\nInvers";
	operator<=(11000, a2);
	if (11000 <= a2)
		cout << "\nAngajatul a2 are un salariu cel putin de 11.000";
	else
		cout << "\nInvers";

	a2 -= 100;//actualizam salariul lui a2
	//a1 = a1 -= 100;
	a2.afisare();

	a2 += 200;//adaug un nou bonus


	/*
	P1.identif tip operator (binar/unar; aritmetic...)
	P2.identif tip operanzi
	P3.daca primul operand este de tipul clasei, atunci se poate/
	se recomanda supraincarcarea printr-o functie membra (primul
	operand este "inghitit" de this; altfel, se implementeaza obligatoriu
	printr-o functie globala(nu mai avem this) (lista param este 
	formata din toti operanzii)
	P4. !!!ce returneaza???
	P5. !!!ce obiecte se modifica????
	*/
	return 0;
}