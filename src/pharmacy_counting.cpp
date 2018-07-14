#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cmath>
using namespace std;

#include "patient_data.h"
#include "drug_data.h"

/*
	Extract Field, Checks if in quotes.
*/
void peekGetField(stringstream &ss, string &field) {
	if (!(ss.peek() == '"')) {
		getline(ss, field, ',');
	}
	else {
		ss.get();
		getline(ss, field, '"');
		field = '"' + field + '"'; // Add quotes back to field for output purposes later
		ss.get();
	}
}

void parseLine(string line, PatientEntry &patient) {
	string field, lname, fname;
	stringstream ss(line);

	//patient.id = stoi(field);
	ss >> patient.id;
	peekGetField(ss, field); // To advance the sstream extraction point.
	
	peekGetField(ss, field);
	lname = field;
	
	peekGetField(ss, field);
	fname = field;
	patient.pname_hash = DJBHash(lname+fname);
		
	peekGetField(ss, field);
	patient.dname = field;
	
	//patient.dcost = stod(field);
	ss >> patient.dcost;
	peekGetField(ss, field); // To advance the sstream extraction point.
}

void parse_ifile(ifstream &ifs, patient_data &if_data) {
	PatientEntry p_ent;
	string line;
	
	getline(ifs, line);	// Assume first line is header names
	while (getline(ifs, line)) {
		parseLine(line, p_ent);
		if (p_ent.id > 0) 
			if_data.addEntry(p_ent.id, p_ent.pname_hash, p_ent.dname, p_ent.dcost);
	}
	cout << "Found " << if_data.getNumEntries() << " entries." << endl;
}

void process_data(patient_data &if_data, drug_data &of_data) {
	int num_patient_entries = if_data.getNumEntries();
	int i;
	PatientEntry ent;
	//cout << "Processing " << num_patient_entries << " entries" << endl;
	for (i = 0; i < num_patient_entries; i++) {
		if (i % 1000000 == 0) {
			cout << "Processing entries " << i+1 << " through " << min(i+1000000, num_patient_entries) << " of " << num_patient_entries << " total entries\r";
			cout.flush();
		}
		ent = if_data.getEntry(i);
		of_data.update_with_patient_entry(ent.dname, ent.pname_hash, ent.dcost);
	}
	cout << "\nFinished processing input data" << endl;
}

void write_ofile(ofstream &ofs, drug_data &of_data) {
	DrugEntry ent;
	int num_drugs = of_data.getNumDrugs();
	int i;
	int precision_val;
	ofs << "drug_name,num_prescriber,total_cost";
	for (i = 0; i < num_drugs; i++) {
		ent = of_data.getEntry(i);
		precision_val = ceil(log10(ent.tot_cost)) + 2; // Determine magnitude of cost to set output precision to include cent precision
		ofs << "\n" << ent.dname << "," << ent.prescribers.size() << "," << setprecision(precision_val) << ent.tot_cost;
	}
	
}


int main(int argc, char **argv) {
	char* fname;
	char* ofname;
	ifstream ifs;
	ofstream ofs;
	patient_data if_data;
	drug_data of_data;
	
	if (argc < 3) {
		cout << "Invalid parameters" << endl;
		cout << "To use this program please use the following syntax:" << endl;
		cout << argv[0] << " input_file output_file" << endl;
		return 0;
	}
	else {
		fname = argv[1];
		ofname = argv[2];
	}
	
	ifs.open(fname);
	if (!ifs.fail()) {
		cout << "Opening File: " << fname << endl;
	}
	else {
		cout << "File " << fname << " Failed to Open" << endl;
		return 0;
	}
	parse_ifile(ifs, if_data); // Reads and parses input file fname into a patient_data class
	ifs.close();
	
	process_data(if_data, of_data); // Processes imported data as per Coding Challenge instructions
	
	cout << of_data.getNumDrugs() << " types of drugs prescribed" << endl;
	of_data.sort_drug_list(); // Sorts drug list by descending order of total cost
	
	ofs.open(ofname, ofstream::out);
	if (!ofs.fail()) {
		cout << "Writing to File: " << ofname << endl;
	}
	else {
		cout << "File " << ofname << " Failed to Open" << endl;
		return 0;
	}
	write_ofile(ofs, of_data); // Writes to output file
	ofs.close();
	
	cout << "Terminating Program" << endl;
	return 0;
}

