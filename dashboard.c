#include <stdio.h>

// Function prototypes
void importDatabase(int *databaseLoaded);
void exportDatabase();
void countEntries();
void sortDatabase();
void editEntry();
void generateReport();
void displayMenu();

int main() {
    int choice;
    int databaseLoaded = 0;  // 0 = not loaded, 1 = loaded

    while (1) {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();  // Consume the newline left by scanf

        if (choice == 7) {
            printf("Exiting program...\n");
            break;
        }

        if (choice == 1) {
            importDatabase(&databaseLoaded);
        } else if (databaseLoaded == 0) {
            printf("Error: Import the database first.\n");
        } else {
            switch (choice) {
                case 2: exportDatabase(); break;
                case 3: countEntries(); break;
                case 4: sortDatabase(); break;
                case 5: editEntry(); break;
                case 6: generateReport(); break;
                default: printf("Invalid option. Please enter a number between 1 and 7.\n");
            }
        }
    }

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

// !! we can fix all of this later when we've got our functions going !!

void importDatabase(int *databaseLoaded) {
    char filename[100];
    printf("Enter database filename to import: ");
    scanf("%99s", filename);
    
    // TODO: Implement actual import logic
    printf("Database '%s' imported successfully!\n", filename);

    *databaseLoaded = 1;  // Mark database as loaded
}

void exportDatabase() {
    char filename[100];
    printf("Enter filename to export database: ");
    scanf("%99s", filename);

    // TODO: implement actual export logic
    printf("Database exported to '%s'.\n", filename);
}

void countEntries() {
    char memberName[50], value[50];
    printf("Enter member name: ");
    scanf("%49s", memberName);
    printf("Enter value: ");
    scanf("%49s", value);

    // TODO: implement actual count logic
    int count = 0;  // placeholder for actual count result
    printf("Found %d entries with %s = %s.\n", count, memberName, value);
}

void sortDatabase() {
    char memberName[50];
    printf("Enter member name to sort by: ");
    scanf("%49s", memberName);

    // TODO: Implement actual sorting logic
    printf("Database sorted by '%s'.\n", memberName);
}

void editEntry() {
    int id;
    char memberName[50], value[50];

    printf("Enter entry ID to edit: ");
    scanf("%d", &id);
    printf("Enter member name: ");
    scanf("%49s", memberName);
    printf("Enter new value: ");
    scanf("%49s", value);

    // TODO: implement actual editing logic here
    printf("Updated entry ID %d: %s = %s.\n", id, memberName, value);
}

void generateReport() {
    int id;
    printf("Enter Ward or Neighbourhood ID: ");
    scanf("%d", &id);

    // TODO: implement actual report generation logic
    printf("Generated report for ID: %d.\n", id);
}
