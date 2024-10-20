#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

enum FormaInvatamant {
    ZI, ID
};

class Student {

    //sir de caractere
    char* nume;
    string facultate;
    int note[20];//zm pe stiva
    int nrNote;
    bool esteBuget;
    FormaInvatamant formaInvatamant;

public:
    //constructor fara parametrii
    Student() {
        //rol:alocare zona de memorie+initializare
        nume = nullptr;
        //sau
        nume = new char[strlen("Anonim") + 1];
        strcpy(nume, "Anonim");
        facultate = "-";
        nrNote = 0;
        esteBuget = false;
        formaInvatamant = FormaInvatamant::ZI;
    }

    //metode accesor(get si set)
    //si fac parte din interfata unui obiect
    //get rol de consultare si set rol de modificare
    //rol de consultare
    string getFacultate() {
        return facultate;
    }
    //rol de modificare
    void setFacultate1(string facultate) {
        this->facultate = facultate;//this este (pointer) adresa obiectului curent

    }
    void setFacultate2(string _facultate) {
        facultate = _facultate;
    }
    void setNume(const char* nume) {
        //daca am pentru cine schimba
        if (nume != nullptr) {
            //daca obj this are deja un nume?
            if (this->nume != nullptr) {
                delete[] this->nume;
                this->nume = nullptr;
            }
            this->nume = new char[strlen(nume) + 1];
            strcpy(this->nume, nume);
        }
    }

    const char* getNume() {
        return this->nume;
    }

    char* getNume2() {
        char* copie = nullptr;
        if (this->nume != nullptr) {
            copie = new char[strlen(this->nume) + 1];
            strcpy(copie, this->nume);
        }
        return copie;
    }

    void afisare() {
        cout << "\n--------------------------------------" << endl;
        if (nume != nullptr)
            cout << "\Nume: " << nume;
        else
            cout << "\nNume: -";
        cout << "\nFacultate: " << facultate;
        cout << "\nNr note: " << nrNote;
        //cout << "\nNote: " << note << " ";
        for (int i = 0; i < nrNote; i++)
            cout << note[i] << " ";
        cout << "\nEste la buget? " << esteBuget;
        cout << "\nForma de invatamant: " << formaInvatamant << endl;
    }
};
int main() {
    Student s;//constructorul default
    //s-obiect apelator
    s.afisare();
    cout << s.getFacultate();
    s.setFacultate1("CSIE");
    cout << endl << s.getFacultate();
    s.setNume("Gigel");//merge doar daca declaram const char* nume in lista de param pt setNume
    char sir[] = "Gigel";
    s.setNume(sir);
    //s.getNume()[0] = 'M';//!!!!get este doar de consultare, ca sa protejam adresa, declaram constanta!
    cout << endl << s.getNume();
    char* numeGet = s.getNume2();
    //....il folosesc pe numeGet
    numeGet[0] = 'M';
    delete[] numeGet;
    return 0;
}