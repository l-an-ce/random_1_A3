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

DataBase *Db;

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


 #define LINE_BUFFER 1024         // max csv line size
 #define INITIAL_TABLE_CAPACITY 100  // starting table size
 
 DataBase *Db = NULL;  // global database pointer
 
 // add unique item to table
 int addToTable(Table *table, int *size, const char *value) {
     for (int i = 0; i < *size; i++) {
         if (strcmp(table->arr[i], value) == 0) return i;
     }
     table->arr = realloc(table->arr, (*size + 1) * sizeof(char *));
     table->arr[*size] = strdup(value);
     return (*size)++;
 }
 
 // add unique neighbourhood
 int addNeighbourhood(Pair **arr, int *size, int id, const char *name) {
     for (int i = 0; i < *size; i++) {
         if ((*arr)[i].code == id) return i;
     }
     *arr = realloc(*arr, (*size + 1) * sizeof(Pair));
     (*arr)[*size].code = id;
     (*arr)[*size].type = strdup(name);
     return (*size)++;
 }
 
 void importDB(char *filename) {
     FILE *fp = fopen(filename, "r");
     if (!fp) {
         printf("Could not open file %s\n", filename);
         return;
     }
 
     Db = malloc(sizeof(DataBase));
 
     // allocate tables
     Db->tableTypeTable = malloc(sizeof(Table));
     Db->surfaceMaterialTable = malloc(sizeof(Table));
     Db->structuralMaterialTable = malloc(sizeof(Table));
     Db->neighborhoodTable = malloc(sizeof(NeighbourhoodTable));
 
     Db->tableTypeTable->arr = NULL;
     Db->surfaceMaterialTable->arr = NULL;
     Db->structuralMaterialTable->arr = NULL;
     Db->neighborhoodTable->arr = NULL;
 
     Db->size_tableTypeTable = 0;
     Db->size_surfaceMaterialTable = 0;
     Db->size_structuralMaterialTable = 0;
     Db->size_neighTable = 0;
     Db->size_of_PtableTable = 0;
 
     int capacity = INITIAL_TABLE_CAPACITY;
     Db->picnicTableTable = malloc(capacity * sizeof(PicnicTable));
 
     char line[LINE_BUFFER];
     fgets(line, LINE_BUFFER, fp);  // skip header
 
     while (fgets(line, LINE_BUFFER, fp)) {
         // resize if needed
         if (Db->size_of_PtableTable >= capacity) {
             capacity *= 2;
             Db->picnicTableTable = realloc(Db->picnicTableTable, capacity * sizeof(PicnicTable));
             if (!Db->picnicTableTable) {
                 printf("Error reallocating picnicTableTable.\n");
                 exit(1);
             }
         }
 
         PicnicTable *pt = &Db->picnicTableTable[Db->size_of_PtableTable];
         char *token;
 
         token = strtok(line, ",");
         pt->siteId = atoi(token);
 
         token = strtok(NULL, ",");
         pt->tableTypeId = addToTable(Db->tableTypeTable, &Db->size_tableTypeTable, token);
 
         token = strtok(NULL, ",");
         pt->surfaceMaterialId = addToTable(Db->surfaceMaterialTable, &Db->size_surfaceMaterialTable, token);
 
         token = strtok(NULL, ",");
         pt->structuralMaterialId = addToTable(Db->structuralMaterialTable, &Db->size_structuralMaterialTable, token);
 
         token = strtok(NULL, ",");
         pt->streetAvenue = strdup(token);
 
         token = strtok(NULL, ",");
         pt->neighbourhoodId = atoi(token);
 
         token = strtok(NULL, ",");
         pt->neighbourhoodName = strdup(token);
         addNeighbourhood(&Db->neighborhoodTable->arr, &Db->size_neighTable, pt->neighbourhoodId, pt->neighbourhoodName);
 
         token = strtok(NULL, ",");
         if (strncmp(token, "WARD ", 5) == 0)
             pt->ward = atoi(token + 5);  // handle "WARD xx"
         else
             pt->ward = atoi(token);
 
         token = strtok(NULL, ",");
         pt->latitude = strdup(token);
 
         token = strtok(NULL, ",\n");
         pt->longitude = strdup(token);
 
         pt->tableID = Db->size_of_PtableTable;
         Db->size_of_PtableTable++;
     }
 
     fclose(fp);
     printf("Database imported successfully from %s\n", filename);
     printf("Imported %d picnic tables.\n", Db->size_of_PtableTable);

 }
 
 void exportDB(char *filename) {
     if (!Db) {
         printf("No database to export.\n");
         return;
     }
 
     FILE *fp = fopen(filename, "w");
     if (!fp) {
         printf("Could not open file %s for writing.\n", filename);
         return;
     }
 
     // write csv header
     fprintf(fp, "Id,Table Type,Surface Material,Structural Material,Street / Avenue,Neighbourhood Id,Neighbourhood Name,Ward,Latitude,Longitude,Location\n");
 
     for (int i = 0; i < Db->size_of_PtableTable; i++) {
         PicnicTable pt = Db->picnicTableTable[i];

     
         // write one row
         fprintf(fp, "%d,%s,%s,%s,%s,%d,%s,WARD %02d,%s,%s,\"(%s,%s)\"\n",
             pt.siteId,
             Db->tableTypeTable->arr[pt.tableTypeId],
             Db->surfaceMaterialTable->arr[pt.surfaceMaterialId],
             Db->structuralMaterialTable->arr[pt.structuralMaterialId],
             pt.streetAvenue,
             pt.neighbourhoodId,
             pt.neighbourhoodName,
             pt.ward,
             pt.latitude,
             pt.longitude,
             pt.latitude,
             pt.longitude
         );
     }
 
     fclose(fp);
     printf("Database exported successfully to %s\n", filename);
 }

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
 void editTableEntry(int siteID, char *memberName, char *value) {
    int T_code = 0;
    const char *constanted = (const char *)memberName;
    int edited = 0;

    for (int i = 0; i < Db->size_of_PtableTable; i++) {
        if (Db->picnicTableTable[i].siteId == siteID) {

            if (strcmp(constanted, "Table Type") == 0) {
                T_code = editHelper(1, value);
                if (T_code == -1) {
                    resizeTable(1, strdup(value));
                    T_code = editHelper(1, value);
                }
                Db->picnicTableTable[i].tableTypeId = T_code;
                edited = 1;
                break;
            }

            else if (strcmp(constanted, "Surface Material") == 0) {
                T_code = editHelper(2, value);
                if (T_code == -1) {
                    resizeTable(2, strdup(value));
                    T_code = editHelper(2, value);
                }
                Db->picnicTableTable[i].surfaceMaterialId = T_code;
                edited = 1;
                break;
            }

            else if (strcmp(constanted, "Structural Material") == 0) {
                T_code = editHelper(3, value);
                if (T_code == -1) {
                    resizeTable(3, strdup(value));
                    T_code = editHelper(3, value);
                }
                Db->picnicTableTable[i].structuralMaterialId = T_code;
                edited = 1;
                break;
            }

            break;
        }
    }

    if (edited) {
        printf("Edited successfully.\n");
    } else {
        printf("Error: ID not found.\n");
    }
}

