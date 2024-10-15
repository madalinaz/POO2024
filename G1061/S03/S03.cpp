#include<iostream>
using namespace std;

int main() {
	/*char s1[20];
	char s2[20];
	cout << "Primul sir: ";
	cin.get(s1, 50);
	cout << s1<<endl;
	cin.ignore(50, '\n');
	cout << "Al doilea sir: ";
	cin.get(s2, 50);
	cout << s2;*/

	//alocare si citire sir de caractere alocat dinamic
	//CU CHAR*
	char* sir = nullptr;
	sir = new char[strlen("Gigel") + 1];
	strcpy_s(sir, strlen("Gigel") + 1, "Gigel");
	cout << "\nSir alocat dinamic: " << sir;
	delete[] sir;

	//CU STRING
	string sir2;
	cout << endl << "Sir care se va stoca cu string: ";
	cin >> sir2;
	cout << "Sir alocat dinamic prin string: " << sir2;

	//un vector de siruri de caractere
	//echivalent cu matrice de caractere

	//1. CU CHAR**
	char** m;
	int nrLinii;//nr de prieteni
	cout << "\nNr prieteni: ";
	cin >> nrLinii;
	char buffer[100];
	m = new char* [nrLinii];
	for (int i = 0; i < nrLinii; i++) {
		cout << "Prieten[" << i << "]= ";
		cin.ignore(100, '\n');
		cin.get(buffer, 100);
		m[i] = new char[strlen(buffer) + 1];
		strcpy_s(m[i], strlen(buffer) + 1, buffer);
	}
	cout << endl << "Lista prieteni: ";
	for (int i = 0; i < nrLinii; i++) {
		cout << "P" << i << ": " << m[i] << endl;
	}
	//dezalocare
	for (int i = 0; i < nrLinii; i++) {
		delete[] m[i];//fiecare linie e un vector de caractere
	}
	delete[] m;//vector de siruri de caractere

	//2. CU STRING*
	string* m2;
	int nrLinii2;//nr de prieteni
	cout << "\nNr prieteni2: ";
	cin >> nrLinii2;
	char buffer2[100];
	m2 = new string[nrLinii2];
	for (int i = 0; i < nrLinii2; i++) {
		cout << "Prieten[" << i << "]= ";
		cin.ignore(100, '\n');
		cin.get(buffer2, 100);
		m2[i] = buffer2;
	}
	cout << endl << "Lista prieteni: ";
	for (int i = 0; i < nrLinii; i++) {
		cout << "P" << i << ": " << m2[i] << endl;
	}
	//dezalocare
	delete[] m2;//vector de string-uri

	return 0;
}