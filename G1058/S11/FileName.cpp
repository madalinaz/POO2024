#include<iostream>
using namespace std;

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

};

//Manager is a Angajat
//Manager has a lista Angajat (vector alocat dinamic de obj tip Angajat)
class Manager : public Angajat {
	int nrSubalterni;
	Angajat* listaAngajati;
	int grad;//1-5

public:
	//constructor fara param
	//constructor cu param mai putin vector si dimensiune
	//constructor de copiere
	//op=
	//destructor
	//ostream
	//op += care populeaza vectorul listaAngajati(fara validari)
	//op += care populeaza vectorul listaAngajati(cu validari unicitate pe nume)

	//constructor cu toti param(adica primeste si un vector + dim)
};

int main() {

	return 0;
}