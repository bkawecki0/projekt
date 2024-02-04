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