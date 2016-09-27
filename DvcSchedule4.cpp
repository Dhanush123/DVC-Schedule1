#define _CRT_SECURE_NO_WARNINGS

#include <vector>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

#include <cstring> // for strtok and strcpy

#include "DynamicArray.h"

struct CInfo{
  string code;
  int typeTotal;
};

void updateRecords(string,DynamicArray<CInfo>&);

int main()
{
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

  int count = 0;
  int duplicates = 0;
  int aSeen = 0;

  // read the input file
  while (fin.good())
  {

    ++count;
//    cout << count << endl;
//      if (count % 1 == 0)
    cout << count << "\r";
      cout.flush();
//  	cout << count << "%\r";

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
    for (int i =0; i < alreadySeen.capacity(); i++){
    	if (alreadySeen[i] == key){
    		found = true;
    	}
    }

    if (found)
    {
      duplicates++;
      cout << "num duplicates: " << duplicates << endl;
//      // if I get this far, then it's a valid record
//      cout << term << '|' << section << '|'
//      << course << '|' << instructor << '|'
//      << whenWhere << '|' << subjectCode << endl;


  	  //++count;
  	  //if (count == 10000) break;
    }
    else
    {
    	alreadySeen[aSeen] = key;
    	aSeen++;
    	updateRecords(course,recordKeep);
    }
  }
  cout << endl;
  cout << "done" << endl;
  fin.close();
}

void updateRecords(string course,DynamicArray<CInfo>& rk){

  bool found = false;
  for (int i = 0; i < rk.capacity(); i++){
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
    rk[rk.capacity()] = ci;
  }
}
