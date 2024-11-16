#include<iostream>
using namespace std;

//(HOME + NEXT TIME) DE REAMINTIT NEXT TIME EXEMPLU DE CITIRE ENUMERATIE IN ISTREAM

enum TipJoc {
	ACTIUNE, RPG
};

class JocVideo {
	const int codUnic;
	char* denumire;

	int varstaMinima;
	int nrNivele;
	float nrMediuOreJoc;//cat dureaza in medie sa termin jocul
	static int nrJocuri;
	static float medieOreJocuri;//medie in ore daca ma joc toate jocurile
	float* costPersonaje;
	int nrPersonaje;

public:
	//constr fara param
	JocVideo() : codUnic(100 + JocVideo::nrJocuri) {
		this->denumire = new char[strlen("-") + 1];
		strcpy_s(this->denumire, strlen("-") + 1, "-");
		this->varstaMinima = 0;
		this->nrNivele = 0;
		this->nrMediuOreJoc = 0;
		this->costPersonaje = nullptr;
		this->nrPersonaje = 0;
		JocVideo::nrJocuri++;

	}

	//constr cu aproape toti param
	JocVideo(const char* _denumire, int _varstaMinima, int _nrNivele, float _nrMediuOreJoc) :codUnic(100 + JocVideo::nrJocuri) {
		this->denumire = new char[strlen(_denumire) + 1];
		strcpy_s(this->denumire, strlen(_denumire) + 1, _denumire);
		this->varstaMinima = _varstaMinima;
		this->nrNivele = _nrNivele;
		this->nrMediuOreJoc = _nrMediuOreJoc;
		this->costPersonaje = nullptr;
		this->nrPersonaje = 0;
		JocVideo::nrJocuri++;
	}

	//constr copiere
	JocVideo(const JocVideo& joc) :codUnic(joc.codUnic) {
		this->denumire = new char[strlen(joc.denumire) + 1];
		strcpy_s(this->denumire, strlen(joc.denumire) + 1, joc.denumire);
		this->varstaMinima = joc.varstaMinima;
		this->nrNivele = joc.nrNivele;
		this->nrMediuOreJoc = joc.nrMediuOreJoc;
		this->nrPersonaje = joc.nrPersonaje;
		if (joc.nrPersonaje > 0 && joc.costPersonaje != nullptr) {
			this->costPersonaje = new float[this->nrPersonaje];
			for (int i = 0; i < this->nrPersonaje; i++)
				this->costPersonaje[i] = joc.costPersonaje[i];
		}
		else {
			this->costPersonaje = nullptr;
			this->nrPersonaje = 0;
		}
		JocVideo::nrJocuri++;
	}

	// op=
	JocVideo& operator=(const JocVideo& joc)// combinatie intre destr cu constr de copiere
	{
		if (this != &joc) {
			if (this->denumire != nullptr)
			{
				delete[]this->denumire;
				this->denumire = nullptr;
			}
			if (this->costPersonaje != nullptr) {
				delete[] this->costPersonaje;
				this->costPersonaje = nullptr;
			}
			this->denumire = new char[strlen(joc.denumire) + 1];
			strcpy_s(this->denumire, strlen(joc.denumire) + 1, joc.denumire);
			this->varstaMinima = joc.varstaMinima;
			this->nrNivele = joc.nrNivele;
			this->nrMediuOreJoc = joc.nrMediuOreJoc;
			if (joc.nrPersonaje > 0 && joc.costPersonaje != nullptr) {
				this->nrPersonaje = joc.nrPersonaje;
				this->costPersonaje = new float[this->nrPersonaje];
				for (int i = 0; i < this->nrPersonaje; i++)
					this->costPersonaje[i] = joc.costPersonaje[i];
			}
			else {
				this->costPersonaje = nullptr;
				this->nrPersonaje = 0;
			}
			//JocVideo::nrJocuri++;  NU pt ca nu avem obiecte noi
		}
		return *this;
	}

	JocVideo& operator+=(float x) {
		if (x > 0) {
			this->nrMediuOreJoc += x;
		}
		return *this;
	}

