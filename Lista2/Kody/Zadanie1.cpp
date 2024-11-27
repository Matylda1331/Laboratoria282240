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

int PARTITION(double A[], int p, int r) {
    int x = A[r];    // Wybieramy ostatni element jako x
    int i = p - 1;   // Indeks mniejszego elementu
    przypisania+=2;

    // Przechodzimy przez podtablicę od p do r-1
    for (int j = p; j <= r - 1; j++) {
        if (A[j] <= x) {     // Jeśli element jest mniejszy lub równy x
            porownania++;
            i++;             // Zwiększamy indeks mniejszego elementu
            przypisania++;
            swap(A[i], A[j]); // Zamieniamy elementy
            przypisania+=2;
        }
    }
    swap(A[i + 1], A[r]); // Umieszczamy x na właściwej pozycji
    przypisania+=2;
    return i + 1;         // Zwracamy indeks x
}

void QUICK_SORT(double A[], int p, int r) {
    if (p < r) { // Warunek zakończenia rekurencji
        porownania++;
        int q = PARTITION(A, p, r); // Podział tablicy
        przypisania++;
        QUICK_SORT(A, p, q - 1);     // Sortowanie lewej części
        QUICK_SORT(A, q + 1, r);     // Sortowanie prawej części
    }
}

void PARTITION2(double A[], int p, int r, int &x, int &y) {
    // Ustawienie dwóch pivotów: pierwszego (left pivot) i drugiego (right pivot)
    if (A[p] > A[r]) {
        porownania++;
        swap(A[p], A[r]);
        przypisania+=2;
    }
    int pivot1 = A[p];
    int pivot2 = A[r];
    przypisania+=2;

    int i = p + 1;
    int a = p + 1; // Indeks mniejszych od pivot1
    int b = r - 1; // Indeks większych od pivot2
    przypisania+=3;

    while (i <= b) {
        porownania++;
        if (A[i] < pivot1) {
            porownania++;
            swap(A[i], A[a]);
            a++;
            przypisania+=3;
        } else if (A[i] > pivot2) {
            porownania++;
            swap(A[i], A[b]);
            b--;
            i--; // Sprawdzamy ten element przeniesiony z pozycji r-1(bo takto zostałby pominienty gdy i++)
            przypisania+=4;
        }
        i++;
        przypisania++;
    }

    // Przesunięcie pivotów na właściwe pozycje
    a--;
    b++;
    swap(A[p], A[a]);
    swap(A[r], A[b]);

    // Zwracamy indeksy pivotów
    x = a;
    y = b;
    przypisania+=6;
}

void QUICK_SORT2(double A[], int p, int r) {
    if (p < r) {
        porownania++;
        int x, y; // Indeksy pivotów po podziale
        PARTITION2(A, p, r, x, y);
        przypisania+=2;
        // Rekurencyjne wywołanie dla trzech części
        QUICK_SORT2(A, p, x - 1);
        QUICK_SORT2(A, x + 1, y - 1);
        QUICK_SORT2(A, y + 1, r);
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

void WYPISZ(double A[], int n) {

    cout << endl;
    DOBRZE_POSORTOWANA( A, n);
    cout << "Porownania: " << porownania << "\nPrzypisania: " << przypisania << "\n";
    RESETUJ();
    cout << endl;
}

double* STWORZ_TABLICE(int n) {
    srand(time(0));
    // Dynamiczna alokacja pamięci dla tablicy
    double* A = new double[n];

    for (int i = 0; i < n; i++) {
        A[i] = (rand() % 100);
    }

    return A;
}


int main()
{
    int wielkosci[] = {100, 200, 300, 400, 500, 600, 700, 800, 900, 1000};

     for (int n : wielkosci) {
        double* A = STWORZ_TABLICE(n);
        auto start = high_resolution_clock::now();
        QUICK_SORT(A, 0, n-1);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "Czas: " << duration.count() << " mikrosekund" << endl;
        WYPISZ(A,n);
        delete[] A;
    }

    cout << "Modyfikacja" << endl << endl;

    for (int n : wielkosci) {
        double* A = STWORZ_TABLICE(n);
        auto start = high_resolution_clock::now();
        QUICK_SORT2(A, 0, n-1);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "Czas: " << duration.count() << " mikrosekund" << endl;
        WYPISZ(A,n);
        delete[] A;

    }
    return 0;


}
