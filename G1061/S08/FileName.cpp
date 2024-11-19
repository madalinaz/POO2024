#include<iostream>
using namespace std;

class Plantatie {
	const int id;
	string adresa;
	int nrPomi;
	int* varsta;
	static int varstaMinimaRod;
	
	//alte atribute la alegere
	//string proprietar;
	//string tipSol;

public:
	Plantatie(int _id):id(_id) {
		this->adresa = "-";
		this->nrPomi = 0;
		this->varsta = nullptr;
	}

	Plantatie(int _id, string _adresa, int _nrPomi, int* _varsta):id(_id) {
		this->adresa = _adresa;
		if (_varsta != nullptr && _nrPomi > 0) {
			this->nrPomi = _nrPomi;
			this->varsta = new int[this->nrPomi];
			for (int i = 0; i < this->nrPomi; i++)
				this->varsta[i] = _varsta[i];
		}
		else {
			this->varsta = nullptr;
			this->nrPomi = 0;
		}
	}

	Plantatie(const Plantatie& p) :id(p.id) {
		this->adresa = p.adresa;
		if (p.varsta != nullptr && p.nrPomi > 0) {
			this->nrPomi = p.nrPomi;
			this->varsta = new int[this->nrPomi];
			for (int i = 0; i < this->nrPomi; i++)
				this->varsta[i] = p.varsta[i];
		}
		else {
			this->varsta = nullptr;
			this->nrPomi = 0;
		}
	}

	Plantatie& operator=(const Plantatie& p) {
		if (this != &p) {
			if (this->varsta != nullptr) {
				delete[] this->varsta;
				this->varsta = nullptr;
			}
			this->adresa = p.adresa;
			if (p.varsta != nullptr && p.nrPomi > 0) {
				this->nrPomi = p.nrPomi;
				this->varsta = new int[this->nrPomi];
				for (int i = 0; i < this->nrPomi; i++)
					this->varsta[i] = p.varsta[i];
			}
			else {
				this->varsta = nullptr;
				this->nrPomi = 0;
			}
		}
		return *this;
	}

	string getAdresa() {
		return this->adresa;
	}

	void setAdresa(string _adresa) {
		if (_adresa.length() >= 5) {
			this->adresa = _adresa;
		}
	}

	void setVarsta(int* _varsta, int _nrPomi) {
		//obj this deja exista
		if (this->varsta != nullptr) {
			delete[] this->varsta;
			this->varsta = nullptr;
		}
		if (_varsta != nullptr && _nrPomi > 0) {
			this->nrPomi = _nrPomi;
			this->varsta = new int[this->nrPomi];
			for (int i = 0; i < this->nrPomi; i++)
				this->varsta[i] = _varsta[i];
		}
		else {
			this->varsta = nullptr;
			this->nrPomi = 0;
		}
	}

	const int* getVarsta1() {
		return this->varsta;
	}

	int* getVarsta2() {
		if (this->varsta != nullptr) {
			int* copie = new int[this->nrPomi];
			for (int i = 0; i < this->nrPomi; i++)
				copie[i] = this->varsta[i];
			return copie;//returnez o adresa care dubleaza valorile din this
		}
		else {
			return nullptr;
		}
	}

	int getNrPomi() {
		return this->nrPomi;
	}

	int getNrPomiVarstaMinima(int pragMinVarsta) {
		int ct = 0;
		for (int i = 0; i < this->nrPomi; i++)
			if (this->varsta[i] >= pragMinVarsta)
				ct++;
		return ct;
	}

	~Plantatie() {
		if (this->varsta != nullptr) {
			delete[] this->varsta;
			this->varsta = nullptr;
		}
	}

	friend ostream& operator<<(ostream& out, const Plantatie& p) {
		out << "\nId: " << p.id;
		out << "\nAdresa: " << p.adresa;
		out << "\nNr pomi: " << p.nrPomi;
		out << "\nVarsta pomi: ";
		for (int i = 0; i < p.nrPomi; i++)
			out << p.varsta[i] << " ";
		return out;
	}
};

int Plantatie::varstaMinimaRod = 3;//minim 3 ani ca pomul sa dea roade

int main() {
	cout << "\n----------Apel constructor cu 1 parametru--------------";
	Plantatie p1(10);
	cout << p1;
	cout << "\n----------Apel metode accesor (get si set)--------------";
	p1.setAdresa("Buzau");
	cout << "\nAdresa de dupa apel set: " << p1.getAdresa();
	int varsta[] = { 4,10,5,5,4,10 };
	p1.setVarsta(varsta, 6);
	cout << "\nNr pomi dupa apel set: " << p1.getNrPomi();
	cout << "\nVector varsta pomi dupa apel set: ";
	for (int i = 0; i < 6; i++)
		cout << p1.getVarsta1()[i] << " ";
	cout << "\n----------Apel constructor cu toti parametri--------------";
	Plantatie p2(15, "Bucuresti", 4, varsta);
	cout << p2;
	{
		Plantatie p3(14);
		//la sf blocului definit de {}, obj p3 se distruge folosind destructorul
	}
	Plantatie* pp = new Plantatie(123);
	delete pp;//apel explicit al destructorului
	cout << "\n----------Apel metoda prelucrare--------------";
	cout << "\nNr total pomi fructiferi peste prag minim este: " << p1.getNrPomiVarstaMinima(6);
	cout << "\n----------Apel constructor de copiere--------------";
	Plantatie p3 = p2;
	cout << p3;
	cout << "\n----------Apel operator =--------------";
	Plantatie p4(1023);
	p4 = p1;
	cout << p4;
	return 0;
}