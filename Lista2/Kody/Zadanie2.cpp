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

void COUNTINGSORT(int A[], int n, int exp, int d) {
    int B[n];        // Tablica wynikowa
    int C[d] = {0};   // Licznik dla systemu d-arnego

    // Liczenie wystąpień cyfr na danej pozycji
    for (int i = 0; i < n; i++) {
        int j = (A[i] / exp) % d;
        przypisania++;
        C[j]++;
        przypisania++;
    }

    // Akumulacja liczników
    for (int i = 1; i < d; i++) {
        C[i] += C[i - 1];
        przypisania++;
    }

    // Umieszczanie elementów w tablicy wynikowej w odpowiedniej kolejności
    for (int i = n - 1; i >= 0; i--) {
        int j = (A[i] / exp) % d;
        B[C[j] - 1] = A[i];
        C[j]--;
        przypisania+=3;
    }

    // Przepisanie posortowanej tablicy wynikowej do pierwotnej tablicy A
    for (int i = 0; i < n; i++) {
        A[i] = B[i];
        przypisania++;
    }
}

void RADIX_SORT(int A[], int n, int d, int k) {
    // Wykonuj sortowanie przez zliczanie dla każdej cyfry od 1 do k
    for (int i = 0, exp = 1; i < k; i++, exp *= d) {
        COUNTINGSORT(A, n, exp, d);
    }
}

void RADIX_SORT2(int A[], int n, int d, int k) {
    // Policz liczby dodatnie i ujemne
    int liczba_dodatnich = 0, liczba_ujemnych = 0;
    przypisania+=2;

    for (int i = 0; i < n; i++) {
        if (A[i] >= 0) {
            porownania++;
            liczba_dodatnich++;
            przypisania++;
        } else {
            porownania++;
            liczba_ujemnych++;
            przypisania++;
        }
    }

    // Utwórz tablice pomocnicze
    int dodatnie[liczba_dodatnich];
    int ujemne[liczba_ujemnych];

    // Rozdziel liczby dodatnie i ujemne
    int dod = 0, uje = 0;
    przypisania+=2;
    for (int i = 0; i < n; i++) {
        if (A[i] >= 0) {
            porownania++;
            dodatnie[dod++] = A[i];
            przypisania++;
        } else {
            porownania++;
            ujemne[uje++] = -A[i];
            przypisania++; // Zamień ujemne na dodatnie
        }
    }

    // Posortuj liczby dodatnie
    if (liczba_dodatnich > 0) {
        porownania++;
        RADIX_SORT(dodatnie, liczba_dodatnich, d, k);
    }

    // Posortuj liczby ujemne (jako dodatnie)
    if (liczba_ujemnych > 0) {
        porownania++;
        RADIX_SORT(ujemne, liczba_ujemnych, d, k);
    }

    // Połącz wyniki: liczby ujemne (od największej do najmniejszej), a potem dodatnie
    int x = 0;
    przypisania++;

    // Liczby ujemne w odwrotnej kolejności
    for (int i = liczba_ujemnych - 1; i >= 0; i--) {
        A[x++] = -ujemne[i];
        przypisania++;
    }

    // Liczby dodatnie
    for (int i = 0; i < liczba_dodatnich; i++) {
        A[x++] = dodatnie[i];
        przypisania++;
    }
}

int* STWORZ_TABLICE1(int n) {
    srand(time(0));
    int* A = new int[n];
    for (int i = 0; i < n; i++) {
        A[i] = (rand() % 100);
    }

    return A;
}

int* STWORZ_TABLICE2(int n) {
    srand(time(0));
    int* A = new int[n];
    for (int i = 0; i < n; i++) {
        A[i] = ((rand() % 199)-99);
    }

    return A;
}

void DOBRZE_POSORTOWANA(int A[], int n) {
    for (int i = 1; i < n; i++) {
        if (A[i - 1] > A[i]) {
            cout << "Zle posortowana." << endl;
            return;
        }
    }
    cout << "Dobrze posortowana." << endl;
}

