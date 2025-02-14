/** @file */
#pragma once
#ifndef KLASY
#define KLASY
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
/** klasa abstakcyjna Produkt zawiera tylko elementy typu protected oraz public*/
class Produkt
{
protected:
    string nazwa;
public:
    /** metoda wirtualna wyswietlająca w konsoli parametry obiektu klasy produkt */
    virtual void Show() = 0;
    /** metoda wirtualna zwracająca nazwe obiektu klasy produkt */
    virtual string GetNameV() = 0;
    /** metoda wirtualna zwracająca pare zalezna od tego czy jest to obiekt klasy skladnik czy przyprawa */
    virtual pair<int, string> GetIleV() = 0;
    /** metoda wirtualna ustawiająca parametry obiektu */
    virtual void SetIleV(int x) = 0;
};

/** klasa skladnik dziedziczy po klasie produkt zawiera elementy obiektu klasy skladnik oraz metody wykonywujące operacje na pojedynczych obiektach z tej klasy*/
class Skladnik : public Produkt
{
    int ile;
    string jednostka;
public:
    /** konstruktor bezargumentowy klasy skladnik */
    Skladnik();
    /** konstruktor wieloargumentowy klasy skladnik */
    Skladnik(string p_nazwa, int p_ile, string p_jednostka);
    /** operator << wyświetlający wszystkie informacje na temat obiektu klasy skladnik  */
    friend ostream& operator << (ostream& s, Skladnik& x);
    /** metoda zwracająca wszystkie informacje o skladniku w jednym stringu */
    string Get();
    /** metoda wyświetlająca wszystkie informacje na temat obiektu klasy skladnik  */
    void Show();
    /** metoda zwracająca nazwe skladnika */
    string GetName();
    /** metoda zwracająca ilosc skladnika skladnika */
    int GetIle();
    /** metoda zwracająca nazwe skladnika korzystajaca z polimorfizmu */
    string GetNameV();
    /** metoda zwracająca pare ilosc oraz nazwa klasy w tym wypadku skladnik*/
    pair<int, string> GetIleV();
    /** metoda ustawiajaca ilosc w obiekcie skladnik */
    void SetIle(int x);
    /** metoda ustawiajaca ilosc w obiekcie skladnik korzystająca z polimorfizmu */
    void SetIleV(int x);
    /** destruktor obiektu klasy skladnik */
    ~Skladnik();
};

/** klasa przyprawa dziedziczy po klasie produkt zawiera elementy obiektu klasy skladnik oraz metody wykonywujące operacje na pojedynczych obiektach z tej klasy*/
class Przyprawa : public Produkt
{
    string intensywnosc, smak;
public:
    /** konstruktor bezargumentowy klasy przyprawa */
    Przyprawa();
    /** konstruktor wieloargumentowy klasy przyprawa */
    Przyprawa(string p_nazwa, string p_intensywnosc, string p_smak);
    /** konstruktor kopiujący klasy przyprawa */
    Przyprawa(Przyprawa& x);
    /** operator << wyświetlający wszystkie informacje na temat obiektu klasy przyprawa  */
    friend ostream& operator << (ostream& s, Przyprawa& x);
    /** metoda zwracająca wszystkie informacje o przyprawie w jednym stringu */
    string Get();
    /** metoda wyświetlająca wszystkie informacje na temat obiektu klasy przyprawa  */
    void Show();
    /** metoda zwracająca nazwe przyprawy */
    string GetName();
    /** metoda zwracająca nazwe przyprawy korzystajaca z polimorfizmu */
    string GetNameV();
    /** metoda zwracająca pare 0 oraz nazwa klasy w tym wypadku przyprawa*/
    pair<int, string> GetIleV();
    /** metoda ustawiajaca ilosc zawsze na zero w obiekcie przyprawa korzystająca z polimorfizmu */
    void SetIleV(int x);
};

/** klasa Przepis zawiera poszczególne elementy obiektu oraz metody wykonywujące operacje na pojedynczych obiektach z tej klasy*/
class Przepis
{
    string nazwa, dieta;
    vector<shared_ptr<Skladnik>> skladniki;
    vector<shared_ptr<Przyprawa>> przyprawy;
    vector<string> opis;
    int kalorycznosc;
public:
    static int it;
    /** konstruktor bezargumentowy klasy przepis */
    Przepis();
    /** konstruktor wieloargumentowy klasy przepis */
    Przepis(string p_nazwa, vector<shared_ptr<Skladnik>> p_skladniki, vector<shared_ptr<Przyprawa>> p_przyprawy, vector<string> p_opis, string p_dieta, int p_kalorycznosc);
    /** operator >> wczytujący dane podawane w konsoli do obiekty klasy przepis */
    friend istream& operator >> (istream& s, Przepis& x);
    /** operator << wyświetlający wszystkie informacje na temat obiektu klasy przepis  */
    friend ostream& operator << (ostream& s, Przepis& x);
    /** metoda wyświetlająca przepis */
    void Wypisz();
    /** metoda zwracająca nazwe obiektu klasy przepis */
    string GetName();
    /** metoda zwracająca nazwe diety obiektu klasy przepis */
    string GetDiet();
    /** metoda zwracająca opis przygotowania dania z obiektu klasy przepis */
    vector<string> GetOpis();
    /** metoda zwracająca wszystkie obiekty kalsy skladnik należące do obiektu klasy przepis */
    vector<shared_ptr<Skladnik>> GetSkladnik();
    /** metoda zwracająca wszystkie obiekty kalsy przyprawa należące do obiektu klasy przepis */
    vector<shared_ptr<Przyprawa>> GetPrzyprawy();
    /** metoda zwracająca wartosc kaloryczna obiektu klasy przepis */
    int GetCal();
    /** metoda ustawiająca nazwe obiektu klasy przepis */
    void Set(string& s);
    /** zaprzyjaźnienie funkcji save z klasa przepis */
    friend void Save(Przepis*& x);
    /** dekonstruktor klasy przepis */
    ~Przepis();
};

