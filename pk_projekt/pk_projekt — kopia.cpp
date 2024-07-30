#include <iostream>
#include <memory>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <list>
#include <iomanip>
#include<map>
using namespace std;

class Produkt
{
protected:
    string nazwa;
public:
    virtual void Show() = 0;
    virtual string GetNameV() = 0;
    virtual pair<int, string> GetIleV() = 0;
    virtual void SetIleV(int x) = 0;
};

class Skladnik : public Produkt
{
    int ile;
    string jednostka;
public:
    Skladnik()
    {
        ile = 0;
    }
    Skladnik(string p_nazwa, int p_ile, string p_jednostka) : ile(p_ile), jednostka(p_jednostka)
    {
        nazwa = p_nazwa;
    }
    friend ostream& operator << (ostream& s, Skladnik& x)
    {
        s << x.nazwa << " ";
        s << x.ile << " ";
        s << x.jednostka;
        return s;
    }
    string Get()
    {
        string pom1, pom2;
        pom2 = to_string(ile);
        pom1 = nazwa + " " + pom2 + " " + jednostka;
        return pom1;
    }
    void Show()
    {
        cout << nazwa << " ";
        cout << ile << " ";
        cout << jednostka << endl;
    }
    string GetName()
    {
        return nazwa;
    }
    int GetIle()
    {
        return ile;
    }
    string GetNameV()
    {
        return nazwa;
    }
    pair<int, string> GetIleV()
    {
        pair<int, string> zestaw(ile, "skladnik");
        return zestaw;
    }

    void SetIle(int x)
    {
        ile = x;
    }
    void SetIleV(int x)
    {
        ile = x;
    }
};

class Przyprawa : public Produkt
{
    string intensywnosc, smak;
public:
    Przyprawa()
    {

    }
    Przyprawa(string p_nazwa, string p_intensywnosc, string p_smak) : intensywnosc(p_intensywnosc), smak(p_smak)
    {
        nazwa = p_nazwa;
    }
    friend ostream& operator << (ostream& s, Przyprawa& x)
    {
        s << x.nazwa << " ";
        s << x.intensywnosc << " ";
        s << x.smak;
        return s;
    }
    string Get()
    {
        string pom1;
        pom1 = nazwa + " " + intensywnosc + " " + smak;
        return pom1;
    }
    void Show()
    {
        cout << nazwa << " ";
        cout << intensywnosc << " ";
        cout << smak << endl;
    }
    string GetName()
    {
        return nazwa;
    }
    string GetNameV()
    {
        return nazwa;
    }
    pair<int, string> GetIleV()
    {
        pair<int, string> zestaw(0, "przyprawa");
        return zestaw;
    }
    void SetIleV(int x)
    {
        int pom;
        x >> pom;
    }
};

