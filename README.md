# Picnic Table Data Processing Module
What's included in this directory:
- DB.c
- DB.h
- DB_impl.c
- DB_impl.h
- dashboard.c
- README.md _(you are here)_

## DB.c
The main C source file that implements core functionalities of the picnic table database.

### <ins>Key Functions and Structures:</ins>
**addNeighbourhood:** Adds a unique neighborhood to the database. It checks for existing neighborhoods before adding a new one to the list.

**importDB:** Imports data from a CSV file. This function reads a CSV file line by line, processes the data, and stores it in the appropriate structures for picnic tables, table types, surface materials, and neighborhoods.

**exportDB:** Exports the current state of the database to a CSV file.

**countEntries:** Counts the number of entries that match a given value for a specific table member (e.g., "Table Type," "Surface Material," etc.).

**editTableEntry:** Allows editing a specific field (like table type or material) for a picnic table entry based on the siteID. If the new value is not found in the table, it is added.

**freeDB:** Frees the dynamically allocated memory used by the database to prevent memory leaks.

**compareByTableId, compareBySiteId, compareByTableTypeId, compareBySurfaceMaterialId, compareByStructuralMaterialId, compareByStreetAvenue, compareByNeighbourhoodId:** Sorting functions used with qsort to sort picnic tables by various attributes like tableId, siteId, tableTypeId, and so on.

**DataBase:** A global structure that holds all the tables (table types, surface materials, structural materials, neighborhood data, and picnic table data).

**Table:** A structure used to store unique values for table types, materials, etc.

**NeighbourhoodTable:** A structure used to store neighborhood information.

**PicnicTable:** A structure that holds the information for each picnic table, including its siteId, tableTypeId, surfaceMaterialId, structuralMaterialId, streetAvenue, neighbourhoodId, neighbourhoodName, ward, latitude, and longitude.

## DB.h
Defines the interface for the picnic table database.

### <ins>Key Functions and Structures:</ins>
**Pair:** Holds a code and its associated type.

**Table:** Represents a collection of table types or materials.

**NeighbourhoodTable:** Stores neighborhood data as pairs of IDs and names.

**PicnicTable:** Stores detailed information about individual picnic tables (e.g., type, material, location).

**countEntries:** Counts entries based on specific attributes.

**sortByMember:** Sorts tables by a given attribute.

**editTableEntry:** Edits a specific table entry based on its ID and member.

**reportByNeighbourhood, reportByWard:** Print reports grouped by neighborhood or ward.

**freeDB:** Frees allocated memory.

**importDB, exportDB:** Imports and exports data to/from CSV files.

## DB_impl.c
### <ins>Key Functions:</ins>
**editHelper:** Searches for a value in the tables (tableType, surfaceMaterial, structuralMaterial) and returns the index if found.

**countEntriesHelper:** A helper function to count how many entries in picnicTableTable match a specified attribute (e.g., table type, material, neighborhood, ward).

**resizeTable:** Dynamically resizes the arrays (tableTypeTable, surfaceMaterialTable, structuralMaterialTable) when new values need to be added.

## DB_impl.h
Contains private function declarations for the database implementation, not intended to be used for external users of the database.

### <ins>Key Functions:</ins>
**countEntriesHelper:** A helper function to count how many entries in the picnicTableTable match a specified attribute (e.g., table type, material, neighborhood, ward).

**editHelper:** A helper function that searches for a value in the internal tables (tableType, surfaceMaterial, structuralMaterial) and returns the index if found.

**resizeTable:** Dynamically resizes internal arrays (e.g., tableTypeTable, surfaceMaterialTable, structuralMaterialTable) to add new entries.

## dashboard.c
The main UI for interacting with the database through a menu system. Allows importing, exporting, and report manipulation and reports based on the data in the database through user ipnutted choices.

### <ins>Key Functions and Structures:</ins>
**Import Database** (Choice 1): Prompts the user for a filename and imports the database from the specified file.

**Export Database** (Choice 2): Prompts the user for a filename and exports the current database to the specified file.

**Count Entries** (Choice 3): Allows the user to enter a member name and value, then counts how many times that combination appears in the database.

**Sort By** (Choice 4): Provides options to sort the data by various fields (e.g., table type, surface material, neighborhood ID).

**Edit Entry** (Choice 5): Allows the user to edit an entry in the database by specifying the table ID, member name, and new value.

**Report by Neighbourhood** (Choice 6): Generates a report based on the neighborhood data.

**Report by Ward** (Choice 7): Generates a report based on the ward data.

**Exit** (Choice 8): Exits the program.
