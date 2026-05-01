#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdio>

using namespace std;

class KalkulatorSecant {
private:
    double fungsi(double x) {
        return exp(-x) - x;
    }

public:
    void eksekusi(double x_lama, double x_sekarang, double tol, int limit) {
        double x_baru;
        
        cout << "\n[ Tabel Konvergensi ]" << endl;
        cout << "---------------------------------------------" << endl;
        cout << "Iter |      x_n      |     f(x_n)    " << endl;
        cout << "---------------------------------------------" << endl;

        for (int n = 1; n <= limit; ++n) {
            double f_lama = fungsi(x_lama);
            double f_sekarang = fungsi(x_sekarang);

            if (abs(f_sekarang - f_lama) < 1e-12) {
                cout << ">> Galat: Slope terlalu datar." << endl;
                return;
            }

            x_baru = x_sekarang - (f_sekarang * (x_sekarang - x_lama) / (f_sekarang - f_lama));

            cout << setw(4) << n << " | " 
                 << setw(13) << fixed << setprecision(7) << x_baru << " | "
                 << setw(13) << scientific << setprecision(4) << fungsi(x_baru) << endl;

            if (abs(x_baru - x_sekarang) < tol) {
                cout << "---------------------------------------------" << endl;
                printf("Hasil Akhir (Root): %.8f\n", x_baru);
                return;
            }

            x_lama = x_sekarang;
            x_sekarang = x_baru;
        }
        cout << ">> Peringatan: Batas iterasi tercapai." << endl;
    }
};

int main() {
    KalkulatorSecant solver;
    double a, b, t;
    int i;

    printf("masukkan tebakan awal x0 dan x1: ");
    scanf("%lf %lf", &a, &b);

    printf("masukkan toleransi dan max iterasi: ");
    scanf("%lf %d", &t, &i);

    solver.eksekusi(a, b, t, i);

    return 0;
}
