#ifndef TEXTFILE_H
#define TEXTFILE_H

using namespace std;

#include "QuadraticProbing.h"

class TextFile{
public:
  TextFile(char* fileName);
  ~TextFile();
  
  void SetFilename(char* name){fileName = name;}
  char* GetFilename(){return fileName;}
  HashTable<char*> GetHashtable(){return hash;}
  

private:
  char* fileName;
  HashTable<char*> hash;
};

#endif
