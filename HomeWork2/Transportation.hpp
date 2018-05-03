//
//  Transportation.hpp
//  HomeWork2
//
//  Created by Matan Raviv on 5/3/18.
//  Copyright © 2018 Matan Raviv. All rights reserved.
//

#ifndef Transportation_hpp
#define Transportation_hpp

#include <stdio.h>
#include <iostream>
#include <fstream>

using namespace std;

class Transportation
{
    
private:
    
    struct FileValue // struct incase we need ?
    {
        int wantedIndex;
        int refCount;
        std::fstream * data;
        FileValue(); // c'tor
        FileValue(FileValue * rhsFile ); // copy c'tor
        FileValue & operator=(FileValue &rhs) noexcept;
        char * operator[](int index) throw(const char *);
        void operator=(char other);
        string * valueName;
        ~FileValue(); // d'tor
    };
    FileValue *value;
    
public:
    // data member
    string * fileName;
    
    Transportation(string * initThis) noexcept; // c'tor
    Transportation(const Transportation &f2) noexcept; //copy c'tor
    ~Transportation(); // d'tor
    
    // operators incase we need
    char * operator[](int i) const throw (const char*);
    FileValue & operator[](int i);
    Transportation & operator= ( const Transportation& rhs) noexcept;
    Transportation& operator= ( Transportation* rhs) noexcept;


};

#endif /* Transportation_hpp */
