#include <iostream>
#include <limits>
using namespace std;

int main() {
    int angkaRahasia, tebakan, percobaan = 0;

    cout << "=== GAME TEBAK ANGKA (MODE 2 PEMAIN) ===" << endl;
    
    // Pemain 1 memasukkan angka rahasia
    cout << "Pemain 1, masukkan angka rahasia (1 - 100): ";
    cin >> angkaRahasia;

    // Validasi angka
    while (angkaRahasia < 1 || angkaRahasia > 100) {
        cout << "Angka harus antara 1 - 100. Ulangi: ";
        cin >> angkaRahasia;
    }

    // Bersihkan layar agar pemain 2 tidak bisa melihat
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    cout << "Sekarang giliran Pemain 2 untuk menebak angka!\n";

    // Mulai menebak
    do {
        cout << "Tebakan kamu: ";
        cin >> tebakan;
        percobaan++;

        if (tebakan > angkaRahasia) {
            cout << "Terlalu besar!\n";
        } else if (tebakan < angkaRahasia) {
            cout << "Terlalu kecil!\n";
        } else {
            cout << "Selamat! Kamu menebak dengan benar dalam " << percobaan << " percobaan!\n";
        }

    } while (tebakan != angkaRahasia);

    return 0;
}

