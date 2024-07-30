#include"pk_projekt_naglówki.h"

using namespace std;

/** glowna funkcja MENU z dostępnynymi funkcjami programu oraz wywolujaca odwołująca się do class i ich metod z pliku pk_projekt_main.cpp zwraca 0*/
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
        system("CLS");
        show_me();   
        cout << "ilosc obiektow typu przepis:" << Przepis::it<<endl;
        Przepis* przepis_kucharski = (new Przepis);
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
            Przepis::it++;
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