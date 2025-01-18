#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>
using namespace std;

struct Musteri {
    int no;
    char ad[50];
    char soyad[50];
    char telefon[15];
    char adres[100];
};

struct Cihaz {
    int no;
    int musteriId;
    char marka[30];
    char model[30];
    char ariza[200];
    char durum[20];
    char gelisTarihi[11];
    float ucret;
};

void menuGoster();
void musteriEkle();
void musteriListele();
void musteriAra();
void musteriGuncelle();
void musteriSil();
void cihazEkle();
void cihazListele();
void cihazAra();
void cihazGuncelle();
void cihazSil();

int main() {
    setlocale(LC_ALL, "Turkish");
    int secim;
    
    do {
        menuGoster();
        cout << "Seçiminiz: ";
        cin >> secim;
        
        switch(secim) {
            case 1: musteriEkle(); 
			break;
            case 2: musteriListele(); 
			break;
            case 3: musteriAra(); 
			break;
            case 4: musteriGuncelle(); 
			break;
            case 5: musteriSil(); 
			break;
            case 6: cihazEkle(); 
			break;
            case 7: cihazListele(); 
			break;
            case 8: cihazAra(); 
			break;
            case 9: cihazGuncelle(); 
			break;
            case 10: cihazSil(); 
			break;
            case 0: cout << "Program sonlandýrýlýyor...\n"; 
			break;
            default: cout << "Geçersiz seçim!\n";
        }
    } while(secim != 0);
    
    return 0;
}

void menuGoster() {
    cout << "\n=== TEKNÝK SERVÝS OTOMASYONU ===\n";
    cout << "1. Müþteri Ekle\n";
    cout << "2. Müþterileri Listele\n";
    cout << "3. Müþteri Ara\n";
    cout << "4. Müþteri Güncelle\n";
    cout << "5. Müþteri Sil\n";
    cout << "6. Cihaz Ekle\n";
    cout << "7. Cihazlarý Listele\n";
    cout << "8. Cihaz Ara\n";
    cout << "9. Cihaz Güncelle\n";
    cout << "10. Cihaz Sil\n";
    cout << "0. Çýkýþ\n";
}

void musteriEkle() {
    Musteri musteri;
    ofstream dosya("musteriler.dat", ios::binary | ios::app);
    
    cout << "\nMüþteri No: ";
    cin >> musteri.no;
    cin.ignore();
    
    cout << "Ad: ";
    cin.getline(musteri.ad, 50);
    
    cout << "Soyad: ";
    cin.getline(musteri.soyad, 50);
    
    cout << "Telefon: ";
    cin.getline(musteri.telefon, 15);
    
    cout << "Adres: ";
    cin.getline(musteri.adres, 100);
    
    dosya.write((char*)&musteri, sizeof(Musteri));
    dosya.close();
    
    cout << "Müþteri kaydý baþarýyla eklendi.\n";
}

void musteriListele() {
    Musteri musteri;
    ifstream dosya("musteriler.dat", ios::binary);
    
    if(!dosya) {
        cout << "Dosya açýlamadý veya kayýt bulunamadý!\n";
        return;
    }
    
    cout << "\n=== MÜÞTERÝ LÝSTESÝ ===\n";
    while(dosya.read((char*)&musteri, sizeof(Musteri))) {
        cout << "\nNO:" << musteri.no;
        cout << "\nAd: " << musteri.ad;
        cout << "\nSoyad: " << musteri.soyad;
        cout << "\nTelefon: " << musteri.telefon;
        cout << "\nAdres: " << musteri.adres;
        cout << "\n-------------------\n";
    }
    
    dosya.close();
}

void musteriAra() {
    Musteri musteri;
    ifstream dosya("musteriler.dat", ios::binary);
    int arananId;
    bool bulundu = false;
    
    cout << "\nAranacak müþteri NO:";
    cin >> arananId;
    
    while(dosya.read((char*)&musteri, sizeof(Musteri))) {
        if(musteri.no == arananId) {
            cout << "\nMüþteri bulundu:\n";
            cout << "No: " << musteri.no << endl;
            cout << "Ad: " << musteri.ad << endl;
            cout << "Soyad: " << musteri.soyad << endl;
            cout << "Telefon: " << musteri.telefon << endl;
            cout << "Adres: " << musteri.adres << endl;
            bulundu = true;
            break;
        }
    }
    
    if(!bulundu) {
        cout << "Müþteri bulunamadý!\n";
    }
    
    dosya.close();
}

