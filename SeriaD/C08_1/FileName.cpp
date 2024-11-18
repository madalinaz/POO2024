#include<iostream>
using namespace std;

class Masina {
	string model;
	int nrDeplasari;
	float* distantaDeplasari;
	float pret;
	const int anFabricatie;

public:
	Masina(int _anFabricatie) : anFabricatie(_anFabricatie) {
		this->model = "-";
		this->nrDeplasari = 0;
		this->distantaDeplasari = nullptr;
		this->pret = 0;
	}

	Masina(string _model, int _nrDeplasari, float* _distantaDeplasari, float _pret, int _anFabricatie) : anFabricatie(_anFabricatie) {
		this->model = _model;
		this->pret = _pret;
		if (_nrDeplasari > 0 && _distantaDeplasari != nullptr) {
			this->nrDeplasari = _nrDeplasari;
			this->distantaDeplasari = new float[this->nrDeplasari];
			for (int i = 0; i < this->nrDeplasari; i++)
				this->distantaDeplasari[i] = _distantaDeplasari[i];
		}
		else {
			this->nrDeplasari = 0;
			this->distantaDeplasari = nullptr;
		}
	}

	Masina(const Masina& m) :anFabricatie(m.anFabricatie) {
		this->model = m.model;
		this->pret = m.pret;
		if (m.nrDeplasari > 0 && m.distantaDeplasari != nullptr) {
			this->nrDeplasari = m.nrDeplasari;
			this->distantaDeplasari = new float[this->nrDeplasari];
			for (int i = 0; i < this->nrDeplasari; i++)
				this->distantaDeplasari[i] = m.distantaDeplasari[i];
		}
		else {
			this->nrDeplasari = 0;
			this->distantaDeplasari = nullptr;
		}
	}

	Masina& operator=(const Masina& m) {
		if (this != &m) {
			if (this->distantaDeplasari != nullptr) {
				delete[] this->distantaDeplasari;
				this->distantaDeplasari = nullptr;
			}
			this->model = m.model;
			this->pret = m.pret;
			if (m.nrDeplasari > 0 && m.distantaDeplasari != nullptr) {
				this->nrDeplasari = m.nrDeplasari;
				this->distantaDeplasari = new float[this->nrDeplasari];
				for (int i = 0; i < this->nrDeplasari; i++)
					this->distantaDeplasari[i] = m.distantaDeplasari[i];
			}
			else {
				this->nrDeplasari = 0;
				this->distantaDeplasari = nullptr;
			}
		}
		return *this;
	}

	//forma pre-incrementare
	Masina& operator++() {
		this->pret++;
		return *this;//returneaza starea de dupa incrementare
	}

	//forma post-incrementare
	//return prin valoare pentru ca
	//copie se distruge ( este pe stiva op++)
	Masina operator++(int) {
		Masina copie = *this;
		this->pret++;
		return copie;//returnez starea de dinainte a incrementarii
	}

	//putem const ca sa protejam obj this
	//cu const nu putem sa modificam obj this
	float operator+(float x) const {
		//NU modificam this-ul
		if (x > 0) {
			float total = 0;
			for (int i = 0; i < this->nrDeplasari; i++)
				total += this->distantaDeplasari[i];
			return total + x;
		}
		return 0;
	}

	//operator index
	//daca return e prin valoare, atunci nu face modificari
	//return prin referinta, poate modifica
	//VARIARII
	//op [] primeste un element/cod/cod unic/si intoarce pozitia pe care se gaseste elem cautat
	float operator[](int _index) {
		if (_index >= 0 && _index < this->nrDeplasari)
			return this->distantaDeplasari[_index];
	}

	//cast explicit la int
	explicit operator int() {
		return this->nrDeplasari;
	}

	//operator implicit la string
	//echivalent toString
	operator string() {
		string rez;
		rez += "\nModel: " + this->model;
		char buffer[100];
		//itoa(this->pret, buffer, 10);
		//rez+= ", pret: " + (string)buffer;
		return rez;
	}

	//operator functie
	float operator()(int _index1, int _index2) {
		if (_index1 <= _index2 && _index1 >= 0 && _index2 < this->nrDeplasari) {
			float suma = 0;
			for (int i = _index1; i <= _index2; i++)
				suma += this->distantaDeplasari[i];
			return suma;
		}
	}

