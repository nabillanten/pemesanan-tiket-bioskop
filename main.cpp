#include <iostream>
using namespace std;

// Tipe Data Penonton (Child)
struct Penonton
{
    string id_penonton;
    string nama;
    string no_handphone;
    Penonton *next_penonton;
};

// Tipe Data Pemesanan (Relasi)
struct Pemesanan
{
    Penonton *penonton;
    Pemesanan *next_pemesanan;
};

// Tipe Data Film (Parent)
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

// Menambah Film (Parent)
Film *addFilm(string judul_film, string tanggal_tayang, string jam_tayang, string studio)
{

    static int counter = 1;

    Film *new_film = new Film();

    new_film->id_film = "F-" + string(3 - to_string(counter).length(), '0') + to_string(counter);
    new_film->judul_film = judul_film;
    new_film->tanggal_tayang = tanggal_tayang;
    new_film->jam_tayang = jam_tayang;
    new_film->studio = studio;
    new_film->next_film = new_film->prev_film = NULL;
    new_film->next_pemesanan = NULL;

    counter++;

    return new_film;
}

// Insert Last Film (Parent)
void insertFilm(string judul_film, string tanggal_tayang, string jam_tayang, string studio, Film *&head, Film *&tail)
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
}

// Cari Film (Parent)
Film *findFilm(string judul, Film *&head)
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

// Menampilkan List Film (Parent)
void printListFilm(Film *head)
{
    Film *temp = head;

    cout << "LIST FILM : " << endl
         << endl;

    while (temp != NULL)
    {
        cout << "ID Film : " << temp->id_film << endl;
        cout << "Judul Film : " << temp->judul_film << endl;
        cout << "Tanggal Tayang : " << temp->tanggal_tayang << endl;
        cout << "Jam Tayang : " << temp->jam_tayang << endl;
        cout << "Studio : " << temp->studio << endl;
        if (temp->next_film != NULL)
            cout << endl;
        temp = temp->next_film;
    }
    cout << endl;
    cout << "===============================================";
    cout << endl
         << endl;
}

// Menambah Penonton (Child)
Penonton *addPenonton(string nama, string no_handphone)
{
    static int counter = 1;

    Penonton *new_penonton = new Penonton();
    new_penonton->id_penonton = "C-" + string(3 - to_string(counter).length(), '0') + to_string(counter);
    new_penonton->nama = nama;
    new_penonton->no_handphone = no_handphone;

    new_penonton->next_penonton = NULL;

    counter++;

    return new_penonton;
}

// Insert Last Penonton (Child)
void insertPenonton(string nama, string no_handphone, Penonton *&head)
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
}

// Cari Penonton (Child)
Penonton *findPenonton(string nama, Penonton *head) // Perubahan: head tidak perlu reference di sini
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

// Menampilkan List Penonton (Child)
void printPenonton(Penonton *head)
{

    Penonton *temp = head;

    cout << "LIST PENONTON : " << endl
         << endl;

    while (temp != NULL)
    {
        cout << "Nama : " << temp->nama << endl;
        cout << "No Handphone : " << temp->no_handphone << endl;
        if (temp->next_penonton != NULL)
        {
            cout << endl;
        }
        temp = temp->next_penonton;
    }

    cout << endl;
    cout << "===============================================";
    cout << endl
         << endl;
}

// Insert Pemesanan (Relasi)
void insertPemesanan(Film *film, Penonton *penonton)
{

    if (film == NULL || penonton == NULL)
        return;

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
};

// Delete Pemesanan (Relasi)
void deletePemesanan(Film *film, Penonton *target)
{
    if (film == NULL || film->next_pemesanan == NULL)
    {
        cout << "Tidak ada relasi yang dihapus\n";
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
            cout << "Relasi dengan child \"" << target->nama << "\" berhasil dihapus\n";
            return;
        }
        prev = current;
        current = current->next_pemesanan;
    }
    cout << "Relasi tidak ditemukan\n";
}

// Find Pemesanan (Relasi)
void findPemesanan(Film *film, Penonton *penonton)
{
    if (film == NULL || penonton == NULL)
    {
        cout << "Data film atau penonton tidak valid.\n";
        return;
    }

    Pemesanan *current = film->next_pemesanan;

    while (current != NULL)
    {
        if (current->penonton == penonton)
        {
            cout << "Film \"" << film->judul_film
                 << "\" berelasi dengan penonton \""
                 << penonton->nama << "\".\n";
            return; // selesai
        }
        current = current->next_pemesanan;
    }

    cout << "Film \"" << film->judul_film
         << "\" tidak berelasi dengan penonton \""
         << penonton->nama << "\".\n";
    cout << endl;
    cout << "===============================================";
    cout << endl
         << endl;
}

