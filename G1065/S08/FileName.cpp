#include<iostream>
using namespace std;

class Sejur {
	const int id;
	string destinatie;
	float pretBaza;
	int nrExcursiiOptionale;
	float* pretExcursii;
	int nrZile;
	//int durata;
	static string agentie;//toate pachetele sunt de la aceeasi agentie

public:
	Sejur(int _id) :id(_id) {
		this->destinatie = "-";
		this->pretBaza = 0;
		this->nrExcursiiOptionale = 0;
		this->pretExcursii = nullptr;
		this->nrZile = 0;
	}

	Sejur(int _id, string _destinatie, float _pretBaza, int _nrExcursiiOptionale, float* _pretExcursii, int _nrZile) :id(_id) {
		if (_destinatie.length() >= 2)
			this->destinatie = _destinatie;
		else
			this->destinatie = "-";
		if (_pretBaza > 0)
			this->pretBaza = _pretBaza;
		else
			this->pretBaza = 0;
		if (_nrExcursiiOptionale > 0 && _pretExcursii != nullptr) {
			this->nrExcursiiOptionale = _nrExcursiiOptionale;
			this->pretExcursii = new float[this->nrExcursiiOptionale];
			for (int i = 0; i < this->nrExcursiiOptionale; i++)
				this->pretExcursii[i] = _pretExcursii[i];
		}
		else {
			this->nrExcursiiOptionale = 0;
			this->pretExcursii = nullptr;
		}
		if (_nrZile > 0)
			this->nrZile = _nrZile;
		else
			this->nrZile = 0;
	}

	Sejur(const Sejur& s) :id(s.id) {
		if (s.destinatie.length() >= 2)
			this->destinatie = s.destinatie;
		else
			this->destinatie = "-";
		if (s.pretBaza > 0)
			this->pretBaza = s.pretBaza;
		else
			this->pretBaza = 0;
		if (s.nrExcursiiOptionale > 0 && s.pretExcursii != nullptr) {
			this->nrExcursiiOptionale = s.nrExcursiiOptionale;
			this->pretExcursii = new float[this->nrExcursiiOptionale];
			for (int i = 0; i < this->nrExcursiiOptionale; i++)
				this->pretExcursii[i] = s.pretExcursii[i];
		}
		else {
			this->nrExcursiiOptionale = 0;
			this->pretExcursii = nullptr;
		}
		if (s.nrZile > 0)
			this->nrZile = s.nrZile;
		else
			this->nrZile = 0;
	}

	Sejur& operator=(const Sejur& s) {
		if (this != &s) {
			if (this->pretExcursii != nullptr) {
				delete[] this->pretExcursii;
				this->pretExcursii = nullptr;
			}
			if (s.destinatie.length() >= 2)
				this->destinatie = s.destinatie;
			else
				this->destinatie = "-";
			if (s.pretBaza > 0)
				this->pretBaza = s.pretBaza;
			else
				this->pretBaza = 0;
			if (s.nrExcursiiOptionale > 0 && s.pretExcursii != nullptr) {
				this->nrExcursiiOptionale = s.nrExcursiiOptionale;
				this->pretExcursii = new float[this->nrExcursiiOptionale];
				for (int i = 0; i < this->nrExcursiiOptionale; i++)
					this->pretExcursii[i] = s.pretExcursii[i];
			}
			else {
				this->nrExcursiiOptionale = 0;
				this->pretExcursii = nullptr;
			}
			if (s.nrZile > 0)
				this->nrZile = s.nrZile;
			else
				this->nrZile = 0;
		}
		return *this;
	}

	//cast explicit la float
	explicit operator float() {
		float total = this->pretBaza;
		for (int i = 0; i < this->nrExcursiiOptionale; i++)
			total += this->pretExcursii[i];
		return total;
	}

	//cast implicit la char*
	operator char* () {
		char* copieDestinatie = new char[this->destinatie.length() + 1];
		strcpy_s(copieDestinatie, this->destinatie.length() + 1, this->destinatie.data());
		return copieDestinatie;//cine utilizeaza cast la char*, EL e cel care dezaloca aceasta zm
	}

