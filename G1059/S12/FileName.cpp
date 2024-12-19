#include<iostream>
#include<fstream>
using namespace std;

enum TipCombustibil {
	BENZINA95, BENZINA98, MOTORINA
};

class Rezervor {
	TipCombustibil tipCombustibil;
	float capacitateMaxima;
	float capacitateCurenta; //nivelCurent

public:
	Rezervor(){
		this->tipCombustibil = BENZINA95;
		this->capacitateCurenta = 0;
		this->capacitateMaxima = 0;
	}

	Rezervor(TipCombustibil _tipCombustibil, float _capacitateMaxima, float _capacitateCurenta) {
		this->tipCombustibil = _tipCombustibil;
		this->capacitateMaxima = _capacitateMaxima;
		this->capacitateCurenta = _capacitateCurenta;
	}

	friend ostream& operator<<(ostream& out, const Rezervor& r) {
		out << "\nRezervor tip " << r.tipCombustibil << ", capacitate curenta: " << r.capacitateCurenta;
		out << ", capacitate maxima: " << r.capacitateMaxima;
		return out;
	}
	//op +=
	Rezervor& operator+=(float _cantitate) {
		if (_cantitate > 0 && _cantitate + this->capacitateCurenta <= this->capacitateMaxima) {
			this->capacitateCurenta += _cantitate;
		}
		else {
			throw exception("alimentarea depaseste capacitatea maxima a rezervorului");
		}
		return *this;
	}

	//op -=
	Rezervor& operator-=(float _cantitate) {
		if (_cantitate > 0) {
			if (_cantitate <= this->capacitateCurenta) {
				this->capacitateCurenta -= _cantitate;
			}
		}
		return *this;
	}

	bool operator!() {
		return this->capacitateCurenta != 0;
	}
};

//clasa optionala
class Pompa {
	//vector cu tipurile de combustibil
	//legatura cu rezervoarele cu care comunica
	//dispobilitate
	//valoare curenta
};

class Benzinarie {
	const string denumire;
	int nrRezervoare;
	Rezervor* listaRezervoare;
	int nrPompe;//toate pompele sunt conectate la toate rezervoarele din benzinarie
	float listaPreturi[3];//3 este cardinalitatea enumeratiei
	static float alimentareMaxima;//restrictie de la guvern prin OU
	float vanzari[3];

public:
	Benzinarie():denumire("-") {
		this->nrRezervoare = 0;
		this->listaRezervoare = nullptr;
		this->nrPompe = 0;
		for (int i = 0; i < 3; i++)
			this->listaPreturi[i] = 0;
		for (int i = 0; i < 3; i++)
			this->vanzari[i] = 0;
	}

	Benzinarie(string _denumire, int _nrRezervoare, Rezervor* _listaRezervoare, int _nrPompe, float _listaPreturi[3]):denumire(_denumire) {
		this->nrRezervoare = _nrRezervoare;
		this->listaRezervoare = new Rezervor[this->nrRezervoare];
		for (int i = 0; i < this->nrRezervoare; i++)
			this->listaRezervoare[i] = _listaRezervoare[i];
		this->nrPompe = _nrPompe;
		for (int i = 0; i < 3; i++)
			this->listaPreturi[i] = _listaPreturi[i];
		for (int i = 0; i < 3; i++)
			this->vanzari[i] = 0;
	}

	Benzinarie(const Benzinarie& b) :denumire(b.denumire) {
		this->nrRezervoare = b.nrRezervoare;
		this->listaRezervoare = new Rezervor[this->nrRezervoare];
		for (int i = 0; i < this->nrRezervoare; i++)
			this->listaRezervoare[i] = b.listaRezervoare[i];
		this->nrPompe = b.nrPompe;
		for (int i = 0; i < 3; i++)
			this->listaPreturi[i] = b.listaPreturi[i];
		for (int i = 0; i < 3; i++)
			this->vanzari[i] = b.vanzari[i];
	}

