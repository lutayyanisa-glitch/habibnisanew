#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <limits>

using namespace std;

// Struct untuk Detail Kategori Tiket
struct KategoriTiket {
    string namaKelas; 
    int harga;
    int sisaTiket;
};

// Struct utama untuk Data Pertandingan
struct Pertandingan {
    int id;
    string timHome;
    string timAway;
    string stadion;
    string tanggal;
    string jam;
    KategoriTiket kelas[3]; 
};

// Node untuk Single Linked List (Manajemen Jadwal Pertandingan) dengan Head-Tail
struct NodePertandingan {
    Pertandingan data;
    NodePertandingan* next;
};

// Struct untuk Data Pesanan Tiket (Transaksi)
struct Pesanan {
    string kodeBooking;
    string namaPemesan;
    string nomorHp;
    int idPertandingan;
    string detailMatch;
    string kelasDipilih;
    int jumlahTiket;
    int totalHarga;
    string metodeBayar;
    string statusBayar; // PENDING, LUNAS, KADALUARSA
};

// Node untuk Double Linked List (Manajemen Antrean/Riwayat Pesanan) dengan Head-Tail
struct NodePesanan {
    Pesanan data;
    NodePesanan* next;
    NodePesanan* prev;
};

// ====================================================================
// 1. CLASS SINGLE LINKED LIST (HEAD - TAIL) - JADWAL PERTANDINGAN
// ====================================================================
class ListPertandingan {
private:
    NodePertandingan* head;
    NodePertandingan* tail;

public:
    ListPertandingan() {
        head = nullptr;
        tail = nullptr;
    }

    void tambahJadwal(int id, string home, string away, string stadion, string tgl, string jam,
                      string k1, int h1, int s1, string k2, int h2, int s2, string k3, int h3, int s3) {
        
        NodePertandingan* newNode = new NodePertandingan;
        newNode->data.id = id;
        newNode->data.timHome = home;
        newNode->data.timAway = away;
        newNode->data.stadion = stadion;
        newNode->data.tanggal = tgl;
        newNode->data.jam = jam;
        
        newNode->data.kelas[0] = {k1, h1, s1};
        newNode->data.kelas[1] = {k2, h2, s2};
        newNode->data.kelas[2] = {k3, h3, s3};
        
        newNode->next = nullptr;

        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    void tampilkanJadwal() {
        if (head == nullptr) {
            cout << "\n[!] Belum ada jadwal pertandingan yang tersedia.\n";
            return;
        }

        NodePertandingan* curr = head;
        cout << "\n==========================================================================================\n";
        cout << "                             JADWAL PERTANDINGAN SEPAK BOLA (YESPLIS)                     \n";
        cout << "==========================================================================================\n";
        
        while (curr != nullptr) {
            cout << " [" << curr->data.id << "] " << curr->data.timHome << " VS " << curr->data.timAway << endl;
            cout << "     Stadion : " << curr->data.stadion << " | Waktu: " << curr->data.tanggal << " @ " << curr->data.jam << endl;
            cout << "     Kategori Tiket Tersedia:\n";
            for (int i = 0; i < 3; i++) {
                cout << "       " << i + 1 << ". " << setw(15) << left << curr->data.kelas[i].namaKelas 
                     << " : Rp. " << setw(8) << curr->data.kelas[i].harga 
                     << " [Sisa: " << curr->data.kelas[i].sisaTiket << "]\n";
            }
            cout << "------------------------------------------------------------------------------------------\n";
            curr = curr->next;
        }
    }

    void cariPertandingan(string keyword) {
        if (head == nullptr) {
            cout << "[!] Data kosong.\n";
            return;
        }

        NodePertandingan* curr = head;
        bool ditemukan = false;
        
        cout << "\n-------------------------------------------------------------\n";
        cout << " Hasil Pencarian untuk Klub: '" << keyword << "'\n";
        cout << "-------------------------------------------------------------\n";

        while (curr != nullptr) {
            if (curr->data.timHome.find(keyword) != string::npos || curr->data.timAway.find(keyword) != string::npos) {
                cout << " -> ID [" << curr->data.id << "] " << curr->data.timHome << " VS " << curr->data.timAway << endl;
                cout << "    Stadion: " << curr->data.stadion << " (" << curr->data.tanggal << ")\n";
                ditemukan = true;
            }
            curr = curr->next;
        }

        if (!ditemukan) {
            cout << "[!] Tidak ada pertandingan yang melibatkan klub '" << keyword << "'.\n";
        }
        cout << "-------------------------------------------------------------\n";
    }

    NodePertandingan* dapatkanMatchById(int id) {
        NodePertandingan* curr = head;
        while (curr != nullptr) {
            if (curr->data.id == id) {
                return curr;
            }
            curr = curr->next;
        }
        return nullptr;
    }
};
