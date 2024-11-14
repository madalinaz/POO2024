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

	FelMancare operator+(float pretNou) {
		FelMancare rez 
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

	//variatii
	//nu fac si citirea vectorului
	//de avut grija la citiri multiple de siruri de caractere cu spatii
	//se cere reintroducere pana la introducere valoare corecta

	//transferul prin referinta pentru f nu se declara constant
	//dorim sa facem modificari la nivelul obj f
	friend istream& operator>>(istream& in, FelMancare& f) {
		cout << "\nIntroduceti denumire: ";
		string buffer;
		//char buffer2[50];
		in >> buffer;
		if (f.denumire != nullptr) {
			delete[] f.denumire;
			f.denumire = nullptr;
		}
		f.denumire = new char[buffer.size() + 1];
		strcpy_s(f.denumire, buffer.size() + 1, buffer.data());//data() extrage char* din string
		cout << "Introduceti nr calorii: ";
		in >> f.nrCalorii;
		cout << "Introduceti pretul: ";
		in >> f.pret;
		if (f.istoricPreturi != nullptr) {
			delete[] f.istoricPreturi;
			f.istoricPreturi = nullptr;
		}
		cout << "Introduceti dimensiune istoric preturi: ";
		in >> f.nrPreturi;
		if (f.nrPreturi > 0) {
			f.istoricPreturi = new float[f.nrPreturi];
			for (int i = 0; i < f.nrPreturi; i++)
				in >> f.istoricPreturi[i];
		}
		else {
			f.nrPreturi = 0;
			f.istoricPreturi = nullptr;
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
	cout << f2;//cout este un obiect de tip ostream
	cout << f2 << f1;
	cin >> f1;
	cout << f1;
	f1 = f2 + 120;//adaug in istoric preturi un pret nou de 120 ( la sfarsit)
	//f1 = 120 + f2;//adaug la istoric preturi la inceput un nou pret de 120.
	/*
	<< si >>
	+
	-=
	++ (pre si post)
	*/

	
	/*
	P1. se indentifica tipul operatorului(binar/unar) (aritmetic/logic...)
	P2. se identifica tipul operanzilor
	P3. daca primul operand este de tipul clasei, atunci se recomanda supraincarcare prin
	metoda a clasei (this-ul "inghite" primul operand); daca nu, atunci obligatoriu
	se implementeaza printr-o functie globala
	P4. !!! returneaza ceva operatorul?
	P5. !!! se modifica vreun operand?
	*/
	
	return 0;
}