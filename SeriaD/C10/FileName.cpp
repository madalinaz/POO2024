#include<iostream>
using namespace std;


class Persoana {
	string nume;
	int varsta;

public:
	Persoana() {
		cout << "\nAPEL CONSTRUCTOR FARA PARAM PERSOANA";
		this->nume = "Anonim";
		this->varsta = 0;
	}
	Persoana(string _nume, int _varsta) {
		cout << "\nAPEL CONSTRUCTOR CU TOTI PARAM PERSOANA";
		this->nume = _nume;
		this->varsta = _varsta;
	}

	Persoana(const Persoana& p) {
		cout << "\nAPEL CONSTRUCTOR COPY PERSOANA";
		this->nume = p.nume;
		this->varsta = p.varsta;
	}

	void setNume(string _nume) {
		if (_nume.length() >= 5) {
			this->nume = _nume;
		}
		else {
			throw - 1;//arunca un cod de eroare
		}
	}

	void setVarsta(int _varsta) {
		if (_varsta > 0) {
			this->varsta = _varsta;
		}
		else {
			throw new exception("varsta negativa");
		}
	}

	bool operator<(const Persoana& p) {
		cout << "\nAPEL OP < PERSOANA";
		return this->varsta < p.varsta;
	}

	Persoana& operator=(const Persoana& p) {
		cout << "\nAPEL OP= PERSOANA";
		this->nume = p.nume;
		this->varsta = p.varsta;
		return *this;
	}

	~Persoana() {
		cout << "\nAPEL DESTRUCTOR PERSOANA";
	}

	friend ostream& operator<<(ostream& out, const Persoana& p) {
		out << "\nNume: " << p.nume << ", varsta: " << p.varsta;
		return out;
	}

	friend istream& operator>>(istream& in, Persoana& p) {
		cout << "\nNume: ";
		in >> p.nume;
		cout << "Varsta: ";
		in >> p.varsta;
		return in;
	}
};

class Student: public Persoana {
	string facultate;
	int anStudiu;

public:
	Student():Persoana() {
		cout << "\nAPEL CONSTRUCTOR FARA PARAM STUDENT";
		this->facultate = "-";
		this->anStudiu = 0;
	}

	Student(string _nume, int _varsta, string _facultate, int _anStudiu):Persoana(_nume,_varsta) {
		cout << "\nAPEL CONSTRUCTOR CU TOTI PARAM STUDENT";
		this->facultate = _facultate;
		this->anStudiu = _anStudiu;
	}

	Student(Persoana _p, string _facultate, int _anStudiu):Persoana(_p) {
		cout << "\nAPEL CONSTRUCTOR CU TOTI PARAM 2 STUDENT";
		this->facultate = _facultate;
		this->anStudiu = _anStudiu;
	}

	Student(const Student& s):Persoana(s)//apel constructor copiere + upcast
	{
		cout << "\nAPEL CONSTRUCTOR COPY STUDENT";
		this->facultate = s.facultate;
		this->anStudiu = s.anStudiu;
	}

	Student& operator=(const Student& s) {
		cout << "\nAPEL OP= STUDENT";
		if (this != &s) {
			//this->Persoana::operator=(s);
			Persoana::operator=(s);
			this->facultate = s.facultate;
			this->anStudiu = s.anStudiu;
		}
		return *this;
	}

	~Student() {
		cout << "\nAPEL DESTRUCTOR STUDENT";
	}

	friend ostream& operator<<(ostream& out, const Student& s) {
		out << (Persoana)s;//upcast prin valoare
		out << ", facultate: " << s.facultate << ", an studiu: " << s.anStudiu;
		return out;
	}

	friend istream& operator>>(istream& in, Student& s) {
		in >> (Persoana&)s;//upcast prin referinta
		cout << "Introduceti facultate: ";
		in >> s.facultate;
		cout << "Introduceti an studiu: ";
		in >> s.anStudiu;
		return in;
	}
};

int main() {
	Student s1;
	Student s2("Gigel", 19, "CSIE", 1);
	Persoana p1("Costel", 20);
	Student s3(p1, "FABIZ", 2);
	cout << "\n------------------------";
	Student s4(s3);
	cout << "\n------------------------";
	s3 = s4;
	cout << "\n------------------------";
	cout << s3;
	cout << "\n------------------------";
	//cin >> s3;
	cout << "\n------------------------";
	cout << s3;
	cout << "\n-------ARUNCARE DE EXCEPTII--------";
	try {
		p1.setNume("AB");
		cout << p1;
	}
	catch (int cod) {
		cout << "\nNu s-a setat numele";
	}

	try {
		p1.setVarsta(-5);
		cout << p1;
	}
	catch (exception* ex) {
		cout << endl<<ex->what();//este un getter pentru mesaj
		delete ex;
	}
	
	cout << "\n------------------------";
	//to do
	//derivare
	// meth de tratare exceptii
	//meth virtuale + meth virtuale pure
	//clase abstracte + interfete
	//fisiere text + binare
	//clase template
	//STL
	return 0;
}