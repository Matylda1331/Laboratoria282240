#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <chrono>
using namespace std;
using namespace std::chrono;

void RECURSIVE_ACTIVITY_SELECTOR2(int s[], int f[], int k, int zajecia[], int &ile) {
    int m = k - 1;

    while (m > 0 && f[m] > s[k]) {// Szukamy zajęcia, które kończy się przed rozpoczęciem zajęcia k
        m--;
    }
    if (m > 0) { // Jeśli znaleziono pasujące zajęcie
        zajecia[ile++] = m; // Dodajemy indeks zajęcia do wyniku
        RECURSIVE_ACTIVITY_SELECTOR2(s, f, m, zajecia, ile); // Rekurencyjnie wybieramy wcześniejsze zajęcia
    }
}

void WYNIK_R_A_S2(int s[], int f[], int n) {
    int zajecia[n];
    int ile = 0;
    RECURSIVE_ACTIVITY_SELECTOR2(s, f, n, zajecia, ile);
    cout << "Wybrane zajecia (rekurencyjnie): ";
    for (int i = ile - 1; i >= 0; i--) { // Wyświetlamy od końca
        cout << zajecia[i] << " ";
    }
    cout << endl;
}

void ACTIVITY_SELECTOR2(int s[], int f[], int n, int zajecia[], int &ile) {
    zajecia[ile++] = n - 1; // Ostatnie zajęcie przed fikcyjnym jest zawsze wybrane
    int k = n - 1;

    for (int m = n - 2; m >= 1; m--) {// Iterujemy od końca i wybieramy zajęcia, które kończą się przed rozpoczęciem ostatnio wybranego zajęcia
        if (f[m] <= s[k]) {
            zajecia[ile++] = m; // Dodajemy indeks zajęcia do wyniku
            k = m;
        }
    }
}

void WYNIK_A_S2(int s[], int f[], int n) {
    int zajecia[n]; // Tablica zawierająca indeksy zajęć pasujących
    int ile = 0;    // Liczba wybranych zajęć

    ACTIVITY_SELECTOR2(s, f, n, zajecia, ile);

    cout << "Wybrane zajecia (iteracyjnie): ";
    for (int i = ile - 1; i >= 0; i--) { // Wyświetlamy w odwrotnej kolejności
        cout << zajecia[i] << " ";
    }
    cout << endl;
}

void GENERUJ_s(int s[], int n) {
    s[0] = 0;
    for (int i = 1; i <= n; i++) {
        s[i] = rand() % (n * 2);
    }
    s[n + 1] = INT_MAX;
    sort(s + 1, s + n + 1);
}

void GENERUJ_f(int f[], int s[], int n) {
    f[0] = INT_MIN;
    for (int i = 1; i <= n; i++) {
        f[i] = s[i] + rand() % 100 + 1;
    }
    f[n + 1] = 0;
}

int main() {
    // Tablice zajęć (ostatnie i pierwsze zajęcie jest fikcyjne)
    int s[] = { 0, 2, 3, 4, 5, 8, INT_MAX};
    int f[] = {INT_MIN, 3, 6, 5, 6, 9, 0};
    int n = 6;//o 1 więcej niż zajęć bo ostatnie fikcyjne
    WYNIK_R_A_S2(s, f, n);
    WYNIK_A_S2(s, f, n);

    srand(time(0));
    int wielkosci[] = {1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000};
    for (int n : wielkosci) {
        int s[n+1];
        int f[n+1];
        GENERUJ_s(s, n);
        GENERUJ_f(f, s, n);
        int zajecia[n];
        int ile = 0;
        auto start_rec = high_resolution_clock::now();
        RECURSIVE_ACTIVITY_SELECTOR2(s, f, n + 1, zajecia, ile);
        auto stop_rec = high_resolution_clock::now();
        auto duration_rec = duration_cast<microseconds>(stop_rec - start_rec);
        cout << "Czas dla rekursji: " << duration_rec.count() << " mikrosekund" << endl;

        int zajecia2[n];
        int ile2 = 0;
        auto start_iter = high_resolution_clock::now();
        ACTIVITY_SELECTOR2(s, f, n, zajecia2, ile2);
        auto stop_iter = high_resolution_clock::now();
        auto duration_iter = duration_cast<microseconds>(stop_iter - start_iter);
        cout << "Czas iteracji: " << duration_iter.count() << " mikrosekund" << endl;

    }


    return 0;
}