class Przepis
{
    string nazwa, dieta;
    vector<shared_ptr<Skladnik>> skladniki;
    vector<shared_ptr<Przyprawa>> przyprawy;
    vector<string> opis;
    int kalorycznosc;
public:
    Przepis()
    {
        nazwa = "";
        dieta = "";
        kalorycznosc = 0;
    }
    Przepis(string p_nazwa, vector<shared_ptr<Skladnik>> p_skladniki, vector<shared_ptr<Przyprawa>> p_przyprawy, vector<string> p_opis, string p_dieta, int p_kalorycznosc) : nazwa(p_nazwa), skladniki(p_skladniki), przyprawy(p_przyprawy), opis(p_opis), dieta(p_dieta), kalorycznosc(p_kalorycznosc)
    {

    }
    friend istream& operator >> (istream& s, Przepis& x)
    {
        int marker = 0;
        string pom, pom2, pom3, pom4;
        int pom1 = 0;
        cout << "wpisz nazwe \n";
        cin.ignore();
        getline(cin, pom);
        x.nazwa = pom;
        cout << "nazwy przypraw i skladnikow ktores wielo czlonowe rodzielaj '_'" << endl;
        cout << "wpisz nazwe skladnika, potem ilosc i jednostke skladnika gdy skonczysz wpisz ten znak '^'\n";
        do {
            getline(cin, pom);
            if (pom[0] == '^')break;
            stringstream ss(pom);

            if (ss >> pom && ss >> pom1 && ss >> pom3)
            {
                if (ss >> pom4)
                {
                    cout << "nie udalo sie wczytac danych za duzo podano\n";
                    continue;
                }
                if (!(pom3 == "g" || pom3 == "ml" || pom3 == "sztuk"))
                {
                    cout << "podana jednostka jest z poza zakresu \n";
                    continue;
                }
                x.skladniki.push_back(shared_ptr<Skladnik>(new Skladnik(pom, pom1, pom3)));
            }
            else cout << "nie udalo sie wczytac danych\n";
        } while (true);
        cout << "wpisz nazwe przyprawy itensywnosc i jej smak (jesli jest to cos oczywistego mozna wpisac brak zamiast intensywnosci i brak zamiast samku) \ngdy skonczysz wpisz ten znak '^'\n";
        do {
            getline(cin, pom);
            if (pom[0] == '^')break;
            stringstream ss(pom);
            if (ss >> pom && ss >> pom2 && ss >> pom3)
            {
                if (ss >> pom4)
                {
                    cout << "nie udalo sie wczytac danych za duzo podano\n";
                    continue;
                }
                x.przyprawy.push_back(shared_ptr<Przyprawa>(new Przyprawa(pom, pom2, pom3)));
            }
        } while (true);
        cout << "wpisz opis przygotowania gdy skonczysz wpisz '^' \n";
        do
        {
            s >> pom;
            if (pom[0] == '^') break;
            x.opis.push_back(pom);
        } while (true);
        cout << "wpisz rodzaj diety przy ktorej mozna jesc to danie \n";
        cin.ignore();
        getline(cin, pom);
        x.dieta = pom;
        cout << "wpisz kalorycznosc \n";
        do
        {
            getline(cin, pom);
            stringstream ss(pom);
            if (ss >> pom1)
            {
                x.kalorycznosc = pom1;
                break;
            }
            else cout << "bledne dane\n";
        } while (true);
        return s;
    }
    friend ostream& operator << (ostream& s, Przepis& x)
    {
        s << x.nazwa << endl;
        s << "skladniki:" << endl;
        for (int i = 0; i < x.skladniki.size(); i++)
        {
            s << *(x.skladniki[i]) << endl;
        }
        s << "przyprawy:" << endl;
        for (int i = 0; i < x.przyprawy.size(); i++)
        {
            s << *(x.przyprawy[i]) << endl;
        }
        s << "opis przygotowania:" << endl;
        for (int i = 0; i < x.opis.size(); i++)
        {
            s << x.opis[i];
        }
        s << endl;
        s << "dieta do ktorej pasuje:" << endl;
        s << x.dieta << endl;
        s << "kalorycznosc potrawy:" << endl;
        s << x.kalorycznosc << " cal" << endl;
        return s;
    }
    void Wypisz()
    {
        cout << nazwa << endl;
        cout << "Skladniki: \n";
        for (auto& x : skladniki)
        {
            cout << *x << endl;
        }
        cout << "Przyprawy: \n";
        for (auto& x : przyprawy)
        {
            cout << *x << endl;
        }
        cout << "Opis przygotowania: \n";
        for (auto& x : opis)
        {
            cout << x << " ";
        }
        cout << endl;
        cout << "Nazwa diety: \n";
        cout << dieta << endl;
        cout << "kalorycznosc: \n";
        cout << kalorycznosc << " cal" << endl;
    }
    string GetName()
    {
        return nazwa;
    }
    string GetDiet()
    {
        return dieta;
    }
    vector<string> GetOpis()
    {
        return opis;
    }
    vector<shared_ptr<Skladnik>> GetSkladnik()
    {
        return skladniki;
    }
    vector<shared_ptr<Przyprawa>> GetPrzyprawy()
    {
        return przyprawy;
    }
    int GetCal()
    {
        return kalorycznosc;
    }
    void Set(string& s)
    {
        nazwa = s;
    }
    friend void Save(Przepis*& x);
};

class Dieta
{
    string nazwa_diety;
    vector<shared_ptr<Przepis>> wszystkie_z_diety;
public:
    Dieta()
    {

    }
    Dieta(string p_nazwa_diety, vector<shared_ptr<Przepis>> p_wszystkie_z_diety) : nazwa_diety(p_nazwa_diety), wszystkie_z_diety(p_wszystkie_z_diety)
    {

    }
    string Get()
    {
        return nazwa_diety;
    }
    vector<shared_ptr<Przepis>> GetVec()
    {
        return wszystkie_z_diety;
    }
    void push(Przepis*& x)
    {
        wszystkie_z_diety.push_back(shared_ptr<Przepis>(new Przepis(*x)));
    }
    void push1(Przepis& x)
    {
        wszystkie_z_diety.push_back(shared_ptr<Przepis>(new Przepis(x)));
    }
};