void freeDB() {
    if (!Db) return;

    // Free Table Type strings
    for (int i = 0; i < Db->size_tableTypeTable; i++) {
        free(Db->tableTypeTable->arr[i]);
    }
    free(Db->tableTypeTable->arr);
    free(Db->tableTypeTable);

    // Free Surface Material strings
    for (int i = 0; i < Db->size_surfaceMaterialTable; i++) {
        free(Db->surfaceMaterialTable->arr[i]);
    }
    free(Db->surfaceMaterialTable->arr);
    free(Db->surfaceMaterialTable);

    // Free Structural Material strings
    for (int i = 0; i < Db->size_structuralMaterialTable; i++) {
        free(Db->structuralMaterialTable->arr[i]);
    }
    free(Db->structuralMaterialTable->arr);
    free(Db->structuralMaterialTable);

    // Free Neighbourhood name strings (from Pair array)
    for (int i = 0; i < Db->size_neighTable; i++) {
        free(Db->neighborhoodTable->arr[i].type);
    }
    free(Db->neighborhoodTable->arr);
    free(Db->neighborhoodTable);

    // Free fields inside PicnicTable records
    for (int i = 0; i < Db->size_of_PtableTable; i++) {
        free(Db->picnicTableTable[i].streetAvenue);
        free(Db->picnicTableTable[i].neighbourhoodName);
        free(Db->picnicTableTable[i].latitude);
        free(Db->picnicTableTable[i].longitude);
    }
    free(Db->picnicTableTable);

    // Finally, free the main Db struct
    free(Db);
    Db = NULL;
}


