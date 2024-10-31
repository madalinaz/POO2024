#include<iostream>
using namespace std;

enum TipLocuinta {
	AP, CASA
};

class Locuinta {
	const int codUnic;
	char* adresa;
	TipLocuinta tip;
	float suprafata;
	static int nrLocuinte;//contor pt nr obiecte construite
	static float suprafataMinima;
	static float suprafataMaxima;
	//static float suprafataMedie;
	//variabila se actualizeaza pe parcurs atunci cand se creaza obiecte noi


public:
	//constr fara param
	Locuinta() :codUnic(100+Locuinta::nrLocuinte++){
		this->adresa = new char[strlen("-") + 1];
		strcpy_s(this->adresa,strlen( "-")+1,"-");
		this->tip = TipLocuinta::AP;
		this->suprafata = 0;



	}
	//constr cu toti param
	Locuinta(const char* _adresa, TipLocuinta _tip, float _suprafata) : codUnic(100 + Locuinta::nrLocuinte++) 
	{
		this->adresa = new char[strlen(_adresa) + 1];
		strcpy_s(this->adresa, strlen(_adresa) + 1, _adresa);
		this->tip = _tip;
		this->suprafata = _suprafata;
	}
	//constr de copiere
	Locuinta(const Locuinta& l) : codUnic(100 + Locuinta::nrLocuinte++)
	{
		this->adresa = new char[strlen(l.adresa) + 1];
		strcpy_s(this->adresa, strlen(l.adresa) + 1, l.adresa);
		this->tip = l.tip;
		this->suprafata = l.suprafata;
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
			this->adresa = new char[strlen(l.adresa) + 1];
			strcpy_s(this->adresa, strlen(l.adresa) + 1, l.adresa);
			this->tip = l.tip;
			this->suprafata = l.suprafata;
		}
		return *this;
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
	}
	//destructor
	~Locuinta()
	{
		if (this->adresa != nullptr) {
			delete[] this->adresa;
			this->adresa = nullptr;
		}
	}
};

int Locuinta::nrLocuinte = 0;
float Locuinta::suprafataMinima = 50;
float Locuinta::suprafataMaxima = 300;


int main() {

	Locuinta l1;
	Locuinta l2("Bucuresti", TipLocuinta::AP, 122);
	l1.afisare();
	l2.afisare();
	cout << endl<<l2.getAdresa();
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
	return 0;
}