#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <sstream>



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


        
        
void RunCommand(vector<string>& parsedInput,map<string,int>& commandNumbersMap)
{
    // data members
    string commandName;
    string * arg1=nullptr, *arg2=nullptr, *arg3=nullptr, *pathLastIndex=nullptr, *secondPathLastIndex = nullptr;
    int convertedCommnad;
    unsigned long vectorIndex=0;
    
    vector<string> pathsVector;
    vector<string> secondPathVector; // is used just in case there are 2 path arguments

   
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
          
        }
            
        
        
        case 2: // write
        {
          
        }
    
        case 3:// touch
        {
           
        }
        
        case 4: // copy
        {
           
        }
        case 5: // remove
        {
          
        }
        case 6: // move
        {
          
           
          
        }
        case 7: // cat
        {
          
        }
        case 8: // wc
        {
            
        }
        case 10: // mkdir
        {
            
        }
            
        case 11: // chdir
        {
            
        }
         
        case 12:// rmdir
        {
            
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

    
    //initialaize folder directory to root

    
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
                        RunCommand(parsedInput, commandNunmbersMap);
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



