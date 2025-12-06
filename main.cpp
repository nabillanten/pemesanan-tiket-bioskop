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

// ===== RELATION SECTION START =====

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

// ===== RELATION SECTION END =====

// ===== PARENT SECTION START =====

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

// 1. DELETE FILM (PARENT)
// Menghapus film dari list parent, termasuk seluruh relasi yang berhubungan dengan film tersebut
void deleteFilm(Film *&head, Film *&tail, string judul_film, Penonton *&headPenonton)
{
    if (head == NULL)
    {
        cout << "List film kosong!" << endl;
        return;
    }

    Film *current = head;
    Film *prev = NULL;

    // Cari film yang akan dihapus
    while (current != NULL && current->judul_film != judul_film)
    {
        prev = current;
        current = current->next_film;
    }

    // Jika film tidak ditemukan
    if (current == NULL)
    {
        cout << "Film dengan judul '" << judul_film << "' tidak ditemukan!" << endl;
        return;
    }

    // Hapus semua relasi pemesanan yang terkait dengan film ini
    Pemesanan *pemesanan = current->next_pemesanan;
    while (pemesanan != NULL)
    {
        Pemesanan *temp = pemesanan;
        pemesanan = pemesanan->next_pemesanan;
        delete temp;
    }
    current->next_pemesanan = NULL;

    // Hapus node film dari doubly linked list
    if (prev == NULL)
    { // Film berada di head
        head = current->next_film;
        if (head != NULL)
        {
            head->prev_film = NULL;
        }
        else
        {
            tail = NULL; // List menjadi kosong
        }
    }
    else if (current->next_film == NULL)
    { // Film berada di tail
        tail = current->prev_film;
        if (tail != NULL)
        {
            tail->next_film = NULL;
        }
    }
    else
    { // Film di tengah
        prev->next_film = current->next_film;
        current->next_film->prev_film = prev;
    }

    cout << "Film '" << judul_film << "' berhasil dihapus beserta semua relasinya!" << endl;
    delete current;
}

// 2. FIND FILM (PARENT) - Versi alternatif dengan pencarian lebih fleksibel
// Mencari node film berdasarkan judul atau id_film
Film *findFilmByJudul(string judul, Film *&head)
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

// 3. SHOW ALL FILM (LIST PARENT) - Versi lebih informatif
// Menampilkan semua film yang ada di list parent dengan informasi lebih lengkap
void showAllFilm(Film *head)
{
    if (head == NULL)
    {
        cout << "Belum ada film yang tersedia!" << endl;
        cout << "===============================================" << endl
             << endl;
        return;
    }

    Film *temp = head;
    int counter = 1;

    cout << "DAFTAR SEMUA FILM (PARENT LIST):" << endl
         << endl;

    while (temp != NULL)
    {
        cout << counter++ << ". ID Film       : " << temp->id_film << endl;
        cout << "   Judul Film    : " << temp->judul_film << endl;
        cout << "   Tanggal Tayang: " << temp->tanggal_tayang << endl;
        cout << "   Jam Tayang    : " << temp->jam_tayang << endl;
        cout << "   Studio        : " << temp->studio << endl;

        // Tampilkan jumlah penonton yang memesan film ini
        int countPenonton = 0;
        Pemesanan *p = temp->next_pemesanan;
        while (p != NULL)
        {
            countPenonton++;
            p = p->next_pemesanan;
        }
        cout << "   Jumlah Penonton: " << countPenonton << " orang" << endl
             << endl;

        temp = temp->next_film;
    }
    cout << "===============================================" << endl
         << endl;
}

