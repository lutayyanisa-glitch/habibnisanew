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


// ====================================================================
// 2. CLASS DOUBLE LINKED LIST (HEAD - TAIL) - TRANSAKSI & PESANAN
// ====================================================================
class ListPesanan {
private:
    NodePesanan* head;
    NodePesanan* tail;
    int counterPesanan;

public:
    ListPesanan() {
        head = nullptr;
        tail = nullptr;
        counterPesanan = 100;
    }

    string buatKodeBooking() {
        counterPesanan++;
        return "YPL-" + to_string(counterPesanan);
    }

    void tambahPesanan(Pesanan baru) {
        NodePesanan* newNode = new NodePesanan;
        newNode->data = baru;
        newNode->next = nullptr;
        newNode->prev = nullptr;

        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    // SEARCHING & GET NODE PESANAN UNTUK PROSES PEMBAYARAN
    NodePesanan* cariBooking(string kode) {
        NodePesanan* curr = head;
        while (curr != nullptr) {
            if (curr->data.kodeBooking == kode) {
                return curr;
            }
            curr = curr->next;
        }
        return nullptr;
    }

    void tampilkanSemuaPesanan() {
        if (head == nullptr) {
            cout << "\n[!] Belum ada tiket yang dipesan saat ini.\n";
            return;
        }

        NodePesanan* curr = head;
        cout << "\n============================================================================================================\n";
        cout << "                                         DAFTAR RIWAYAT BOOKING TIKET                                       \n";
        cout << "============================================================================================================\n";
        cout << setw(10) << left << "KODE" << setw(13) << "PEMESAN" << setw(22) << "PERTANDINGAN" << setw(12) << "KELAS" << setw(6) << "QTY" << setw(12) << "TOTAL" << setw(15) << "METODE" << setw(10) << "STATUS" << endl;
        cout << "------------------------------------------------------------------------------------------------------------\n";
        
        while (curr != nullptr) {
            cout << setw(10) << left << curr->data.kodeBooking 
                 << setw(13) << (curr->data.namaPemesan.length() > 11 ? curr->data.namaPemesan.substr(0,10)+"." : curr->data.namaPemesan)
                 << setw(22) << (curr->data.detailMatch.length() > 20 ? curr->data.detailMatch.substr(0,19)+"." : curr->data.detailMatch)
                 << setw(12) << curr->data.kelasDipilih 
                 << setw(6) << curr->data.jumlahTiket 
                 << "Rp." << setw(9) << curr->data.totalHarga 
                 << setw(15) << curr->data.metodeBayar
                 << "[" << curr->data.statusBayar << "]" << endl;
            curr = curr->next;
        }
        cout << "============================================================================================================\n";
    }
    void urutkanPesanan() {
        if (head == nullptr || head->next == nullptr) {
            cout << "[!] Data tidak cukup untuk diurutkan.\n";
            return;
        }

        bool swapped;
        NodePesanan* ptr1;
        NodePesanan* lptr = nullptr;

        do {
            swapped = false;
            ptr1 = head;

            while (ptr1->next != lptr) {
                if (ptr1->data.totalHarga < ptr1->next->data.totalHarga) {
                    Pesanan temp = ptr1->data;
                    ptr1->data = ptr1->next->data;
                    ptr1->next->data = temp;
                    swapped = true;
                }
                ptr1 = ptr1->next;
            }
            lptr = ptr1;
        } while (swapped);

        cout << "\n[✓] Data riwayat pesanan berhasil diurutkan berdasarkan nominal billing terbesar!\n";
    }

    bool batalkanPesanan(string kode, ListPertandingan& listMatch) {
        if (head == nullptr) return false;

        NodePesanan* curr = head;
        while (curr != nullptr) {
            if (curr->data.kodeBooking == kode) {
                
                // Jika status lunas/pending, kembalikan kuota tiket ke stadion
                if (curr->data.statusBayar != "KADALUARSA") {
                    NodePertandingan* matchNode = listMatch.dapatkanMatchById(curr->data.idPertandingan);
                    if (matchNode != nullptr) {
                        for (int i = 0; i < 3; i++) {
                            if (matchNode->data.kelas[i].namaKelas == curr->data.kelasDipilih) {
                                matchNode->data.kelas[i].sisaTiket += curr->data.jumlahTiket;
                                break;
                            }
                        }
                    }
                }

                // Lepas linkage node
                if (curr == head && curr == tail) {
                    head = nullptr;
                    tail = nullptr;
                } else if (curr == head) {
                    head = head->next;
                    head->prev = nullptr;
                } else if (curr == tail) {
                    tail = tail->prev;
                    tail->next = nullptr;
                } else {
                    curr->prev->next = curr->next;
                    curr->next->prev = curr->prev;
                }

                delete curr;
                return true;
            }
            curr = curr->next;
        }
        return false;
    }

    void eksporKeFile() {
        if (head == nullptr) {
            cout << "[!] Riwayat kosong, tidak ada file invoice yang dicetak.\n";
            return;
        }

        ofstream file;
        file.open("manifest_yesplis.txt", ios::out);

        if (!file.is_open()) {
            cout << "[!] Galat: Gagal menulis berkas teks invoice.\n";
            return;
        }

        file << "=========================================================================\n";
        file << "                    DATA MANIFEST TIKET STADION - YESPLIS                \n";
        file << "=========================================================================\n";
        
        NodePesanan* curr = head;
        int num = 1;
        while (curr != nullptr) {
            // Hanya mengekspor tiket yang transaksinya sudah LUNAS
            if (curr->data.statusBayar == "LUNAS") {
                file << num++ << ". Kode Booking : " << curr->data.kodeBooking << " [LUNAS]\n";
                file << "   Nama Pemesan : " << curr->data.namaPemesan << " (" << curr->data.nomorHp << ")\n";
                file << "   Match        : " << curr->data.detailMatch << "\n";
                file << "   Kategori     : " << curr->data.kelasDipilih << "\n";
                file << "   Kuantitas    : " << curr->data.jumlahTiket << " Tiket\n";
                file << "   Metode Bayar : " << curr->data.metodeBayar << "\n";
                file << "   Total Bayar  : Rp. " << curr->data.totalHarga << "\n";
                file << "-------------------------------------------------------------------------\n";
            }
            curr = curr->next;
        }
        
        file.close();
        cout << "\n[✓] Berhasil mengekspor manifest tiket LUNAS ke 'manifest_yesplis.txt'!\n";
    }
};

// ====================================================================
// UTILITY FUNCTION (Validasi Input)
// ====================================================================
void bersihkanInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// ====================================================================
// INTERFACE DRIVER PROGRAM (MAIN)
// ====================================================================