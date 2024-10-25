#include <iostream>
using namespace std;

class Produs {
	string denumire = "-";
	int* actualizareStoc = nullptr;//+ adaug la stoc; - scot din stoc
	int nrActualizari = 0;
	float pret = 0;

public:
	//constructor fara parametri
	Produs() {
		cout << "\nAPEL CONSTRUCTOR FARA PARAM";
	}

	//constructor cu toti parametri
	Produs(string _denumire, int* _actualizareStoc, int _nrActualizari, float _pret) {
		cout << "\nAPEL CONSTRUCTOR CU TOTI PARAM";
		this->denumire = _denumire;
		if (_nrActualizari > 0 && _actualizareStoc != nullptr) {
			this->nrActualizari = _nrActualizari;
			this->actualizareStoc = new int[this->nrActualizari];
			for (int i = 0; i < this->nrActualizari; i++)
				this->actualizareStoc[i] = _actualizareStoc[i];
		}
		this->pret = _pret;
	}

	//constructor copiere
	Produs(const Produs& p) {
		cout << "\nAPEL CONSTRUCTOR COPIERE";
		this->denumire = p.denumire;
		if (p.nrActualizari > 0 && p.actualizareStoc != nullptr) {
			this->nrActualizari = p.nrActualizari;
			this->actualizareStoc = new int[this->nrActualizari];
			for (int i = 0; i < this->nrActualizari; i++)
				this->actualizareStoc[i] = p.actualizareStoc[i];
		}
		this->pret = p.pret;
	}

	//metoda afisare
	void afisare() {
		cout << "\n-------------------------------------------------";
		cout << "\nDenumire: " << this->denumire;
		cout << "\nActualizare stoc: ";
		for (int i = 0; i < this->nrActualizari; i++)
			cout << this->actualizareStoc[i] << " ";
		cout << "\nPret: " << this->pret;
		cout << "\n--------------------------------------------------";
	}
	//destructor
	~Produs() {
		cout << "\nAPEL DESTRUCTOR";
		if (this->actualizareStoc != nullptr) {
			delete[] this->actualizareStoc;
			this->actualizareStoc = nullptr;//no dangling pointers
		}
	}
};
int main() {
	Produs p1;
	p1.afisare();
	int actualizari[] = { 10,-4,20 };
	Produs p2("Stilou", actualizari, 3, 550);
	p2.afisare();
	Produs* ps = new Produs();
	delete ps;

	Produs* vp = new Produs[5];
	delete[] vp;

	//ambele forme apeleaza constructorul de copiere
	Produs p3(p2);
	Produs p4 = p2;

	return 0;
}