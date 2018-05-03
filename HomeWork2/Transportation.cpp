//
//  Transportation.cpp
//  HomeWork2
//
//  Created by Matan Raviv on 5/3/18.
//  Copyright © 2018 Matan Raviv. All rights reserved.
//

#include "Transportation.hpp"



//
//  file.cpp
//  hw1
//
//  Created by Matan Raviv on 4/7/18.
//  Copyright © 2018 Matan Raviv. All rights reserved.
//

#include "Transportation.hpp"

using namespace std;

// CONSTRUCTORS
// string c'tor
Transportation::Transportation(string * initThis) noexcept
{
    fileName = new string (*initThis);
    value = new FileValue();
    value->valueName=fileName;
    value->data = new fstream(fileName->c_str(),std::ios::in | std::ios::out | std::ios::app);
    
}

// d'tor
Transportation::~Transportation()
{
    delete (fileName);
    --value->refCount;
    if(value->refCount==0) // if the refCounter = 1 this is the last reference hense delete the entire object
    {
        delete (value);
        return;
    }
    
}

// Copy c'tor
Transportation::Transportation(const Transportation &otherFile) noexcept
{
    fileName=otherFile.fileName;
    value = new FileValue();
    value = otherFile.value;
    value->data = otherFile.value->data;
    
}

// FileValue C'tor
Transportation::FileValue::FileValue() // fileValue constructor and destructor
:refCount(1),wantedIndex(0),valueName()
{
    
}
Transportation::FileValue::~FileValue() // FileValue D'tor
{
    if(--refCount!=0)
    {
        refCount--;
    }
    else
    {
        delete(data);
        delete(valueName);
    }
}
char * Transportation::FileValue::operator[](int index) throw(const char *) // write support operator
{
    
    int i;
    char *a = nullptr;
    data->open(*this->valueName, std::ios::in | std::ios::out | std::ios::app);
    if(data->gcount()<wantedIndex)
        throw "not enough characters in the file - exception from reading operator";
    for(i=0;i<wantedIndex;i++)
        *a=data->get();
    data->close();
    return a;
    
}
void Transportation::FileValue::operator=(char typeThis)
{
    
    data->open(*valueName, std::ios::in | std::ios::out | std::ios::app);
    data->put(typeThis);
    data->flush();
    data->clear();
    
}

Transportation::FileValue & Transportation::FileValue::operator=(FileValue &rhs) noexcept
{
    ++rhs.refCount;
    --this->refCount;
    if(this->refCount==0)
    {
        this->data->close();
        delete (this->data);
    }
    this->data=rhs.data;
    return *this;
}

Transportation::FileValue::FileValue(FileValue * rhsFile ) // fileValue constructor and destructor
{
    rhsFile->refCount++;
    this->data=rhsFile->data;
}

// OPERATORS
Transportation& Transportation::operator= (Transportation* rhs) noexcept
{
    if(this==&*rhs)
        return *this;
    this->fileName=rhs->fileName;
    this->value=rhs->value;
    return *this;
}

Transportation& Transportation::operator= ( const Transportation& rhs) noexcept
{
    if (value==rhs.value)
        return *this;
    this->fileName=rhs.fileName;
    ++rhs.value->refCount;
    --this->value->refCount;
    
    if (this->value->refCount == 0)
        delete value;
    this->value=rhs.value;
    
    return *this;
}




char * Transportation::operator[](int wantedIndex) const throw (const char*)
{
    
    int i;
    char *a = nullptr;
    value->data->open(*this->fileName, std::ios::in | std::ios::out | std::ios::app);
    if(value->data->gcount()<wantedIndex)
        throw "not enough characters in the file - exception from char * file::operator[](int)";
    for(i=0;i<wantedIndex;i++)
        *a=value->data->get();
    value->data->close();
    return a;
}


// TERMINAL FUNCTION
