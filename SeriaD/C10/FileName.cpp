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

class Student :public Persoana {
	string facultate;
public:
	Student() {
		cout << "\nAPEL CONSTRUCTOR FARA PARAM STUDENT";
		this->facultate = "-";
	}

	Student(string _nume, int _varsta, string _facultate) :Persoana(_nume, _varsta) {
		cout << "\nAPEL CONSTRUCTOR CU TOTI PARAM STUDENT";
		this->facultate = _facultate;
	}

	Student(const Student& s) :Persoana(s) {
		cout << "\nAPEL CONSTRUCTOR COPY STUDENT";
		this->facultate = s.facultate;
	}

	Student& operator=(const Student& s) {
		Persoana::operator=(s);
		this->facultate = s.facultate;
		return *this;
	}

	friend ostream& operator<<(ostream& out, const Student& s) {
		out << (Persoana)s;
		out << ", facultate: " << s.facultate;
		return out;
	}

	friend istream& operator>>(istream& in, Student& s) {
		in >> (Persoana&)s;
		cout << "Facultate: ";
		in >> s.facultate;
		return in;
	}
};

int main() {
	Persoana p1("Maria", 10);
	cout << p1;
	Persoana p2(p1);
	p1 = p2;
	cout << p1;

	Student s1;
	cout << s1;
	Student s2(s1);
	cout << s2;
	Student s3("Gigel", 19, "CSIE");
	cout << s3;
	s1 = s3;
	cout << s1;
	cin >> s3;
	cout << s3;
	return 0;
}