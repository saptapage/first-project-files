#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

struct Task {
    string title;
    string deadline;
    bool isDone;
};

vector<Task> tasks;

void loadTasks() {
    ifstream file("todolist.txt");
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string statusStr, title, deadline;
        getline(ss, statusStr, ';');
        getline(ss, title, ';');
        getline(ss, deadline);

        Task task;
        task.isDone = (statusStr == "1");
        task.title = title;
        task.deadline = deadline;
        tasks.push_back(task);
    }

    file.close();
}

void saveTasks() {
    ofstream file("todolist.txt");
    for (const Task& task : tasks) {
        file << (task.isDone ? "1" : "0") << ";" << task.title << ";" << task.deadline << endl;
    }
    file.close();
}

void tampilkanTugas() {
    cout << "\n--- Daftar Tugas ---\n";
    if (tasks.empty()) {
        cout << "Belum ada tugas.\n";
        return;
    }

    for (size_t i = 0; i < tasks.size(); ++i) {
        cout << i + 1 << ". [" << (tasks[i].isDone ? "X" : " ") << "] "
             << tasks[i].title << " (Deadline: " << tasks[i].deadline << ")\n";
    }
}

void tambahTugas() {
    Task task;
    cout << "Judul tugas: ";
    cin.ignore();
    getline(cin, task.title);
    cout << "Deadline (YYYY-MM-DD): ";
    getline(cin, task.deadline);
    task.isDone = false;
    tasks.push_back(task);
    saveTasks();
    cout << "Tugas ditambahkan!\n";
}

void tandaiSelesai() {
    tampilkanTugas();
    int index;
    cout << "Masukkan nomor tugas yang ingin ditandai selesai: ";
    cin >> index;
    if (index < 1 || index > tasks.size()) {
        cout << "Nomor tidak valid.\n";
        return;
    }
    tasks[index - 1].isDone = true;
    saveTasks();
    cout << "Tugas ditandai selesai!\n";
}

void hapusTugas() {
    tampilkanTugas();
    int index;
    cout << "Masukkan nomor tugas yang ingin dihapus: ";
    cin >> index;
    if (index < 1 || index > tasks.size()) {
        cout << "Nomor tidak valid.\n";
        return;
    }
    tasks.erase(tasks.begin() + index - 1);
    saveTasks();
    cout << "Tugas dihapus!\n";
}

int main() {
    loadTasks();
    int pilihan;

    do {
        cout << "\n=== TO-DO LIST ===\n";
        cout << "1. Tampilkan Tugas\n";
        cout << "2. Tambah Tugas\n";
        cout << "3. Tandai Tugas Selesai\n";
        cout << "4. Hapus Tugas\n";
        cout << "5. Keluar\n";
        cout << "Pilih menu (1-5): ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: tampilkanTugas(); break;
            case 2: tambahTugas(); break;
            case 3: tandaiSelesai(); break;
            case 4: hapusTugas(); break;
            case 5: cout << "Keluar dari program.\n"; break;
            default: cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 5);

    return 0;
}

