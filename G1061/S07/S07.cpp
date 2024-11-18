#include<iostream>
using namespace std;

enum Departament {
	IT, HR, SALES
};

class Angajat {
	const int cod;//codul este unic si generat automat 1001, 1002, etc
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

	//operator=
	Angajat& operator=(const Angajat& a) {
		if (this != &a)
		{
			//lucreaza pe obj existente, atunci avem in vedere
			//posibile dezalocari
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

	//operator comparatie
	bool operator!=(const char* _altNume) {
		if (this->nume != nullptr && _altNume != nullptr) {
			if (strcmp(this->nume, _altNume) != 0)
				return true;
			else
				return false;
		}
		return false;
	}

	//redimensionare vector alocat dinamic
	Angajat& operator+=(float _altBonus) {
		if (_altBonus > 0) {
			Angajat copie = *this;
			if (this->listaBonusuri != nullptr) {
				delete[] this->listaBonusuri;
				this->listaBonusuri = nullptr;
			}
			this->listaBonusuri = new float[this->nrBonusuri + 1];
			for (int i = 0; i < this->nrBonusuri; i++)
				this->listaBonusuri[i] = copie.listaBonusuri[i];
			this->listaBonusuri[this->nrBonusuri] = _altBonus;
			this->nrBonusuri++;
		}
		return *this;
	}

	bool operator!=(const Angajat& a) {
		if (strcmp(this->nume, a.nume) != 0)
			return true;
		if (this->salariu != a.salariu)
			return true;
		//....pentru toate celelalte
		return false;
	}

	//operator++ pre incrementare
	Angajat& operator++() {
		this->salariu++;
		return *this;//returneaza starea obj de dupa incrementare
	}

	//forma de post incrementare
	//return este prin valoare pentru ca obj copie este declarat pe stiva op ++
	Angajat operator++(int) {
		Angajat copie = *this;//copiez starea obj this de dinainte de incrementare
		this->salariu++;
		//(*this)++;//apel operator++ in forma de pre-incrementare
		return copie;//returnez stare obj de dinainte de ++
	}

	//se pune const pentru ca this NU se modifica in aceasta metoda
	//si atunci ne protejam obj this
	float operator+(const Angajat& a) const{
		//OBJ THIS NU SE MODIFICA
		float rez = 0;
		rez = this->salariu + a.salariu;
		return rez;
	}

	//operator index
	float operator[](int _index) {
		if (_index >= 0 && _index < this->nrBonusuri) {
			return this->listaBonusuri[_index];
		}
		return -1;
	}

	//cast implicit la float
	operator float() {
		//de validat ca exista bonusuri
		float bonusMaxim = this->listaBonusuri[0];
		for (int i = 1; i < this->nrBonusuri; i++)
			if (this->listaBonusuri[i] > bonusMaxim)
				bonusMaxim = this->listaBonusuri[i];
		return bonusMaxim;
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

	// meth pentru gestiune atribute statice
	static int getNrAngajati() {
		return Angajat::nrAngajati;
	}

	// get si set pentru nume
	const char* getNume() {
		return this->nume;
	}

	char* getNume2() {
		char* copie = nullptr;
		if (this->nume != nullptr) {
			copie = new char[strlen(this->nume) + 1];
			strcpy_s(copie, strlen(this->nume) + 1, this->nume);
		}
		return copie;
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

	friend bool operator>(float _altSalariu, const Angajat& a);

	friend ostream& operator<<(ostream& out, const Angajat& a) {
		out << "\n----------------";
		out << "\nCod: " << a.cod;
		out << "\nNume: " << a.nume;
		out << "\nDepartament: " << a.departament;
		out << "\nSalariu: " << a.salariu;
		out << "\nNr bonusuri: " << a.nrBonusuri;
		out << "\nLista bonusuri: ";
		for (int i = 0; i < a.nrBonusuri; i++)
			out << a.listaBonusuri[i] << " ";
		return out;
	}

	//VARIATII
	//posibilitate citire siruri de caractere cu spatii
	//citire multipla pana cand se introduce o valoare corecta
	//posibilitate de citire partiala de obj (poate nu se cere si lista=> atunci lista se goleste si se face nullptr)

	//obligatoriu transfer pe a prin referinta
	//pentru ca obj a se actualizeaza in proces de citire
	friend istream& operator>>(istream& in, Angajat& a) {
		//NU citim atribute constante pentru ca nu le putem modifica
		cout << "\nIntroduceti nume: ";
		string buffer;
		in >> buffer;
		//ca sa nu avem memory leaks
		//pentru ca obj a deja exista
		if (a.nume != nullptr) {
			delete[] a.nume;
			a.nume = nullptr;
		}
		a.nume = new char[buffer.length() + 1];//echivalent lui strlen(buffer)
		strcpy_s(a.nume, buffer.length() + 1, buffer.data());//meth data extrage char*-ul din string
		cout << "Introduceti departament: ";
		//in >> a.departament;
		int codDepartament;
		in >> codDepartament;
		//cu riscul ca utilizatorul introduce si alte valori....
		a.departament = (Departament)codDepartament;
		cout << "Introduceti salariu: ";
		in >> a.salariu;
		cout << "Introduceti nr bonusuri: ";
		in >> a.nrBonusuri;
		//pentru no memory leaks, obj a deja exista
		if (a.listaBonusuri != nullptr) {
			delete[] a.listaBonusuri;
			a.listaBonusuri = nullptr;
		}
		if (a.nrBonusuri <= 0) {
			a.nrBonusuri = 0;
			a.listaBonusuri = nullptr;
		}
		else {
			//alocam zm pentru noua dimensiune citita
			a.listaBonusuri = new float[a.nrBonusuri];
			cout << "Introduceti lista bonusuri: ";
			for (int i = 0; i < a.nrBonusuri; i++)
				in >> a.listaBonusuri[i];
		}
		return in;
	}
};

int Angajat::nrAngajati = 0;

bool operator>(float _altSalariu, const Angajat& a) {
	return _altSalariu > a.salariu;
}

int main() {
	Angajat a1;

	float bonusuri[] = { 120.5,1000,1200 };
	Angajat a2("Gigel", Departament::IT, 12000, 3, bonusuri);
	cout << a2; //(cout->obiect de tip ostream) si (a2->Angajat)
	//operator<<(cout, a2);
	//cin >> a2;//istream >> Angajat
	cout << a2;

	a1 = ++a2;
	cout << a1 << a2;
	a1 = a2++;
	cout << a1 << a2;

	float salariuTotal = a2 + a1;
	cout << "\nSalariu total folosind operator+ " << salariuTotal;

	float bonus = a2[0];//utilizare op index[]
	cout << "\nBonus folosind operator index[]: " << bonus;
	//op index cu rol de modificari 
	//a2[0] = 123;

	//exemple operator cast
	float bonusMaxim = a2;//cast implicit la float
	cout << "\nBonus maxim folosind cast la float implicit: " << bonusMaxim;
	
	int test = a2 - 10;//apel implicit cast la float
	float rez = 12.5;
	int val = rez;
	/*
	!
	cast
	() functie
	*/


	/*
	P1.se identif tipul operatorului (binar/unar, aritmetic, logic...)
	P2.se indetif tipul operanzilor
	P3.daca primul operand este de tipul clasei, atunci
	se poate supraincarca printr-o metoda a clasei (primul
	operand este "inghitit" de this). daca nu,
	atunci obligatoriu se implementeaza printr-o functie globala
	(primeste ca parametri toti operanzii)
	P4.!!!ce obiecte se modifica?
	P5. !!!ce returneaza metoda
	*/
	return 0;
}