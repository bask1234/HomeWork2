#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include "file.hpp"
#include "Folder.hpp"
#include "Root.hpp"


using namespace std;


// this function splits a string into vector that contains words separeted by ' '
void split(const string &s, char delim, vector<string> &elems) {
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
}

// utility function for split 
vector<string> split(const string &s, char delim) {
    vector<string> elems;
    split(s, delim, elems);
    return elems;
}

void PrintVector(vector<string>& vector)
{
    unsigned int i;
    // this function prints the commands list after every iteration
    cout << "\n";
    for(i=0;i<vector.size();i++)
    {
        cout << vector[i] << "\n" ;
        
    }
}

void FillCommandNamesVector(vector<string>& menuVector, vector<string>& commandVector)
{
    string temp;
    
    for(unsigned int i=0;i<10;i++) // checking command names from 1-10
    {
        temp=menuVector[i].substr(4,menuVector.size());
        commandVector.push_back(temp);
    }
    for(unsigned int i=10;i<menuVector.size();i++) // checking command names from 10-end
    {
        temp=menuVector[i].substr(5,menuVector.size());
        commandVector.push_back(temp);
    }
    return;
}

void FillMenuVector(vector<string>& menuVector)
{   
    menuVector.push_back("[1] read FILENAME POSITION");
    menuVector.push_back("[2] write FILENAME POSITION CHARACTER");
    menuVector.push_back("[3] touch FILENAME");
    menuVector.push_back("[4] copy SOURCE_FILENAME TARGET_FILENAME");
    menuVector.push_back("[5] remove FILENAME");
    menuVector.push_back("[6] move SOURCE_FILENAME TARGET_FILENAME");
    menuVector.push_back("[7] cat FILENAME");
    menuVector.push_back("[8] wc FILENAME");
    menuVector.push_back("[9] ln TARGET_FILENAME LINK_NAME");
    menuVector.push_back("[10] mkdir FOLDERNAME");
    menuVector.push_back("[11] chdir FOLDERNAME");
    menuVector.push_back("[12] rmdir FOLDERNAME");
    menuVector.push_back("[13] ls FOLDERNAME");
    menuVector.push_back("[14] lproot");
    menuVector.push_back("[15] pwd");
    menuVector.push_back("[16] exit");
}

void FillCommandNumbersMap(map<string,int>& commandMap) // this function fills the command map
{
   
    commandMap["read"]=1;
    commandMap["write"]=2;
    commandMap["touch"]=3;
    commandMap["copy"]=4;
    commandMap["remove"]=5;
    commandMap["move"]=6;
    commandMap["cat"]=7;
    commandMap["wc"]=8;
    commandMap["ln"]=9;
    commandMap["mkdir"]=10;
    commandMap["chdir"]=11;
    commandMap["rmdir"]=12;
    commandMap["ls"]=13;
    commandMap["lproot"]=14;
    commandMap["pwd"]=15;
    commandMap["exit"]=16;
}

void FillCommandMap(map<string,int>& commandMap) // this function fills the command map
{
    
    commandMap["read"]=2;
    commandMap["write"]=3;
    commandMap["touch"]=1;
    commandMap["copy"]=2;
    commandMap["remove"]=1;
    commandMap["move"]=2;
    commandMap["cat"]=1;
    commandMap["wc"]=1;
    commandMap["ln"]=2;
    commandMap["mkdir"]=1;
    commandMap["chdir"]=1;
    commandMap["rmdir"]=1;
    commandMap["ls"]=0;
    commandMap["lproot"]=0;
    commandMap["pwd"]=0;
    commandMap["exit"]=0;
}

