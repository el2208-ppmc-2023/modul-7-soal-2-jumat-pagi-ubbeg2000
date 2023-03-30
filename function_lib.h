/** EL2208 Praktikum Pemecahan Masalah dengan C 2020/2021
*   Modul               : 7
*   Soal                : 
*   Hari dan Tanggal    : 
*   Nama (NIM)          : 
*   Asisten (NIM)       : 
*   Nama File           : function_lib.h
*   Deskripsi           : Program merupakan header dari function_lib.c
*/ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max_len 255
#define n_tof 7

// Struct yang berisi perubahan yang terjadi pada Tablet of Founder sekaligus untuk node stack
typedef struct history{
    int row;
    int col;
    char new_state; // Menyatakan char baru yang diletakkan pada ToF
    char prev_state; // Char sebelumnya pada ToF (sebelum ditumpuk dengan char baru)
    struct history* next;
} history;

// Tambakan deklarasi stack sesuai keperluan

// Deklarasi stack
typedef struct stack{
    history* head;
} stack;

/** Deklarasi stack transfiguration magic
 * stack digunakan untuk mengubah kondisi ToF dengan Undounus Incantatem atau Redolus Revelio
*/
typedef struct transfiguration_magic{
    stack* present;
    stack* temp;
} transfiguration_magic;

/** @brief Fungsi digunakan untuk menampilkan interface awal dan input nama file 
 * @param file_name Variabel yang digunakan untuk menyimpan string nama file
*/
void interface_input(char* file_name);

/** @brief Fungsi digunakan untuk membaca data dari file eksternal dan menyimmpannya pada array daftar undo redo serta struct history
 * @param file_name string nama file yang dibaca
 * @param n_undo_redo pointer menuju int yang menyimpan jumlah undo redo
 * @param undo_redo_list pointer menuju alamat dari array daftar undo redo
 * @param n_history pointer menuju int yang menyimpan jumlah perubahan yang terjadi pada ToF
 * @param history_list pointer menuju array of struct history yang berisi riwayat perubahan ToF
 * @return integer yang menentukan keberlanjutan program main
*/
int read_data(char* file_name, int* n_undo_redo, char** undo_redo_list, int* n_history, history** history_list);

/** @brief Tampilkan array of struct history yang berisi perubahan yang terjadi pada tablet
 * @param n_history jumlah elemen array of struct history
 * @param history_list alamat dari array of struct history
*/
void display_history(int n_history,history* history_list);

/** @brief Tampilkan array daftar urutan undo redo, digunakan untuk debugging
 * @param n_undo_redo jumlah undo redo yang dilakukan
 * @param undo_redo_list alamat dari array of char daftar undo redo
*/
void display_undo_redo(int n_undo_redo, char* undo_redo_list);

/** @brief fungsi digunakan untuk menampilkan Tablet of Founder
 * @param tof matriks of character untuk Tablet of Founder
*/
void print_tof(char tof[n_tof][n_tof]);

/** @brief Fungsi digunakan untuk inisialisasi struct transfiguration magic
 * @param tm_pointer pointer menuju alamat dari struct transfiguration magic
*/
void initialize_transfiguration_magic(transfiguration_magic** tm_pointer);

/** @brief Fungsi digunakan untuk melakukan perubahan pada Tablet of Founder
 * Perubahan dilakukan dengan menambahkan node baru (history) pada stack present di struct transfiguration magic 
 * @param tof matriks of character untuk Tablet of Founder
 * @param state alamat menuju struct transfiguration_magic
 * @param new_change alamat menuju node history yang memodelkan perubahan yang dilakukan pada Tablet of Wonder
*/
void change_tof(char tof[n_tof][n_tof],transfiguration_magic* state, history* new_change);

/** @brief Fungsi digunakan untuk melakukan perubahan pada tablet of founder berdasarkan riwayat perubahan
 * @param tof matriks of character untuk Tablet of Founder
 * @param state alamat menuju struct transfiguration_magic
 * @param n_history_list jumlah perubahan yang terjadi pada ToF
 * @param history_list daftar riwayat perubahan yang terjadi pada ToF
*/
void overall_change_tof(char tof[n_tof][n_tof],transfiguration_magic* state, int n_history_list, history* history_list);

/** @brief Fungsi digunakan untuk menggunakan mantera undounus incantatem pada Tablet of Fouder
 * @param tof matriks of character untuk Tablet of Founder
 * @param state alamat menuju struct transfiguration_magic
*/
void undounus_incantatem(char tof[n_tof][n_tof],transfiguration_magic* state);

/** @brief Fungsi digunakan untuk menggunakan mantera Redolus Revelio pada Tablet of Fouder
 * @param tof matriks of character untuk Tablet of Founder
 * @param state alamat menuju struct transfiguration_magic
*/
void redolus_revelio(char tof[n_tof][n_tof],transfiguration_magic* state);

/** @brief Fungsi digunakan untuk menggunakan mantera Undoulus Incantatem atau Redolus Revelio pada Tablet of Fouder sesuai urutan
 * @param tof matriks of character untuk Tablet of Founder
 * @param state alamat menuju struct transfiguration_magic
 * @param n_undo_redo jumlah undo redo yang dilakukan pada ToF
 * @param undo_redo_list alamat menuju array of char dari daftar undo redo
*/
void cast_spell(char tof[n_tof][n_tof],transfiguration_magic* state,int n_undo_redo, char* undo_redo_list);
