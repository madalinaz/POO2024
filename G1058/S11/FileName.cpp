#include<iostream>
using namespace std;

class Angajat {

protected:
	string nume = "Anonim";
	float salariuBaza = 0;

public:
	Angajat() {
	}

	Angajat(string _nume, float _salariuBaza) {
		this->nume = _nume;
		this->salariuBaza = _salariuBaza;
	}

	Angajat(const Angajat& a) {
		this->nume = a.nume;
		this->salariuBaza = a.salariuBaza;
	}

	Angajat& operator=(const Angajat& a) {
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

	float calculSalariu() {
		return this->salariuBaza;
	}
	bool operator==(const Angajat& a)const {
		return this->nume == a.nume;
	}

};
//Manager is an angajat
//Manager has a lista angajati(vector alocat dinamic de obiecte de tip angajat)

class Manager :public Angajat {
	int nrSubalterni;
	Angajat* listaAngajati;
	int grad;//1-5

public:
	//Constructor fara param
	Manager() {
		this->nrSubalterni = 0;
		this->listaAngajati = nullptr;
		this->grad = 0;

	}
	//Constructor cu param, mai putin vector si dim
	Manager(string _nume, float _salariuBaza, int _grad) :Angajat(_nume, _salariuBaza) {
		this->nrSubalterni = 0;
		this->listaAngajati = nullptr;
		/*this->nume = _nume;
		if (_salariuBaza > 0)
			this->salariuBaza = _salariuBaza;
		else
			this->salariuBaza = 0;*///Asa nu
		if (_grad >= 0 && _grad <= 5)
			this->grad = _grad;
		else
			this->grad = 1;

	}
	//constructor de copiere
	Manager(const Manager& m) :Angajat(m) {
		/*this->nume = m.nume;
		if (m.salariuBaza > 0)
			this->salariuBaza = m.salariuBaza;
		else
			this->salariuBaza = 0;*/
		this->nrSubalterni = m.nrSubalterni;
		this->listaAngajati = new Angajat[this->nrSubalterni];
		for (int i = 0; i < this->nrSubalterni; i++)
			this->listaAngajati[i] = m.listaAngajati[i];
		if (m.grad >= 0 && m.grad <= 5)
			this->grad = m.grad;
		else
			this->grad = 1;
	}
	//operator =
	Manager& operator=(const Manager& m) {
		if (this != &m) {
			Angajat::operator=(m);
			if (this->listaAngajati != nullptr)
			{
				delete[]this->listaAngajati;
				this->listaAngajati = nullptr;
			}
			this->nrSubalterni = m.nrSubalterni;
			this->listaAngajati = new Angajat[this->nrSubalterni];
			for (int i = 0; i < this->nrSubalterni; i++)
				this->listaAngajati[i] = m.listaAngajati[i];
			if (m.grad >= 0 && m.grad <= 5)
				this->grad = m.grad;
			else
				this->grad = 1;

		}
		return*this;
	}
	//destructor
	~Manager() {
		if (this->listaAngajati != nullptr)
		{
			delete[]this->listaAngajati;
			this->listaAngajati = nullptr;
		}
	}
	//ostream
	friend ostream& operator<<(ostream& out, Manager& m)
	{
		out << "\n--------------------\n";
		out << (Angajat)m;
		out << "\nnr subalterni:" << m.nrSubalterni;
		out << "\nsubalterni:";
		for (int i = 0; i < m.nrSubalterni; i++)
		{
			out << "\n" << (Angajat)m.listaAngajati[i];
		}
		out << "\ngradul angajatului:" << m.grad;
		out << "\n-------------------------\n";
		return out;
	}
	//Operator +=(fara validari)
	/*Manager& operator+=(const Angajat& a) {
		Manager copie = *this;
		delete[]this->listaAngajati;
		this->nrSubalterni++;
		this->listaAngajati = new Angajat[this->nrSubalterni];
		for (int i = 0; i < this->nrSubalterni - 1; i++)
			this->listaAngajati[i] = copie.listaAngajati[i];
		this->listaAngajati[this->nrSubalterni-1] = a;
		return *this;
	}*/
	//Operator +=(cu validari+ unicitate(nenorocire))
	Manager& operator+=(const Angajat& a) {
		Manager copie = *this;
		bool OK = 1;
		for (int i = 0; i < copie.nrSubalterni; i++)
		{
			if (copie.listaAngajati[i] == a)
				OK = 0;
		}
		if (OK == 1) {
			delete[]this->listaAngajati;
			this->nrSubalterni++;
			this->listaAngajati = new Angajat[this->nrSubalterni];


			for (int i = 0; i < this->nrSubalterni - 1; i++)
				this->listaAngajati[i] = copie.listaAngajati[i];

			this->listaAngajati[this->nrSubalterni - 1] = a;
		}

		return *this;
	}
};


int main() {
	Manager m1;
	cout << m1;
	Manager m2("andrei", 6200, 3);
	cout << m2;
	m1 = m2;
	cout << m1;
	Manager m3("Ionescu", 220000, 5);
	m1 = m3;
	cout << m3;
	Angajat a1("gigel", 222.23);
	m1 += a1;
	cout << m1;
	Angajat a2("costelou", 7100.2);
	m1 += a2;
	Angajat a3("gigel", 2223);
	m1 += a3;
	cout << m1;
	return 0;
}
