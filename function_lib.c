/** EL2208 Praktikum Pemecahan Masalah dengan C 2020/2021
*   Modul               : 7
*   Soal                : 
*   Hari dan Tanggal    : 
*   Nama (NIM)          : 
*   Asisten (NIM)       : 
*   Nama File           : function_lib.c
*   Deskripsi           : Program digunakan untuk mengimplementasikan berbagai fungsi yang digunakan pada program main
*/ 

#include "function_lib.h"

// Tambahkan implementasi fungsi lainnya sesuai keperluan

void interface_input(char* file_name){
    // Tampilkan interface input untuk pengguna (input nama file)
    printf("Simulator Sihir Transfigurasi pada Tablet of Founder\n");
    printf("Masukkan nama file yang berisi data kondisi mantera pada Tablet of Founder: ");
    scanf("%s",file_name);
}

int read_data(char* file_name, int* n_undo_redo, char** undo_redo_list, int* n_history, history** history_list){    
    // Deklarasi variabel sementara untuk input data
    char each_line[max_len];
    char temp[max_len];
    char *token;
    int count = 0;
    
    // Buka file eksternal
    FILE* file_history = fopen(file_name,"r");
    // printf("Nama File: %s\n",file_name); // Untuk debugging

    // Lakukan validasi file
    if(file_history == NULL){
        printf("File tidak dapat dibuka. Program Berakhir.");
        fclose(file_history);
        return 1;
    }
    else{
        // Baca baris pertama dan simpan sebagai jumlah undo_redo
        fgets(each_line,max_len,file_history);
        strcpy(temp, each_line);
        *n_undo_redo = atoi(temp); 
        // printf("n_undo_redo = %d\n",*n_undo_redo); // Untuk debugging
        

        // Lakukan penyesuaian jumlah memory
        *undo_redo_list = realloc(*undo_redo_list,(*n_undo_redo)*sizeof(char));
        
        // Baca baris kedua yang berisi urutan undo_redo
        fgets(each_line,max_len,file_history);
        strcpy(temp,each_line);
        token = strtok(temp,",");
        while(token!=NULL){
            (*undo_redo_list)[count] = *token;
            count+=1;
            token = strtok(NULL,",");
        }

        // Reset count menjadi 0
        count = 0;
        int column = 0;

        // Inisialisasi temp untuk struct history
        history* history_temp = NULL;
        history_temp = *history_list;

        // Baca baris ketiga yang berisi jumlah perubahan yang terjadi pada Tablet of Founder
        fgets(each_line,max_len,file_history);
        strcpy(temp, each_line);
        *n_history = atoi(temp);
        // printf("n_history = %d\n",*n_history); // Untuk debugging

        // Lakukan penyesuaian jumlah memory
        *history_list = realloc(*history_list,(*n_history)*sizeof(history));

        // Baca baris keempat dan seterusnya yang berisi daftar perubahan yang terjadi pada tablet of founder
        while(fgets(each_line,max_len,file_history)){
            strcpy(temp,each_line);
            int column = 0;
            token = strtok(temp,",");
            while(token!=NULL){
                if(column==0){
                    (*history_list)[count].row = atoi(token);
                    column+=1;
                }
                else if(column==1){
                    (*history_list)[count].col = atoi(token);
                    column+=1;
                }
                else{ // Column = 2
                    (*history_list)[count].new_state = *token;
                    column = 0;
                }
                token = strtok(NULL,",");
            }     
            // printf("%d,%d,%c count=%d\n",(*history_list)[count].row,(*history_list)[count].col,(*history_list)[count].new_state,count);  // Untuk debugging
            // printf("n_history = %d\n",*n_history); // Untuk debugging
            count+=1; 
        }
        return 0;
    }
}

void display_history(int n_history, history* history_list){
    // Tampilkan array of history struct, digunakan untuk debugging
    printf("Array daftar perubahan yang terjadi pada tablet\n");
    for(int i=0;i<n_history;i++){
        printf("%d,%d,%c i=%d\n",history_list[i].row,history_list[i].col,history_list[i].new_state,i);
    }
}

void display_undo_redo(int n_undo_redo, char* undo_redo_list){
    // Tampilkan array daftar urutan undo redo, digunakan untuk debugging
    printf("Array daftar aksi undo redo\n");
    for(int i=0;i<n_undo_redo;i++){
        printf("undo_redo[%d] = %c\n",i,undo_redo_list[i]);
    }
}

void print_tof(char tof[n_tof][n_tof]){
    for(int i=0; i<n_tof; i++){
        for(int j=0; j<n_tof; j++){
            printf("%c ",tof[i][j]);
        }
        printf("\n");
    }
}

void initialize_transfiguration_magic(transfiguration_magic** tm_pointer){
    // Alokasikan memory untuk stack transfiguration magic
    (*tm_pointer)->present = (stack*) malloc (sizeof(stack));
    (*tm_pointer)->temp = (stack*) malloc (sizeof(stack));
    (*tm_pointer)->present->head = NULL;
    (*tm_pointer)->temp->head = NULL;
}

void change_tof(char tof[n_tof][n_tof],transfiguration_magic* state, history* new_change){
    // Ganti posisi next dan head dari stack
    new_change->next = state->present->head;
    state->present->head = new_change;
    // Simpan nilai sebelum terjadinya perubahan
    new_change->prev_state = tof[new_change->row][new_change->col];
    // Lakukan perubahan pada Tablet of Founder di elemen bersangkutan
    tof[new_change->row][new_change->col] = new_change->new_state;
}

void overall_change_tof(char tof[n_tof][n_tof],transfiguration_magic* state, int n_history_list, history* history_list){
    // Lakukan perubahan pada ToF berdasarkan daftar perubahan yang terjadi
    for(int i=0; i<n_history_list;i++){
        change_tof(tof,state,&history_list[i]);
    }
}

void undounus_incantatem(char tof[n_tof][n_tof],transfiguration_magic* state){
    // Inisalisasi node sementara
    history* history_temp = state->present->head;
    if(history_temp!=NULL){
        char state_temp = history_temp->prev_state;
        // Pindahkan head dari stack present ke stack temp
        state->present->head = history_temp->next;
        history_temp->prev_state = history_temp->new_state;
        history_temp->new_state = state_temp;
        tof[history_temp->row][history_temp->col] = history_temp->new_state;
        history_temp->next = state->temp->head;
        state->temp->head = history_temp;
    }
}

void redolus_revelio(char tof[n_tof][n_tof],transfiguration_magic* state){
    // Inisalisasi node sementara
    history* history_temp = state->temp->head;
    if(history_temp!=NULL){
        char state_temp = history_temp->prev_state;
        // Pindahkan head dari stack temp ke stack present
        state->temp->head = history_temp->next;
        history_temp->prev_state = history_temp->new_state;
        history_temp->new_state = state_temp;
        tof[history_temp->row][history_temp->col] = history_temp->new_state;
        history_temp->next = state->present->head;
        state->present->head = history_temp;
    }
}

void cast_spell(char tof[n_tof][n_tof],transfiguration_magic* state,int n_undo_redo, char* undo_redo_list){
    for(int i=0; i<n_undo_redo; i++){
        if(undo_redo_list[i]=='U'){
            undounus_incantatem(tof,state);
            // printf("Undo %d\n",i); // Debugging
        }
        else if(undo_redo_list[i]=='R'){
            redolus_revelio(tof,state);
            // printf("Redo %d\n",i); // Debugging
        }
        // print_tof(tof); // Debugging
    }
}
