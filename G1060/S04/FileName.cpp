#include<iostream>
using namespace std;

class Zbor {
	string sursa;
	string destinatie;
	char data[11]; //zz/ll/aaaa
	int nrLocuri;
	bool* disponibilitateLoc;

public:
	//constructor fara param
	Zbor() {
		cout << "\nAPEL CONSTRUCTOR FARA PARAM";
		sursa = "-";
		destinatie = "-";
		strcpy_s(data, "01/01/1970");
		nrLocuri = 0;
		disponibilitateLoc = nullptr;
	}

	//constructor cu cativa param
	//la un zbor nou pentru care nu primesc vectorul de disponibilitate, atunci acel vector se aloca dinamic si se init cu true pentru fiecare loc implicit
	Zbor(string _sursa, string _destinatie, const char _data[11],
		int _nrLocuri) {
		cout << "\nAPEL CONSTRUCTOR CU CATIVA PARAM";
		sursa = _sursa;
		destinatie = _destinatie;
		strcpy_s(data, _data);
		if (_nrLocuri > 0) {
			nrLocuri = _nrLocuri;
			disponibilitateLoc = new bool[nrLocuri];
			for (int i = 0; i < nrLocuri; i++)
				disponibilitateLoc[i] = true;
		}
		else {
			nrLocuri = 0;
			disponibilitateLoc = nullptr;
		}
	}

	//constructor cu toti param
	Zbor(string _sursa, string _destinatie, const char _data[11],
		int _nrLocuri, bool* _disponibilitateLoc) {
		cout << "\nAPEL CONSTRUCTOR CU TOTI PARAM";
		sursa = _sursa;
		destinatie = _destinatie;
		strcpy_s(data, _data);
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
	//se apeleaza in 3 cazuri
	//1. construire obj nou: Zbor z3(z2);
	//2. transfer prin valoare: fct(Zbor z, int nr);
	//3. return prin valoare: Zbor getMaxZbor(Zbor v[10], int nr);
	Zbor(const Zbor& z) {
		cout << "\nAPEL CONSTRUCTOR COPIERE";
		sursa = z.sursa;
		destinatie = z.destinatie;
		strcpy_s(data, z.data);
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

	//meth de afisare
	void afisare() {
		cout << "\n----------";
		cout << "\nSursa: " << sursa;
		cout << "\nDestinatie: " << destinatie;
		cout << "\nData: " << data;
		cout << "\nNr locuri: " << nrLocuri;
		cout << "\nDisponibilitate: ";
		for (int i = 0; i < nrLocuri; i++)
			cout << disponibilitateLoc[i] << " ";
		cout << "\n----------";
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

Zbor f1(Zbor* vector, int nrZboruri) {
	//....
	return Zbor();
}

Zbor f2(Zbor* vector, int nrZboruri) {
	return vector[0];
}

Zbor& f3(Zbor z1, Zbor& z2) {
	return z1;
}

Zbor& f4() {
	Zbor z;
	return z;
}

Zbor f5() {
	Zbor z;
	return z;
}

void f6(Zbor vector[10], int nrZboruri) {
	//....
}

int main() {
	Zbor z1;
	z1.afisare();
	//Zbor z2(); nu este apel constructor fara param
	bool disponibilitate[] = { true,true,true,false,true };
	Zbor z2("Bucuresti", "Roma", "12/12/2024", 5, disponibilitate);
	z2.afisare();
	Zbor z3("Bucuresti", "Milano", "13/12/2024", 100);
	z3.afisare();
	Zbor* pZbor = new Zbor();//pointer la un zbor; //op new apeleaza un constructor
	delete pZbor;
	Zbor* vZbor = new Zbor[5];//pointer ->vector dinamic cu 5 zboruri
	delete[] vZbor;

	Zbor z4 = z2;
	Zbor z5(z2);//construire obj nou pe baza unui obj vechi
	//adica o copie a unui obj care exista deja =>constructor de copiere
	z5.afisare();
	return 0;
}