#include "DB.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

DataBase *Db;

int compareByTableId(const void *a, const void *b) 
{
    // To be used with qsort().
    // Compare two tables by tableId and return difference.
    // Parameters: Two void pointers to PicnicTable struct.

    PicnicTable *tableA = (PicnicTable *)a;
    PicnicTable *tableB = (PicnicTable *)b;

    return (tableA->tableID - tableB->tableID);
}

int compareBySiteId(const void *a, const void *b) 
{
    // To be used with qsort().
    // Compare two tables by siteId and return difference.
    // Parameters: Two void pointers to PicnicTable struct.

    PicnicTable *tableA = (PicnicTable *)a;
    PicnicTable *tableB = (PicnicTable *)b;

    return (tableA->siteId - tableB->siteId);
}

int compareByTableTypeId(const void *a, const void *b) 
{
    // To be used with qsort().
    // Compare two tables by tableTypeId and return difference.
    // Parameters: Two void pointers to PicnicTable struct.

    PicnicTable *tableA = (PicnicTable *)a;
    PicnicTable *tableB = (PicnicTable *)b;

    return (tableA->tableTypeId - tableB->tableTypeId);
}

int compareBySurfaceMaterialId(const void *a, const void *b) 
{
    // To be used with qsort().
    // Compare two tables by surafaceMaterialId and return difference.
    // Parameters: Two void pointers to PicnicTable struct.

    PicnicTable *tableA = (PicnicTable *)a;
    PicnicTable *tableB = (PicnicTable *)b;

    return (tableA->surfaceMaterialId - tableB->surfaceMaterialId);
}

int compareByStructuralMaterialId(const void *a, const void *b) 
{
    // To be used with qsort().
    // Compare two tables by structuralMaterialId and return difference.
    // Parameters: Two void pointers to PicnicTable struct.

    PicnicTable *tableA = (PicnicTable *)a;
    PicnicTable *tableB = (PicnicTable *)b;

    return (tableA->structuralMaterialId - tableB->structuralMaterialId);
}

int compareByStreetAvenue(const void *a, const void *b) 
{
    // To be used with qsort().
    // Compare two tables by streetAvenue and return info regarding alphebetical order.
    // Parameters: Two void pointers to PicnicTable struct.

    PicnicTable *tableA = (PicnicTable *)a;
    PicnicTable *tableB = (PicnicTable *)b;

    return strcmp(tableA->streetAvenue, tableB->streetAvenue);
}

int compareByNeighbourhoodId(const void *a, const void *b) 
{
    // To be used with qsort().
    // Compare two tables by neighbourhoodId and return difference.
    // Parameters: Two void pointers to PicnicTable struct.

    PicnicTable *tableA = (PicnicTable *)a;
    PicnicTable *tableB = (PicnicTable *)b;

    return (tableA->neighbourhoodId - tableB->neighbourhoodId);
}

int compareByNeighbourhoodName(const void *a, const void *b) 
{
    // To be used with qsort().
    // Compare two tables by neighbourhoodName and return info regarding alphebetical order.
    // Parameters: Two void pointers to PicnicTable struct.

    PicnicTable *tableA = (PicnicTable *)a;
    PicnicTable *tableB = (PicnicTable *)b;

    return strcmp(tableA->neighbourhoodName, tableB->neighbourhoodName);
}

int compareByWard(const void *a, const void *b) 
{
    // To be used with qsort().
    // Compare two tables by ward and return difference.
    // Parameters: Two void pointers to PicnicTable struct.

    PicnicTable *tableA = (PicnicTable *)a;
    PicnicTable *tableB = (PicnicTable *)b;

    return (tableA->ward - tableB->ward);
}

int compareByLatitude(const void *a, const void *b) 
{
    // To be used with qsort().
    // Compare two tables by latitude and return info regarding alphebetical/numerical order.
    // Parameters: Two void pointers to PicnicTable struct.

    PicnicTable *tableA = (PicnicTable *)a;
    PicnicTable *tableB = (PicnicTable *)b;

    return strcmp(tableA->latitude, tableB->latitude);
}

