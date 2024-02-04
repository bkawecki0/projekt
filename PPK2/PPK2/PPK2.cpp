#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <iomanip>

using namespace std;

struct Potrawa {
    int id_potrawy;
    string nazwa_potrawy;
    string kategoria_potrawy;
    double cena;
    string opis;
};

vector<Potrawa> odczytajBaze(const string& nazwaPliku) {
    vector<Potrawa> wynik;
    ifstream plik(nazwaPliku);
    if (plik) {
        string wiersz;
        while (getline(plik, wiersz)) {
            string s;
            stringstream ss(wiersz);

            vector<string> tokens;
            while (getline(ss, s, ';')) {
                tokens.push_back(s);
            }

            if (tokens.size() == 5) {
                wynik.push_back({ stoi(tokens[0]), tokens[1], tokens[2], stod(tokens[3]), tokens[4] });
            }
            
        }
        plik.close();
    }
    else {
        cout << "Blad: Plik nie jest otwarty" << endl;
    }
    return wynik;
}

void Napoje(const vector<Potrawa>& menu) {
    cout << "===Napoje===" << endl;
    cout << endl;
    for (const auto& potrawa : menu) {
        if (potrawa.kategoria_potrawy == " Napoje") {
            cout << potrawa.id_potrawy << ". " << potrawa.nazwa_potrawy << " " << potrawa.opis << "     " << potrawa.cena << " zl" << endl;
        }
    }
}

void Sniadania(const vector<Potrawa>& menu) {
    cout << "===Sniadania===" << endl;
    cout << endl;
    for (const auto& potrawa : menu) {
        if ((potrawa.kategoria_potrawy == " Sniadania") || (potrawa.kategoria_potrawy == " Sniadanie")){
            cout << potrawa.id_potrawy << ". " << potrawa.nazwa_potrawy << " " << potrawa.opis << "     " << potrawa.cena << " zl" << endl;
        }
    }
}

void Paragon(const vector<Potrawa>& zamowienie, const string& nazwaPliku, double& suma) {
    ofstream plik(nazwaPliku);
    if (plik) {
        for (const auto& potrawa : zamowienie) {
            plik << potrawa.nazwa_potrawy << " " << potrawa.kategoria_potrawy << " " << potrawa.cena << "zl" << endl;
            suma += potrawa.cena;
        }
        plik << endl;
        plik << "===================" << endl;
        plik << "Suma: " << suma << " zl" << endl;
        plik.close();
    }
}


int main() {
    auto menu = odczytajBaze("baza.txt");
    char wybor;
    vector<Potrawa> zamowienie;
    double suma = 0.0;
    char kontynuuj;

    for (;;) {
        cout << "===Menu programu===" << endl;
        cout << endl;
        cout << "1 Napoje" << endl;
        cout << "2 Sniadania" << endl;
        cout << "0 Wyczysc zamowienie" << endl;
        cout << "Q wylacz program" << endl;
        //cout << "R Zloz zamowienie" << endl;
        cin >> wybor;

        /*switch (wybor) {
        case '1':
            system("cls");
            Napoje(menu);
            cout << endl;
            break;
        case'2':
            system("cls");
            Sniadania(menu);
            cout << endl;
            break;
        case'0':
            system("cls");
            zamowienie.clear();
            cout << "Zamowienie zostalo wyczyszczone" << endl;
            cout << endl;
            break;
       /* case'r':
        case'R':
            system("cls");
            Paragon(zamowienie, "zamowienie.txt", suma);
            cout << "Zamowienie zostalo zlozone" << endl;
            exit(0);
            break;
        default:
            cout << "Nieprawidlowy wybor" << endl;
        } */

        if (wybor == '1') {
            system("cls");
            Napoje(menu);
            cout << endl;
            int idPotrawa;
            cout << "Podaj numer potrawy, ktora chcesz dodac do zamowienia: ";
            cin >> idPotrawa;
            system("cls");

            for (const auto& potrawa : menu) {
                if (potrawa.id_potrawy == idPotrawa) {
                    zamowienie.push_back(potrawa);
                    break;
                }
            }
            cout << "Czy chcesz zamawiac dalej?" << endl;
            cout << "K - zamawiaj dalej" << endl;
            cout << "R - zakoncz zamawiac" << endl;
            cin >> kontynuuj;
            system("cls");

            if (kontynuuj == 'r' || kontynuuj == 'R') {
                Paragon(zamowienie, "zamowienie.txt", suma);
                cout << "Zamowienie zostalo zlozone" << endl;
                return 0;
            }
        }

        else if (wybor == '2') {
            system("cls");
            Sniadania(menu);
            cout << endl;
            int idPotrawa;
            cout << "Podaj numer potrawy, ktora chcesz dodac do zamowienia: ";
            cin >> idPotrawa;
            system("cls");

            for (const auto& potrawa : menu) {
                if (potrawa.id_potrawy == idPotrawa) {
                    zamowienie.push_back(potrawa);
                    break;
                }
            }
            cout << "Czy chcesz zamawiac dalej?" << endl;
            cout << "K - zamawiaj dalej" << endl;
            cout << "R - zakoncz zamawiac" << endl;
            cin >> kontynuuj;
            system("cls");

            if (kontynuuj == 'r' || kontynuuj == 'R') {
                Paragon(zamowienie, "zamowienie.txt", suma);
                cout << "Zamowienie zostalo zlozone" << endl;
                return 0;
            }
        }

        else if (wybor == '0') {
            system("cls");
            zamowienie.clear();
            cout << "Zamowienie zostalo wyczyszczone" << endl;
            cout << endl;
        }
        else if (wybor == 'q' || wybor == 'Q') {
            exit(0);
        }
        else {
            system("cls");
            
            cout << "Nieprawidlowy wybor" << endl;
            cout << endl;
        }
    }
    return 0;
}