#include<iostream>
using namespace std;

//model de mostenire (relatie is a)
//modelare a departamentului de salarizari
//Angajat - clasa baza
//Cadru didactic - clasa derivata din Angajat
//Secretara - clasa derivata din Angajat

class Angajat {

protected:
	string nume = "Anonim";
	float salariuBaza = 0;

public:
	Angajat() {
	}

	Angajat(string _nume, float _salariuBaza) {
		this->nume = _nume;
		this->salariuBaza = _salariuBaza;
	}

	Angajat(const Angajat& a) {
		this->nume = a.nume;
		this->salariuBaza = a.salariuBaza;
	}

	Angajat& operator=(const Angajat& a) {
		if (this != &a) {
			this->nume = a.nume;
			this->salariuBaza = a.salariuBaza;
		}
		return *this;
	}

	friend ostream& operator<<(ostream& out, const Angajat& a) {
		out << "\nNume: " << a.nume;
		out << "\nSalariu baza: " << a.salariuBaza;
		return out;
	}

	float calculSalariu() {
		return this->salariuBaza;
	}

	bool operator!=(const Angajat& a) {
		if (this->nume != a.nume)
			return true;
		if (this->salariuBaza != a.salariuBaza)
			return true;
		return false;
	}
};

enum Functie {
	ASIST, LECT, CONF, PROF
};

class CadruDidactic :public Angajat{
	Functie functieDidactica=ASIST;
	int nrOreSuplimentare=0;
	char* departament = nullptr;
	static float tarifOrar;

public:
	CadruDidactic() {
	}

	CadruDidactic(string _nume, float _salariuBaza, Functie _functieDidactica, int _nrOreSuplimentare, const char* _departament):Angajat(_nume,_salariuBaza) {
		this->functieDidactica = _functieDidactica;
		this->nrOreSuplimentare = _nrOreSuplimentare;
		if (_departament != nullptr) {
			this->departament = new char[strlen(_departament) + 1];
			strcpy_s(this->departament, strlen(_departament) + 1, _departament);
		}
	}

	CadruDidactic(const CadruDidactic& c):Angajat(c)//upcast din CadruDidactic in Angajat
	{
		this->functieDidactica = c.functieDidactica;
		this->nrOreSuplimentare = c.nrOreSuplimentare;
		if (c.departament != nullptr) {
			this->departament = new char[strlen(c.departament) + 1];
			strcpy_s(this->departament, strlen(c.departament) + 1, c.departament);
		}
	}

	CadruDidactic& operator=(const CadruDidactic& c) {
		if (this != &c) {
			//cerem apelul explicit al op= din clasa de baza
			Angajat::operator=(c);//un upcast implicit care se realizeaza pentru obj c
			if (this->departament != nullptr) {
				delete[] this->departament;
				this->departament = nullptr;
			}
			this->functieDidactica = c.functieDidactica;
			this->nrOreSuplimentare = c.nrOreSuplimentare;
			if (c.departament != nullptr) {
				this->departament = new char[strlen(c.departament) + 1];
				strcpy_s(this->departament, strlen(c.departament) + 1, c.departament);
			}
		}
		return *this;
	}

	~CadruDidactic() {
		if (this->departament != nullptr) {
			delete[] this->departament;
			this->departament = nullptr;
		}
	}

	friend ostream& operator<<(ostream& out, const CadruDidactic& c) {
		//cer apelul explicit al operatorului<< care este specializat sa afiseze obj de tip Angajat
		out << (Angajat)c;//upcast prin valoare(adica se face o copie a lui c si devine un obj Angajat) explicit
		out << "\nFunctie didactica: " << c.functieDidactica;
		out << "\nNr ore suplimentare: " << c.nrOreSuplimentare;
		if (c.departament != nullptr)
			out << "\nDepartament: " << c.departament;
		else
			out << "\nDepartament: -";
		return out;
	}

	static void setTarifOrar(float _tarifOrar) {
		if (_tarifOrar <= 0)
			throw new exception("tarif negativ");
		else
			CadruDidactic::tarifOrar = _tarifOrar;
	}

	float calculSalariu() {
		//salariul unui cadru didactic il reprezinta salariul de baza la care suplimentam in functie de
		//nr de ore suplimentare, tarif orar si gradul sau didactic
		/*float salariu = this->salariuBaza;
		salariu += this->nrOreSuplimentare * CadruDidactic::tarifOrar * (1 + this->functieDidactica * 0.1);
		return salariu;*/

		//salariul unui cadru didactic il reprezinta salariul ca si angajat la care suplimentam in functie de
		//nr de ore suplimentare, tarif orar si gradul sau didactic
		return Angajat::calculSalariu() + this->nrOreSuplimentare * CadruDidactic::tarifOrar * (1 + this->functieDidactica * 0.1);
	}
	
	bool operator!=(CadruDidactic& c) {
		if (Angajat::operator!=(c) == true)
			return true;
		if (this->functieDidactica != c.functieDidactica)
			return true;
		if (this->nrOreSuplimentare != c.nrOreSuplimentare)
			return true;
		if (this->departament == nullptr && c.departament == nullptr)
			return false;
		if (this->departament != nullptr && c.departament != nullptr)
			if (strcmp(this->departament, c.departament) != 0)
				return true;
			else
				return false;
		else
			return true;
		return false;
	}
};

float CadruDidactic::tarifOrar = 100;

int main() {
	Angajat a("Gigel",1200);
	Angajat a2("Marcel", 2400);
	cout << a;
	cout << endl << a.calculSalariu();
	CadruDidactic c1("Costel", 2000, LECT, 10, "CSIE");
	CadruDidactic c2("Costel", 2000, ASIST, 10, "FABIZ");
	cout << c1;
	cout << endl << c1.calculSalariu();//la derivare, clasa derivata mosteneste si comportamentul(->metode) clasei de baza
	
	if (a != a2)
		cout << "\nCei doi angajati sunt diferiti cel putin dpdv al unui atribut";
	else
		cout << "\nCei doi angajati sunt identici";

	if (c1 != c2)
		cout << "\nCei doi angajati tip cadru didactic sunt diferiti cel putin dpdv al unui atribut";
	else
		cout << "\nCei doi angajati tip cadru didactic sunt identici";
	return 0;
}