	int operator()() {
		int ct = 0;
		for (int i = 0; i < this->nrDeplasari; i++)
			if (this->distantaDeplasari[i] >= 100)
				ct++;
		return ct;
	}


	~Masina() {
		if (this->distantaDeplasari != nullptr) {
			delete[] this->distantaDeplasari;
			this->distantaDeplasari = nullptr;
		}
	}

	void afisare() {
		cout << "\n------------------";
		cout << "\nModel: " << this->model;
		cout << "\nNr deplasari: " << this->nrDeplasari;
		cout << "\nDistanta deplasari: ";
		for (int i = 0; i < this->nrDeplasari; i++)
			cout << this->distantaDeplasari[i] << " ";
		cout << "\nPret: " << this->pret;
		cout << "\nAn fabricatie: " << this->anFabricatie;
	}

	friend ostream& operator<<(ostream& out, const Masina& m);
	friend istream& operator>>(istream& in, Masina& m);
};


//DP Adapter
float operator+(float x, const Masina& m) {
	return m + x;
}

ostream& operator<<(ostream& out, const Masina& m) {
	out << "\n------------------";
	out << "\nModel: " << m.model;
	out << "\nNr deplasari: " << m.nrDeplasari;
	out << "\nDistanta deplasari: ";
	for (int i = 0; i < m.nrDeplasari; i++)
		out << m.distantaDeplasari[i] << " ";
	out << "\nPret: " << m.pret;
	out << "\nAn fabricatie: " << m.anFabricatie;
	return out;
}

//transfer prin referinta m pentru ca il modific
//deci nu declar si constant
istream& operator>>(istream& in, Masina& m) {
	//nu mai pot citi atributele constante
	//SAU POT????DE GANDIT
	cout << "\nIntroduceti model: ";
	in >> m.model;
	cout << "Introduceti pret: ";
	in >> m.pret;
	if (m.distantaDeplasari != nullptr) {
		delete[] m.distantaDeplasari;
		m.distantaDeplasari = nullptr;
	}
	cout << "Introduceti nr deplasari: ";
	int x;
	in >> x;
	if (x > 0) {
		m.nrDeplasari = x;
		m.distantaDeplasari = new float[x];
		cout << "Introduceti deplasarile: ";
		for (int i = 0; i < x; i++)
			in >> m.distantaDeplasari[i];
	}
	else {
		m.nrDeplasari = 0;
		m.distantaDeplasari = nullptr;
	}
	return in;
}

Masina test() {
	float deplasari[] = { 100,200,300 };
	Masina m("Dacia", 3, deplasari, 12000, 2010);
	return m;
}

int main() {
	Masina rez(2010);
	rez = test();
	rez.afisare();
	int x = 2;

	int y = 3;
	y = ++x;
	y = x++;

	float deplasari[] = { 100,200,300 };
	Masina m1("Dacia", 3, deplasari, 12000, 2010);
	Masina m2("Ford", 0, nullptr, 20000, 2024);
	m2 = ++m1;
	m2.operator=(m1.operator++());
	m1.afisare();
	m2.afisare();
	m2 = m1++;
	m2.operator=(m1.operator++(2));
	m1.afisare();
	m2.afisare();

	float totalDeplasari = m1 + 200;
	cout << endl << "Total: " << totalDeplasari;

	float totalDeplasari2 = 300 + m1;
	operator+(x, m1);
	cout << endl << "Total: " << totalDeplasari2;

	cout << m1 << m2;
	//cin >> m1;
	cout << m1;

	//operator index
	float distantaDeplasare = m1[0];
	cout << endl << "\nDistanta deplasare 0 folosind operator index: " << distantaDeplasare;
	//m1[0] = 123; doar ca e return prin & la op[]

	//operator cast
	int nrDeplasari = (int)m1;//conversie/cast explicit de la Masina la int
	cout << "\nNr deplasari folosind cast la int: " << nrDeplasari;
	
	string model = m1;//cast implicit la string
	cout << "\nModel masina folosind cast la string: " << model;
	
	//operator functie
	float sumaDeplasariInInterval = m1(0, 2);//m1.operator()(0,2)
	int nrDeplasariPeste100 = m1();
	return 0;
}