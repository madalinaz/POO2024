#include<iostream>
using namespace std;

//o piesa de teatru
//scena are 2 personaje

//interfata este o clasa abstracta care are DOAR meth virtuale pure
//interfata = contract
class IPersonaj {
public:
	virtual void striga() = 0;//meth virtuala pura
	virtual void seEnerveaza() = 0;
	//virtual void enerveaza(IPersonaj* p) = 0;
};

//nu se pot instantia obj de tip interfata/clasa abstracta
void scenetaI(IPersonaj* p1, IPersonaj* p2) {
	cout << "\nSceneta I";
	p1->striga();
	//p1->enerveaza(p2);
	p2->seEnerveaza();
}

class Actor :public IPersonaj {
	string nume;

public:
	Actor(string _nume) {
		this->nume = _nume;
	}

	//implementare concreta a meth virtuale pure din clasa de baza
	void striga() {
		cout << "\nActorul " + this->nume << " striga";
	}

	void seEnerveaza() {
		cout << "\nActorul " + this->nume << " tranteste usa";
	}
};

//clasa abstracta
class Animal :public  IPersonaj {
protected:
	string denumire;

public:
	Animal(string _denumire) {
		this->denumire = _denumire;
	}

	//implementare concreta a meth virtuale pure din clasa de baza
	void seEnerveaza() {
		cout << "\nAnimalul " + this->denumire << " se enerveaza";
	}

	//cealalta meth (striga) ramane meth virtuala pura => clasa Animal inca este clasa abstracta
	
};

//get
//friend
//protected

class Pisica :public Animal {
public:
	Pisica(string _denumire):Animal(_denumire) {

	}
	void striga() {
		cout << "\nPisica " + this->denumire << " miauna";
	}

	void seEnerveaza() {
		cout << "\nPisica " + this->denumire << " zgarie";
	}
};

class Caine :public Animal {
	void striga() {
		cout << "\nCainele " + this->denumire << " latra";
	}
};

int main() {
	Actor a1("Gigel");
	//a1.striga();
	//a1.seEnerveaza();

	Actor* pa2 = new Actor("Costel");

	//apel sceneta cu 2 personaje tip Actor
	scenetaI(&a1, pa2);

	//Animal animal1("Grivei");
	Animal* pAnimal = new Pisica("Oscar");

	IPersonaj* pPersonaj = new Pisica("Oscar");
	scenetaI(pa2, pPersonaj);
	scenetaI(pPersonaj, pa2);
	return 0;
}