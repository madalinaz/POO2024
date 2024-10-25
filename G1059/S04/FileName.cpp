#include<iostream>
using namespace std;

class Zbor {
	string sursa;
	string destinatie;
	int nrKilometri;
	int nrLocuri;
	bool* disponibilitateLoc;

public:
	//constructor fara param
	Zbor() {
		cout << "\nAPEL CONSTRUCTOR FARA PARAM";
		sursa = "-";
		destinatie = "-";
		nrKilometri = 0;
		nrLocuri = 0;
		disponibilitateLoc = nullptr;
	}

	//constructor cu toti param
	Zbor(string _sursa, string _destinatie, int _nrKilometri, int _nrLocuri, bool* _disponibilitateLoc) {
		cout << "\nAPEL CONSTRUCTOR CU TOTI PARAM";
		sursa = _sursa;
		destinatie = _destinatie;
		nrKilometri = _nrKilometri;
		if (_nrLocuri > 0 && _disponibilitateLoc != nullptr) {
			nrLocuri = _nrLocuri;
			disponibilitateLoc = new bool[nrLocuri];
			for (int i = 0; i < nrLocuri; i++)
				disponibilitateLoc[i] = _disponibilitateLoc[i];
		}
		else {
			nrLocuri = 0;
			disponibilitateLoc = nullptr;
		}
	}

	//constructor de copiere
	Zbor(const Zbor& z) {
		cout << "\nAPEL CONSTRUCTOR COPIERE";
		sursa = z.sursa;
		destinatie = z.destinatie;
		nrKilometri = z.nrKilometri;
		if (z.nrLocuri > 0 && z.disponibilitateLoc != nullptr) {
			nrLocuri = z.nrLocuri;
			disponibilitateLoc = new bool[nrLocuri];
			for (int i = 0; i < nrLocuri; i++)
				disponibilitateLoc[i] = z.disponibilitateLoc[i];
		}
		else {
			nrLocuri = 0;
			disponibilitateLoc = nullptr;
		}
	}
	
	//meth afisare
	void afisare() {
		cout << "\n-----------";
		cout << endl << "Oras sursa: " << sursa;
		cout << endl << "Oras destinatie: " << destinatie;
		cout << "\nNr kilometri: " << nrKilometri;
		cout << "\nNr locuri: " << nrLocuri;
		cout << "\nDisponibilitate locuri: ";
		for (int i = 0; i < nrLocuri; i++)
			cout << disponibilitateLoc[i] << " ";
		cout << "\n-----------";
	}

	//destructor
	~Zbor() {
		cout << "\nAPEL DESTRUCTOR";
		if (disponibilitateLoc != nullptr) {
			delete[] disponibilitateLoc;
			disponibilitateLoc = nullptr;//no dangling pointers
		}
	}
};

int main() {
	Zbor z1;
	z1.afisare();
	//Zbor z2(); nu se apeleaza constructor fara param
	bool locuri[] = { true,true,true,true,false };
	Zbor z3("Bucuresti", "Roma", 2000, 5, locuri);
	z3.afisare();

	Zbor* pz = new Zbor();
	delete pz;

	Zbor* vz = new Zbor[5];
	delete[] vz;

	//construim obj nou pe baza unui obj existent (constructor de copiere)
	Zbor z4 = z3;
	Zbor z5(z3);

	return 0;
}