	bool operator>(float x) {
		return this->nrMediuOreJoc >= x;
	}

	//supraincarcare cu redimensionare de vector alocat dinamic
	JocVideo operator+(float x) {
		//!!!!!nu lucram pe this
		JocVideo rez = *this;
		if (rez.costPersonaje != nullptr) {
			delete[] rez.costPersonaje;
			rez.costPersonaje = nullptr;
		}
		rez.costPersonaje = new float[rez.nrPersonaje + 1];
		for (int i = 0; i < rez.nrPersonaje; i++)
			rez.costPersonaje[i] = this->costPersonaje[i];
		rez.nrPersonaje++;
		rez.costPersonaje[rez.nrPersonaje - 1] = x;
		return rez;
	}

	float operator+(const JocVideo& j) {
		return this->nrMediuOreJoc + j.nrMediuOreJoc;
	}

	// get si set pentru zona statica
	static int getNrJocuri() {
		return JocVideo::nrJocuri;
	}
	// get si set pentru denumire
	const char* getDenumire() {
		return this->denumire;
	}

	void setDenumire(const char* _denumire) {
		if (this->denumire != nullptr)
		{
			delete[]this->denumire;
			this->denumire = nullptr;
		}
		this->denumire = new char[strlen(_denumire) + 1];
		strcpy_s(this->denumire, strlen(_denumire) + 1, _denumire);
	}

	// meth afisare
	void afisare() {
		cout << "\n----------------------";
		cout << "\nCod Unic " << this->codUnic;
		cout << "\nDenumire " << this->denumire;
		cout << "\nVarsta minima " << this->varstaMinima;
		cout << "\nNr nivele " << this->nrNivele;
		cout << "\nNr mediu ore joc " << this->nrMediuOreJoc;
		cout << "\nNr personaje: " << this->nrPersonaje;
		cout << "\nCost personaje: ";
		for (int i = 0; i < this->nrPersonaje; i++)
			cout << this->costPersonaje[i] << " ";
		cout << "\n----------------------";
	}

	//destructor
	~JocVideo()
	{
		if (this->denumire != nullptr)
		{
			delete[]this->denumire;
			this->denumire = nullptr;
		}
		if (this->costPersonaje != nullptr) {
			delete[] this->costPersonaje;
			this->costPersonaje = nullptr;
		}
	}

	//friend bool operator<(float x, JocVideo j);

	friend ostream& operator<<(ostream& out, const JocVideo& j) {
		out << "\n----------------------";
		out << "\nCod Unic " << j.codUnic;
		out << "\nDenumire " << j.denumire;
		out << "\nVarsta minima " << j.varstaMinima;
		out << "\nNr nivele " << j.nrNivele;
		out << "\nNr mediu ore joc " << j.nrMediuOreJoc;
		out << "\nNr personaje: " << j.nrPersonaje;
		out << "\nCost personaje: ";
		for (int i = 0; i < j.nrPersonaje; i++)
			out << j.costPersonaje[i] << " ";
		out << "\n----------------------";
		return out;
	}

	friend istream& operator>>(istream& in, JocVideo& j) {
		cout << "\nIntroduceti denumire: ";
		//pentru no memory leaks
		if (j.denumire != nullptr)
		{
			delete[]j.denumire;
			j.denumire = nullptr;
		}
		string buffer;
		//char buffer2[50];
		in >> buffer;
		//buffer.length();
		j.denumire = new char[buffer.length() + 1];
		strcpy_s(j.denumire, buffer.length() + 1, buffer.data());
		//data() extrage doar char*-ul din string (echivalent cu un getter)
		cout << "Introduceti varsta minima: ";
		in >> j.varstaMinima;
		cout << "Introduceti nr nivele: ";
		in >> j.nrNivele;
		cout << "Introduceti nr mediu ore joc: ";
		in >> j.nrMediuOreJoc;

		if (j.costPersonaje != nullptr) {
			delete[] j.costPersonaje;
			j.costPersonaje = nullptr;
		}
		cout << "Introduceti nr personaje: ";
		in >> j.nrPersonaje;
		if (j.nrPersonaje <= 0) {
			j.nrPersonaje = 0;
			j.costPersonaje = nullptr;
		}
		else {
			j.costPersonaje = new float[j.nrPersonaje];
			cout << "Introduceti lista costuri personaje: ";
			for (int i = 0; i < j.nrPersonaje; i++)
				in >> j.costPersonaje[i];
		}
		return in;
	}

