#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class FelMancare {
	const int cod;
	char* denumire;
	int nrCalorii;
	float pret;
	static int nrFeluriMancare;
	static float pretMinim;

public:
	//constructor fara param
	FelMancare():cod(1000+ FelMancare::nrFeluriMancare++)
	{
		this->denumire = new char[strlen("anonim") + 1];
		strcpy(this->denumire, "anonim");
		this->nrCalorii = 0;
		this->pret = 0;
	}
	//constructor cu toti param
	FelMancare(const char* _denumire, int _nrCalorii, float _pret) :cod(1000 + FelMancare::nrFeluriMancare++)
	{
		this->denumire = new char[strlen(_denumire) + 1];
		strcpy(this->denumire, _denumire);
		this->nrCalorii = _nrCalorii;
		this->pret = _pret;
		if (_pret < FelMancare::pretMinim)
		{
			this->pret = FelMancare::pretMinim;
		}
		else
		{
			this->pret = _pret;
		}
	}
	//ce nu se protejeaza la nivel de obiect f, chiar daca fac declar constant
	//prin referinta se protejeaza doar sizeof(obiect), adica doar zona stack, nu si heap
	//constructor de copiere
	
	FelMancare(const FelMancare& f) :cod(1000 + FelMancare::nrFeluriMancare++) {
		this->denumire = new char[strlen(f.denumire) + 1];
		strcpy(this->denumire, f.denumire);
		this->nrCalorii = f.nrCalorii;
		//memorie heap: f.denumire[0] = 'M';
		this->pret = f.pret;
		if (f.pret < FelMancare::pretMinim)
		{
			this->pret = FelMancare::pretMinim;
		}
		else
		{
			this->pret = f.pret;
		}
	}

	//meth afisare
	void afisare()
	{
		cout << "\n-----------";
		cout << "\nCod: " << this->cod;
		cout << "\nDenumire: " << this->denumire;
		cout << "\nNr.Calorii: " << this->nrCalorii;
		cout << "\nPret: " << this->pret;
		cout << "\n-----------";
	}
	//operator=
	FelMancare& operator=(const FelMancare& f) {
		//obiectul this deja exista 
		//destructor + constructor de copiere
		if (this->denumire != nullptr) {
			delete[] this->denumire;
			this->denumire = nullptr;
		}
		this->denumire = new char[strlen(f.denumire) + 1];
		strcpy(this->denumire, f.denumire);
		this->nrCalorii = f.nrCalorii;
		//memorie heap: f.denumire[0] = 'M';
		this->pret = f.pret;
		if (f.pret < FelMancare::pretMinim)
		{
			this->pret = FelMancare::pretMinim;
		}
		else
		{
			this->pret = f.pret;
		}
		return *this;
	}
	//get si set pentru denumire
	const char* getDenumire() {
		return this->denumire;
	}
	void setDenumire(const char* _denumire) {
		if (this->denumire != nullptr) {
			delete[] this->denumire;
			this->denumire = nullptr;
		}
		this->denumire = new char[strlen(_denumire) + 1];
		strcpy(this->denumire, _denumire);
		
	}
	//metode statice pentru afisare atribute statice
	static float getPretMinim() {
		return FelMancare::pretMinim;
	}

	static void setPretMinim(const float _pretMinim) {
		if (_pretMinim > 0) {
			FelMancare::pretMinim = _pretMinim;
		}
	}

	//destructor
	~FelMancare() {
		if (this->denumire != nullptr) {
			delete[] this->denumire;
			this->denumire = nullptr;
		}
	}
};
int FelMancare::nrFeluriMancare = 0;
float FelMancare::pretMinim = 20;

int main() {
	FelMancare f1;
	FelMancare f2("Pizza", 1450, 40);
	f1.afisare();
	f2.afisare();

	FelMancare::setPretMinim(30);
	cout<< endl << FelMancare::getPretMinim();

	FelMancare f3(f2);
	f3.afisare();

	f3.setDenumire("Tiramisu");
	cout << endl << f3.getDenumire();

	f1 = f3 = f2;
	f1.operator=(f3);
	f1.afisare();
	return 0;
}