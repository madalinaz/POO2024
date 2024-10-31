#include<iostream>
using namespace std;

enum TipJoc {
	ACTIUNE , RPG
};

class JocVideo {
	const int codUnic;
	char* denumire;
	
	int varstaMinima;
	int nrNivele;
	float nrMediuOreJoc;//cat dureaza in medie sa termin jocul
	static int nrJocuri;
	static float medieOreJocuri;//medie in ore daca ma joc toate jocurile

public:
	//constr fara param
	JocVideo() : codUnic(100+JocVideo::nrJocuri){
		this->denumire = new char[strlen("-") + 1];
		strcpy_s(this->denumire, strlen("-") + 1, "-");
		this->varstaMinima = 0;
		this->nrNivele = 0;
		this->nrMediuOreJoc = 0;
		JocVideo::nrJocuri++;
		
	}
	//constr cu toti param
	JocVideo(const char* _denumire, int _varstaMinima, int _nrNivele, float _nrMediuOreJoc):codUnic(100 + JocVideo::nrJocuri) {
		this->denumire = new char[strlen(_denumire)+1];
		strcpy_s(this->denumire, strlen(_denumire) + 1, _denumire);
		this->varstaMinima = _varstaMinima;
		this->nrNivele = _nrNivele;
		this->nrMediuOreJoc = _nrMediuOreJoc;
		JocVideo::nrJocuri++;
	}
	//constr copiere
	JocVideo(const JocVideo& joc) :codUnic(joc.codUnic) {
		this->denumire = new char[strlen(joc.denumire) + 1];
		strcpy_s(this->denumire, strlen(joc.denumire) + 1, joc.denumire);
		this->varstaMinima = joc.varstaMinima;
		this->nrNivele = joc.nrNivele;
		this->nrMediuOreJoc = joc.nrMediuOreJoc;
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
			this->denumire = new char[strlen(joc.denumire) + 1];
			strcpy_s(this->denumire, strlen(joc.denumire) + 1, joc.denumire);
			this->varstaMinima = joc.varstaMinima;
			this->nrNivele = joc.nrNivele;
			this->nrMediuOreJoc = joc.nrMediuOreJoc;
			//JocVideo::nrJocuri++;  NU pt ca nu avem obiecte noi
		}
		return *this;
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
		cout << "\nCod Unic "<< this->codUnic;
		cout << "\nDenumire " << this->denumire;
		cout << "\nVarsta minima " << this->varstaMinima;
		cout << "\nNr nivele " << this->nrNivele;
		cout << "\nNr mediu ore joc " << this->nrMediuOreJoc;
		cout << endl;
	}
	//destructor
	~JocVideo()
	{
		if (this->denumire != nullptr)
		{
			delete[]this->denumire;
			this->denumire = nullptr;
		}
	}

};
int JocVideo::nrJocuri = 0;
float JocVideo::medieOreJocuri = 0;


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
}