// 4. SHOW PENONTON DARI FILM TERTENTU
// Menampilkan daftar penonton yang menonton film tertentu melalui relasi pada parent film tersebut
void showPenontonFromFilm(Film *film)
{
    if (film == NULL)
    {
        cout << "Film tidak ditemukan!" << endl;
        return;
    }

    cout << "DAFTAR PENONTON FILM: " << film->judul_film << endl;
    cout << "ID Film: " << film->id_film << endl;
    cout << "Studio: " << film->studio << " | " << film->tanggal_tayang << " " << film->jam_tayang << endl;
    cout << "===============================================" << endl;

    Pemesanan *pemesanan = film->next_pemesanan;

    if (pemesanan == NULL)
    {
        cout << "Belum ada penonton yang memesan film ini." << endl
             << endl;
        return;
    }

    int counter = 1;
    while (pemesanan != NULL)
    {
        cout << counter++ << ". ID Penonton : " << pemesanan->penonton->id_penonton << endl;
        cout << "   Nama        : " << pemesanan->penonton->nama << endl;
        cout << "   No. HP      : " << pemesanan->penonton->no_handphone << endl
             << endl;
        pemesanan = pemesanan->next_pemesanan;
    }
    cout << "===============================================" << endl
         << endl;
}

// 5. SHOW FILM YANG DITONTON OLEH PENONTON TERTENTU
// Mencari penonton tertentu lalu menampilkan daftar film yang telah ia tonton
void showFilmFromPenonton(Penonton *penonton, Film *headFilm)
{
    if (penonton == NULL)
    {
        cout << "Penonton tidak ditemukan!" << endl;
        return;
    }

    cout << "DAFTAR FILM YANG DITONTON OLEH: " << penonton->nama << endl;
    cout << "ID Penonton: " << penonton->id_penonton << endl;
    cout << "No. HP: " << penonton->no_handphone << endl;
    cout << "===============================================" << endl;

    Film *tempFilm = headFilm;
    bool adaFilm = false;
    int counter = 1;

    while (tempFilm != NULL)
    {
        Pemesanan *pemesanan = tempFilm->next_pemesanan;
        bool sudahNonton = false;

        // Cek apakah penonton ini memesan film ini
        while (pemesanan != NULL)
        {
            if (pemesanan->penonton == penonton)
            {
                sudahNonton = true;
                break;
            }
            pemesanan = pemesanan->next_pemesanan;
        }

        // Jika penonton menonton film ini, tampilkan info film
        if (sudahNonton)
        {
            cout << counter++ << ". ID Film       : " << tempFilm->id_film << endl;
            cout << "   Judul Film    : " << tempFilm->judul_film << endl;
            cout << "   Tanggal Tayang: " << tempFilm->tanggal_tayang << endl;
            cout << "   Jam Tayang    : " << tempFilm->jam_tayang << endl;
            cout << "   Studio        : " << tempFilm->studio << endl
                 << endl;
            adaFilm = true;
        }

        tempFilm = tempFilm->next_film;
    }

    if (!adaFilm)
    {
        cout << "Penonton ini belum menonton film apapun." << endl
             << endl;
    }
    cout << "===============================================" << endl
         << endl;
}

// ===== PARENT SECTION END =====

// ===== CHILD SECTION START =====

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

            cout << "Penonton \"" << target->nama << "\" berhasil dihapus\n";
            delete current;
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

// ===== CHILD SECTION END =====

