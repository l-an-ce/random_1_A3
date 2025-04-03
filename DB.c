/* DB.c
 *
 * TODO: Provide a high-level description of what is contained
 * in this file.
 *
 * Author: <TODO: Group Member Names>
 * Lab instructor: <TODO: Your lab instructor's name here>
 * Lecture instructor: <TODO: Your lecture instructor's name here>
 */

#include "DB.h"       /* Import the public database header. */
#include "DB_impl.h"  /* Import the private database header */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
 * Take the name of a member of the picnicTable entry and a value for that member 
 * as parameters and return the number of entries in the picnicTable which have 
 * that value for the memberName.
 * 
 * This is to be implemented for the following members:
 *  1- Table Type
 *  2- Surface Material
 *  3- Structural Material
 *  4- Neighborhood ID
 *  5- Neighborhood Name
 *  6- Ward
 */
int countEntries(char *memberName, char * value){
    /*
    Can't I just turn the memberName into its ASCII value and use that for switches?
    then I wouldn't need the helper function and can just use the converted ASCII
    number as the cases in a switch case block???
    ie for loop that loops through the member name string and finding 
    each characters ascii then adding that to a variable and using that variable 
    for the argument in a switchcases block? so the 6 if statements using strcmp won't be needed?
    */
    int counted = 0;
    int len_of_pTables = sizeof(DB->picnicTableTable) / sizeof(DB->picnicTableTable[0]); // to find the size of the actual array of picnic tables
    if (strcmp(*memberName, "Table Type") == 0){  // fuck it 6 if statements cause i couldnt find a better way, and i cant change the parameters
        int counted = countEntriesHelper(1, value);
        return counted;
    }
    else if (strcmp(*memberName, "Surface Material") == 0){
        int id = countEntriesHelper(2, value);
        return counted;
    }
    else if (strcmp(*memberName, "Structural Material") == 0){
        int id = countEntriesHelper(3, value);
        return counted;
    }
    else if (strcmp(*memberName, "Neighborhood ID") == 0){
        int id = countEntriesHelper(4, value);
        return counted;
    }
    else if (strcmp(*memberName, "Neighborhood Name") == 0){
        int id = countEntriesHelper(5, value);
        return counted;
    }
    else if (strcmp(*memberName, "Ward") == 0){
        int id = countEntriesHelper(6, value);
        return counted;
    }
}

// need to move helper functions to the private header
int countEntriesHelper(int member, char *thing){ // just wanted to make a function so the main count entries doesn't look like a lot
    int code = 0, count = 0;
    int len_of_pTables = sizeof(DB->picnicTableTable) / sizeof(DB->picnicTableTable[0]);
    switch (member){ // most the cases coded the same just reaching for different tables cant figure out for the life of me how to make this easier
        case 1:
            int len_of_Table = sizeof(DB->tableTypeTable) / sizeof(DB->tableTypeTable[0]);
            /*
            cant just put this at the top the save space cause each table
            could potentially be a differernt size since editTable entry will
            add a new entry if the value isnt part of the table
            */
            for (int v = 0; v < len_of_Table;v++){ 
                if (strcmp(DB->tableTypeTable[v], *thing) == 0){
                    code = v;
                }
            }
            for (int i = 0;i < len_of_pTables; i++){
                if ((DB->picnicTableTable[i].tableTypeId) == code){
                    count += 1;
                }
            }
            return count;
        case 2:
            int len_of_Table = sizeof(DB->surfaceMaterialTable) / sizeof(DB->surfaceMaterialTable[0]);
            for (int v = 0; v < len_of_Table;v++){
                if (strcmp(DB->surfaceMaterialTable[v], *thing) == 0){
                    code = v;
                }
            }
            for (int i = 0;i < len_of_pTables; i++){
                if ((DB->picnicTableTable[i].surfaceMaterialId) == code){
                    count += 1;
                }
            }
            return count;
        case 3:
            int len_of_Table = sizeof(DB->structuralMaterialId) / sizeof(DB->structuralMaterialId[0]);
            for (int v = 0; v < len_of_Table;v++){
                if (strcmp(DB->structuralMaterialId[v], *thing) == 0){
                    code = v;
                }
            }
            for (int i = 0;i < len_of_pTables; i++){
                if ((DB->picnicTableTable[i].structuralMaterialId) == code){
                    count += 1;
                }
            }
            return count;
        case 4:
            int len_of_Table = sizeof(DB->surfaceMaterialTable) / sizeof(DB->surfaceMaterialTable[0]);
            for (int v = 0; v < len_of_Table;v++){
                if (strcmp(DB->structuralMaterialTable[v], *thing) == 0){
                    id = v;
                }
            }
            for (int i = 0;i < len_of_pTables; i++){
                if ((DB->picnicTableTable[i].structuralMaterialId) == id){
                    count += 1;
                }
            }
            return count;
        case 4:
            val = atoi(thing);  //https://www.tutorialspoint.com/c_standard_library/c_function_atoi.htm
            for (int i = 0;i < len_of_pTables; i++){
                if ((DB->picnicTableTable[i].neighbourhoodId) == val){
                    count += 1;
                }
            }
            return count;
        case 5:
            val = atoi(thing);
            for (int i = 0;i < len_of_pTables; i++){
                if (strcmp((DB->picnicTableTable[i].neighbourhoodName), *thing)){
                    count += 1;
                }
            }
            return count;
        case 6:
            val = atoi(thing);
            for (int i = 0;i < len_of_pTables; i++){
                if (strcmp((DB->picnicTableTable[i].ward), val)){
                    count += 1;
                }
            }
            return count;
    }
}

