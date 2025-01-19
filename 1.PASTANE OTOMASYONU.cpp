#include <iomanip>
#include <cstring>
#include <stdlib.h>
#include <conio.h>
#include <stdio.h>
#include <fstream>
#include <iostream>

using namespace std;

struct Urun {
    char urun_adi[80];
    char urun_kodu[10];
    float fiyat;
    int stok;
};

void UrunEkle();
void UrunListeleme();
void UrunArama();
void UrunSil();
void UrunDuzenle();

int main() {
    char anamenu;
    do {
        system("cls");
        cout << "|-------Pastane Otomasyonu------|" << endl;
        cout << "|       Secim Yapiniz           |" << endl;
        cout << "|   1- Urun Ekleme              |" << endl;
        cout << "|   2- Urun Listeleme           |" << endl;
        cout << "|   3- Urun Arama               |" << endl;
        cout << "|   4- Urun Sil                 |" << endl;
        cout << "|   5- Urun Duzenle             |" << endl;
        cout << "|-------------------------------|" << endl;
        char secim;
        cin >> secim;

        switch (secim) {
            case '1':
                UrunEkle();
                break;
            case '2':
                UrunListeleme();
                break;
            case '3':
                UrunArama();
                break;
            case '4':
                UrunSil();
                break;
            case '5':
                UrunDuzenle();
                break;
            default:
                cout << "Gecersiz Secim" << endl;
                break;
        }

        cout << "Anamenuye Donmek icin: a basin, cikmak icin: c" << endl;
        anamenu = getche();

    } while (anamenu == 'a');

    return 0;
}

Urun urun;

