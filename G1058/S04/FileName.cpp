#include<iostream>
using namespace std;

class FelMancare
{
    string denumire;
    int nrCalorii;
    int nrIngrediente;
    string* listaIngrediente;
    float* gramajIngrediente;
public:

    FelMancare()
    {
        cout << "\nAPEL CONSTR FARA PARAM";
        denumire = "-";
        nrCalorii = 0;
        nrIngrediente = 0;
        listaIngrediente = nullptr;
    }

    FelMancare(string _denumire, int _nrCalorii)
    {
        cout << "\nAPEL CONSTR CU CATIVA PARAM";
        denumire = _denumire;
        nrCalorii = _nrCalorii;
        nrIngrediente = 0;
        listaIngrediente = nullptr;
    }

    FelMancare(string _denumire, int _nrCalorii, int _nrIngrediente, string* _listaIngrediente)
    {
        cout << "\nAPEL CONSTR CU TOTI PARAM";
        denumire = _denumire;
        nrCalorii = _nrCalorii;
        // nu validam nimic din ce tine de obiect in constructor, acum se construieste
        if (_nrIngrediente > 0 && _listaIngrediente != nullptr)
        {
            nrIngrediente = _nrIngrediente;
            listaIngrediente = new string[nrIngrediente]; //vector de siruri de caractere
            for (int i = 0; i < nrIngrediente; i++)
            {
                listaIngrediente[i] = _listaIngrediente[i];
            }
        }
        else
        {
            nrIngrediente = 0;
            listaIngrediente = nullptr;
        }
    }

    //constructor de copiere
    FelMancare(const FelMancare& f)
    {
        cout << "\nAPEL CONSTR DE COPIERE";
        denumire = f.denumire;
        nrCalorii = f.nrCalorii;
        // nu validam nimic din ce tine de obiect in constructor, acum se construieste
        if (f.nrIngrediente > 0 && f.listaIngrediente != nullptr)
        {
            nrIngrediente = f.nrIngrediente;
            listaIngrediente = new string[nrIngrediente]; //vector de siruri de caractere
            for (int i = 0; i < nrIngrediente; i++)
            {
                listaIngrediente[i] = f.listaIngrediente[i];
            }
        }
        else
        {
            nrIngrediente = 0;
            listaIngrediente = nullptr;
        }
    }

    ~FelMancare()
    {
        cout << "\nAPEL DESTRUCTOR";
        if (listaIngrediente != nullptr)
        {
            delete[] listaIngrediente;
            listaIngrediente = nullptr; //dangling pointers, not good
        }
    }

    void afisare()
    {
        cout << "\n--------------------------";
        cout << "\nDenumire: " << denumire;
        cout << "\nNr calorii: " << nrCalorii;
        cout << "\nNr ingrediente: " << nrIngrediente;
        cout << "\nIngrediente: ";
        for (int i = 0; i < nrIngrediente; i++)
        {
            cout << listaIngrediente[i] << ", ";
        }
        cout << "\n--------------------------";

    }

};


int main()
{
    FelMancare f1;
    f1.afisare();
    string listaIngrediente[] = { "blat", "mozzarela", "sos rosii", "ciuperci" };
    FelMancare f2("Pizza", 400, 4, listaIngrediente);
    f2.afisare();
    FelMancare f3("Burger", 730);
    f3.afisare();

    FelMancare* pf = new FelMancare(); //alocare dinamica cu clase
    delete pf; //fara [] deoarece pf este un singur pointer

    FelMancare f5 = f2; //stie sa apeleze constructorul de copiere
    FelMancare f6(f3); //este acelasi lucru cu linia de mai sus
    f5.afisare();
    return 0;
}