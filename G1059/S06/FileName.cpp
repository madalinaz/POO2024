#include<iostream>
using namespace std;

enum TipLocuinta {
	AP, CASA
};

class Locuinta {
	const int codUnic;
	char* adresa;
	TipLocuinta tip;
	float suprafata;//suprafata totala
	static int nrLocuinte;//contor pt nr obiecte construite
	static float suprafataMinima;
	static float suprafataMaxima;
	int nrDormitoare;
	float* suprafataDormitoare;
	//static float suprafataMedie;
	//variabila se actualizeaza pe parcurs atunci cand se creaza obiecte noi


public:
	//constr fara param
	Locuinta() :codUnic(100 + Locuinta::nrLocuinte++) {
		this->adresa = new char[strlen("-") + 1];
		strcpy_s(this->adresa, strlen("-") + 1, "-");
		this->tip = TipLocuinta::AP;
		this->suprafata = 0;
		this->nrDormitoare = 0;
		this->suprafataDormitoare = nullptr;
	}

	//constr cu aproape toti param
	Locuinta(const char* _adresa, TipLocuinta _tip, float _suprafata) : codUnic(100 + Locuinta::nrLocuinte++)
	{
		this->adresa = new char[strlen(_adresa) + 1];
		strcpy_s(this->adresa, strlen(_adresa) + 1, _adresa);
		this->tip = _tip;
		this->suprafata = _suprafata;
		this->nrDormitoare = 0;
		this->suprafataDormitoare = nullptr;
	}

	//constr de copiere
	Locuinta(const Locuinta& l) : codUnic(100 + Locuinta::nrLocuinte++)
	{
		this->adresa = new char[strlen(l.adresa) + 1];
		strcpy_s(this->adresa, strlen(l.adresa) + 1, l.adresa);
		this->tip = l.tip;
		this->suprafata = l.suprafata;
		if (l.nrDormitoare > 0 && l.suprafataDormitoare != nullptr) {
			this->nrDormitoare = l.nrDormitoare;
			this->suprafataDormitoare = new float[this->nrDormitoare];
			for (int i = 0; i < this->nrDormitoare; i++)
				this->suprafataDormitoare[i] = l.suprafataDormitoare[i];
		}
		else {
			this->nrDormitoare = 0;
			this->suprafataDormitoare = nullptr;
		}
	}

	//op =
	Locuinta& operator=(const Locuinta& l)
	{
		if (this != &l)
		{
			if (this->adresa != nullptr) {
				delete[] this->adresa;
				this->adresa = nullptr;
			}
			if (this->suprafataDormitoare != nullptr) {
				delete[] this->suprafataDormitoare;
				this->suprafataDormitoare = nullptr;
			}
			this->adresa = new char[strlen(l.adresa) + 1];
			strcpy_s(this->adresa, strlen(l.adresa) + 1, l.adresa);
			this->tip = l.tip;
			this->suprafata = l.suprafata;
			if (l.nrDormitoare > 0 && l.suprafataDormitoare != nullptr) {
				this->nrDormitoare = l.nrDormitoare;
				this->suprafataDormitoare = new float[this->nrDormitoare];
				for (int i = 0; i < this->nrDormitoare; i++)
					this->suprafataDormitoare[i] = l.suprafataDormitoare[i];
			}
			else {
				this->nrDormitoare = 0;
				this->suprafataDormitoare = nullptr;
			}
		}
		return *this;
	}

	Locuinta& operator+=(float x) {
		if (x > 0) {
			Locuinta copie = *this;
			if (this->suprafataDormitoare != nullptr) {
				delete[] this->suprafataDormitoare;
				this->suprafataDormitoare = nullptr;
			}
			this->suprafataDormitoare = new float[this->nrDormitoare + 1];
			for (int i = 0; i < copie.nrDormitoare; i++)
				this->suprafataDormitoare[i] = copie.suprafataDormitoare[i];
			this->suprafataDormitoare[this->nrDormitoare] = x;
			this->nrDormitoare++;
		}
		return *this;
	}

	bool operator>(float x) {
		return this->suprafata > x;
	}