void UrunEkle() {
    ofstream yaz("urun.dat", ios::binary | ios::app);
    char secim;
    int adet = 0;

    do {
        cout << "Urun Adi Giriniz" << endl;
        cin >> urun.urun_adi;
        cout << "Urun Kodu Giriniz" << endl;
        cin >> urun.urun_kodu;
        cout << "Urun Fiyati Giriniz" << endl;
        cin >> urun.fiyat;
        cout << "Urun Stok Miktarini Giriniz" << endl;
        cin >> urun.stok;
        yaz.write((char*)&urun, sizeof(urun));
        adet++;
        cout << "Baska Kayit Eklemek Istermisiniz (E/H)" << endl;
        secim = getche();
        cout << endl;
    } while (secim == 'e' || secim == 'E');

    cout << adet << " adet Urun Eklendi." << endl;
    yaz.close();
}
void UrunListeleme() {
    ifstream oku("urun.dat", ios::binary);
    oku.seekg(0, ios::end);
    int kayits = oku.tellg() / sizeof(urun);
    oku.seekg(0, ios::beg);
    cout << "Toplam Urun Kayit Sayisi: " << kayits << endl;

    if (kayits > 0) {
        for (int i = 0; i < kayits; i++) {
            oku.read((char*)&urun, sizeof(urun));

            cout << i + 1 << ". Urunun Bilgileri" << endl;
            cout << "Urun Adi: " << urun.urun_adi << endl;
            cout << "Urun Kodu: " << urun.urun_kodu << endl;
            cout << "Urun Fiyati: " << urun.fiyat << endl;
            cout << "Urun Stok: " << urun.stok << endl;
        }
    } else {
        cout << "Kayit Bulunamadi..." << endl;
    }

    oku.close();
}
void UrunArama() {
    ifstream oku("urun.dat", ios::binary);
    oku.seekg(0, ios::end);
    int kayits = oku.tellg() / sizeof(urun);
    oku.seekg(0, ios::beg);
    cout << "Aranan Urun Kodunu Giriniz" << endl;
    char urun_kodu[10];
    cin >> urun_kodu;

    if (kayits > 0) {
        bool bulundu = false;
        for (int i = 0; i < kayits; i++) {
            oku.read((char*)&urun, sizeof(urun));

            if (strcmp(urun.urun_kodu, urun_kodu) == 0) {
                cout << "Bulunan Urunun Bilgileri" << endl;
                cout << "Urun Adi: " << urun.urun_adi << endl;
                cout << "Urun Kodu: " << urun.urun_kodu << endl;
                cout << "Urun Fiyati: " << urun.fiyat << endl;
                cout << "Urun Stok: " << urun.stok << endl;
                bulundu = true;
                break;
            }
        }
        if (!bulundu)
            cout << "Kayit Bulunamadi..." << endl;
    } else {
        cout << "Kayit Bulunamadi..." << endl;
    }

    oku.close();
}
void UrunSil() {
    char urun_kodu[10];
    char secim = ' ';
    bool var = false;

    ifstream oku("urun.dat", ios::binary);
    oku.seekg(0, ios::end);
    int kayitsayisi = oku.tellg() / sizeof(urun);
    oku.seekg(0, ios::beg);
    cout << "Kaydini Sileceginiz Urun Kodunu Giriniz: ";
    cin >> urun_kodu;

    ofstream y_dosya("Yedek.dat", ios::binary | ios::app);

    for (int i = 0; i < kayitsayisi; i++) {
        oku.read((char*)&urun, sizeof(urun));

        if (strcmp(urun.urun_kodu, urun_kodu) == 0) {
            cout << endl;
            cout << "Urunun";
            cout << "\nAdi: " << urun.urun_adi;
            cout << "\nFiyat: " << urun.fiyat << endl;
            cout << "\nStok: " << urun.stok;
            cout << "\n\nSilmek Istediginiz Kayit Bu Mu? [E/H]: ";
            secim = getche();
            if (secim == 'E' || secim == 'e') {
                var = true;
            } else {
                y_dosya.write((char*)&urun, sizeof(urun));
            }
        } else {
            y_dosya.write((char*)&urun, sizeof(urun));
        }
    }

    oku.close();
    y_dosya.close();
    if (var) {
        remove("urun.dat");
        rename("Yedek.dat", "urun.dat");
        cout << "\nKayit Silindi." << endl;
    } else {
        remove("Yedek.dat");
        cout << "\nKayit Bulunamadi..." << endl;
    }
}
void UrunDuzenle() {
    char urun_kodu[10];
    char secim = ' ';
    bool var = false;

    ifstream oku("urun.dat", ios::binary);
    if (!oku) {
        cout << "Dosya acilamadi..." << endl;
        return;
    }

    oku.seekg(0, ios::end);
    int kayitsayisi = oku.tellg() / sizeof(urun);
    oku.seekg(0, ios::beg);
    cout << "Kaydini Duzelteceginiz Urun Kodunu Giriniz: ";
    cin >> urun_kodu;

    ofstream y_dosya("Yedek.dat", ios::binary | ios::app);

    for (int i = 0; i < kayitsayisi; i++) {
        oku.read((char*)&urun, sizeof(urun));

        if (strcmp(urun.urun_kodu, urun_kodu) == 0) {
            cout << endl;
            cout << "Urunun";
            cout << "\nAdi: " << urun.urun_adi;
            cout << "\nFiyat: " << urun.fiyat << endl;
            cout << "\nStok: " << urun.stok;
            cout << "\n\nDuzeltmek Istediginiz Kayit Bu Mu? [E/H]: ";
            secim = getche();
            if (secim == 'E' || secim == 'e') {
                var = true;
                cout << "\nUrun Adi Giriniz: ";
                cin >> urun.urun_adi;
                cout << "Urun Kodu Giriniz: ";
                cin >> urun.urun_kodu;
                cout << "Urun Fiyati Giriniz: ";
                cin >> urun.fiyat;
                cout << "Urun Stok Miktarini Giriniz: ";
                cin >> urun.stok;
            }
        }
        y_dosya.write((char*)&urun, sizeof(urun));
    }

    oku.close();
    y_dosya.close();

    if (var) {
        remove("urun.dat");
        rename("Yedek.dat", "urun.dat");
        cout << "\nKayit Duzeltildi." << endl;
    } else {
        remove("Yedek.dat");
        cout << "\nKayit Bulunamadi..." << endl;
    }
}

