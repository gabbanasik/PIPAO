#include <iostream> // wlaczenie plikow biblioteki standardowej
#include "zlozal.h" // wlaczenie pliku z klasami do badania zlozonosci algorytmow
using namespace std;

//
// Klasy pochodne definiujace konkretne algorytmy
//

class AlgorytmSortowaniaBabelkowego : public Algorytm { // algorytm posiada zlozonosc czasowa klasy O(n^2)
 public:
  typedef double typ;
 private: 
  typ *dane_;
 public:
  AlgorytmSortowaniaBabelkowego(): dane_(NULL)
  {}
  
  ~AlgorytmSortowaniaBabelkowego()
  {
   if (dane_!=NULL) delete[] dane_;
  }
   
  string Nazwa() const
  {
   return string("sortowania babelkowego"); 
  }
  
  void Ustaw(int n)
  {
   Algorytm::Ustaw(n);
   if (dane_!=NULL) delete[] dane_;
   dane_ = new typ[n];
   for (int i=0; i<n; i++) dane_[i]=1.2345*(n-i);
  }

  void Wykonaj();
};

void AlgorytmSortowaniaBabelkowego::Wykonaj() 
{
 int n = Rozmiar();
 typ *t = dane_;
 bool zmiana;
 do {
  zmiana = false;
  n = n-1;
  for (int i=0; i<n; i++)
  if (t[i] > t[i+1]) {
   typ pom = t[i];
   t[i] = t[i+1];
   t[i+1] = pom;
   zmiana = true;
  }
 } while (zmiana);
}

class AlgorytmSortowaniaSzybkiego : public Algorytm { // algorytm posiada zlozonosc czasowa klasy O(n*log n)
 public:
  typedef double typ;
 private: 
  typ *dane_;
 public:
  AlgorytmSortowaniaSzybkiego(): dane_(NULL)
  {}
  
  ~AlgorytmSortowaniaSzybkiego()
  {
   if (dane_!=NULL) delete[] dane_;
  }
   
  string Nazwa() const
  {
   return string("sortowania szybkiego"); 
  }
  
  void Ustaw(int n)
  {
   Algorytm::Ustaw(n);
   if (dane_!=NULL) delete[] dane_;
   dane_ = new typ[n];
   for (int i=0; i<n; i++) dane_[i]=1.2345*(n-i);
  }

  void Wykonaj()
  {
   int n = Rozmiar();
   typ *t = dane_;
   quick_sort_(t, 0, n-1);   
  }

  private: static void quick_sort_(typ *t, int il, int ip);
};

void AlgorytmSortowaniaSzybkiego::quick_sort_(typ *t, int il, int ip)
{
 int i,j;
 typ x;
 x = t[(il+ip)/2];
 i = il;
 j = ip;
 do {
  while (t[i] < x) ++i;
  while (t[j] > x) --j;
  if (i <= j) {
   typ pom = t[i];
   t[i] = t[j];
   t[j] = pom;
   ++i; --j;
  }
 } while (i < j);
 if (il < j) quick_sort_(t, il, j);
 if (ip > i) quick_sort_(t, i, ip);
} 

//
// Program z przykladami tworzenia algorytmu A i jego
// badania w maszynie APU do przetwarzania algorytmow
//

int main()
{
 {
  Maszyna APU(1000, 10000, 100);
  AlgorytmSortowaniaBabelkowego A;
  APU.Uruchom(A);
  APU.Wyswietl();
 }{
  Maszyna APU(1000, 10000, 100);
  AlgorytmSortowaniaSzybkiego A;
  APU.Uruchom(A);
  APU.Wyswietl();
 }
 return 0;
}