void musteriGuncelle() {
    Musteri musteri;
    fstream dosya("musteriler.dat", ios::binary | ios::in | ios::out);
    int arananId;
    bool bulundu = false;
    
    cout << "\nGüncellenecek müþteri NO: ";
    cin >> arananId;
    
    while(dosya.read((char*)&musteri, sizeof(Musteri))) {
        if(musteri.no == arananId) {
            cout << "Yeni bilgileri giriniz:\n";
            musteri.no = arananId;
            cin.ignore();
            
            cout << "Ad: ";
            cin.getline(musteri.ad, 50);
            
            cout << "Soyad: ";
            cin.getline(musteri.soyad, 50);
            
            cout << "Telefon: ";
            cin.getline(musteri.telefon, 15);
            
            cout << "Adres: ";
            cin.getline(musteri.adres, 100);
            
            dosya.seekp(-sizeof(Musteri), ios::cur);
            dosya.write((char*)&musteri, sizeof(Musteri));
            bulundu = true;
            cout << "Müþteri bilgileri güncellendi.\n";
            break;
        }
    }
    
    if(!bulundu) {
        cout << "Müþteri bulunamadý!\n";
    }
    
    dosya.close();
}

void musteriSil() {
    int arananId;
    cout << "\nSilinecek müþteri NO: ";
    cin >> arananId;
    
    ifstream eskiDosya("musteriler.dat", ios::binary);
    ofstream yeniDosya("temp.dat", ios::binary);
    Musteri musteri;
    bool bulundu = false;
    
    while(eskiDosya.read((char*)&musteri, sizeof(Musteri))) {
        if(musteri.no != arananId) {
            yeniDosya.write((char*)&musteri, sizeof(Musteri));
        } else {
            bulundu = true;
        }
    }
    
    eskiDosya.close();
    yeniDosya.close();
    
    remove("musteriler.dat");
    rename("temp.dat", "musteriler.dat");
    
    if(bulundu) {
        cout << "Müþteri kaydý silindi.\n";
    } else {
        cout << "Müþteri bulunamadý!\n";
    }
}

void cihazEkle() {
    Cihaz cihaz;
    ofstream dosya("cihazlar.dat", ios::binary | ios::app);
    
    cout << "\nCihaz NO: ";
    cin >> cihaz.no;
    
    cout << "Müþteri NO: ";
    cin >> cihaz.musteriId;
    cin.ignore();
    
    cout << "Marka: ";
    cin.getline(cihaz.marka, 30);
    
    cout << "Model: ";
    cin.getline(cihaz.model, 30);
    
    cout << "Arýza: ";
    cin.getline(cihaz.ariza, 200);
    
    cout << "Durum (Beklemede/Tamir Ediliyor/Tamamlandý): ";
    cin.getline(cihaz.durum, 20);
    
    cout << "Geliþ Tarihi (GG.AA.YYYY): ";
    cin.getline(cihaz.gelisTarihi, 11);
    
    cout << "Ücret: ";
    cin >> cihaz.ucret;
    
    dosya.write((char*)&cihaz, sizeof(Cihaz));
    dosya.close();
    
    cout << "Cihaz kaydý baþarýyla eklendi.\n";
}

void cihazListele() {
    Cihaz cihaz;
    ifstream dosya("cihazlar.dat", ios::binary);
    
    if(!dosya) {
        cout << "Dosya açýlamadý veya kayýt bulunamadý!\n";
        return;
    }
    
    cout << "\n=== CÝHAZ LÝSTESÝ ===\n";
    while(dosya.read((char*)&cihaz, sizeof(Cihaz))) {
        cout << "\nCihaz No: " << cihaz.no;
        cout << "\nMüþteri No: " << cihaz.musteriId;
        cout << "\nMarka: " << cihaz.marka;
        cout << "\nModel: " << cihaz.model;
        cout << "\nArýza: " << cihaz.ariza;
        cout << "\nDurum: " << cihaz.durum;
        cout << "\nGeliþ Tarihi: " << cihaz.gelisTarihi;
        cout << "\nÜcret: " << cihaz.ucret;
        cout << "\n-------------------\n";
    }
    
    dosya.close();
}

