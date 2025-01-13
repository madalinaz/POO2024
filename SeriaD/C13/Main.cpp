#include<iostream>
#include "Persoana.h"
#include<vector>
using namespace std;

int sumaInt(int v1, int v2) {
	return v1 + v2;
}

//functie sablon/template
template<class T>
T suma(T v1, T v2) {
	return v1 + v2;
}

template<class T1, class T2>
T1 sumaGenerala(T2 v1, T2 v2) {
	return (T1)(v1 + v2);
}


class Angajat {
public:
	string nume;
	float salariu;

	explicit operator float() {
		return this->salariu;
	}

	Angajat(float _salariu) {
		this->nume = "Anonim";
		this->salariu = _salariu;
	}

	Angajat() {
		this->nume = "-";
		this->salariu = 0;
	}

	Angajat operator+(const Angajat& a) {
		Angajat rez;
		rez.nume = this->nume;
		rez.salariu = this->salariu + a.salariu;
		return rez;
	}

	friend ostream& operator<<(ostream& out, const Angajat& a) {
		out << "\nNume: " << a.nume << ", salariu: " << a.salariu;
		return out;
	}
};

template<class T>
class Container {
	T v[10];
	int nrElem;

public:
	Container() {
		this->nrElem = 0;
	}

	Container(T _v[10], int _nrElem) {
		this->nrElem = _nrElem;
		for (int i = 0; i < this->nrElem; i++)
			this->v[i] = _v[i];
	}

	friend ostream& operator<<(ostream& out, const Container& c) {
		out << "\nNr elem: " << c.nrElem;
		out << "\nLista elem: ";
		for (int i = 0; i < c.nrElem; i++)
			out << c.v[i] << " ";
		return out;
	}
};

int main() {
	//Persoana p;
	//p.nume = "Gigel";
	//p.prezentare();

	int rez = sumaInt(2, 5);
	Angajat a1;
	a1.salariu = 1000;
	Angajat a2;
	a2.salariu = 2000;
	//int rez2 = sumaInt(a1, a2);

	rez = suma<int>(2, 5);
	cout << endl << rez;

	float rezFloat = suma<float>(2.5, 5.2);
	cout << endl << rezFloat;

	Angajat rezAngajat = suma<Angajat>(a1, a2);
	cout << endl << rezAngajat.salariu;

	int rezInt = sumaGenerala<int, int>(2, 5);
	cout << endl << rezInt;

	bool rezBool = sumaGenerala<bool, int>(2, 5);
	cout << endl << rezBool;

	rezFloat = sumaGenerala<float, Angajat>(a1, a2);

	int v[] = { 1,2,3,4,5 };
	Container<int> containerInt(v, 5);
	cout << containerInt;

	Angajat vAngajat[] = { a1,a2 };
	Container<Angajat> containerAngajat(vAngajat, 2);
	cout << containerAngajat;

	vector<int> vInt;
	vInt.push_back(1);

}