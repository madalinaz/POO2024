#include<iostream>
using namespace std;

//enum, const, static
//char* string*
//redimensionare vector
//supraincarca op prin friend (int +Obj)
//validari in constructori


class Plantatie {
	const int id;
	const string codCompozit;
	string adresa;
	int nrPomi;
	int* varsta;
	static int varstaMinRod;
	//float suprafata;
	//string sol;

public:

	static int testId(int _id) {
		if (_id > 0)
			return _id;
		else
			return 1;
	}

	static string generareCodCompozit(string _adresa) {
		return "Plantatie " + _adresa;
	}

	Plantatie(int _id) :id(Plantatie::testId(_id)), codCompozit(Plantatie::generareCodCompozit("Bucuresti")) {
		this->adresa = "-";
		this->nrPomi = 0;
		this->varsta = nullptr;
	}

	Plantatie(int _id, string _adresa, int _nrPomi, int* _varsta) :id(Plantatie::testId(_id)) {
		if (_adresa.length() >= 5)
			this->adresa = _adresa;
		else
			this->adresa = "-";
		if (_nrPomi > 0 && _varsta != nullptr) {
			this->nrPomi = _nrPomi;
			this->varsta = new int[this->nrPomi];
			for (int i = 0; i < this->nrPomi; i++) {
				if (_varsta[i] > 0)
					this->varsta[i] = _varsta[i];
				else
					this->varsta[i] = 1;
			}
		}
		else {
			this->nrPomi = 0;
			this->varsta = nullptr;
		}
	}

	Plantatie(const Plantatie& p) :id(Plantatie::testId(p.id)) {
		if (p.adresa.length() >= 5)
			this->adresa = p.adresa;
		else
			this->adresa = "-";
		if (p.nrPomi > 0 && p.varsta != nullptr) {
			this->nrPomi = p.nrPomi;
			this->varsta = new int[this->nrPomi];
			for (int i = 0; i < this->nrPomi; i++) {
				if (p.varsta[i] > 0)
					this->varsta[i] = p.varsta[i];
				else
					this->varsta[i] = 1;
			}
		}
		else {
			this->nrPomi = 0;
			this->varsta = nullptr;
		}
	}

	Plantatie& operator=(const Plantatie& p) {
		if (this != &p) {
			if (this->varsta != nullptr) {
				delete[] this->varsta;
				this->varsta = nullptr;
			}
			if (p.adresa.length() >= 5)
				this->adresa = p.adresa;
			else
				this->adresa = "-";
			if (p.nrPomi > 0 && p.varsta != nullptr) {
				this->nrPomi = p.nrPomi;
				this->varsta = new int[this->nrPomi];
				for (int i = 0; i < this->nrPomi; i++) {
					if (p.varsta[i] > 0)
						this->varsta[i] = p.varsta[i];
					else
						this->varsta[i] = 1;
				}
			}
			else {
				this->nrPomi = 0;
				this->varsta = nullptr;
			}
		}
		return *this;
	}

	~Plantatie() {
		if (this->varsta != nullptr) {
			delete[] this->varsta;
			this->varsta = nullptr;
		}
	}

	friend ostream& operator<<(ostream& out, const Plantatie& p) {
		out << "\nId: " << p.id << ", adresa: " << p.adresa << ", nr pomi: " << p.nrPomi << ", varsta pomi: ";
		for (int i = 0; i < p.nrPomi; i++)
			out << p.varsta[i] << " ";
		return out;
	}

	friend Plantatie operator+(int nr, const Plantatie& p) {
		Plantatie rez = p;
		delete[] rez.varsta;
		rez.varsta = new int[rez.nrPomi + nr];
		rez.nrPomi = rez.nrPomi + nr;
		for (int i = 0; i < p.nrPomi; i++)
			rez.varsta[i] = p.varsta[i];
		for (int i = p.nrPomi; i < rez.nrPomi; i++)
			rez.varsta[i] = 1;// Plantatie::varstaMinRod;
		return rez;
	}

	Plantatie operator+(int nr) {
		return nr + *this;
	}
};

int Plantatie::varstaMinRod = 3;



int main() {
	Plantatie p1(12);
	int varsta[] = { 5,-4,10,6,5,10 };
	Plantatie p2(13, "Barlad", 6, varsta);
	cout << p1 << p2;
	Plantatie p3(p2);
	cout << p3;
	p1 = p3;
	cout << p1;
	Plantatie p4(13);
	p4 = 10 + p4;
	cout << p4;
	Plantatie p5 = 10 + p3;
	Plantatie p6 = 5;
	p4 = p4 + 10;
	cout << p4;
	return 0;
}