void ZROB(int A[], int n) {
    DOBRZE_POSORTOWANA( A, n);
    cout << "Porownania: " << porownania << "\nPrzypisania: " << przypisania << "\n";
    RESETUJ();
    cout << endl;
}

int main() {

    int wielkosci[] = {100, 200, 300, 400, 500, 600};

    cout << "Radix_Sort dla d=2 i k=7" << endl;
    for (int n : wielkosci) {
        int* A = STWORZ_TABLICE1(n);
        auto start = high_resolution_clock::now();
        RADIX_SORT(A, n, 2, 7);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "Czas: " << duration.count() << " mikrosekund" << endl;
        ZROB(A,n);
        delete[] A;
    }

    cout << "Radix_Sort dla d=4 i k=4" << endl;
      for (int n : wielkosci) {
        int* A = STWORZ_TABLICE1(n);
        auto start = high_resolution_clock::now();
        RADIX_SORT(A, n, 4, 4);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "Czas: " << duration.count() << " mikrosekund" << endl;
        ZROB(A,n);
        delete[] A;
    }

    cout << "Radix_Sort dla d=8 i k=3" << endl;
      for (int n : wielkosci) {
        int* A = STWORZ_TABLICE1(n);
        auto start = high_resolution_clock::now();
        RADIX_SORT(A, n, 8, 3);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "Czas: " << duration.count() << " mikrosekund" << endl;
        ZROB(A,n);
        delete[] A;
    }

    cout << "Radix_Sort dla d=10 i k=2" << endl;
      for (int n : wielkosci) {
        int* A = STWORZ_TABLICE1(n);
        auto start = high_resolution_clock::now();
        RADIX_SORT(A, n, 10, 2);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "Czas: " << duration.count() << " mikrosekund" << endl;
        ZROB(A,n);
        delete[] A;
    }

    cout << "Radix_Sort dla d=16 i k=2" << endl;
      for (int n : wielkosci) {
        int* A = STWORZ_TABLICE1(n);
        auto start = high_resolution_clock::now();
        RADIX_SORT(A, n, 16, 2);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "Czas: " << duration.count() << " mikrosekund" << endl;
        ZROB(A,n);
        delete[] A;
    }


    cout << "Radix_Sort2 dla d=2 i k=7" << endl;
    for (int n : wielkosci) {
        int* A = STWORZ_TABLICE2(n);
        auto start = high_resolution_clock::now();
        RADIX_SORT2(A, n, 2, 7);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "Czas: " << duration.count() << " mikrosekund" << endl;
        ZROB(A,n);
        delete[] A;
    }

    cout << "Radix_Sort2 dla d=4 i k=4" << endl;
    for (int n : wielkosci) {
        int* A = STWORZ_TABLICE2(n);
        auto start = high_resolution_clock::now();
        RADIX_SORT2(A, n, 4, 4);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "Czas: " << duration.count() << " mikrosekund" << endl;
        ZROB(A,n);
        delete[] A;
    }

    cout << "Radix_Sort2 dla d=8 i k=3" << endl;
    for (int n : wielkosci) {
        int* A = STWORZ_TABLICE2(n);
        auto start = high_resolution_clock::now();
        RADIX_SORT2(A, n, 8, 3);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "Czas: " << duration.count() << " mikrosekund" << endl;
        ZROB(A,n);
        delete[] A;
    }

    cout << "Radix_Sort2 dla d=10 i k=2" << endl;
    for (int n : wielkosci) {
        int* A = STWORZ_TABLICE2(n);
        auto start = high_resolution_clock::now();
        RADIX_SORT2(A, n, 10, 2);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "Czas: " << duration.count() << " mikrosekund" << endl;
        ZROB(A,n);
        delete[] A;
    }

    cout << "Radix_Sort2 dla d=16 i k=2" << endl;
    for (int n : wielkosci) {
        int* A = STWORZ_TABLICE2(n);
        auto start = high_resolution_clock::now();
        RADIX_SORT2(A, n, 16, 2);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "Czas: " << duration.count() << " mikrosekund" << endl;
        ZROB(A,n);
        delete[] A;
    }

    return 0;
}
