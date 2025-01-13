#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

struct Urun {
char ad[80];
char birim[10];
float fiyat;
int stok;
};

void meyveStokSil(const char* urunAdi);
void sebzeStokSil(const char* urunAdi);
void meyveEkle();
void sebzeEkle();
void meyveListele();
void sebzeListele();
void meyveArama();
void sebzeArama();
void guncelleMeyve(const char* urunAdi, int yeniStok);
void guncelleSebze(const char* urunAdi, int yeniStok);

int main() {
char secim;

do {
system("clear");
cout << "  |********************************|\n";
cout << "  |******* Manav Otomasyonu *******|\n";
cout << "  |        1-Meyve Ekle            |\n";
cout << "  |        2-Sebze Ekle            |\n";
cout << "  |        3-Meyve Listele         |\n";
cout << "  |        4-Sebze Listele         |\n";
cout << "  |        5-Meyve Arama           |\n";
cout << "  |        6-Sebze Arama           |\n";
cout << "  |        7-Meyve Stok Silme      |\n";
cout << "  |        8-Sebze Stok Silme      |\n";
cout << "  |        9-Meyve Stok Guncelle   |\n";
cout << "  |        A-Sebze Stok Guncelle   |\n";
cout << "  |        0-Cikis                 |\n";
cout << "  |********************************|\n";
cout << "  |********************************|\n";
cout << "Seciminizi yapiniz: ";
cin >> secim;

switch (secim) {
case '1': 
meyveEkle();
break;
case '2': 
sebzeEkle();
break;
case '3': 
meyveListele();
break;
case '4': 
sebzeListele();
break;
case '5': 
meyveArama();
break;
case '6': 
sebzeArama();
break;
case '7': {
char meyveAdi[80];
cout << "Silmek istediginiz meyve adini giriniz: ";
cin >> meyveAdi;
meyveStokSil(meyveAdi);
break;
}
case '8': {
char sebzeAdi[80];
cout << "Silmek istediginiz sebze adini giriniz: ";
cin >> sebzeAdi;
sebzeStokSil(sebzeAdi);
break;
}
case '9': {
char meyveAdi[80];
int yeniStok;
cout << "Stok miktarini guncellemek istediğiniz meyve adini giriniz: ";
cin >> meyveAdi;
cout << "Yeni stok miktarini giriniz: ";
cin >> yeniStok;
guncelleMeyve(meyveAdi, yeniStok);
break;
}
case 'A': {
char sebzeAdi[80];
int yeniStok;
cout << "Stok miktarini güncellemek istediğiniz sebze adini giriniz: ";
cin >> sebzeAdi;
cout << "Yeni stok miktarini giriniz: ";
cin >> yeniStok;
guncelleSebze(sebzeAdi, yeniStok);
break;
}
case '0': 
cout << "Cıkıs yapıiliyor..." << endl;
break;
default: 
cout << "Gecersiz secim, tekrar deneyin." << endl;
break;
}

} while (secim != '0');

return 0;
}

void guncelleMeyve(const char* urunAdi, int yeniStok) {
ifstream oku("meyveler.dat", ios::binary);
ofstream gecici("gecici.dat", ios::binary);
Urun urun;
bool bulundu = false;

if (!oku) {
cout << "Meyve dosyasi acılamadi!" << endl;
return;
}

while (oku.read((char*)&urun, sizeof(urun))) {
if (strcmp(urun.ad, urunAdi) == 0) {
urun.stok = yeniStok;
cout << urunAdi << " adli meyvenin yeni stok miktarı: " << yeniStok << endl;
bulundu = true;
}
gecici.write((char*)&urun, sizeof(urun));
}

oku.close();
gecici.close();

if (!bulundu) {
cout << urunAdi << " adli meyve bulunamadi" << endl;
remove("gecici.dat");
return;
}

remove("meyveler.dat");
rename("gecici.dat", "meyveler.dat");

cout << urunAdi << " adlı meyve  guncellendi" << endl;
}

