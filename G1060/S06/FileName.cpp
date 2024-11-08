#include<iostream>
using namespace std;

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
	joc.afisare();
	joc2.afisare();
	joc.setDenumire("SIMS");
	JocVideo joc3(joc2);
	joc3.afisare();
	cout << endl << joc.getDenumire();
	cout << endl << JocVideo::getNrJocuri();
	cout << endl << joc2.getNrJocuri();//se recomanda sa nu facem asta
	joc = joc2;
	joc.operator=(joc2);
	joc.afisare();

	int x, y, z;
	x = y = z = 2;//apel in cascada

	joc = joc2 = joc3;
	joc.operator=(joc2.operator=(joc3));

	joc = joc;//auto-asignare

	joc += 1.5f;//actualizam durata medie cu 1.5
	joc.operator+=(1.5f);//forma apelului unui op supraincarcat printr-o metoda a clasei
	//operator+=(joc, 1.5f);
	joc.afisare();

	if (joc > 10)
		cout << "\nDureaza mai mult de 10 ore sa termin jocul joc";
	else
		cout << "\nInvers";

	if (20 < joc)
		cout << "\nDureaza mai mult de 20 ore sa termin jocul joc";
	else
		cout << "\nInvers";

	joc.afisare();
	joc2 = joc + 120.0f;//construim un nou joc plecand de la variabila joc si adaugand un personaj care costa 120.0f
	joc2.afisare();
	joc.afisare();

	float durataTotala = joc + joc2;
	/*
	p1.se identifica tipul de operator (binar/unar; aritmetic/logic...)
	p2.identif tipul de operanzi
	p3.daca primul operand este de tipul clasei, atunci se poate implementa printr-o metoda in clasa (primul operand este "inghitit" de this). in caz contrar, obligatoriu se implementeaza printr-o functie globala (atunci toti operanzii se trimit ca param)
	p4. !!!! ce returneaza operatorul???
	p5. !!! ce operanzi se modifica????
	*/


	return 0;
}