#include <dirent.h>
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <vector>
#include <iomanip>
#include <algorithm>

#include "TextFile.h"

using namespace std;

void PrintGreeting();

int main(int argc,char* argv[]){

  std::vector <TextFile*> files;
  
  PrintGreeting();
    
  // read files from directory
  struct dirent *pDirent;
  DIR *pDir;  
  
  // get folder name
  pDir = opendir(argv[1]);
    
  // guard 
  if (pDir == NULL) {
    cout<<"Cannot open directory" << endl;
    return 1;
  }
  
  // store file names
  vector<string> filenames;

  // read each entry
  while ((pDirent = readdir(pDir)) != NULL) {    
    string name = pDirent->d_name;
    
    // only read .txt
    if(name.substr(name.find_last_of(".") + 1) == "txt"){
      cout << pDirent->d_name << endl;
      filenames.push_back(pDirent->d_name);
    }  
  }
  
  // sort file names
  sort(filenames.begin(),filenames.end());

  string folderPath = argv[1];
  
  // create file obj
  for(int f = 0; f < filenames.size(); f++ ){
    
    // get file abs path
    string path = folderPath + "/" + filenames[f];
    char* cPath = new char[path.length()+1];
    strcpy(cPath,path.c_str());
    
    // crate file obj
    TextFile* file = new TextFile(cPath);

    // set file name
    char* fname = new char[filenames[f].length()+1];
    strcpy(fname,filenames[f].c_str());
    file->SetFilename(fname);
    
    // store in vector
    files.push_back(file);
  }

  // open output file
  ofstream resultFile;
  resultFile.open("result.txt");

  
  // to sotre most similar files
  string simFiles[2];
  float maxJac = 0;

  // each file
  for(int i = 0; i < files.size(); i++){
    
    // check each file
    for(int j = i; j < files.size(); j++){
      
      HashTable<char*> myTable = files[i]->GetHashtable();
      HashTable<char*> otherTable = files[j]->GetHashtable(); 
      
      float jac = myTable.CalJaccardVal(otherTable);
      
      resultFile << "J("  << files[i]->GetFilename() << ", "
		 << files[j]->GetFilename() << ") = "
		 << std::fixed << std::setprecision(1) << jac
		 << endl;
      
      // record largest jaccard val
      // not the same file
      if(jac > maxJac && jac != 1){
	maxJac = jac;
	
	simFiles[0] = files[i]->GetFilename();
	simFiles[1] = files[j]->GetFilename();
      }
    }
  }
  
  // output most similar
  resultFile << "Most similar: \"" << simFiles[0]
	     << "\", \"" << simFiles[1] 
	     << "\""
	     << endl; 
  

  resultFile.close();
  closedir (pDir);
  return 0;
}

void PrintGreeting(){
  cout << "Yadikaer Yasheng" << endl;
  cout << "Section 3" << endl;
}


