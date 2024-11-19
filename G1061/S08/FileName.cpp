#include<iostream>
using namespace std;

class Plantatie {
	const int id;
	string adresa;
	int nrPomi;
	int* varsta;
	static int varstaMinimaRod;
	
	//alte atribute la alegere
	//string proprietar;
	//string tipSol;

public:
	Plantatie(int _id):id(_id) {
		this->adresa = "-";
		this->nrPomi = 0;
		this->varsta = nullptr;
	}

	string getAdresa() {
		return this->adresa;
	}

	void setAdresa(string _adresa) {
		if (_adresa.length() >= 5) {
			this->adresa = _adresa;
		}
	}
};

int Plantatie::varstaMinimaRod = 3;//minim 3 ani ca pomul sa dea roade

int main() {
	cout << "\n----------Apel constructor cu 1 parametru--------------";
	Plantatie p1(10);

	return 0;
}