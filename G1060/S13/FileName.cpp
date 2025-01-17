#include<iostream>
using namespace std;

class Animal {
public:
	virtual void spune() {
		cout << "\nSunt animal!";
	}
};

class Caine : public Animal {
public:
	void spune() override {
		cout << "\nSunt catel, ham, ham!";
	}

};

class Pisica : public Animal {
public:
	void spune() {
		cout << "\nSunt pisica, miau, miau!";
	}
};

//interfata unei clase ->meth accesor (get si set)

//clasa tip Interfata
//clasa care are doar meth virtuale pure
//interfata = contract
//interfata - caz particular din clasa abstracta
class ICheltuiala {
public:
	virtual void getInfo() = 0;//meth virtuala pura
	virtual float getCostLunar() = 0;
};

//clasa abstracta -> are cel putin o meth virtuala pura
class ACheltuiala : public ICheltuiala {
protected:
	string denumire;
	string dataContract;

public:
	ACheltuiala(string _denumire, string _dataContract) {
		this->denumire = _denumire;
		this->dataContract = _dataContract;
	}
};

//clasa concreta din clasa abstracta
class CheltuialaEchipament :public ACheltuiala {
	float pretAchizitie;
	int nrLuniAmortizare;

public:
	CheltuialaEchipament(string _denumire, string _dataContract, float _pretAchizitie, int _nrLuniAmortiszare) :ACheltuiala(_denumire, _dataContract) {
		this->pretAchizitie = _pretAchizitie;
		this->nrLuniAmortizare = _nrLuniAmortiszare;
	}

	void getInfo() {
		cout << "\nCheltuiala: " << this->denumire << ", pret achizitie: " << this->pretAchizitie;
	}

	float getCostLunar() {
		return this->pretAchizitie / this->nrLuniAmortizare;
	}
};

class CheltuialaFurnizor :public ACheltuiala {
	float costLunar;

public:
	CheltuialaFurnizor(string _denumire, string _dataContract, float _costLunar) :ACheltuiala(_denumire, _dataContract) {
		this->costLunar = _costLunar;
	}

	void getInfo() {
		cout << "\nCheltuiala: " << this->denumire << ", cost lunar: " << this->costLunar;
	}

	float getCostLunar() {
		return this->costLunar;
	}
};

class Angajat : public ICheltuiala {
	string nume;
	float salariu;

public:
	Angajat(string _nume, float _salariu) {
		this->nume = _nume;
		this->salariu = _salariu;
	}

	void getInfo() {
		cout << "\nAngajat: " << this->nume;
	}

	float getCostLunar() {
		return this->salariu;
	}
};

//colectie de cheltuieli
//class WishList???

class Companie {
	int nrCheltuieli;
	ICheltuiala** listaCheltuiala;

public:
	Companie(int _nrCheltuieli, ICheltuiala** _listaCheltuiala) {
		this->nrCheltuieli = _nrCheltuieli;
		//this->listaCheltuiala = _listaCheltuiala; shallow all the way

		this->listaCheltuiala = new ICheltuiala * [this->nrCheltuieli];
		for (int i = 0; i < this->nrCheltuieli; i++)
			this->listaCheltuiala[i] = _listaCheltuiala[i];//shallow copy
	}
};

int main() {
	cout << "\n-----------ZOO-------------";
	Animal animal;
	Pisica pisica;
	Caine caine;
	animal.spune();
	pisica.spune();
	caine.spune();

	//"retine ce a fost candva"
	animal = pisica;//upcast pe obiecte
	animal.spune();

	Animal* pAnimal = &animal;
	Pisica* pPisica = &pisica;
	Caine* pCaine = &caine;
	pAnimal = pPisica;//upcast pe pointeri
	pAnimal->spune();

	cout << "\n-----------ZOO-------------";
	int x(2);
	int x2 = 2;
	//clasa tip Interfata
	//ICheltuiala obj;
	ICheltuiala* pObj = nullptr;
	//pObj->getInfo();

	//clasa abstracta
	//ACheltuiala obj("contract apa", "12/12/2020");
	//ACheltuiala* pObj2 = new ACheltuiala("contract apa", "12/12/2020");
	//
	CheltuialaEchipament chEp("laptop", "12/12/2000", 4800, 24);
	chEp.getInfo();
	ACheltuiala* pCh = new CheltuialaEchipament("laptop", "12/12/2000", 4800, 24);//upcast pe pointeri

	CheltuialaFurnizor chFz("apa", "20/12/2020", 250);
	chFz.getInfo();
	return 0;
}