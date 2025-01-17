#include <iostream>
using namespace std;

int porownania = 0;
int przypisania = 0;

void RESETUJ() {
    porownania = 0;
    przypisania = 0;
}

int LEFT(int i) {
    return 2 * i + 1;
}

int RIGHT(int i) {
    return 2 * i + 2;
}

void HEAPIFY(int A[], int i, int n) {
    int l = LEFT(i);
    int r = RIGHT(i);
    int najwiekszy = i;

    if (l < n && A[l] > A[i]) {
        porownania++;
        najwiekszy = l;
        przypisania++;
    }

    if (r < n && A[r] > A[najwiekszy]) {
        porownania++;
        najwiekszy = r;
        przypisania++;
    }

    if (najwiekszy != i) {
        porownania++;
        swap(A[i], A[najwiekszy]);
        przypisania +=2;
        HEAPIFY(A, najwiekszy, n);
    }
}


void BUILD_HEAP(int A[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
    HEAPIFY(A, i, n);
    }
}

void HEAPSORT(int A[], int n) {
    BUILD_HEAP(A, n);

    for (int i = n - 1; i >= 1; i--) {
        swap(A[0], A[i]);
        przypisania +=2;
        n--;
        HEAPIFY(A, 0, n);
    }
}

int LEWY2(int i) {
    return 3 * i + 1;
}

int SRODKOWY2(int i) {
    return 3 * i + 2;
}

int PRAWY2(int i) {
    return 3 * i + 3;
}

void HEAPIFY2(int A[], int i, int n) {
    int l = LEWY2(i);
    int s = SRODKOWY2(i);
    int p = PRAWY2(i);
    int najwiekszy = i;

    if (l < n && A[l] > A[i]) {
        porownania++;
        przypisania++;
        najwiekszy = l;
    }

    if (s < n && A[s] > A[najwiekszy]) {
        najwiekszy = s;
        porownania++;
        przypisania++;
    }

    if (p < n && A[p] > A[najwiekszy]) {
        porownania++;
        przypisania++;
        najwiekszy = p;
    }

    if (najwiekszy != i) {
        porownania++;
        swap(A[i], A[najwiekszy]);
        przypisania +=2;
        HEAPIFY2(A, najwiekszy, n);
    }
}

void BUILD_HEAP2(int A[], int n){
    for (int i = n / 3 - 1; i >= 0; i--) {
        HEAPIFY2(A, i, n);
    }
}

void HEAPSORT2(int A[], int n) {
    BUILD_HEAP2(A, n);

    for (int i = n - 1; i >= 1; i--) {
        swap(A[0], A[i]);
        przypisania +=2;
        n--;
        HEAPIFY2(A, 0, n);
    }
}

void WYPISZ(int A[], int n) {
    for (int i = 0; i < n; i++) {
        cout << A[i] << " ";
    }
    cout << endl;
    cout << "Porownania: " << porownania << "\nPrzypisania: " << przypisania << "\n";
    RESETUJ();
    cout << endl;
}

