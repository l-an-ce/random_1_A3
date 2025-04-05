#include "DB.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Remove this for merge
// #define tableSize 5

// IMPORTANT: DB.h longitude name needs to be fixed for this code to work.

DataBase *Db;

// Marek's Functions:
//      - sortByMember(memberName)
//      - reportByNeighbourhood()
//      - reportByWard()

int compareByTableId(const void *a, const void *b) 
{
    PicnicTable *tableA = (PicnicTable *)a;
    PicnicTable *tableB = (PicnicTable *)b;

    return (tableA->tableID - tableB->tableID);
}

int compareBySiteId(const void *a, const void *b) 
{
    PicnicTable *tableA = (PicnicTable *)a;
    PicnicTable *tableB = (PicnicTable *)b;

    return (tableA->siteId - tableB->siteId);
}

int compareByTableTypeId(const void *a, const void *b) 
{
    PicnicTable *tableA = (PicnicTable *)a;
    PicnicTable *tableB = (PicnicTable *)b;

    return (tableA->tableTypeId - tableB->tableTypeId);
}

int compareBySurfaceMaterialId(const void *a, const void *b) 
{
    PicnicTable *tableA = (PicnicTable *)a;
    PicnicTable *tableB = (PicnicTable *)b;

    return (tableA->surfaceMaterialId - tableB->surfaceMaterialId);
}

int compareByStructuralMaterialId(const void *a, const void *b) 
{
    PicnicTable *tableA = (PicnicTable *)a;
    PicnicTable *tableB = (PicnicTable *)b;

    return (tableA->structuralMaterialId - tableB->structuralMaterialId);
}

int compareByStreetAvenue(const void *a, const void *b) 
{
    PicnicTable *tableA = (PicnicTable *)a;
    PicnicTable *tableB = (PicnicTable *)b;

    return strcmp(tableA->streetAvenue, tableB->streetAvenue);
}

int compareByNeighbourhoodId(const void *a, const void *b) 
{
    PicnicTable *tableA = (PicnicTable *)a;
    PicnicTable *tableB = (PicnicTable *)b;

    return (tableA->neighbourhoodId - tableB->neighbourhoodId);
}

int compareByNeighbourhoodName(const void *a, const void *b) 
{
    PicnicTable *tableA = (PicnicTable *)a;
    PicnicTable *tableB = (PicnicTable *)b;

    return strcmp(tableA->neighbourhoodName, tableB->neighbourhoodName);
}

int compareByWard(const void *a, const void *b) 
{
    PicnicTable *tableA = (PicnicTable *)a;
    PicnicTable *tableB = (PicnicTable *)b;

    return (tableA->ward - tableB->ward);
}

int compareByLatitude(const void *a, const void *b) 
{
    PicnicTable *tableA = (PicnicTable *)a;
    PicnicTable *tableB = (PicnicTable *)b;

    return strcmp(tableA->latitude, tableB->latitude);
}

int compareByLongitude(const void *a, const void *b) 
{
    PicnicTable *tableA = (PicnicTable *)a;
    PicnicTable *tableB = (PicnicTable *)b;

    return strcmp(tableA->longitude, tableB->longitude);
}

void sortByMember(char *memberName) 
// I think Table size will need to be global value that is continously updated.
{
    // Set tableSize to however it's setup in new struct
    // int tableSize = 

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

void reportByNeighbourhood() 
{
    // Set tableSize to however it's setup in new struct
    // int tableSize = 

    sortByMember("neighbourhoodName");

    printf("Report by Neighbourhood: \n");

    char selectedNeighbourhood[128] = "";

    for (int i = 0; i < tableSize; i++) 
    {
        PicnicTable *table = &Db->picnicTableTable[i];

        // Check if in new neighbourhood to print out the change.
        if (strcmp(table->neighbourhoodName, selectedNeighbourhood) != 0) 
        {
            strcpy(selectedNeighbourhood, table->neighbourhoodName);
            printf("\nNeighbourhood: %s\n", selectedNeighbourhood);
        }

        // Print Each Neighbourhood
        printf("Table %d, %s, %s, Ward: %d, Latitude: %s, Longitude: %s\n", 
            table->tableID, table->streetAvenue, table->neighbourhoodName, table->ward, table->latitude, table->longitude);
    }
}

void reportByWard() 
{
    // Set tableSize to however it's setup in new struct
    // int tableSize = 
    
    sortByMember("ward");

    printf("Report by Ward: \n");

    int selectedWard = -1; // We start with -1 so the table will run ward print out on first go.

    for (int i = 0; i < tableSize; i++) 
    {
        PicnicTable *table = &Db->picnicTableTable[i];

        if (table->ward != selectedWard) 
        {
            selectedWard = table->ward;
            printf("\nWard: %d\n", selectedWard);
        }

        // Print the Table info.
        printf("Table %d, %s, %s, Neighbourhood: %s, Latitude: %s, Longitude %s\n", 
            table->tableID, table->streetAvenue, table->neighbourhoodName, table->neighbourhoodName, table->latitude, table->longitude);
    }
}