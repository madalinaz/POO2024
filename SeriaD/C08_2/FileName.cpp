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
	Cadou(){ }
	
	Cadou(string _denumire, float _pret, Ambalaj _ambalaj):denumire(_denumire), pret(_pret), ambalaj(_ambalaj){ }
	
	Cadou(const Cadou& c):denumire(c.denumire), pret(c.pret), ambalaj(c.ambalaj) { }
	
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

class WishList1 {
	string detinator;
	Cadou** listaCadouri;//vector alocat dinamic de Cadou*
	int nrCadouri;
};

class WishList2 {
	string detinator;
	Cadou* listaCadouri[100];//vector alocat static de Cadou*
	int nrCadouri;
};

class WishList3 {
	string detinator;
	Cadou* listaCadouri;//vector alocat dinamic de Cadou
	int nrCadouri;
};

class WishList4 {
	string detinator;
	Cadou listaCadouri[100];//vector alocat static de Cadou
	int nrCadouri;
};

//has a de tip 1-1
class WishList5 {
	string detinator;
	Cadou cadouSpecial;//un obj de tip Cadou
	int nrCadouri;
};

//has a de tip 1-1
class WishList6 {
	string detinator;
	Cadou* cadouSpecial;//un pointer la un Cadou
	int nrCadouri;
};

class WishList7 {
	string detinator;
	Cadou** cadouSpecial[24];//calendar Advent
	int* nrCadouri;
	int nrPrieteni;
};

int main() {
	Cadou c1("Stilou", 450, Ambalaj::CUTIE);
	cout << c1;
	cin >> c1;
	cout << c1;
	return 0;
}