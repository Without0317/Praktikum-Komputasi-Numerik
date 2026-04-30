# PPT 2 Regula Falsi

## A. Library
```cpp
#include <vector>
#include <cmath>
#include <iomanip>
#include <string>
```
## B. f(x) persamaan 
```cpp
double f(double x, const vector<double>& koefisien, int derajat) {
    double hasil = 0;
    for (int i = 0; i <= derajat; i++) {
        hasil += koefisien[i] * pow(x, i);
    }
    return hasil;
}
```
- sebagai function untuk menghitung batas atas f(a), batas bawah f(b), dan persamaan yang diinputkan oleh pengguna

## C. Menggambarkan grafik
```cpp
void gambarGrafikHorizontal(double a, double b, const vector<double>& koefisien, int derajat) {
    const int LEBAR = 60;  // Lebar grafik (Sumbu X)
    const int TINGGI = 20; // Tinggi grafik (Sumbu Y)
```
- membuat function lalu menyatakan lebar dan tinggi grafik

```cpp
double min_y = f(a, koefisien, derajat);
    double max_y = min_y;
    for (int i = 0; i <= LEBAR; i++) {
        double x = a + i * (b - a) / LEBAR;
        double y = f(x, koefisien, derajat);
        if (y < min_y) min_y = y;
        if (y > max_y) max_y = y;
    }
```
- Program mengecek 60 titik di sepanjang batas $a$ sampai $b$ untuk mencari nilai fungsi tertinggi (max_y) dan terendah (min_y). Langkah ini memastikan kurva nantinya tidak terpotong (keluar layar) dan ukurannya pas memenuhi 20 baris terminal.

```cpp

    if (max_y - min_y < 0.000001) {
        max_y += 1.0;
        min_y -= 1.0;
    }
```
-jika nilai maks dan min sama persis grafik akan memperbesar skalanya secara paksa,Jika tidak diperbsesar, baris kode di bawahnya akan mengalami error fatal (division by zero) karena mencoba membagi dengan max_y - min_y yang bernilai nol.

```cpp
 vector<string> kanvas(TINGGI, string(LEBAR, ' '));
 ```
- menggunakan vector agar dinamis ukurannya

```cpp
int baris_nol = -1;
if (min_y <= 0 && max_y >= 0) {
    baris_nol = TINGGI - 1 - (int)((0 - min_y) / (max_y - min_y) * (TINGGI - 1));
    for (int i = 0; i < LEBAR; i++) {
        kanvas[baris_nol][i] = '-';
    }
}
```
-Mengecek apakah nilai $y=0$ melintas di dalam kanvas. Jika ya, program menghitung posisi barisnya (menggunakan interpolasi linier), lalu menimpa baris tersebut secara memanjang dengan karakter strip (-) sebagai penanda sumbu X.

```cpp
for (int i = 0; i < LEBAR; i++) {
    double x = a + i * (b - a) / (LEBAR - 1);
    double y = f(x, koefisien, derajat);
    
    int j = TINGGI - 1 - (int)((y - min_y) / (max_y - min_y) * (TINGGI - 1));
    
    if (j >= 0 && j < TINGGI) {
        kanvas[j][i] = '*'; 
    }
}
```
- proses menggambar grafik dengan *

```cpp
cout << "\n=== GRAFIK FUNGSI f(x) ===" << endl;
cout << "Rentang X: [" << a << ", " << b << "]\n\n";

for (int j = 0; j < TINGGI; j++) {
    double y_val = max_y - j * (max_y - min_y) / (TINGGI - 1);
    cout << setw(8) << fixed << setprecision(2) << y_val << " | " << kanvas[j] << endl;
}
```
-Mulai mencetak ke layar CMD. Di dalam looping, program menghitung label nilai y_val (seperti 2.00, 0.50, -1.00), menampilkannya di sebelah kiri, disusul dengan garis pembatas |, dan akhirnya mencetak seluruh isi kanvas baris tersebut (yang sudah berisi spasi, -, dan *).

```cpp
cout << "           ";
for(int i = 0; i < LEBAR; i++) cout << "=";
cout << endl;
cout << "           " << left << setw(LEBAR/2) << a << right << setw(LEBAR/2) << b << endl;
```
- Membuat bingkai bawah grafik menggunakan deretan tanda sama dengan (=). Setelah itu, program meletakkan angka batas bawah (a) di sisi paling kiri bawah, dan angka batas atas (b) di sisi paling kanan bawah sebagai panduan bagi pengguna untuk membaca grafik




