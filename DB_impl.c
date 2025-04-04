/* DB_impl.c
 *
 * TODO: Provide a high-level description of what is contained
 * in this file.
 *
 * Author: <TODO: Group Member Names>
 * Lab instructor: <TODO: Your lab instructor's name here>
 * Lecture instructor: <TODO: Your lecture instructor's name here>
 */

#include "DB.h"      /* Import the public database header. */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int editHelper(int member,const char *thing){ // handles finding where the value is on the tables
    int code = -1;
    switch (member){
        case 1:
            for (int v = 0; v < Db->size_tableTypeTable;v++){ 
                if (strcmp(Db->tableTypeTable->arr[v], thing) == 0){
                    code = v;
                }
            }
        case 2:
            for (int v = 0; v < Db->size_surfaceMaterialTable;v++){
                if (strcmp(Db->surfaceMaterialTable->arr[v], thing) == 0){
                    code = v;
                }
            }
        case 3:
            for (int v = 0; v < Db->size_structuralMaterialTable;v++){
                if (strcmp(Db->structuralMaterialTable->arr[v], thing) == 0){
                    code = v;
                }
            }
    }
    return code;
}

int countEntriesHelper(int member, const char *thing){ // just wanted to make a function so the main count entries doesn't look like a lot
    int code = 0, count = 0, val = 0;
    switch (member){ // most the cases coded the same just reaching for different tables cant figure out for the life of me how to make this easier
        case 1:
            /*
            cant just put this at the top the save space cause each table
            could potentially be a differernt size since editTable entry will
            add a new entry if the value isnt part of the table
            */
            for (int v = 0; v < Db->size_tableTypeTable;v++){ 
                if (strcmp(Db->tableTypeTable->arr[v], thing) == 0){
                    code = v;
                }
            }
            for (int i = 0;i < Db->size_of_PtableTable; i++){
                if ((Db->picnicTableTable[i].tableTypeId) == code){
                    count += 1;
                }
            }
        case 2:
            for (int v = 0; v < Db->size_surfaceMaterialTable;v++){
                if (strcmp(Db->surfaceMaterialTable->arr[v], thing) == 0){
                    code = v;
                }
            }
            for (int i = 0;i < Db->size_of_PtableTable; i++){
                if ((Db->picnicTableTable[i].surfaceMaterialId) == code){
                    count += 1;
                }
            }
        case 3:
            for (int v = 0; v < Db->size_structuralMaterialTable;v++){
                if (strcmp(Db->structuralMaterialTable->arr[v], thing) == 0){
                    code = v;
                }
            }
            for (int i = 0;i < Db->size_of_PtableTable; i++){
                if ((Db->picnicTableTable[i].structuralMaterialId) == code){
                    count += 1;
                }
            }
        case 4:
            val = atoi(thing);  //https://www.tutorialspoint.com/c_standard_library/c_function_atoi.htm
            for (int i = 0;i < Db->size_of_PtableTable; i++){
                if ((Db->picnicTableTable[i].neighbourhoodId) == val){
                    count += 1;
                }
            }
        case 5:
            val = atoi(thing);
            for (int i = 0;i < Db->size_of_PtableTable; i++){
                if (strcmp((Db->picnicTableTable[i].neighbourhoodName), thing)){
                    count += 1;
                }
            }
        case 6:
            val = atoi(thing);
            for (int i = 0;i < Db->size_of_PtableTable; i++){
                if ((Db->picnicTableTable[i].ward) == val){
                    count += 1;
                }
            }

    }
    return count;
}


void resizeTable(int table, char *add){
    int i;
    switch (table){
        case 1: {
            char *new_arr[Db->size_tableTypeTable + 1];
            for (i = 0;i < Db->size_tableTypeTable; i++){
                new_arr[i] = Db->tableTypeTable->arr[i];
            }
            new_arr[i] = add;
            Db->tableTypeTable->arr = new_arr;
            Db->size_tableTypeTable += 1;
        }
        case 2: {
            char *new_arr[Db->size_surfaceMaterialTable + 1];
            for (i = 0;i < Db->size_surfaceMaterialTable; i++){
                new_arr[i] = Db->surfaceMaterialTable->arr[i];
            }
            new_arr[i] = add;
            Db->surfaceMaterialTable->arr = new_arr;
            Db->size_surfaceMaterialTable += 1;
        }
        case 3:{
            char *new_arr[Db->size_structuralMaterialTable + 1];
            for (i = 0;i < Db->size_structuralMaterialTable; i++){
                new_arr[i] = Db->structuralMaterialTable->arr[i];
            }
            new_arr[i] = add;
            Db->structuralMaterialTable->arr = new_arr;
            Db->size_structuralMaterialTable += 1;
        }
    }
}