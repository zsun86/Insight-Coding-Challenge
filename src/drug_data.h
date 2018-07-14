#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

#include "HashTable.h"

/*
	drug_data class and basic DrugEntry struct. DrugEntry contains the necessary information for each row in the output file.
*/

struct DrugEntry {
	string dname;
	//int num_prescriber;
	vector<unsigned int> prescribers; // Store hashed copies of each prescriber name.*See Note
	double tot_cost;
	
	bool operator==(const string s) {  // Overloads comparison operator when comparing to a string key
		return !dname.compare(s);
	}
	
	// Comparison operators for ranking against each other based on cost
	bool operator<(const DrugEntry s) {
		return tot_cost < s.tot_cost;
	}
	bool operator>(const DrugEntry s) {
		return tot_cost > s.tot_cost;
	}
	bool operator<=(const DrugEntry s) {
		return tot_cost <= s.tot_cost;
	}
	bool operator>=(const DrugEntry s) {
		return tot_cost >= s.tot_cost;
	}
};


class drug_data {
public:
	drug_data(int num_entries = DEFAULT_HASH_SIZE) : drug_entries(num_entries) { }
	
	void update_with_patient_entry(string dname, unsigned int pname_hash, double dcost);
	
	int getNumDrugs() {
		return drug_list.size();
	}
	
	// Basic Entry fetch
	DrugEntry getEntry(int id) {
		DrugEntry entry;
		drug_entries.lookup(entry, drug_list[id]);
		return entry;
	}
	
	void sort_drug_list();
	
	~drug_data() { }

private:
	HashTable<DrugEntry> drug_entries;
	vector<string> drug_list;
	
	void drug_quicksort(int start, int end); // utility function to quicksort drug_list based on total cost in descending order
};



/* 
	*Notes: I realize storing hashed copies of prescriber names has the potential of collisions but it at
	least preserves memory rather than storing explicit names and makes checking uniqueness faster. For
	the purposes of this exercise I consider the risks reasonable enough. My alternative approach would be
	to assign a unique id to each prescriber and store that instead, but that would require a seperate hash table
	to lookup said id.
*/
