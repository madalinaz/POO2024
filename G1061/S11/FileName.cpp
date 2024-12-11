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
};

int main() {
	Angajat a("Gigel",1200);
	cout << a;
	return 0;
}