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
    const char *constanted = (const char *)memberName; // strcmpr takes const char
    int counted = 0;
    if (strcmp(constanted, "Table Type") == 0){  // fuck it 6 if statements cause i couldnt find a better way, and i cant change the parameters
        counted = countEntriesHelper(1, value);
        return counted;
    }
    else if (strcmp(constanted, "Surface Material") == 0){
        counted = countEntriesHelper(2, value);
        return counted;
    }
    else if (strcmp(constanted, "Structural Material") == 0){
        counted = countEntriesHelper(3, value);
        return counted;
    }
    else if (strcmp(constanted, "Neighborhood ID") == 0){
        counted = countEntriesHelper(4, value);
        return counted;
    }
    else if (strcmp(constanted, "Neighborhood Name") == 0){
        counted = countEntriesHelper(5, value);
        return counted;
    }
    else if (strcmp(constanted, "Ward") == 0){
        counted = countEntriesHelper(6, value);
        return counted;
    }
    printf("Invalid Member name \n");
    return -1;
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
void editTableEntry(int tableID,char *memberName, char *value){
    int T_code = 0;
    const char *constanted = (const char *)memberName; // since strcmp take const char
    for (int i = 0; i < Db->size_of_PtableTable;i++){
        if ((Db->picnicTableTable[i].tableID) == tableID){
            if (strcmp(constanted, "Table Type") == 0){ 
                T_code = editHelper(1, value);
                if (T_code == -1){ // these if statements will check if the value exists in the table
                    resizeTable(1, value);
                    T_code = editHelper(1, value);
                    Db->tableTypeTable->arr[T_code] = value;
                    Db->picnicTableTable[i].tableID = T_code;
                    break;
                } else{
                    Db->picnicTableTable[i].tableTypeId = T_code;
                    break;
                }
            }
            else if (strcmp(constanted, "Surface Material") == 0){ 
                T_code = editHelper(2, value);
                if (T_code == -1){ // these if statements will check if the value exists in the table
                    T_code = editHelper(2, value);
                    Db->surfaceMaterialTable->arr[T_code] = value;
                    Db->picnicTableTable[i].surfaceMaterialId = T_code;
                    break;
                    }
                } else{
                    Db->picnicTableTable[i].surfaceMaterialId = T_code;
                    break;
                }
            }
            else if (strcmp(constanted, "Structural Material") == 0){ 
                T_code = editHelper(3, value);
                if (T_code == -1){ // these if statements will check if the value exists in the table
                    T_code = editHelper(3, value);
                    Db->structuralMaterialTable->arr[T_code] = value;
                    Db->picnicTableTable[i].structuralMaterialId = T_code;
                    break;
                } else{
                    Db->picnicTableTable[i].structuralMaterialId = T_code;
                    break;
                }
            }
        }
    }

