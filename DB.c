/* DB.c
 *
 * This program lays out the database functions required
 * for data regarding Picnic Tables. Functions are in place to
 * accomodate setup, importing, exporting, counting, sorting and
 * reporting on Pinic Table data.
 *
 * Author: Lexis Tran, Aryan Mahendru, Marek Maisonneuve, Lance Malafu
 * Lab instructor: Salwa Abougamila
 * Lecture instructor: Dhara Wagh, Abdullah Mohiuddin
 */

#include "DB.h"                         /* Import the public database header. */
#include "DB_impl.h"                    /* Import the private database header */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

DataBase *Db;

 #define LINE_BUFFER 1024               // Max CSV line size.
 #define INITIAL_TABLE_CAPACITY 100     // Initial table size.
 
 DataBase *Db = NULL;                   // Global database pointer.
 

 int addToTable(Table *table, int *size, const char *value) {
    // Function to add unique item to table.
    // Parameters: Pointer to a Table, int pointer for size
    //             and value you want to add to the table.

    // Check if item already inside table.
     for (int i = 0; i < *size; i++) {
         if (strcmp(table->arr[i], value) == 0) return i;
     }
    // Add item to the table
     table->arr = realloc(table->arr, (*size + 1) * sizeof(char *));
     table->arr[*size] = strdup(value);
     // Increment the size pointer upon return.
     return (*size)++;
 }
 
 int addNeighbourhood(Pair **arr, int *size, int id, const char *name) {
    // Function to add unique neighbourhood to table.
    // Parameters: Pointer to a pair, int pointer for size,
    //             int for id of neighbourhood and name of neighbourhood.

    // Check if item already inside table.
     for (int i = 0; i < *size; i++) {
         if ((*arr)[i].code == id) return i;
     }
    // Reallocate memory to accomodate for new item
    // and add the new item.
     *arr = realloc(*arr, (*size + 1) * sizeof(Pair));
     (*arr)[*size].code = id;
     (*arr)[*size].type = strdup(name);
     // Increment the size pointer upon return.
     return (*size)++;
 }
 
 void importDB(char *filename) {
    // Function to import database from a file.
    // Parameters: name of the file to open and read from.
    FILE *fp = fopen(filename, "r");  // open the csv file to read
    if (!fp) {
        printf("Could not open file %s\n", filename);
        return;
    }

    Db = malloc(sizeof(DataBase));  // make space for the whole database

    // set up memory for all the different tables
    Db->tableTypeTable = malloc(sizeof(Table));
    Db->surfaceMaterialTable = malloc(sizeof(Table));
    Db->structuralMaterialTable = malloc(sizeof(Table));
    Db->neighborhoodTable = malloc(sizeof(NeighbourhoodTable));

    // initialize them to empty/null
    Db->tableTypeTable->arr = NULL;
    Db->surfaceMaterialTable->arr = NULL;
    Db->structuralMaterialTable->arr = NULL;
    Db->neighborhoodTable->arr = NULL;

    // start sizes at zero
    Db->size_tableTypeTable = 0;
    Db->size_surfaceMaterialTable = 0;
    Db->size_structuralMaterialTable = 0;
    Db->size_neighTable = 0;
    Db->size_of_PtableTable = 0;

    int capacity = INITIAL_TABLE_CAPACITY;  // how many tables we can hold at first
    Db->picnicTableTable = malloc(capacity * sizeof(PicnicTable));  // space for picnic table records

    char line[LINE_BUFFER];
    fgets(line, LINE_BUFFER, fp);  // skip the first line 

    while (fgets(line, LINE_BUFFER, fp)) {
        // double the space if full
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

        // go through each comma separated value in the line
        token = strtok(line, ",");
        pt->siteId = atoi(token);  // site id

        token = strtok(NULL, ",");
        pt->tableTypeId = addToTable(Db->tableTypeTable, &Db->size_tableTypeTable, token);  // table type

        token = strtok(NULL, ",");
        pt->surfaceMaterialId = addToTable(Db->surfaceMaterialTable, &Db->size_surfaceMaterialTable, token);  // surface material

        token = strtok(NULL, ",");
        pt->structuralMaterialId = addToTable(Db->structuralMaterialTable, &Db->size_structuralMaterialTable, token);  // structural material

        token = strtok(NULL, ",");
        pt->streetAvenue = strdup(token);  // copy the string

        token = strtok(NULL, ",");
        pt->neighbourhoodId = atoi(token);  // neighborhood id

        token = strtok(NULL, ",");
        pt->neighbourhoodName = strdup(token);  // copy name
        addNeighbourhood(&Db->neighborhoodTable->arr, &Db->size_neighTable, pt->neighbourhoodId, pt->neighbourhoodName);  // keep track of neighborhoods

        token = strtok(NULL, ",");
        if (strncmp(token, "WARD ", 5) == 0)
            pt->ward = atoi(token + 5); 
        else
            pt->ward = atoi(token);  

        token = strtok(NULL, ",");
        pt->latitude = strdup(token);  // copy latitude

        token = strtok(NULL, ",\n");
        pt->longitude = strdup(token);  // copy longitude

        pt->tableID = Db->size_of_PtableTable;  // assign a table id (just use its index)
        Db->size_of_PtableTable++;
    }

    fclose(fp);
    printf("Database imported successfully from %s\n", filename);
    printf("Imported %d picnic tables.\n", Db->size_of_PtableTable);
}

