#include "TextFile.h"
#include <fstream>
#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>

using namespace std;

TextFile::TextFile(char* fileName)
{  
  // read file
  ifstream file;
  file.open(fileName);
  
  this->fileName = fileName;
  
  string line;
  while(getline(file,line)){
    
    transform(line.begin(),line.end(),line.begin(),(int (*)(int))tolower);
    
    line =  line.substr( 0, line.find_last_not_of( '\n' ) + 1 );
    
    char* token;
    
    char* charLine = new char[line.length()+1];
    strcpy(charLine,line.c_str());
    
    token = strtok(charLine,", . - << >> \n ( ) ! ' ; [ ] ?  \" ");
    
    while(token != NULL){
      char* hashStr = new char[sizeof(token)+1];
      strcpy(hashStr,token);
      
      hash.insert(hashStr);
       
      token = strtok(NULL,", . - << >> \n () ! ' ; [ ] ? \" ");
    }
  }
  
  file.close();
}

TextFile::~TextFile()
{
}