int compareByLongitude(const void *a, const void *b) 
{
    // To be used with qsort().
    // Compare two tables by longitude and return info regarding alphebetical/numerical order.
    // Parameters: Two void pointers to PicnicTable struct.

    PicnicTable *tableA = (PicnicTable *)a;
    PicnicTable *tableB = (PicnicTable *)b;

    return strcmp(tableA->longitude, tableB->longitude);
}

void sortByMember(char *memberName) 
{
    // This function takes a member name from the PicnicTable struct
    // and sorts the table accordingly using qsort which is supplied
    // with specific comparison functions for each member name.
    // Parameters: Pointer to first character of memberName string.

    // Retrieve current table size from database.
    int tableSize = Db->size_of_PtableTable;

    // Determine specific compare function to use in qsort based off memberName.
    if (strcmp(memberName, "tableId") == 0) 
    {
        qsort(Db->picnicTableTable, tableSize, sizeof(PicnicTable), compareByTableId);
    }
    else if (strcmp(memberName, "siteId") == 0) 
    {
        qsort(Db->picnicTableTable, tableSize, sizeof(PicnicTable), compareBySiteId);
    }
    else if (strcmp(memberName, "tableTypeId") == 0) 
    {
        qsort(Db->picnicTableTable, tableSize, sizeof(PicnicTable), compareByTableTypeId);
    }
    else if (strcmp(memberName, "surfaceMaterialId") == 0) 
    {
        qsort(Db->picnicTableTable, tableSize, sizeof(PicnicTable), compareBySurfaceMaterialId);
    }
    else if (strcmp(memberName, "structuralMaterialId") == 0) 
    {
        qsort(Db->picnicTableTable, tableSize, sizeof(PicnicTable), compareByStructuralMaterialId);
    }
    else if (strcmp(memberName, "streetAvenue") == 0) 
    {
        qsort(Db->picnicTableTable, tableSize, sizeof(PicnicTable), compareByStreetAvenue);
    }
    else if (strcmp(memberName, "neighbourhoodId") == 0) 
    {
        qsort(Db->picnicTableTable, tableSize, sizeof(PicnicTable), compareByNeighbourhoodId);
    }
    else if (strcmp(memberName, "neighbourhoodName") == 0) 
    {
        qsort(Db->picnicTableTable, tableSize, sizeof(PicnicTable), compareByNeighbourhoodName);
    }
    else if (strcmp(memberName, "ward") == 0) 
    {
        qsort(Db->picnicTableTable, tableSize, sizeof(PicnicTable), compareByWard);
    }
    else if (strcmp(memberName, "latitude") == 0) 
    {
        qsort(Db->picnicTableTable, tableSize, sizeof(PicnicTable), compareByLatitude);
    }
    else if (strcmp(memberName, "longitude") == 0) 
    {
        qsort(Db->picnicTableTable, tableSize, sizeof(PicnicTable), compareByLongitude);
    }
}

char *tableCodeToString(int givenId, const char *tableName) 
{
    // Helper function to retrieve the string value associated
    // with a specific Id/Index in the "Type" tables of the Database.
    // Parameters: givenId int from PicnicTable and constant pointer to tableName.

    // Double check tableName was given.
    if (tableName == NULL) 
    {
        return NULL;
    }

    // Using if/else statements determine if given tableName fits any of the database tables.
    if (strcmp(tableName, "tableTypeTable") == 0) 
    {
        // Double check givenId is valid (> 0 and within selected tableType length.)
        if (givenId >= 0 && givenId < Db->size_tableTypeTable) 
        {
            // Return the value at the specic Id/Index of the selected table.
            return Db->tableTypeTable->arr[givenId];
        }
    }
    else if (strcmp(tableName, "surfaceMaterialTable") == 0) 
    {
        // Double check givenId is valid (> 0 and within selected tableType length.)
        if (givenId >= 0 && givenId < Db->size_surfaceMaterialTable) 
        {
            // Return the value at the specic Id/Index of the selected table.
            return Db->surfaceMaterialTable->arr[givenId];
        }
    }
    else if (strcmp(tableName, "structuralMaterialTable") == 0) 
    {
        // Double check givenId is valid (> 0 and within selected tableType length.)
        if (givenId >= 0 && givenId < Db->size_structuralMaterialTable) 
        {
            // Return the value at the specic Id/Index of the selected table.
            return Db->structuralMaterialTable->arr[givenId];
        }
    }
    else 
    {
        return NULL;
    }
}

