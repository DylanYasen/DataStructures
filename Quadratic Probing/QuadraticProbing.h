#ifndef QUADRATIC_PROBING_H
#define QUADRATIC_PROBING_H

#include <vector>
#include <string>
#include <iostream>
using namespace std;

int nextPrime( int n );

// QuadraticProbing Hash table class
//
// CONSTRUCTION: an approximate initial size or default of 101
//
// ******************PUBLIC OPERATIONS*********************
// bool insert( x )       --> Insert x
// bool remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// void makeEmpty( )      --> Remove all items
// int hash( string str ) --> Global method to hash strings

template <typename HashedObj>
class HashTable
{
 public:
    explicit HashTable( int size = 101 ) : array( nextPrime( size ) )
    { makeEmpty( );}

  bool contains( const HashedObj & x ) const
  {
    int pos = findPos(x);
    bool active = isActive(pos);
    
    //cout << "find position at " << pos << "which is active:" << active << endl;
    
    return isActive( findPos( x ) );
  }
  
  bool hasValue(const HashedObj & x){
    
    
  }
  
  HashedObj GetValAtKey(int key){
    
    return array[key].element;
  }

  void makeEmpty( )
  {
    currentSize = 0;
    for( int i = 0; i < array.size( ); i++ )
      array[ i ].info = EMPTY;
  }
  
  bool insert( const HashedObj & x )
  {
    //cout << "hash insert " << x << endl;
    
    if(contains(x)){
      
      //cout << "already contains " << x  << " don't add" << endl
      return false;
    }    
    
    // Insert x as active
    int currentPos = findPos( x );
    
    if( isActive( currentPos ) )
      return false;
    
    array[ currentPos ] = HashEntry( x, ACTIVE );
    
    // Rehash; see Section 5.5
    if( ++currentSize > array.size( ) / 2 )
      rehash( );
    
    
    //cout << "inserted " << x  <<" at " << currentPos <<endl;
    //cout << currentPos << " is now active: " << isActive(currentPos) << endl;

    return true;
  }
  
  void printHash(){
    
    for(int i = 0; i < array.size();i++){
      
      if(!isActive(i))
	continue;
      
      cout << "index " << i << " : " << array[i].element  << endl;
    }    
  }
  

  bool remove( const HashedObj & x )
  {
    int currentPos = findPos( x );
    if( !isActive( currentPos ) )
      return false;
    
    array[ currentPos ].info = DELETED;
    return true;
  }
  
  float CalJaccardVal(HashTable<char*> hashTable){

    // debug
    //cout  << "MY TABLE CONTENT========" << endl;
    //printHash();
    
    //cout << "HIS TABLE CONTENT========" << endl;
    //hashTable.printHash();

    int intersectNum = 0 ;
    int unionNum = 0;
    
    //cout << "my array " << array.size() << endl;
    //cout << "my count " << GetEntryCount() << endl;
    
    //cout << "his array " << hashtable.array.size() << endl;
    //cout << "his count " << hashTable.GetEntryCount() << endl;   
    
    int count = 0;
    for(int i = 0; i < array.size(); i++){
      
      if(!isActive(i))
	continue;	
      
      //cout << array[i].element << endl;
      
      // no need to check no more
      /*
      if(count > GetEntryCount()){
      	cout << "no need to loop no more" << endl;
	break;
      }
      */      
      
      /*
	int key = hash(array[i].element);
	HashedObj obj = hashTable.GetValAtKey(i);
	
	if(obj == GetValAtKey(i)){
	intersectNum++;
	count++;
	}
      */
      
      
      if(hashTable.contains(array[i].element)){	
	//cout << "found same " << array[i].element << endl;
	intersectNum++;
	count++;
      }
      
    }
    
    unionNum = GetEntryCount() + hashTable.GetEntryCount() - intersectNum;
    
    //cout << "intersect num:" << intersectNum << endl;
    //cout << "union num:" << unionNum << endl;

    return ((float)intersectNum / (float)unionNum);
    }
  
    int GetEntryCount(){
      
      int size = 0;
      for(int i = 0; i < array.size(); i++){	
	
	if(isActive(i)){
	  size++;
	}	
      }
      
      return size;
    }
    
    enum EntryType { ACTIVE, EMPTY, DELETED };
    
  private:
    struct HashEntry
    {
      HashedObj element;
      EntryType info;

    HashEntry( const HashedObj & e = HashedObj( ), EntryType i = EMPTY )
	: element( e ), info( i ) { }
    };
    
    vector<HashEntry> array;
    int currentSize;
    
    bool isActive( int currentPos ) const
    { return array[ currentPos ].info == ACTIVE; }
    
    int findPos( const HashedObj & x ) const
    {
      int offset = 1;
      int currentPos = myhash( x );
      
      if( currentPos >= array.size( ) )
	currentPos -= array.size( );

      /*
      // Assuming table is half-empty, and table length is prime,
          // this loop terminates
      while( array[ currentPos ].info != EMPTY &&
	     array[ currentPos ].element != x )
	{
	  currentPos += offset;  // Compute ith probe
	  offset += 2;
	  if( currentPos >= array.size( ) )
	    currentPos -= array.size( );
	}
      */      

      return currentPos;
    }
    
    /*
    int findCurrentPos(const HashedObj & x) const{
    int offset = 1;
      int currentPos = myhash( x );

      // Assuming table is half-empty, and table length is prime,
      // this loop terminates
      while( array[ currentPos ].info != EMPTY &&
	     array[ currentPos ].element != x )
        {
	  currentPos += offset;  // Compute ith probe
	  offset += 2;
	  if( currentPos >= array.size( ) )
	    currentPos -= array.size( );
        }

	return currentPos;
      }
    */
    
    void rehash( )
    {
      vector<HashEntry> oldArray = array;
      
      // Create new double-sized, empty table
      array.resize( nextPrime( 2 * oldArray.size( ) ) );
      for( int j = 0; j < array.size( ); j++ )
	array[ j ].info = EMPTY;
      
      // Copy table over
      currentSize = 0;
      for( int i = 0; i < oldArray.size( ); i++ )
	if( oldArray[ i ].info == ACTIVE )
	  insert( oldArray[ i ].element );
    }
    
    int myhash( const HashedObj & x ) const
    {
      int hashVal = hash( x );
      
      hashVal %= array.size( );
      if( hashVal < 0 )
	hashVal += array.size( );
      
      return hashVal;
    }
};

int hash( const string & key );
int hash( int key );

#endif
