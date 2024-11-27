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

// Struktura dla jednego elementu listy
struct Wezel {
    double wartosc;       // Wartość przechowywana w węźle
    Wezel* prev;    // Wskaźnik na poprzedni element
    Wezel* next;    // Wskaźnik na następny element

    Wezel(double war) : wartosc(war), prev(nullptr), next(nullptr) {} // Konstruktor
};

// Struktura dla listy
struct Lista {
    Wezel* head; // Wskaźnik na pierwszy element listy

    Lista() : head(nullptr) {} // Konstruktor inicjalizujący pustą listę
};
// Funkcja dodająca element
void LIST_INSERT(Lista& L, Wezel* x) {
    x->next = L.head;
    x->prev = nullptr; // NIL w C++ to nullptr

    if (L.head != nullptr) {
        L.head->prev = x;
    }
    L.head = x;
}

// Funkcja usuwająca element
void LIST_DELETE(Lista& L, Wezel* x) {
    if (x->prev != nullptr) {
        x->prev->next = x->next;
    } else {
        L.head = x->next; // Jeśli usuwany element to pierwszy węzeł
    }

    if (x->next != nullptr) {
        x->next->prev = x->prev;
    }

    delete x; // Zwolnienie pamięci
}

// Funkcja szukająca element
Wezel* LIST_SEARCH(Lista& L, double k) {
    Wezel* x = L.head;

    while (x != nullptr && x->wartosc != k) {
        x = x->next;
    }

    return x; // Zwraca wskaźnik na znaleziony element lub nullptr, jeśli nie znaleziono
}

// Funkcja wyświetlająca listę
void PRINT_LIST(Lista& L) {
    Wezel* x = L.head;
    while (x != nullptr) {
        cout << x->wartosc << " ";
        x = x->next;
    }
    cout << endl;
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

void STWORZ_LISTE(Lista& L, int n) {
    srand(time(0));
    for (int i = 0; i < n; ++i) {
        double wartosc = (rand() % 100);
        Wezel* x = new Wezel(wartosc);
        LIST_INSERT(L, x);
    }
}

void DOBRZE_POSORTOWANA(Lista& L) {
     if (L.head == nullptr || L.head->next == nullptr) {
        cout << "Dobrze posortowana." << endl; // Pusta lista lub lista z jednym elementem jest posortowana
    }

    Wezel* x = L.head;
    while (x->next != nullptr) {
        if (x->wartosc > x->next->wartosc) {
            cout << "Zle posortowana." << endl;
            return;
        }
        x = x->next;
    }

    cout << "Dobrze posortowana." << endl;
}

void ZROB(Lista& L) {
    auto start = high_resolution_clock::now();
    INSERTION_SORT(L);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Czas: " << duration.count() << " mikrosekund" << endl;
    DOBRZE_POSORTOWANA(L);
    cout << "Porownania: " << porownania << "\nPrzypisania: " << przypisania << "\n";
    RESETUJ();
    cout << endl;
}

int main() {
    // Test funkcji
    Lista L;

    LIST_INSERT(L, new Wezel(1));
    LIST_INSERT(L, new Wezel(2));
    LIST_INSERT(L, new Wezel(3));

    PRINT_LIST(L);

    double szukany = 2;
    Wezel* znaleziony = LIST_SEARCH(L, szukany);
    if (znaleziony) {
        cout << "Znaleziono " << znaleziony->wartosc << endl;
    } else {
        cout << "Nie znaleziono " << szukany << endl;
    }

    LIST_DELETE(L, znaleziony);
    PRINT_LIST(L);

    // Test insertion sort
    int wielkosci[] = {100, 200, 300, 400, 500, 600, 700, 800, 900, 1000};

    for (int n : wielkosci) {

        Lista L;
        STWORZ_LISTE(L, n);
        ZROB(L);

        // Zwolnienie pamięci
        while (L.head != nullptr) {
            LIST_DELETE(L, L.head);
        }
    }

    return 0;
}
