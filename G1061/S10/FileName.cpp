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

	friend istream& operator>>(istream& in, Cadou& c) {
		cout << "\nIntroduceti denumire: ";
		in >> c.denumire;
		cout << "Introduceti pret: ";
		in >> c.pret;
		cout << "Introduceti ambalaj: ";
		in >> c.ambalaj;
		return in;
	}
};

//relatia has a/compunere intre WishList si Cadou
class WishList {
	string posesor="Anonim";
	Cadou** listaCadouri=nullptr;//vector dinamic de Cadou*
	int nrCadouri=0;
	float buget=0;
	static int nrCadouriInGlob;

public:
	WishList() {
	}

	WishList(string _posesor, Cadou** _listaCadouri, int _nrCadouri, float _buget) {
		this->posesor = _posesor;
		this->buget = _buget;
		if (_listaCadouri != nullptr && _nrCadouri > 0) {
			//implementarea este "total deep"
			this->nrCadouri = _nrCadouri;
			this->listaCadouri = new Cadou * [this->nrCadouri];
			for (int i = 0; i < this->nrCadouri; i++) {
				//this->listaCadouri[i] = _listaCadouri[i];
				
				//this->listaCadouri[i] = new Cadou();
				//*this->listaCadouri[i] = *_listaCadouri[i];

				this->listaCadouri[i] = new Cadou(*_listaCadouri[i]);
			}
		}
	}

	WishList(const WishList& w) {
		this->posesor = w.posesor;
		this->buget = w.buget;
		if (w.listaCadouri != nullptr && w.nrCadouri > 0) {
			this->nrCadouri = w.nrCadouri;
			this->listaCadouri = new Cadou * [this->nrCadouri];
			for (int i = 0; i < this->nrCadouri; i++) {
				this->listaCadouri[i] = new Cadou(*w.listaCadouri[i]);
			}
		}
	}

	WishList& operator=(const WishList& w) {
		if (this != &w) {
			if (this->listaCadouri != nullptr) {
				for (int i = 0; i < this->nrCadouri; i++)
					delete this->listaCadouri[i];
				delete[] this->listaCadouri;
				this->listaCadouri = nullptr;
			}
			this->posesor = w.posesor;
			this->buget = w.buget;
			if (w.listaCadouri != nullptr && w.nrCadouri > 0) {
				this->nrCadouri = w.nrCadouri;
				this->listaCadouri = new Cadou * [this->nrCadouri];
				for (int i = 0; i < this->nrCadouri; i++) {
					this->listaCadouri[i] = new Cadou(*w.listaCadouri[i]);
				}
			}
			else {
				this->nrCadouri = 0;
				this->listaCadouri = nullptr;
			}
		}
		return *this;
	}

	~WishList() {
		if (this->listaCadouri != nullptr) {
			for (int i = 0; i < this->nrCadouri; i++)
				delete this->listaCadouri[i];
			delete[] this->listaCadouri;
			this->listaCadouri = nullptr;
		}
	}

	friend ostream& operator<<(ostream& out, const WishList& w) {
		out << "\n------------------";
		out << "\nPosesor: " << w.posesor;
		out << "\nBuget: " << w.buget;
		out << "\nNr cadouri: " << w.nrCadouri;
		out << "\nLista cadouri: ";
		for (int i = 0; i < w.nrCadouri; i++)
			out << *w.listaCadouri[i];
		return out;
	}
};

int WishList::nrCadouriInGlob = 0;

int main() {
	return 0;
}