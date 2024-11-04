#include<iostream>
using namespace std;

enum Departament {
	IT, HR, SALES
};

class Angajat {
	const int cod;
	char* nume;
	Departament departament;
	float salariu;
	int nrBonusuri;
	float* listaBonusuri;
	static int nrAngajati;
	
public:
	//constr fara param
	Angajat() :cod(1000 + (++Angajat::nrAngajati)) {
		this->nume = new char[strlen("Anonim") + 1];
		strcpy_s(this->nume, strlen("Anonim") + 1, "Anonim");
		this->departament = Departament::SALES;
		this->salariu = 0;
		this->nrBonusuri = 0;
		this->listaBonusuri = nullptr;
	}

	//constr cu toti param
	Angajat(const char* _nume, Departament _departament,
		float _salariu, int _nrBonusuri,
		float* _listaBonusuri) :cod(1000 + (++Angajat::nrAngajati)) {
		if (_nume != nullptr) {
			this->nume = new char[strlen(_nume) + 1];
			strcpy_s(this->nume, strlen(_nume) + 1, _nume);
		}
		else {
			this->nume = new char[strlen("Anonim") + 1];
			strcpy_s(this->nume, strlen("Anonim") + 1, "Anonim");
		}
		this->departament = _departament;
		this->salariu = _salariu;
		if (_nrBonusuri > 0 && _listaBonusuri != nullptr) {
			this->nrBonusuri = _nrBonusuri;
			this->listaBonusuri = new float[this->nrBonusuri];
			for (int i = 0; i < this->nrBonusuri; i++)
				this->listaBonusuri[i] = _listaBonusuri[i];
		}
		else {
			this->nrBonusuri = 0;
			this->listaBonusuri = nullptr;
		}
	}

	//constr de copiere
	Angajat(const Angajat& a) : cod(1000 + (++Angajat::nrAngajati)) {//folosesc & pentru ca vreau sa ocolesc copierea
		if (a.nume != nullptr) {
			this->nume = new char[strlen(a.nume) + 1];
			strcpy_s(this->nume, strlen(a.nume) + 1, a.nume);
		}
		else {
			this->nume = new char[strlen("Anonim") + 1];
			strcpy_s(this->nume, strlen("Anonim") + 1, "Anonim");
		}
		this->departament = a.departament;
		this->salariu = a.salariu;
		if (a.nrBonusuri > 0 && a.listaBonusuri != nullptr) {
			this->nrBonusuri = a.nrBonusuri;
			this->listaBonusuri = new float[this->nrBonusuri];
			for (int i = 0; i < this->nrBonusuri; i++)
				this->listaBonusuri[i] = a.listaBonusuri[i];
		}
		else {
			this->nrBonusuri = 0;
			this->listaBonusuri = nullptr;
		}
	}

	Angajat& operator=(const Angajat& a) {
		//this-ul se actualizeaza in functie de a
		if (this != &a) {
			if (this->nume != nullptr) {
				delete[] this->nume;
				this->nume = nullptr;
			}
			if (this->listaBonusuri != nullptr) {
				delete[] this->listaBonusuri;
				this->listaBonusuri = nullptr;
			}
			if (a.nume != nullptr) {
				this->nume = new char[strlen(a.nume) + 1];
				strcpy_s(this->nume, strlen(a.nume) + 1, a.nume);
			}
			else {
				this->nume = new char[strlen("Anonim") + 1];
				strcpy_s(this->nume, strlen("Anonim") + 1, "Anonim");
			}
			this->departament = a.departament;
			this->salariu = a.salariu;
			if (a.nrBonusuri > 0 && a.listaBonusuri != nullptr) {
				this->nrBonusuri = a.nrBonusuri;
				this->listaBonusuri = new float[this->nrBonusuri];
				for (int i = 0; i < this->nrBonusuri; i++)
					this->listaBonusuri[i] = a.listaBonusuri[i];
			}
			else {
				this->nrBonusuri = 0;
				this->listaBonusuri = nullptr;
			}

		}
		return *this;
	}

	//supraincarcare operatori
	/*bool operator!() {
		return this->salariu == 0;
	}*/

	//get si set vector numeric+dimensiune
	int getNrBonusuri() {
		return this->nrBonusuri;
	}

	const float* getListaBonusuri() {
		return this->listaBonusuri;
	}