// delete penonton (child)
void deletePenonton(Penonton *&headPenonton, Film *headFilm, Penonton *target)
{
    if (target == NULL)
    {
        cout << "Penonton tidak ditemukan\n";
        return;
    }

    if (headPenonton == NULL)
    {
        cout << "Tidak ada penonton yang dihapus\n";
        return;
    }

    Film *f = headFilm;
    while (f != NULL)
    {
        deletePemesanan(f, target);
        f = f->next_film;
    }

    Penonton *current = headPenonton;
    Penonton *prev = NULL;

    while (current != NULL)
    {
        if (current == target)
        {
            if (prev == NULL)
            {
                headPenonton = current->next_penonton;
            }
            else
            {
                prev->next_penonton = current->next_penonton;
            }

            delete current;
            cout << "Penonton \"" << target->nama << "\" berhasil dihapus\n";
            return;
        }

        prev = current;
        current = current->next_penonton;
    }

    cout << "Penonton tidak ditemukan\n";
}

// show all penonton (child)
void showAllPenonton(Penonton *headPenonton)
{
    if (headPenonton == NULL)
    {
        cout << "Tidak ada data penonton\n\n";
        return;
    }

    Penonton *p = headPenonton;
    int counter = 1;

    cout << "DATA SEMUA PENONTON (CHILD LIST):\n\n";

    while (p != NULL)
    {
        cout << counter++ << ". ID: " << p->id_penonton << "\n";
        cout << "   Nama: " << p->nama << "\n";
        cout << "   No HP: " << p->no_handphone << "\n\n";
        p = p->next_penonton;
    }
    cout << endl;
    cout << "===============================================";
    cout << endl
         << endl;
}

// Show penonton beserta Semua Film yang di tonton (child)
void showPenontonDanFilm(Penonton *headPenonton, Film *headFilm)
{
    if (headPenonton == NULL)
    {
        cout << "Tidak ada data penonton\n\n";
        return;
    }

    Penonton *p = headPenonton;
    cout << "--- LIST PENONTON DAN FILM YANG DITONTON ---\n\n";

    while (p != NULL)
    {
        cout << "Nama: " << p->nama << " (" << p->id_penonton << ")\n";
        cout << "No HP: " << p->no_handphone << "\n";

        bool adaRelasi = false;

        Film *f = headFilm;
        while (f != NULL)
        {
            Pemesanan *pm = f->next_pemesanan;

            while (pm != NULL)
            {
                // Cek apakah Pemesanan ini menunjuk ke Penonton saat ini (p)
                if (pm->penonton == p)
                {
                    if (!adaRelasi)
                    {
                        cout << "  Film yang ditonton:\n";
                        adaRelasi = true;
                    }
                    cout << "  - " << f->judul_film << " (ID Film: " << f->id_film << ", Studio: " << f->studio << ")\n";
                }
                pm = pm->next_pemesanan;
            }

            f = f->next_film;
        }

        if (!adaRelasi)
        {
            cout << "  Tidak menonton film\n";
        }

        cout << "\n";
        p = p->next_penonton;
    }
    cout << endl;
    cout << "===============================================";
    cout << endl
         << endl;
}

// count jumlah relasi penonton film tertentu (child)
int countRelasiPenonton(Penonton *target, Film *headFilm)
{
    int count = 0;

    Film *f = headFilm;

    while (f != NULL)
    {
        Pemesanan *pm = f->next_pemesanan;

        while (pm != NULL)
        {
            if (pm->penonton == target)
            {
                count++;
            }
            pm = pm->next_pemesanan;
        }

        f = f->next_film;
    }

    return count;
}

// penonton yang tidak memiliki relasi (child)
int countPenontonTanpaRelasi(Penonton *headPenonton, Film *headFilm)
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
        {
            total++;
        }

        p = p->next_penonton;
    }

    return total;
}