void exportDB(char *filename) {
    // Function to export from database to a file
    // Parameters: name of the file to export to.
    if (!Db) {
        printf("No database to export.\n");
        return;
    }

    FILE *fp = fopen(filename, "w");  // open file to write
    if (!fp) {
        printf("Could not open file %s for writing.\n", filename);
        return;
    }

    // write the CSV header
    fprintf(fp, "Id,Table Type,Surface Material,Structural Material,Street / Avenue,Neighbourhood Id,Neighbourhood Name,Ward,Latitude,Longitude,Location\n");

    for (int i = 0; i < Db->size_of_PtableTable; i++) {
        PicnicTable pt = Db->picnicTableTable[i];

        // write each row with actual values instead of ids
        fprintf(fp, "%d,%s,%s,%s,%s,%d,%s,WARD %02d,%s,%s,\"(%s, %s)\"\n",
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
    // This function counts entires of a specific type specified by memberName.
    // Parameters: memberName and string value.

    const char *constanted = (const char *)memberName; // strcmpr takes const char
    int counted = 0;
    // if/else statement to determine the appropriate memberName
    if (strcmp(constanted, "Table Type") == 0){ 
        // Call count entries helper in DB_impl.c
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

 void editTableEntry(int siteID, char *memberName, char *value) {
    // This function handles editing of a table entry, and calls
    // upon a helper function from DB_impl.c.
    // Parameters: Id int, memberName and the string value.

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
            }

            else if (strcmp(constanted, "Surface Material") == 0) {
                T_code = editHelper(2, value);
                if (T_code == -1) {
                    resizeTable(2, strdup(value));
                    T_code = editHelper(2, value);
                }
                Db->picnicTableTable[i].surfaceMaterialId = T_code;
                edited = 1;
            }

            else if (strcmp(constanted, "Structural Material") == 0) {
                T_code = editHelper(3, value);
                if (T_code == -1) {
                    resizeTable(3, strdup(value));
                    T_code = editHelper(3, value);
                }
                Db->picnicTableTable[i].structuralMaterialId = T_code;
                edited = 1;
            }

            else if (strcmp(constanted, "Street / Avenue") == 0) {
                strncpy(Db->picnicTableTable[i].streetAvenue, value, sizeof(Db->picnicTableTable[i].streetAvenue) - 1);
                Db->picnicTableTable[i].streetAvenue[sizeof(Db->picnicTableTable[i].streetAvenue) - 1] = '\0';
                edited = 1;
            }

            else if (strcmp(constanted, "Neighbourhood ID") == 0) {
                Db->picnicTableTable[i].neighbourhoodId = atoi(value);
                edited = 1;
            }

            else if (strcmp(constanted, "Neighbourhood Name") == 0) {
                strncpy(Db->picnicTableTable[i].neighbourhoodName, value, sizeof(Db->picnicTableTable[i].neighbourhoodName) - 1);
                Db->picnicTableTable[i].neighbourhoodName[sizeof(Db->picnicTableTable[i].neighbourhoodName) - 1] = '\0';
                edited = 1;
            }

            else if (strcmp(constanted, "Ward") == 0) {
                Db->picnicTableTable[i].ward = atoi(value);
                edited = 1;
            }

            else if (strcmp(constanted, "Latitude") == 0) {
                strncpy(Db->picnicTableTable[i].latitude, value, sizeof(Db->picnicTableTable[i].latitude) - 1);
                Db->picnicTableTable[i].latitude[sizeof(Db->picnicTableTable[i].latitude) - 1] = '\0';
                edited = 1;
            }

            else if (strcmp(constanted, "Longitude") == 0) {
                strncpy(Db->picnicTableTable[i].longitude, value, sizeof(Db->picnicTableTable[i].longitude) - 1);
                Db->picnicTableTable[i].longitude[sizeof(Db->picnicTableTable[i].longitude) - 1] = '\0';
                edited = 1;
            }

            break;
        }
    }

    if (edited) {
        printf("Edited successfully.\n");
    } else {
        printf("Error: ID not found or invalid member name.\n");
    }
}

void freeDB() {
    // This function handles the free'ing of the entire database.
    // Parameters: None.

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

            // Prints the first item alongside the neighbourhood title,
            // this is done to accomodate spacing consistency and look.
            printf("\n%-35s %-4d %-25s %-12s %-15s %-30s %-6d %-20s %-20s %-20s (%s, - %s)\n", 
            selectedNeighbourhood,
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
        printf("%-35c %-4d %-25s %-12s %-15s %-30s %-6d %-20s %-20s %-20s (%s, - %s)\n", 
            ' ',
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
        printf("\t   %-4d %-25s %-12s %-15s %-40s %-6d %-35s %-20s %-20s (%s, - %s)\n", 
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
