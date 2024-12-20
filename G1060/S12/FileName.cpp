#include<iostream>
using namespace std;

//custom exception
class Exception_Cantitate : public exception {
public:
	Exception_Cantitate(string _mesaj) :exception(_mesaj.data()) {

	}
};

class Exception_CapacitateMaxima : public exception {
public:
	Exception_CapacitateMaxima(string _mesaj) :exception(_mesaj.data()) {

	}
};

enum TipCarburant {
	BENZINA95, BENZINA98, MOTORINA
};

class Rezervor {
	TipCarburant tipCarburant = BENZINA95;
	float nivelCurent = 0;//capacitateCurenta
	const float capacitateMaxima;
	//static float procentMinim;

public:
	Rezervor() :capacitateMaxima(1000) {
	}

	Rezervor(float _capacitateMaxima) :capacitateMaxima(_capacitateMaxima) {
	}

	Rezervor(TipCarburant _tipCarburant, float _nivelCurent, float _capacitateMaxima) :capacitateMaxima(_capacitateMaxima) {
		this->tipCarburant = _tipCarburant;
		this->nivelCurent = _nivelCurent;
	}

	Rezervor& operator=(const Rezervor& r) {
		if (this != &r) {
			this->tipCarburant = r.tipCarburant;
			this->nivelCurent = r.nivelCurent;
		}
		return *this;
	}

	//op +=
	Rezervor& operator+=(float _cantitate) {
		if (_cantitate > 0) {
			if (this->nivelCurent + _cantitate < this->capacitateMaxima)
				this->nivelCurent += _cantitate;
			else {
				throw Exception_CapacitateMaxima("S-a atins maximul");
			}
		}
		else {
			throw Exception_Cantitate("Cantitate negativa");
		}
	}
	//op -=
	//op !
};

//clasa optionala
class Pompa {
	int nrPompa;
	//retin interactiunea cu rezervoarele
	Rezervor** listaRezervoare;
	int nrRezervoare;
};

class Benzinarie {
	int nrPompe = 0;
	int nrRezervoare = 0;
	Rezervor* listaRezervoare = nullptr;
	bool existentaCarburant[3] = { 0 };
	float preturi[3] = { 0 };

public:
	Benzinarie(int _nrPompe, int _nrRezervoare, Rezervor* _listaRezervoare, bool _existentaCarburant[3], float _preturi[3]) {
		this->nrPompe = _nrPompe;
		this->nrRezervoare = _nrRezervoare;
		this->listaRezervoare = new Rezervor[this->nrRezervoare];
		for (int i = 0; i < this->nrRezervoare; i++)
			this->listaRezervoare[i] = _listaRezervoare[i];
		for (int i = 0; i < 3; i++)
			this->existentaCarburant[i] = _existentaCarburant[i];
		for (int i = 0; i < 3; i++)
			this->preturi[i] = _preturi[i];
	}
};

int main() {
	Rezervor r1(BENZINA95, 100, 1000);
	try {
		r1 += 1020;
	}
	catch (Exception_Cantitate ex) {
		cout << ex.what();//getter pe mesaj
	}
	catch (Exception_CapacitateMaxima ex) {
		cout << ex.what();//getter pe mesaj
	}
	return 0;
}