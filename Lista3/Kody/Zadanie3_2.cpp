#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
using namespace std;
using namespace std::chrono;

void PRINT_SOLUTION(char** b, string& X, int i, int j) {
    if (i > 0 && j > 0) {
        if (b[i][j] == '\\') { // Diagonalnie
            PRINT_SOLUTION(b, X, i - 1, j - 1);
            cout << X[i - 1]; // Wypisujemy znak
        } else if (b[i][j] == '|') { // W górę
            PRINT_SOLUTION(b, X, i - 1, j);
        } else { // W lewo
            PRINT_SOLUTION(b, X, i, j - 1);
        }
    }
}

char** LCS_ITERA(string& s1, string& s2, int& długość) {
    int m = s1.length();
    int n = s2.length();

    int** c = new int*[m + 1];
    char** b = new char*[m + 1];
    for (int i = 0; i <= m; i++) {
        c[i] = new int[n + 1];
        b[i] = new char[n + 1];
    }

    for (int i = 0; i <= m; i++) c[i][0] = 0;
    for (int j = 0; j <= n; j++) c[0][j] = 0;

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                c[i][j] = c[i - 1][j - 1] + 1;
                b[i][j] = '\\'; // Diagonalnie
            } else if (c[i - 1][j] >= c[i][j - 1]) {
                c[i][j] = c[i - 1][j];
                b[i][j] = '|'; // W górę
            } else {
                c[i][j] = c[i][j - 1];
                b[i][j] = '-'; // W lewo
            }
        }
    }

    // Zapisujemy długość LCS
    długość = c[m][n];

    for (int i = 0; i <= m; i++) {
        delete[] c[i];
    }
    delete[] c;

    // Zwracamy tablicę kierunków
    return b;
}

string RANDOMOWY_NAPIS(int l) {
    string znaki = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string napis;
    for (int i = 0; i < l; i++) {
        napis += znaki[rand() % znaki.length()];
    }
    return napis;
}

int main() {
    string s1 = "AGGTAB";
    string s2 = "GXTXAYB";
    int długość;
    char** b = LCS_ITERA(s1, s2, długość);
    cout << "Dlugosc : " << długość << ", ";
    PRINT_SOLUTION(b, s1, s1.length(), s2.length());
    cout << endl;
    for (int i = 0; i <= s1.length(); i++) {
        delete[] b[i];
    }
    delete[] b;

    srand(time(0));
    int długości[] = {1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000};
    for (int i : długości) {
        string s1 = RANDOMOWY_NAPIS(i);
        string s2 = RANDOMOWY_NAPIS(i);
        int długość;
        auto start = high_resolution_clock::now();
        char** b = LCS_ITERA(s1, s2, długość);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "Czas: " << duration.count() << " mikrosekund" << endl;
        for (int j = 0; j <= s1.length(); j++) {
            delete[] b[j];
        }
        delete[] b;
        }

    return 0;
}
