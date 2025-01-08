#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
using namespace std;
using namespace std::chrono;

int CUT_ROD(int p[], int n) {
    if (n == 0) return 0; // Zysk 0 dla długości 0

    int q = INT_MIN;
    for (int i = 1; i <= n; ++i) { //Długość pierwszego kawałka
        q = max(q, p[i - 1] + CUT_ROD(p, n - i)); // Max z ceny dla tego odcinka i jego pociętych wersji
    }
    return q;
}

int MEMORIZED_CUT_ROD(int p[], int r[], int s[], int n) {
    if (r[n] >= 0) return r[n]; // Zwróć wynik jeśli był już liczony
    int q;
    if (n == 0) {
        q = 0; // Zysk 0 dla długości 0
    } else {
        q = INT_MIN; //Ustawienie minimalnej wartości
        for (int i = 1; i <= n; ++i) {
            int możliwość = p[i - 1] + MEMORIZED_CUT_ROD(p, r, s, n - i);
            if (q < możliwość) {
                q = możliwość;
                s[n] = i; // Zapisujemy optymalne pierwsze cięcie
            }
        }
    }
    r[n] = q;
    return q;
}

void PRINT_SOLUTION1(int p[], int n) {
    int* r = new int[n + 1]; // Tablica maksymalnych zysków
    int* s = new int[n + 1]; // Tablica optymalnych cięć

    for (int i = 0; i <= n; ++i) {
        r[i] = INT_MIN; // Wypełniamy tablicę r minimalnymi wartościami
        s[i] = 0;       // Wypełniamy tablicę s zerami
    }
    int zysk= MEMORIZED_CUT_ROD(p, r, s, n);
    cout << "Maksymalny zysk: " << zysk << endl;
    cout << "Optymalne ciecia: ";
    while (n > 0) {
        cout << s[n] << ", ";
        n -= s[n];
    }
    cout << endl;

    delete[] r;
    delete[] s;
}

int EXT_BOT_UP_CUT_ROD(int p[], int n, int r[], int s[]) {
    r[0] = 0; // Cena 0 dla 0
    for (int j = 1; j <= n; ++j) {// Liczymy maksymalne zyski dla każdej długości
        int q = INT_MIN;
        for (int i = 1; i <= j; ++i) { // Pierwsze cięcia
            if (q < p[i - 1] + r[j - i]) {
                q = p[i - 1] + r[j - i];// Jeśli lepsze przypisz do q
                s[j] = i; // Zapisujemy długość cięcia
            }
        }
        r[j] = q; // Maksymalny zysk dla długości j
    }
    return r[n];
}

void PRINT_SOLUTION2(int p[], int n) {
    int* r = new int[n + 1]; // Tablica maksymalnych zysków
    int* s = new int[n + 1]; // Tablica optymalnych cięć

    cout << "Maksymalny zysk: " << EXT_BOT_UP_CUT_ROD(p, n, r, s) << endl;
    cout << "Optymalne ciecia: ";
    while (n > 0) {
        cout << s[n] << ", ";
        n -= s[n];
    }
    cout << endl;

    delete[] r;
    delete[] s;
}

int* Stwórz_Ceny(int n) {
    int* prices = new int[n];
    prices[0] = 2;
    for (int i = 1; i < n; ++i) {
        prices[i] = prices[i - 1] + (2+ (rand() % 3));
    }

    return prices;
}

int main() {

    srand(time(0));
    int wielkosci1[] = {4, 8, 12, 16, 20, 24};
    for (int n : wielkosci1) {
        int* p =Stwórz_Ceny(n);
        auto start = high_resolution_clock::now();
        CUT_ROD(p, n);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "Czas: " << duration.count() << " mikrosekund" << endl;
        delete[] p;
    }

    cout << " Z spamietywaniem " << endl;

    int wielkosci2[] = {4, 8, 12, 16, 20, 24, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000};
    for (int n : wielkosci2) {
        int* p =Stwórz_Ceny(n);
        int* r = new int[n + 1];
        int* s = new int[n + 1];
        for (int i = 0; i <= n; ++i) {
        r[i] = INT_MIN;
        s[i] = 0;
        }
        auto start = high_resolution_clock::now();
        MEMORIZED_CUT_ROD(p, r, s, n);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "Czas: " << duration.count() << " mikrosekund" << endl;
        delete[] p;
        delete[] r;
        delete[] s;
    }

    cout << " iteracyjna " << endl;

    for (int n : wielkosci2) {
        int* p =Stwórz_Ceny(n);
        int* r = new int[n + 1];
        int* s = new int[n + 1];
        auto start = high_resolution_clock::now();
        EXT_BOT_UP_CUT_ROD(p, n, r, s);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "Czas: " << duration.count() << " mikrosekund" << endl;
        delete[] p;
        delete[] r;
        delete[] s;
    }

    return 0;
}
