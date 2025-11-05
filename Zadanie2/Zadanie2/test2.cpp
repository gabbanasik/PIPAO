#include <iostream>
#include "zlozal.h" 
using namespace std;


class AlgorytmWyszukiwaniaLiniowego : public Algorytm {
public:
    typedef string typ; // typ danych – mozesz zmienic np. na string
private:
    typ* dane_;
    typ wybrane_;
public:
    AlgorytmWyszukiwaniaLiniowego() : dane_(NULL) {}
    ~AlgorytmWyszukiwaniaLiniowego()
    { 
        if (dane_ != NULL) delete[] dane_;
    }

    string Nazwa() const 
    { 
        return string("Algorytm wyszukiwania liniowego");
    }

    void Ustaw(int n) {
        Algorytm::Ustaw(n);
   if (dane_!=NULL) delete[] dane_;
   dane_ = new typ[n];
   for (int i = 0; i < n; i++) {
       dane_[i] = string(50, 'a' + (i % 26)); 
   }
   wybrane_ = dane_[n / 2]; 
    }

    void Wykonaj() {
        int n = Rozmiar();
        typ* t = dane_;
        typ x = wybrane_;
        for (int i = 0; i < n; i++) {
            typ a = t[i];
            if (x == a) break;
        }
    }
};


class AlgorytmWyszukiwaniaBinarnego : public Algorytm {
public:
    typedef string typ;
private:
    typ* dane_;
    typ wybrane_;
public:
    AlgorytmWyszukiwaniaBinarnego() : dane_(NULL) {}
    ~AlgorytmWyszukiwaniaBinarnego() 
    { 
        if (dane_ != NULL) delete[] dane_; 
    }

    string Nazwa() const
    { 
        return string("wyszukiwania binarnego");
    }

    void Ustaw(int n) {
        Algorytm::Ustaw(n);
        if (dane_ != NULL) delete[] dane_;
        dane_ = new typ[n];
        for (int i = 0; i < n; i++) {
            dane_[i] = string(50, 'a' + (i % 26)); 
        }
        wybrane_ = dane_[n / 2]; 
    } //dla typu double wychodzily same zera, zmiana na string i porownywanie dlugiego stringa, wybrane_ ustawione na srodkowy wyraz tablicy bo szuak psutego stringa

    void Wykonaj() {
        int n = Rozmiar();
        typ* t = dane_;
        typ x = wybrane_;
        int i = 0, j = n - 1;
        while (i <= j) {
            int k = (i + j) / 2;
            typ a = t[k];
            if (x == a) break;
            if (x < a) j = k - 1; else i = k + 1;
        }
    }
};

int main() {
    {
        //n1 = 50000, n2 = 1000000, dn = 50000 oraz liczba powtórzeñ algorytmu : m = 1000 lub m = 10000
        //przy zwieks
        Maszyna APU(50000, 1000000, 50000, 10000);
        AlgorytmWyszukiwaniaLiniowego A;
        APU.Uruchom(A);
        APU.Wyswietl();
    }
    //przy liczbie powtorzen 1000 sa bardzo male czasy,delikatnie poowyzej zera(0,001)
    {
        Maszyna APU(50000, 1000000, 50000, 10000);
        AlgorytmWyszukiwaniaBinarnego A;
        APU.Uruchom(A);
        APU.Wyswietl();
    }
    return 0;
}