/** klasa Dieta zawiera poszczególne elementy obiektu oraz metody wykonywujące operacje na pojedynczych obiektach z tej klasy*/
class Dieta
{
    string nazwa_diety;
    vector<shared_ptr<Przepis>> wszystkie_z_diety;
public:
    /** konstruktor bezargumentowy klasy dieta */
    Dieta();
    /** konstruktor wieloargumentowy klasy dieta */
    Dieta(string p_nazwa_diety, vector<shared_ptr<Przepis>> p_wszystkie_z_diety);
    /** metoda zwracająca nazwe obiektu klasy dieta */
    string Get();
    /** metoda zwracająca wszystkie obiekty klasy przepis należące do obiektu klasy dieta */
    vector<shared_ptr<Przepis>> GetVec();    
    /** metoda dodająca wskaźnik na nowy nowy obiekt klasy przepis do wektoru przepisów obiektu z kalsy dieta */
    void push(Przepis*& x);
    /** metoda dodająca nowy obiekt klasy przepis do wektoru przepisów obiektu z kalsy dieta */
    void push1(Przepis& x);
};

/** funkcja zwracjająca moduł z liczby*/
int Modul(int& x);

/** klasa Bazadanych główna klasa zawiera poszczególne elementy obiektu oraz metody wykonywujące operacje na pojedynczych obiektach z tej klasy*/
class BazaDanych
{
    vector<shared_ptr<Dieta>> diety;
    vector<shared_ptr<Przepis>> przepisy;
public:
    /** konstruktor bezargumentowy klasy Bazadanych */
    BazaDanych();
    /** metoda dopisująca obiekt klasy przepis do wektora obiektow klasy przepis oraz wektora przepisow z klasy dieta */
    void NadpiszPrzepis(Przepis*& x);
    /** metoda ladujaca perzepisy z pliku i dodajaca je na koniec wektora przepisow w obiekcie klasy dieta oraz obiekcie klasy bazadanych */
    void Load();
    /** metoda zapisujaca bazedanych do pliku  */
    void Save();
    /** metoda wyszukujaca obiekt klasy przepis po nazwie*/
    void Search();
    /** metoda wyszukujaca obiekt klasy przepis po kaloryczności*/
    void SearchCal();
    /** metoda segregująca obiekty klasy ze wzgledu na przypisana diete*/
    void SearchDieta();
    /** metoda zwracajaca wektor obiekto klasy przepis z obiektu klasy bazadanych*/
    vector<shared_ptr<Przepis>> Get();
};

/** klasa spizarka pomocnicza klasa zawiera poszczególne elementy obiektu oraz metody wykonywujące operacje na pojedynczych obiektach z tej klasy */
class Spizarka
{
    vector<shared_ptr<Skladnik>> skladniki_dostepne;
    vector<shared_ptr<Przyprawa>> przyprawy_dostepne;
    vector<shared_ptr<Produkt>> produkty;
public:
    /** konstruktor bezargumentowy klasy spizarka */
    Spizarka();
    /** operator >> wczytujący dane podawane w konsoli do odpowiednich wektorów obiektów klasy klasy produkt, skladnik i przyprawa nalezacych do obiektu klasy spizarka */
    friend istream& operator >> (istream& s, Spizarka& x);
    /** metoda zapisujaca skladniki i przyprawy do pliku */
    void Save();
    /** metoda wczytując skladniki i przyprawy oraz produkty z pliku  */
    void LoadFridge();
    /** metoda wyswietlajaca wszystkie skladniki i produkty moze tez je dodawac i usuwac ale pojedynczo */
    void ShowMe();
    /** metoda pokazujaca nam ktore przepisy mozna wykonac przy obecnym stanie spizarki */
    void WhatCanIDo(BazaDanych& x);
    /** metoda czyszcząca wektory obiektu klasy spizarka  */
    void Delete();
};

/** funkcja wyświetlająca opcjie z MENU głównego dla użytkownika */
void show_me();

/** funkcja wyświetlająca opcjie z MENU spiżarki dla użytkownika */
void show_me2();

/** funkcja zapisująca pojedynczy przepis do pliku */
void Save(Przepis*& x);

/** funkcja sprawdzjąca czy podana nazwa przepisu znajduje się już w bazie danych jeśli tak to prosi użytkownika o zmiane nazwy przepisu */
void If(Przepis*& x, BazaDanych& y);

#endif 

