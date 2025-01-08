#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <chrono>
using namespace std;
using namespace std::chrono;

void PRINT_ACTIVITIES(int **c, int **b, int i, int j) {
    if (c[i][j] > 0) {
        int k = b[i][j];
        cout << k << " ";
        PRINT_ACTIVITIES(c, b, i, k);
        PRINT_ACTIVITIES(c, b, k, j);
    }
}

void DYNAMIC_ACTIVITY_SELECTOR(int s[], int f[], int n) {
    int **c = new int *[n + 2]; // Tablica przechowująca maksymalną liczbę aktywności
    int **b = new int *[n + 2];// Tablica przechowująca indeksy wybranych aktywności
    for (int i = 0; i < n + 2; ++i) {
        c[i] = new int[n + 2]{0};
        b[i] = new int[n + 2]{0};
    }

    //(chyba nie potrzebne?)
    for (int i = 0; i <= n; ++i) {
        c[i][i] = 0; // Brak aktywności, jeśli początek i koniec są takie same
        c[i][i + 1] = 0;// Brak aktywności między sąsiednimi elementami
    }
    c[n + 1][n + 1] = 0;

    // Obliczanie tablicy c dla wszystkich możliwych przedziałów długości od 2 do n+1
    for (int l = 2; l <= n + 1; ++l) {// Iteracja po długościach przedziałów
        for (int i = 0; i <= n - l + 1; ++i) { // Początek przedziału
            int j = i + l;// Koniec przedziału
            c[i][j] = 0;// nie potrzebne?
            // Szukanie maksymalnego zbioru aktywności między i a j
            for (int k = j - 1; k > i; --k) { // Iteracja po możliwych zajęciach między i a j
                if (f[i] <= s[k] && f[k] <= s[j] && c[i][k] + c[k][j] + 1 > c[i][j]) { // jeśli zajęcie jest pomiędzy zajęciami i i j oraz???
                    // Jeśli warunki są spełnione, aktualizacja wartości w c i zapamiętanie k
                    c[i][j] = c[i][k] + c[k][j] + 1;
                    b[i][j] = k;
                }
            }
        }
    }

    cout << "Maksymalna liczba zajec " << c[0][n + 1] << endl;
    cout << "Zajecia: ";
    PRINT_ACTIVITIES(c, b, 0, n + 1);
    cout << endl;

    for (int i = 0; i < n + 2; ++i) {
        delete[] c[i];
        delete[] b[i];
    }
    delete[] c;
    delete[] b;
}

int main() {
    int n = 5;
    int s[] = {0, 2, 4, 3, 5, 8, INT_MAX};// Ostatnia i pierwsza aktywność fikcyjna
    int f[] = {INT_MIN,3, 5, 6, 6, 9, 0};
    DYNAMIC_ACTIVITY_SELECTOR(s, f, n);

    return 0;
}
