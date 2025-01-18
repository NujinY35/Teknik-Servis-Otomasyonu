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
        cout << "Se�iminiz: ";
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
            case 0: cout << "Program sonland�r�l�yor...\n"; 
			break;
            default: cout << "Ge�ersiz se�im!\n";
        }
    } while(secim != 0);
    
    return 0;
}

void menuGoster() {
    cout << "\n=== TEKN�K SERV�S OTOMASYONU ===\n";
    cout << "1. M��teri Ekle\n";
    cout << "2. M��terileri Listele\n";
    cout << "3. M��teri Ara\n";
    cout << "4. M��teri G�ncelle\n";
    cout << "5. M��teri Sil\n";
    cout << "6. Cihaz Ekle\n";
    cout << "7. Cihazlar� Listele\n";
    cout << "8. Cihaz Ara\n";
    cout << "9. Cihaz G�ncelle\n";
    cout << "10. Cihaz Sil\n";
    cout << "0. ��k��\n";
}

void musteriEkle() {
    Musteri musteri;
    ofstream dosya("musteriler.dat", ios::binary | ios::app);
    
    cout << "\nM��teri No: ";
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
    
    cout << "M��teri kayd� ba�ar�yla eklendi.\n";
}

void musteriListele() {
    Musteri musteri;
    ifstream dosya("musteriler.dat", ios::binary);
    
    if(!dosya) {
        cout << "Dosya a��lamad� veya kay�t bulunamad�!\n";
        return;
    }
    
    cout << "\n=== M��TER� L�STES� ===\n";
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
    
    cout << "\nAranacak m��teri NO:";
    cin >> arananId;
    
    while(dosya.read((char*)&musteri, sizeof(Musteri))) {
        if(musteri.no == arananId) {
            cout << "\nM��teri bulundu:\n";
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
        cout << "M��teri bulunamad�!\n";
    }
    
    dosya.close();
}

void musteriGuncelle() {
    Musteri musteri;
    fstream dosya("musteriler.dat", ios::binary | ios::in | ios::out);
    int arananId;
    bool bulundu = false;
    
    cout << "\nG�ncellenecek m��teri NO: ";
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
            cout << "M��teri bilgileri g�ncellendi.\n";
            break;
        }
    }
    
    if(!bulundu) {
        cout << "M��teri bulunamad�!\n";
    }
    
    dosya.close();
}

void musteriSil() {
    int arananId;
    cout << "\nSilinecek m��teri NO: ";
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
        cout << "M��teri kayd� silindi.\n";
    } else {
        cout << "M��teri bulunamad�!\n";
    }
}

void cihazEkle() {
    Cihaz cihaz;
    ofstream dosya("cihazlar.dat", ios::binary | ios::app);
    
    cout << "\nCihaz NO: ";
    cin >> cihaz.no;
    
    cout << "M��teri NO: ";
    cin >> cihaz.musteriId;
    cin.ignore();
    
    cout << "Marka: ";
    cin.getline(cihaz.marka, 30);
    
    cout << "Model: ";
    cin.getline(cihaz.model, 30);
    
    cout << "Ar�za: ";
    cin.getline(cihaz.ariza, 200);
    
    cout << "Durum (Beklemede/Tamir Ediliyor/Tamamland�): ";
    cin.getline(cihaz.durum, 20);
    
    cout << "Geli� Tarihi (GG.AA.YYYY): ";
    cin.getline(cihaz.gelisTarihi, 11);
    
    cout << "�cret: ";
    cin >> cihaz.ucret;
    
    dosya.write((char*)&cihaz, sizeof(Cihaz));
    dosya.close();
    
    cout << "Cihaz kayd� ba�ar�yla eklendi.\n";
}

void cihazListele() {
    Cihaz cihaz;
    ifstream dosya("cihazlar.dat", ios::binary);
    
    if(!dosya) {
        cout << "Dosya a��lamad� veya kay�t bulunamad�!\n";
        return;
    }
    
    cout << "\n=== C�HAZ L�STES� ===\n";
    while(dosya.read((char*)&cihaz, sizeof(Cihaz))) {
        cout << "\nCihaz No: " << cihaz.no;
        cout << "\nM��teri No: " << cihaz.musteriId;
        cout << "\nMarka: " << cihaz.marka;
        cout << "\nModel: " << cihaz.model;
        cout << "\nAr�za: " << cihaz.ariza;
        cout << "\nDurum: " << cihaz.durum;
        cout << "\nGeli� Tarihi: " << cihaz.gelisTarihi;
        cout << "\n�cret: " << cihaz.ucret;
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
            cout << "M��teri NO: " << cihaz.musteriId << endl;
            cout << "Marka: " << cihaz.marka << endl;
            cout << "Model: " << cihaz.model << endl;
            cout << "Ar�za: " << cihaz.ariza << endl;
            cout << "Durum: " << cihaz.durum << endl;
            cout << "Geli� Tarihi: " << cihaz.gelisTarihi << endl;
            cout << "�cret: " << cihaz.ucret << endl;
            bulundu = true;
            break;
        }
    }
    
    if(!bulundu) {
        cout << "Cihaz bulunamad�!\n";
    }
    
    dosya.close();
}

void cihazGuncelle() {
    Cihaz cihaz;
    fstream dosya("cihazlar.dat", ios::binary | ios::in | ios::out);
    int arananId;
    bool bulundu = false;
    
    cout << "\nG�ncellenecek cihaz NO: ";
    cin >> arananId;
    
    while(dosya.read((char*)&cihaz, sizeof(Cihaz))) {
        if(cihaz.no == arananId) {
            cout << "Yeni bilgileri giriniz:\n";
            cihaz.no = arananId;
            
            cout << "M��teri No: ";
            cin >> cihaz.musteriId;
            cin.ignore();
            
            cout << "Marka: ";
            cin.getline(cihaz.marka, 30);
            
            cout << "Model: ";
            cin.getline(cihaz.model, 30);
            
            cout << "Ar�za: ";
            cin.getline(cihaz.ariza, 200);
            
            cout << "Durum (Beklemede/Tamir Ediliyor/Tamamland�): ";
            cin.getline(cihaz.durum, 20);
            
            cout << "Geli� Tarihi (GG.AA.YYYY): ";
            cin.getline(cihaz.gelisTarihi, 11);
            
            cout << "�cret: ";
            cin >> cihaz.ucret;
            
            dosya.seekp(-sizeof(Cihaz), ios::cur);
            dosya.write((char*)&cihaz, sizeof(Cihaz));
            bulundu = true;
            cout << "Cihaz bilgileri g�ncellendi.\n";
            break;
        }
    }
    
    if(!bulundu) {
        cout << "Cihaz bulunamad�!\n";
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
        cout << "Cihaz kayd� silindi.\n";
    } else {
        cout << "Cihaz bulunamad�!\n";
    }
}













