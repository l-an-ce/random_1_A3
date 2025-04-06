/* DB_impl.c
 *
 * This file contains private functions and helper functions that are
 * are to manage the database within DB.c.
 *
 * Author: Lexis Tran, Aryan Mahendru, Marek Maisonneuve, Lance Malafu
 * Lab instructor: Salwa Abougamila
 * Lecture instructor: Dhara Wagh, Abdullah Mohiuddin
 */

 #include "DB.h"
 #include <stdio.h>
 #include <string.h>
 #include <stdlib.h>
 
 int editHelper(int member,const char *thing){ 
    // Function handles finding where a value is located on the tables.
     int code = -1;
     switch (member){
    // Switch cases that depend upon the member int.
         case 1: {
             for (int v = 0; v < Db->size_tableTypeTable;v++){ 
                 if (strcmp(Db->tableTypeTable->arr[v], thing) == 0){
                     code = v;
                     break;
                 }
             }
             break;
         }
         case 2: {
             for (int v = 0; v < Db->size_surfaceMaterialTable;v++){
                 if (strcmp(Db->surfaceMaterialTable->arr[v], thing) == 0){
                     code = v;
                     break;
                 }
             }
             break;
         }
         case 3: {
             for (int v = 0; v < Db->size_structuralMaterialTable;v++){
                 if (strcmp(Db->structuralMaterialTable->arr[v], thing) == 0){
                     code = v;
                     break;
                 }
             }
             break;
         }
     }
     return code;
 }
 
 int countEntriesHelper(int member, const char *thing){ 
    // Function aids the countEntries function inside DB.c
    // by moving the multiple switch cases to a helper function.
     int code = 0, count = 0, val = 0;
     switch (member){ 
        // Switch cases for different tables.
         case 1: {
             for (int v = 0; v < Db->size_tableTypeTable;v++){ 
                 if (strcmp(Db->tableTypeTable->arr[v], thing) == 0){
                     code = v;
                     break;
                 }
             }
             for (int i = 0;i < Db->size_of_PtableTable; i++){
                 if ((Db->picnicTableTable[i].tableTypeId) == code){
                     count += 1;
                 }
             }
             break;
         }
         case 2: {
             for (int v = 0; v < Db->size_surfaceMaterialTable;v++){
                 if (strcmp(Db->surfaceMaterialTable->arr[v], thing) == 0){
                     code = v;
                     break;
                 }
             }
             for (int i = 0;i < Db->size_of_PtableTable; i++){
                 if ((Db->picnicTableTable[i].surfaceMaterialId) == code){
                     count += 1;
                 }
             }
             break;
         }
         case 3: {
             for (int v = 0; v < Db->size_structuralMaterialTable;v++){
                 if (strcmp(Db->structuralMaterialTable->arr[v], thing) == 0){
                     code = v;
                     break;
                 }
             }
             for (int i = 0;i < Db->size_of_PtableTable; i++){
                 if ((Db->picnicTableTable[i].structuralMaterialId) == code){
                     count += 1;
                 }
             }
             break;
         }
         case 4: {
             val = atoi(thing);
             for (int i = 0;i < Db->size_of_PtableTable; i++){
                 if ((Db->picnicTableTable[i].neighbourhoodId) == val){
                     count += 1;
                 }
             }
             break;
         }
         case 5: {
             for (int i = 0;i < Db->size_of_PtableTable; i++){
                 if (strcmp(Db->picnicTableTable[i].neighbourhoodName, thing) == 0){
                     count += 1;
                 }
             }
             break;
         }
         case 6: {
             val = atoi(thing);
             for (int i = 0;i < Db->size_of_PtableTable; i++){
                 if ((Db->picnicTableTable[i].ward) == val){
                     count += 1;
                 }
             }
             break;
         }
     }
     return count;
 }
 
 void resizeTable(int table, char *add){
    // Function responsible for the resizing of a database table.
     switch (table){
         case 1: {
             char **new_arr = (char **)realloc(Db->tableTypeTable->arr, (Db->size_tableTypeTable + 1) * sizeof(char *));
             new_arr[Db->size_tableTypeTable] = add;
             Db->tableTypeTable->arr = new_arr;
             Db->size_tableTypeTable += 1;
             break;
         }
         case 2: {
             char **new_arr = (char **)realloc(Db->surfaceMaterialTable->arr, (Db->size_surfaceMaterialTable + 1) * sizeof(char *));
             new_arr[Db->size_surfaceMaterialTable] = add;
             Db->surfaceMaterialTable->arr = new_arr;
             Db->size_surfaceMaterialTable += 1;
             break;
         }
         case 3:{
             char **new_arr = (char **)realloc(Db->structuralMaterialTable->arr, (Db->size_structuralMaterialTable + 1) * sizeof(char *));
             new_arr[Db->size_structuralMaterialTable] = add;
             Db->structuralMaterialTable->arr = new_arr;
             Db->size_structuralMaterialTable += 1;
             break;
         }
     }
 }
 