	JocVideo& operator-=(int x) {
		JocVideo copie = *this;
		this->nrPersonaje -= x;
		if (this->nrPersonaje <= 0) {
			if (this->costPersonaje != nullptr) {
				delete[] this->costPersonaje;
				this->costPersonaje = nullptr;
			}
			this->nrPersonaje = 0;
		}
		else {
			this->costPersonaje = new float[this->nrPersonaje];
			for (int i = 0; i < this->nrPersonaje; i++)
				this->costPersonaje[i] = copie.costPersonaje[i];
		}
		return *this;
	}

	//pre-incrementare
	JocVideo& operator++() {
		if (this->nrPersonaje > 0) {
			*this = *this + this->costPersonaje[this->nrPersonaje - 1];
		}
		return *this;//intoarce starea obj de dupa incrementare
	}

	//post-incrementare
	JocVideo operator++(int) {
		JocVideo copie = *this;
		if (this->nrPersonaje > 0) {
			/*float* nouCostPersonaje = new float[this->nrPersonaje + 1];
			for (int i = 0; i < this->nrPersonaje; i++) {
				nouCostPersonaje[i] = this->costPersonaje[i];
			}
			nouCostPersonaje[this->nrPersonaje] = this->costPersonaje[this->nrPersonaje - 1];
			delete[] this->costPersonaje;
			this->costPersonaje = nouCostPersonaje;
			this->nrPersonaje++;*/

			delete[] this->costPersonaje;
			this->costPersonaje = new float[this->nrPersonaje + 1];
			for (int i = 0; i < copie.nrPersonaje; i++)
				this->costPersonaje[i] = copie.costPersonaje[i];
			this->nrPersonaje++;
			this->costPersonaje[this->nrPersonaje - 1] = this->costPersonaje[this->nrPersonaje - 2];
		}
		return copie;//se returneaza starea de dinainte de incrementare
	}

	bool operator!=(const JocVideo& j) {
		if (strcmp(this->denumire, j.denumire) != 0)
			return true;
		if (this->varstaMinima != j.varstaMinima)
			return true;
		if (this->nrNivele != j.nrNivele)
			return true;
		if (this->nrPersonaje != j.nrPersonaje)
			return true;
		for (int i = 0; i < this->nrPersonaje; i++)
			if (this->costPersonaje[i] != j.costPersonaje[i])
				return true;
		return false;
	}
};

int JocVideo::nrJocuri = 0;
float JocVideo::medieOreJocuri = 0;

bool operator<(float x, JocVideo j) {
	//return x < j.nrMediuOreJoc;
	return j > x;
}


int main() {

	JocVideo joc;
	JocVideo joc2("GTA", 15, 10, 20);
	// << si >>
	cout << joc2;
	//cin >> joc2;
	cout << joc2;

	joc2 = joc2 + 150;
	joc2 = joc2 + 110;
	cout << joc2;
	for (int i = 0; i < 5; i++)
		joc2 = joc2 + (100 + i * 10);
	cout << joc2;

	joc2 -= 5;//elimina ultimele 5 costuri ale personajelor
	cout << joc2;

	//reutilizand op+ (daca se doreste), sa se supraincarce op++
	//care dubleaza ca aparitii ultimul cost de personaj
	joc = joc2++;
	joc = ++joc2;
	cout << joc;
	cout << joc2;

	if (joc != joc2)
		cout << "\nObj comparate sunt diferite prin cel putin un atribut (exceptand cod)";
	else
		cout << "\nObj identice";

	/*
	index[]
	functie()
	cast
	*/
	return 0;
}