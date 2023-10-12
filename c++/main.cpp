#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class Mahasiswa {
public:
    string nama;
    string NRP;
    string jurusan;

    Mahasiswa(string nama, string NRP, string jurusan) {
        Mahasiswa::nama = nama;
        Mahasiswa::NRP = NRP;
        Mahasiswa::jurusan = jurusan;
    }

    string stringify() {
        return "\n" + nama + " " + NRP + " " + jurusan;
    }
};

class DBase {
public:
    ifstream in;
    ofstream out;
    string fileName;

    DBase(const char *fileName) {
        DBase::fileName = fileName;
    }

    void save(Mahasiswa data) {
        DBase::out.open(DBase::fileName, ios::app);
        DBase::out << data.stringify();
        DBase::out.close();
    }

    void showAll() {
        DBase::in.open(DBase::fileName, ios::in);
        string nama, NRP, jurusan;
        int index = 1;

        while (!DBase::in.eof()) {
            DBase::in >> nama;
            DBase::in >> NRP;
            DBase::in >> jurusan;
            cout << index++ << ".\t" << nama << "\t" << NRP << "\t" << jurusan << endl;
        }
        DBase::in.close();
    }
};

int main(int argc, char const *argv[]) {
    // user input
    string nama, NRP, jurusan;
    // cout << "MASUKKAN DATA MAHASISWA" << endl;
    // cout << "Nama: ";
    // cin >> nama;
    // cout << "NRP: ";
    // cin >> NRP;
    // cout << "Jurusan: ";
    // cin >> jurusan;

    // deklarasi object
    Mahasiswa dataMahasiswa = Mahasiswa(nama, NRP, jurusan);
    DBase database = DBase("data.txt");

    // save data ke database
    // database.save(dataMahasiswa);

    // tampilkan seluruh data di database
    database.showAll();
    return 0;
}
