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
	float* istoricPreturi;
	int nrPreturi;

public:

	//constructor fara param
	FelMancare() :cod(1000 + FelMancare::nrFeluriMancare++)
	{
		this->denumire = new char[strlen("anonim") + 1];
		strcpy(this->denumire, "anonim");
		this->nrCalorii = 0;
		this->pret = 0;
		this->istoricPreturi = nullptr;
		this->nrPreturi = 0;
	}



	//constructor cu aproape toti param
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
		this->istoricPreturi = nullptr;
		this->nrPreturi = 0;
	}



	//ce nu se protejeaza la nivel de obiect f, chiar daca fac declar constant
	//prin referinta se protejeaza doar sizeof(obiect), adica doar zona stack, nu si 
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
		if (f.nrPreturi > 0 && f.istoricPreturi != nullptr) {
			this->nrPreturi = f.nrPreturi;
			this->istoricPreturi = new float[this->nrPreturi];
			for (int i = 0; i < this->nrPreturi; i++)
				this->istoricPreturi[i] = f.istoricPreturi[i];
		}
		else {
			this->istoricPreturi = nullptr;
			this->nrPreturi = 0;
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
		cout << "\nNr preturi: " << this->nrPreturi;
		cout << " \nIstoric preturi: ";
		for (int i = 0; i < this->nrPreturi; i++) {
			cout << this->istoricPreturi[i] << " ";
		}
		cout << "\n-----------";
	}

	//operator=
	FelMancare& operator=(const FelMancare& f) {
		if (this != &f) {
			//obiectul this deja exista 
			//destructor + constructor de copiere
			if (this->denumire != nullptr) {
				delete[] this->denumire;
				this->denumire = nullptr;
			}
			if (this->istoricPreturi != nullptr) {
				delete[] this->istoricPreturi;
				this->istoricPreturi = nullptr;
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
			if (f.nrPreturi > 0 && f.istoricPreturi != nullptr) {
				this->nrPreturi = f.nrPreturi;
				this->istoricPreturi = new float[this->nrPreturi];
				for (int i = 0; i < this->nrPreturi; i++)
					this->istoricPreturi[i] = f.istoricPreturi[i];
			}
			else {
				this->istoricPreturi = nullptr;
				this->nrPreturi = 0;
			}
		}
		return *this;
	}

	FelMancare& operator+=(float x) {
		if (x > 0) {
			this->pret += x;
			//ar trebui adaugata sectiune de actualizare vector istoricPreturi
		}
		return *this;
	}

	bool operator>=(int x) {
		return this->nrPreturi >= x;
	}

	bool operator==(const FelMancare& f) {
		if (this->nrCalorii != f.nrCalorii)
			return false;
		if (strcmp(this->denumire, f.denumire) != 0)
			return false;
		//.....to add all
		return true;
	}

	bool operator!=(const FelMancare& f) {
		return !(this->operator==(f));
		//return !(*this == f); //SAU
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

	void setDenumire2();

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
		if (this->istoricPreturi != nullptr) {
			delete[] this->istoricPreturi;
			this->istoricPreturi = nullptr;
		}
	}

	friend bool operator<(float x, FelMancare f);
	friend FelMancare& operator+=(FelMancare& f, float x);
};
int FelMancare::nrFeluriMancare = 0;
float FelMancare::pretMinim = 20;

bool operator<(float x, FelMancare f) {
	return x < f.pret;
}

void FelMancare::setDenumire2() {
	//bla bla bla
	cout << "\nMeth care NU este inline";
}

bool operator<=(int x, FelMancare f) {
	return f >= x;
}

FelMancare& operator+=(FelMancare& f, float x) {
	if (x > 0)
		f.pret += x;
	return f;
}

int main() {
	FelMancare f1;
	FelMancare f2("Pizza", 1450, 40);
	f1.afisare();
	f2.afisare();

	FelMancare::setPretMinim(30);
	cout << endl << FelMancare::getPretMinim();

	FelMancare f3(f2);
	f3.afisare();

	f3.setDenumire("Tiramisu");
	cout << endl << f3.getDenumire();

	f1 = f3 = f2;
	f1.operator=(f3);
	f1.afisare();

	f1 = f1;
	f1.afisare();
	/*
	P1. se indentifica tipul operatorului(binar/unar) (aritmetic/logic...)
	P2. se identifica tipul operanzilor
	P3. daca primul operand este de tipul clasei, atunci se recomanda supraincarcare prin
	metoda a clasei (this-ul "inghite" primul operand); daca nu, atunci obligatoriu
	se implementeaza printr-o functie globala
	P4. !!! returneaza ceva operatorul?
	P5. !!! se modifica vreun operand?
	*/
	//f1 += 10;
	f1.operator+=(10);
	operator+=(f1, 10);
	f1.afisare();

	operator<(100.0f, f1);
	if (100.0f < f1)
		cout << "\nF1 are un pret > ca 100";
	else
		cout << "\nInvers";

	if (2 <= f1)
		cout << "\nF1 are mai mult de 2 preturi in istoric";
	else
		cout << "\nInvers";

	// ! ==(compar dpdv al tuturor campurilor) !=(true daca difera prin cel putin 1)
	// + [] cast ++(pre si post) () 
	return 0;
}