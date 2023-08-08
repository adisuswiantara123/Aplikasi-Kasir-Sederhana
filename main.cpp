#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

class User {
private:
    string nama;
    string nim;
    double saldo;

public:
    User(string nama, string nim, double saldo) {
        this->nama = nama;
        this->nim = nim;
        this->saldo = saldo;
    }

    bool login(string nim, string password) {
        return this->nim == nim && password == "058";
    }

    double getSaldo() {
        return saldo;
    }

    void setSaldo(double saldo) {
        this->saldo = saldo;
    }

    string getNIM() {
        return nim;
    }

    string getNama() {
        return nama;
    }
};

class Barang {
private:
    string nama;
    double harga;
    int stok;

public:
    Barang(string nama, double harga, int stok) {
        this->nama = nama;
        this->harga = harga;
        this->stok = stok;
    }

    string getNama() {
        return nama;
    }

    double getHarga() {
        return harga;
    }

    int getStok() {
        return stok;
    }

    void setStok(int stok) {
        this->stok = stok;
    }
};

class Transaksi {
private:
    User* user;
    vector<pair<Barang*, int>> belanjaan;
    string alamat;
    double totalHarga;

public:
    Transaksi(User* user, string alamat) {
        this->user = user;
        this->alamat = alamat;
        totalHarga = 0.0;
    }

    void tambahBarang(Barang* barang, int jumlah) {
        if (barang->getStok() >= jumlah) {
            belanjaan.push_back(make_pair(barang, jumlah));
            totalHarga += barang->getHarga() * jumlah;
            barang->setStok(barang->getStok() - jumlah);
        } else {
            cout << "Stok barang tidak mencukupi." << endl;
        }
    }

    double hitungTotalHarga() {
        return totalHarga;
    }

    void tampilkanStruk() {
        ofstream file("struk.txt");
        if (file.is_open()) {
            file << "Nama: " << user->getNama() << endl;
            file << "NIM: " << user->getNIM() << endl;
            file << "Alamat: " << alamat << endl;
            file << "==================================" << endl;
            file << setw(15) << left << "Nama Barang"
                 << setw(10) << left << "Harga"
                 << setw(10) << left << "Jumlah"
                 << setw(10) << left << "Subtotal" << endl;
            file << "==================================" << endl;
            for (const auto& item : belanjaan) {
                Barang* barang = item.first;
                int jumlah = item.second;
                double subtotal = barang->getHarga() * jumlah;
                file << setw(15) << left << barang->getNama()
                     << setw(10) << left << barang->getHarga()
                     << setw(10) << left << jumlah
                     << setw(10) << left << subtotal << endl;
            }
            file << "==================================" << endl;
            file << "Total Harga: " << totalHarga << endl;
            file << "Saldo: " << user->getSaldo() - totalHarga << endl;
            file.close();
            cout << "Struk telah disimpan dalam file struk.txt." << endl;
        } else {
            cout << "Gagal menyimpan struk." << endl;
        }
    }
};

int main() {
    User user("Adi", "adi", 100000.0);
    Barang rinso("Rinso", 15000.0, 10);
    Barang sabun("Sabun", 5000.0, 5);
    Barang pastaGigi("Kopi ", 10000.0, 8);
    Barang gula("Gula", 8000.0, 12);
    Barang beras("Beras", 20000.0, 15);

    string nim, password;
    cout << "Masukkan NIM: ";
    cin >> nim;
    cout << "Masukkan password: ";
    cin >> password;

    if (user.login(nim, password)) {
        string alamat;
        cout << "Masukkan alamat penerima: ";
        cin.ignore();
        getline(cin, alamat);

        Transaksi transaksi(&user, alamat);

        int pilihan = 0;
        while (pilihan != 7) {
            cout << endl;
            cout << "Menu:" << endl;
            cout << "1. Rinso" << endl;
            cout << "2. Sabun" << endl;
            cout << "3. Pasta Gigi" << endl;
            cout << "4. Gula" << endl;
            cout << "5. Beras" << endl;
            cout << "6. Tampilkan struk" << endl;
            cout << "7. Keluar" << endl;
            cout << "Pilihan Anda: ";
            cin >> pilihan;

            switch (pilihan) {
                case 1: {
                    int jumlah;
                    cout << "Masukkan jumlah Rinso: ";
                    cin >> jumlah;
                    transaksi.tambahBarang(&rinso, jumlah);
                    break;
                }
                case 2: {
                    int jumlah;
                    cout << "Masukkan jumlah Sabun: ";
                    cin >> jumlah;
                    transaksi.tambahBarang(&sabun, jumlah);
                    break;
                }
                case 3: {
                    int jumlah;
                    cout << "Masukkan jumlah Pasta Gigi: ";
                    cin >> jumlah;
                    transaksi.tambahBarang(&pastaGigi, jumlah);
                    break;
                }
                case 4: {
                    int jumlah;
                    cout << "Masukkan jumlah Gula: ";
                    cin >> jumlah;
                    transaksi.tambahBarang(&gula, jumlah);
                    break;
                }
                case 5: {
                    int jumlah;
                    cout << "Masukkan jumlah Beras: ";
                    cin >> jumlah;
                    transaksi.tambahBarang(&beras, jumlah);
                    break;
                }
                case 6: {
                    transaksi.tampilkanStruk();
                    break;
                }
                case 7: {
                    cout << "Terima kasih." << endl;
                    break;
                }
                default: {
                    cout << "Pilihan tidak valid." << endl;
                    break;
                }
            }
        }
    } else {
        cout << "NIM atau password tidak valid. Login gagal." << endl;
    }

    return 0;
}
