#include<iostream>

using namespace std;

class Salariat {
	const int id;
	char* nume;
	static int nrSalariati;
	//static float salariuMediu;
	static float salariuMinim;//din legislatie
	float salariu;
	int nrOreZi;

public:
	//const fara param
	Salariat():id(0) {
		cout <<endl<< "Apel cosntructor fara param";
		this->nume = new char[strlen("-")+1];
		strcpy_s(this->nume,2, "-");
		this->salariu = 0;
		this->nrOreZi = 0;
		Salariat::nrSalariati++;
	}
	//constr cu toti param
	Salariat(int _id,const char* _nume, float _salariu, int _nrOreZi):id(_id)
	{
		cout << "\nApel constructor cu toti param";
		this->nume = new char[strlen(_nume) + 1];
		strcpy_s(this->nume, strlen(_nume) + 1, _nume);
		if (_salariu >= Salariat::salariuMinim)
			this->salariu = _salariu;
		else
			this->salariu = Salariat::salariuMinim;
		if (_nrOreZi > 8)
			this->nrOreZi = 8;
		else if (_nrOreZi < 1)
			this->nrOreZi = 1;
		else
			this->nrOreZi = _nrOreZi;
		Salariat::nrSalariati++;
	}
	//constr copiere
	Salariat(const Salariat& s):id(s.id) {
		cout << "\nApel constructor de copiere";
		this->nume = new char[strlen(s.nume) + 1];
		strcpy_s(this->nume, strlen(s.nume) + 1, s.nume);
		if (s.salariu >= Salariat::salariuMinim)
			this->salariu = s.salariu;
		else
			this->salariu = Salariat::salariuMinim;
		if (s.nrOreZi > 8)
			this->nrOreZi = 8;
		else if (s.nrOreZi < 1)
			this->nrOreZi = 1;
		else
			this->nrOreZi = s.nrOreZi;
		Salariat::nrSalariati++;
	}
	//operator=
	Salariat& operator=(const Salariat& s) {
		cout << "\nApel operator =";
		if (this != &s) {
			if (this->nume != nullptr) {
				delete[] this->nume;
				this->nume = nullptr;
			}
			this->nume = new char[strlen(s.nume) + 1];
			strcpy_s(this->nume, strlen(s.nume) + 1, s.nume);
			if (s.salariu >= Salariat::salariuMinim)
				this->salariu = s.salariu;
			else
				this->salariu = Salariat::salariuMinim;
			if (s.nrOreZi > 8)
				this->nrOreZi = 8;
			else if (s.nrOreZi < 1)
				this->nrOreZi = 1;
			else
				this->nrOreZi = s.nrOreZi;
		
		}
		return *this;
	}
	//meth afisare;
	void afisare() {
		cout << "\n-----------------";
		cout << "\n id:" << this->id;
		cout << "\n nume:" << this->nume;
		cout << "\n salariu:" << this->salariu;
		cout << "\n numar ore:" << this->nrOreZi;
	}
	
	//destructor
	~Salariat() {
		cout << "\nAPELARE DESTRUCTOR";
		if (this->nume != nullptr) {
			delete[] this->nume;
			this->nume = nullptr;
		}
	}
	//set salariu
	void setSalariu(float _salariu)
	{
		if (_salariu >= Salariat::salariuMinim)
			this->salariu = _salariu;
		else
			this->salariu = Salariat::salariuMinim;
	}
	//get salariu
	float getSalariu()
	{
		return this->salariu;
	}


	//set nume
	void setNume(const char* _nume) {
		//OBIECTUL THIS DEJA EXISTA
		//POSIBIL EXISTENTA NUME DEJA
		if (this->nume != nullptr) {
			delete[] this->nume;
			this->nume = nullptr;
		}
		this->nume = new char[strlen(_nume) + 1];
		strcpy_s(this->nume, strlen(_nume) + 1, _nume);
	}
	//get nume
	const char* getNume() {
		return this->nume;
	}
	
	
};

int Salariat::nrSalariati = 0;
float Salariat::salariuMinim = 2500;

Salariat getSalariatMaxSalariu(Salariat v[], int nr) {
	//to do home
	return Salariat();
}


int main() {
	Salariat s1;
	Salariat s2(123, "Ionescu", 2600, 6);
	s1.afisare();
	s2.afisare();
	Salariat s3(s2);
	s3.afisare();
	s2.setNume("Gigel");
	s2.afisare();
	cout << "\nTEST: " << s2.getNume();
	s2.setSalariu(5000);
	s2.afisare();
	cout << "\nTest: " << s2.getSalariu();
	s1 = s2;
	s1.afisare();
	return 0;
}