#include<iostream>
using namespace std;

//c++ 11 (c14)
//namespace, headers (c14)
//virtualizare->late binding (c12)
// clasa abstracta + interfata (c12)
//clase template + stl-uri (c13)

class Animal {
public:
	string denumire;
	string rasa;
	int varsta;

	virtual void scoateSunet() {
		cout << "\nAnimalul: " + this->denumire + " scoate sunet";
	}
};

class Pisica : public Animal {
public:
	void scoateSunet() {
		cout << "\nPisica: " + this->denumire + " face miau miau";
	}
};

class Caine : public Animal {
public:
	void scoateSunet() {
		cout << "\nCainele: " + this->denumire + " face ham ham";
	}
};

//o colectie de animale
class ColectieAnimale {
	Animal listaAnimale[10];
	int nrAnimale;

public:
	ColectieAnimale(Animal* _listaAnimale, int _nrAnimale) {
		this->nrAnimale = _nrAnimale;
		for (int i = 0; i < this->nrAnimale; i++)
			this->listaAnimale[i] = _listaAnimale[i];
	}

	void activareAlarma() {
		for (int i = 0; i < this->nrAnimale; i++) {
			this->listaAnimale[i].scoateSunet();
		}
	}
};



class Angajat {
public:
	float salariu = 0;

	virtual float calculSalariu() {
		return this->salariu;
	}
};

class Manager : public Angajat {
public:
	int nrMembriEchipa = 0;

	float calculSalariu() {
		return Angajat::calculSalariu() + 100 * this->nrMembriEchipa;
	}
};

//clasa abstract
//rol de contract -> interfata(are doar meth virtuale pure)
class Entitate {
public:
	virtual void enerveaza() = 0;//meth virtuala pura
	virtual void reactioneaza() = 0;
};

class ActorFemeie : public Entitate {
public:
	void enerveaza() {
		cout << "\nActorul femeie zgarie";
	}

	void reactioneaza() {
		cout << "\nActorul femeie tipa";
	}
};

class Robot :public Entitate {
public:
	void enerveaza() {
		cout << "\nRobotul piuie incontinuu";
	}

	void reactioneaza() {
		cout << "\nRobotul loveste";
	}
};

class Actor :public Entitate {
	void enerveaza() {
		cout << "\nActorul ridica tonul";
	}

	void reactioneaza() {
		cout << "\nActorul plange";
	}
};

void scena1_Generalizata(Entitate* e1, Entitate* e2) {
	e1->enerveaza();
	e2->reactioneaza();
}


class Personaj {
public:
	string nume;
	void enerveaza() {
		cout << "\n" << this->nume << " enerveaza";
	}

	void reactioneaza() {
		cout << "\n" << this->nume << " reactioneaza";
	}
};

//piesa de teatru
//scena1
//2 personaje
//implementare care depinde de concret
void scena1(Personaj p1, Personaj p2) {
	p1.enerveaza();
	p2.reactioneaza();
}

//implementare care depinde de abstract


int main() {
	Entitate* e1 = new Actor();
	Entitate* e2 = new Robot();
	scena1_Generalizata(e1, e2);
	scena1_Generalizata(e2, e2);
	cout << "\n\n---------------------------";
	Personaj pp1;
	Personaj pp2;
	pp1.nume = "Gigel";
	pp2.nume = "Costel";
	scena1(pp1, pp2);
	cout << "\n\n---------------------------";
	Angajat ang1;
	ang1.salariu = 1000;
	Manager m1;
	m1.salariu = 1000;
	m1.nrMembriEchipa = 5;
	cout << "\nSalariu angajat: " << ang1.calculSalariu();
	cout << "\nSalariu manager: " << m1.calculSalariu();
	ang1 = m1;//virtualizarea NU se aplica la obiecte
	//ptr ca op= din upcast elimina surplusul clasei derivate
	cout << "\nSalariu angajat (fost manager): " << ang1.calculSalariu();
	Angajat* pang1;
	pang1 = &m1;
	cout << "\nSalariu pointer angajat (fost manager): " << pang1->calculSalariu();

	cout << "\n\n---------------------------";
	Animal a1;
	a1.denumire = "Animal";
	//a1.scoateSunet();
	Pisica p1;
	p1.denumire = "PisPis";
	//p1.scoateSunet();
	Caine c1;
	c1.denumire = "Grivei";
	//c1.scoateSunet();
	a1 = p1;//upcast pe obiecte
	a1.scoateSunet();
	Animal* pa = new Animal();
	pa->scoateSunet();
	pa = &p1;//upcast pe pointeri
	pa->scoateSunet();

	Animal vector[] = { a1,p1,c1 };
	ColectieAnimale colectie1(vector, 3);
	//colectie1.activareAlarma();
	return 0;
}