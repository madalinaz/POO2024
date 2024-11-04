#include<iostream>
using namespace std;

enum Departament {
	IT, HR, VZ
};

class Angajat {
	const int id;//cod unic care se genereaza automat
	char* nume;
	float salariu;
	Departament departament;
	static int nrAngajati;
	static float salariuMediu;//TO DO HOME

public:
	//constr fara param
	Angajat():id(1000+(++Angajat::nrAngajati)) {
		this->nume = new char[strlen("Anonim") + 1];
		strcpy_s(this->nume, strlen("Anonim") + 1, "Anonim");
		this->salariu = 0;
		this->departament = IT;
	}
	//constr cu toti param
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
	}
	//constr de copiere
	Angajat(const Angajat&a) :id(1000 + (++Angajat::nrAngajati)) {
		if (a.nume != nullptr) {
			this->nume = new char[strlen(a.nume) + 1];
			strcpy_s(this->nume, strlen(a.nume) + 1, a.nume);
		}
		else {
			this->nume = nullptr;
		}
		this->salariu = a.salariu;
		this->departament = a.departament;
	}
	//op =
	Angajat& operator=(const Angajat & a)
	{
		if (this != &a)
		{
			//combinatie intre destructor si constructor de copiere
			if (this->nume != nullptr)
			{
				delete[] this->nume;
				this->nume = nullptr;
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
		}
		return *this;
	}
	//get si set pentru nume
	 const char* getNume(){
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
	//meth afisare
	void afisare()
	{
		cout << "ID" << this->id << endl;
		cout << "Nume" << this->nume << endl;
		cout << "Salariul" << this->salariu << endl;
		cout << "Departament" << this->departament << endl;
	}
	//destructor
	~Angajat() {
		if (this->nume != nullptr)
		{
			delete[] this->nume;
			this->nume = nullptr;
		}
	}
};

int Angajat::nrAngajati = 0;

int main() {

	Angajat a1;
	Angajat a2("Nume", 10000, IT);
	a1.afisare();
	cout << endl;
	a2.afisare();
	Angajat a3(a2);
	a3.afisare();
	cout<<a2.getNume();
	a2.setNume("George");
	a2.afisare();
	a1 = a2;
	a1.afisare();
	a1 = a2 = a3;//apel in cascada
	a1.afisare();
	//a1 += a2 = a3;//apel in compunere
	a1 = a1;//auto asignare
	a1.afisare();
	cout << Angajat::getNrAngajati();
	return 0;
}