	Locuinta operator+(float x) {
		Locuinta rez = *this;
		rez.suprafata += x;
		return rez;
	}

	// get si set pentru adresa
	const char* getAdresa() {
		return this->adresa;
	}

	void setAdresa(const char* _adresa)
	{
		if (this->adresa != nullptr) {
			delete[] this->adresa;
			this->adresa = nullptr;
		}
		this->adresa = new char[strlen(_adresa) + 1];
		strcpy_s(this->adresa, strlen(_adresa) + 1, _adresa);
	}

	// get pentru membrii statici
	static int getNrLocuinte() {
		return Locuinta::nrLocuinte;
	}

	static float getSuprafataMinima() {
		return Locuinta::suprafataMinima;
	}

	static void setSuprafataMinima(float _suprafata) {
		if (_suprafata > 0 && _suprafata < Locuinta::suprafataMaxima) {
			Locuinta::suprafataMinima = _suprafata;
		}
	}

	// meth afisare
	void afisare() {
		cout << "\nCod unic: " << this->codUnic;
		cout << "\nAdresa: " << this->adresa;
		cout << "\nTip: " << this->tip;
		cout << "\nSuprafata: " << this->suprafata;
		cout << "\nNr dormitoare: " << this->nrDormitoare;
		cout << "\nSuprafata dormitoare: ";
		for (int i = 0; i < this->nrDormitoare; i++)
			cout << this->suprafataDormitoare[i] << " ";
	}

	//destructor
	~Locuinta()
	{
		if (this->adresa != nullptr) {
			delete[] this->adresa;
			this->adresa = nullptr;
		}
		if (this->suprafataDormitoare != nullptr) {
			delete[] this->suprafataDormitoare;
			this->suprafataDormitoare = nullptr;
		}
	}

	//friend bool operator>=(float x, Locuinta l);
};

int Locuinta::nrLocuinte = 0;
float Locuinta::suprafataMinima = 50;
float Locuinta::suprafataMaxima = 300;

//bool operator>=(float x, Locuinta l) {
//	return x >= l.suprafata;
//}

bool operator>=(float x, Locuinta l) {
	return !(l > x);
}

int main() {

	Locuinta l1;
	Locuinta l2("Bucuresti", TipLocuinta::AP, 122);
	l1.afisare();
	l2.afisare();
	cout << endl << l2.getAdresa();
	l2.setAdresa("Ilfov");
	l2.afisare();
	Locuinta l3(l1);
	l3.afisare();
	cout << endl << "S-au creat : " << Locuinta::getNrLocuinte();
	Locuinta::setSuprafataMinima(60);
	cout << endl << Locuinta::getSuprafataMinima();
	l1 = l2;
	l1.operator=(l2);
	l1.afisare();

	l1 += 20;//adauga un nou dormitor de suprafata primita ca param
	l1.operator+=(20);//meth a clasei
	//operator+=(l1, 20);//fct globala
	l1.afisare();

	//l1 -= 2;//elimina ultimele 2 dormitoare; SAU elimina cele mai mari 2 dormitoare
	//l1 += 2;//adauga 2 dormitoare noi de suprafata egala cu ultimul dormitor existent

	if (l1 > 100)
		cout << "\nL1 are cel putin 100 metri patrati suprafata";
	else
		cout << "\nInvers";

	if (200 >= l1)
		cout << "\nL1 are maxim 200 metri patrati";
	else
		cout << "\nInvers";

	l2 = l1 + 10; //construim un nou obj plecand de la l1 si marind suprafata cu 10
	l2.afisare();
	//float suprafataActualizata = l1 - 10.0f;
	/*
	p1.identif tip operator (unar/binar sau aritmetic/logic)
	p2.identif tip operanzi
	p3.daca primul operand este de tipul clasei, atunci se poate implementa
	printr-o metoda a clasei (primul operand este "inghitit" de this). altfel, obligatoriu printr-o fct globala (toti opezantii sunt trimisi ca parametru)
	p4. !!!! ce returneaza operatorul????
	p5. !!! ce operanzi se modifica???
	*/
	return 0;
}