	Sejur operator--(int) {
		Sejur copie = *this;
		if (this->pretExcursii != nullptr) {
			float min = this->pretExcursii[0];
			int ctMin = 0;
			for (int i = 0; i < this->nrExcursiiOptionale; i++)
				if (this->pretExcursii[i] < min) {
					min = this->pretExcursii[i];
					ctMin = 1;
				}
				else if (this->pretExcursii[i] == min) {
					ctMin++;
				}
			delete[] this->pretExcursii;
			this->pretExcursii = nullptr;
			if (this->nrExcursiiOptionale - ctMin > 0) {
				this->nrExcursiiOptionale = this->nrExcursiiOptionale - ctMin;
				this->pretExcursii = new float[this->nrExcursiiOptionale];
				for (int i = 0, j = 0; i < copie.nrExcursiiOptionale; i++) {
					if (copie.pretExcursii[i] != min) {
						this->pretExcursii[j++] = copie.pretExcursii[i];
					}
				}
			}
			else {
				this->nrExcursiiOptionale = 0;
				this->pretExcursii = nullptr;
			}
		}
		return copie;
	}

	int getNrZile() {
		return this->nrZile;
	}

	void setNrZile(int _nrZile) {
		if (_nrZile > 0)
			this->nrZile = _nrZile;
	}

	static string getAgentie() {
		return Sejur::agentie;
	}

	static void setAgentie(string _agentie) {
		if (_agentie.length() >= 2)
			Sejur::agentie = _agentie;
	}

	~Sejur() {
		if (this->pretExcursii != nullptr) {
			delete[] this->pretExcursii;
			this->pretExcursii = nullptr;
		}
	}

	friend ostream& operator<<(ostream& out, const Sejur& s) {
		out << "\nId: " << s.id << ", destinatie: " << s.destinatie;
		out << ", pret baza: " << s.pretBaza << ", nr excursii optionale: " << s.nrExcursiiOptionale << ", pret excursii: ";
		for (int i = 0; i < s.nrExcursiiOptionale; i++)
			out << s.pretExcursii[i] << " ";
		out << ", nr zile: " << s.nrZile;
		return out;
	}

	friend istream& operator>>(istream& in, Sejur*& ps) {
		string destinatie;
		int id;
		float pret;
		//si celelalte atribute
		cout << "\nDestinatie: ";
		in >> destinatie;
		cout << "Id: ";
		in >> id;
		cout << "Pret baza: ";
		in >> pret;
		ps = new Sejur(id, destinatie, pret, 0, nullptr, 0);
		return in;
	}

	bool operator<(float x) {
		if (x > 0) {
			if (this->pretExcursii != nullptr) {
				float max = this->pretExcursii[0];
				for (int i = 0; i < this->nrExcursiiOptionale; i++)
					if (this->pretExcursii[i] > max)
						max = this->pretExcursii[i];
				if (max < x)
					return true;
				return false;
			}
			else
				return true;
		}
	}
};

string Sejur::agentie = "AgentieABC";

bool operator<=(float x, Sejur s) {
	return !(s < x);
}

int main() {
	Sejur s1(12);
	s1.setNrZile(2);
	cout << endl << s1.getNrZile();
	Sejur::setAgentie("Agentia_ASE");
	cout << endl << Sejur::getAgentie();
	float preturi[] = { 100,200,100,300, 100 };
	Sejur s2(13, "Roma", 150, 5, preturi, 3);
	cout << s2;
	Sejur s3 = s2;
	cout << s3;
	Sejur* ps = new Sejur(17);
	delete ps;//apel explicit destructor al clasei Sejur
	{
		Sejur s4(123);
	}
	s1 = s3;//operator =
	cout << s1;

	/*Sejur s6(1234);
	cin >> s6;*/

	Sejur* pSejur = new Sejur(134);
	//Sejur* pSejur2 = &s1;
	//cin >> pSejur;
	//cout << *pSejur;

	float total = (float)s3;//conversie de la Sejur la float=> cast
	cout << endl << total;

	char* destinatie = s3;
	cout << endl << destinatie;
	delete[] destinatie;
	destinatie = nullptr;
	if (destinatie != nullptr) {
		cout << endl << destinatie;
	}

	s3--;
	cout << s3--;
	cout << s3--;
	cout << s3--;
	cout << s3;
	return 0;
}