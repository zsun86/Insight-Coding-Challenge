#include "drug_data.h"


/* Function to accumulate drug data with new entries from input file */
void drug_data::update_with_patient_entry(string dname, unsigned int pname_hash, double dcost) {
	DrugEntry dentry;
	bool res = drug_entries.lookup(dentry, dname); // Fetch existing drug entry if its available
	
	// Checks if we have a new drug or not
	if (!res) {
		dentry.dname = dname;
		//dentry.num_prescriber = 1;
		dentry.prescribers.clear();
		dentry.prescribers.push_back(pname_hash);
		dentry.tot_cost = dcost;
		drug_list.push_back(dname);
		drug_entries.install(dentry, dname); // Adds new drug entry to our hash table
	}
	else if (!dentry.dname.compare(dname)) {
		// Check list of prescriber hashes to see if this prescriber already prescribed this drug or not
		if (find(dentry.prescribers.begin(), dentry.prescribers.end(), pname_hash) == dentry.prescribers.end()) {
			dentry.prescribers.push_back(pname_hash);
			//dentry.num_prescriber++;
		}
		dentry.tot_cost += dcost;
		drug_entries.update(dentry, dname);
	}
	else {
		cout << "Incorrect entry retrieved" << endl; // We retrieved a drug but for some reason the keys dont match (drug name was incorrect).
	}
}

/* Public function to initiate sorting in a descending order based on total cost and then by drug name */
void drug_data::sort_drug_list() {
	cout << "Sorting Drug List" << endl;
	drug_quicksort(0, drug_list.size()-1);
	cout << "Done Sorting" << endl;
}

/* Recrusive quicksort function for sorting drug list in descending order based on total cost and then by drug name if costs are tied */
void drug_data::drug_quicksort(int s, int e) {
	int p;
	int i, j;
	DrugEntry di, dj, dp;
	string tmp;
	if (s < e) {
		p = e;
		drug_entries.lookup(dp, drug_list[p]);
		i = s;
		for (j = s; j < e; j++) {
			drug_entries.lookup(di, drug_list[i]);
			drug_entries.lookup(dj, drug_list[j]);
			if (dj > dp) {
				tmp = drug_list[i];
				drug_list[i] = drug_list[j];
				drug_list[j] = tmp;
				i++;
			}
			else if (dj.tot_cost == dp.tot_cost) {
				if (dj.dname.compare(dp.dname) > 0) {
					tmp = drug_list[i];
					drug_list[i] = drug_list[j];
					drug_list[j] = tmp;
					i++;
				}
			}
		}
		tmp = drug_list[p];
		drug_list[p] = drug_list[i];
		drug_list[i] = tmp;
		drug_quicksort(s, i-1);
		drug_quicksort(i+1, e);
	}
}