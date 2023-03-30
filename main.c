/** EL2208 Praktikum Pemecahan Masalah dengan C 2022/2023
 *   Modul               : 
 *   Hari dan Tanggal    :
 *   Nama (NIM)          :
 *   Nama File           : main.c
 *   Deskripsi           :
 */

// Jalankan kode dengan perintah "gcc -o main main.c function_lib.c"
// Sangat disarankan untuk menggunakan VSCode agar dapat melihat deskripsi masing-masing fungsi saat fungsi ditunjuk dengan kursor

#include <stdio.h>
#include <stdlib.h>
#include "function_lib.h"

int main(){
    // Deklarasi variabel awal
    char filename[max_len];
    int n_undo_redo;
    int n_history;
    int stop;
    char* undo_redo_list = (char*) malloc(sizeof(char));
    history* history_list = (history*) malloc(sizeof(history));
    // Deklarasi Matriks Tablet of Founder
    char tof[n_tof][n_tof] = {
        {'o','*','*','-','*','*','o'},
        {'*','x','*','-','*','x','*'},
        {'*','*','x','-','x','*','*'},
        {'-','-','-','x','-','-','-'},
        {'*','*','x','-','x','*','*'},
        {'*','x','*','-','*','x','*'},
        {'o','*','*','-','*','*','o'}
    };

    // Tambahkan variabel lain yang diperlukan

    interface_input(filename);
    stop = read_data(filename,&n_undo_redo,&undo_redo_list,&n_history,&history_list);
    if(stop){
        // Hentikan program jika file tidak valid
        free(undo_redo_list);
        free(history_list);
        return 0;
    }
    else{
        // Lanjutkan program jika file valid
        // display_undo_redo(n_undo_redo,undo_redo_list); // Tampilkan array of char dari daftar undo redo yang dilakukan, silahkan comment jika sudah tidak diperlukan
        // display_history(n_history,history_list); // Tampilkan array of struct history, silahkan comment jika sudah tidak diperlukan

        // Inisialisasi Tablet of Founder
        // printf("Kondisi Awal Tablet of Founder\n"); // Untuk debugging, comment jika sudah tidak diperlukan
        // print_tof(tof); // Untuk debugging, comment jika sudah tidak diperlukan

        // Tambahkan pemanggilan fungsi atau kode yang diperlukan
        // Deklarasi stack transfiguration magic
        transfiguration_magic* tm_stack = (transfiguration_magic*)malloc(sizeof(transfiguration_magic));
        initialize_transfiguration_magic(&tm_stack);

        // Lakukan perubahan pada ToF sesuai data perubahan yang terjadi
        overall_change_tof(tof,tm_stack,n_history,history_list);
        printf("Kondisi Tablet of Founder sebelum Undounus Incantatem & Redolus Revelio\n");
        print_tof(tof);

        // Lakukan Undounus Incantatem atau Redolus Revelio sesuai data
        cast_spell(tof,tm_stack,n_undo_redo,undo_redo_list);
        printf("Kondisi Akhir Tablet of Founder Setelah Transfigurasi\n");
        print_tof(tof);

        free(tm_stack);
    }
    
    free(undo_redo_list);
    free(history_list);
    return 0;
}