## D. Metode Regula Falsi
```cpp
void regulafalsi(const vector<double>& koefisien, int derajat, double a, double b, double toleransi) {
    if (f(a, koefisien, derajat) * f(b, koefisien, derajat) >= 0) {
        cout << "tidak ada akar akar persamaan dalam rentang " << a << " dan " << b << "\n";
        return;
    }
```
- membuat function regula falsi
- jika `f(a) x f(b) >= 0` maka tidak ada akar akar persamaan dalam rentang tersebut karena salah satu syarat regula falsi adalah `f(a) x f(b) < 0`
```cpp
 gambarGrafikHorizontal(a, b, koefisien, derajat);
```
- memanggil fungsi gambarGrafikHorizontal.
```cpp
 double c = a;
    int iterasi = 0;
    cout << "\nIterasi ke- |      c      |     f(c)    " << endl;
    cout << "---------------------------------------" << endl;
```
- menginisialisasikan c
- mencetak iterasi numerik dari proses Regula Falsi

```cpp
 while (true) {
        double fa = f(a, koefisien, derajat);
        double fb = f(b, koefisien, derajat);

        c = (a * fb - b * fa) / (fb - fa);
        double fc = f(c, koefisien, derajat);

        iterasi++;
        cout << setw(10) << iterasi << " | " << setw(11) << fixed << setprecision(6) << c 
             << " | " << setw(11) << fc << endl;

        if (abs(fc) < toleransi) {
            break;
        }

        if (fa * fc < 0) {
            b = c; 
        } else {
            a = c;
        }

        if (iterasi > 1000) {
            cout << "Konvergensi lambat \n";
            break;
        }
    }
```
- mendeklerasikan f(a) dan f(b) dengan menggunakan function f
- Rumus Regula falsi
  <img width="379" height="174" alt="image" src="https://github.com/user-attachments/assets/8ba4f119-4e41-4d5c-898a-f091fc21192b" />
- `if (abs(fc) < toleransi) {break;` jika c sudah dibawah toleransi yang diinginkan maka looping akan break
- Menginisialisasikan batas atas dan batas bawahnya setelah pengoperasian c
- apabila iterasi sudah lebih dari 1000 berarti konvergensi akar persamaan berlangsung lambat

## E. main()
```cpp
int derajat;
    cout << "Mencari akar akar persamaan menggunakan metode Regula Falsi\n";
    cout << "Masukkan pangkat tertinggi : ";
    cin >> derajat;
```
```cpp
 if (derajat > 100 || derajat < 0) {
        if (derajat > 100) {
            cout << "derajat yang anda masukkan melebihi kapasitas";
        } else if (derajat < 0) {
            cout << "derajat yang anda masukkan tidak valid";
        }
        return 0;
    }
```
- jika derajat lebih dari 100 atau kurang dari nol maka derajat akan melebihi kapasitas
- jika derajat < 0 maka derajat yang dimasukkan tidak valid
``` cpp
vector<double> koefisien(derajat + 1);
    for (int i = 0; i <= derajat; i++) {
        cout << "masukkan koefisien x^" << i << ": ";
        cin >> koefisien[i];
    }
```
- menggunakan vector agar size nya lebih dinamis
- looping untuk memasukkan koefisien variabel x, x^2,dst.
- menginput koefisien

```cpp
double a, b, toleransi;
    cout << "Masukkan batas bawah (a) : ";
    cin >> a;
    cout << "Masukkan batas atas (b)  : ";
    cin >> b;
    cout << "Masukkan toleransi error : ";
    cin >> toleransi;
```
- menginputkan batas atas(a) dan batas bawah(b)
- menginputkan toleransi
```cpp
 regulafalsi(koefisien, derajat, a, b, toleransi);
```
- memanggil fungsi Regula Falsi

