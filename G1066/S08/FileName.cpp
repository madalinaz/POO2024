#include<iostream>
using namespace std;

class Sejur {
	const int id;
	string destinatie="-";
	float pretBaza=0;
	int nrExcursiiOptionale=0;
	float* pretExcursie=nullptr;
	string numeGhid="-";
	int durataSejur = 0;
	static float pretMinimExcursie;
	float bacsisGhid;

public:
	Sejur(int _id) :id(_id) {

	}

	//constructor cu toti param
	//cosntructor copiere
	//op =
	//destructor

	int getNrMaximExcursii(float bugetMaximSejur) {
		int ct = 0;
		//scad din buget pretul de baza sejur
		//fac copie pe vector de excursii optionale
		//sortez crescator
		//le aleg pe cele mai ieftine pana ating pretul de buget maxim
		return ct;
	}

	explicit operator float() {
		//total pe pret sejur + toate optionalele
		return 0.0f;
	}

	//exemplu lucru cu siruri de caractere si citiri cu spatii
	//https://github.com/madalinaz/POO2024/blob/main/G1061/S03/S03.cpp

	//operator -- in post-decremetnare
	Sejur operator--(int) {
		Sejur copie = *this;
		//get min si de cate ori apare
		float min = this->pretExcursie[0];
		int ctMin = 1;
		for(int i=1;i<this->nrExcursiiOptionale;i++)
			if (this->pretExcursie[i] < min) {
				min = this->pretExcursie[i];
				ctMin = 1;
			}
			else if (this->pretExcursie[i] == min) {
				ctMin++;
			}
		//dezalocare pe this
		//alocare cat trebuie
		//copiere din copie a tuturor elem diferite de min
		return copie;
	}

	bool operator<(int x) const {
		//evalueaza un Sejur dpdv al nr de excursii optionale
		return this->nrExcursiiOptionale < x;
	}
};

bool operator<=(int x, const Sejur& s) {
	return !(s < x);
}

enum Departament {
	IT, HR, VZ
};

//TO DO supraincarcare operator >> si << pentru a citi si scrie obj de tip Departament
ostream& operator<<(ostream& out, Departament d) {
	if (d == Departament::IT)
		out << "IT";
	else
		out << "OTHER";
	return out;
}

class Angajat {
	const int id;//cod unic care se genereaza automat
	char* nume;
	float salariu;
	Departament departament;
	static int nrAngajati;
	int nrBonusuri;
	float* listaBonusuri;

public:
	//constr fara param
	Angajat() :id(1000 + (++Angajat::nrAngajati)) {
		this->nume = new char[strlen("Anonim") + 1];
		strcpy_s(this->nume, strlen("Anonim") + 1, "Anonim");
		this->salariu = 0;
		this->departament = IT;
		this->nrBonusuri = 0;
		this->listaBonusuri = nullptr;
	}

	//constr cu aproape toti param
	Angajat(const char* _nume, float salariu = 0, Departament = IT) :id(1000 + (++Angajat::nrAngajati)) {
		if (_nume != nullptr) {
			this->nume = new char[strlen(_nume) + 1];
			strcpy_s(this->nume, strlen(_nume) + 1, _nume);
		}
		else {
			this->nume = nullptr;
		}
		this->salariu = salariu;
		this->departament = departament;
		this->nrBonusuri = 0;
		this->listaBonusuri = nullptr;
	}

