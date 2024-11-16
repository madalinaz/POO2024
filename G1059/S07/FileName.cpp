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

	//declarand friend, fiind totusi in corpul clasei, functia este globala
	friend ostream& operator<<(ostream& out, const Locuinta& l) {
		out << "\nCod unic: " << l.codUnic;
		out << "\nAdresa: " << l.adresa;
		out << "\nTip: " << l.tip;
		out << "\nSuprafata: " << l.suprafata;
		out << "\nNr dormitoare: " << l.nrDormitoare;
		out << "\nSuprafata dormitoare: ";
		for (int i = 0; i < l.nrDormitoare; i++)
			out << l.suprafataDormitoare[i] << " ";
		return out;
	}

	//VARIATII
	//citire pana cand utilizatorul introduce ce trebuie
	//citiri multiple de siruri de caractere cu spatii
	friend istream& operator>>(istream& in, Locuinta& l) {
		cout << "\nIntroduceti adresa: ";
		if (l.adresa != nullptr) {
			delete[] l.adresa;
			l.adresa = nullptr;
		}
		string buffer;
		in >> buffer;
		l.adresa = new char[buffer.length() + 1];
		strcpy_s(l.adresa, buffer.length() + 1, buffer.data());//meth data returneaza char*-ul din string
		cout << "Introduceti tip locuinta: ";
		int x;
		in >> x;//0 sau 1
		l.tip = (TipLocuinta)x;//cast explicit de la int la TipLocuinta
		cout << "Introduceti suprafata: ";
		in >> l.suprafata;
		if (l.suprafataDormitoare != nullptr) {
			delete[] l.suprafataDormitoare;
			l.suprafataDormitoare = nullptr;
		}
		cout << "Introduceti nr dormitoare: ";
		in >> l.nrDormitoare;
		if (l.nrDormitoare <= 0) {
			l.nrDormitoare = 0;
			l.suprafataDormitoare = nullptr;
		}
		else {
			l.suprafataDormitoare = new float[l.nrDormitoare];
			cout << "Introduceti lista suprafete dormitoare: ";
			for (int i = 0; i < l.nrDormitoare; i++)
				in >> l.suprafataDormitoare[i];
		}
		return in;
	}

	//operator + NU modifica operanzii (adica nici pe this, nici pe x)
	Locuinta operator+(float x) const {
		Locuinta rez = *this;
		rez += x;
		return rez;
	}

	//facem modificari pe this
	Locuinta& operator-=(int nr) {
		Locuinta copie = *this;
		this->nrDormitoare -= nr;
		if (this->nrDormitoare <= 0) {
			this->nrDormitoare = 0;
			delete[] this->suprafataDormitoare;
			this->suprafataDormitoare = nullptr;
		}
		else {
			delete[] this->suprafataDormitoare;
			this->suprafataDormitoare = new float[this->nrDormitoare];
			//copiez in this ce este "bun" din copie
			for (int i = nr, k = 0; i < copie.nrDormitoare; i++, k++)
				this->suprafataDormitoare[k] = copie.suprafataDormitoare[i];
		}
		return *this;
	}

	//pre-incrementare
	Locuinta& operator++() {
		for (int i = 0; i < this->nrDormitoare; i++)
			this->suprafataDormitoare[i]++;
		return *this;//returnez obj de dupa incrementare
	}

	//post-incrementare
	Locuinta operator++(int) {
		Locuinta copie = *this;//salvez starea anterioara incrementarii
		for (int i = 0; i < this->nrDormitoare; i++)
			this->suprafataDormitoare[i]++;
		return copie;//returnez obj de dinainte de incrementare
	}
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
	// << si >>
	cout << l2;
	l2 += 10;
	l2 += 13;
	l2 += 20;
	cout << l2;

	//cin >> l2;
	cout << l2;

	l2 = l2 + 13.3;//adauga un nou dormitor la sfarsitul listei de suprafete
	cout << l2;
	for (int i = 1; i <= 5; i++)
		l2 = l2 + (i + 10);
	cout << l2;
	l2 -= 7;//elimina primele 7 dormitoare sau cate are
	cout << l2;

	l1 = ++l2;//adauga 1 metru patrat la fiecare dormitor din lista suprafete
	l1 = l2++;//adauga 1 metru patrat la fiecare dormitor din lista suprafete
	cout << l1;
	cout << l2;

	return 0;
}