file * fileFinder2(string * searchedFileName, Folder & targetFolder) throw (file *)
{
    int tempInt;
    if(targetFolder.FilesVectorGetter().empty()==true)
            {
                return nullptr;
            }
    for(unsigned long i=0;i<targetFolder.FilesVectorGetter().size();i++)
            {
                //if(targetFolder.FilesVectorGetter()[i]->fileName==searchedFileName)
                //if((tempInt=targetFolder.FilesVectorGetter()[i]->fileName->compare(*searchedFileName))==0)
            tempInt=targetFolder.FilesVectorGetter()[i]->fileName->compare(*searchedFileName);
            if(tempInt==0) // checks if the file exists in the folder
                {
                    return(targetFolder.FilesVectorGetter()[i]);
                    break;
                }
            }
            return nullptr;
}

        
        
        
void RunCommand(vector<string>& parsedInput,map<string,int>& commandNumbersMap, Folder & targetFolder , Folder & rootFolder)
{
    // data members
    string commandName;
    string * arg1=nullptr, *arg2=nullptr, *arg3=nullptr, *pathLastIndex=nullptr, *secondPathLastIndex = nullptr;
    int convertedCommnad;
    unsigned long vectorIndex=0;
    
    vector<string> pathsVector;
    vector<string> secondPathVector; // is used just in case there are 2 path arguments
    file * tempFilePTR = nullptr;
    file * tempFilePTR2 = nullptr;
    Folder * tempFolderPTR =nullptr;
   
    // parsing
    if(parsedInput.size()>1)
    {
        arg1 = new string(parsedInput[1]);
        pathsVector = split(*arg1, '/'); // if arg1 was given as a file, the path and file name will be held in this vector while ignoring all the '/' in the file's path adress
        pathLastIndex = new string(pathsVector[pathsVector.size()-1]);
    
    }
 
    if(parsedInput.size()>2)
    {
        arg2 = new string(parsedInput[2]);
        secondPathVector = split(*arg2, '/');
        secondPathLastIndex = new string(pathsVector[pathsVector.size()-1]);
    }
    if(parsedInput.size()>3)
    {
        arg3 = new string(parsedInput[3]);
    }
    
    // parsing done
   
    
    commandName=parsedInput[0]; // extracts the current command name to a var
    convertedCommnad=commandNumbersMap[commandName];
    
    switch(convertedCommnad)
    {
        case 1: // read
        {
            char a;
            int tempIndex;
            try {
                tempIndex=stoi(*arg2);
                tempIndex++;
            } catch (exception) {
                cerr << "ERROE: argument 2 was not a number";
            }
            
            try
            { // finds if the file and folder we want exists
                tempFolderPTR=rootFolder.FilePathFinder(pathsVector, rootFolder, 1);
            }
            catch (const char * e)
            {
                cerr << " ERROR: " << e;
                break;
            }
            tempFilePTR=fileFinder2(pathLastIndex, *tempFolderPTR); // looking for the file in the path given to us
            if(tempFilePTR==nullptr)
            {
                cerr << " ERROR: file does not exist";
                break; // discontinue the case
            }
            tempFilePTR->dereferenceVAL().data->open(*pathLastIndex, std::ios::in | std::ios::out | std::ios::app);
            // opens file
            if(tempFilePTR->dereferenceVAL().data->gcount()< tempIndex)
                throw "not enough characters in the file";
            for( int i=0;i<tempIndex;i++)
            {
                a=tempFilePTR->dereferenceVAL().data->get();
            }
            tempFilePTR->dereferenceVAL().data->close();
            //cout << tempFilePTR->read(pathLastIndex, tempIndex) << endl;
            break;
            
        }
        case 2: // write
        {
            
            int tempIndex;
            char tempChar;
            // checking arguements
            if(arg2->size()>1)
                throw(" invalid number of characters to write, only 1 character allowed ");
            try {
                  tempIndex=stoi(*arg2);
            } catch (exception) {
                cerr << "ERROE: argument 2 was not a number";
            }
            try {
                 tempChar=*arg3->c_str();
            } catch (exception) {
                cerr << "ERROE: argument 3 was not a char";
            }
            // checking if the path exists
            try
            { // finds if the file and folder we want exists
                tempFolderPTR=rootFolder.FilePathFinder(pathsVector, rootFolder, 1);
            }
            catch (const char * e)
            {
                cerr << " ERROR: " << e;
                break;
            }
            
            // CHECKS DONE
    
            tempFilePTR=fileFinder2(pathLastIndex, *tempFolderPTR); // looking for the file in the path given to us
            if(tempFilePTR==nullptr)
            {
                tempFilePTR = new file(pathLastIndex);
                tempFolderPTR->FilesVectorGetter().push_back(tempFilePTR);
            }
            try
            {
                tempFilePTR->dereferenceVAL().data->open(*pathLastIndex, std::ios::in | std::ios::out | std::ios::app);
                // opens file
                *tempFilePTR->dereferenceVAL().data << tempChar;
                tempFilePTR->dereferenceVAL().data->close();
                tempFilePTR->write(pathLastIndex, tempIndex, tempChar);
                break;
            }
            catch (const char * e)
            {
                cerr << " ERROR: " << e;
                break;
            }
        }
    
        case 3:// touch
        {
            tempFolderPTR=rootFolder.FilePathFinder(pathsVector, rootFolder, 1); // finds the folder
            tempFilePTR=fileFinder2(pathLastIndex, *tempFolderPTR); // finds the file
                if(tempFilePTR==nullptr) // if file does not exist
                {
                    tempFilePTR = new file(pathLastIndex); // allocating new file
                    tempFolderPTR->FilesVectorGetter().push_back(tempFilePTR); // adding the new file to the file vector
                    tempFilePTR->touch(pathLastIndex);
                    break;
                }
                tempFilePTR->touch(pathLastIndex);
                break;
        }
        
        case 4: // copy
        {
            try {
                    tempFolderPTR=rootFolder.FilePathFinder(pathsVector, rootFolder, 0);
                }
            catch (const char * e)
            {
                cerr << " ERROR: " << e;
                break;
            }
            try {
                tempFilePTR=tempFolderPTR->FilesVectorGetter()[vectorIndex]; // turning tempFilePTR into source file
            }
            catch (const char * e) // incase source file does not exist
            {
                cerr << " ERROR: " << e;
                break;
            }
            try {
                tempFolderPTR=rootFolder.FilePathFinder(secondPathVector, rootFolder, 0); // searching the path to target file
            }
            catch (const char * e)
            {
                cerr << " ERROR: " << e;
                break;
            }
            try {
                tempFilePTR=tempFolderPTR->FilesVectorGetter()[vectorIndex]; // turning tempFilePTR into source file
            }
            catch (const char * e) // incase target file does not exist
            {
                tempFilePTR2 = new file(secondPathLastIndex);
                tempFilePTR2->touch(pathLastIndex); // refresh the file makes
                targetFolder.FilesVectorGetter().push_back(tempFilePTR2);
            }

            // we have both files at the tempFilePTRs
            tempFilePTR->copy(tempFilePTR2->fileName, *tempFilePTR2); // copy source file to target file
            
            break;
        }
        case 5: // remove
        {
            try {
                tempFolderPTR=rootFolder.FilePathFinder(pathsVector, rootFolder, 0);
            }
            catch (const char * e)
            {
                cerr << " ERROR: " << e;
                break;
            }
            // looking for file
            tempFilePTR=fileFinder2(pathLastIndex, *tempFolderPTR); // looking for the file in the path given to us
            if(tempFilePTR==nullptr)
            {
                cerr << " ERROR: file does not exist";
                break; // discontinue the case
            }
            tempFilePTR->remove(secondPathLastIndex);
            break;
        }
        case 6: // move
        {
            // looking for folder
            try {
                tempFolderPTR=rootFolder.FilePathFinder(pathsVector, rootFolder, 0);
            }
            catch (const char * e)
            {
                cerr << " ERROR: " << e;
                break;
            }
            // looking for file
            tempFilePTR=fileFinder2(pathLastIndex, *tempFolderPTR); // looking for the file in the path given to us
            if(tempFilePTR==nullptr)
            {
                cerr << " ERROR: file does not exist";
                break; // discontinue the case
            }
            // looking for second folder
            try {
                tempFolderPTR=rootFolder.FilePathFinder(secondPathVector, rootFolder, 0);
            }
            catch (const char * e)
            {
                cerr << " ERROR: " << e;
                break;
            }
            // looking for second file
            tempFilePTR2=fileFinder2(secondPathLastIndex, *tempFolderPTR); // looking for the file in the path given to us
            if(tempFilePTR==nullptr)
            {
                cerr << " ERROR: file does not exist";
                break; // discontinue the case
            }
            tempFilePTR->move(secondPathLastIndex, *tempFilePTR2);
            break;
        }
        case 7: // cat
        {
            // looking for folder
            try {
                tempFolderPTR=rootFolder.FilePathFinder(pathsVector, rootFolder, 0);
            }
            catch (const char * e)
            {
                cerr << " ERROR: " << e;
                break;
            }
            // looking for file
            tempFilePTR=fileFinder2(pathLastIndex, *tempFolderPTR); // looking for the file in the path given to us
            if(tempFilePTR==nullptr)
            {
                cerr << " ERROR: file does not exist";
                break; // discontinue the case
            }
            tempFilePTR->cat();
            break;
        }
        case 8: // wc
        {
            // looking for folder
            try {
                tempFolderPTR=rootFolder.FilePathFinder(pathsVector, rootFolder, 0);
            }
            catch (const char * e)
            {
                cerr << " ERROR: " << e;
                break;
            }
            // looking for file
            tempFilePTR=fileFinder2(pathLastIndex, *tempFolderPTR); // looking for the file in the path given to us
            if(tempFilePTR==nullptr)
            {
                cerr << " ERROR: file does not exist";
                break; // discontinue the case
            }
            tempFilePTR->wc();
            break;
        }
        case 9: // ln
        {
            unsigned int i;
            tempFolderPTR=rootFolder.FilePathFinder(pathsVector, rootFolder, 0); // searching for 1st path
            
            for(i=0;i<tempFolderPTR->FilesVectorGetter().size();i++)
            {
                if(tempFolderPTR->FilesVectorGetter()[i]->fileName==pathLastIndex) // searching the first file
                    tempFilePTR=tempFolderPTR->FilesVectorGetter()[i];
                if(i==tempFolderPTR->FilesVectorGetter().size()) // the file does not exist
                {
                    throw "  file a does not exist";
                }
            }
            tempFolderPTR=rootFolder.FilePathFinder(secondPathVector, rootFolder, 0); // searching for 2nd path
            for(i=0;i<tempFolderPTR->FilesVectorGetter().size();i++)
            {
                if(tempFolderPTR->FilesVectorGetter()[i]->fileName==pathLastIndex) // searching the first file
                    tempFilePTR2=tempFolderPTR->FilesVectorGetter()[i];
                if(i==tempFolderPTR->FilesVectorGetter().size()) // the file does not exist
                {
                    throw "  file a does not exist";
                }
            }
            tempFilePTR2->ln(tempFilePTR);
            
            break;
        }
        case 10: // mkdir
        {
            try{
                tempFolderPTR=rootFolder.FolderPathFinder(pathsVector, rootFolder, 1);
            }
            catch (const char * e)
            {
                cerr << "EXCEPTION: " << e << endl;
                 break;
            }
           
             tempFolderPTR->mkdir(pathLastIndex); // adds a new folder to the path's vector
             break;
        }
            
        case 11: // chdir
        {
            try{
                rootFolder.chdir(pathsVector, rootFolder);
            }
            catch (const char * e)
            {
                cerr << "EXCEPTION: " << e << endl;
                break;
            }
            throw targetFolder.chdir(pathsVector, rootFolder);
            break;
        }
         
        case 12:// rmdir
        {
            try {
                tempFolderPTR=rootFolder.FolderPathFinder(pathsVector, rootFolder, 0);
            }
            catch (const char * e)
            {
                cerr << " ERROR: " << e;
                break;
            }
            tempFolderPTR->rmdir(pathsVector, rootFolder);
            break;
        }
        case 13: // ls
        {
            targetFolder.ls();
            break;
        }
        case 14: // lproot
        {
            rootFolder.lproot();
            break;
        }
        case 15: // pwd
        {
            targetFolder.pwd();
            break;
        }
        case 16: // exit beein made at the menu function
        {
            break;
        }
        default: std::cout << "default\n"; // no error
            break;
    }
    
    // deletes
    if(arg1!=nullptr)
        delete(arg1);
    if(arg2!=nullptr)
        delete(arg2);
    if(arg3!=nullptr)
        delete(arg3);
    if(pathLastIndex!=nullptr)
        delete(pathLastIndex);
    if(secondPathLastIndex!=nullptr)
        delete(secondPathLastIndex);
    
    return; // return to menu
}

