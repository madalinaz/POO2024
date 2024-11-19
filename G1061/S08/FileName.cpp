#include<iostream>
using namespace std;

class Plantatie {
	const int id;
	string adresa;
	int nrPomi;
	int* varsta;
	static int varstaMinimaRod;
	//char* proprietar;
	//string* vectorStringuri;
	//bool* vectorBooluri;
	
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

	//cast la int explicit
	explicit operator int() {
		int ct = 0;
		for (int i = 0; i < this->nrPomi; i++)
			if (this->varsta[i] >= Plantatie::varstaMinimaRod)
				ct++;
		return ct;
	}

	bool operator==(const Plantatie& p) {
		if (this->id != p.id)
			return false;
		if (this->adresa != p.adresa)
			return false;
		if (this->nrPomi != p.nrPomi)
			return false;
		for (int i = 0; i < this->nrPomi; i++)
			if (this->varsta[i] != p.varsta[i])
				return false;
		return true;
	}

	//operator functie
	Plantatie operator()(int pragMinim) {
		Plantatie rez = *this; //constructor de copiere
		//cati pomi pastrez in rez
		int ct = 0;
		for (int i = 0; i < rez.nrPomi; i++)
			if (rez.varsta[i] >= pragMinim)
				ct++;
		if (rez.varsta != nullptr) {
			delete[] rez.varsta;
			rez.varsta = nullptr;
		}
		if (ct == 0) {
			rez.nrPomi = 0;
			rez.varsta = nullptr;
		}
		else {
			rez.nrPomi = ct;
			rez.varsta = new int[ct];
			//int k = 0;
			for (int i = 0, k=0; i < this->nrPomi; i++) {
				if (this->varsta[i] >= pragMinim) {
					rez.varsta[k++] = this->varsta[i];
				}
			}
		}
		return rez;
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

	static int getVarstaMinimaRod() {
		return Plantatie::varstaMinimaRod;
	}

	static void setVarstaMinimaRod(int _varstaMinimaRod) {
		if (_varstaMinimaRod >= 1) {
			Plantatie::varstaMinimaRod = _varstaMinimaRod;
		}
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

	friend istream& operator>>(istream& in, Plantatie& p) {
		cout << "\nIntroduceti adresa: ";
		in >> p.adresa;
		if (p.varsta != nullptr) {
			delete[] p.varsta;
			p.varsta = nullptr;
		}
		cout << "Introduceti nr pomi: ";
		in >> p.nrPomi;
		if (p.nrPomi <= 0) {
			p.nrPomi = 0;
			p.varsta = nullptr;
		}
		else {
			p.varsta = new int[p.nrPomi];
			cout << "Introduceti varsta pomi: ";
			for (int i = 0; i < p.nrPomi; i++)
				in >> p.varsta[i];
		}
		return in;
	}

	friend Plantatie operator+(int x, const Plantatie& p) {
		Plantatie rez = p;
		if (x > 0) {
			if (rez.varsta != nullptr) {
				delete[] rez.varsta;
				rez.varsta = nullptr;
			}
			rez.varsta = new int[rez.nrPomi + 1];
			for (int i = 0; i < rez.nrPomi; i++)
				rez.varsta[i] = p.varsta[i];
			rez.varsta[rez.nrPomi] = x;
			rez.nrPomi++;
		}
		return rez;
	}
};

int Plantatie::varstaMinimaRod = 6;//minim 3 ani ca pomul sa dea roade

class A {
	int nrLocuri;
	bool* ocupareLoc;

public:
	A(int _nrLocuri, bool* _ocupareLoc) {
		if (_nrLocuri > 0 && _ocupareLoc != nullptr) {
			this->nrLocuri = _nrLocuri;
			this->ocupareLoc = new bool[this->nrLocuri];
			for (int i = 0; i < this->nrLocuri; i++)
				this->ocupareLoc[i] = _ocupareLoc[i];
		}
	}
};

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
	cout << "\n----------Apel operator +--------------";
	p4 = 10 + p4;
	cout << p4;
	cout << "\n----------Apel operator cast la int--------------";
	int nrPomiRod = (int)p4;
	cout << "\nNr pomi cu rod folosind cast la int: " << nrPomiRod;
	cout << "\n----------Apel operator ==--------------";
	Plantatie p5(p4);
	cout << endl<< (p5 == p4);
	cout << "\n----------Apel operator >>-------------";
	//cin >> p5;
	cout << p5;
	cout << "\n----------Apel meth get si set pentru atribut static-------------";
	Plantatie::setVarstaMinimaRod(5);
	cout << "\nVarsta minima rod: " << Plantatie::getVarstaMinimaRod();
	cout << "\n----------Apel operator functie-------------";
	p4 = p5(4);//construieste un obj nou plecand de la p5 elimina din el toti pomii care au varsta sub 4 ani
	Plantatie p6 = p5(5);
	cout << p6;
	cout << "\n----------CLASA A CU BOOL*-------------";
	bool v[] = { true, true,true,false };
	A a(4, v);
	return 0;
}