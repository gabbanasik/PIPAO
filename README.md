#include "Wybor.h"
#include"zbior.h"
#include<list>
#include<random>
using namespace std;

/*
* Uwaga: Zadania kod rozwiazania zaania umieszczać pomiędzy #ifdef a #endif.
*/

#ifdef Zad_7_1
void test1()
{
	Zbior A(5,0,10);
	Zbior B(6, 0, 10);
	cout << static_cast<int>(A)<<endl;
	cout << static_cast<int>(B)<<endl;
	A = B;
	cout << static_cast<int>(A)<<endl;
	cout << static_cast<int>(B)<<endl;
	if (A.getRozmiar() == B.getRozmiar())
	{
		cout << "Operator zadzialal!" << endl;

	}
	else
	{
		cout << "Cos poszlo nie tak.." << endl;
	}
}
struct CzyWLiczbie {
	int c, d;

	CzyWLiczbie(int c_, int d_) : c(c_), d(d_) {}

	bool operator()(const Zbior& z) const {
		int n = static_cast<int>(z);  // ✔ jawna, dozwolona konwersja
		return (n >= c && n <= d);
	}
};
class Sprawdzana
{
	int m_value;
public:
	Sprawdzana(int val) :m_value(val) {}
	bool operator()(int val) { return val >= 5 && val <= 8; }
};

int main()
{
	double c, d;
	do {
		cout << "Podaj c: ";
		cin >> c;
		cout << "Podaj d: ";
		cin >> d;
	} while (c >= d);

	Zbior z(5, 0, 10);

	CzyWLiczbie funktor((int)c, (int)d);

	if (funktor(z))
		cout << "Liczba elementow jest w zakresie\n";
	else
		cout << "Liczba elementow poza zakresem\n";
	list<Zbior> lista;
	list<Zbior>::iterator iter = lista.begin();

	std::random_device rd;
	std::mt19937 gen(rd());

	// losowa liczba Zbiorów
	std::uniform_int_distribution<int> LiczInst(5, 10);
	int ileZbiorow = LiczInst(gen);

	// losowa liczba elementów w Zbiorze
	std::uniform_int_distribution<int> LiczEle(2, 17);

	// losowy przedział
	std::uniform_real_distribution<double> Przedzial(0.0, 20.0);

	for (int i = 0; i < ileZbiorow; i++)
	{
		int liczElem = LiczEle(gen);

		double a = Przedzial(gen);
		double b = Przedzial(gen);

		// upewniamy się że a < b
		if (a > b) std::swap(a, b);

		// tworzysz Zbior
		Zbior z(liczElem, a, b);

		// wstawiasz przed iter — czyli na początek listy
	
		++iter; // przesuwasz iter za wstawiony element
	}


	CzyWLiczbie predykat(5, 8);
	int ile_w_zakresie = count_if(lista.begin(), lista.end(), predykat);
	cout << "Zbiory o liczbie elementow w zakresie [5,8]: " << ile_w_zakresie << endl;

	// 2️⃣ Zliczamy Zbiory o nieparzystej liczbie elementów przy użyciu lambdy
	int ile_nieparzystych = count_if(lista.begin(), lista.end(),
		[](const Zbior& z) {
			int n = static_cast<int>(z); // jawna konwersja
			return n % 2 == 1;
		});
	cout << "Zbiory o nieparzystej liczbie elementow: " << ile_nieparzystych << endl;
}


#include "zbior.h"
#include <new>
#include <random>
#include <cassert>

void Zbior::alokuj(int n)
{
	assert(n > 0);
	m_elementy = new(std::nothrow) double[n] {};
	m_liczbaElementow = n;

}
void Zbior::zwolnij()
{
	delete[] m_elementy;
}
Zbior::Zbior(const Zbior& org)
	: m_dolnaGranica(org.m_dolnaGranica), m_gornaGranica(org.m_gornaGranica)
{
	alokuj(org.m_liczbaElementow);
	for (size_t i = 0; i < org.m_liczbaElementow; i++)
		m_elementy[i] = org.m_elementy[i];
}

Zbior::Zbior(size_t liczElem, double dGran, double gGran)
	: m_dolnaGranica(dGran), m_gornaGranica(gGran)
{
	alokuj(liczElem);
	std::uniform_real_distribution<double> zakres(dGran, gGran);
	std::random_device generator;
	for (int elem = 0; elem < liczElem; elem++)
		m_elementy[elem] = zakres(generator);
}
 Zbior:: operator int()const
{
	return static_cast<int>(m_liczbaElementow);
}
Zbior Zbior:: operator+(const Zbior& rhs)
{
	
	double suma = this->m_liczbaElementow + rhs.m_liczbaElementow;
	double beg = (this->m_dolnaGranica < rhs.m_dolnaGranica) ? this->m_dolnaGranica : rhs.m_dolnaGranica;
	double end = (this->m_gornaGranica > rhs.m_gornaGranica) ? this->m_gornaGranica : rhs.m_gornaGranica;
	std::uniform_real_distribution<double> zakres(beg, end);
	std::random_device generator;
	for (int elem = 0; elem < suma; elem++)
		m_elementy[elem] = zakres(generator);
	return Zbior(suma, beg, end);
}

Zbior::~Zbior()
{
	zwolnij();
}
Zbior& Zbior::operator=(const Zbior& org)
{
	if (this != &org)
	{
		bool roznyRozmiar = this->m_liczbaElementow != org.m_liczbaElementow;
		if (this->m_elementy != nullptr && roznyRozmiar)
		{
			zwolnij();
		}
		if (org.m_elementy != nullptr)
		{
			if (roznyRozmiar) 
				alokuj(org.m_liczbaElementow);
			for (int i = 0; i < org.m_liczbaElementow; i++)
				this->m_elementy[i] = org.m_elementy[i];
		 }
			this->m_liczbaElementow = org.m_liczbaElementow;
    }
 return *this;
}
double Zbior::getRozmiar()
{
	return m_liczbaElementow;
}

}

#endif
