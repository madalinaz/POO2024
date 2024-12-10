#include<iostream>
using namespace std;

// relatie is a (derivare)
// conceptul de virtualizare
// citire si scriere in fisiere text

class Angajat {
	string nume ="Anonim";
	float salariuBaza = 0;
	
public:
	Angajat() {
		cout << "\nAPEL CONSTRUCTOR FARA PARAM ANGAJAT";
	}

	Angajat(string _nume, float _salariuBaza) {
		cout << "\nAPEL CONSTRUCTOR CU TOTI PARAM ANGAJAT";
		this->nume = _nume;
		this->salariuBaza = _salariuBaza;
	}

	Angajat(const Angajat& a) {
		cout << "\nAPEL CONSTRUCTOR COPIERE ANGAJAT";
		this->nume = a.nume;
		this->salariuBaza = a.salariuBaza;
	}

	Angajat& operator=(const Angajat& a) {
		cout << "\nAPEL OPERATOR= ANGAJAT";
		if (this != &a) {
			this->nume = a.nume;
			this->salariuBaza = a.salariuBaza;
		}
		return *this;
	}

	~Angajat() {
		cout << "\nAPEL DESTRUCTOR ANGAJAT";
	}

	friend ostream& operator<<(ostream& out, const Angajat& a) {
		out << "\nNume: " << a.nume;
		out << "\nSalariu baza: " << a.salariuBaza;
		return out;
	}

	friend istream& operator>>(istream& in, Angajat& a) {
		cout << "\nIntroduceti nume: ";
		in >> a.nume;
		cout << "Introduceti salariu baza: ";
		in >> a.salariuBaza;
		return in;
	}
};

class Profesor {

};

int main() {
	return 0;
}