int Modul(int& x)
{
    if (x < 0) x = -x;
    return x;
}

class BazaDanych
{
    vector<shared_ptr<Dieta>> diety;
    vector<shared_ptr<Przepis>> przepisy;
public:
    BazaDanych()
    {

    }
    void NadpiszPrzepis(Przepis*& x)
    {
        int marker = 0;
        string pom1, pom2;
        vector<shared_ptr<Przepis>> pom;
        przepisy.push_back(shared_ptr<Przepis>(new Przepis(*x)));
        for (int i = 0; i < diety.size(); i++)
        {
            pom1 = diety[i]->Get();
            if (pom1 == x->GetDiet())
            {
                marker = 1;
                diety[i]->push(x);
            }
        }
        if (marker == 0)
        {
            pom2 = x->GetDiet();
            pom.push_back(shared_ptr<Przepis>(new Przepis(*x)));
            diety.push_back(shared_ptr<Dieta>(new Dieta(pom2, pom)));
        }

    }
    void Load()
    {
        string s, nazwa, dieta, pom1, pom2, pom3;
        int pom = 0, marker = 0;
        int kalorycznosc;
        vector<shared_ptr<Skladnik>> skladniki;
        vector<shared_ptr<Przyprawa>> przyprawy;
        vector<string> opis;
        vector<shared_ptr<Przepis>> pom4;
        shared_ptr<Przepis> pom5;
        fstream fille;
        fille.open("Bazadanych.txt", ios::in);
        while (!fille.eof())
        {
            getline(fille, s);
            if (s == "")continue;
            nazwa = s;
            while (true)
            {
                getline(fille, s);
                if (s == "^")break;
                istringstream ss(s);
                ss >> pom1 >> pom >> pom3;
                skladniki.push_back(shared_ptr<Skladnik>(new Skladnik(pom1, pom, pom3)));
            }
            while (true)
            {
                getline(fille, s);
                if (s == "^")break;
                istringstream ss(s);
                ss >> pom1 >> pom2 >> pom3;
                przyprawy.push_back(shared_ptr<Przyprawa>(new Przyprawa(pom1, pom2, pom3)));
            }
            while (true)
            {
                getline(fille, s);
                if (s == "^")break;
                istringstream ss(s);
                while (ss >> pom1)
                {
                    opis.push_back(pom1);
                }
            }
            getline(fille, s);
            dieta = s;
            getline(fille, s);
            istringstream ss(s);
            ss >> kalorycznosc;
            przepisy.push_back(shared_ptr<Przepis>(new Przepis(nazwa, skladniki, przyprawy, opis, dieta, kalorycznosc)));
            pom4.push_back(shared_ptr<Przepis>(new Przepis(nazwa, skladniki, przyprawy, opis, dieta, kalorycznosc)));
            pom5 = (shared_ptr<Przepis>(new Przepis(nazwa, skladniki, przyprawy, opis, dieta, kalorycznosc)));
            for (int i = 0; i < diety.size(); i++)
            {
                pom1 = diety[i]->Get();
                if (pom1 == dieta)
                {
                    marker = 1;
                    diety[i]->push1(*pom5);
                }
            }
            if (marker == 0)
            {
                pom2 = dieta;
                diety.push_back(shared_ptr<Dieta>(new Dieta(pom2, pom4)));
            }
            skladniki.clear();
            przyprawy.clear();
            pom4.clear();
            opis.clear();
            marker = 0;
        }
        fille.close();
    }
    void Save()
    {
        string nazwa, dieta, pom1, pom2, pom3;
        int kalorycznosc;
        int pom;
        vector<shared_ptr<Skladnik>> skladniki;
        vector<shared_ptr<Przyprawa>> przyprawy;
        vector<string> opis;
        fstream fille;
        fille.open("Bazadanych.txt", ios::out);
        for (int i = 0; i < przepisy.size(); i++)
        {
            nazwa = przepisy[i]->GetName();
            fille << nazwa << endl;
            skladniki = przepisy[i]->GetSkladnik();
            for (int i = 0; i < skladniki.size(); i++)
            {
                fille << skladniki[i]->Get() << endl;
            }
            fille << "^" << endl;
            przyprawy = przepisy[i]->GetPrzyprawy();
            for (int i = 0; i < przyprawy.size(); i++)
            {
                fille << przyprawy[i]->Get() << endl;
            }
            fille << "^" << endl;
            opis = przepisy[i]->GetOpis();
            for (int i = 0; i < opis.size(); i++)
            {
                fille << opis[i] << " ";
            }
            fille << endl;
            fille << "^" << endl;
            dieta = przepisy[i]->GetDiet();
            fille << dieta << endl;
            kalorycznosc = przepisy[i]->GetCal();
            fille << kalorycznosc << " cal" << endl;
        }
        fille.close();
    }
    void Search()
    {
        string pom1, pom2;
        int marker = 0, x;
        for (int i = 0; i < przepisy.size(); i++)
        {
            cout << "Nazwa przepisu: " << przepisy[i]->GetName() << " | ";
            cout << "Dieta do ktorej pasuje: " << przepisy[i]->GetDiet() << endl;
        }
        cout << "jaki przepis chcesz wybrac" << endl;
        cin.ignore();
        getline(cin, pom1);
        system("CLS");
        for (int i = 0; i < przepisy.size(); i++)
        {
            pom2 = przepisy[i]->GetName();
            if (pom1 == pom2)
            {
                marker = 1;
                cout << endl;
                przepisy[i]->Wypisz();
                do
                {
                    cout << "\n\n\nco chcesz zrobic \n";
                    cout << "1.nic \n";
                    cout << "2.usun przepis \n";
                    cin >> x;
                    switch (x)
                    {
                    case 1:
                        break;
                    case 2:
                        przepisy.erase(przepisy.begin() + i);
                        break;
                    default:
                        break;
                    }
                } while (x != 1 && x != 2);
            }
        }
        system("PAUSE");
    }
    void SearchCal()
    {
        string pom1, pom2;
        int pom3 = 0, pom4 = 0, pom5 = 0, pom6 = 0;
        int marker = 0, najblizej = 10000, obecna, y = 0;
        cout << "jaki wartosci kaloryczne cie interesuja" << endl;
        cin >> pom3;
        pom5 = pom3 + 20;
        pom6 = pom3 - 20;
        for (int i = 0; i < przepisy.size(); i++)
        {
            pom4 = przepisy[i]->GetCal();
            obecna = pom3 - pom4;
            Modul(obecna);
            if (obecna < najblizej)
            {
                najblizej = obecna;
                y = i;
            }
            if (pom5 >= pom4 && pom4 >= pom6)
            {
                marker = 1;
                cout << "Nazwa przepisu: " << przepisy[i]->GetName() << " | ";
                cout << "kalorycznosc: " << przepisy[i]->GetCal() << endl;
            }
        }
        if (marker == 0)
        {
            system("CLS");
            cout << endl;
            cout << "Nie znaleziono przepisow z zadawalajacego przedzialu \n w zamian za to pokazujemy przepis kalorycznie najblizej zapytania \n";
            przepisy[y]->Wypisz();
        }
        else
        {
            cout << "jaki przepis chcesz wybrac" << endl;
            cin.ignore();
            getline(cin, pom1);
            for (int i = 0; i < przepisy.size(); i++)
            {
                pom2 = przepisy[i]->GetName();
                if (pom1 == pom2)
                {
                    marker = 1;
                    system("CLS");
                    cout << endl;
                    przepisy[i]->Wypisz();
                }
            }
            system("PAUSE");
        }
        system("PAUSE");
    }
    void SearchDieta()
    {
        string pom1, pom2;
        vector<shared_ptr<Przepis>> pom;
        int marker = 0;
        for (int i = 0; i < diety.size(); i++)
        {
            cout << "Nazwa Diety: " << diety[i]->Get() << endl;
            pom = diety[i]->GetVec();
            for (int i = 0; i < pom.size(); i++)
            {
                cout << "Nazwa przepisu: " << pom[i]->GetName() << " | ";
                cout << "kalorycznosc: " << pom[i]->GetCal() << endl;
            }
            pom.clear();
            cout << endl;
        }
        cout << "jaki przepis chcesz wybrac" << endl;
        cin.ignore();
        getline(cin, pom1);
        for (int i = 0; i < przepisy.size(); i++)
        {
            pom2 = przepisy[i]->GetName();
            if (pom1 == pom2)
            {
                marker = 1;
                system("CLS");
                cout << endl;
                przepisy[i]->Wypisz();
            }
        }
        system("PAUSE");
    }
    vector<shared_ptr<Przepis>> Get()
    {
        return przepisy;
    }
};

