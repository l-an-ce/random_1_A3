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