void reportByNeighbourhood() 
{
    // Produces a listing of Picnic Tables grouped by neighbourhood
    // in ascending alphebetical order, prints to terminal.
    // Parameters: None

    // Retrieve current table size from database.
    int tableSize = Db->size_of_PtableTable;

    // Use sortByMember to get table in alphebetical order.
    sortByMember("neighbourhoodName");

    printf("Report by Neighbourhood: \n");

    // Temp string to hold what neighbourhood currently looking at.
    // Begins as "empty" string so that first loop will print the first neighbourhood title.
    char selectedNeighbourhood[128] = "";

    // Loop through all items in PicnicTable.
    for (int i = 0; i < tableSize; i++) 
    {
        PicnicTable *table = &Db->picnicTableTable[i];

        // Check If Neighbourhood has changed.
        if (strcmp(table->neighbourhoodName, selectedNeighbourhood) != 0) 
        {
            // Update temp selectedNeighbourhood string.
            strcpy(selectedNeighbourhood, table->neighbourhoodName);
            // Print Neighbourhood title.
            printf("\n%s", selectedNeighbourhood);

            // Prints the first item alongside the neighbourhood title,
            // this is done to accomodate spacing consistency and look.
            printf("\t\t   %-4d %-16s %-12s %-15s %-40s %-6d %-20s %-20s %-20s (%s, - %s)\n", 
            table->siteId, 
            tableCodeToString(table->tableTypeId, "tableTypeTable"),
            tableCodeToString(table->surfaceMaterialId, "surfaceMaterialTable"),
            tableCodeToString(table->structuralMaterialId, "structuralMaterialTable"),
            table->streetAvenue,
            table->neighbourhoodId,
            table->neighbourhoodName,
            table->latitude,
            table->longitude,
            table->latitude,
            table->longitude);
            continue;
        }

        // Print each subseqent non-first item inside the neighbourhood.
        printf("\t\t\t   %-4d %-16s %-12s %-15s %-40s %-6d %-20s %-20s %-20s (%s, - %s)\n", 
            table->siteId, 
            tableCodeToString(table->tableTypeId, "tableTypeTable"),
            tableCodeToString(table->surfaceMaterialId, "surfaceMaterialTable"),
            tableCodeToString(table->structuralMaterialId, "structuralMaterialTable"),
            table->streetAvenue,
            table->neighbourhoodId,
            table->neighbourhoodName,
            table->latitude,
            table->longitude,
            table->latitude,
            table->longitude);
    }
}

void reportByWard() 
{
    // Produces a listing of Picnic Tables grouped by ward
    // in ascending numerical order, prints to terminal.
    // Parameters: None

    // Retrieve current table size from database.
    int tableSize = Db->size_of_PtableTable;
    
    // Use sortByMember to get table in numerical order.
    sortByMember("ward");

    printf("Report by Ward: \n");

    // Temp int to hold which ward currently looking at.
    // Begins at -1 so that first loop will print the first ward title.
    int selectedWard = -1;

    // Loop through all items in PicnicTable.
    for (int i = 0; i < tableSize; i++) 
    {
        PicnicTable *table = &Db->picnicTableTable[i];

        // Check If ward has changed.
        if (table->ward != selectedWard) 
        {
            // Update temp selected ward.
            selectedWard = table->ward;
            // Print ward title.
            printf("\nWARD %d", selectedWard);
            // NOTE: First print loop in this function does not need first item
            //       to be printed within this if statement, since ward title is
            //       much smaller than in the reportByNeighbourhood() function.
        }

        // Print each item within the selected ward.
        printf("\t   %-4d %-16s %-12s %-15s %-40s %-6d %-20s %-20s %-20s (%s, - %s)\n", 
            table->siteId, 
            tableCodeToString(table->tableTypeId, "tableTypeTable"),
            tableCodeToString(table->surfaceMaterialId, "surfaceMaterialTable"),
            tableCodeToString(table->structuralMaterialId, "structuralMaterialTable"),
            table->streetAvenue,
            table->neighbourhoodId,
            table->neighbourhoodName,
            table->latitude,
            table->longitude,
            table->latitude,
            table->longitude);
    }
}