class Spizarka
{
    vector<shared_ptr<Skladnik>> skladniki_dostepne;
    vector<shared_ptr<Przyprawa>> przyprawy_dostepne;
    vector<shared_ptr<Produkt>> produkty;
public:
    Spizarka()
    {

    }
    friend istream& operator >> (istream& s, Spizarka& x)
    {
        string pom, pom2, pom3, pom4;
        int pom1;
        cin.ignore();
        cout << "wpisz jakie masz produkty w spizarce wpisz nazwe skladnika, potem ilosc i jednostke\n gdy skonczysz wpisz ten znak '^'\n";
        do {
            getline(cin, pom);
            if (pom[0] == '^')break;
            stringstream ss(pom);
            if (ss >> pom && ss >> pom1 && ss >> pom3)
            {
                if (ss >> pom4)
                {
                    cout << "nie udalo sie wczytac danych za duzo podano\n";
                    continue;
                }
                if (!(pom3 == "g" || pom3 == "ml" || pom3 == "sztuk"))
                {
                    cout << "podana jednostka jest z poza zakresu \n";
                    continue;
                }
                x.skladniki_dostepne.push_back(shared_ptr<Skladnik>(new Skladnik(pom, pom1, pom3)));
                x.produkty.push_back(shared_ptr<Skladnik>(new Skladnik(pom, pom1, pom3)));
            }
            else cout << "nie udalo sie wczytac danych\n";
        } while (true);
        cout << "wpisz jakie masz przyprawy w spizarce wpisz nazwe przyprawy itensywnosc i jej smak \n(jesli jest to cos oczywistego mozna wpisac brak zamiast intensywnosci i brak zamiast samku) \n gdy skonczysz wpisz ten znak '^' \n";
        do {
            getline(cin, pom);
            if (pom[0] == '^')break;
            stringstream ss(pom);
            if (ss >> pom && ss >> pom2 && ss >> pom3)
            {
                if (ss >> pom4)
                {
                    cout << "nie udalo sie wczytac danych za duzo podano\n";
                    continue;
                }
                x.przyprawy_dostepne.push_back(shared_ptr<Przyprawa>(new Przyprawa(pom, pom2, pom3)));
                x.produkty.push_back(shared_ptr<Przyprawa>(new Przyprawa(pom, pom2, pom3)));
            }
        } while (true);
        return s;
    }
    void Save()
    {
        string pom1, pom2;
        fstream fille1, fille2;
        fille1.open("skladnik.txt", ios::out);
        fille2.open("przyprawy.txt", ios::out);
        for (int i = 0; i < skladniki_dostepne.size(); i++)
        {
            pom2 = skladniki_dostepne[i]->Get();
            fille1 << pom2 << endl;
        }
        for (int i = 0; i < przyprawy_dostepne.size(); i++)
        {
            pom2 = przyprawy_dostepne[i]->Get();
            fille2 << pom2 << endl;
        }
        fille1.close();
        fille2.close();
    }
    void LoadFridge()
    {
        string pom1, pom2, pom3, s;
        int pom;
        fstream fille1, fille2;
        fille1.open("skladnik.txt", ios::in);
        fille2.open("przyprawy.txt", ios::in);
        while (!fille1.eof())
        {
            getline(fille1, s);
            if (s == "")continue;
            stringstream ss(s);
            ss >> pom1 >> pom >> pom3;
            skladniki_dostepne.push_back(shared_ptr<Skladnik>(new Skladnik(pom1, pom, pom3)));
            produkty.push_back(shared_ptr<Skladnik>(new Skladnik(pom1, pom, pom3)));
        }
        while (!fille2.eof())
        {
            getline(fille2, s);
            if (s == "")continue;
            stringstream ss(s);
            ss >> pom1 >> pom2 >> pom3;
            przyprawy_dostepne.push_back(shared_ptr<Przyprawa>(new Przyprawa(pom1, pom2, pom3)));
            produkty.push_back(shared_ptr<Przyprawa>(new Przyprawa(pom1, pom2, pom3)));
        }
        fille1.close();
        fille2.close();
    }
    void ShowMe()
    {
        string pom, pom2, pom3;
        int pom1, marker = 0;
        int x, y;
        string s;
        for (int i = 0; i < produkty.size(); i++)
        {
            produkty[i]->Show();
        }
        cout << "czy chcesz cos zmienic:" << endl;
        cout << "1.nie:" << endl;
        cout << "2.wybierz produkt do usuniecia:" << endl;
        cout << "3.dodaj jeden produkt:" << endl;
        do
        {
            cin >> x;
            switch (x)
            {
            case 1:
                break;
            case 2:
                cout << "co chcesz ususnac:" << endl;
                cin.ignore();
                getline(cin, s);
                for (int i = 0; i < skladniki_dostepne.size(); i++)
                {
                    if (skladniki_dostepne[i]->GetName() == s) skladniki_dostepne.erase(skladniki_dostepne.begin() + i);

                }
                for (int i = 0; i < przyprawy_dostepne.size(); i++)
                {
                    if (przyprawy_dostepne[i]->GetName() == s) przyprawy_dostepne.erase(przyprawy_dostepne.begin() + i);
                }
                for (int i = 0; i < produkty.size(); i++)
                {
                    if (produkty[i]->GetNameV() == s) produkty.erase(produkty.begin() + i);
                }
                break;
            case 3:
                do
                {
                    cout << "co chcesz dodac :\n";
                    cout << "1. skladnik \n";
                    cout << "2. przyprawe \n";
                    cout << "0. koniec dodawania \n";
                    cin >> y;
                    switch (y)
                    {
                    case 1:
                        do {
                            cout << "wpisz nazwe skladnika ilosc oraz jednostek g, ml lub sztuk" << endl;
                            cin.ignore();
                            getline(cin, pom);
                            stringstream ss(pom);
                            if (ss >> pom && ss >> pom1 && ss >> pom3)
                            {
                                if (!(pom3 == "g" || pom3 == "ml" || pom3 == "sztuk"))
                                {
                                    cout << "podana jednostka jest z poza zakresu \n";
                                    continue;
                                }
                                skladniki_dostepne.push_back(shared_ptr<Skladnik>(new Skladnik(pom, pom1, pom3)));
                                produkty.push_back(shared_ptr<Skladnik>(new Skladnik(pom, pom1, pom3)));
                                marker = 1;
                            }
                            else cout << "nie udalo sie wczytac danych\n";
                        } while (!(marker == 1));
                        marker = 0;
                        break;
                    case 2:
                        do {
                            cout << "wpisz nazwe przyprawy, intensywnosc i smak" << endl;
                            cin.ignore();
                            getline(cin, pom);
                            stringstream ss(pom);
                            if (ss >> pom && ss >> pom2 && ss >> pom3)
                            {
                                przyprawy_dostepne.push_back(shared_ptr<Przyprawa>(new Przyprawa(pom, pom2, pom3)));
                                produkty.push_back(shared_ptr<Przyprawa>(new Przyprawa(pom, pom2, pom3)));
                                marker = 1;
                            }
                        } while (!(marker == 1));
                        marker = 0;
                        break;
                    default:
                        break;
                    }
                } while (!y == 0);
                break;
            default:
                break;
            }
        } while (!x == 1);
    }
    void WhatCanIDo(BazaDanych& x)
    {
        vector<shared_ptr<Przepis>> pom, pom3;
        shared_ptr<Przepis> zapasowy2;
        vector<shared_ptr<Skladnik>> pom1;
        vector<shared_ptr<Przyprawa>> pom2;
        int value = 0, all = 0, marker = 0, marker1 = 0, zapasowy = 1000, a, ilosc_z_lodowki, pomp;
        string pomp1, pomp2, pomp3;
        system("CLS");
        pom = x.Get();
        for (int i = 0; i < pom.size(); i++)
        {
            pom1 = pom[i]->GetSkladnik();
            all = pom1.size();
            for (int y = 0; y < pom1.size(); y++)
            {
                for (int z = 0; z < skladniki_dostepne.size(); z++)
                {
                    if ((skladniki_dostepne[z]->GetName() == pom1[y]->GetName()) && (skladniki_dostepne[z]->GetIle() >= pom1[y]->GetIle())) marker = 1;
                }
                if (marker == 1)value++;
                marker = 0;
            }
            pom2 = pom[i]->GetPrzyprawy();
            all += pom2.size();
            for (int y = 0; y < pom2.size(); y++)
            {
                for (int z = 0; z < przyprawy_dostepne.size(); z++)
                {
                    if (przyprawy_dostepne[z]->GetName() == pom2[y]->GetName())marker = 1;
                }
                if (marker == 1)value++;
                marker = 0;
            }
            if (1 >= (all - value))
            {
                marker1 = 1;
                cout << pom[i]->GetName() << endl;
                pom3.push_back(pom[i]);
                cout << "ilosc brakujacych skladnikow:" << all - value << endl << endl;
            }
            if ((all - value) < zapasowy)
            {
                zapasowy = all - value;
                zapasowy2 = pom[i];
            }
            all = 0;
            value = 0;
        }
        if (marker1 == 0)
        {
            pom3.push_back(zapasowy2);
            cout << "nie jestes wystarczajaco blisko zadnego przepisu wiec wyswietlamy jeden z tych do ktorego brakuje naj mniej skladnikow\n";
            cout << *zapasowy2 << endl;
            cout << "ilosc brakujacych skladnikow: " << zapasowy << endl;
            cout << "czy przepis zostal wykonany wybranie odpowiedzi tak poskutkuje usunieciem przedmiotow z lodowki" << endl;
            cout << "1.tak \n";
            cout << "2.nie \n";
            cin >> a;
            do
            {
                switch (a)
                {
                case 1:
                    for (int i = 0; i < pom3.size(); i++)
                    {
                        pom1 = pom3[i]->GetSkladnik();
                        for (int y = 0; y < pom1.size(); y++)
                        {
                            for (int z = 0; z < skladniki_dostepne.size(); z++)
                            {
                                if ((skladniki_dostepne[z]->GetName() == pom1[y]->GetName()))
                                {
                                    ilosc_z_lodowki = skladniki_dostepne[z]->GetIle();
                                    if ((ilosc_z_lodowki - pom1[y]->GetIle()) <= 0)skladniki_dostepne.erase(skladniki_dostepne.begin() + z);
                                    if ((ilosc_z_lodowki - pom1[y]->GetIle()) > 0) skladniki_dostepne[z]->SetIle(ilosc_z_lodowki - pom1[y]->GetIle());
                                }
                            }
                            for (int z = 0; z < produkty.size(); z++)
                            {
                                if ((produkty[z]->GetIleV().second) == "przyprawa")continue;
                                ilosc_z_lodowki = produkty[z]->GetIleV().first;
                                if ((ilosc_z_lodowki - pom1[y]->GetIle()) <= 0)produkty.erase(produkty.begin() + z);
                                if ((ilosc_z_lodowki - pom1[y]->GetIle()) > 0) produkty[z]->SetIleV(ilosc_z_lodowki - pom1[y]->GetIle());
                            }
                        }
                    }
                    break;
                default:
                    break;
                }
            } while (!(a == 1 || a == 2));
        }
        if (marker1 == 1)
        {
            cout << "jaki przepis chcesz wybrac" << endl;
            cin.ignore();
            getline(cin, pomp1);
            system("CLS");
            for (int i = 0; i < pom3.size(); i++)
            {
                pomp2 = pom3[i]->GetName();
                if (pomp1 == pomp2)
                {
                    cout << endl;
                    pom3[i]->Wypisz();
                    do
                    {
                        cout << "czy przepis zostal wykonany wybranie odpowiedzi tak poskutkuje usunieciem przedmiotow z lodowki" << endl;
                        cout << "1.tak \n";
                        cout << "2.nie \n";
                        cin >> a;
                        switch (a)
                        {
                        case 1:
                            pom1 = pom3[i]->GetSkladnik();
                            for (int y = 0; y < pom1.size(); y++)
                            {
                                for (int z = 0; z < skladniki_dostepne.size(); z++)
                                {
                                    if ((skladniki_dostepne[z]->GetName() == pom1[y]->GetName()))
                                    {
                                        ilosc_z_lodowki = skladniki_dostepne[z]->GetIle();
                                        if ((ilosc_z_lodowki - pom1[y]->GetIle()) <= 0)skladniki_dostepne.erase(skladniki_dostepne.begin() + z);
                                        if ((ilosc_z_lodowki - pom1[y]->GetIle()) > 0) skladniki_dostepne[z]->SetIle((ilosc_z_lodowki - pom1[y]->GetIle()));
                                    }
                                }
                                for (int z = 0; z < produkty.size(); z++)
                                {
                                    if ((produkty[z]->GetIleV().second) == "przyprawa")continue;
                                    if ((produkty[z]->GetNameV() == pom1[y]->GetName()))
                                    {
                                        ilosc_z_lodowki = produkty[z]->GetIleV().first;
                                        if ((ilosc_z_lodowki - pom1[y]->GetIle()) <= 0)produkty.erase(produkty.begin() + z);
                                        if ((ilosc_z_lodowki - pom1[y]->GetIle()) > 0) produkty[z]->SetIleV((ilosc_z_lodowki - pom1[y]->GetIle()));
                                    }
                                }
                            }
                            break;
                        default:
                            break;
                        }
                    } while (!(a == 1 || a == 2));
                }
            }
            system("PAUSE");
        }
    }
    void Delete()
    {
        skladniki_dostepne.clear();
        przyprawy_dostepne.clear();
        produkty.clear();
    }
};