int main()
{

    // Doubly Linked List Film (Parent)
    Film *firstFilm = NULL;
    Film *lastFilm = NULL;

    // Singly Linked List Penonton (Child)
    Penonton *headPenonton = NULL;

    // Insert Film ke Doubly Linked List (Parent)
    insertFilm("Harry Potter", "02-12-2025", "20:30", "STD-01", firstFilm, lastFilm); // F-001
    insertFilm("Harry Potter II", "03-12-2025", "10:30", "STD-01", firstFilm, lastFilm); // F-002

    // print semua film ke layar
    printListFilm(firstFilm);

    // Insert Penonton Ke Singly Linked List (Child)
    insertPenonton("Nabil Lanten", "089657393880", headPenonton); // C-001
    insertPenonton("Brigitta Dwi Lestari", "08132466282", headPenonton); // C-002
    insertPenonton("Khalisa Assyifa", "085678926520", headPenonton); // C-003

    // print semua penonton ke layar
    printPenonton(headPenonton);

    // Cari Film dengan judul Harry Potter
    Film *f1 = findFilm("Harry Potter", firstFilm);

    // Cari Penonton dengna nama Nabil Lanten
    Penonton *p1 = findPenonton("Nabil Lanten", headPenonton);
    // Cari Penonton dengna nama Brigitta Dwi Lestari
    Penonton *p2 = findPenonton("Brigitta Dwi Lestari", headPenonton);

    // Insert Relasi : Film Harry Potter, dengan penonton Nabil Lanten
    insertPemesanan(f1, p1);

    // Insert Relasi : Film Harry Potter, dengan penonton Brigitta Dwi lestari
    insertPemesanan(f1, p2);

    // Print film yang telah di tonton
    cout << "Film " << firstFilm->judul_film << " telah ditonton oleh : " << firstFilm->next_pemesanan->penonton->nama << ", " << firstFilm->next_pemesanan->next_pemesanan->penonton->nama << endl;

    // Find Pemesanan : Mencari apakah Film Harry Potter memiliki relasi dengan penonton Nabil Lanten
    findPemesanan(f1, p1);

    // Delete Pemesanan : Menghapus relasi film Harry Potter dengan penonton dengan nama Nabil Lanten
    deletePemesanan(f1, p1);

    // Print film yang telah di tonton
    cout
        << "Film " << firstFilm->judul_film << " telah ditonton oleh : " << firstFilm->next_pemesanan->penonton->nama << endl;

    // Find Pemesanan : Mencari apakah Film Harry Potter memiliki relasi dengan penonton Nabil Lanten
    findPemesanan(f1, p1);

    // Tambah Film baru
    insertFilm("Now You See Me 3", "04-12-2025", "15:00", "STD-02", firstFilm, lastFilm); // F-003

    // Tambah Penonton (Untuk demo multi-relasi dan tanpa relasi)
    insertPenonton("Jeki", "081388879123", headPenonton); // C-004

    // Cari Pointer untuk data baru
    Film *f2 = findFilm("Harry Potter II", firstFilm); // F-002
    Film *f3 = findFilm("Now You See Me 3", firstFilm); // F-003
    Penonton *p3 = findPenonton("Khalisa Assyifa", headPenonton); // C-003
    Penonton *p4 = findPenonton("Jeki", headPenonton); // C-004

    // Tambah Relasi:
    // P2 (Brigitta) sudah nonton F1. Tambah dia nonton F2 juga.
    insertPemesanan(f2, p2);
    // P4 (Jeki) nonton F2 dan F3 (2 relasi)
    insertPemesanan(f2, p4);
    insertPemesanan(f3, p4);
    // P3 (Khalisa) nonton F3
    insertPemesanan(f3, p3);

    // Show All Penonton (List Child)
    showAllPenonton(headPenonton);

    // Find Penonton (Child)
    cout << "FIND PENONTON 'Jeki'\n";
    Penonton *targetFind = findPenonton("Jeki", headPenonton);
    if (targetFind != NULL) {
        cout << "Penonton Ditemukan:\n";
        cout << "ID Penonton: " << targetFind->id_penonton << "\n";
        cout << "Nama: " << targetFind->nama << "\n";
        cout << "No HP: " << targetFind->no_handphone << "\n\n";
    } else {
        cout << "Penonton tidak ditemukan.\n\n";
    }

    // Count Jumlah Relasi Penonton Film Tertentu
    cout << "COUNT JUMLAH RELASI UNTUK PENONTON 'Jeki' \n";
    int countJeki = countRelasiPenonton(p4, firstFilm);
    cout << "Jumlah pemesanan yang dimiliki oleh Jeki: " << countJeki << "\n\n";

    // Count Penonton yang Tidak Memiliki Relasi

    cout << "COUNT PENONTON YANG TIDAK MEMILIKI RELASI \n";
    int countTanpaRelasi = countPenontonTanpaRelasi(headPenonton, firstFilm);
    cout << "Jumlah penonton yang tidak memiliki relasi: " << countTanpaRelasi << "\n\n";

    // Show Penonton Beserta Semua Film yang Ditonton
    cout << "SHOW PENONTON BESERTA SEMUA FILM YANG DITONTON\n";
    showPenontonDanFilm(headPenonton, firstFilm);

    // Delete Penonton (Child)
    cout << "DELETE PENONTON 'Jeki' (C-004)\n";
    cout << "Cek relasi Jeki sebelum hapus:\n";
    findPemesanan(f2, p4); // Ada relasi di F-002
    findPemesanan(f3, p4); // Ada relasi di F-003

    // Hapus Penonton Jeki (C-004). Menghapus dari List Penonton DAN relasinya di semua Film.
    deletePenonton(headPenonton, firstFilm, p4);

    cout << "\nCek relasi Jeki setelah hapus :\n";
    findPemesanan(f2, p4);
    findPemesanan(f3, p4);

    cout << "\nLIST PENONTON Setelah Hapus 'Jeki':\n";
    showAllPenonton(headPenonton);

    return 0;
}