## Full Code
```cpp
#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <string>

using namespace std;

double f(double x, const vector<double>& koefisien, int derajat) {
    double hasil = 0;
    for (int i = 0; i <= derajat; i++) {
        hasil += koefisien[i] * pow(x, i);
    }
    return hasil;
}

void gambarGrafikHorizontal(double a, double b, const vector<double>& koefisien, int derajat) {
    const int LEBAR = 60;  // Lebar grafik (Sumbu X)
    const int TINGGI = 20; // Tinggi grafik (Sumbu Y)

    double min_y = f(a, koefisien, derajat);
    double max_y = min_y;
    for (int i = 0; i <= LEBAR; i++) {
        double x = a + i * (b - a) / LEBAR;
        double y = f(x, koefisien, derajat);
        if (y < min_y) min_y = y;
        if (y > max_y) max_y = y;
    }

    if (max_y - min_y < 0.000001) {
        max_y += 1.0;
        min_y -= 1.0;
    }

    vector<string> kanvas(TINGGI, string(LEBAR, ' '));

    int baris_nol = -1;
    if (min_y <= 0 && max_y >= 0) {
        baris_nol = TINGGI - 1 - (int)((0 - min_y) / (max_y - min_y) * (TINGGI - 1));
        for (int i = 0; i < LEBAR; i++) {
            kanvas[baris_nol][i] = '-';
        }
    }

    for (int i = 0; i < LEBAR; i++) {
        double x = a + i * (b - a) / (LEBAR - 1);
        double y = f(x, koefisien, derajat);
        
        int j = TINGGI - 1 - (int)((y - min_y) / (max_y - min_y) * (TINGGI - 1));
        
        if (j >= 0 && j < TINGGI) {
            kanvas[j][i] = '*'; 
        }
    }

    cout << "\n=== GRAFIK FUNGSI f(x) ===" << endl;
    cout << "Rentang X: [" << a << ", " << b << "]\n\n";
    
    for (int j = 0; j < TINGGI; j++) {
        double y_val = max_y - j * (max_y - min_y) / (TINGGI - 1);
        cout << setw(8) << fixed << setprecision(2) << y_val << " | " << kanvas[j] << endl;
    }

    cout << "           ";
    for(int i = 0; i < LEBAR; i++) cout << "=";
    cout << endl;
    cout << "           " << left << setw(LEBAR/2) << a << right << setw(LEBAR/2) << b << endl;
}

void regulafalsi(const vector<double>& koefisien, int derajat, double a, double b, double toleransi) {
    if (f(a, koefisien, derajat) * f(b, koefisien, derajat) >= 0) {
        cout << "tidak ada akar akar persamaan dalam rentang " << a << " dan " << b << "\n";
        return;
    }
    
    gambarGrafikHorizontal(a, b, koefisien, derajat);
    
    double c = a;
    int iterasi = 0;
    cout << "\nIterasi ke- |      c      |     f(c)    " << endl;
    cout << "---------------------------------------" << endl;

    while (true) {
        double fa = f(a, koefisien, derajat);
        double fb = f(b, koefisien, derajat);

        c = (a * fb - b * fa) / (fb - fa);
        double fc = f(c, koefisien, derajat);

        iterasi++;
        cout << setw(10) << iterasi << " | " << setw(11) << fixed << setprecision(6) << c 
             << " | " << setw(11) << fc << endl;

        if (abs(fc) < toleransi) {
            break;
        }

        if (fa * fc < 0) {
            b = c; 
        } else {
            a = c;
        }

        if (iterasi > 1000) {
            cout << "Konvergensi lambat \n";
            break;
        }
    }
    cout << "\nAkar ditemukan pada x = " << setprecision(6) << c << endl;
}

int main() {
    int derajat;
    cout << "Mencari akar akar persamaan menggunakan metode Regula Falsi\n";
    cout << "Masukkan pangkat tertinggi : ";
    cin >> derajat;

    if (derajat > 100 || derajat < 0) {
        if (derajat > 100) {
            cout << "derajat yang anda masukkan melebihi kapasitas";
        } else if (derajat < 0) {
            cout << "derajat yang anda masukkan tidak valid";
        }
        return 0;
    }

    vector<double> koefisien(derajat + 1);
    for (int i = 0; i <= derajat; i++) {
        cout << "masukkan koefisien x^" << i << ": ";
        cin >> koefisien[i];
    }

    double a, b, toleransi;
    cout << "Masukkan batas bawah (a) : ";
    cin >> a;
    cout << "Masukkan batas atas (b)  : ";
    cin >> b;
    cout << "Masukkan toleransi error : ";
    cin >> toleransi;

    regulafalsi(koefisien, derajat, a, b, toleransi);

    return 0;
}
```