void show_me()
{
    cout << "1.dodaj przepis" << endl;
    cout << "2.wyszukaj przepis " << endl;
    cout << "3.otworz spizarke " << endl;
    cout << "4.znajdz przepis po kalorycznosc " << endl;
    cout << "5.przeszukaj diety " << endl;
    cout << "0.koniec " << endl;
}

void show_me2()
{
    cout << "1.zresetuj spizarke" << endl;
    cout << "2.przejzyj spizarke" << endl;
    cout << "3.sprawdz czy mozesz cos zrobic z tymi produktami" << endl;
    cout << "0.MENU glowne" << endl;
}

void Save(Przepis*& x)
{
    fstream fille;
    fille.open("Bazadanych1.txt", ios::app);
    fille << endl;
    fille << x->nazwa << endl;
    for (auto& y : x->skladniki)
    {
        fille << *y << endl;
    }
    fille << "^" << endl;
    for (auto& y : x->przyprawy)
    {
        fille << *y << endl;
    }
    fille << "^" << endl;
    for (auto& y : x->opis)
    {
        fille << y << " ";
    }
    fille << endl;
    fille << "^" << endl;
    fille << x->dieta;
    fille << endl;
    fille << x->kalorycznosc << " cal";
    fille << endl;
    fille.close();
}

