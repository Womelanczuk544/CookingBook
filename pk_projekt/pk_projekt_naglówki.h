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
    /** metoda wirtualna wyswietlaj�ca w konsoli parametry obiektu klasy produkt */
    virtual void Show() = 0;
    /** metoda wirtualna zwracaj�ca nazwe obiektu klasy produkt */
    virtual string GetNameV() = 0;
    /** metoda wirtualna zwracaj�ca pare zalezna od tego czy jest to obiekt klasy skladnik czy przyprawa */
    virtual pair<int, string> GetIleV() = 0;
    /** metoda wirtualna ustawiaj�ca parametry obiektu */
    virtual void SetIleV(int x) = 0;
};

/** klasa skladnik dziedziczy po klasie produkt zawiera elementy obiektu klasy skladnik oraz metody wykonywuj�ce operacje na pojedynczych obiektach z tej klasy*/
class Skladnik : public Produkt
{
    int ile;
    string jednostka;
public:
    /** konstruktor bezargumentowy klasy skladnik */
    Skladnik();
    /** konstruktor wieloargumentowy klasy skladnik */
    Skladnik(string p_nazwa, int p_ile, string p_jednostka);
    /** operator << wy�wietlaj�cy wszystkie informacje na temat obiektu klasy skladnik  */
    friend ostream& operator << (ostream& s, Skladnik& x);
    /** metoda zwracaj�ca wszystkie informacje o skladniku w jednym stringu */
    string Get();
    /** metoda wy�wietlaj�ca wszystkie informacje na temat obiektu klasy skladnik  */
    void Show();
    /** metoda zwracaj�ca nazwe skladnika */
    string GetName();
    /** metoda zwracaj�ca ilosc skladnika skladnika */
    int GetIle();
    /** metoda zwracaj�ca nazwe skladnika korzystajaca z polimorfizmu */
    string GetNameV();
    /** metoda zwracaj�ca pare ilosc oraz nazwa klasy w tym wypadku skladnik*/
    pair<int, string> GetIleV();
    /** metoda ustawiajaca ilosc w obiekcie skladnik */
    void SetIle(int x);
    /** metoda ustawiajaca ilosc w obiekcie skladnik korzystaj�ca z polimorfizmu */
    void SetIleV(int x);
    /** destruktor obiektu klasy skladnik */
    ~Skladnik();
};

/** klasa przyprawa dziedziczy po klasie produkt zawiera elementy obiektu klasy skladnik oraz metody wykonywuj�ce operacje na pojedynczych obiektach z tej klasy*/
class Przyprawa : public Produkt
{
    string intensywnosc, smak;
public:
    /** konstruktor bezargumentowy klasy przyprawa */
    Przyprawa();
    /** konstruktor wieloargumentowy klasy przyprawa */
    Przyprawa(string p_nazwa, string p_intensywnosc, string p_smak);
    /** konstruktor kopiuj�cy klasy przyprawa */
    Przyprawa(Przyprawa& x);
    /** operator << wy�wietlaj�cy wszystkie informacje na temat obiektu klasy przyprawa  */
    friend ostream& operator << (ostream& s, Przyprawa& x);
    /** metoda zwracaj�ca wszystkie informacje o przyprawie w jednym stringu */
    string Get();
    /** metoda wy�wietlaj�ca wszystkie informacje na temat obiektu klasy przyprawa  */
    void Show();
    /** metoda zwracaj�ca nazwe przyprawy */
    string GetName();
    /** metoda zwracaj�ca nazwe przyprawy korzystajaca z polimorfizmu */
    string GetNameV();
    /** metoda zwracaj�ca pare 0 oraz nazwa klasy w tym wypadku przyprawa*/
    pair<int, string> GetIleV();
    /** metoda ustawiajaca ilosc zawsze na zero w obiekcie przyprawa korzystaj�ca z polimorfizmu */
    void SetIleV(int x);
};

/** klasa Przepis zawiera poszczeg�lne elementy obiektu oraz metody wykonywuj�ce operacje na pojedynczych obiektach z tej klasy*/
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
    /** operator >> wczytuj�cy dane podawane w konsoli do obiekty klasy przepis */
    friend istream& operator >> (istream& s, Przepis& x);
    /** operator << wy�wietlaj�cy wszystkie informacje na temat obiektu klasy przepis  */
    friend ostream& operator << (ostream& s, Przepis& x);
    /** metoda wy�wietlaj�ca przepis */
    void Wypisz();
    /** metoda zwracaj�ca nazwe obiektu klasy przepis */
    string GetName();
    /** metoda zwracaj�ca nazwe diety obiektu klasy przepis */
    string GetDiet();
    /** metoda zwracaj�ca opis przygotowania dania z obiektu klasy przepis */
    vector<string> GetOpis();
    /** metoda zwracaj�ca wszystkie obiekty kalsy skladnik nale��ce do obiektu klasy przepis */
    vector<shared_ptr<Skladnik>> GetSkladnik();
    /** metoda zwracaj�ca wszystkie obiekty kalsy przyprawa nale��ce do obiektu klasy przepis */
    vector<shared_ptr<Przyprawa>> GetPrzyprawy();
    /** metoda zwracaj�ca wartosc kaloryczna obiektu klasy przepis */
    int GetCal();
    /** metoda ustawiaj�ca nazwe obiektu klasy przepis */
    void Set(string& s);
    /** zaprzyja�nienie funkcji save z klasa przepis */
    friend void Save(Przepis*& x);
    /** dekonstruktor klasy przepis */
    ~Przepis();
};

