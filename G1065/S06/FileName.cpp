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
	int nrBonusuri;
	float* listaBonusuri;

public:
	//const fara param
	Salariat() :id(0) {
		cout << endl << "Apel cosntructor fara param";
		this->nume = new char[strlen("-") + 1];
		strcpy_s(this->nume, 2, "-");
		this->salariu = 0;
		this->nrOreZi = 0;
		this->nrBonusuri = 0;
		this->listaBonusuri = nullptr;
		Salariat::nrSalariati++;
	}
	//constr cu aproape toti param
	Salariat(int _id, const char* _nume, float _salariu, int _nrOreZi) :id(_id)
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
		this->nrBonusuri = 0;
		this->listaBonusuri = nullptr;
		Salariat::nrSalariati++;
	}
	//constr copiere
	Salariat(const Salariat& s) :id(s.id) {
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
		if (this->nrBonusuri > 0 && this->listaBonusuri != nullptr) {
			this->nrBonusuri = s.nrBonusuri;
			this->listaBonusuri = new float[this->nrBonusuri];
			for (int i = 0; i < this->nrBonusuri; i++)
				this->listaBonusuri[i] = s.listaBonusuri[i];
		}
		else {
			this->nrBonusuri = 0;
			this->listaBonusuri = nullptr;
		}
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
			if (this->listaBonusuri != nullptr) {
				delete[] this->listaBonusuri;
				this->listaBonusuri = nullptr;
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
			if (this->nrBonusuri > 0 && this->listaBonusuri != nullptr) {
				this->nrBonusuri = s.nrBonusuri;
				this->listaBonusuri = new float[this->nrBonusuri];
				for (int i = 0; i < this->nrBonusuri; i++)
					this->listaBonusuri[i] = s.listaBonusuri[i];
			}
			else {
				this->nrBonusuri = 0;
				this->listaBonusuri = nullptr;
			}
		}
		return *this;
	}

	bool operator>(Salariat s) {
		return this->getSalariuTotal() > s.getSalariuTotal();
	}

	bool operator==(const Salariat& s) {
		if (strcmp(this->nume, s.nume) != 0)
			return false;
		if (this->salariu != s.salariu)
			return false;
		if (this->nrOreZi != s.nrOreZi)
			return false;
		if (this->nrBonusuri != s.nrBonusuri)
			return false;
		for (int i = 0; i < this->nrBonusuri; i++)
			if (this->listaBonusuri[i] != s.listaBonusuri[i])
				return false;
		return true;
	}

	Salariat& operator+=(float x) {
		if (x > 0) {
			Salariat copie = *this;
			if (this->listaBonusuri != nullptr) {
				delete[] this->listaBonusuri;
				this->listaBonusuri = nullptr;
			}
			this->nrBonusuri++;
			this->listaBonusuri = new float[this->nrBonusuri];
			for (int i = 0; i < copie.nrBonusuri; i++)
				this->listaBonusuri[i] = copie.listaBonusuri[i];
			this->listaBonusuri[this->nrBonusuri - 1] = x;
		}
		else {
			cout << "\nBonus negativ. Nu se poate adauga";
		}
		return *this;
	}

	//meth de prelucrare
	float getSalariuTotal() {
		float salariuT = this->salariu;
		for (int i = 0; i < this->nrBonusuri; i++)
			salariuT += this->listaBonusuri[i];
		return salariuT;
	}

	//meth afisare;
	void afisare() {
		cout << "\n-----------------";
		cout << "\nid: " << this->id;
		cout << "\nnume: " << this->nume;
		cout << "\nsalariu: " << this->salariu;
		cout << "\nnumar ore: " << this->nrOreZi;
		cout << "\nnr bonusuri: " << this->nrBonusuri;
		cout << "\nLista bonusuri: ";
		for (int i = 0; i < this->nrBonusuri; i++)
			cout << this->listaBonusuri[i] << " ";
	}

	//destructor
	~Salariat() {
		cout << "\nAPELARE DESTRUCTOR";
		if (this->nume != nullptr) {
			delete[] this->nume;
			this->nume = nullptr;
		}
		if (this->listaBonusuri != nullptr) {
			delete[] this->listaBonusuri;
			this->listaBonusuri = nullptr;
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

	friend Salariat& operator+=(Salariat& s, float x);
};

int Salariat::nrSalariati = 0;
float Salariat::salariuMinim = 2500;

Salariat getSalariatMaxSalariu(Salariat v[], int nr) {
	//to do home
	return Salariat();
}

bool operator>(int x, Salariat s) {
	return x > s.getSalariu();
}

//implementare operator += printr-o functie globala
Salariat& operator+=(Salariat& s, float x) {
	if (x > 0) {
		Salariat copie = s;
		if (s.listaBonusuri != nullptr) {
			delete[] s.listaBonusuri;
			s.listaBonusuri = nullptr;
		}
		s.nrBonusuri++;
		s.listaBonusuri = new float[s.nrBonusuri];
		for (int i = 0; i < copie.nrBonusuri; i++)
			s.listaBonusuri[i] = copie.listaBonusuri[i];
		s.listaBonusuri[s.nrBonusuri - 1] = x;
	}
	else {
		cout << "\nBonus negativ. Nu se poate adauga";
	}
	return s;
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

	if (s1 > s2)
		cout << "\nSalariatul s1 are un salariu total > ca s2";
	else
		cout << "\nInvers";

	if (s1 == s2)
		cout << "\nObj identice exceptand codul";
	else
		cout << "\nInvers";

	if (1000 > s2)
		cout << "\nS2 are un salariu <1000";
	else
		cout << "\nInvers";

	operator+=(s2, 100); //forma explicita op += implementat prin fct globala
	s2.afisare();
	return 0;
}