int main()
{

    // Doubly Linked List Film (Parent)
    Film *firstFilm = NULL;
    Film *lastFilm = NULL;

    // Singly Linked List Penonton (Child)
    Penonton *headPenonton = NULL;

    // Insert beberapa film untuk demo
    cout << "MEMBUAT DATA FILM:" << endl;
    insertFilm("Harry Potter", "02-12-2025", "20:30", "STD-01", firstFilm, lastFilm);
    insertFilm("Harry Potter II", "03-12-2025", "10:30", "STD-01", firstFilm, lastFilm);
    insertFilm("Now You See Me 3", "04-12-2025", "15:00", "STD-02", firstFilm, lastFilm);
    insertFilm("Avengers: Endgame", "05-12-2025", "19:00", "STD-03", firstFilm, lastFilm);
    cout << "Data film berhasil ditambahkan!" << endl
         << endl;

    // Insert beberapa penonton
    cout << "MEMBUAT DATA PENONTON:" << endl;
    insertPenonton("Nabil Lanten", "089657393880", headPenonton);
    insertPenonton("Brigitta Dwi Lestari", "08132466282", headPenonton);
    insertPenonton("Khalisa Assyifa", "085678926520", headPenonton);
    insertPenonton("Jeki", "081388879123", headPenonton);
    cout << "Data penonton berhasil ditambahkan!" << endl
         << endl;

    // SHOW ALL FILM
    cout << "SHOW ALL FILM :" << endl;
    showAllFilm(firstFilm);

    // FIND FILM (Fungsi yang sudah ada)
    cout << "FIND FILM 'Harry Potter':" << endl;
    Film *f1 = findFilmByJudul("Harry Potter", firstFilm);
    if (f1 != NULL)
    {
        cout << "Film ditemukan! ID: " << f1->id_film << ", Studio: " << f1->studio << endl
             << endl;
    }

    // DELETE FILM
    cout << "DELETE FILM 'Now You See Me 3':" << endl;
    cout << "Sebelum delete:" << endl;
    showAllFilm(firstFilm);

    deleteFilm(firstFilm, lastFilm, "Now You See Me 3", headPenonton);

    cout << "Setelah delete:" << endl;
    showAllFilm(firstFilm);

    // Tambah relasi pemesanan untuk demo
    cout << "MEMBUAT RELASI PEMESANAN:" << endl;
    // Film *f1 = findFilmByJudul("Harry Potter", firstFilm);
    Film *f2 = findFilmByJudul("Harry Potter II", firstFilm);
    Film *f4 = findFilmByJudul("Avengers: Endgame", firstFilm);

    Penonton *p1 = findPenonton("Nabil Lanten", headPenonton);
    Penonton *p2 = findPenonton("Brigitta Dwi Lestari", headPenonton);
    Penonton *p3 = findPenonton("Khalisa Assyifa", headPenonton);
    Penonton *p4 = findPenonton("Jeki", headPenonton);

    // Tambah beberapa relasi
    insertPemesanan(f1, p1);
    insertPemesanan(f1, p2);
    insertPemesanan(f2, p2);
    insertPemesanan(f2, p4);
    insertPemesanan(f1, p4);
    insertPemesanan(f4, p1);
    insertPemesanan(f4, p2);
    insertPemesanan(f4, p3);
    cout << "Relasi pemesanan berhasil ditambahkan!" << endl
         << endl;

    // SHOW PENONTON DARI FILM TERTENTU
    cout << "SHOW PENONTON DARI FILM 'Avengers: Endgame':" << endl;
    showPenontonFromFilm(f4);

    // SHOW FILM YANG DITONTON OLEH PENONTON TERTENTU
    cout << "SHOW FILM YANG DITONTON OLEH 'Brigitta Dwi Lestari':" << endl;
    showFilmFromPenonton(p2, firstFilm);

    // ============== kalisa ================

    // Show All Penonton (List Child)
    showAllPenonton(headPenonton);

    // Count Penonton yang Tidak Memiliki Relasi

    cout << "COUNT PENONTON YANG TIDAK MEMILIKI RELASI \n";
    int countTanpaRelasi = countPenontonTanpaRelasi(headPenonton, firstFilm);
    cout << "Jumlah penonton yang tidak memiliki relasi: " << countTanpaRelasi << "\n\n";

    // Show Penonton Beserta Semua Film yang Ditonton
    cout << "SHOW PENONTON BESERTA SEMUA FILM YANG DITONTON\n";
    showPenontonDanFilm(headPenonton, firstFilm);

    // Count Jumlah Relasi Penonton Film Tertentu
    cout << "COUNT JUMLAH RELASI UNTUK PENONTON 'Jeki' \n";
    int countJeki = countRelasiPenonton(p4, firstFilm);
    cout << "Jumlah pemesanan yang dimiliki oleh Jeki: " << countJeki << "\n\n";

    // Delete Penonton (Child)
    cout << "DELETE PENONTON 'Jeki' (C-004)\n";
    cout << "Cek relasi Jeki sebelum hapus:\n";
    findPemesanan(f2, p4);
    findPemesanan(f1, p4);

    // Hapus Penonton Jeki (C-004). Menghapus dari List Penonton DAN relasinya di semua Film.
    deletePenonton(headPenonton, firstFilm, p4);

    cout << "\nCek relasi Jeki setelah hapus :\n";
    findPemesanan(f2, p4);
    findPemesanan(f1, p4);

    cout << "\nLIST PENONTON Setelah Hapus 'Jeki':\n";
    showAllPenonton(headPenonton);

    return 0;
}
