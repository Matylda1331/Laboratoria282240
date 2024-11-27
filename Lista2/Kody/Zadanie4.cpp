#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
using namespace std;
using namespace std::chrono;

int porownania = 0;
int przypisania = 0;

void RESETUJ() {
    porownania = 0;
    przypisania = 0;
}

struct Wezel {
    double wartosc;
    Wezel* prev;
    Wezel* next;

    Wezel(double war) : wartosc(war), prev(nullptr), next(nullptr) {}
};

struct Lista {
    Wezel* head;

    Lista() : head(nullptr) {}
};

void LIST_INSERT(Lista& L, Wezel* x) {
    x->next = L.head;
    x->prev = nullptr;
    przypisania+=2;
    if (L.head != nullptr) {
        porownania++;
        L.head->prev = x;
        przypisania++;
    }
    L.head = x;
    przypisania++;
}

void INSERTION_SORT(Lista& L) {
    if (L.head == nullptr || L.head->next == nullptr) {
        porownania++;
        return; // Lista jest pusta lub ma jeden element, więc jest już posortowana
    }

    Wezel* x = L.head->next;
    przypisania++; // Zaczynamy od drugiego elementu
    while (x != nullptr) {
        porownania++;
        Wezel* Key = x;
        przypisania++;
        Wezel* prevKey = x->prev;
        przypisania++;

        // Przesuwanie elementów w uporządkowanej części listy
        while (prevKey != nullptr && prevKey->wartosc > Key->wartosc) {
            porownania++;
            // Zamiana wartości między węzłami
            swap(prevKey->wartosc, Key->wartosc);
            przypisania+=2;

            // Przesunięcie do poprzedniego elementu
            Key = prevKey;
            prevKey = prevKey->prev;
            przypisania+=2;
        }

        // Przejście do następnego elementu w nieposortowanej części listy
        x = x->next;
        przypisania++;
    }
}

void BUCKET_SORT(double A[], int n) {
    Lista B[n]; // Tablica B zawierająca n pustych list

    // Inicjalizacja pustych list w B
    for (int j = 0; j < n; j++) {
        B[j] = Lista();
        przypisania++;
    }

    // Rozdzielenie elementów tablicy A do odpowiednich list w B
    for (int i = 0; i < n; i++) {
        int index = static_cast<int>(n * A[i]); // Oblicz indeks kubełka
        Wezel* nowy = new Wezel(A[i]);         // Utwórz nowy węzeł dla elementu A[i]
        przypisania+=2;
        LIST_INSERT(B[index], nowy);           // Wstaw element do odpowiedniej listy
    }

    // Posortowanie każdej listy za pomocą INSERTION_SORT
    for (int j = 0; j < n; j++) {
        INSERTION_SORT(B[j]);
    }

    // Połączenie wszystkich list z tablicy B w jedną posortowaną tablicę A
    int i = 0;
    przypisania++;
    for (int j = 0; j < n; j++) {
        Wezel* x = B[j].head;
        przypisania++;
        while (x != nullptr) {
            porownania++;
            A[i++] = x->wartosc; // Przepisanie wartości do A
            x = x->next;
            przypisania+=2;
        }
    }
}

void BUCKET_SORT2(double A[], int n) {
    // Znajdź minimalną i maksymalną wartość w tablicy
    double minimalna = A[0];
    double maksymalna = A[0];
    przypisania+=2;
   for (int i = 1; i < n; i++) {
    if (A[i] < minimalna) {
        porownania++;
        przypisania++;
        minimalna = A[i];
    }

    if (A[i] > maksymalna) {
        porownania++;
        przypisania++;
        maksymalna = A[i];
    }
}
    if (maksymalna == minimalna) {
        for (int i = 0; i < n; i++) {
            A[i] = minimalna; // Wszystkie elementy są identyczne
        }
        return;
    }

    Lista B[n]; // Tablica B zawierająca n pustych list

    // Inicjalizacja pustych list w B
    for (int j = 0; j < n; j++) {
        B[j] = Lista();
        przypisania++;
    }

    // Rozdzielenie elementów tablicy A do odpowiednich kubełków
    for (int i = 0; i < n; i++) {
        int index = static_cast<int>(n * (A[i] - minimalna) / (maksymalna - minimalna)); // Oblicz indeks kubełka
        przypisania++;
        if (index == n){
            porownania++;
            index--;
            przypisania++;  // Obsługa przypadku, gdy index=n, żeby był w kubełku n-1
        }
        Wezel* nowy = new Wezel(A[i]);                // Utwórz nowy węzeł
        przypisania++;
        LIST_INSERT(B[index], nowy);                  // Wstaw element do odpowiedniej listy
    }

    // Posortowanie każdej listy za pomocą INSERTION_SORT
    for (int j = 0; j < n; j++) {
        INSERTION_SORT(B[j]);
    }

    // Połączenie wszystkich list z tablicy B w jedną posortowaną tablicę A
    int i = 0;
    for (int j = 0; j < n; j++) {
        Wezel* x = B[j].head;
        przypisania++;
        while (x != nullptr) {
            porownania++;
            A[i++] = x->wartosc; // Przepisanie wartości do A
            x = x->next;
            przypisania+=2;
        }
    }
}

void DOBRZE_POSORTOWANA(double A[], int n) {
    for (int i = 1; i < n; i++) {
        if (A[i - 1] > A[i]) {
            cout << "Zle posortowana." << endl;
            return;
        }
    }
    cout << "Dobrze posortowana." << endl;
}

double* STWORZ_TABLICE1(int n) {
    srand(time(0));
    double* A = new double[n];
    for (int i = 0; i < n; i++) {
        A[i] = rand() / (RAND_MAX + 1.0); // Liczby od 0 i mniejsze niż 1
    }

    return A;
}

double* STWORZ_TABLICE2(int n) {
    srand(time(0));
    double* A = new double[n];
    for (int i = 0; i < n; i++) {
        A[i] = (rand() % 100); // Liczby od 0 do 99
    }

    return A;
}

void ZROB(double A[], int n) {
    DOBRZE_POSORTOWANA( A, n);
    cout << "Porownania: " << porownania << "\nPrzypisania: " << przypisania << "\n";
    RESETUJ();
    cout << endl;
}

int main() {

    int wielkosci[] = {100, 200, 300, 400, 500, 600, 700, 800, 900, 1000};

    for (int n : wielkosci) {
        double* A = STWORZ_TABLICE1(n);
        auto start = high_resolution_clock::now();
        BUCKET_SORT(A, n);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "Czas: " << duration.count() << " mikrosekund" << endl;
        ZROB(A,n);
        delete[] A;
    }

    cout << "Modyfikacja" << endl << endl;

    for (int n : wielkosci) {
        double* A = STWORZ_TABLICE2(n);
        auto start = high_resolution_clock::now();
        BUCKET_SORT2(A, n);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "Czas: " << duration.count() << " mikrosekund" << endl;
        ZROB(A,n);
        delete[] A;

    }
  return 0;
}