/** klasa Dieta zawiera poszczeg�lne elementy obiektu oraz metody wykonywuj�ce operacje na pojedynczych obiektach z tej klasy*/
class Dieta
{
    string nazwa_diety;
    vector<shared_ptr<Przepis>> wszystkie_z_diety;
public:
    /** konstruktor bezargumentowy klasy dieta */
    Dieta();
    /** konstruktor wieloargumentowy klasy dieta */
    Dieta(string p_nazwa_diety, vector<shared_ptr<Przepis>> p_wszystkie_z_diety);
    /** metoda zwracaj�ca nazwe obiektu klasy dieta */
    string Get();
    /** metoda zwracaj�ca wszystkie obiekty klasy przepis nale��ce do obiektu klasy dieta */
    vector<shared_ptr<Przepis>> GetVec();    
    /** metoda dodaj�ca wska�nik na nowy nowy obiekt klasy przepis do wektoru przepis�w obiektu z kalsy dieta */
    void push(Przepis*& x);
    /** metoda dodaj�ca nowy obiekt klasy przepis do wektoru przepis�w obiektu z kalsy dieta */
    void push1(Przepis& x);
};

/** funkcja zwracjaj�ca modu� z liczby*/
int Modul(int& x);

/** klasa Bazadanych g��wna klasa zawiera poszczeg�lne elementy obiektu oraz metody wykonywuj�ce operacje na pojedynczych obiektach z tej klasy*/
class BazaDanych
{
    vector<shared_ptr<Dieta>> diety;
    vector<shared_ptr<Przepis>> przepisy;
public:
    /** konstruktor bezargumentowy klasy Bazadanych */
    BazaDanych();
    /** metoda dopisuj�ca obiekt klasy przepis do wektora obiektow klasy przepis oraz wektora przepisow z klasy dieta */
    void NadpiszPrzepis(Przepis*& x);
    /** metoda ladujaca perzepisy z pliku i dodajaca je na koniec wektora przepisow w obiekcie klasy dieta oraz obiekcie klasy bazadanych */
    void Load();
    /** metoda zapisujaca bazedanych do pliku  */
    void Save();
    /** metoda wyszukujaca obiekt klasy przepis po nazwie*/
    void Search();
    /** metoda wyszukujaca obiekt klasy przepis po kaloryczno�ci*/
    void SearchCal();
    /** metoda segreguj�ca obiekty klasy ze wzgledu na przypisana diete*/
    void SearchDieta();
    /** metoda zwracajaca wektor obiekto klasy przepis z obiektu klasy bazadanych*/
    vector<shared_ptr<Przepis>> Get();
};

/** klasa spizarka pomocnicza klasa zawiera poszczeg�lne elementy obiektu oraz metody wykonywuj�ce operacje na pojedynczych obiektach z tej klasy */
class Spizarka
{
    vector<shared_ptr<Skladnik>> skladniki_dostepne;
    vector<shared_ptr<Przyprawa>> przyprawy_dostepne;
    vector<shared_ptr<Produkt>> produkty;
public:
    /** konstruktor bezargumentowy klasy spizarka */
    Spizarka();
    /** operator >> wczytuj�cy dane podawane w konsoli do odpowiednich wektor�w obiekt�w klasy klasy produkt, skladnik i przyprawa nalezacych do obiektu klasy spizarka */
    friend istream& operator >> (istream& s, Spizarka& x);
    /** metoda zapisujaca skladniki i przyprawy do pliku */
    void Save();
    /** metoda wczytuj�c skladniki i przyprawy oraz produkty z pliku  */
    void LoadFridge();
    /** metoda wyswietlajaca wszystkie skladniki i produkty moze tez je dodawac i usuwac ale pojedynczo */
    void ShowMe();
    /** metoda pokazujaca nam ktore przepisy mozna wykonac przy obecnym stanie spizarki */
    void WhatCanIDo(BazaDanych& x);
    /** metoda czyszcz�ca wektory obiektu klasy spizarka  */
    void Delete();
};

/** funkcja wy�wietlaj�ca opcjie z MENU g��wnego dla u�ytkownika */
void show_me();

/** funkcja wy�wietlaj�ca opcjie z MENU spi�arki dla u�ytkownika */
void show_me2();

/** funkcja zapisuj�ca pojedynczy przepis do pliku */
void Save(Przepis*& x);

/** funkcja sprawdzj�ca czy podana nazwa przepisu znajduje si� ju� w bazie danych je�li tak to prosi u�ytkownika o zmiane nazwy przepisu */
void If(Przepis*& x, BazaDanych& y);

#endif 

