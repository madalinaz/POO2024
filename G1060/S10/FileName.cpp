#include<iostream>
using namespace std;

enum Ambalaj {
	CUTIE, HARTIE, GLOB, PLIC
};

ostream& operator<<(ostream& out, Ambalaj a) {
	switch (a)
	{
	case CUTIE:
		out << "Cutie";
		break;
	case HARTIE:
		out << "Hartie";
		break;
	case GLOB:
		out << "Glob";
		break;
	case PLIC:
		out << "Plic";
		break;
	default:
		out << "Lipsa";
		break;
	}
	return out;
}

istream& operator>>(istream& in, Ambalaj& a) {
	int x;
	cin >> x;
	switch (x)
	{
	case 0:
		a = Ambalaj::CUTIE;
		break;
	case 1:
		a = Ambalaj::HARTIE;
		break;
	case 2:
		a = Ambalaj::GLOB;
		break;
	case 3:
		a = Ambalaj::PLIC;
		break;
	default:
		a = Ambalaj::HARTIE;
		break;
	}
	return in;
}

//Cadou has a Ambalaj
class Cadou {
	string denumire = "-";
	float pret = 0;
	Ambalaj ambalaj = Ambalaj::HARTIE;

public:
	Cadou() { }

	Cadou(string _denumire, float _pret, Ambalaj _ambalaj) :denumire(_denumire), pret(_pret), ambalaj(_ambalaj) { }

	Cadou(const Cadou& c) :denumire(c.denumire), pret(c.pret), ambalaj(c.ambalaj) { }

	Cadou& operator=(const Cadou& c) {
		this->denumire = c.denumire;
		this->pret = c.pret;
		this->ambalaj = c.ambalaj;
		return *this;
	}

	friend ostream& operator<<(ostream& out, const Cadou& c) {
		out << "\nDenumire: " << c.denumire;
		out << ", pret: " << c.pret;
		out << ", ambalaj: " << c.ambalaj;
		return out;
	}

	friend istream& operator>>(istream& in, Cadou& c); 
};

istream& operator>>(istream& in, Cadou& c)
{
	cout << "\nIntroduceti denumire: ";
	in >> c.denumire;
	cout << "Introduceti pret: ";
	in >> c.pret;
	cout << "Introduceti ambalaj: ";
	in >> c.ambalaj;
	return in;
}

class WishList {
	string posesor="Anonim";
	int nrCadouri=0;
	Cadou** listaCadouri=nullptr;//vector alocat dinamic de Cadou*

public:
	WishList(){ }

	WishList(string _posesor, int _nrCadouri, Cadou** _listaCadouri) {
		this->posesor = _posesor;
		if (_nrCadouri > 0 && _listaCadouri != nullptr) {
			this->nrCadouri = _nrCadouri;
			this->listaCadouri = new Cadou * [this->nrCadouri];//nici un constructor din Cadou
			for (int i = 0; i < this->nrCadouri; i++)
				this->listaCadouri[i] = new Cadou(*_listaCadouri[i]);//constructor de copiere
		}
	}

	//constructor care primeste doar dimensiune si init pe nullptr fiecare cadou
	WishList(string _posesor, int _nrCadouri) {
		this->posesor = _posesor;
		if (_nrCadouri > 0) {
			this->nrCadouri = _nrCadouri;
			this->listaCadouri = new Cadou * [this->nrCadouri];
			for (int i = 0; i < this->nrCadouri; i++)
				this->listaCadouri[i] = nullptr;
		}
	}

	WishList(const WishList& w) {
		this->posesor = w.posesor;
		if (w.nrCadouri > 0 && w.listaCadouri != nullptr) {
			this->nrCadouri = w.nrCadouri;
			this->listaCadouri = new Cadou * [this->nrCadouri];//nici un constructor din Cadou
			for (int i = 0; i < this->nrCadouri; i++)
				this->listaCadouri[i] = new Cadou(*w.listaCadouri[i]);//constructor de copiere
		}
	}

	WishList& operator=(const WishList& w) {
		if (this != &w) {
			if (this->listaCadouri != nullptr) {
				for (int i = 0; i < this->nrCadouri; i++) {
					delete this->listaCadouri[i];
					this->listaCadouri[i] = nullptr;
				}
				delete[] this->listaCadouri;
				this->listaCadouri = nullptr;
			}
			this->posesor = w.posesor;
			if (w.nrCadouri > 0 && w.listaCadouri != nullptr) {
				this->nrCadouri = w.nrCadouri;
				this->listaCadouri = new Cadou * [this->nrCadouri];//nici un constructor din Cadou
				for (int i = 0; i < this->nrCadouri; i++)
					this->listaCadouri[i] = new Cadou(*w.listaCadouri[i]);//constructor de copiere
			}
			else {
				this->listaCadouri = nullptr;
				this->nrCadouri = 0;
			}
		}
		return *this;
	}

	~WishList() {
		if (this->listaCadouri != nullptr) {
			for (int i = 0; i < this->nrCadouri; i++) {
				delete this->listaCadouri[i];
				this->listaCadouri[i] = nullptr;
			}
			delete[] this->listaCadouri;
			this->listaCadouri = nullptr;
		}
	}

	friend ostream& operator<<(ostream& out, const WishList& w) {
		out << "\nPosesor: " << w.posesor;
		out << "\nNr cadouri: " << w.nrCadouri;
		out << "\nLista cadouri:";
		for (int i = 0; i < w.nrCadouri; i++)
			out << *w.listaCadouri[i];
		return out;
	}
};

int main() {
	Cadou v[10];//vector de obiecte apeleaza constructor fara param din Cadou
	Cadou* v2;
	v2 = new Cadou[10];

	Cadou c1("stilou", 490, CUTIE);
	Cadou c2("carte", 120, HARTIE);
	Cadou c3("inel", 2000, GLOB);
	Cadou c4;
	Cadou* listaNormala[] = { &c1,&c2,&c3 };
	Cadou* listaC[] = { &c1,&(c4 = c2), new Cadou(c2), new Cadou("geanta",1200,CUTIE), new Cadou};
	WishList w1("Gigel", 5, listaC);
	cout << w1;

	delete listaC[2];
	delete listaC[3];
	delete listaC[4];
	return 0;
}