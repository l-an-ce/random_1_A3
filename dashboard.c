#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DB.h"

// Structure to represent a table entry
typedef struct {
    int id;
    char memberName[50];
    char value[50];
} Table;

// Structure to represent the entire database
typedef struct {
    Table *entries;
    int size;
} Database;

// Function prototypes
void importDatabase(int *databaseLoaded, Database *db);
void exportDatabase(Database *db);
void countEntries(Database *db);
void sortDatabase(Database *db);
void editEntry(Database *db);
void generateReport(Database *db);
void displayMenu();

int main(int argc, char *argv[]) {
    int choice;
    int databaseLoaded = 0;  // 0 = not loaded, 1 = loaded
    initDatabase();  // Initialize the database

    while (1) {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();  // Consume the newline left by scanf

        if (choice == 8) {
            printf("Exiting program...\n");
            break;
        }

        if (choice == 1) {
            // Import functionality (not yet implemented)
            databaseLoaded = 1;    // Mark the database as loaded
        } else if (!databaseLoaded) {
            printf("Error: Import the database first.\n");
        } else {
            switch (choice) {
                case 2:
                    // Export functionality (not yet implemented)
                    break;
                case 3:
                    {
                        char memberName[50], value[50];
                        printf("Enter member name: ");
                        scanf("%s", memberName);
                        printf("Enter value: ");
                        scanf("%s", value);
                        int count = countEntries(memberName, value);
                        printf("Count: %d\n", count);
                        break;
                    }
                case 4:
                    {
                        char memberName[50];
                        printf("Enter member name to sort by: ");
                        scanf("%s", memberName);
                        sortByMember(memberName);
                        break;
                    }
                case 5:
                    {
                        int tableID;
                        char memberName[50], value[50];
                        printf("Enter table ID: ");
                        scanf("%d", &tableID);
                        printf("Enter member name to edit: ");
                        scanf("%s", memberName);
                        printf("Enter new value: ");
                        scanf("%s", value);
                        editTableEntry(tableID, memberName, value);
                        break;
                    }
                case 6:
                    reportByNeighbourhood();
                    break;
                case 7:
                    reportByWard();
                    break;
                default:
                    printf("Invalid choice. Please try again.\n");
            }
        }
    }

    // Clean up database memory before exiting
    freeDB();

    return 0;
}

void displayMenu() {
    printf("\n=== Dashboard Menu ===\n");
    printf("1. Import Database\n");
    printf("2. Export Database\n");
    printf("3. Count Entries\n");
    printf("4. Sort By\n");
    printf("5. Edit Entry\n");
    printf("6. Report\n");
    printf("7. Exit\n");
}

void importDatabase(int *databaseLoaded, Database *db) {
    char filename[100];
    printf("Enter database filename to import: ");
    scanf("%99s", filename);

    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Failed to open file.\n");
        return;
    }

    // Free any previously allocated memory
    if (db->entries) {
        free(db->entries);
    }

    db->size = 0;
    db->entries = NULL;

    Table tempTable;
    while (fscanf(file, "%d,%49[^,],%49[^\n]\n", &tempTable.id, tempTable.memberName, tempTable.value) != EOF) {
        db->entries = realloc(db->entries, (db->size + 1) * sizeof(Table));
        db->entries[db->size] = tempTable;
        db->size++;
    }

    fclose(file);
    *databaseLoaded = 1;
    printf("Database '%s' imported successfully!\n", filename);
}

void exportDatabase(Database *db) {
    char filename[100];
    printf("Enter filename to export database: ");
    scanf("%99s", filename);

    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Failed to open file.\n");
        return;
    }

    for (int i = 0; i < db->size; i++) { // Write each entry to the file
        fprintf(file, "%d,%s,%s\n", db->entries[i].id, db->entries[i].memberName, db->entries[i].value);
    }

    fclose(file);
    printf("Database exported to '%s'.\n", filename);
}

void countEntries(Database *db) {
    char memberName[50], value[50];
    printf("Enter member name: ");
    scanf("%49s", memberName);
    printf("Enter value: ");
    scanf("%49s", value);

    int count = 0;
    for (int i = 0; i < db->size; i++) {  // Counting entries that match the given memberName and value
        if (strcmp(db->entries[i].memberName, memberName) == 0 && strcmp(db->entries[i].value, value) == 0) {
            count++;
        }
    }

    printf("Found %d entries with %s = %s.\n", count, memberName, value);
}

void sortDatabase(Database *db) {
    char memberName[50];
    printf("Enter member name to sort by: ");
    scanf("%49s", memberName);

    for (int i = 0; i < db->size - 1; i++) {  // Sorting based on memberName (using strcmp for sorting by name)
        for (int j = i + 1; j < db->size; j++) {
            if (strcmp(db->entries[i].memberName, db->entries[j].memberName) > 0) {
                Table temp = db->entries[i];
                db->entries[i] = db->entries[j];
                db->entries[j] = temp;
            }
        }
    }

    printf("Database sorted by '%s'.\n", memberName);
}

void editEntry(Database *db) {
    int id;
    char memberName[50], value[50];

    printf("Enter entry ID to edit: ");
    scanf("%d", &id);

    // Search for the entry by ID
    int found = 0;
    for (int i = 0; i < db->size; i++) {
        if (db->entries[i].id == id) {
            found = 1;
            printf("Enter new member name: ");
            scanf("%49s", memberName);
            printf("Enter new value: ");
            scanf("%49s", value);

            // Update the entry
            strcpy(db->entries[i].memberName, memberName);
            strcpy(db->entries[i].value, value);

            printf("Updated entry ID %d: %s = %s.\n", id, memberName, value);
            break;
        }
    }

    if (!found) {
        printf("Entry with ID %d not found.\n", id);
    }
}

void generateReport(Database *db) {
    int id;
    printf("Enter Ward or Neighbourhood ID: ");
    scanf("%d", &id);

    // Generate a simple report by listing entries with the given ID
    int found = 0;
    for (int i = 0; i < db->size; i++) {
        if (db->entries[i].id == id) {
            found = 1;
            printf("ID: %d, Member: %s, Value: %s\n", db->entries[i].id, db->entries[i].memberName, db->entries[i].value);
        }
    }

    if (!found) {
        printf("No entries found for ID: %d.\n", id);
    }
}
