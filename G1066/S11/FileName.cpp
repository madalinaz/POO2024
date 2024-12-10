#include<iostream>
#include<fstream>
using namespace std;

// relatie is a (derivare)
// citire si scriere in fisiere text

class Angajat {

	string nume ="Anonim";

protected:
	float salariuBaza = 0;
	
public:
	Angajat() {
		cout << "\nAPEL CONSTRUCTOR FARA PARAM ANGAJAT";
	}

	Angajat(string _nume, float _salariuBaza) {
		cout << "\nAPEL CONSTRUCTOR CU TOTI PARAM ANGAJAT";
		this->nume = _nume;
		this->salariuBaza = _salariuBaza;
	}

	Angajat(const Angajat& a) {
		cout << "\nAPEL CONSTRUCTOR COPIERE ANGAJAT";
		this->nume = a.nume;
		this->salariuBaza = a.salariuBaza;
	}

	Angajat& operator=(const Angajat& a) {
		cout << "\nAPEL OPERATOR= ANGAJAT";
		if (this != &a) {
			this->nume = a.nume;
			this->salariuBaza = a.salariuBaza;
		}
		return *this;
	}

	~Angajat() {
		cout << "\nAPEL DESTRUCTOR ANGAJAT";
	}

	//afisarea la consola
	friend ostream& operator<<(ostream& out, const Angajat& a) {
		out << "\nNume: " << a.nume;
		out << "\nSalariu baza: " << a.salariuBaza;
		return out;
	}

	//afisarea in fisiere text
	friend ofstream& operator<<(ofstream& out, const Angajat& a) {
		out << "\n" << a.nume;
		out << "\n" << a.salariuBaza;
		return out;
	}

	friend istream& operator>>(istream& in, Angajat& a) {
		cout << "\nIntroduceti nume: ";
		in >> a.nume;
		cout << "Introduceti salariu baza: ";
		in >> a.salariuBaza;
		return in;
	}

	friend ifstream& operator>>(ifstream& in, Angajat& a) {
		in >> a.nume;
		in >> a.salariuBaza;
		return in;
	}
};

//relatiei de tipul is a / derivare/mostenire/specializare
//nu orice Angajat este un Profesor
//orice Profesor este un Angajat
//avantajul: reutilizarea codului
//clasa Profesor ->clasa derivata/copil
//clasa Angajat->clasa baza/parinte

//clasa derivata se ocupa DOAR de zona ei noua + trimite spre clasa de Baza responsabilitatea zonei sale
class Profesor:public Angajat{
	const int cod;
	int nrOreSuplimentare;
	static float tarifOrar;

public:
	Profesor():cod(0),Angajat() {
		cout << "\nAPEL CONSTRUCTOR FARA PARAM PROFESOR";
		this->nrOreSuplimentare = 0;
	}

	Profesor(string _nume, float _salariuBaza, int _cod, int _nrOreSuplimentare):cod(_cod), Angajat(_nume,_salariuBaza) {
		cout << "\nAPEL CONSTRUCTOR CU TOTI PARAM PROFESOR";
		this->nrOreSuplimentare = _nrOreSuplimentare;
	}

	Profesor(const Profesor& p):cod(p.cod), Angajat(p) //apel constructor copiere din baza + upcast
	{
		cout << "\nAPEL CONSTRUCTOR COPIERE PROFESOR";
		this->nrOreSuplimentare = p.nrOreSuplimentare;
	}

	Profesor& operator=(const Profesor& p) {
		cout << "\nAPEL OPERATOR= PROFESOR";
		if (this != &p) {
			//cer apel op= din clasa de baza
			Angajat::operator=(p);//upcast dintr-un Profesor(p) intr-un Angajat
			this->nrOreSuplimentare = p.nrOreSuplimentare;
		}
		return *this;
	}

	~Profesor() {
		cout << "\nAPEL DESTRUCTOR PROFESOR";
	}

	friend ostream& operator<<(ostream& out, const Profesor& p) {
		//cerem apel op<< care este specializat in a afisa obiecte de tip Angajat
		out << (Angajat)p;//upcast explicit prin valoare
		out << "\nCod: " << p.cod;
		out << "\nNr ore suplimentare: " << p.nrOreSuplimentare;
		return out;
	}

	friend istream& operator>>(istream& in, Profesor& p) {
		in >> (Angajat&)p; //upcast explicit prin referinta
		cout << "Introduceti nr ore suplimentare: ";
		in >> p.nrOreSuplimentare;
		return in;
	}
};

float Profesor::tarifOrar = 100;

//relatie has a =>Masina has a Angajat
class Masina {
	string model;
	int serie;
	int km;
	Angajat a;
};

int main() {
	Angajat a("Gigel", 1200);
	cout << a;
	//cin >> a;
	//cout << a;

	cout << "\n--------------CLASA DERIVATA------------------";
	Profesor p1;
	Profesor p2("Gigel", 2000, 1234, 10);
	Profesor p3(p2);
	p1 = p2;
	cout << p3;
	//cin >> p3;
	//cout << p3;
	cout << "\n--------------FISIERE TEXT------------------";
	ofstream f("angajati.txt");//fisier de scriere
	f << a;//ofstream is a ostream
	f.close();
	ifstream g("angajati.txt");
	Angajat a2;
	g >> a2;
	cout << a2;
	g.close();

	//DE COMPLETAT LA FISIERE TEXT
	//meth/functie care detine un vector de obj si introduce in fisier
	//1. doar unele obiecte pe baza unei filtrari (toate informatiile despre angajatii care au un salariu peste un prag primit ca param)
	//2. valori agregate (media tuturor angajatilor)....(numele doar al angajatilor care....)
	return 0;
}