void guncelleSebze(const char* urunAdi, int yeniStok) {
ifstream oku("sebzeler.dat", ios::binary);
ofstream gecici("gecici.dat", ios::binary);
Urun urun;
bool bulundu = false;

if (!oku) {
cout << "Sebze dosyasi açılamadi!" << endl;
return;
}
while (oku.read((char*)&urun, sizeof(urun))) {
if (strcmp(urun.ad, urunAdi) == 0) {
urun.stok = yeniStok;
cout << urunAdi << " adli sebzenin yeni stok miktarı: " << yeniStok << endl;
bulundu = true;
}
gecici.write((char*)&urun, sizeof(urun));
}

oku.close();
gecici.close();

if (!bulundu) {
cout << urunAdi << " adli sebze bulunamadi" << endl;
remove("gecici.dat");
return;
}

remove("sebzeler.dat"); // Eski dosyayı sil
rename("gecici.dat", "sebzeler.dat"); // Geçici dosyayı orijinal dosyaya dönüştür

cout << urunAdi << " adlı sebze güncellendi." << endl;
}

void meyveEkle() {
ofstream yaz("meyveler.dat", ios::binary | ios::app);
Urun urun;
char secim;

do {
system("clear");
cout << "Meyve Adi Giriniz: ";
cin >> urun.ad;
cout << "Kilogram Miktari Giriniz: ";
 cin >> urun.birim;
cout << "Fiyat Giriniz: ";
cin >> urun.fiyat;
cout << "Stok Miktari Giriniz (KG): ";
cin >> urun.stok;

yaz.write((char*)&urun, sizeof(urun));

cout << "Baska Meyve Eklemek Ister Misiniz? (E/H): ";
cin >> secim;
} while (secim == 'E' || secim == 'e');

yaz.close();
}

void sebzeEkle() {
ofstream yaz("sebzeler.dat", ios::binary | ios::app);
Urun urun;
char secim;

    do {
system("clear");
cout << "Sebze Adi Giriniz: ";
cin >> urun.ad;
cout << "Kilogram Miktari Giriniz: ";
cin >> urun.birim;
cout << "Fiyat Giriniz: ";
cin >> urun.fiyat;
cout << "Stok Miktari Giriniz (KG): ";
cin >> urun.stok;

yaz.write((char*)&urun, sizeof(urun));

cout << "Baska Sebze Eklemek Ister Misiniz? (E/H): ";
cin >> secim;
} while (secim == 'E' || secim == 'e');

yaz.close();
}

void meyveListele() {
ifstream oku("meyveler.dat", ios::binary);
Urun urun;

if (!oku) {
cout << "Meyve dosyasi acılamadi!" << endl;
return;
}

oku.seekg(0, ios::end);
int kayits = oku.tellg() / sizeof(urun);

if (kayits > 0) {
cout << "Toplam Meyve Sayisi: " << kayits << endl;
for (int i = 0; i < kayits; i++) {
oku.seekg(-((i + 1) * sizeof(urun)), ios::end);
oku.read((char*)&urun, sizeof(urun));
cout << i + 1 << ". Meyve Bilgileri: " << endl;
cout << "Ad: " << urun.ad << endl;
cout << "Birim: " << urun.birim << endl;
cout << "Fiyat: " << urun.fiyat << " TL" << endl;
cout << "Stok: " << urun.stok << " adet" << endl;
}
} else {
cout << "Meyve kaydi bulunamadi" << endl;
}

oku.close();

cout << "\nAna menuye donmek için bir tusa basiniz";
char secim;
cin >> secim;
}


void sebzeListele() {
ifstream oku("sebzeler.dat", ios::binary);
Urun urun;

if (!oku) {
cout << "Sebze dosyasi acılamadi!" << endl;
return;
}
oku.seekg(0, ios::end);
int kayits = oku.tellg() / sizeof(urun);

if (kayits > 0) {
cout << "Toplam Sebze Sayısı: " << kayits << endl;
for (int i = 0; i < kayits; i++) {
oku.seekg(-((i + 1) * sizeof(urun)), ios::end);
oku.read((char*)&urun, sizeof(urun));
cout << i + 1 << ". Sebze Bilgileri: " << endl;
cout << "Ad: " << urun.ad << endl;
cout << "Birim: " << urun.birim << endl;
cout << "Fiyat: " << urun.fiyat << " TL" << endl;
cout << "Stok: " << urun.stok << " adet" << endl;
}
} else {
cout << "Sebze kaydi bulunamadi" << endl;
}

oku.close();

cout << "\n Ana menuye donmek için bir tusa basiniz.";
char secim;
cin >> secim;
}