/*
 * Take a tableID, the name of a member of the picnicTable entry and a value for that 
 * member as parameters, and find the entry which has that tableID and 
 * change its memberName value to newValue. 
 * Members that can be modified:
 *  1- Table Type
 *  2- Surface Material
 *  3- Structural Material 
 * If the new value is not found in the existing tables, this value must be added to the 
 * corresponding table.
 */
void editTableEntry(int tableID, char *memberName, char *value){
    int T_code = 0;
    int len_of_pTables = sizeof(DB->picnicTableTable) / sizeof(DB->picnicTableTable[0]);
    for (int i = 0; i < len_of_pTables;i++){
        if ((DB->picnicTableTable[i].tableID) == tableID){
            if (strcmp(*memberName, "Table Type") == 0){ 
                T_code = editHelper(1, value);
                if (T_code == -1){ // these if statements will check if the value exists in the table
                    resizeTable(1, value);
                    T_code = editHelper(1, value);
                    DB->picnicTableTable[i].tableTypeId = DB->tableTypeTable[T_code];
                    break;
                } else{
                    DB->picnicTableTable[i].tableTypeId = DB->tableTypeTable[T_code];
                    break;
                }
            }
            else if (strcmp(*memberName, "Surface Material") == 0){ 
                T_code = editHelper(2, value);
                if (T_code == -1){ // these if statements will check if the value exists in the table
                    T_code = editHelper(2, value);
                    DB->picnicTableTable[i].surfaceMaterialId = DB->surfaceMaterialTable[T_code];
                    break;
                    }
                } else{
                    DB->picnicTableTable[i].surfaceMaterialId = DB->surfaceMaterialTable[T_code];
                    break;
                }
            }
            else if (strcmp(*memberName, "Structural Material") == 0){ 
                T_code = editHelper(3, value);
                if (T_code == -1){ // these if statements will check if the value exists in the table
                    T_code = editHelper(2, value);
                    DB->picnicTableTable[i].structuralMaterialId = DB->structuralMaterialTable[T_code];
                    break;
                } else{
                    DB->picnicTableTable[i].structuralMaterialId = DB->structuralMaterialTable[T_code];
                    break;
                }
            }
        }
    }
}

int editHelper(int member, char *thing){ // handles finding where the value is on the tables
    int code = -1;
    switch (member){
        case 1:
            int len_of_Table = sizeof(DB->tableTypeTable) / sizeof(DB->tableTypeTable[0]);
            for (int v = 0; v < len_of_Table;v++){ 
                if (strcmp(DB->tableTypeTable[v], *thing) == 0){
                    code = v;
                }
            }
            return code;
        case 2:
            int len_of_Table = sizeof(DB->surfaceMaterialTable) / sizeof(DB->surfaceMaterialTable[0]);
            for (int v = 0; v < len_of_Table;v++){
                if (strcmp(DB->surfaceMaterialTable[v], *thing) == 0){
                    code = v;
                }
            }
            return code;
        case 3:
            int len_of_Table = sizeof(DB->surfaceMaterialTable) / sizeof(DB->surfaceMaterialTable[0]);
            for (int v = 0; v < len_of_Table;v++){
                if (strcmp(DB->surfaceMaterialTable[v], *thing) == 0){
                    code = v;
                }
            }
            return code;
    }
}
// move this to private header
void resizeTable(int table, char *add){
    switch (table){
        case 1:
            int len_of_Table = sizeof(DB->tableTypeTable) / sizeof(DB->tableTypeTable[0]);
            char *new_arr[(len_of_Table + 1)];
            int i = 0;
            for (i = 0;i < len_of_Table; i++){
                new_arr[i] = DB->tableTypeTable[i]
            }
            new_arr[i] = add;
            DB->tableTypeTable = new_arr;
        case 2:
            int len_of_Table = sizeof(DB->surfaceMaterialTable) / sizeof(DB->surfaceMaterialTable[0]);
            char *new_arr[(len_of_Table + 1)];
            int i = 0;
            for (i = 0;i < len_of_Table; i++){
                new_arr[i] = DB->surfaceMaterialTable[i]
            }
            new_arr[i] = add;
            DB->surfaceMaterialTable = new_arr;
        case 3:
            int len_of_Table = sizeof(DB->structuralMaterialTable) / sizeof(DB->structuralMaterialTable[0]);
            char *new_arr[(len_of_Table + 1)];
            int i = 0;
            for (i = 0;i < len_of_Table; i++){
                new_arr[i] = DB->structuralMaterialTable[i]
            }
            new_arr[i] = add;
            DB->structuralMaterialTable = new_arr;
    }
}
