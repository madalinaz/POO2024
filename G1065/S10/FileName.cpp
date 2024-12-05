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

//evidentiere concept compunere
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

class WishList {
	string posesor="Anonim";
	int nrCadouri=0;
	Cadou** listaCadouri=nullptr;//vector alocat dinamic de pointeri de Cadou

public:
	WishList(){ }

	WishList(string _posesor, int _nrCadouri, Cadou** _listaCadouri) {
		this->posesor = _posesor;
		if (_nrCadouri > 0 && _listaCadouri != nullptr) {
			this->nrCadouri = _nrCadouri;
			this->listaCadouri = new Cadou * [this->nrCadouri];//NU se apeleaza niciun constructor din Cadou
			for (int i = 0; i < this->nrCadouri; i++)
				this->listaCadouri[i] = new Cadou(*_listaCadouri[i]);//apel constructor copiere din Cadou
		}
	}

	WishList(const WishList& w) {
		this->posesor = w.posesor;
		if (w.nrCadouri > 0 && w.listaCadouri != nullptr) {
			this->nrCadouri = w.nrCadouri;
			this->listaCadouri = new Cadou * [this->nrCadouri];//NU se apeleaza niciun constructor din Cadou
			for (int i = 0; i < this->nrCadouri; i++)
				this->listaCadouri[i] = new Cadou(*w.listaCadouri[i]);//apel constructor copiere din Cadou
		}
	}

	WishList& operator=(const WishList& w) {
		if (this != &w) {
			if (this->listaCadouri != nullptr) {
				for (int i = 0; i < this->nrCadouri; i++) {
					delete this->listaCadouri[i];//apel destructor din Cadou
					this->listaCadouri[i] = nullptr;
				}
				delete[] this->listaCadouri;
				this->listaCadouri = nullptr;
			}
			this->posesor = w.posesor;
			if (w.nrCadouri > 0 && w.listaCadouri != nullptr) {
				this->nrCadouri = w.nrCadouri;
				this->listaCadouri = new Cadou * [this->nrCadouri];//NU se apeleaza niciun constructor din Cadou
				for (int i = 0; i < this->nrCadouri; i++)
					this->listaCadouri[i] = new Cadou(*w.listaCadouri[i]);//apel constructor copiere din Cadou
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
				delete this->listaCadouri[i];//apel destructor din Cadou
				this->listaCadouri[i] = nullptr;
			}
			delete[] this->listaCadouri;
			this->listaCadouri = nullptr;
		}
	}

	friend ostream& operator<<(ostream& out, const WishList& w) {
		out << "\nPosesor: " << w.posesor;
		out << "\nNr cadouri: " << w.nrCadouri;
		out << "\nLista cadouri: ";
		for (int i = 0; i < w.nrCadouri; i++)
			out << *w.listaCadouri[i];
		return out;
	}
};

class WishList2 {
	string posesor;
	int nrCadouri;
	Cadou* listaCadouri[100];//vector static de Cadou*
};

class WishList3 {
	string posesor;
	int nrCadouri;
	Cadou* listaCadouri;//vector dinamic de Cadou
};

class WishList4 {
	string posesor;
	int nrCadouri;
	Cadou listaCadouri[100];//vector static de Cadou
};

class WishList5 {
	string posesor;
	Cadou* cadouSpecial;//pointer la un Cadou
};

class WishList6 {
	string posesor;
	Cadou cadouSpecial;//un obj de tip Cadou
};

class WishList7 {
	string posesor;
	int nrPrieteni;
	int* nrCadouri;
	Cadou*** listaCadouri;//
};

class WishList8 {
	string posesor;
	int nrPrieteni;
	int* nrCadouri;
	Cadou** listaCadouri[24];
};

int main() {
	Cadou c1("stilou", 450, CUTIE);
	Cadou c2("carte", 100, HARTIE);
	Cadou c3("geanta", 1200, CUTIE);

	Cadou* lista[] = { &c1,&c2,&c3, new Cadou("inel",2000,GLOB) };//refer obj Cadou si de pe stiva si de pe heap
	cout << *lista[3];

	WishList w1("Gigel", 4, lista);
	cout << w1;

	delete lista[3];

	//sa se modeleze relatia has a intre WishList si 
	// Cadou astfel incat sa implice o alocare contigua de zona de memorie

	return 0;
}