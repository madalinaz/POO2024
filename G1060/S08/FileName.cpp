#include<iostream>
using namespace std;

//enum
//string*
//const, static
//validari in constructori
//operatori supraincarcati prin friend
//redimensionare vector
//validari pentru const

class Magazin {
	const int id;//id-ul este >=100
	//daca se introduce un id<100, atunci se va folosi pragul 100
	string denumire;//de lungime minim 5 caractere sau -, daca lipseste
	int nrProduse;
	int* listaCoduri;//vector este format din elem distincte

	static int generareId(int _id) {
		if (_id < 100)
			return 100;
		return _id;
	}
public:


	Magazin(int _id) :id(Magazin::generareId(_id)) {
		this->denumire = "-";
		this->nrProduse = 0;
		this->listaCoduri = nullptr;
	}

	Magazin(int _id, string _denumire) :id(Magazin::generareId(_id)) {
		if (_denumire.length() >= 5)
			this->denumire = _denumire;
		else
			this->denumire = "-";
		this->nrProduse = 0;
		this->listaCoduri = nullptr;
	}

	Magazin(const Magazin& m) :id(m.id) {
		this->denumire = m.denumire;
		if (m.nrProduse > 0 && m.listaCoduri != nullptr) {
			this->nrProduse = m.nrProduse;
			this->listaCoduri = new int[this->nrProduse];
			for (int i = 0; i < this->nrProduse; i++)
				this->listaCoduri[i] = m.listaCoduri[i];
		}
		else {
			this->nrProduse = 0;
			this->listaCoduri = nullptr;
		}
	}

	Magazin& operator=(const Magazin& m) {
		if (this != &m) {
			if (this->listaCoduri != nullptr) {
				delete[] this->listaCoduri;
				this->listaCoduri = nullptr;
			}
			this->denumire = m.denumire;
			if (m.nrProduse > 0 && m.listaCoduri != nullptr) {
				this->nrProduse = m.nrProduse;
				this->listaCoduri = new int[this->nrProduse];
				for (int i = 0; i < this->nrProduse; i++)
					this->listaCoduri[i] = m.listaCoduri[i];
			}
			else {
				this->nrProduse = 0;
				this->listaCoduri = nullptr;
			}
		}
		return *this;
	}

	~Magazin() {
		if (this->listaCoduri != nullptr) {
			delete[] this->listaCoduri;
			this->listaCoduri = nullptr;
		}
	}

	friend ostream& operator<<(ostream& out, const Magazin& m) {
		out << "\nId: " << m.id << ", denumire: " << m.denumire << ", nr produse: " << m.nrProduse << ", lista coduri: ";
		for (int i = 0; i < m.nrProduse; i++)
			out << m.listaCoduri[i] << " ";
		return out;
	}

	void adaugaCod(int cod) {
		bool ok = true;
		for (int i = 0; i < this->nrProduse && ok == true; i++)
			if (this->listaCoduri[i] == cod)
				ok = false;
		if (ok == true) {
			Magazin copie = *this;//copie ptr this
			if (this->listaCoduri != nullptr) {
				delete[] this->listaCoduri;
				this->listaCoduri = nullptr;
			}
			this->listaCoduri = new int[this->nrProduse + 1];
			for (int i = 0; i < this->nrProduse; i++)
				this->listaCoduri[i] = copie.listaCoduri[i];
			this->listaCoduri[this->nrProduse] = cod;
			this->nrProduse++;
		}
	}

	//supraincarcare operator +=(int)
	Magazin& operator+=(int cod) {
		bool ok = true;
		for (int i = 0; i < this->nrProduse && ok == true; i++)
			if (this->listaCoduri[i] == cod)
				ok = false;
		if (ok == true) {
			Magazin copie = *this;//copie ptr this
			if (this->listaCoduri != nullptr) {
				delete[] this->listaCoduri;
				this->listaCoduri = nullptr;
			}
			this->listaCoduri = new int[this->nrProduse + 1];
			for (int i = 0; i < this->nrProduse; i++)
				this->listaCoduri[i] = copie.listaCoduri[i];
			this->listaCoduri[this->nrProduse] = cod;
			this->nrProduse++;
		}
		return *this;
	}

	friend bool operator!=(int cod, const Magazin& m)
	{
		for (int i = 0; i < m.nrProduse; i++)
			if (cod == m.listaCoduri[i])
				return false;
		return true;
	}
	int operator[](int _cod) {
		for (int i = 0; i < this->nrProduse; i++)
			if (this->listaCoduri[i] == _cod)
				return i;
		return -1;
	}

	Magazin operator+(const Magazin& m) {
		Magazin rez = *this;
		rez.denumire += "-";
		rez.denumire += m.denumire;
		for (int i = 0; i < m.nrProduse; i++)
			rez.adaugaCod(m.listaCoduri[i]);
		return rez;
	}

	int operator()(int pragMinCod) {
		int ct = 0;
		for (int i = 0; i < this->nrProduse; i++)
			if (this->listaCoduri[i] >= pragMinCod)
				ct++;
		return ct;
	}

	//cast implicit la string
	operator string() {
		return this->denumire;
	}
};

int main() {
	Magazin m1(12, "Magazin1");
	cout << m1;
	m1.adaugaCod(10);
	m1.adaugaCod(20);
	m1.adaugaCod(10);
	m1.adaugaCod(30);
	cout << m1;
	m1 += 50;
	cout << m1;

	if (60 != m1)
		cout << "\nCodul 60 NU se gaseste in m1";
	else
		cout << "\nInvers";

	int pozitie = m1[50];
	cout << endl << pozitie;
	Magazin m2(123, "Magazin2");
	m2.adaugaCod(90);
	m2.adaugaCod(50);
	Magazin m3(1234);
	m3 = m2 + m1;
	cout << m3;
	string denumire = m3; //cast la string
	cout << endl << denumire;
	int nrProduse = m3(30); //cate produse depasesc in cod valoare 30 ->operator functie
	cout << endl << nrProduse;
	return 0;
}