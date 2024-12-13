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
		return this->pret;
		//to do
	}

protected:
	void setPret(float _pret) {
		this->pret = _pret;
	}
};

//Box is a Cadou
//Box has a lista de Cadou

//daca se achizitioneaza un Box format din alte Cadouri
//atunci se aplica o reducere de 10% pe total
enum Culoare {
	NA, ROSU, GALBEN, NEGRU, GRI
};

class Box : public Cadou {
	Culoare culoare;
	int nrCadouri;
	Cadou* listaCadouri;
	string textFelicitare;

public:

	//constructor fara param
	Box() :Cadou() {
		this->culoare = Culoare::NA;
		this->nrCadouri = 0;
		this->listaCadouri = nullptr;
		this->textFelicitare = "-";
	}
	//constructor cu toti fara vector + dimensiune
	Box(Culoare _culoare, string _textFelicitare, string _denumire) :Cadou(_denumire, 0) {
		this->culoare = _culoare;
		this->textFelicitare = _textFelicitare;
		this->nrCadouri = 0;
		this->listaCadouri = nullptr;
	}

	//constructor copiere
	Box(const Box& b) :Cadou(b) {
		this->culoare = b.culoare;
		this->textFelicitare = b.textFelicitare;
		if (b.nrCadouri > 0 && b.listaCadouri != nullptr) {
			this->nrCadouri = b.nrCadouri;
			delete[]this->listaCadouri;
			this->listaCadouri = new Cadou[this->nrCadouri];
			for (int i = 0; i < this->nrCadouri; i++)
				this->listaCadouri[i] = b.listaCadouri[i];
		}
		else {
			this->nrCadouri = 0;
			this->listaCadouri = nullptr;
		}
	}
	//op=
	Box operator=(const Box& b) {
		if (this != &b) {
			Cadou::operator=(b);
			if (this->listaCadouri != nullptr) {
				delete[]this->listaCadouri;
				this->listaCadouri = nullptr;
			}
			this->culoare = b.culoare;
			this->textFelicitare = b.textFelicitare;
			if (b.nrCadouri > 0 && b.listaCadouri != nullptr) {
				this->nrCadouri = b.nrCadouri;
				delete[]this->listaCadouri;
				this->listaCadouri = new Cadou[this->nrCadouri];
				for (int i = 0; i < this->nrCadouri; i++)
					this->listaCadouri[i] = b.listaCadouri[i];
			}
			else {
				this->nrCadouri = 0;
				this->listaCadouri = nullptr;
			}

		}
		return *this;
	}
	//destructor
	~Box() {
		if (this->listaCadouri != nullptr) {
			delete[]this->listaCadouri;
			this->listaCadouri = nullptr;
		}
	}
	//ostream
	friend ostream& operator<<(ostream& out, const Box& b) {
		out << (Cadou)b;
		out << "\nCuloarea: " << b.culoare;
		out << "\nText Felicitare: " << b.textFelicitare;
		out << "\nNumar cadouri: " << b.nrCadouri;
		out << "\nLista Cadouri: ";
		for (int i = 0; i < b.nrCadouri; i++) {
			out << b.listaCadouri[i] << " ";
		}
		return out;
	}
	//set si get pe vector + dimensiune
	Cadou* getLista() {
		return this->listaCadouri;
	}

	void setLista(int _nrCadouri, Cadou* _listaCadouri) {
		int totalPret = 0;
		if (_nrCadouri > 0 && _listaCadouri != nullptr) {
			delete[]this->listaCadouri;
			this->nrCadouri = _nrCadouri;
			this->listaCadouri = new Cadou[this->nrCadouri];
			for (int i = 0; i < this->nrCadouri; i++) {
				this->listaCadouri[i] = _listaCadouri[i];
				totalPret += this->listaCadouri[i].getPret();
			}
		}
		totalPret *= 0.9;
		this->setPret(totalPret);
	}
	//op + care adauga un nou Cadou in vector
};

int main() {
	Cadou c1("Jucarie", 120);
	Cadou c2("Joc", 30);
	Cadou c3("Puzzle", 60);
	Cadou lista[] = { c1,c2,c3 };
	Box b1(Culoare::ROSU, "Felicitari", "Box Magic");
	cout << b1;
	b1.setLista(3, lista);
	cout << endl << b1;
	cout << b1.getPret();
	return 0;
}