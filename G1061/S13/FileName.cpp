#include<iostream>
using namespace std;

//cheltuieli (angajati->salarii ; productie/exploatare)
//interfata/clasa de baza (ICheltuiala)
//clasa abstracta este derivata din interfata
//clasa concreta derivata din interfata 
//2 clase concrete derivate din clasa abstracta (Laptop)
//clasa care se afla in relatie de has a

//clasa este de tip interfata -> clasa care are DOAR meth virtuale pure
//interfata = contract
class ICheltuiala {
public:
	virtual float getCostLunar() = 0;
};

//clasa abstracta
//mosteneste meth virtuala pura din clasa sa de baza
//nu vine cu implementare concreta pentru acea meth => ramane meth virtuala pura
//clasa abstracta = clasa cu cel putin o meth virtuala pura
class Echipament : public ICheltuiala {
	string tipEchipament;
	string denumire;

public:
	Echipament(string _tipEchipament, string _denumire) {
		this->tipEchipament = _tipEchipament;
		this->denumire = _denumire;
	}
};

//clasa concreta derivata din clasa abstracta
class Laptop:public Echipament {
	float pretAchizitie;
	int nrLuniAmortizare;

public:
	Laptop(string _denumire,
		float _pretAchizitie, int _nrLuniAmortizare):Echipament("laptop", _denumire) {
		this->pretAchizitie = _pretAchizitie;
		this->nrLuniAmortizare = _nrLuniAmortizare;
	}

	float getCostLunar() {
		return this->pretAchizitie / this->nrLuniAmortizare;
	}
};

//clasa concreta derivata din interfata
class Angajat :public ICheltuiala {
	string nume;
	float salariu;

public:
	Angajat(string _nume, float _salariu) {
		this->nume = _nume;
		this->salariu = _salariu;
	}
	float getCostLunar() {
		return this->salariu;
	}

};

//clasa Companie
//modalitate de a calcula totalul cheltuielilor luna pe care le are compania
//vector static/dinamic de ICheltuiala*
class Companie {
	int nrCheltuieli;
	ICheltuiala** listaCheltuieli;

public:
	Companie(int _nrCheltuieli, ICheltuiala** _listaCheltuieli) {
		this->nrCheltuieli = _nrCheltuieli;
		this->listaCheltuieli = new ICheltuiala*[this->nrCheltuieli];
		for (int i = 0; i < this->nrCheltuieli; i++)
			this->listaCheltuieli[i] = _listaCheltuieli[i];
	}

	~Companie() {
		delete[] this->listaCheltuieli;
		this->listaCheltuieli = nullptr;
	}

	float getTotalCheltuieli() {
		float total = 0;
		for (int i = 0; i < this->nrCheltuieli; i++)
			total += this->listaCheltuieli[i]->getCostLunar();
		return total;
	}
};

int main() {
	//interfata
	//ICheltuiala ch;
	ICheltuiala* pCh;
	//clasa abstracta
	//Echipament e;
	//Echipament* pe = new Echipament("laptop", "laptop Lenovo");
	Echipament* pe;
	//clasa concreta derivata din clasa abtracta
	Laptop laptop("laptop Lenovo", 2400, 24);
	Echipament* echipament = new Laptop("laptop Dell", 4800, 24);
	echipament = &laptop;

	ICheltuiala* lista[] = { echipament, &laptop, new Angajat("Gigel",4000) };
	Companie c(3, lista);
	cout << endl << "Total cheltuieli: " << c.getTotalCheltuieli();
	return 0;
}