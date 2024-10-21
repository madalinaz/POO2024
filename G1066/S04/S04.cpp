#include<iostream>
using namespace std;

class Masina {
	string model;
	int kilometraj;
	int nrAlimentari;
	float* alimentari;

public:
	/*Masina() {
		cout << "\nAPEL CONSTRUCTOR FARA PARAM";
		this->model = "-";
		this->kilometraj = 0;
		this->nrAlimentari = 0;
		this->alimentari = nullptr;
	}*/

	Masina(string _model = "-", int _kilometraj = 0, int _nrAlimentari = 0, float* _alimentari = nullptr) {
		cout << "\nAPEL CONSTRUCTOR CU PARAM";
		this->model = _model;
		this->kilometraj = _kilometraj;
		if (_nrAlimentari > 0 && _alimentari != nullptr) {
			this->nrAlimentari = _nrAlimentari;
			//deep copy
			this->alimentari = new float[this->nrAlimentari];
			for (int i = 0; i < this->nrAlimentari; i++)
				this->alimentari[i] = _alimentari[i];
		}
		else {
			this->nrAlimentari = 0;
			this->alimentari = nullptr;
		}
	}

	Masina(const Masina& m) {
		cout << "\nAPEL CONSTRUCTOR COPY";
		this->model = m.model;
		this->kilometraj = m.kilometraj;
		if (m.nrAlimentari > 0 && m.alimentari != nullptr) {
			this->nrAlimentari = m.nrAlimentari;
			//deep copy
			this->alimentari = new float[this->nrAlimentari];
			for (int i = 0; i < this->nrAlimentari; i++)
				this->alimentari[i] = m.alimentari[i];
		}
		else {
			this->nrAlimentari = 0;
			this->alimentari = nullptr;
		}
	}

	void afisare() {
		cout << "\n--------------";
		cout << "\nModel: " << this->model;
		cout << "\nKilometraj: " << this->kilometraj;
		cout << "\nNr alimentari: " << this->nrAlimentari;
		cout << "\nAlimentari: ";
		for (int i = 0; i < this->nrAlimentari; i++)
			cout << this->alimentari[i] << " ";
		cout << "\n--------------";
	}

	~Masina() {
		cout << "\nAPEL DESTRUCTOR";
		if (this->alimentari != nullptr) {
			delete[] this->alimentari;
			this->alimentari = nullptr;
			//this->nrAlimentari = 0;
		}
	}
};

Masina f1(Masina vm[10], int nrMasini) {
	return Masina();
}

int main() {
	//Masina m("Audi Q5", 1000, 3, new float[3] {60.5, 50, 65}); (genereaza memory leaks
	float* alimentari = new float[3] {60.5, 50, 65};
	Masina m2("Audi Q5", 1000, 3, alimentari);
	delete[] alimentari;
	m2.afisare();

	Masina m3("Audi q7", 20000);
	m3.afisare();

	//Masina m4 = m2;
	Masina m4(m2);
	m4.afisare();

	return 0;
}