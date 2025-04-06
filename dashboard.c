#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DB.h"

// Function prototypes
void importDatabase(int *databaseLoaded);
void exportDatabase();
void displayMenu();

int main(int argc, char *argv[]) {
    int choice;
    int databaseLoaded = 0;  // 0 = not loaded, 1 = loaded

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
            importDatabase(&databaseLoaded);  
        } else if (!databaseLoaded) {
            printf("Error: Import the database first.\n");
        } else {
            switch (choice) {
                case 2:
                    exportDatabase();  
                    break;
                case 3: {
                    char memberName[50], value[50];
                    printf("Enter member name: ");
                    scanf(" %[^\n]", memberName);
                    printf("Enter value: ");
                    scanf(" %[^\n]", value);
                    int count = countEntries(memberName, value);
                    printf("Count: %d\n", count);
                    break;
                }
                case 4: {
                    int sortChoice;
                    printf("Sort by:\n");
                    printf("  1. Table Type\n");
                    printf("  2. Surface Material\n");
                    printf("  3. Structural Material\n");
                    printf("  4. Street / Avenue\n");
                    printf("  5. Neighbourhood ID\n");
                    printf("  6. Neighbourhood Name\n");
                    printf("  7. Ward\n");
                    printf("  8. Latitude\n");
                    printf("  9. Longitude\n");
                    printf(" 10. Site ID\n");
                    printf("Enter your choice: ");
                    scanf("%d", &sortChoice);
                    getchar();  // Clear newline
                
                    char *sortField = NULL;
                    switch (sortChoice) {
                        case 1: sortField = "tableTypeId"; break;
                        case 2: sortField = "surfaceMaterialId"; break;
                        case 3: sortField = "structuralMaterialId"; break;
                        case 4: sortField = "streetAvenue"; break;
                        case 5: sortField = "neighbourhoodId"; break;
                        case 6: sortField = "neighbourhoodName"; break;
                        case 7: sortField = "ward"; break;
                        case 8: sortField = "latitude"; break;
                        case 9: sortField = "longitude"; break;
                        case 10: sortField = "siteId"; break;
                        default: printf("Invalid choice.\n"); break;
                    }
                
                    if (sortField != NULL) {
                        sortByMember(sortField);
                        printf("Sorted by %s.\n", sortField);
                    }
                
                    break;
                }
                case 5: {
                    int tableID;
                    char memberName[50], value[50];
                    printf("Enter table ID: ");
                    scanf("%d", &tableID);
                    getchar();
                    printf("Enter member name to edit: ");
                    scanf(" %[^\n]", memberName);
                    printf("Enter new value: ");
                    scanf(" %[^\n]", value);
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
    printf("6. Report by Neighbourhood\n");
    printf("7. Report by Ward\n");
    printf("8. Exit\n");
}

void importDatabase(int *databaseLoaded) {
    char filename[100];
    printf("Enter database filename to import: ");
    scanf("%99s", filename);
    importDB(filename);
    *databaseLoaded = 1;
}

void exportDatabase() {
    char filename[100];
    printf("Enter filename to export database: ");
    scanf("%99s", filename);
    exportDB(filename);
}
