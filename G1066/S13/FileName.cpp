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

	void striga() {
		cout << "\nActorul " + this->nume << " striga";
	}

	void seEnerveaza() {
		cout << "\nActorul " + this->nume << " tranteste usa";
	}

};

int main() {
	Actor a("Gigel");
	return 0;
}