	//constr de copiere
	Angajat(const Angajat& a) :id(1000 + (++Angajat::nrAngajati)) {
		if (a.nume != nullptr) {
			this->nume = new char[strlen(a.nume) + 1];
			strcpy_s(this->nume, strlen(a.nume) + 1, a.nume);
		}
		else {
			this->nume = nullptr;
		}
		this->salariu = a.salariu;
		this->departament = a.departament;
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
	//op =
	Angajat& operator=(const Angajat& a)
	{
		if (this != &a)
		{
			//combinatie intre destructor si constructor de copiere
			if (this->nume != nullptr)
			{
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
				this->nume = nullptr;
			}
			this->salariu = a.salariu;
			this->departament = a.departament;
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

	//op comparatie
	bool operator<(float x) {
		return this->salariu < x;
	}

	Angajat& operator-=(float x) {
		if (x > 0 && this->salariu > x) {
			this->salariu -= x;
		}
		return *this;
	}

	Angajat& operator+=(float x) {
		if (x > 0) {
			Angajat copie = *this;
			if (this->listaBonusuri != nullptr) {
				delete[] this->listaBonusuri;
				this->listaBonusuri = nullptr;
			}
			this->nrBonusuri++;
			this->listaBonusuri = new float[this->nrBonusuri];
			for (int i = 0; i < copie.nrBonusuri; i++)
				this->listaBonusuri[i] = copie.listaBonusuri[i];
			this->listaBonusuri[this->nrBonusuri - 1] = x;
		}
		return *this;
	}

	bool operator==(Angajat a) {
		if (strcmp(this->nume, a.nume) != 0)
			return false;
		if (this->salariu != a.salariu)
			return false;
		//....
		return true;
	}

	//pre-incrementare
	//return prin referinta pentru ca obj this NU este alocat pe stiva fct operator ++ si NU se distruge dupa ce se termina apelul operatorului++
	Angajat& operator++() {
		this->salariu++;
		return *this;//returnam obj de dupa incrementare
	}

	//post-incrementare
	//returnez prin valoare obj Angajat pentru ca obj copie este declarat pe stiva fct operator++ si este distrus atunci cand se termina executia operatorului ++
	Angajat operator++(int) {
		Angajat copie = *this;
		this->salariu++;
		return copie;//returnez stare obj de dinainte de incrementare
	}

	bool operator!() {
		return this->nume == nullptr;
	}

	//operator index de consultare (return float)
	//operator index si de modificare (get si set) (return float&)
	float operator[](int _index) {
		if (_index >= 0 && _index < this->nrBonusuri) {
			return this->listaBonusuri[_index];
		}
	}

	Angajat operator/(float x) {
		//acest operator NU modifica niciun operand, adica NU modifica pe this
		Angajat rez = *this;
		if (x > 0) {
			for (int i = 0; i < rez.nrBonusuri; i++)
				rez.listaBonusuri[i] /= x;
		}
		return rez;
	}

	//cast explicit la float
	explicit operator float() {
		float salariuTotal = this->salariu;
		for (int i = 0; i < this->nrBonusuri; i++)
			salariuTotal += this->listaBonusuri[i];
		return salariuTotal;
	}

	//cast implicit la string
	operator string() {
		return this->nume;
	}

	//operator functie
	int operator()(float prag) {
		int ct = 0;
		for (int i = 0; i < this->nrBonusuri; i++)
			if (this->listaBonusuri[i] >= prag)
				ct++;
		return ct;
	}

	//get si set pentru nume
	const char* getNume() {
		return this->nume;
	}

	void setNume(const char* _nume)
	{
		if (this->nume != nullptr)
		{
			delete[] this->nume;
			this->nume = nullptr;
		}

		if (_nume != nullptr) {
			this->nume = new char[strlen(_nume) + 1];
			strcpy_s(this->nume, strlen(_nume) + 1, _nume);
		}
		else {
			this->nume = nullptr;
		}
	}

	//meth statice pentru atributul static
	static int  getNrAngajati()
	{
		return Angajat::nrAngajati;
	}

	float getSalariu() {
		this->salariu = 10;
		return this->salariu;
	}


	//destructor
	~Angajat() {
		if (this->nume != nullptr)
		{
			delete[] this->nume;
			this->nume = nullptr;
		}
		if (this->listaBonusuri != nullptr) {
			delete[] this->listaBonusuri;
			this->listaBonusuri = nullptr;
		}
	}

	friend ostream& operator<<(ostream& out, const Angajat& a);

	//este o functie globala dar care este declarata friend in clasa Angajat si avem
	//acces la zona private si protected
	//transfer prin referinta caci vreau sa operez asupra obj real, si nu asupra copiei
	friend istream& operator>>(istream& in, Angajat& a) {
		//nu avem cum sa gestionam atributele constante (adica nu le mai citim si le modificam)
		if (a.nume != nullptr)
		{
			delete[] a.nume;
			a.nume = nullptr;
		}
		cout << "\nIntroduceti nume: ";
		string nume;
		in >> nume;
		a.nume = new char[nume.length() + 1];//length pentru ca nume este string
		strcpy_s(a.nume, nume.length() + 1, nume.data());//metoda data din clasa string este echivalenta cu getString-ul

		cout << "Introduceti salariu: ";
		in >> a.salariu;
		cout << "Introduceti departament: ";
		int codDepartament;
		in >> codDepartament;
		a.departament = (Departament)codDepartament;//cast explicit de la int la Departament
		if (a.listaBonusuri != nullptr) {
			delete[] a.listaBonusuri;
			a.listaBonusuri = nullptr;
		}
		cout << "Introduceti nr bonusuri: ";
		in >> a.nrBonusuri;
		if (a.nrBonusuri <= 0) {
			a.nrBonusuri = 0;
			a.listaBonusuri = nullptr;
		}
		else {
			a.listaBonusuri = new float[a.nrBonusuri];
			cout << "Introduceti lista bonusuri: ";
			for (int i = 0; i < a.nrBonusuri; i++)
				in >> a.listaBonusuri[i];
		}
		return in;
	}
};

int Angajat::nrAngajati = 0;

bool operator<=(float x, Angajat a) {
	return x <= a.getSalariu();
	//return !(a < x);
}

//ostream& pentru ca obj out se modifica si vrem sa pastram respectivele modificari
ostream& operator<<(ostream& out, const Angajat& a) {
	out << "\n-----------<<-------------\n";
	out << "ID: " << a.id << endl;
	out << "Nume: " << a.nume << endl;
	out << "Salariul: " << a.salariu << endl;
	out << "Departament: " << a.departament << endl;
	out << "Nr bonusuri: " << a.nrBonusuri << endl;
	out << "Lista bonusuri: ";
	for (int i = 0; i < a.nrBonusuri; i++)
		out << a.listaBonusuri[i] << " ";
	out << "\n--------------------------\n";
	return out;
}

int main() {

	Angajat a1;
	Angajat a2("Gigel", 10000, IT);
	cout << a2; //cout este un obj de tipul ostream
	cout << a2 << a1;
	//cin >> a2;//cin este un obj de tip istream
	cout << a2;

	a1 = ++a2;
	cout << a1 << a2;
	a1 = a2++;//adauga inca un bonus egal cu ultimul din lista
	//adauga inca un bonus egal cu media tuturor bonusurilor din lista angajatului
	//adaug 1 leu la salariu
	cout << a1 << a2;

	int x = 10;
	int y = 2;
	y = !x;

	if (!x)
		cout << "\nx este 0";
	else
		cout << "\nx este diferit de 0";


	if (!a2)
		cout << "\nAngajatul a2 nu are nume";
	else
		cout << "\nAngajatul a2 are un nume";

	a2 += 100;
	a2 += 200;
	a2 += 300;
	float bonus = a2[1];
	cout << "\nBonusul de pe pozitia 1 este: " << bonus;
	/*a2[1] = 201;
	cout << a2;*/

	a2 = a2 / 2;
	cout << a2;

	/*
	cast
	functie ()
	*/

	float salariuTotal = (float)a2; //cast (operator unar) la float

	string nume = a2;
	cout << endl << nume;
	//float test = a2--;

	//a2.operator=(a1);
	//operator functie
	int nrBonusuriPestePrag = a2(200); //a2.operator()(200)
	cout << endl << nrBonusuriPestePrag;

	Angajat listaAngajati[10];
	int nr;
	//int pozitie = a2(listaAngajati, nr);
	//int nrBonusuri = a2();
	//float medieBonusuri = a2();

	return 0;
}