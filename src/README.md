This is the directory where your source code would reside.

# Source Files
**`pharmacy_counting.cpp`**: This is the main program. Contains functions to read and parse the input file as well as functions to write out the drug data.

**`patient_data.h*``: Header file that includes a basic `PatientEntry` struct for each line entry in the input file as well as a basic class to store the entire input file information after being parsed.

**`drug_data.h`** and **`drug_data.cpp`**: Source files for `drug_data` class as well as `DrugEntry` struct. `DrugEntry` retains necessary information for one line of the output file as well as tracks prescribers for a given drug to ensure counting of unique prescribers. Also contains functions to accumulate up drug costs and to sort the final drug list.

**`util.h`**: My utility functions for this project, at this point only has one DJB2 Hash function.

**`List.h`**: Basic Linked List class that I created as part of my old data structures course rather than recreating one.

**`HashTable.h`**: Hash Table class that was also created as part of my old data structures course but modified to use a DJB2 hash.
