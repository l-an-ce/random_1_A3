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
