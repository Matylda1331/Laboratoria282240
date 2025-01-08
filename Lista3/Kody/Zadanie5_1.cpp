#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
using namespace std;
using namespace std::chrono;

void RECURSIVE_ACTIVITY_SELECTOR(int s[], int f[], int n, int k, int zajecia[], int &ile) {
    int m = k + 1;
    while (m <= n && s[m] < f[k]) { // jak spełniony jest warunek s[m] < f[k] to znaczy że dane zajęcie m nie pasuje więc przechodzi się do kolejnego (m++), (zjęcie m zaczyna się w czasie zajęcia k)
        m++;
    }
    if (m <= n) {
        zajecia[ile++] = m; // Dodaj indeks m do wyniku, jeśli zajęcie pasuje czasowo
        RECURSIVE_ACTIVITY_SELECTOR(s, f, n, m, zajecia, ile); // sprawdzamy teraz rekurencyjnie jakie kolejne zajęcie będzie pasować
    }
}

void WYNIK_R_A_S(int s[], int f[], int n) {
    int zajecia[n]; // Tablica zawierająca indeksy zajęć pasujących
    int ile = 0; // ilość zajęć
    RECURSIVE_ACTIVITY_SELECTOR(s, f, n, 0, zajecia, ile);
    cout << "Wybrane zajecia (rekurencyjnie): ";
    for (int i = 0; i < ile; i++) {
        cout << zajecia[i] << " ";
    }
    cout << endl;
}

void ACTIVITY_SELECTOR(int s[], int f[], int n, int zajecia[], int &ile){
    zajecia[ile++] = 1; // Pierwsza aktywność zawsze jest wybrana
    int k = 1;

    for (int m = 2; m <= n; m++) {
        if (s[m] >= f[k]) {
            zajecia[ile++] = m; // Dodaj indeks do wyniku
            k = m;
        }
    }
}
void WYNIK_A_S(int s[], int f[], int n) {
    int zajecia[n]; // Tablica zawierająca indeksy zajęć pasujących
    int ile = 0; // ilość zajęć
    ACTIVITY_SELECTOR(s, f, n, zajecia, ile);
    cout << "Wybrane zajecia (iteracyjnie): ";
    for (int i = 0; i < ile; i++) {
        cout << zajecia[i] << " ";
    }
    cout << endl;
}

void GENERUJ_s(int s[], int n) {
    s[0] = 0; // Fikcyjny na początku
    for (int i = 1; i <= n; i++) {
        s[i] = rand() % (n * 2);
    }
}

void GENERUJ_f(int f[], int s[], int n) {
    f[0] = INT_MIN; // Fikcyjny  na początku
    for (int i = 1; i <= n; i++) {
        f[i] = s[i] + rand() % 100 + 1;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (f[i] > f[j]) {
                swap(f[i], f[j]);
                swap(s[i], s[j]);
            }
        }
    }
}


int main() {
    int s[] = {0, 2, 4, 3, 5, 8}; // Czasy rozpoczęcia (indeks 0 to fikcyjny element)
    int f[] = {INT_MIN, 3, 5, 6, 6, 9}; // Czasy zakończenia (indeks 0 to fikcyjny element)
    int n = 5; // Liczba aktywności (bez indeksu 0)

    WYNIK_R_A_S(s, f, n);
    WYNIK_A_S(s, f, n);

    srand(time(0));
    int wielkosci[] = {1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000};
    for (int n : wielkosci) {
        int s[n + 1];
        int f[n + 1];
        GENERUJ_s(s, n);
        GENERUJ_f(f, s, n);

        int zajecia[n];
        int ile = 0;
        auto start_rec = high_resolution_clock::now();
        RECURSIVE_ACTIVITY_SELECTOR(s, f, n, 0, zajecia, ile);
        auto stop_rec = high_resolution_clock::now();
        auto duration_rec = duration_cast<microseconds>(stop_rec - start_rec);
        cout << "Czas dla rekursji: " << duration_rec.count() << " mikrosekund" << endl;

        int zajecia2[n];
        int ile2 = 0;
        auto start_iter = high_resolution_clock::now();
        ACTIVITY_SELECTOR(s, f, n, zajecia2, ile2);
        auto stop_iter = high_resolution_clock::now();
        auto duration_iter = duration_cast<microseconds>(stop_iter - start_iter);
        cout << "Czas iteracji: " << duration_iter.count() << " mikrosekund" << endl;
    }

    return 0;
}
