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
        if (temp->next_film != NULL) // Memeriksa apakah ada node berikutnya.
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
Penonton *findPenonton(string nama, Penonton *&head)
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

int main()
{

    // Doubly Linked List Film (Parent)
    Film *firstFilm = NULL;
    Film *lastFilm = NULL;

    // Singly Linked List Penonton (Child)
    Penonton *headPenonton = NULL;

    // Insert Film ke Doubly Linked List (Parent)
    insertFilm("Harry Potter", "02-12-2025", "20:30", "STD-01", firstFilm, lastFilm);
    insertFilm("Harry Potter II", "03-12-2025", "10:30", "STD-01", firstFilm, lastFilm);

    // print semua film ke layar
    printListFilm(firstFilm);

    // Insert Penonton Ke Singly Linked List (Child)
    insertPenonton("Nabil Lanten", "089657393880", headPenonton);
    insertPenonton("Brigitta Dwi Lestari", "08132466282", headPenonton);
    insertPenonton("Khalisa Assyifa", "085678926520", headPenonton);

    // print semua penonton ke layar
    printPenonton(headPenonton);

    return 0;
}