void If(Przepis*& x, BazaDanych& y)
{
    vector<shared_ptr<Przepis>> pom2;
    string pom3, pom4;
    int marker = 0;
    pom2 = y.Get();
    pom3 = x->GetName();
    for (int i = 0; i < pom2.size(); i++)
    {
        if (pom2[i]->GetName() == pom3)
        {
            do
            {
                cout << "wpisz inna nazwe przepisu rozumiem ze moze moga byc rozne przepisy na ta sama rzecz proponuje dopisanie numeru do nazwy \n";
                cin.ignore();
                getline(cin, pom4);
                if (pom3 == pom4)continue;
                x->Set(pom4);
                break;
            } while (true);
        }
    }
}
int main()
{
    string pom;
    int x, y;
    BazaDanych glowna;
    Spizarka lodowka;
    lodowka.LoadFridge();
    glowna.Load();
    cout << "oto menu do kazdej z opcji przechodzimy wybierajac na klawiaturze odpowiednia liczbe. 0 konczy program \n\n";
    do
    {
        Przepis* przepis_kucharski = (new Przepis);
        system("CLS");
        show_me();
        cin >> x;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            x = -1;
        }
        switch (x)
        {
        case 0:
            cout << "zycze smacznego :) zamykam program \n";
            break;
        case 1:
            cout << "stworz przepis \n";
            cin >> *przepis_kucharski;
            If(przepis_kucharski, glowna);
            Save(przepis_kucharski);
            glowna.NadpiszPrzepis(przepis_kucharski);
            break;
        case 2:
            glowna.Search();
            break;
        case 3:
            do
            {
                system("CLS");
                show_me2();
                cin >> y;
                switch (y)
                {
                case 1:
                    lodowka.Delete();
                    cin >> lodowka;
                    break;
                case 2:
                    lodowka.ShowMe();
                    lodowka.Save();
                    break;
                case 3:
                    lodowka.WhatCanIDo(glowna);
                    lodowka.Save();
                    break;
                default:
                    cout << "podano znak ktory nie znajduje sie na liscie \n";
                    break;
                }
            } while (y != 0);
            break;
        case 4:
            glowna.SearchCal();
            break;
        case 5:
            glowna.SearchDieta();
            break;
        default:
            cout << "podano znak ktory nie znajduje sie na liscie \n";
            system("PAUSE");
            break;
        }
        delete przepis_kucharski;
    } while (x != 0);
    glowna.Save();
}