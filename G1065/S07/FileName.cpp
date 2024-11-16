#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

//adaugati un enum in clasa
//supraincarcati op << si >> pentru a gestiona enum

enum TipMancare {
	PIZZA, PASTE, DESERT, BURGER
};

ostream& operator<<(ostream& out, TipMancare t) {
	if (t == TipMancare::PIZZA)
		out << "Pizza";
	else
		out << "Other";
	return out;
}

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

	bool operator!() {
		return this->nrPreturi == 0;
	}

	//forma de pre-incrementare
	FelMancare& operator++() {
		this->pret++;
		return *this;//returnez obj de dupa incrementare
	}

	//forma de post-incrementare
	FelMancare operator++(int) {
		FelMancare copie = *this;//salvez starea anterioara incrementarii
		this->pret++;
		return copie;//returnez starea de dinainte de incrementare
	}


	//operator modifica this-ul???
	//const pus dupa inseamna ca protejam this-ul
	FelMancare operator+(float pretNou) const {
		FelMancare rez = *this;
		//adaug un pretNou
		if (rez.istoricPreturi != nullptr) {
			delete[] rez.istoricPreturi;
			rez.istoricPreturi = nullptr;
		}
		rez.istoricPreturi = new float[rez.nrPreturi + 1];
		for (int i = 0; i < rez.nrPreturi; i++)
			rez.istoricPreturi[i] = this->istoricPreturi[i];
		rez.nrPreturi++;
		rez.istoricPreturi[rez.nrPreturi - 1] = pretNou;
		return rez;
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

	friend ostream& operator<<(ostream& out, const FelMancare& f) {
		out << "\n-----------";
		out << "\nCod: " << f.cod;
		out << "\nDenumire: " << f.denumire;
		out << "\nNr.Calorii: " << f.nrCalorii;
		out << "\nPret: " << f.pret;
		out << "\nNr preturi: " << f.nrPreturi;
		out << " \nIstoric preturi: ";
		for (int i = 0; i < f.nrPreturi; i++) {
			out << f.istoricPreturi[i] << " ";
		}
		out << "\n-----------";
		return out;
	}

	//VARIATIUNI
	//citiri multiple de siruri de caractere cu spatii 
	//se cere reintroducerea unei valori pana ce valoarea este corecta
	//citire de enum

	//transfer prin referinta pe f fara sa il declar const pentru ca il modific
	friend istream& operator>>(istream& in, FelMancare& f) {
		cout << "\nIntroduceti denumire: ";
		if (f.denumire != nullptr) {
			delete[] f.denumire;
			f.denumire = nullptr;
		}
		//char buffer2[50];
		string buffer;
		in >> buffer;
		f.denumire = new char[buffer.size() + 1];
		strcpy_s(f.denumire, buffer.size() + 1, buffer.data());//meth data preia char* dintr-un string
		cout << "Introduceti nr calorii: ";
		in >> f.nrCalorii;
		cout << "Introduceti pret: ";
		in >> f.pret;
		if (f.istoricPreturi != nullptr) {
			delete[] f.istoricPreturi;
			f.istoricPreturi = nullptr;
		}
		cout << "Introduceti dimensiune istoric preturi: ";
		in >> f.nrPreturi;
		if (f.nrPreturi <= 0) {
			f.nrPreturi = 0;
			f.istoricPreturi = nullptr;
		}
		else {
			f.istoricPreturi = new float[f.nrPreturi];
			cout << "Introduceti lista istoric preturi: ";
			for (int i = 0; i < f.nrPreturi; i++)
				in >> f.istoricPreturi[i];
		}
		return in;
	}
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
	cout << f2;//ostream<<FelMancare
	cout << f2 << f1;
	cout.operator<<(5);
	operator<<(cout, f2);
	f2.operator=(f1);
	//cin >> f1;
	cout << f1;

	int x = 2, y = 5;
	if (!x)
		cout << "\nx nu exista//x este 0";
	else
		cout << "\nx exista";
	x = !y;
	//operator ! evalueaza existenta obj nostru

	if (!f2)
		cout << "\nF2 nu are istoric de preturi";
	else
		cout << "\nF2 are un istoric de preturi";

	f1 = ++f2;
	f1 = f2++;

	f1 = f2 + 10;//adaug un nou pret la istoric preturi


	// ! ==(compar dpdv al tuturor campurilor) !=(true daca difera prin cel putin 1)
	// + [] cast ++(pre si post) () 

	TipMancare tipMancare = TipMancare::PIZZA;
	cout << endl << tipMancare;
	return 0;
}