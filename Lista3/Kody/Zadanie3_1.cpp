#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
using namespace std;
using namespace std::chrono;

int LCS_REKU_SPAM(const string &s1, const string &s2, int m, int n, int **b) { // dynamiczne tablice bo rekurencja
    if (m == 0 || n == 0) // gdy któreś słowo ma długość 0 to 0
        return 0;

    if (b[m][n] != -1) // Jeśli wynik już istnieje w tablicy
        return b[m][n];

    if (s1[m - 1] == s2[n - 1]) // Jeśli ostatnie znaki pasują
        return b[m][n] = 1 + LCS_REKU_SPAM(s1, s2, m - 1, n - 1, b);
    // Jeśli ostatnie znaki nie pasują
    return b[m][n] = max(LCS_REKU_SPAM(s1, s2, m, n - 1, b), LCS_REKU_SPAM(s1, s2, m - 1, n, b));
}

void ROZWIAZANIE(const string &s1, const string &s2) {
    int m = s1.length();
    int n = s2.length();

    int **b = new int*[m + 1]; // wypełniamy tablice -1
    for (int i = 0; i <= m; ++i) {
        b[i] = new int[n + 1];
        for (int j = 0; j <= n; ++j) {
            b[i][j] = -1;
        }
    }

    int l = LCS_REKU_SPAM(s1, s2, m, n, b); // Jak długi najdłuższy podciąg

    string podciag = "";
    while (m > 0 && n > 0) {
        if (s1[m - 1] == s2[n - 1]) {// Jeśli znaki pasują, dodaj do wyniku
            podciag = s1[m - 1] + podciag;
            m--;
            n--;
        } else if (b[m - 1][n] > b[m][n - 1]) {// Przechodzimy w kierunku większej wartości
            m--;
        } else {
            n--;
        }
    }

    cout << "Dlugosc: " << l << endl;
    cout << "Podciag: " << podciag << endl;

    for (int i = 0; i <= m; ++i) {
        delete[] b[i];
    }
    delete[] b;
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
    string X = "AGGTAB";
    string Y = "GXTXAYB";
    ROZWIAZANIE(X, Y);

    srand(time(0));

    int długości[] = {1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000};
    for (int i : długości) {
        string s1 = RANDOMOWY_NAPIS(i);
        string s2 = RANDOMOWY_NAPIS(i);
        int m = s1.length();
        int n = s2.length();
        int **b = new int*[m + 1];
        for (int i = 0; i <= m; ++i) {
            b[i] = new int[n + 1];
            for (int j = 0; j <= n; ++j) {
                b[i][j] = -1;
            }
        }
        auto start = high_resolution_clock::now();
        LCS_REKU_SPAM(s1, s2, m, n, b);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "Czas: " << duration.count() << " mikrosekund" << endl;
        for (int i = 0; i <= m; ++i) {
        delete[] b[i];
        }
        delete[] b;

    }
    return 0;
}
