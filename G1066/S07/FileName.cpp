#include<iostream>
using namespace std;

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
	cin >> a2;//cin este un obj de tip istream
	cout << a2;

	/*
	! ++ (pre si post)
	+ (obj + obj; obj + int; int + obj)
	cast
	[] (index ce primeste o pozitie dar si index ce returneaza o pozitie)
	<< si >>
	functie ()
	*/


	return 0;
}