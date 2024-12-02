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

	void setPret(float _pret) {
		if (_pret > 0) {
			this->pret = _pret;
		}
		else {
			throw - 1;
		}
	}

	void setDenumire(string _denumire) {
		if (_denumire.length() >= 3) {
			this->denumire = _denumire;
		}
		else {
			throw new exception("denumirea are o lg prea scurta");
		}
	}

	friend ostream& operator<<(ostream& out, const Cadou& c) {
		out << "\nDenumire: " << c.denumire << ", pret: " << c.pret;
		return out;
	}
};

class WishList {
	string posesor;
	Cadou** listaCadouri;//vector alocat dinamic de Cadou*
	int nrCadouri;

public:
	WishList() {
		this->posesor = "Anonim";
		this->listaCadouri = nullptr;
		this->nrCadouri = 0;
	}

	WishList(string _posesor, Cadou** _listaCadouri, int _nrCadouri) {
		this->posesor = _posesor;
		//alocare dinamica in context de deep copy
		if (_listaCadouri != nullptr && _nrCadouri > 0) {
			this->nrCadouri = _nrCadouri;
			this->listaCadouri = new Cadou * [this->nrCadouri];
			for (int i = 0; i < this->nrCadouri; i++) {
				//this->listaCadouri[i] = _listaCadouri[i];
				this->listaCadouri[i] = new Cadou(*_listaCadouri[i]);

				/*this->listaCadouri[i] = new Cadou();
				*this->listaCadouri[i] = *_listaCadouri[i];*/
			}
		}
		else {
			this->listaCadouri = nullptr;
			this->nrCadouri = 0;
		}
	}

	WishList(const WishList& w) {
		this->posesor = w.posesor;
		if (w.listaCadouri != nullptr && w.nrCadouri > 0) {
			this->nrCadouri = w.nrCadouri;
			this->listaCadouri = new Cadou * [this->nrCadouri];
			for (int i = 0; i < this->nrCadouri; i++) {
				this->listaCadouri[i] = new Cadou(*w.listaCadouri[i]);
			}
		}
		else {
			this->listaCadouri = nullptr;
			this->nrCadouri = 0;
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
			if (w.listaCadouri != nullptr && w.nrCadouri > 0) {
				this->nrCadouri = w.nrCadouri;
				this->listaCadouri = new Cadou * [this->nrCadouri];
				for (int i = 0; i < this->nrCadouri; i++) {
					this->listaCadouri[i] = new Cadou(*w.listaCadouri[i]);
				}
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
		out << "\n---------------------";
		out << "\nPosesor lista: " << w.posesor;
		out << "\nNr cadouri: " << w.nrCadouri;
		out << "\nLista cadouri: ";
		for (int i = 0; i < w.nrCadouri; i++) {
			out << *w.listaCadouri[i];
		}
		return out;
	}
};

class WishList2 {
	string posesor;
	Cadou* listaCadouri[10];//vector static de Cadou*
	int nrCadouri;
};

class WishList3 {
	string posesor;
	Cadou* listaCadouri;//vector dinamic de Cadou
	int nrCadouri;
};

class WishList4 {
	string posesor;
	Cadou listaCadouri[10];//vector static de Cadou
	int nrCadouri;
};

class WishList5 {
	string posesor;
	Cadou* cadouSpecial;//un pointer la Cadou
};

//relatie has a 1-1
class WishList6 {
	string posesor;
	Cadou cadouSpecial;//un obj de tip Cadou
};

//
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
	Cadou vector[4];
	Cadou* vector2 = new Cadou[5];

	Cadou* lista[] = { &c1, &c2, &c3, &c4 };
	WishList w("Gigel", lista, 4);
	cout << w;

	cout << "\n\n%%%%%%TRATARE EXCEPTII%%%%%%%%%";
	//c1.setPret(120);
	cout << endl<<c1;
	try {
		c1.setPret(-10);
		cout << endl << c1;
	}
	catch (int cod) {
		cout << endl << "Hey, pretul este negativ";
	}
	
	try {
		c1.setDenumire("AB");
		cout << endl << c1;
	}
	catch (exception* ex) {
		cout << endl << ex->what();//gettter pe message
		delete ex;
		//to do-ul in caz ca setDenumire nu s-a executat
	}

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