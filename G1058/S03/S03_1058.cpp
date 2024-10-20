#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;


enum Facultate {
	CSIE, MK, MN, FABIZ, OTHER
};

class Student {
	char* nume;
	Facultate facultate;
	string specializare;
	float noteBac[7];
	int nrNote;
	bool esteBursier;

public:
	//metode accesor
	bool getEsteBursier() {
		return esteBursier;
	}

	//metoda set pentru esteBursier
	void setEsteBursier(bool _esteBursier) {
		esteBursier = _esteBursier;
	}

	void setNume(const char* _nume) {
		if (_nume != nullptr && strlen(_nume) >= 5) {
			//obj deja exista, poate deja are un nume
			if (nume != nullptr) {
				delete[] nume;
				nume = nullptr;
			}
			nume = new char[strlen(_nume) + 1];
			strcpy(nume, _nume);
		}
	}

	const char* getNume() {
		return nume;
	}

	void initializare() {
		nume = nullptr;
		facultate = Facultate::OTHER;
		specializare = "-";
		nrNote = 0;
		esteBursier = false;
	}

	void afisare() {
		cout << "\n---------------------";
		if (nume != nullptr) {
			cout << "\nNume: " << nume;
		}
		else {
			cout << "\nNume: -";
		}
		cout << "\nFacultate: " << facultate;
		cout << "\nSpecializare: " << specializare;
		cout << "\nNr note bac: " << nrNote;
		cout << "\nNote bac: ";
		for (int i = 0; i < nrNote; i++)
			cout << noteBac[i] << " ";
		cout << "\nEste bursier? " << esteBursier;
		cout << "\n---------------------";
	}

};

int main() {
	Student s;
	s.initializare();
	s.afisare();
	if (s.getNume() != nullptr) {
		cout << "\nNume: " << s.getNume();
	}
	s.setNume("Gigel");
	//s.getNume()[0] = 'M';
	if (s.getNume() != nullptr) {
		cout << "\nNume: " << s.getNume();
	}

	s.afisare();
	cout << "\nEste bursier?: " << s.getEsteBursier();
	s.setEsteBursier(true);
	cout << "\nEste bursier?: " << s.getEsteBursier();

	return 0;
}