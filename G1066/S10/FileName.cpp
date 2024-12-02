#include<iostream>
using namespace std;

class Cadou {
	string denumire;
	float pret;

public:
	Cadou() {
		this->denumire = "-";
		this->pret = 0;
	}

	Cadou(string _denumire, float _pret) {
		this->denumire = _denumire;
		this->pret = _pret;
	}

	Cadou(const Cadou& c) {
		this->denumire = c.denumire;
		this->pret = c.pret;
	}

	Cadou& operator=(const Cadou& c) {
		if (this != &c) {
			this->denumire = c.denumire;
			this->pret = c.pret;
		}
		return *this;
	}

	friend ostream& operator<<(ostream& out, const Cadou& c) {
		out << "\nDenumire: " << c.denumire << ", pret: " << c.pret;
		return out;
	}
};

class WishList {
	string posesor;
	Cadou** listaCadouri;
	int nrCadouri;
};

class WishList2 {
	string posesor;
	Cadou* listaCadouri[10];
	int nrCadouri;
};

class WishList3 {
	string posesor;
	Cadou* listaCadouri;
	int nrCadouri;
};

class WishList4 {
	string posesor;
	Cadou listaCadouri[10];
	int nrCadouri;
};

class WishList5 {
	string posesor;
	Cadou* cadouSpecial;
};

class WishList6 {
	string posesor;
	Cadou cadouSpecial;
};

class WishList7 {
	string posesor;
	Cadou** listaCadouri[24];
	int nrPrieteni;
	int* nrCadouri;
};

int main() {
	Cadou c1("stilou", 550);
	Cadou c2("carte", 100);
	Cadou c3("geanta", 1200);
	Cadou c4("ceas", 2000);


	//TO DO
	//relatie has a
	//exceptii + try-catch
	//derivare/mostenire/specializare =>relatie is a
	//virtualizare (meth virtuala + meth virtuala pura)
	//clase abstracte +interfete
	//clasa template + STL-uri
	//fisiere binare + text
	return 0;
}