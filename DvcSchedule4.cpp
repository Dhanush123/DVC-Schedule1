// Programmer: Dhanush Patel
// Programmer's ID: 1553428

#define _CRT_SECURE_NO_WARNINGS

#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

#include <cstring> // for strtok and strcpy

#include "DynamicArray.h"

struct CInfo{
  string code;
  int typeTotal;
};

void updateRecords(string, DynamicArray<CInfo>&, int&);

int main(){
  cout << "Programmer: Dhanush Patel\n";
  cout << "Programmer's ID: 1553428\n";
  cout << "File: " << __FILE__ << endl;
  
  // for parsing the inputfile
  char* token;
  char buf[1000];
  const char* const tab = "\t";

  // open the input file
  ifstream fin;
  fin.open("dvc-schedule.txt");
  if (!fin.good()) throw "I/O error";

  DynamicArray<string> alreadySeen;
  DynamicArray<CInfo> recordKeep;

  int duplicates = 0;
  int aSeen = 0;
  int rKeep = 0;
  double count = 0.0;

  // read the input file
  while (fin.good()){
    count++;
    cout << (count/74411) * 100 << "% \r";
    cout.flush();
    // read the line
    string line;
    getline(fin, line);
    strcpy(buf, line.c_str());
    if (buf[0] == 0) continue; // skip blank lines

    // parse the line
    const string term(token = strtok(buf, tab));
    const string section(token = strtok(0, tab));
    const string course((token = strtok(0, tab)) ? token : "");
    const string instructor((token = strtok(0, tab)) ? token : "");
    const string whenWhere((token = strtok(0, tab)) ? token : "");
    if (course.find('-') == string::npos) continue; // invalid line: no dash in course name
    const string subjectCode(course.begin(), course.begin() + course.find('-'));

    string key = term + "," +section;
    bool found = false;
    for (int i = 0; i < alreadySeen.capacity(); i++){
    	if (alreadySeen[i] == key){
    		found = true;
    	}
    }

    if (found){
      duplicates++;
    }
    else
    {
    	alreadySeen[aSeen] = key;
    	aSeen++;
        updateRecords(subjectCode, recordKeep, rKeep);
    }
  }
  cout << "number of duplicates: " << duplicates << endl;
  
  for(int i = 0; i < rKeep; i++){
    for(int j = 0; j < rKeep; j++){
      if(recordKeep[i].code < recordKeep[j].code)
        swap(recordKeep[i], recordKeep[j]);
    }
  }
  
  for(int i = 0; i < recordKeep.capacity(); i++){
    if(recordKeep[i].code == "" || recordKeep[i].typeTotal == 0){
      continue;
    }
    cout << recordKeep[i].code << ": " << recordKeep[i].typeTotal << endl;
  }
  
  fin.close();
}

void updateRecords(string course, DynamicArray<CInfo>& rk, int& used){
  bool found = false;
  for (int i = 0; i < used; i++){
    if (rk[i].code == course){
      rk[i].typeTotal++;
      found = true;
      break;
    }
  }
  if (!found){
    CInfo ci;
    ci.code = course;
    ci.typeTotal = 1;
    rk[used] = ci;
    used++;
  }
}