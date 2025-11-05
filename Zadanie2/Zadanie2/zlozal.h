/********************
 *
 * Plik naglowkowy z deklaracjami klas
 * przeznaczonymi do badania zlozonosci 
 * dowolnych algorytmow w postaci czasu 
 * w funkcji rozmiaru danych wejsciowych
 *
 * Uwaga: Program nalezy budowac w solucji 
 * o konfiguracji Release dla platformy x86
 *
 */
#ifndef ZLOZAL_H_
#define ZLOZAL_H_

// dodatkowa konfiguracja dla kompilatora MSVC
//
#pragma warning(disable:4244)
#pragma warning(disable:4996 4005)
#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#ifndef __cplusplus
# error C++ compiler required
#endif

// biblioteka standardowa jezyka C++
//
#include <string>

// Klasa bazowa dowolnych algorytmow
// ktorych czas wykonania zalezy od
// jednego parametru 'n' czyli rozmiaru
// struktury danych na wejsciu algorytmu
//
class Algorytm {
  int n_; // rozmiar wejscia algorytmu
 private: // kopiowanie obiektu algorytmu jest niedostepne i niezdefiniowane
  Algorytm(Algorytm &);
  void operator=(Algorytm &);
 public:
  Algorytm(); // tworzy nowy obiekt algorytmu, na poczatku bez wejscia
  virtual ~Algorytm(); // wirtualny destruktor umozliwia poprawne usuwanie obiektow algorytmu
  
  virtual std::string Nazwa() const = 0; // zwraca nazwe wlasna algorytmu, 
                                         // metoda musi byc zdefiniowana w klasach pochodnych
  
  int Rozmiar() const // zwraca biezacy rozmiar wejscia algorytmu
  { return n_; }
  
  virtual void Ustaw(int n); // ustawia biezaca strukture danych wejsciowych algorytmu dla podanego rozmiaru ich struktury 'n'
                             // uwaga: metoda moze byc redefiniowana (pokryta) w klasach pochodnych

  virtual void Wykonaj() = 0; // glowna procedura wykonawcza obiektu algorytmu ktora wykonuje algorytm dla biezacej struktury danych wejsciowych
                              // uwaga: metoda musi byc zdefiniowana w klasach pochodnych
};

// Pojedyncza klasa reprezentujaca wirtualne urzadzenie
// przeznaczone do uruchomienia procedury przetwarzajacej 
// podany algorytm w ramach badania zlozonosci algorytmu 
// poprzez pomiar czasu jego wykonania dla kolejnych danych
// 
class Maszyna {
  int n1_, n2_, dn_; // przedzial zmiennosci rozmiaru wejscia dla badanego algorytmu
  int ilczas_; // liczba kolejnych pomiarow czasu w badaniu zlozonosci
  int iliter_; // liczba powtorzen wykonywania algorytmu w jednym pomiarze
  double *czas_; // tablica wynikow pomiaru czasu dla kolejnych rozmiarow wejscia
  std::string alg_; // nazwa przetwarzanego algorytmu
 public:
  Maszyna(int n1,int n2,int dn,int m=100); // konstruktor obiektu maszyny 
  ~Maszyna(); // destruktor obiektu maszyny
  
  void Uruchom(Algorytm &Alg); // uruchamia podany algorytm i wykonuje badanie
  void Wyswietl() const; // wyswietla wyniki badania zlozonosci czasowej
};  

#endif /* koniec pliku naglowkowego 'zlozal' */