void cihazAra() {
    Cihaz cihaz;
    ifstream dosya("cihazlar.dat", ios::binary);
    int arananId;
    bool bulundu = false;
    
    cout << "\nAranacak cihaz NO: ";
    cin >> arananId;
    
    while(dosya.read((char*)&cihaz, sizeof(Cihaz))) {
        if(cihaz.no== arananId) {
            cout << "\nCihaz bulundu:\n";
            cout << "Cihaz No: " << cihaz.no << endl;
            cout << "Müþteri NO: " << cihaz.musteriId << endl;
            cout << "Marka: " << cihaz.marka << endl;
            cout << "Model: " << cihaz.model << endl;
            cout << "Arýza: " << cihaz.ariza << endl;
            cout << "Durum: " << cihaz.durum << endl;
            cout << "Geliþ Tarihi: " << cihaz.gelisTarihi << endl;
            cout << "Ücret: " << cihaz.ucret << endl;
            bulundu = true;
            break;
        }
    }
    
    if(!bulundu) {
        cout << "Cihaz bulunamadý!\n";
    }
    
    dosya.close();
}

void cihazGuncelle() {
    Cihaz cihaz;
    fstream dosya("cihazlar.dat", ios::binary | ios::in | ios::out);
    int arananId;
    bool bulundu = false;
    
    cout << "\nGüncellenecek cihaz NO: ";
    cin >> arananId;
    
    while(dosya.read((char*)&cihaz, sizeof(Cihaz))) {
        if(cihaz.no == arananId) {
            cout << "Yeni bilgileri giriniz:\n";
            cihaz.no = arananId;
            
            cout << "Müþteri No: ";
            cin >> cihaz.musteriId;
            cin.ignore();
            
            cout << "Marka: ";
            cin.getline(cihaz.marka, 30);
            
            cout << "Model: ";
            cin.getline(cihaz.model, 30);
            
            cout << "Arýza: ";
            cin.getline(cihaz.ariza, 200);
            
            cout << "Durum (Beklemede/Tamir Ediliyor/Tamamlandý): ";
            cin.getline(cihaz.durum, 20);
            
            cout << "Geliþ Tarihi (GG.AA.YYYY): ";
            cin.getline(cihaz.gelisTarihi, 11);
            
            cout << "Ücret: ";
            cin >> cihaz.ucret;
            
            dosya.seekp(-sizeof(Cihaz), ios::cur);
            dosya.write((char*)&cihaz, sizeof(Cihaz));
            bulundu = true;
            cout << "Cihaz bilgileri güncellendi.\n";
            break;
        }
    }
    
    if(!bulundu) {
        cout << "Cihaz bulunamadý!\n";
    }
    
    dosya.close();
}

void cihazSil() {
    int arananId;
    cout << "\nSilinecek cihaz NO: ";
    cin >> arananId;
    
    ifstream eskiDosya("cihazlar.dat", ios::binary);
    ofstream yeniDosya("temp.dat", ios::binary);
    Cihaz cihaz;
    bool bulundu = false;
    
    while(eskiDosya.read((char*)&cihaz, sizeof(Cihaz))) {
        if(cihaz.no != arananId) {
            yeniDosya.write((char*)&cihaz, sizeof(Cihaz));
        } else {
            bulundu = true;
        }
    }
    
    eskiDosya.close();
    yeniDosya.close();
    
    remove("cihazlar.dat");
    rename("temp.dat", "cihazlar.dat");
    
    if(bulundu) {
        cout << "Cihaz kaydý silindi.\n";
    } else {
        cout << "Cihaz bulunamadý!\n";
    }
}













