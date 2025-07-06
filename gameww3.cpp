#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <map>

using namespace std;

struct Pemain {
    string nama;
    string role;
    bool hidup = true;
};

vector<Pemain> pemain;

void acakRole(int jumlahWerewolf) {
    vector<string> roleList;
    for (int i = 0; i < pemain.size(); i++) {
        if (i < jumlahWerewolf)
            roleList.push_back("Werewolf");
        else
            roleList.push_back("Villager");
    }

    srand(time(0));
    random_shuffle(roleList.begin(), roleList.end());

    for (int i = 0; i < pemain.size(); i++) {
        pemain[i].role = roleList[i];
    }
}

void tampilkanStatus() {
    cout << "\nStatus Pemain:\n";
    for (auto& p : pemain) {
        cout << "- " << p.nama << " (" << (p.hidup ? "Hidup" : "Mati") << ")\n";
    }
}

int hitungRole(string role) {
    int count = 0;
    for (auto& p : pemain) {
        if (p.hidup && p.role == role)
            count++;
    }
    return count;
}

bool cekGameOver() {
    int werewolf = hitungRole("Werewolf");
    int villager = hitungRole("Villager");

    if (werewolf == 0) {
        cout << "\n?? Villager menang!\n";
        return true;
    } else if (werewolf >= villager) {
        cout << "\n?? Werewolf menang!\n";
        return true;
    }
    return false;
}

void faseMalam() {
    cout << "\n?? Malam tiba...\n";
    cout << "Hanya Werewolf yang boleh memilih korban!\n";

    string korban;
    cout << "Masukkan nama pemain yang ingin dibunuh: ";
    cin.ignore();
    getline(cin, korban);

    for (auto& p : pemain) {
        if (p.nama == korban && p.hidup) {
            p.hidup = false;
            cout << korban << " telah dibunuh oleh Werewolf!\n";
            return;
        }
    }
    cout << "Nama tidak ditemukan atau sudah mati!\n";
}

void faseSiang() {
    cout << "\n?? Siang tiba...\n";
    tampilkanStatus();

    map<string, int> suara;
    string vote;
    for (auto& p : pemain) {
        if (p.hidup) {
            cout << p.nama << ", pilih siapa yang ingin kamu gantung: ";
            getline(cin, vote);
            suara[vote]++;
        }
    }

    string target;
    int maxVote = 0;
    for (auto& s : suara) {
        if (s.second > maxVote) {
            maxVote = s.second;
            target = s.first;
        }
    }

    for (auto& p : pemain) {
        if (p.nama == target && p.hidup) {
            p.hidup = false;
            cout << target << " telah digantung oleh warga!\n";
            return;
        }
    }

    cout << "Tidak ada yang digantung.\n";
}

int main() {
    int jumlahPemain, jumlahWerewolf;

    cout << "=== GAME WEREWOLF TEXT MODE ===\n";
    cout << "Jumlah pemain: ";
    cin >> jumlahPemain;

    cout << "Masukkan nama-nama pemain:\n";
    cin.ignore();
    for (int i = 0; i < jumlahPemain; i++) {
        Pemain p;
        cout << "Nama pemain " << i + 1 << ": ";
        getline(cin, p.nama);
        pemain.push_back(p);
    }

    cout << "Jumlah Werewolf: ";
    cin >> jumlahWerewolf;

    acakRole(jumlahWerewolf);

    cout << "\n=== ROLE PEMAIN ===\n";
    for (auto& p : pemain) {
        cout << p.nama << ": " << p.role << endl;
    }

    while (true) {
        if (cekGameOver()) break;
        faseMalam();
        if (cekGameOver()) break;
        faseSiang();
    }

    cout << "\n=== GAME OVER ===\n";
    return 0;
}

