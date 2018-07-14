#include <string>
#include <vector>
#include <iostream>
using namespace std;

/*
	patient_data class with basic PatientEntry struct which incoporates the information from each row in input file. Instead of storing names, storing hashed copies of the full name
*/

struct PatientEntry {
	PatientEntry(int id = 0, unsigned int pname_hash = 0, string dname = "", double dcost = 0) : id(id), pname_hash(pname_hash), dname(dname), dcost(dcost) {}
	int id;
	unsigned int pname_hash;
	string dname;
	double dcost;
};

class patient_data {
	public:
		patient_data() {}
		
		void addEntry(int id, unsigned int pname_hash, string dname, double dcost) {
			PatientEntry ent(id, pname_hash, dname, dcost);
			
			patient_entries.push_back(ent);
			//patient_entries.emplace_back(id, pname_hash, dname, dcost);
		}
		
		PatientEntry getEntry(int id) { return patient_entries[id]; }
		
		int getNumEntries() { return patient_entries.size(); }
		
	private:
		vector<PatientEntry> patient_entries;
		
};

