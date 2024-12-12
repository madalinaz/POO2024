#include<iostream>
using namespace std;

class Angajat {

protected:
	string nume = "Anonim";
	float salariuBaza = 0;

public:
	Angajat() {
		cout << "\nCONSTRUCTOR FARA PARAM ANGAJAT";
	}

	Angajat(string _nume, float _salariuBaza) {
		cout << "\nCONSTRUCTOR CU PARAM ANGAJAT";
		this->nume = _nume;
		this->salariuBaza = _salariuBaza;
	}

	Angajat(const Angajat& a) {
		cout << "\nCONSTRUCTOR COPIERE ANGAJAT";
		this->nume = a.nume;
		this->salariuBaza = a.salariuBaza;
	}

	Angajat& operator=(const Angajat& a) {
		cout << "\nOP= ANGAJAT";
		if (this != &a) {
			this->nume = a.nume;
			this->salariuBaza = a.salariuBaza;
		}
		return *this;
	}

	friend ostream& operator<<(ostream& out, const Angajat& a) {
		out << "\nNume: " << a.nume;
		out << "\nSalariu baza: " << a.salariuBaza;
		return out;
	}

	friend istream& operator>>(istream& in, Angajat& a) {
		cout << "\nIntroduceti nume: ";
		in >> a.nume;
		cout << "Introduceti salariu: ";
		in >> a.salariuBaza;
		return in;
	}

	~Angajat() {
		cout << "\nDESTRUCTOR ANGAJAT";
	}

	bool operator==(const Angajat& a) {
		if (this->nume != a.nume)
			return false;
		if (this->salariuBaza != a.salariuBaza)
			return false;
		return true;
	}
};

//relatia de tip is a
//relatie de mostenire/derivare/specializare
//Manager is a Angajat?
//Manager has a lista Angajati? (vector static de obj de tip Angajat)
//clasa derivata se ocupa doar de ce a adaugat + trimite spre clasa de baza sa se ocupe de restu

class Manager: public Angajat {
	int nrSubalterni;
	Angajat listaAngajati[10];

public:
	Manager(){
		this->nrSubalterni = 0;
	}

	Manager(string _nume, float _salariuBaza, int _nrSubAlterni, Angajat _listaAngajati[10]):Angajat(_nume,_salariuBaza) {
		this->nrSubalterni = _nrSubAlterni;
		for (int i = 0; i < this->nrSubalterni; i++)
			this->listaAngajati[i] = _listaAngajati[i];
	}

	//constructor cu param (combinat)
	Manager(Angajat _a, int _nrSubAlterni, Angajat _listaAngajati[10]) :Angajat(_a) {
		this->nrSubalterni = _nrSubAlterni;
		for (int i = 0; i < this->nrSubalterni; i++)
			this->listaAngajati[i] = _listaAngajati[i];

	}

	//constructor copiere
	Manager(const Manager& m):Angajat(m)//upcast implicit
	{
		this->nrSubalterni = m.nrSubalterni;
		for (int i = 0; i < this->nrSubalterni; i++)
			this->listaAngajati[i] = m.listaAngajati[i];
	}

	Manager& operator=(const Manager& m) {
		if (this != &m) {
			//this->Angajat::operator=(m);//upcast implicit
			Angajat::operator=(m);
			this->nrSubalterni = m.nrSubalterni;
			for (int i = 0; i < this->nrSubalterni; i++)
				this->listaAngajati[i] = m.listaAngajati[i];
		}
		return *this;
	}

	//destructor
	~Manager() {
		//destructor apeleaza implicit destructor clasa de baza
	}

	friend ostream& operator<<(ostream& out, const Manager& m) {
		out << (Angajat)m;//upcast prin valoare explicit
		out << "\nNr subalterni: " << m.nrSubalterni;
		out << "\nLista subalterni: ";
		for (int i = 0; i < m.nrSubalterni; i++)
			out << m.listaAngajati[i];
		return out;
	}

	friend istream& operator>>(istream& in, Manager& m) {
		in >> (Angajat&)m;//upcast prin referinta explicit
		cout << "\nIntroduceti nr subalterni: ";
		in >> m.nrSubalterni;
		for (int i = 0; i < m.nrSubalterni; i++) {
			cout << "subaltern[" << i << "]=";
			in >> m.listaAngajati[i];
		}
		return in;
	}

	bool operator==(const Manager& m) {
		if (Angajat::operator==(m) == false)
			return false;
		if (this->nrSubalterni != m.nrSubalterni)
			return false;
		//....etc pentru vector
		return true;
	}
};

int main() {
	Angajat a1("Gigel", 1200);
	Manager m1;
	Manager m2("Costel", 1500, 0, nullptr);
	Manager m3(m2);
	m1 = m3;
	cout << "\n------------------";
	cout << m1;
	cout << "\n------------------";
	cin >> m1;
	cout << m1;
	return 0;
}