void Menu (vector<string>& menuVector)
{
    // menu data members
    string input; // these vars will hold the input from user and verify it
    vector<string> parsedInput; // this is where we keep the parsed input to send for verification
    vector<string> commandVector; // this will hold command names
    map<string,int> commandMap; // this will hold command names and num of arguments the command uses
    map<string,int> commandNunmbersMap; // this will hold command names and num of arguments the command uses
    Root * rootDirectory;
    
    
    //initialaize folder directory to root
    rootDirectory = new Root;
    Folder * rootDirectoryPTR;
    rootDirectoryPTR=rootDirectory->innerFoldersVector.at(0);
    Folder * targetFolderTEMP = nullptr;
    targetFolderTEMP=rootDirectory->innerFoldersVector[0];
    
    
    // fill data members
    FillCommandNamesVector(menuVector, commandVector); // extracting the command names from the menuVector
    FillCommandMap(commandMap); // filling the commands map with number of argument each command requires
    FillCommandNumbersMap(commandNunmbersMap); // filling the command numbers in order to use swich case in RunCommand function
    
    // code
        do {
            cin.clear();
            
            std::getline(cin, input); // gets the next line
            parsedInput = split(input, ' '); // parsing function
        if(parsedInput.size()>0)
        {
            if(commandMap.find(parsedInput[0])!=commandMap.end()) // if the command name was found
            {
                if(commandMap[parsedInput[0]]==(parsedInput.size()-1)) // makes sure the number of arguments is valid for the command
                {
                    try
                    {
                        RunCommand(parsedInput, commandNunmbersMap,*targetFolderTEMP, *rootDirectoryPTR);
                    }
                    catch (Folder * changeTargetToThat) // catching folder from chdir
                    {
                        targetFolderTEMP = changeTargetToThat;
                    }
                    catch (Folder changeTargetToThis) // catching folder from chdir
                    {
                        *targetFolderTEMP = changeTargetToThis;
                    }
                    catch (const char * e)
                    {
                        cerr << "EXCEPTION: " << e << endl;
                        break;
                    }
              
                }
            }
                else
                {
                    // invalid input case
                    cerr << "ERROR , invalid command or invalid number of arguments" << endl;
                }
            }
            else
            {
                cerr << "ERROR , Invalid Command" << endl;
            }
            
      } while( input !="exit");
    
   
    return;
}


// ___________________________________________ MAIN ___________________________________________
int main()
{
    vector <string> menuVector;
    
    FillMenuVector(menuVector); // fills the menu vector with the commands list
    Menu(menuVector); // the function works as the mini terminal
    
    return 0;
}