	float* getListaBonusuri2() {
		float* copie = nullptr;
		if (this->listaBonusuri != nullptr) {
			copie = new float[this->nrBonusuri];
			for (int i = 0; i < this->nrBonusuri; i++)
				copie[i] = this->listaBonusuri[i];
		}
		return copie;
	}

	float getBonus(int _index) {
		if (_index >= 0 && _index < this->nrBonusuri) {
			return this->listaBonusuri[_index];
		}
		return -1;
	}

	void setListaBonusuri(int _nrBonusuri, float* _listaBonusuri) {
		if (_nrBonusuri > 0 && _listaBonusuri != nullptr) {
			//verific daca am ceva de dezalocat
			if (this->listaBonusuri != nullptr) {
				delete[] this->listaBonusuri;
				this->listaBonusuri = nullptr;
			}
			this->nrBonusuri = _nrBonusuri;
			this->listaBonusuri = new float[this->nrBonusuri];
			for (int i = 0; i < this->nrBonusuri; i++)
				this->listaBonusuri[i] = _listaBonusuri[i];
		}
	}

	void setBonus(int _index, float _bonus) {
		if (_index >= 0 && _index < this->nrBonusuri)
			if (_bonus > 0)
				this->listaBonusuri[_index] = _bonus;
	}

	//meth afisare
	void afisare() {
		cout << "\n----------------";
		cout << "\nCod: " << this->cod;
		cout << "\nNume: " << this->nume;
		cout << "\nDepartament: " << this->departament;
		cout << "\nSalariu: " << this->salariu;
		cout << "\nNr bonusuri: " << this->nrBonusuri;
		cout << "\nLista bonusuri: ";
		for (int i = 0; i < this->nrBonusuri; i++)
			cout << this->listaBonusuri[i] << " ";
	}

	//destructor
	~Angajat() {
		if (this->nume != nullptr) {
			delete[] this->nume;
			this->nume = nullptr;
		}
		if (this->listaBonusuri != nullptr) {
			delete[] this->listaBonusuri;
			this->listaBonusuri = nullptr;
		}
	}

	friend class Companie;
	friend void getMaxAngajati(Angajat listaA[], int nr);
	friend bool operator!(const Angajat& a);
};

//operator! prin functie globala
bool operator!(const Angajat& a) {
	return a.salariu == 0;
}

void getMaxAngajati(Angajat listaA[], int nr) {
	//get angajat cu salariu maxim
}

class Companie {
	string denumire;
	int caen;
	//etc
	//are o lista de angajati

	void test() {
		Angajat a;
	}
};

int Angajat::nrAngajati = 0;

int main() {
	float bonusuri[] = { 120.5,1000,1200 };
	Angajat a1("Gigel", Departament::IT, 12000, 3, bonusuri);
	Angajat a2;

	a2 = a1;
	a2.afisare();
	

	cout << "\n-------get si set------";
	cout << "\nNr bonusuri: " << a2.getNrBonusuri();
	cout << "\nLista bonusuri: ";
	for (int i = 0; i < a2.getNrBonusuri(); i++)
		cout << a2.getListaBonusuri()[i] << " ";
	cout << "\nLista bonusuri2: ";
	for (int i = 0; i < a2.getNrBonusuri(); i++)
		cout << a2.getBonus(i) << " ";
	const float* lista = a2.getListaBonusuri();

	float* listaB = a2.getListaBonusuri2();
	cout << "\nLista bonusuri: ";
	for (int i = 0; i < a2.getNrBonusuri(); i++)
		cout << listaB[i] << " ";
	if (listaB != nullptr) {
		delete[] listaB;
		listaB = nullptr;
	}

	float bonusuri2[] = { 120.5,1000,1200, 2300 };
	a2.setListaBonusuri(4, bonusuri2);
	a2.afisare();
	a2.setBonus(2, 2000);
	a2.afisare();
	//cout << a2;

	a2.setBonus(0, a2.getBonus(0) + 100);
	/*a2[0] += 100;
	a2 -= 2;*/

	//operatori unari=> 1 singur operand
	int x = 2;
	if (x)
		cout << "\nx exista";
	else
		cout << "\nx nu exista";

	if(!x)
		cout << "\nx nu exista";
	else
		cout << "\nx exista";

	if (!a2)
		cout << "\na2 nu are salariu";
	else
		cout << "\na2 are un salariu diferit de 0";
	//a2.operator!();//ca metoda a clasei
	operator!(a2);//ca functie globala
	return 0;
}