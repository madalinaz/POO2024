#include<iostream>
using namespace std;

enum Facultate {
	CSIE, MK, MN = 100, FABIZ
};

class Produs {
	int codUnic;
	string denumire;
	char um[10];
	bool esteFragil;
	int istoricPreturi[20];
	int nrPreturi;

public:
	int cantitate;
	void adaugaCantitateNoua(int val) {
		cantitate += val;
	}

	void reducerePretCurent(float procent) {
		istoricPreturi[nrPreturi - 1] *= 1 - procent;
	}

	//meth constructor
	//supraincarc operatori
	//destructor
};

union Id {
	long cnp;
	int cui;
	char test;
};

int main() {
	//sir de caractere
	//meth1 alocare statica
	/*char sir[50];
	cin >> sir;
	cout << sir << endl;*/

	//meth2 alocare dinamica
	/*char* sir2 = nullptr;
	char buffer[50];
	cin >> buffer;
	sir2 = new char[strlen(buffer) + 1];
	strcpy_s(sir2, strlen(buffer) + 1, buffer);
	cout << sir2 << endl;
	delete[] sir2;*/

	//meth3 clasa string ( alocare dinamica "ascunsa")
	/*string sir3;
	cin >> sir3;
	cout << sir3;
	sir3 = "Popescu";
	cout << endl << sir3;
	sir3 += " concatenare";
	sir3 = buffer;*/

	//enum
	/*Facultate f;
	f = Facultate::CSIE;
	cout << endl << f << endl;
	int codFacultate;
	cin >> codFacultate;
	f = (Facultate)codFacultate;
	cout << f;*/

	//union
	/*Id id;
	id.cnp = 1672345;
	cout << endl << id.cnp << " " << id.cui << " " << id.test;
	id.cui = 123456;
	cout << endl << id.cnp << " " << id.cui << " " << id.test;
	id.test = 'A';
	cout << endl << id.cnp << " " << id.cui << " " << id.test;*/


	//clase
	Produs p1;//implicit constructor
	cout << endl << sizeof(p1);
	p1.cantitate = 100;
	p1.adaugaCantitateNoua(10);
	cout << endl << p1.cantitate;
	return 0;
}