void meyveArama() {
ifstream oku("meyveler.dat", ios::binary);
Urun urun;
char arananAd[80];

cout << "Aramak istediginiz meyve adini giriniz: ";
cin >> arananAd;

if (!oku) {
cout << "Meyve dosyası açılamadi!" << endl;
return;
}

bool bulundu = false;

while (oku.read((char*)&urun, sizeof(urun))) {
if (strcmp(urun.ad, arananAd) == 0) {
cout << "Bulunan Meyve Bilgileri: " << endl;
cout << "Ad: " << urun.ad << endl;
cout << "Birim: " << urun.birim << endl;
cout << "Fiyat: " << urun.fiyat << " TL" << endl;
cout << "Stok: " << urun.stok << " adet" << endl;
bulundu = true;
break;
}
}

if (!bulundu) {
cout << "Meyve bulunamadi" << endl;
}

oku.close();

cout << "Ana menuye donmek için bir tusa basiniz...";
char secim;
cin >> secim;
}

void sebzeArama() {
ifstream oku("sebzeler.dat", ios::binary);
Urun urun;
char arananAd[80];

cout << "Aramak istediginiz sebze adini giriniz: ";
cin >> arananAd;

if (!oku) {
cout << "Sebze dosyasi acilamadi!" << endl;
return;
}

int bulundu = 0;

oku.seekg(0, ios::end);
int kayits = oku.tellg() / sizeof(urun);

if (kayits > 0) {
for (int i = 0; i < kayits; i++) {
oku.seekg(-((i + 1) * sizeof(urun)), ios::end);
oku.read((char*)&urun, sizeof(urun));

if (strcmp(urun.ad, arananAd) == 0) {
cout << "Bulunan Sebze Bilgileri: " << endl;
cout << "Ad: " << urun.ad << endl;
cout << "Birim: " << urun.birim << endl;
cout << "Fiyat: " << urun.fiyat << " TL" << endl;
cout << "Stok: " << urun.stok << " adet" << endl;
bulundu = 1;
break;
}
}
}

if (!bulundu) {
cout << "Sebze bulunamadi" << endl;
}
oku.close();

cout << "Ana menuye donmek için bir tusa basiniz...";
cin.get(); // Kullanıcıdan tuş bekler
cin.ignore(); // Geçerli tuşu alır, bekleyen yeni satırları engeller
}



void meyveStokSil(const char* urunAdi) {
ifstream oku("meyveler.dat", ios::binary);
ofstream gecici("gecici.dat", ios::binary);
Urun urun;
bool bulundu = false;

if (!oku) {
cout << "Meyve dosyasi acilamadi!" << endl;
return;
}

while (oku.read((char*)&urun, sizeof(urun))) {
if (strcmp(urun.ad, urunAdi) == 0) {
cout << urunAdi << " adli meyve stoktan silindi." << endl;
bulundu = true;
} else {
gecici.write((char*)&urun, sizeof(urun));
}
}

oku.close();
gecici.close();

if (!bulundu) {
cout << urunAdi << " adli meyve bulunamadi" << endl;
remove("gecici.dat");
return;
}

remove("meyveler.dat");
rename("gecici.dat", "meyveler.dat");

cout << urunAdi << " adli meyve silindi." << endl;
}

void sebzeStokSil(const char* urunAdi) {
ifstream oku("sebzeler.dat", ios::binary);
ofstream gecici("gecici.dat", ios::binary);
Urun urun;
bool bulundu = false;

if (!oku) {
cout << "Sebze dosyasi acilamadi!" << endl;
return;
}

while (oku.read((char*)&urun, sizeof(urun))) {
if (strcmp(urun.ad, urunAdi) == 0) {
cout << urunAdi << " adli sebze stoktan silindi" << endl;
bulundu = true;
} else {
gecici.write((char*)&urun, sizeof(urun));
}
}

oku.close();
gecici.close();

if (!bulundu) {
cout << urunAdi << " adli sebze bulunamadi" << endl;
remove("gecici.dat");
return;
}
remove("sebzeler.dat");
rename("gecici.dat", "sebzeler.dat");
cout << urunAdi << " adli sebze silindi." << endl;
}
