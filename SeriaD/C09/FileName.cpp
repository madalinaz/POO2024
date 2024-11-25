#include<iostream>
using namespace std;

class Student {
	string nume;
	static int nrStudenti;
public:
	static float taxaRestanta;

	Student(string _nume) {
		this->nume = _nume;
		Student::nrStudenti++;
	}

	static int getNrStudenti() {
		return Student::nrStudenti;
	}

	//verifica daca param sunt potentiali pentru un obj student
	static bool verificare(string _nume, int _varsta) {
		//to do de adaugat conditii
		return true;
	}
};

float Student::taxaRestanta = 100;
int Student::nrStudenti = 0;

class Masina {
public:
	string model;
};

//has a
class Persoana {
public:
	string nume;
	Masina masina;

	Persoana() {
		this->nume = "Anonim";
		this->masina.model = "Dacia";
		this->adresa = "Bucuresti";
		this->contBancar = "123456789";
	}
protected:
	string adresa;//este private pentru exterior clasa sau "public" pentru clasele derivate din ea
private:
	string contBancar;
};

//Stud is a Persoana
class Stud :public Persoana {
public:
	string facultate;
	Persoana::nume;//publicizare

	Stud():Persoana() {
		this->facultate = "ASE";
	}
};

int main() {
	Student s("Gigel");
	cout << endl << s.taxaRestanta;
	cout << endl << Student::taxaRestanta;
	Student::taxaRestanta = -20;
	cout << endl << Student::getNrStudenti();
	cout << endl << Student::verificare("Gigel", 19);

	cout << endl << "\n-------DERIVARE--------";
	Stud s2;
	Persoana p1;
	
	return 0;
}