int main() {
    int A1[] = {52, 54, 58, 62, 89, 75, 39, 38, 19, 81, 12, 80, 98, 37, 88, 52, 43, 94, 18, 89};
    int n1 = sizeof(A1) / sizeof(A1[0]);
    int A2[] = {2, 5, 52, 33, 40, 51, 75, 15, 3, 7, 97, 58, 42, 95, 59, 49, 84, 79, 83, 60, 43, 20, 40, 77, 16, 96, 28, 26, 7, 34, 16, 51, 43, 67, 64, 85, 67, 12, 30, 28};
    int n2 = sizeof(A2) / sizeof(A2[0]);
    int A3[] = {100, 26, 14, 77, 50, 47, 27, 88, 58, 56, 22, 49, 17, 83, 41, 43, 37, 18, 86, 96, 68, 6, 29, 68, 29, 43, 70, 82, 82, 21, 9, 68, 38, 12, 12, 67, 11, 4, 92, 99, 11, 37, 96, 38, 67, 21, 81, 76, 28, 6, 89, 64, 70, 28, 57, 72, 39, 47, 71, 67};
    int n3 = sizeof(A3) / sizeof(A3[0]);
    int A4[] = {53, 70, 15, 85, 46, 57, 9, 63, 15, 51, 25, 40, 47, 73, 97, 68, 3, 78, 41, 88, 18, 44, 68, 81, 5, 91, 50, 78, 2, 69, 6, 74, 55, 51, 78, 41, 21, 25, 8, 57, 71, 68, 53, 20, 58, 91, 19, 71, 26, 52, 81, 64, 74, 43, 69, 16, 32, 92, 40, 91, 32, 60, 82, 24, 40, 61, 93, 38, 28, 74, 76, 61, 94, 95, 6, 37, 70, 82, 26, 26};
    int n4 = sizeof(A4) / sizeof(A4[0]);
    int A5[] = {87, 83, 49, 96, 97, 6, 52, 56, 5, 72, 75, 25, 35, 85, 75, 30, 13, 10, 13, 42, 43, 1, 61, 60, 45, 37, 80, 57, 61, 31, 59, 2, 66, 58, 87, 94, 100, 51, 11, 17, 47, 22, 62, 83, 71, 21, 14, 76, 80, 52, 19, 90, 82, 14, 95, 84, 45, 51, 42, 71, 57, 22, 62, 13, 13, 17, 76, 31, 22, 15, 15, 75, 26, 34, 52, 26, 93, 75, 96, 69, 46, 29, 69, 54, 47, 28, 18, 29, 16, 81, 62, 50, 2, 13, 16, 41, 81, 50, 94, 2};
    int n5 = sizeof(A5) / sizeof(A5[0]);
    int A6[] = {7, 66, 92, 75, 22, 65, 21, 84, 45, 78, 84, 16, 49, 11, 10, 85, 59, 2, 49, 92, 36, 80, 81, 81, 1, 29, 5, 70, 86, 64, 67, 53, 22, 53, 57, 7, 78, 30, 97, 31, 74, 23, 58, 79, 55, 78, 77, 6, 1, 50, 83, 87, 88, 33, 31, 61, 24, 49, 77, 43, 24, 54, 59, 85, 2, 80, 82, 48, 6, 66, 65, 22, 16, 65, 33, 47, 63, 25, 97, 27, 82, 49, 22, 78, 50, 67, 39, 76, 23, 21, 49, 99, 69, 98, 85, 46, 97, 63, 63, 66, 96, 79, 78, 46, 14, 90, 61, 29, 69, 2, 65, 32, 25, 71, 45, 84, 63, 60, 100, 71};
    int n6 = sizeof(A6) / sizeof(A6[0]);

    HEAPSORT(A1, n1);
    WYPISZ(A1, n1);
    HEAPSORT(A2, n2);
    WYPISZ(A2, n2);
    HEAPSORT(A3, n3);
    WYPISZ(A3, n3);
    HEAPSORT(A4, n4);
    WYPISZ(A4, n4);
    HEAPSORT(A5, n5);
    WYPISZ(A5, n5);
    HEAPSORT(A6, n6);
    WYPISZ(A6, n6);

    int B1[] = {52, 54, 58, 62, 89, 75, 39, 38, 19, 81, 12, 80, 98, 37, 88, 52, 43, 94, 18, 89};
    int m1 = sizeof(B1) / sizeof(B1[0]);
    int B2[] = {2, 5, 52, 33, 40, 51, 75, 15, 3, 7, 97, 58, 42, 95, 59, 49, 84, 79, 83, 60, 43, 20, 40, 77, 16, 96, 28, 26, 7, 34, 16, 51, 43, 67, 64, 85, 67, 12, 30, 28};
    int m2 = sizeof(B2) / sizeof(B2[0]);
    int B3[] = {100, 26, 14, 77, 50, 47, 27, 88, 58, 56, 22, 49, 17, 83, 41, 43, 37, 18, 86, 96, 68, 6, 29, 68, 29, 43, 70, 82, 82, 21, 9, 68, 38, 12, 12, 67, 11, 4, 92, 99, 11, 37, 96, 38, 67, 21, 81, 76, 28, 6, 89, 64, 70, 28, 57, 72, 39, 47, 71, 67};
    int m3 = sizeof(B3) / sizeof(B3[0]);
    int B4[] = {53, 70, 15, 85, 46, 57, 9, 63, 15, 51, 25, 40, 47, 73, 97, 68, 3, 78, 41, 88, 18, 44, 68, 81, 5, 91, 50, 78, 2, 69, 6, 74, 55, 51, 78, 41, 21, 25, 8, 57, 71, 68, 53, 20, 58, 91, 19, 71, 26, 52, 81, 64, 74, 43, 69, 16, 32, 92, 40, 91, 32, 60, 82, 24, 40, 61, 93, 38, 28, 74, 76, 61, 94, 95, 6, 37, 70, 82, 26, 26};
    int m4 = sizeof(B4) / sizeof(B4[0]);
    int B5[] = {87, 83, 49, 96, 97, 6, 52, 56, 5, 72, 75, 25, 35, 85, 75, 30, 13, 10, 13, 42, 43, 1, 61, 60, 45, 37, 80, 57, 61, 31, 59, 2, 66, 58, 87, 94, 100, 51, 11, 17, 47, 22, 62, 83, 71, 21, 14, 76, 80, 52, 19, 90, 82, 14, 95, 84, 45, 51, 42, 71, 57, 22, 62, 13, 13, 17, 76, 31, 22, 15, 15, 75, 26, 34, 52, 26, 93, 75, 96, 69, 46, 29, 69, 54, 47, 28, 18, 29, 16, 81, 62, 50, 2, 13, 16, 41, 81, 50, 94, 2};
    int m5 = sizeof(B5) / sizeof(B5[0]);
    int B6[] = {7, 66, 92, 75, 22, 65, 21, 84, 45, 78, 84, 16, 49, 11, 10, 85, 59, 2, 49, 92, 36, 80, 81, 81, 1, 29, 5, 70, 86, 64, 67, 53, 22, 53, 57, 7, 78, 30, 97, 31, 74, 23, 58, 79, 55, 78, 77, 6, 1, 50, 83, 87, 88, 33, 31, 61, 24, 49, 77, 43, 24, 54, 59, 85, 2, 80, 82, 48, 6, 66, 65, 22, 16, 65, 33, 47, 63, 25, 97, 27, 82, 49, 22, 78, 50, 67, 39, 76, 23, 21, 49, 99, 69, 98, 85, 46, 97, 63, 63, 66, 96, 79, 78, 46, 14, 90, 61, 29, 69, 2, 65, 32, 25, 71, 45, 84, 63, 60, 100, 71};
    int m6 = sizeof(B6) / sizeof(B6[0]);
    
    cout << "Modyfikowane " <<endl <<endl;

    HEAPSORT2(B1, m1);
    WYPISZ(B1, m1);
    HEAPSORT2(B2, m2);
    WYPISZ(B2, m2);
    HEAPSORT2(B3, m3);
    WYPISZ(B3, m3);
    HEAPSORT2(B4, m4);
    WYPISZ(B4, m4);
    HEAPSORT2(B5, m5);
    WYPISZ(B5, m5);
    HEAPSORT2(B6, m6);
    WYPISZ(B6, m6);


    return 0;
}