	Benzinarie& operator=(const Benzinarie& b) {
		if (this != &b) {
			if (this->listaRezervoare != nullptr) {
				delete[] this->listaRezervoare;
				this->listaRezervoare = nullptr;
			}
			this->nrRezervoare = b.nrRezervoare;
			this->listaRezervoare = new Rezervor[this->nrRezervoare];
			for (int i = 0; i < this->nrRezervoare; i++)
				this->listaRezervoare[i] = b.listaRezervoare[i];
			this->nrPompe = b.nrPompe;
			for (int i = 0; i < 3; i++)
				this->listaPreturi[i] = b.listaPreturi[i];
			for (int i = 0; i < 3; i++)
				this->vanzari[i] = b.vanzari[i];
		}
		return *this;
	}

	~Benzinarie() {
		if (this->listaRezervoare != nullptr) {
			delete[] this->listaRezervoare;
			this->listaRezervoare = nullptr;
		}
	}

	friend ostream& operator<<(ostream& out, const Benzinarie& b) {
		out << "\nDenumire: " << b.denumire;
		out << "\nNr rezervoare: " << b.nrRezervoare;
		out << "\nRezervoare: ";
		for (int i = 0; i < b.nrRezervoare; i++)
			out << b.listaRezervoare[i];
		out << "\nNr pompe: " << b.nrPompe;
		out << "\nLista preturi: ";
		for (int i = 0; i < 3; i++)
			out << b.listaPreturi[i] << " ";
		out << "\nLista vanzari: ";
		for (int i = 0; i < 3; i++)
			out << b.vanzari[i] << " ";
		return out;
	}

	void suplimentareRezervor(float cantitate, TipCombustibil tipCombustibil) {
		//apelati op += pentru actualizare in rezervor
		if (cantitate > 0) {
			//situatie in care exista un singur rezervor cu un tip de combustibil
			this->listaRezervoare[tipCombustibil] += cantitate;
		}
	}

	void alimentareDinPompa(float cantitate, int nrPompa, TipCombustibil tipCombustibil) {
		//apelati op -= pentru actualizare in rezervor
		if (cantitate > 0) {
			this->listaRezervoare[tipCombustibil] -= cantitate;
			this->vanzari[tipCombustibil] += cantitate;
		}
	}

	void generareRaport(string denumireRaport) {
		ofstream g(denumireRaport);
		g << "------------Raport vanzari------------";
		g << "\n------Benzinaria: " << this->denumire << "-----------";
		for (int i = 0; i < 3; i++) {
			g << "\nCombustibil: " << i << ", vanzari: " << this->vanzari[i];
		}
		g.close();
	}

	TipCombustibil getBestCombustibil() {
		int imax = 0;
		for (int i = 0; i < 3; i++)
			if (this->vanzari[i] > this->vanzari[imax])
				imax = i;
		return (TipCombustibil)imax;
	}
};

int main() {
	Rezervor r1(BENZINA95, 1000, 800);
	Rezervor r2(BENZINA98, 900, 700);
	Rezervor r3(MOTORINA, 1000, 1000);
	cout << !r3;
	Rezervor v[] = { r1,r2,r3 };
	float preturi[] = { 8,8.5,9 };
	Benzinarie b("OMV Zorelelor nr 40", 3, v, 6, preturi);
	cout << b;
	try {
		b.suplimentareRezervor(100, BENZINA95);
	}
	catch (exception ex) {
		cout << endl << ex.what();
	}

	try {
		b.suplimentareRezervor(300, BENZINA95);
	}
	catch (exception ex) {
		cout << endl << ex.what();
	}
	b.alimentareDinPompa(50, 4, BENZINA95);
	b.alimentareDinPompa(50, 4, BENZINA95);
	b.alimentareDinPompa(50, 4, BENZINA98);
	b.alimentareDinPompa(70, 4, MOTORINA);
	b.generareRaport("raport1.txt");
	cout << b;
	cout << endl << "\nBest combustibil: " << b.getBestCombustibil();
	return 0;
}