/*
  TEMA :
  Lista prieteni cu nume si prenume
Vector de nume
Separat primesc numele unui sfant
Subprogram sau direct in main
1. Cati sunt sarbatoriti de sfantul X?
2. Folosind toate valentele (Ion, ioana, ionela etc)
*/


#include<iostream>
using namespace std;

// elimină cele mai mari 2 valori din vector cu valori distincte
void eliminaCeleMaMari2Val(int*& v, int& n)
{
    // p1. Se calculează noua dimensiune
    int dimensiuneNoua = n - 2;

    // Găsim cele mai mari 2 valori distincte, max1 >= max2 (presupunere)
    int max1 = v[0], max2 = v[1];

    if (max1 < max2)
        swap(max1, max2);

    for (int i = 1; i < n; i++)
    {
        if (v[i] > max1)
        {
            max2 = max1;
            max1 = v[i];
        }
        else if (v[i] > max2)
        {
            max2 = v[i];
        }
    }

    // p2. Se alocă memorie pentru un vector nou de dimensiune redusă
    int* aux = new int[dimensiuneNoua];

    // p3. Copiem în noul vector toate valorile care nu sunt max1 sau max2
    int k = 0; // poziția în care scriu în vectorul nou
    for (int i = 0; i < n; i++)
        if (v[i] < max2)
            // if (v[i] != max1 && v[i] != max2)
        {
            aux[k++] = v[i];
        }

    // p4. Dezalocăm memoria pentru vectorul vechi
    delete[] v;

    // p5. Vectorul nou pointează spre cel vechi
    v = aux;
    n = dimensiuneNoua;
}

void adauga(int*& v, int& n)
// Intre oricare doua valori de aceeasi paritate se adauga media lor aritmetica)
{
    // Pas 1. Se calculeaza noua dimensiune
    int dimensiuneNoua = n;
    for (int i = 0; i < n - 1; i++)
        if (v[i] % 2 == v[i + 1] % 2)
            dimensiuneNoua++;

    // Pas 2. Se aloca zona de memorie pt un nou vector cu dim de la Pas 1
    int* aux = new int[dimensiuneNoua];

    // Pas 3. Copiem in noul vector ce ne trebuie
    int k = 0; // pozitia in care scriu in vectorul nou
    for (int i = 0; i < n - 1; i++)
    {
        aux[k++] = v[i];
        if (v[i] % 2 == v[i + 1] % 2)
            aux[k++] = (v[i] + v[i + 1]) / 2;
    }
    aux[k++] = v[n - 1];

    // Pas 4. Dezalocam zona de memorie pentru vectorul vechi
    delete[] v; // dezalocam ce a fost alocat in main()

    // Pas 5. Vector nou points to vector vechi
    v = aux;
    n = dimensiuneNoua;
}

int main()
{
    int n1, n2;
    int* v1 = nullptr;
    int* v2 = nullptr;

    cout << "Introdu dimensiunea primului vector (pentru adaugarea mediilor): ";
    cin >> n1;

    // Alocăm memorie pentru primul vector și citim elementele
    v1 = new int[n1];
    cout << "Introdu elementele primului vector:\n";
    for (int i = 0; i < n1; i++)
        cin >> v1[i];

    // Apelăm funcția pentru a adăuga media între valorile de aceeași paritate
    adauga(v1, n1);

    // Afișăm vectorul cu mediile adăugate
    cout << "Vector dupa adaugarea mediilor:\n";
    for (int i = 0; i < n1; i++)
        cout << v1[i] << " ";
    cout << endl;

    // Citim dimensiunea celui de-al doilea vector (pentru eliminarea celor mai mari 2 valori)
    cout << "\nIntrodu dimensiunea celui de-al doilea vector (pentru eliminarea celor mai mari 2 valori): ";
    cin >> n2;

    // Alocăm memorie pentru al doilea vector și citim elementele
    v2 = new int[n2];
    cout << "Introdu elementele celui de-al doilea vector:\n";
    for (int i = 0; i < n2; i++)
        cin >> v2[i];

    // Apelăm funcția pentru a elimina cele mai mari 2 valori
    eliminaCeleMaMari2Val(v2, n2);

    // Afișăm noul vector
    cout << "Vector dupa eliminarea celor mai mari 2 valori:\n";
    for (int i = 0; i < n2; i++)
        cout << v2[i] << " ";
    cout << endl;


    // Dezalocăm memoria pentru ambii vectori
    delete[] v1;
    v1 = nullptr; // !!! Dupa orice delete !!!

    delete[] v2;
    v2 = nullptr;

    return 0;
}
