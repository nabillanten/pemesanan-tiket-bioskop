#include <iostream>
#include <string>
#include <limits> // Untuk numeric_limits

using namespace std;

// ==========================================
// TIPE DATA & STRUKTUR
// ==========================================

struct Penonton
{
    string id_penonton;
    string nama;
    string no_handphone;
    Penonton *next_penonton;
};

struct Pemesanan
{
    Penonton *penonton;
    Pemesanan *next_pemesanan;
};

struct Film
{
    string id_film;
    string judul_film;
    string tanggal_tayang;
    string jam_tayang;
    string studio;
    Film *next_film;
    Film *prev_film;
    Pemesanan *next_pemesanan;
};

// ==========================================
// FUNGSI UTILITY (BANTUAN)
// ==========================================

void clearInputBuffer()
{
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void pause()
{
    cout << "\nTekan Enter untuk kembali...";
    cin.get();
}

// ==========================================
// PARENT SECTION (FILM)
// ==========================================

Film *addFilm(string judul_film, string tanggal_tayang, string jam_tayang, string studio) // GITTA
{
    static int counter = 1;
    Film *new_film = new Film();
    string numStr = to_string(counter);
    while (numStr.length() < 3)
        numStr = "0" + numStr;

    new_film->id_film = "F-" + numStr;
    new_film->judul_film = judul_film;
    new_film->tanggal_tayang = tanggal_tayang;
    new_film->jam_tayang = jam_tayang;
    new_film->studio = studio;
    new_film->next_film = new_film->prev_film = NULL;
    new_film->next_pemesanan = NULL;
    counter++;
    return new_film;
}

void insertFilm(string judul_film, string tanggal_tayang, string jam_tayang, string studio, Film *&head, Film *&tail) // GITTA
{
    Film *new_film = addFilm(judul_film, tanggal_tayang, jam_tayang, studio);
    if (tail == NULL)
    {
        head = tail = new_film;
    }
    else
    {
        tail->next_film = new_film;
        new_film->prev_film = tail;
        tail = new_film;
    }
    cout << ">> Film berhasil ditambahkan! (ID: " << new_film->id_film << ")\n";
}

Film *findFilmByJudul(string judul, Film *head) // GITTA
{
    Film *p = head;
    while (p != NULL)
    {
        if (p->judul_film == judul)
            return p;
        p = p->next_film;
    }
    return NULL;
}

void deleteFilm(Film *&head, Film *&tail, string judul_film) // GITTA
{
    if (head == NULL)
    {
        cout << ">> List film kosong!\n";
        return;
    }

    Film *current = findFilmByJudul(judul_film, head);

    if (current == NULL)
    {
        cout << ">> Film tidak ditemukan!\n";
        return;
    }

    Pemesanan *pemesanan = current->next_pemesanan;
    while (pemesanan != NULL)
    {
        Pemesanan *temp = pemesanan;
        pemesanan = pemesanan->next_pemesanan;
        delete temp;
    }
    current->next_pemesanan = NULL;

    if (current == head)
    {
        head = current->next_film;
        if (head != NULL)
            head->prev_film = NULL;
        else
            tail = NULL;
    }
    else if (current == tail)
    {
        tail = current->prev_film;
        tail->next_film = NULL;
    }
    else
    {
        current->prev_film->next_film = current->next_film;
        current->next_film->prev_film = current->prev_film;
    }

    delete current;
    cout << ">> Film berhasil dihapus beserta semua relasinya!\n";
}

void showAllFilm(Film *head) // GITTA
{
    if (head == NULL)
    {
        cout << ">> Belum ada film yang tersedia.\n";
        return;
    }
    Film *temp = head;
    int counter = 1;
    cout << "=== DAFTAR SEMUA FILM ===\n";
    while (temp != NULL)
    {
        cout << counter++ << ". [" << temp->id_film << "] " << temp->judul_film << endl;
        cout << "   " << temp->tanggal_tayang << " " << temp->jam_tayang << " | " << temp->studio << endl;
        temp = temp->next_film;
    }
    cout << "-------------------------\n";
}

void showPenontonFromFilm(Film *film) // GITTA
{
    if (film == NULL)
    {
        cout << ">> Film tidak ditemukan.\n";
        return;
    }
    cout << "Daftar Penonton di Film: " << film->judul_film << endl;
    Pemesanan *pm = film->next_pemesanan;
    if (pm == NULL)
        cout << "   (Kosong)\n";
    int i = 1;
    while (pm != NULL)
    {
        cout << "   " << i++ << ". " << pm->penonton->nama << endl;
        pm = pm->next_pemesanan;
    }
}

void showFilmFromPenonton(Penonton *penonton, Film *headFilm) // GITTA
{
    if (penonton == NULL)
    {
        cout << ">> Penonton tidak ditemukan.\n";
        return;
    }
    cout << "Riwayat Tontonan: " << penonton->nama << endl;
    Film *f = headFilm;
    bool found = false;
    while (f != NULL)
    {
        Pemesanan *pm = f->next_pemesanan;
        while (pm != NULL)
        {
            if (pm->penonton == penonton)
            {
                cout << "   - " << f->judul_film << endl;
                found = true;
            }
            pm = pm->next_pemesanan;
        }
        f = f->next_film;
    }
    if (!found)
        cout << "   (Belum ada riwayat)\n";
}

// ==========================================
// CHILD SECTION (PENONTON)
// ==========================================

Penonton *addPenonton(string nama, string no_handphone) // KHALISA
{
    static int counter = 1;
    Penonton *new_penonton = new Penonton();
    string numStr = to_string(counter);
    while (numStr.length() < 3)
        numStr = "0" + numStr;

    new_penonton->id_penonton = "C-" + numStr;
    new_penonton->nama = nama;
    new_penonton->no_handphone = no_handphone;
    new_penonton->next_penonton = NULL;
    counter++;
    return new_penonton;
}

void insertPenonton(string nama, string no_handphone, Penonton *&head) // KHALISA
{
    Penonton *new_penonton = addPenonton(nama, no_handphone);
    if (head == NULL)
    {
        head = new_penonton;
    }
    else
    {
        Penonton *temp = head;
        while (temp->next_penonton != NULL)
        {
            temp = temp->next_penonton;
        }
        temp->next_penonton = new_penonton;
    }
    cout << ">> Penonton berhasil ditambahkan! (ID: " << new_penonton->id_penonton << ")\n";
}

Penonton *findPenonton(string nama, Penonton *head) // KHALISA
{
    Penonton *p = head;
    while (p != NULL)
    {
        if (p->nama == nama)
            return p;
        p = p->next_penonton;
    }
    return NULL;
}

void showAllPenonton(Penonton *headPenonton) // KHALISA
{
    if (headPenonton == NULL)
    {
        cout << ">> Tidak ada data penonton.\n";
        return;
    }
    Penonton *p = headPenonton;
    int counter = 1;
    cout << "=== DATA PENONTON ===\n";
    while (p != NULL)
    {
        cout << counter++ << ". [" << p->id_penonton << "] " << p->nama << " (" << p->no_handphone << ")" << endl;
        p = p->next_penonton;
    }
    cout << "---------------------\n";
}

void deletePenonton(Penonton *&headPenonton, Film *headFilm, Penonton *target) // KHALISA
{
    if (target == NULL)
    {
        cout << ">> Penonton tidak ditemukan\n";
        return;
    }

    Film *f = headFilm;
    while (f != NULL)
    {
        Pemesanan *currP = f->next_pemesanan;
        Pemesanan *prevP = NULL;
        while (currP != NULL)
        {
            if (currP->penonton == target)
            {
                if (prevP == NULL)
                    f->next_pemesanan = currP->next_pemesanan;
                else
                    prevP->next_pemesanan = currP->next_pemesanan;
                Pemesanan *del = currP;
                currP = currP->next_pemesanan;
                delete del;
            }
            else
            {
                prevP = currP;
                currP = currP->next_pemesanan;
            }
        }
        f = f->next_film;
    }

    Penonton *current = headPenonton;
    Penonton *prev = NULL;
    while (current != NULL)
    {
        if (current == target)
        {
            if (prev == NULL)
                headPenonton = current->next_penonton;
            else
                prev->next_penonton = current->next_penonton;
            delete current;
            cout << ">> Data penonton berhasil dihapus.\n";
            return;
        }
        prev = current;
        current = current->next_penonton;
    }
}

void showPenontonDanFilm(Penonton *headPenonton, Film *headFilm) // KHALISA
{
    Penonton *p = headPenonton;
    cout << "=== SEMUA CHILD BESERTA PARENT ===\n";
    while (p != NULL)
    {
        cout << "[" << p->nama << "]\n";
        bool ada = false;
        Film *f = headFilm;
        while (f != NULL)
        {
            Pemesanan *pm = f->next_pemesanan;
            while (pm != NULL)
            {
                if (pm->penonton == p)
                {
                    cout << "   - " << f->judul_film << endl;
                    ada = true;
                }
                pm = pm->next_pemesanan;
            }
            f = f->next_film;
        }
        if (!ada)
            cout << "   - Belum menonton film apapun\n";
        cout << endl;
        p = p->next_penonton;
    }
}

void countRelasiPenonton(Penonton *target, Film *headFilm) // KHALISA
{
    if (target == NULL)
        return;
    int count = 0;
    Film *f = headFilm;
    while (f != NULL)
    {
        Pemesanan *pm = f->next_pemesanan;
        while (pm != NULL)
        {
            if (pm->penonton == target)
                count++;
            pm = pm->next_pemesanan;
        }
        f = f->next_film;
    }
    cout << "Total tiket yang dibeli " << target->nama << ": " << count << endl;
}

void countPenontonTanpaRelasi(Penonton *headPenonton, Film *headFilm) // KHALISA
{
    int total = 0;
    Penonton *p = headPenonton;
    while (p != NULL)
    {
        bool ada = false;
        Film *f = headFilm;
        while (f != NULL)
        {
            Pemesanan *pm = f->next_pemesanan;
            while (pm != NULL)
            {
                if (pm->penonton == p)
                {
                    ada = true;
                    break;
                }
                pm = pm->next_pemesanan;
            }
            if (ada)
                break;
            f = f->next_film;
        }
        if (!ada)
            total++;
        p = p->next_penonton;
    }
    cout << "Jumlah penonton yang belum membeli tiket: " << total << " orang.\n";
}

// ==========================================
// RELATION SECTION (PEMESANAN)
// ==========================================

void insertPemesanan(Film *film, Penonton *penonton) // NABIL
{
    if (film == NULL || penonton == NULL)
        return;

    Pemesanan *check = film->next_pemesanan;
    while (check != NULL)
    {
        if (check->penonton == penonton)
        {
            cout << ">> Penonton ini sudah memesan film tersebut!\n";
            return;
        }
        check = check->next_pemesanan;
    }

    Pemesanan *new_pemesanan = new Pemesanan;
    new_pemesanan->penonton = penonton;
    new_pemesanan->next_pemesanan = NULL;

    if (film->next_pemesanan == NULL)
    {
        film->next_pemesanan = new_pemesanan;
    }
    else
    {
        Pemesanan *p = film->next_pemesanan;
        while (p->next_pemesanan != NULL)
        {
            p = p->next_pemesanan;
        }
        p->next_pemesanan = new_pemesanan;
    }
    cout << ">> Sukses! " << penonton->nama << " menonton " << film->judul_film << endl;
}

void deletePemesanan(Film *film, Penonton *target) // NABIL
{
    if (film == NULL || film->next_pemesanan == NULL)
    {
        cout << ">> Data tidak valid / Tidak ada relasi.\n";
        return;
    }

    Pemesanan *current = film->next_pemesanan;
    Pemesanan *prev = NULL;

    while (current != NULL)
    {
        if (current->penonton == target)
        {
            if (prev == NULL)
            {
                film->next_pemesanan = current->next_pemesanan;
            }
            else
            {
                prev->next_pemesanan = current->next_pemesanan;
            }
            delete current;
            cout << ">> Tiket berhasil dibatalkan.\n";
            return;
        }
        prev = current;
        current = current->next_pemesanan;
    }
    cout << ">> Relasi tidak ditemukan.\n";
}

void findPemesanan(Film *film, Penonton *penonton) // NABIL
{
    if (film == NULL || penonton == NULL)
        return;
    Pemesanan *curr = film->next_pemesanan;
    while (curr != NULL)
    {
        if (curr->penonton == penonton)
        {
            cout << "STATUS: ADA. " << penonton->nama << " tercatat menonton " << film->judul_film << endl;
            return;
        }
        curr = curr->next_pemesanan;
    }
    cout << "STATUS: TIDAK ADA. " << penonton->nama << " tidak menonton " << film->judul_film << endl;
}

void editPemesanan(Film *film, Penonton *penontonLama, Penonton *penontonBaru) // NABIL
{
    if (film == NULL || penontonLama == NULL || penontonBaru == NULL)
    {
        cout << ">> Data tidak valid.\n";
        return;
    }
    Pemesanan *pm = film->next_pemesanan;
    while (pm != NULL)
    {
        if (pm->penonton == penontonLama)
        {
            pm->penonton = penontonBaru;
            cout << ">> Berhasil transfer tiket film " << film->judul_film << " ke " << penontonBaru->nama << endl;
            return;
        }
        pm = pm->next_pemesanan;
    }
    cout << ">> Tiket lama tidak ditemukan.\n";
}

void showAllFilmWithPenonton(Film *headFilm) // NABIL
{
    Film *f = headFilm;
    cout << "=== SEMUA PARENT BESERTA CHILD ===\n";
    while (f != NULL)
    {
        cout << "[" << f->judul_film << "]\n";
        Pemesanan *pm = f->next_pemesanan;
        if (pm == NULL)
            cout << "   - Tidak ada penonton\n";
        else
        {
            while (pm != NULL)
            {
                cout << "   - " << pm->penonton->nama << endl;
                pm = pm->next_pemesanan;
            }
        }
        cout << endl;
        f = f->next_film;
    }
}

void countRelasiSetiapFilm(Film *headFilm) //NABIL
{
    Film *f = headFilm;
    cout << "=== JUMLAH PENONTON PER FILM ===\n";
    while (f != NULL)
    {
        int count = 0;
        Pemesanan *pm = f->next_pemesanan;
        while (pm != NULL)
        {
            count++;
            pm = pm->next_pemesanan;
        }
        cout << f->judul_film << ": " << count << " orang\n";
        f = f->next_film;
    }
}

// ==========================================
// MAIN FUNCTION (MENU UTAMA)
// ==========================================

int main()
{
    // Struktur Data
    Film *firstFilm = NULL;
    Film *lastFilm = NULL;
    Penonton *headPenonton = NULL;

    // Variabel Input
    int mainMenu;
    char subMenu;
    string inJudul, inTanggal, inJam, inStudio, inNama, inHP, inNamaBaru;
    Film *selectedFilm = NULL;
    Penonton *selectedPenonton = NULL;
    Penonton *newPenontonPtr = NULL;

    do
    {
        // TAMPILAN MENU UTAMA
        cout << "\n=====================================\n";
        cout << "SISTEM JADWAL PEMESANAN TIKET BIOSKOP        \n";
        cout << "=====================================\n";
        cout << "1. MENU PARENT (Kelola Film)\n";
        cout << "2. MENU CHILD (Kelola Penonton)\n";
        cout << "3. MENU RELASI (Transaksi & Laporan)\n";
        cout << "0. EXIT\n";
        cout << "====================================\n";
        cout << "Pilih Menu [1/2/3/0]: ";
        cin >> mainMenu;
        clearInputBuffer();

        if (mainMenu == 1)
        {
            // MENU PARENT
            do
            {
                cout << "\n--- [ MENU PARENT : FILM ] ---\n";
                cout << "a. Insert Film\n";
                cout << "b. Delete Film\n";
                cout << "c. Find Film\n";
                cout << "d. Show All Film\n";
                cout << "e. Show Penonton di Film Tertentu\n";
                cout << "f. Count Relasi per Film\n";
                cout << "x. Kembali ke Menu Utama\n";
                cout << "Pilihan: ";
                cin >> subMenu;
                clearInputBuffer();

                switch (subMenu)
                {
                case 'a': // Insert
                    cout << ">> Judul Film     : ";
                    getline(cin, inJudul);
                    cout << ">> Tanggal Tayang : ";
                    getline(cin, inTanggal);
                    cout << ">> Jam Tayang     : ";
                    getline(cin, inJam);
                    cout << ">> Studio         : ";
                    getline(cin, inStudio);
                    insertFilm(inJudul, inTanggal, inJam, inStudio, firstFilm, lastFilm);
                    break;
                case 'b': // Delete
                    cout << ">> Judul Film yg dihapus: ";
                    getline(cin, inJudul);
                    deleteFilm(firstFilm, lastFilm, inJudul);
                    break;
                case 'c': // Find
                    cout << ">> Cari Judul Film: ";
                    getline(cin, inJudul);
                    selectedFilm = findFilmByJudul(inJudul, firstFilm);
                    if (selectedFilm)
                        cout << "Ditemukan! ID: " << selectedFilm->id_film << ", Studio: " << selectedFilm->studio << endl;
                    else
                        cout << "Tidak ditemukan.\n";
                    break;
                case 'd': // Show All
                    showAllFilm(firstFilm);
                    break;
                case 'e': // Show Child by Parent
                    cout << ">> Masukan Judul Film: ";
                    getline(cin, inJudul);
                    selectedFilm = findFilmByJudul(inJudul, firstFilm);
                    showPenontonFromFilm(selectedFilm);
                    break;
                case 'f': // Count - NABIL
                    countRelasiSetiapFilm(firstFilm);
                    break;
                case 'x':
                    break;
                default:
                    cout << "Pilihan salah.\n";
                }
                if (subMenu != 'x')
                    pause();
            } while (subMenu != 'x');
        }
        else if (mainMenu == 2)
        {
            // MENU CHILD
            do
            {
                cout << "\n--- [ MENU CHILD : PENONTON ] ---\n";
                cout << "a. Insert Penonton\n";
                cout << "b. Delete Penonton\n";
                cout << "c. Find Penonton\n";
                cout << "d. Show All Penonton\n";
                cout << "e. Show Film yang ditonton (History User)\n";
                cout << "f. Count Film yang ditonton User\n";
                cout << "g. Count User tanpa Tiket\n";
                cout << "x. Kembali ke Menu Utama\n";
                cout << "Pilihan: ";
                cin >> subMenu;
                clearInputBuffer();

                switch (subMenu)
                {
                case 'a': // Insert
                    cout << ">> Nama Penonton : ";
                    getline(cin, inNama);
                    cout << ">> No Handphone  : ";
                    getline(cin, inHP);
                    insertPenonton(inNama, inHP, headPenonton);
                    break;
                case 'b': // Delete
                    cout << ">> Hapus Penonton (Nama): ";
                    getline(cin, inNama);
                    selectedPenonton = findPenonton(inNama, headPenonton);
                    deletePenonton(headPenonton, firstFilm, selectedPenonton);
                    break;
                case 'c': // Find
                    cout << ">> Cari Penonton (Nama): ";
                    getline(cin, inNama);
                    selectedPenonton = findPenonton(inNama, headPenonton);
                    if (selectedPenonton)
                        cout << "Ditemukan! ID: " << selectedPenonton->id_penonton << ", HP: " << selectedPenonton->no_handphone << endl;
                    else
                        cout << "Tidak ditemukan.\n";
                    break;
                case 'd': // Show All
                    showAllPenonton(headPenonton);
                    break;
                case 'e': // Show Parent by Child GITTA
                    cout << ">> Nama Penonton: ";
                    getline(cin, inNama);
                    selectedPenonton = findPenonton(inNama, headPenonton);
                    showFilmFromPenonton(selectedPenonton, firstFilm);
                    break;
                case 'f': // Count
                    cout << ">> Nama Penonton: ";
                    getline(cin, inNama);
                    selectedPenonton = findPenonton(inNama, headPenonton);
                    if (selectedPenonton)
                        countRelasiPenonton(selectedPenonton, firstFilm);
                    else
                        cout << "User tidak ditemukan.\n";
                    break;
                case 'g': // Count No Relation
                    countPenontonTanpaRelasi(headPenonton, firstFilm);
                    break;
                case 'x':
                    break;
                default:
                    cout << "Pilihan salah.\n";
                }
                if (subMenu != 'x')
                    pause();
            } while (subMenu != 'x');
        }
        else if (mainMenu == 3)
        {
            // MENU RELASI
            do
            {
                cout << "\n--- [ MENU RELASI : TRANSAKSI ] ---\n";
                cout << "a. Insert Relation (Beli Tiket)\n";
                cout << "b. Delete Relation (Batal Tiket)\n";
                cout << "c. Edit Relation (Ganti Nama di Tiket)\n";
                cout << "d. Find Relation (Cek Status Tiket)\n";
                cout << "e. Show All Parent beserta Child\n";
                cout << "f. Show All Child beserta Parent\n";
                cout << "x. Kembali ke Menu Utama\n";
                cout << "Pilihan: ";
                cin >> subMenu;
                clearInputBuffer();

                switch (subMenu)
                {
                case 'a': // Insert
                    cout << ">> Judul Film : ";
                    getline(cin, inJudul);
                    selectedFilm = findFilmByJudul(inJudul, firstFilm);
                    if (!selectedFilm)
                    {
                        cout << "Film tidak ada.\n";
                        break;
                    }
                    cout << ">> Nama Penonton : ";
                    getline(cin, inNama);
                    selectedPenonton = findPenonton(inNama, headPenonton);
                    if (!selectedPenonton)
                    {
                        cout << "Penonton tidak ada.\n";
                        break;
                    }
                    insertPemesanan(selectedFilm, selectedPenonton);
                    break;
                case 'b': // Delete
                    cout << ">> Judul Film : ";
                    getline(cin, inJudul);
                    selectedFilm = findFilmByJudul(inJudul, firstFilm);
                    cout << ">> Nama Penonton : ";
                    getline(cin, inNama);
                    selectedPenonton = findPenonton(inNama, headPenonton);
                    deletePemesanan(selectedFilm, selectedPenonton);
                    break;
                case 'c': // Edit
                    cout << ">> Judul Film : ";
                    getline(cin, inJudul);
                    selectedFilm = findFilmByJudul(inJudul, firstFilm);
                    cout << ">> Nama Penonton LAMA : ";
                    getline(cin, inNama);
                    selectedPenonton = findPenonton(inNama, headPenonton);
                    cout << ">> Nama Penonton BARU : ";
                    getline(cin, inNamaBaru);
                    newPenontonPtr = findPenonton(inNamaBaru, headPenonton);
                    editPemesanan(selectedFilm, selectedPenonton, newPenontonPtr);
                    break;
                case 'd': // Find
                    cout << ">> Judul Film : ";
                    getline(cin, inJudul);
                    selectedFilm = findFilmByJudul(inJudul, firstFilm);
                    cout << ">> Nama Penonton : ";
                    getline(cin, inNama);
                    selectedPenonton = findPenonton(inNama, headPenonton);
                    findPemesanan(selectedFilm, selectedPenonton);
                    break;
                case 'e': // Show Parent + Child
                    showAllFilmWithPenonton(firstFilm);
                    break;
                case 'f': // Show Child + Parent - KHALISA
                    showPenontonDanFilm(headPenonton, firstFilm);
                    break;
                case 'x':
                    break;
                default:
                    cout << "Pilihan salah.\n";
                }
                if (subMenu != 'x')
                    pause();
            } while (subMenu != 'x');
        }
        else if (mainMenu == 0)
        {
            cout << "Terima kasih!\n";
        }
        else
        {
            cout << "Menu tidak tersedia.\n";
            pause();
        }

    } while (mainMenu != 0);

    return 0;
}