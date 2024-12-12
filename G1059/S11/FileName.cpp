#include<iostream>
using namespace std;

class Cadou {
	string denumire = "-";
	float pret = 0;

public:
	Cadou() { }

	Cadou(string _denumire, float _pret) :denumire(_denumire), pret(_pret) { }

	Cadou(const Cadou& c) :denumire(c.denumire), pret(c.pret) { }

	Cadou& operator=(const Cadou& c) {
		this->denumire = c.denumire;
		this->pret = c.pret;
		return *this;
	}

	friend ostream& operator<<(ostream& out, const Cadou& c) {
		out << "\nDenumire: " << c.denumire;
		out << ", pret: " << c.pret;
		return out;
	}

	friend istream& operator>>(istream& in, Cadou& c) {
		cout << "\nIntroduceti denumire: ";
		in >> c.denumire;
		cout << "Introduceti pret: ";
		in >> c.pret;
		return in;
	}

	float getPret() {
		//to do
	}
};

//Box is a Cadou
//Box has a lista de Cadou

//daca se achizitioneaza un Box format din alte Cadouri
//atunci se aplica o reducere de 10% pe total
class Box: public Cadou {
	//enumeratie culoare 
	int nrCadouri;
	Cadou* listaCadouri;
	string textFelicitare;

public:
	float getPret() {
		// se aplica o reducere de 10% pe totalul preturilor
	}

	//constructor fara param
	
	//constructor cu toti fara vector + dimensiune
	//constructor copiere
	//op=
	//destructor
	//ostream
	//set si get pe vector + dimensiune
};

int main() {
	return 0;
}